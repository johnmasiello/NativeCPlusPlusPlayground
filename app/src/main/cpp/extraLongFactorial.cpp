//
// Created by john on 8/1/18.
//

#include "extraLongFactorial.h"
#include "util.h"

using namespace std;

int extraLongFactorialsDriver() {
    extraLongFactorials(1000);
    return 0;
}

// Complete the extraLongFactorials function below.
void extraLongFactorials(int n) {
    // bigIntegerDriver();

    // Solution
    BigInteger bigInteger(1);

    while (n > 1)
        bigInteger.multiply(static_cast<u_int64_t>(n--));

    COUT(bigInteger.to_string().data());
}

/*
 * Definitions for class BigInteger
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
BigInteger::BigInteger(){
    for(int i=0; i< CAPACITY; i++){
        digits[i]=0;
    }
}

BigInteger::~BigInteger() {
    // delete []digits; // digits is not a pointer, so we do not need to delete it
}

BigInteger::BigInteger(u_int64_t init_num){
    int i = 0;
    while(init_num > 0){
        digits[i++] = static_cast<int>(init_num % BASE);
        init_num = init_num/BASE;
    }
    for(;i< CAPACITY;i++){
        digits[i]=0;
    }
}

void BigInteger::accumulate(BigInteger &rVal) {
    for (int i = 0, carry = 0, sum; i < CAPACITY; i++) {
        sum = digits[i] + rVal.digits[i] + carry;

        if (sum > BASE) {
            digits[i] = sum - BASE;
            carry = 1;
        } else {
            digits[i] = sum;
            carry = 0;
        }
    }
}

void BigInteger::multiply(u_int64_t rVal) {
    BigInteger finalProduct(0);
    BigInteger *singleDigitProduct;
    int digit, carry, sum, powerOfBase;

    powerOfBase = 0;

    while (rVal > 0) {
        digit = static_cast<int>(rVal % BASE);
        rVal /= BASE;
        carry = 0;
        singleDigitProduct = new BigInteger(0);

        // Perform a single digit multiplication
        for (int i = 0; i < CAPACITY; i++) {
            sum = digit * digits[i] + carry;
            singleDigitProduct->digits[powerOfBase + i] = sum % BASE;
            carry = sum / BASE;
        }
        // Accumulate the single digit product with the sum of the previous single digit products
        finalProduct.accumulate(*singleDigitProduct);
        delete singleDigitProduct;
        powerOfBase++;
    }
    copyDigits(finalProduct);
}

string BigInteger::to_string() {
    int n = CAPACITY - 1;
    while (digits[n] == 0)
        n--;
    n++;
    char output[n + 1];

    for (int i = 0; i < n; i++)
        output[n - i - 1] = static_cast<char>('0' + digits[i]);

    output[n] = '\0';
    string s = output;
    return s;
}

void BigInteger::copyDigits(BigInteger &source) {
    for (int i = 0; i < CAPACITY; i++)
        digits[i] = source.digits[i];
}

void bigIntegerDriver() {
    BigInteger bigInteger(0);
    BigInteger *bi;

    for (int i = 0; i < 3; i++) {
        bi = new BigInteger(static_cast<u_int64_t>(55 + i));
        bigInteger.accumulate(*bi);
        delete bi;
    }
    COUT((bigInteger.to_string() + '\n').data());
}