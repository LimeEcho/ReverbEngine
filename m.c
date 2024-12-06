#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "vec3.h"

// 初始化随机数种子
void init_random(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);  // 种子仅初始化一次
}

int main(void) {
    //init_random();  // 初始化种子
    float b;
    for (int a = 0; a < 100; a++) {
        b = randoms();
        printf("%f\n", b);
    }
    return 0;
}
