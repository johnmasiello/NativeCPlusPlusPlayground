//
// Created by john on 7/3/18.
//

#ifndef NATIVECPLUSPLUSWRAPPER_UTIL_H
#define NATIVECPLUSPLUSWRAPPER_UTIL_H

// https://stackoverflow.com/questions/4630026/adapter-from-c-output-stream-to-an-android-textview-or-equivalent
#include <android/log.h>
#include <vector>
#include <string>

extern const char * STANDARD_OUTPUT_TAG;


#define COUT(x) {__android_log_write(ANDROID_LOG_DEBUG, STANDARD_OUTPUT_TAG, (x)); }

template <class T>
inline void output_std(std::vector<T> items) {
    std::string output = "";
    for (T x : items)
        output += std::to_string(x) + " ";

    COUT(output.data());
}

// Specialized template
inline void output_std(std::vector<std::string> items) {
    std::string output = "";
    for (std::string x : items)
        output += x + "\n";

    COUT(output.data());
}

#endif //NATIVECPLUSPLUSWRAPPER_UTIL_H
