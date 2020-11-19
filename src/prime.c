#include <math.h>

#include <prime.h>

int is_prime(const int x) {
    if (x < 2) {
        return -1;
    } else if( x == 2) {
        return 1;
    } else {
        for(int i = 2; i < x; i++) {
            if(x % i == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int next_prime(int x) {
    while(is_prime(x) != 1) {
        x++;
    }
    return x;
}