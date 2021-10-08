This wiki page describes the Coding Conventions of Xournal++, if you use an IDE, you may find a formatter configuration for your IDE in development/coding-conventions folder in main repo tree. If not, you may create one and push it.

# File Conventions
The files are structured modular in subfolders. Each class consist of two files, a .cpp and a .h file (even if C++ is used, the files are always named .h, not .hpp).

If there is a small helper class (less than 100 lines of code) it may also be placed in the Parent class file.

The class- and filename have no prefix, so the filename and classname are the same.

File encoding is always UTF-8, without BOM.

To prevent including header files twice, each one should contain as first code line

```cpp
#pragma once
```
All current compilers support this construct. This is the modern equivalent of
```cpp
#ifndef MY_FILE_H 
#define MY_FILE_H
// some code
#endif
```

# Code formatting
## Use clang-format
_Currently we are using version 9. Check your usual installation options first then see the download area at https://llvm.org/  (note the Ubuntu Apt and Win sections)._

Developers tend to use the automatic format functions of their IDE's, those aren't configured the same way other developers configured theirs, and they even differ between your own workstations.

Instead of letting the developers configure their format function, we provide a clang-format configuration file.
Clang-format is mostly IDE and platform independent, it is also supported by mostly every IDE.

This will reduce merge conflicts due different formatting.
We also don't accept PR's if the format of your changed files is wrong, 
so before a pull request, clang-format must be used.

We provide the .clang-format property file in the project root.
Clang-format is a platform and IDE independent tool from the LLVM Compiler Infrastructure project.
For further information take a look at https://clang.llvm.org/docs/ClangFormat.html

You can quickly reformat all your changed lines with:

`git-clang-format-9 Commit_name_or_Hash`, make sure, your changes are staged and not committed.

Example:

`git-clang-format-9 HEAD~6` will reformat only the changes made in the last 6 commits. 


_Note: You may need to specify the git-clang binary ( or link git-clang-8 to git-clang)_

## Indentation
* Spaces are used for indentation, indentation is 4 spaces.
* Each if, for, while etc. are followed by curly braces, even if it only contains one line of code (because this is a common case for errors, e.g. search for "Apple goto fail bug")
* if, for, while etc. are followed by a space, after the braced there is no space, e.g.

```cpp
if (a != b) {
    doSomething()
}
```
* return needs no braces, e.g.

```cpp
return a;
return a != b;
```
**not**

```cpp
return (a);
return (a != b);
```
* Line width is 120 chars. The 80 char limit was historical for printing, printing is usually not used any more, and 120 Chars is even on small notebooks or tables readable, so it should be a good compromise.

* Declare only one variable at once, don't do something like ```int* x, y``` (x is a pointer, y not)
* Write the * of pointer to the type, e.g. ```int* x```, not ```int *x```

## Documentation
* Use doxygen / javadoc compatible documentation tags, e.g.
```cpp
/**
 * Documentation of i
 */
int i;

```

* Add a space after __//__ on single line comments, e.g. ```// This is a comment```

## Includes

Includes should be sorted. General idea is that they should be sorted alphabetically in some groups (from the top):
- for `cpp` files corresponding `h` header
- std libraries
- external libraries (such as boost, glib, poppler, gtk)
- from other dirs absolute paths / Xournal++ utils
- local headers (from the same dir)

If there's long list, these groups should be divided with empty line:
````cpp
#include "Control.h"

#include <ctime>
...
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <gio/gio.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>

#include "gui/TextEditor.h"
#include "gui/XournalView.h"
...
#include "gui/toolbarMenubar/model/ToolbarData.h"
#include "gui/toolbarMenubar/model/ToolbarModel.h"
#include "jobs/AutosaveJob.h"
#include "jobs/BlockingJob.h"
...
#include "util/cpp14memory.h"
#include "view/DocumentView.h"
#include "view/TextView.h"
#include "xojfile/LoadHandler.h"

#include "CrashHandler.h"
#include "FullscreenHandler.h"
#include "LatexController.h"
...
#include "UndoRedoController.h"
#include "Util.h"
#include "XojMsgBox.h"
#include "config-dev.h"
#include "config-features.h"
#include "config.h"
#include "i18n.h"

namespace fs = boost::filesystem;
using namespace std;
````

## Namespaces
using directives and declarations like `using namespace ns_name` and `using ns_name::name` are undesirable in headers. Same for namespace alias definitions.

## Header header
Every header should start with general info comment:
````cpp
/*
 * Xournal++
 *
 * [Header description]
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */
````
# Naming Conventions
## General
* Names are CamelCase (namespaces, classes, structs, enums, etc.)
* Members are camelBack
* Functions are camelBack
* No underlines are used

* Use short concise names - as short as possible as long as necessary
** E.g. do not use unknown abbreviations like ```int lnWidth```, which is not clear without context, but ```int lineWidth``` is clear.
**Common short names should be used, e.g. ```int dpi``` is Ok, because it is well known.

