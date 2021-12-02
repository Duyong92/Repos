#pragma once
#pragma warning(disable:4996)
/* fopen 의 'append' 기능 사용*/
#include <stdio.h>
void run() {
    FILE* fp = fopen("some_data.txt", "a");
    char c;
    if (fp == NULL) {
        printf("파일 열기를 실패하였습니다! \n");
        return;
    }
    /* 아래 내용이 파일 뒤에 덧붙여진다.*/
    // fput + s 는 string, fput + c 는 char 의 약자로 보여진다.
    fputs("IS ADDED HAHAHAHA", fp);
    fclose(fp);
}