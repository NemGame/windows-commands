#include <iostream>
#include <filesystem>
#include <cpp/printfw.h>
#include <cpp/table.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <Windows.h>
#include <exception>
#include <utility>
#include <sstream>
#include <regex>
#include <format>
#include <cmath>
#include <string_view>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

const vector<wstring> argvToVector() {
    vector<wstring> args;
    if (__wargv) {
        for (int i = 0; i < __argc; ++i) args.push_back(__wargv[i]);
        return args;
    }
    // Fallback: convert narrow __argv to wide
    for (int i = 0; i < __argc; ++i) {
        int len = MultiByteToWideChar(CP_UTF8, 0, __argv[i], -1, nullptr, 0);
        if (len > 0) {
            wstring w(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, __argv[i], -1, &w[0], len);
            if (!w.empty() && w.back() == L'\0') w.pop_back();
            args.push_back(move(w));
        } else {
            args.push_back(L"");
        }
    }
    return args;
}

const int PrintHelp() {
    try {
        int width = 100;
        try {
            int cw = TableConsoleWidth();
            double c = floor(cw / 1.1);
            width = static_cast<int>(min(c, cw - 10));
        }catch (const exception&) {}
        wstring h = format(LR"(Lists the contents of the given/current directory.

Parameters:
    /?, -help, --help              |    Shows this help message
    -l                             |    Prints the output in a table format
    -nd, -no-decoration            |    Disables the decorative lines in the output
    -h, -header                    |    Enables headers for sections
    -debug                         |    Shows some pre-runtime infos, such as path
    -deep-debug                    |    Different from -debug, it shows runtime infos, such as item load and suppressed errors
    --version                      |    Shows the version of the program
    --type [files,folders,unknown] |    Filters the output by type, multiple allowed with separator ','
    |   Shorthands: files = f, file; folders = ff, dir, folder; unknown = fff, u, fuck
    |
    |{}
    |    May be provided multiple times, multiple params allowed with separator ','
    |    or  - ',' separation
    |    and - multiple provided (e.x. --search girl --search .mp4
    --search [param]               |    Only shows stuff whose names contain [non-case-sensitive]
    |   Shorthands: --s [param]    |
    --filter [param]               |    Only shows stuff whose names contain [case-sensitive]
    |   Shorthands: --f [param]    |
    --regex [param]                |    Only shows stuff whose names match the regex expression
    |   Shorthands: --r [param])", wstring(width, L'-'));
        printfw(h);
        return 0;
    }
    catch (const exception&) {
        return 1;
    }
}

const vector<wstring> splitw(const wstring& s, const wchar_t& sep = L',') {
    vector<wstring> out;
    wstring temp;
    wstringstream ss(s);
    while (getline(ss, temp, sep)) out.push_back(temp);
    return out;
}

bool IsFullPath(const wstring& path) {
    static const wregex drive_regex(LR"([A-Za-z]:)");
    return regex_search(path, drive_regex);
}

int PrintTables(const vector<wstring>& dirs, const vector<wstring>& files, const vector<wstring>& heh) {
    if (!dirs.empty()) PrintTable(dirs, 0.8);
    if (!files.empty()) PrintTable(files, 0.8);
    if (!heh.empty()) PrintTable(heh, 0.8);
    return 0;
}

const wstring replacew(const wstring_view original, const wstring_view find, const wstring_view replace = L"") {
    wstring out(original);
    size_t pos = 0;
    while ((pos = out.find(find, pos)) != wstring::npos) {
        out.replace(pos, find.length(), replace);
        pos += replace.length();
    }
    return out;
}

bool containsw(const wstring_view s, const wstring_view substring) {
    return s.find(substring) != wstring_view::npos;
}

const wstring normalizew(const wstring_view text) {
    wstring lower;
    lower.reserve(text.length());
    for (const wchar_t& c : text) lower.push_back(towlower(c));
    return lower;
}

bool CheckFilter(const wstring_view text,
    const vector<vector<wstring>>& search,
    const vector<vector<wstring>>& filter,
    const vector<vector<wstring>>& regexes) {
    // --search : case-insensitive "contains" (AND of ORs)
    if (!search.empty()) {
        const wstring ntext = normalizew(text);
        for (const auto& ands : search) {
            bool groupMatch = false;
            for (const auto& maybe : ands) {
                if (containsw(ntext, normalizew(maybe))) {
                    groupMatch = true;
                    break;
                }
            }
            if (!groupMatch) return false;
        }
    }

    // --filter : case-sensitive "contains" (AND of ORs)
    if (!filter.empty()) {
        for (const auto& ands : filter) {
            bool groupMatch = false;
            for (const auto& maybe : ands) {
                if (containsw(text, maybe)) {
                    groupMatch = true;
                    break;
                }
            }
            if (!groupMatch) return false;
        }
    }

    // --regex : regex match (AND of ORs). invalid regex patterns are treated as non-matching.
    if (!regexes.empty()) {
        const wstring stext(text);
        for (const auto& ands : regexes) {
            bool groupMatch = false;
            for (const auto& pattern : ands) {
                try {
                    const wregex re(pattern);
                    if (regex_search(stext, re)) {
                        groupMatch = true;
                        break;
                    }
                }
                catch (const regex_error&) {
                    // invalid pattern -> ignore this pattern (treat as non-matching)
                }
            }
            if (!groupMatch) return false;
        }
    }

    return true;
}

class Settings{
public:
    bool headers = false;
    bool decoration = true;
    bool debug = false;
    bool deep_debug = false;
    bool show[3] = { true, true, true };
    bool table = false;
};

const double version = 0.3;

int main() {
    vector<wstring> args = argvToVector();
    wstring path = L".";
    Settings settings;
    vector<vector<wstring>> search, filter, regex;
    for (int i = 1; i < args.size(); ++i) {
        const wstring arg = args[i];
        const bool islast = i == args.size() - 1;
        if (arg == L"/?" || arg == L"-help" || arg == L"--help") return PrintHelp();
        if (arg == L"--v" || arg == L"--version") {
            cout << version << endl;
            return 0;
        }
        if (arg == L"-debug") {
            settings.debug = true;
            continue;
        }
        if (arg == L"-deep-debug") {
            settings.deep_debug = true;
            continue;
        }
        else if (arg == L"-h" || arg == L"-header") {
            settings.headers = true;
            continue;
        }
        else if (arg == L"-nd" || arg == L"-no-decoration") {
            settings.decoration = false;
            continue;
        }
        else if (arg == L"-l") {
            settings.table = true;
            continue;
        }
        else if (arg == L"--type") {
            if (islast) break;
            const wstring nextarg = args[++i];
            settings.show[0] = false;
            settings.show[1] = false;
            settings.show[2] = false;
            for (const wstring& ws : splitw(nextarg)) {
                if (ws == L"folder" || ws == L"dir" || ws == L"ff") settings.show[0] = true;
                else if (ws == L"file" || ws == L"files" || ws == L"f") settings.show[1] = true;
                else if (ws == L"unknown" || ws == L"fuck" || ws == L"fff") settings.show[2] = true;
            }
        }
        else if (arg == L"--search" || arg == L"--s") {
            if (islast) break;
            const wstring nextarg = args[++i];
            search.push_back(splitw(nextarg));
        }
        else if (arg == L"--filter" || arg == L"--f") {
            if (islast) break;
            const wstring nextarg = args[++i];
            filter.push_back(splitw(nextarg));
        }
        else if (arg == L"--regex" || arg == L"--r") {
            if (islast) break;
            const wstring nextarg = args[++i];
            regex.push_back(splitw(nextarg));
        }
        else {
            path = (IsFullPath(arg) ? L"" : fs::current_path().wstring()) + L'\\' + arg;
        }
    }
    fs::path dirPath = path;
    if (settings.debug) {
        cout << "Paths:" << endl;
        wcout << dirPath.root_directory().wstring() << endl;
        cout << "fs " << fs::current_path() << endl;
        wcout << L"path " << path << endl;
        wcout << L"huh " << dirPath << endl << endl;
    }

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        cout << "The given path is not a valid directory." << endl;
        return 1;
    }
	vector<wstring> dirs, files, huh;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        const wstring path = entry.path().filename().wstring();
        if (settings.deep_debug) wcout << "[????] " << path << '\r';
        if (!CheckFilter(path, search, filter, regex)) {
            if (settings.deep_debug) wcout << "[XXXX]" << endl;
            continue;
        }
        try {
            if (fs::is_directory(entry.status())) {
                if (settings.deep_debug) wcout << "[DIR ]" << endl;
                dirs.push_back(path);
            }
            else if (fs::is_regular_file(entry.status())) {
                if (settings.deep_debug) wcout << "[FILE]" << endl;
                files.push_back(path);
            }
            else {
                if (settings.deep_debug) wcout << "[HUH ]" << endl;
                huh.push_back(path);
            }
        }
        catch (const exception&) {
            if (settings.deep_debug) cout << endl;
            huh.push_back(path);
        }
    }
    if (settings.deep_debug) cout << endl;

    const bool showDirs = dirs.size() > 0 && settings.show[0], showFiles = files.size() > 0 && settings.show[1], showHuh = huh.size() > 0 && settings.show[2];

    if (!showDirs && !showFiles && !showHuh) {
        cout << "The given folder doesn't contain anything";
        return 0;
    }

    if (settings.table) return PrintTables(dirs, files, huh);

    if (showDirs) {
        if (settings.decoration) {
            printfwl(settings.headers ? L"=========Folders=========" : L"=========================");
        }
        for (const wstring& d : dirs) printfwl(d);
        if (showFiles || showHuh) cout << endl;
    }

    if (showFiles) {
        if (settings.decoration) {
            if (settings.headers) printfwl(L"==========Files==========");
            else if (!showDirs) printfwl(L"=========================");
        }
        for (const wstring& f : files) printfwl(f);
        if (showHuh) cout << endl;
    }

    if (showHuh) {
        if (settings.decoration) {
            if (settings.headers) printfwl(L"===========Huh===========");
            else if (!showDirs && !showFiles) printfwl(L"=========================");
        }
        for (size_t i = 0; i < huh.size(); ++i) {
            printfwl(huh[i]);
        }
    }
    if (settings.decoration) {
        printfw(L"=========================");
    }

    if (settings.debug) cout << "d" << showDirs << " f" << showFiles << " u" << showHuh;
    return 0;
}