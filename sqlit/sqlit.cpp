#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <regex>

using namespace std;
namespace fs = filesystem;

wstring replace(wstring main, wstring from, wstring to = L"") {
    return regex_replace(main, wregex(from), to);
}

vector<wstring> dir(const wstring path) {
    vector<wstring> out;
    for (const auto& e : fs::directory_iterator(path)) out.push_back(e.path().wstring());
    return out;
}

vector<wstring> filesInDir(const wstring path) {
    vector<wstring> out;
    for (const auto& e : fs::directory_iterator(path)) if (fs::is_regular_file(e.path())) out.push_back(e.path().wstring());
    return out;
}

void printVector(vector<wstring> q) {
    for (const auto w : q) wcout << w << endl;
}

wstring contents(const wstring path) {
    wifstream ifs(path);
    wstring content((istreambuf_iterator<wchar_t>(ifs)), (istreambuf_iterator<wchar_t>()));
    return content;
}

int wmain(int argc, wchar_t *argv[])
{
    wstring path = L"";
    if (argc > 1) {
        path = wstring(argv[argc - 1]);
        if (!fs::is_regular_file(path)) {
            wcout << L'"' << path << L'"' << L" is not a valid file";
            return 1;
        }
    }
    else {
        printVector(filesInDir(L"."));
        while (true) {
            cout << "File> ";
            wcin >> path;
            if (fs::is_regular_file(path)) break;
        }
    }
    wstring content = contents(path);
    content = replace(replace(content, L"\t", L"\", \""), L"\n", L"\"),\n(\"");
    wofstream ifs(path + L".sql");
    ifs << "(\"" << content << "\")";
    cout << "Done";
    return 0;
}