# Sample project to demonstrate issues ignoring warnings in clang module headers

Stackoverflow question:

[http://stackoverflow.com/questions/38889998/how-to-ignore-warnings-in-headers-that-are-part-of-a-clang-c-module](http://stackoverflow.com/questions/38889998/how-to-ignore-warnings-in-headers-that-are-part-of-a-clang-c-module)

Issues:

* Pragma information does not seem to be preserved in clang's internal/precompiled representation of a module header
* -Wno-system-headers does not inhibit warnings from system headers that have been pulled in as precompiled modules
* Using the `[system]` module attribute will suppress warnings even when including the header via a "user" style include, e.g. when building the library sources themselves, which means warnings we want to see will also be suppressed.

## Building

    mkdir build && cd build
    cmake /path/to/ClangModuleWarnings
    make

You should see two errors:

```
In module 'mylib' imported from /path/to/mylib/mylib.cpp:2:
/path/to/mylib/include/mylib/mylib.h:14:16: error: comparing floating point with == or != is unsafe
      [-Werror,-Wfloat-equal]
    return lhs == rhs;
           ~~~ ^  ~~~
```

This error should have been ignored via the pragmas, since mylib.cpp is including the header as a non-system "user" header and `-Wno-system-headers` will not take effect.

and:

```
In module 'mylib' imported from /path/to/main.cpp:4:
/path/to/mylib/include/mylib/mylib.h:14:16: error: comparing floating point with == or != is unsafe
      [-Werror,-Wfloat-equal]
    return lhs == rhs;
           ~~~ ^  ~~~

```

This error should have been ignored by `-Wno-system-header` since the header is included as a system header via the CMake `include_directories` path which specifies the `SYSTEM` option which causes it to be added via the `-isystem` argument.

Commenting out the CMakeLists.txt lines that enable clang modules fixes both these errors.

Note there is a warning in mylib.h that we *want* to see when buliding mylib.cpp, since it includes the header via a "user" style include, but not when clients import it via a "system" style include:

```
While building module 'mylib' imported from /path/to/mylib/mylib.cpp:2:
In file included from <module-includes>:1:
/path/to/mylib/include/mylib/mylib.h:23:6: warning: variable 'i' is uninitialized when used here [-Wuninitialized]
    *i = 123;
```

This is suppressed if we add the `[system]` attribute to the mylib module, which we don't want.

*Be careful*: you will want to clear your module cache after any tweaks or changes you make otherwise you may end up getting incorrectly (un)successful builds due to stale caches.
