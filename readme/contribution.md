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