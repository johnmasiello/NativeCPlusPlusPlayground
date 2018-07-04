//
// Created by john on 7/3/18.
//

#ifndef NATIVECPLUSPLUSWRAPPER_UTIL_H
#define NATIVECPLUSPLUSWRAPPER_UTIL_H

// https://stackoverflow.com/questions/4630026/adapter-from-c-output-stream-to-an-android-textview-or-equivalent
#include <android/log.h>

extern const char * STANDARD_OUTPUT_TAG;


#define COUT(x) {__android_log_write(ANDROID_LOG_DEBUG, STANDARD_OUTPUT_TAG, (x)); }

#endif //NATIVECPLUSPLUSWRAPPER_UTIL_H
