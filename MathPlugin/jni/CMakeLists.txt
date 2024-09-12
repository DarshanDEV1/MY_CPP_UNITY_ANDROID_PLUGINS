cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             simplemath

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             SimpleMath.cpp )

# Include libraries needed for android
target_link_libraries( simplemath
                       android
                       log )
