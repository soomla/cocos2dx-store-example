LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := jni_init/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ExampleEventHandler.cpp \
                   ../../Classes/LevelIconWidget.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/MuffinRushAssets.cpp \
                   ../../Classes/StoreAScene.cpp \
                   ../../Classes/StoreBScene.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,extensions/cocos2dx-store)
