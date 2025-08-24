# Windows commands
### My windows commands
### All were tested on Windows 10
### Contents:
- [args](#args-args)
- [cmdat.](#cmdat)
- [cmdat](#cmdat-dir)
- [csl](#csl)
- [docs](#docs)
- [docs_](#docs_)
- [dup](#dup-filename--foldername)
- [edit](#edit-filename)
- [explorer.](#explorer)
- [hf](#hf-path)
- [hidefolder](#hidefolder-path)
- [lst](#lst-dir)
- [newfile](#newfile-filename-content)
- [npm_](#npm_-args)
- [rcmd](#rcmd)
- [remove](#remove-path)
- [remove_](#remove_-file)
- [rename](#rename-file)
- [rm](#rm-file)
- [run](#run-command)
- [sf](#sf-path)
- [showfolder](#showfolder-path)
- [vscode](#vscode-args)
## ```args <args>```
### Just prints out the args given to it, used for debugging
## ```cmdat.```
### Runs the [cmdat](#cmdat-2) command with the current directory
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
## ```vscode <args>```
### Just calls ```code <args>``` (by Visual Studio Code)
### It runs as expected when written in the file explorer search bar, unlike ```code```
