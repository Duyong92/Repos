#pragma once
#pragma warning(disable:4996)

/* 파일에서 문자를 하나씩 입력 받는다 */
#include <stdio.h>

void run() {
    FILE* fp = fopen("some_data.txt", "r");
    char data[10];
    char c;

    if (fp == NULL) {
        printf("file open error ! \n");
        return;
    }

    fgets(data, 5, fp);
    printf("입력 받은 데이터 : %s \n", data);

    c = fgetc(fp);
    printf("그 다음에 입력 받은 문자 : %c \n", c);

    fseek(fp, -1, SEEK_CUR);

    c = fgetc(fp);
    printf("그렇다면 무슨 문자가? : %c \n", c);

    fclose(fp);
}