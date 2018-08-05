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

//#define COUT(x) { cout << (x) << endl; } // For environment with stdout
#define COUT(x) {__android_log_write(ANDROID_LOG_DEBUG, STANDARD_OUTPUT_TAG, (x)); }

template <class T>
inline void output_std(std::vector<T> &items) {
    std::string output = "";
    for (T x : items)
        output += std::to_string(x) + " ";

    COUT(output.data());
}

// Specialized template
inline void output_std(std::vector<std::string> &items) {
    std::string output = "";
    for (int i = 0; i < items.size(); i++)
        output += items[i] + "\n";
    COUT(output.data());
}

template <class T>
inline void __quickSort_asc(std::vector<T> &arr, int l, int r) {
    if (l >= r)
        return;

    T swap, pivot = arr[(l + r) >> 1];
    int i = l;
    int j = r;

    while (i <= j) {
        while (arr[i] < pivot)
            i++;

        while (arr[j] > pivot)
            j--;

        if (i <= j) {
            swap = arr[j];
            arr[j] = arr[i];
            arr[i] = swap;
            i++;
            j--;
        }
    }
    // i is at the position of pivot, j is invalidated, since it started >= i, and now j < i
    __quickSort_asc(arr, l, i - 1);
    __quickSort_asc(arr, i, r);
}

// Sorts in ascending order on the < operator
template <class T>
inline void my_quickSort(std::vector<T> &arr) {
    __quickSort_asc(arr, 0, arr.size() - 1);
}

#endif //NATIVECPLUSPLUSWRAPPER_UTIL_H
