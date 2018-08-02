//
// Created by john on 8/1/18.
//

#ifndef NATIVECPLUSPLUSWRAPPER_EXTRALONGFACTORIAL_H
#define NATIVECPLUSPLUSWRAPPER_EXTRALONGFACTORIAL_H

#include <sys/types.h>
#include <string>
inline const int CAPACITY = 2600;
inline const int BASE = 10;

class BigInteger {
public:
    BigInteger();
    ~BigInteger();
    BigInteger(u_int64_t init_num);
    void multiply(u_int64_t rVal);
    void accumulate(BigInteger &rVal);
    std::string to_string();

private:
    int digits[CAPACITY];
    void copyDigits(BigInteger &source);
};

void extraLongFactorials(int n);

int extraLongFactorialsDriver();


#endif //NATIVECPLUSPLUSWRAPPER_EXTRALONGFACTORIAL_H
