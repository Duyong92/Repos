#pragma once
#pragma warning(disable:4996)

/* ���Ͽ��� ���ڸ� �ϳ��� �Է� �޴´� */
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
    printf("�Է� ���� ������ : %s \n", data);

    c = fgetc(fp);
    printf("�� ������ �Է� ���� ���� : %c \n", c);

    fseek(fp, -1, SEEK_CUR);

    c = fgetc(fp);
    printf("�׷��ٸ� ���� ���ڰ�? : %c \n", c);

    fclose(fp);
}