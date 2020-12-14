# Installing from source
In general it's probably the most frequent way you'll install Xournal++, as there are pretty much no recent packages in repositories.

First of all you should clone this repository:
```bash
git clone https://github.com/xournalpp/xournalpp.git
cd xournalpp
```

## Dependencies

`readme/LinuxBuild.md` and other files try to document the dependencies: please update these files if you can.

## CMake
Xournal++ is built using CMake.

Here is the process of building with CMake:

1. Create the build directory – this is where all of the build files will be placed.

   ````bash
   mkdir build
   cd build
   ````

2. You can generate the basic configuration with

   ````bash
   cmake ..
   ````

   If this is failing on Ubuntu/Debian, even with `libpoppler-private-dev` installed, try changing the `POPPLER_INCLUDE_DIR` cmake option from `"POPPLER_INCLUDE_DIR-NOTFOUND"` to `"/usr/include/poppler"`. This is easy to do with `cmake-gui` as below.

   This will cause install commands (see step 4) to install `/usr` folders by default (requires root). You can install to a local directory such as `~/.local` by setting `cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local`

3. If you'd like to customize Xournal++ configuration you can tinker with cmake `-D` parameter, but it's much more convenient to execute

   ````bash
   cmake-gui ..
   ````

   Here you can configure all aspects of Xournal++ build.
   ![cmake-gui](http://i.imgur.com/EYwXMuL.png)

   There are few configuration categories (grouping can be activated with `Grouped` checkbox):
   - **ENABLE** – basic stable features support
   - **UNSTABLE** – unstable, in development features
   - **DEV** – development options, which in most cases should be leaved as they are
   - **TEST** – optional features of CppUnit tests
   - **BUILD** – build dependency libraries and link them statically
   - **EXT** – add dependency basing on precompiled deb packages (UNIX only)
   - **PATH** – here you can specify alternative location of these binaries

   Some of these categories, or some single settings can be unavailable from beginning – they may depend on some other config flags (i.e., to enable entire `TEST` group, first of all you have to enable `ENABLE_CPPUNIT`)

   It's worth mentioning that there are also some hidden options that are shown when `Advanced` is checked. However, don't modify them if you don't know what they can do, or else it will result in unexpected behavior (please don't report bugs if you've made such changes or you've been specifically asked to in a bug report).

   All custom options are listed in `README` file under `cmake` directory.

   After making all changes you should click `Generate` button to generate Makefiles. In the console you can see all configuration steps and at the ending some general info about used features.

   Now you can close cmake-gui.

4. Now it's time for real building :)

   To do this you have just to execute `cmake --build .` in the build directory. You can also specify a specific target using `cmake --build . --target <target>`:
   - **xournalpp** – main executable (found in `build/src` dir)
   - **xournal-thumbnailer** – thumbnailer used to extract thumbnails from .xoj files (found in `build/src/xoj-preview-extractor`)
   - **xournalpp-test** – CppUnit testing binary, which should be executed after any kind of source edit (found in `build/test`)
   
   Other binary targets are used for internal building support:
   - **xournalpp-core** – used by `xournalpp` and `xournalpp-test` targets
   - **util** – util static library (from path `src/util`) used by `xournalpp` and `xournalpp-test` targets

   If you have multicore processor you can build with `make -jN` where N is number of simultaneous jobs.

5. To install entire package execute, you first need to compile it:
   
   ````bash
   cmake --build .
   ````

   Then you can install it with (if you need sudo, be careful--it may create files with root permissions in the build directory)
   ```bash
   cmake --build . --target install
   ```

   It'll install all needed files (of course without `xournalpp-test`) including desktop files and translations.

# Building a pull request

First, you need to find the URL of the repository of the PR. You can do this by going to the PR page and looking for `XXX wants to merge N commits into xournalpp:master from YYY`. The `YYY` part should have the format `Username:Branchname`.

Then, you can checkout the PR with
```bash
git clone https://github.com/Username/xournalpp -b Branchname
```
where you will need to replace `Username` and `Branchname` with the ones you just found.

Afterwards, you can compile and install Xournal++ like above.