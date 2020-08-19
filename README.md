![License](https://img.shields.io/github/license/GigaGrunch/imageviewer?style=for-the-badge)
![Language](https://img.shields.io/github/languages/top/GigaGrunch/imageviewer?label=lang&logo=C&style=for-the-badge)
![LastCommit](https://img.shields.io/github/last-commit/GigaGrunch/imageviewer?style=for-the-badge)
![RepoSize](https://img.shields.io/github/repo-size/GigaGrunch/imageviewer?style=for-the-badge)

*This is just a practice project.*
* simple image viewer, written in C
* uses [SDL](https://www.libsdl.org/) for now so I don't have to worry as much about platform stuff
* currently runs on Windows and Linux, but MacOS should be trivial

### Building
This is a unity build, simply compile `<platform>_imageviewer.c` with a C-compiler. You can use the provided build scripts for that.
* the **Linux** script uses the `cc` command which should be linked to either [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/)
* the **Windows** script uses the `cl` command so [Visual Studio](https://visualstudio.microsoft.com/) has to be installed
* in **Windows**, you will have to setup SDL in the correct way so it can be included and linked — [I'll describe the setup when I'm on a Windows machine again](https://github.com/GigaGrunch/imageviewer/issues/1)
* output will be stored in `build/`
