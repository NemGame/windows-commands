# Windows commands
## !DISCLAIMER! Some source codes may include swearing (lst does), proceed with caution
### My windows commands
### If a .exe doesn't work, recompile it, I used `gcc` for some, but that needs some dlls, I'll recompile and update them later
### All were tested on Windows 10
## The `my/` includes can be found [here](https://github.com/NemGame/C-modules)
<table>
    <thead>
        <tr>
            <th colspan="6">Contents</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><a href="#adminhere-path">adminhere</a></td>
            <td><a href="#args-args">args</a></td>
            <td><a href="#boop">boop</a></td>
            <td><a href="#cmdat">cmdat.</a></td>
            <td><a href="#cmdat-dir">cmdat</a></td>
            <td><a href="#csl">csl</a></td>
        </tr>
        <tr>
            <td><a href="#docs">docs</a></td>
            <td><a href="#docs_">docs_</a></td>
            <td><a href="#dup-filename--foldername">dup</a></td>
            <td><a href="#edit-filename">edit</a></td>
            <td><a href="#explorer">explorer.</a></td>
            <td><a href="#hf-path">hf</a></td>
        </tr>
        <tr>
            <td><a href="#hidefolder-path">hidefolder</a></td>
            <td><a href="#isadmin">isadmin</a></td>
            <td><a href="#ls-dir">ls</a></td>
            <td><a href="#lst-dir">lst</a></td>
            <td><a href="#music">music</a></td>
            <td><a href="#newfile-filename-content">newfile</a></td>
        </tr>
        <tr>
            <td><a href="#no">no</a></td>
            <td><a href="#npm_-args">npm_</a></td>
            <td><a href="#rcmd">rcmd</a></td>
            <td><a href="#remove-path">remove</a></td>
            <td><a href="#remove_-file">remove_</a></td>
            <td><a href="#rename-path">rename</a></td>
        </tr>
        <tr>
            <td><a href="#rm-file">rm</a></td>
            <td><a href="#run-command">run</a></td>
            <td><a href="#runq-command">runq</a></td>
            <td><a href="#runqw-command">runqw</a></td>
            <td><a href="#sf-path">sf</a></td>
            <td><a href="#showfolder-path">showfolder</a></td>
        </tr>
        <tr>
            <td><a href="#sizeof-path">sizeof</a></td>
            <td><a href="#vscode-args">vscode</a></td>
            <td><a href="#ye">ye</a></td>
            <td><a href="#zene">zene</a></td>
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
### Runs the given command and waits for specifically the return key to be pressed
## `runq <command>`
### Runs the given command and instantly quits
## `runqw <command>`
### Runs the given command, waits for the return key to be pressed, then quits
## ```sf <path>```
### Shorthand for [showfolder](#showfolder-path)
## ```showfolder <path>```
### Reveals the path that [hf](#hf-path) and [hidefolder](#hidefolder-path) hid
## ```sizeof <path>```
### Returns the size of the file or folder with the given path
### Supported sizes: bytes, kilobytes, megabytes, gigabytes, terrabytes, petabytes, exabytes, zettabytes, yottabytes
### If you need more, create an issue and I'll add larger sizes to it
## ```vscode <?args>```
### Just calls ```code <args>``` (by Visual Studio Code)
### It runs as expected when written in the file explorer search bar, unlike ```code```
## `adminhere <?path>`
### It opens a new command prompt (terminal) window, the path by default is the current working directory
## `isadmin`
### Returns "ye" if user has admin rights, otherwise returns "no"
## `boop`
### Beeps
## `ls <?dir>`
### Lists the contents of the given directory, if no path is given, path will be the current working directory
## `music`
### Navigates to the user's music directory
## `no`
### Doesn't do anything
## `ye`
### Returns ye
## `zene`
### Alias for [music](#music)
