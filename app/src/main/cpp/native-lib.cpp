#include <jni.h>
#include <string>
#include <iostream>
#include "bestCoins.h"
#include "util.h"
#include "magic-vowels.h"
#include "bookBundles.h"
#include "leonardoPrimeFactors.h"

using namespace std;

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_john_nativecpluspluswrapper_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_john_nativecpluspluswrapper_NativeWrapper_main(JNIEnv *env, jobject instance) {
    COUT("Hello World from Jni!");
//    makeChange_driver();

    /*
     * Here are the valid coin values, in cents:
    100 50 25 10 5 1
    Enter the amount of cents (as an integer) to make change for:
    67
    What is the maximum number of coins to give as change?
    88
    Number of possible combinations: 93
    Best combination of coins:
    50 10 5 1 1
     */

    COUT("\n \n ");
//    magicVowels_driver();

    /*
     * A very long string:
    zzdsfasdegsagweagaeiouuuuoiuiououaaasdbadaaaaeeeeeeeeiiiiiooozzzzzaaaaaeeeeeeeeeeeeeiiiiiiiiooooooouuuuuuuuuuuuuuuuuuuuu
    length of the longest sequence with repeats and in-order of 'aeiou':
    54
     */

    COUT("\n \n ");
//    bookBundles_driver();


    /*
     * Remaining Budget = $100
        4.000000
        3.916667
        2.538462
        2.285714
        3.666667
        4.333333
        3.090909
        Remaining Budget = $1
        429
     */

    COUT("\n \n ");
    prime_driver();
}