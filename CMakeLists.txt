# Required to let CMake know which version of the language and libraries to use. Should be the first thing at the top.
# https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html
cmake_minimum_required(VERSION 3.26)

# Project definition. There will be only one of these and it should pretty much always come before anything else.
# https://cmake.org/cmake/help/latest/command/project.html
project(LList VERSION 0.0.1)

# Put you linked list implementation in a separate static library called llist. You can make it a shared library by using `SHARED` instead of `STATIC`.
# https://cmake.org/cmake/help/latest/command/add_library.html
add_library(llist STATIC source/linkedsys.c)

# Make sure the library declares its public interface to be the headers directory.
# Other targets depending on it will then also know where to find the include files for the library.
# https://cmake.org/cmake/help/latest/command/target_include_directories.html
target_include_directories(llist PUBLIC headers)

# Make sure C11 is used for your llist library. For gcc this will generate the `-std=c11` argument.
# https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html
set_property(TARGET llist PROPERTY C_STANDARD 11)

# Add another binary target, this time an executable, for your main functionality
# https://cmake.org/cmake/help/latest/command/add_executable.html
add_executable(main source/main.c source/general_utils.c)

# Tell CMake that your executable, called main, depends on the llist library defined earlier.
# This will also ensure that it knows about the include directory being headers since we declared it PUBLIC.
# https://cmake.org/cmake/help/latest/command/target_link_libraries.html
target_link_libraries(main llist)

set_property(TARGET main PROPERTY C_STANDARD 11)

# With cmake there are two steps:
# 1. Generate the build files (in a separate directory). This is called the configure step.
# `$ cmake -S . -B build -G "Unix Makefiles"`
# This will generate a makefile build in the build subdirectory based on the source directory (this directory: ".")
# You may notice we didn't specify the compiler here. CMake will typically detect a suitable compiler in your environment,
# but sometimes the compiler options are restricted by the generator you choose.
# If you want to select a specific compiler you may want to do something like `export CC=/usr/local/bin/gcc` behorehand.
# See also https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html for a list of supported generators.
# If you don't like the command line you can also use the cmake-gui for this step.
# 2. Perform the build. This can either be done using the build system you generated the build files for or with cmake itself.
# `$ cmake --build build` or `make -C build`
# Depending on the generator, your library and executable should end up in the build folder or a subfolder thereof.
# See also https://cmake.org/cmake/help/latest/manual/cmake.1.html for an overview of the CLI.

# Tip: Since you're using VSCode you may want to install
# https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools
# This will allow you to control the generate and build steps directly from within VSCode if you open this folder.
# Make sure to execute 'CMake: Scan for Kits' in VSCode beforehand.
# To get help and autocomplete while editing CMake files like these you also may want to install
# https://marketplace.visualstudio.com/items?itemName=twxs.cmake