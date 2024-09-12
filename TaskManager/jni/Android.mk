LOCAL_PATH := $(call my-dir)

# Define the module name and shared library
include $(CLEAR_VARS)
LOCAL_MODULE    := TaskManagerPlugin  # Name of the shared library
LOCAL_SRC_FILES := TaskManagerPlugin.cpp  # Your C++ source files

# Define the NDK STL you want to use. In this case, use c++_shared for better support of modern C++
LOCAL_LDLIBS := -llog -landroid

include $(BUILD_SHARED_LIBRARY)
