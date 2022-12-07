cmake_minimum_required(VERSION 3.10)

# The project name is rather unimportant and you can name it anything you want.
# It just mustn't conflict with the module name that is defined further below.
project(gmod-module-guide LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES Release Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Load the gmod-module-base project that sets up headers and settings.
add_subdirectory(gmod-headers/include)

# The library name defined here (in this case, "testmodule") will be the name of the module.
add_library(testmodule SHARED)

# Add the source files required for the module.
# Again, the file names don't matter and you can even add multiple files by adding more space-delimited filenames after "module.cpp".
target_sources(testmodule PRIVATE module.cpp)

# Actually apply the headers and settings to our module.
target_link_libraries(testmodule gmod-module-base)

set_gmod_suffix_prefix(testmodule)