## Classes, structs and namespaces
shall not contain prefixes or suffixes, and are written CamelCase, starting with a *uppercase* letter

## Members and Functions
shall not contain prefixes or suffixes, and are written camelBack, starting with a *lowercase* letter

## Overload operators
Please don't use overload operators to extensive. Overload "==", "=" etc. are OK and usual.
But don't do unexpected things.

## TODO Comments
Try to avoid unclear TODO comments, e.g. ```// TODO streams``` is really unclear.

Always write your name or the name of the relevant persons behind the todo, eg. ```// Todo (John Doe, Fred Doe) ...```

If there is a TODO which really should be done write a sentence or two what should be done why.

Open an issue for Todo's.

## Common mistakes, please avoid them
### Initialize all members
All constructors should initialize all members, even if not all are used. Initialize them in the body.
Use lambdas or inline/constexpr functions to initialize post evaluated variables.

### Memory 
#### Avoid to allocate objects on the heap, especially if they are only used locally.
Using the heap is almost slower than using the stack you also don't need to be aware of memory leaks.
Only use the heap for big objects, objects with a dynamic size or if you have to expand the lifetime of an object. 
#### Always try to expand the lifetime with "auto const&" or "auto&&" in combination with copy elision first.
#### Use RAII containers to manage memory in newly written code like ```std::unique_ptr``` or ```std::shared_ptr```.
Note: be very careful with pointers to objects from C library dependencies. For example, GLib/GTK implements its own reference counting mechanism and may not be compatible with STL smart pointers. Additionally, a object from a C library may require specific new/destroy method pairs for allocation and deallocation (e.g. `cairo_surface_create`/`cairo_surface_destroy`). For such objects, you will need to implement a custom deleter in order to use a STL smart pointer.
#### Don't use new or delete anymore, because humans make mistakes and forget to delete their objects.
You'll also always get an memory leak, if a unexpected exception isn't catched in this scope.
Since dtor's are always called after leaving a scope, RAII memory container will call delete in his dtor even if an exception is thrown.

Examples: 

Wrong:
```cpp
{
    auto* ptr = new MySmalHelperObj();
    myFunMayThrow(); //Memory leak & no call to ~MySmalHelperObj();
    /*...*/
    delete ptr; // Explicit call of ~MySmalHelperObj();
}
```

Right & ok:
```cpp
{
    auto helper_ptr = std::make_unique<MySmalHelperObj>(); //local Stack Object
    myFunMayThrow();
    /*...*/
} // Implicit call of ~std::unique_ptr<MySmalHelperObj>();
```

Right but better:
```cpp 
{
    auto helper = MySmalHelperObj(); //local Stack Object
    myFunMayThrow(); //No memory leak;
    /*...*/
} // Implicit call of ~MySmalHelperObj();
```

Wrong:
```cpp 
{
MyObj* getMyObject(){  
    auto* ptr = new MyObj();
    ptr->initMayThrow(); //memory leak
    return ptr;
}
```

Right & OK:
``` cpp 
{
std::unique_ptr<MyObj> getMyObject(){ //Additionally shows owner change
    auto ptr = std::make_unique<MyObj>();
    ptr->initMayThrow(); //no memory leak
    return ptr; // no move at an exception, automatic dtor call
}
```

Right but better:
``` cpp 
{
MyObj getMyObject(){
    auto myobj = MyObj();
    myobj.initMayThrow(); //no memory leak, simple stack unwinding
    return myobj; // fast because of copy elision (no copy)
}

int main() {
    MyObj const& myobj1 = getMyObject(); // Life time extension of temporary, legal, same as:
    MyObj const myobj2 = getMyObject(); // Copy elision,

    MyObj&& myobj3 = getMyObject(); // Non const lifetime extension of temporary, in this case same as:
    MyObj myobj3 = getMyObject(); // Copy elision, very fast
}
```

#### Set pointer to `nullptr` after delete
Since calling delete on a `nullptr` is valid, but calling it at a previously deleted pointer is undefined behaviour you should set the pointer to `nullptr`. Not doing this makes the search for errors difficult, because the application doesn't have to crash.

```cpp
if (this->timer)
{
    delete this->timer; May call ctor twice -> undefined
}
```
To avoid this, set the pointer to `nullptr`:
```cpp
delete this->timer;
this->timer = NULL;
```
### Using auto everywhere
While the `auto` type of C++ is very handy, developers tend to abuse it. C++ is a strongly typed language and hence by using this type the developer instructs the compiler to determine the type of the variable at compilation time.

This does not directly lead to problems, as the compiler is able to know about the correct type of the variable. The problems come along the way. Refactoring parts of the code may lead to bugs that occur in positions that should normally not be influenced by the changes. There may also occur bugs that fly by the compiler and won't even raise a warning but still cause problems during execution of the code.

To avoid these problems do only use the `auto` type when creating new objects using the following statement:

```
auto pointer = new Object();
```