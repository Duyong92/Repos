#pragma once
#pragma warning(disable:4996)
/* fscanf 이용하기 */
#include <stdio.h>

void run() {
    FILE* fp = fopen("some_data.txt", "r");
    char data[100];

    if (fp == NULL) {
        printf("파일 열기 오류! \n");
        return;
    }

    printf("---- 입력 받은 단어들 ---- \n");

    // scanf 는 stdin 에서만 입력 받고,
    // fscanf 는 임의의 스트림에서도 입력 받을 수 있다.
    // fscanf(stdin, "%s", data); 와 scanf("%s", data); 는 같은 문장이다.
    while (fscanf(fp, "%s", data) != EOF) {
        printf("%s \n", data);
    }

    fclose(fp);
}