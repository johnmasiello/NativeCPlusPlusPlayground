//
// Created by john on 7/31/18.
//

#include "leonardoPrimeFactors.h"
#include "util.h"
#include <vector>
#include <string>

using namespace std;

int prime_driver() {

    int count = primeCount(1000000000000000000);
    COUT(("number of primes " + to_string(count)).data());
    return 0;
}

// Helper method. Saves the work from finding the next prime number
int nextPrime(bool fromBeginning) {
    static int currentIndex;
    static vector<int> primes(0);

    if (primes.size() == 0) {
        primes.push_back(2);
        primes.push_back(3);
        // primes.push_back(5);
        // primes.push_back(7);
        // primes.push_back(11);
        // primes.push_back(13);
        // primes.push_back(17);
        // primes.push_back(19);
        // primes.push_back(23);
    }
    if (fromBeginning) {
        currentIndex = 0;
    } else if (currentIndex >= primes.size()) {
        // Find the next prime; we want to generate the list ourselves, and we want to make sure it is inclusive
        int nextPrime = primes[currentIndex - 1];
        bool isPrime;

        do {
            // The primes need to be initialized with at least 2 and 3
            nextPrime += 2;
            isPrime = true;
            for (int i = 0; i < primes.size(); i++) {
                if (nextPrime % primes[i] == 0) {
                    isPrime = false;
                    break;
                }
            }
        } while (!isPrime);
        primes.push_back(nextPrime);
    }
    return primes[currentIndex++];
}

/*
 * Complete the primeCount function below.
 */
int primeCount(long n) {
    unsigned long long primeFactors = nextPrime(true);
    int count = 0;

    while (n > primeFactors) {
        primeFactors *= nextPrime(false);
        count++;
    }
    // We guard against needlessly computing the next prime
    return n == primeFactors ? ++count : count;
}