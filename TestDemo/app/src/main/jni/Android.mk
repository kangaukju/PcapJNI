LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := pcap
LOCAL_SRC_FILES := libpcap/libpcap.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hello
LOCAL_SRC_FILES := hello.c
LOCAL_STATIC_LIBRARIES := pcap
include $(BUILD_SHARED_LIBRARY)
