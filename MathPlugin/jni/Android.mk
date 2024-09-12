LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := simplemath
LOCAL_SRC_FILES := SimpleMath.cpp

include $(BUILD_SHARED_LIBRARY)
