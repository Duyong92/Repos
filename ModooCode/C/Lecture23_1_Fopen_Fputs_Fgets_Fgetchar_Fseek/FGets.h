// 전처리기 사용 후에도 지속적인 C4996 오류가 생긴다.
#pragma warning(disable:4996)
// 혹은 _CRT_SECURE_NO_WARNINGS 를 define 해주어도 된다.
#pragma once

/* fgets 로 a.txt 에서 내용을 입력 받는다. */
#include <stdio.h>
void run() {
    FILE* fp = fopen("a.txt", "r");
    char buf[20];  // 내용을 입력받을 곳
    if (fp == NULL) {
        printf("READ ERROR !! \n");
        return;
    }
    // scanf 와 같이 해당 메모리 할당 보다 더 많이 받는 오버플로우가 생기지 않는다.
    fgets(buf, 20, fp);
    printf("입력받는 내용 : %s \n", buf);

    // fgets 이후 내용이 사라지는 같아 다시 내용을 입력 받는다.
    if (fgetc(fp) == EOF) {
        fp = fopen("a.txt", "r");
        printf("해당 내용이 없어서 fp 를 다시 입력한다. \n");
    }

    char c;
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    // 위 내용을 증명하는 내용이다 get 함수들을 사용하게 되면 fp의 내용을 다시 받아야한다.
    //fp = fopen("a.txt", "r");
    int size = 0;

    while (fgetc(fp) != EOF) {
        size++;
    }

    printf("이 파일의 크기는 : %d bytes \n", size);

    fclose(fp);
    return;
}