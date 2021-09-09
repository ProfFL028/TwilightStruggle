# Programming in CLion

## How to include multi main functions

In CMakeList.txt:

```cmake
file(GLOB files tests/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file})
    message(\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
```

The main purpose of previous cmake file is to add every executable cpp files in tests directory to the IDE. Change 'tests/*.cpp' to whatever we want.

