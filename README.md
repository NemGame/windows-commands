# Windows commands
## !DISCLAIMER! Some source codes may include swearing (lst does), the .exe's and .bat's don't
### My windows commands
### All were tested on Windows 10
<table>
    <thead>
        <tr>
            <th colspan="6">Contents</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><a href="#args-args">args</a></td>
            <td><a href="#cmdat">cmdat.</a></td>
            <td><a href="#cmdat-dir">cmdat</a></td>
            <td><a href="#csl">csl</a></td>
            <td><a href="#docs">docs</a></td>
            <td><a href="#docs_">docs_</a></td>
        </tr>
        <tr>
            <td><a href="#dup-filename--foldername">dup</a></td>
            <td><a href="#edit-filename">edit</a></td>
            <td><a href="#explorer">explorer.</a></td>
            <td><a href="#hf-path">hf</a></td>
            <td><a href="#hidefolder-path">hidefolder</a></td>
            <td><a href="#lst-dir">lst</a></td>
        </tr>
        <tr>
            <td><a href="#newfile-filename-content">newfile</a></td>
            <td><a href="#npm_-args">npm_</a></td>
            <td><a href="#rcmd">rcmd</a></td>
            <td><a href="#remove-path">remove</a></td>
            <td><a href="#remove_-file">remove_</a></td>
            <td><a href="#rename-path">rename</a></td>
        </tr>
        <tr>
            <td><a href="#rm-file">rm</a></td>
            <td><a href="#run-command">run</a></td>
            <td><a href="#sf-path">sf</a></td>
            <td><a href="#showfolder-path">showfolder</a></td>
            <td><a href="#sizeof-path">sizeof</a></td>
            <td><a href="#vscode-args">vscode</a></td>
        </tr>
    </tbody>
</table>

## ```args <args>```
### Just prints out the args given to it, used for debugging
## ```cmdat.```
### Runs the [cmdat](#cmdat-dir) command with the current directory
## ```cmdat <dir>```
### Opens a new command prompt in the given directory
## ```csl```
### Utility, misstyped cls
## ```docs```
### Navigates to the user's documents folder, fast
## ```docs_```
### Navigates to the user's documents folder, slow
## ```dup <filename / foldername>```
### Duplicates the given item
## ```edit <filename>```
### Opens the given file in notepad
## ```explorer.```
### Opens the file explorer in the current directory
## ```hf <path>```
### Shorthand for [hidefolder](#hidefolder-path)
## ```hidefolder <path>```
### Hides the given element, so that even the file explorer can't see it
### You can access it, by writing the path in the search bar
### Can be reversed with [sf](#sf-path) and [showfolder](#showfolder-path)
## ```lst <?dir>```
### Lists the files, folders and unkown things in the given directory, or where it was ran
## ```newfile <filename> <?content>```
### Creates a new file with the given name
### Unless you specify any content it's gonna be empty
## ```npm_ <?args>```
### Shorthand for ```npm.cmd``` (by NodeJS) for easier powershell use (mostly for vscode)
## ```rcmd```
### Opens a new command prompt in the same directory and closes itself
## ```remove <path>```
### Removes the path, be it a file or a folder, no discrimination here
## ```remove_ <file>```
### Rememberable ```del```
## ```rename <path>```
### Rememberable ```ren```
## ```rm <file>```
### Rememberable ```del```
## ```run <command>```
### Runs the given command in a new command prompt
### After execution, it waits for the Enter to be pressed and only that
## ```sf <path>```
### Shorthand for [showfolder](#showfolder-path)
## ```showfolder <path>```
### Reveals the path that [hf](#hf-path) and [hidefolder](#hidefolder-path) hid
## ```sizeof <path>```
### Returns the size of the file or folder with the given path
### Supported sizes: bytes, kilobytes, megabytes, gigabytes, terrabytes, petabytes, zettabytes, yottabytes
### If you need more create an issue and I'll add larger sizes to
## `vscode <?args>`
### Just calls ```code <args>``` (by Visual Studio Code)
### It runs as expected when written in the file explorer search bar, unlike ```code```
