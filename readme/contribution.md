# How to contribute


## Get the repo

```bash
git clone http://github.com/xournalpp/xournalpp.git
```

## Build for the very fist time

```bash
cd xournalpp
mkdir build
cd build
cmake ..
cmake --build .
# For a faster build, set the flag -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

## Rebuild

After this it should be sufficient to just call make unless you changed `CMakeLists.txt`.

```bash
cd build
make -j 4
```

## How to change the UI

The user interface is created via [glade](https://glade.gnome.org/), which is "a RAD tool to enable quick & easy development of user interfaces for the `GTK+` toolkit and the GNOME desktop environment".

To change an existing UI component:

 1. search for it under `/ui`
 2. open `glade`
 3. from within glade open the file
 4. do your thing
 5. save

If you are perfectionist you can optimize the produced xml to produce a minimal diff by hand, but make sure that it still works after meddling with it 😉.

If you need to find the `.cpp` file that defines the ui component you can ususually find it at `/src/gui`.
To streamline the process just search for `$GLADE_FILE_NAME` in all `.cpp` files.

## Debugging

### Poor Mans Debugger

If you didn't figure out yet how to get the debugger working, there's always the trusty way of "print debugging".
Keep in mind that in the long run the time invested in learning to use the debugger will pay off.

In case you still want to quickly test an hypothesis, simply sprinkle `g_message("$your_unique_debug_message");` over your code.
Compile, run from cli, and just follow the output in the commandline while interacting with xournalpp.


## VSCode

Recommended plugins:
 * `ms-vscode.cpptools`
 * `ms-vscode.cmake-tools`
 * `eamodio.gitlens`

 ### Settings

 My settings under `Preferences: Open Settings (JSON)`:

 ```json
 {
    "cmake.configureOnOpen": false,
    "cmake.buildArgs": [
        "-j 3"
    ],
    "[cpp]": {
        "editor.defaultFormatter": "ms-vscode.cpptools"
    },
    "C_Cpp.clang_format_fallbackStyle": "LLVM",
    "window.zoomLevel": 0,
    "editor.formatOnSave": true,
    "debug.toolBarLocation": "docked"
}
 ```

### Build using cmake

    F7 -> CMake: Build

### Start Debugging Session

    Ctrl + F5 -> CMake: Debug