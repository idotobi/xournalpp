Please follow these steps to provide information required to solve input related bugs:

1. Clone the source code (with the appropriate repo/branch, if needed):
```
git clone https://github.com/xournalpp/xournalpp
cd xournalpp
mkdir build && cd build
```
2. (Re)Generate build files with the input debug flags unset:
```
cmake -UDEBUG_INPUT_GDK_PRINT_EVENTS -UDEBUG_INPUT ..
```
3. Build Xournal++ with the following command:
```
cmake -DDEBUG_INPUT=ON ..
cmake --build .
```
4. Run Xournal++ from the console (!) and follow the steps to reproduce the error (Try to do as few steps as possible)
```
./src/xournalpp > debug_input.log 2>&1
```
5. Build Xournal++ once again with the following command:
```
cmake -DDEBUG_INPUT_GDK_PRINT_EVENTS=ON ..
cmake --build .
```
6. Run Xournal++ from the console (!) and follow the steps to reproduce the error (Try to do as few steps as possible)
```
./src/xournalpp > debug_gdk_input.log 2>&1
```
7. Unset the debug flags (you may want to compile again afterwards if you don't want to see the debug output):
```
cmake -UDEBUG_INPUT_GDK_PRINT_EVENTS -UDEBUG_INPUT ..
```

8. Attach the files `debug_input.log` and `debug_gdk_input.log`, found in your current working directory, to the bug report

9. Attach the output of the command `xinput list` if you use X.org (respectively `libinput list-devices` if you use Wayland)
