LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := pluginpractice

# No need to specify jni folder as it's assumed
LOCAL_SRC_FILES := PluginPractice.cpp

include $(BUILD_SHARED_LIBRARY)
