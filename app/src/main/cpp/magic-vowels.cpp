//
// Problem from HackerRank.com
// Created by john on 7/5/18.
//
#include "magic-vowels.h"
#include "util.h"
using namespace std;

int magicVowels_driver() {
    string letters("zzdsfasdegsagweagaeiouuuuoiuiououaaasdbadaaaaeeeeeeeeiiiiiooozzzzzaaaaaeeeeeeeeeeeeeiiiiiiiiooooooouuuuuuuuuuuuuuuuuuuuu");
//    string letters("zzdsfasdegsagweagaeiouuuuoiuiououaaasdbadaaaaeeeeeeeeiiiiiooozzzzzbbbbbeeeeeeeeeeeeeiiiiiiiiooooooouuuuuuuuuuuuuuuuuuuuu");
//    string letters("ab"); // string.size() does not include the null terminator
    COUT("A very long string: ");
    COUT(letters.data());
    COUT("length of the longest sequence with repeats and in-order of \'aeiou\': ");
    COUT(to_string(longestSequenceMagicVowels(letters)).data());
    return 0;
}

int longestSequenceMagicVowels(string s) {
    int maxSequence = 0;
    int currentSequence = 0;
    int prevChar = 0,
         currentChar;

    unsigned long nonNullLength = s.size();

    for (uint16_t i = 0; i < nonNullLength; i++) {
        currentChar = tolower(s.at(i));

        if (currentSequence > 0) { // Guard against false positives, regarding the start of the sequence, ie, iou is a false positive, the letters step correct and the sequence terminates correct, but does not start correctly
            // Step 'up' from or repeat letters
            switch (prevChar) {
                case 'u':
                    if (currentChar == 'u') // Repeating u
                        currentSequence++;
                    else {
                        if (currentSequence > maxSequence) // Accepted string
                            maxSequence = currentSequence;
                        currentSequence = 0;
                    }
                    break;
                case 'a':
                    if (currentChar == 'a' || currentChar == 'e')
                        currentSequence++;
                    else
                        currentSequence = 0;
                    break;
                case 'e':
                    if (currentChar == 'e' || currentChar == 'i')
                        currentSequence++;
                    else
                        currentSequence = 0;
                    break;
                case 'i':
                    if (currentChar == 'i' || currentChar == 'o')
                        currentSequence++;
                    else
                        currentSequence = 0;
                    break;
                case 'o':
                    if (currentChar == 'o' || currentChar == 'u')
                        currentSequence++;
                    else
                        currentSequence = 0;
                    break;
            }
        } else {
            switch (prevChar) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    break;

                default:
                    if (currentChar == 'a')
                        currentSequence = 1; // The start of the magic sequence
            }
        }

        // Update
        prevChar = currentChar;
    }

    // Handle the edge case the accepted sequence was terminated by end of string
    if (prevChar == 'u' && currentSequence > maxSequence)
        return currentSequence;
    else
        return maxSequence;
}