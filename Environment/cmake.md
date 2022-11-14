## How to Build the project?
```
cmake -S . -B build
cmake --build build
```

## How to recursely add files?
```
file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/src/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()
```


