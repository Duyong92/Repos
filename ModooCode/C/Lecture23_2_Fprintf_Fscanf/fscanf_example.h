#pragma once
#pragma warning(disable:4996)
/* ���Ͽ��� 'this' �� 'that' ���� �ٲٱ�*/
#include <stdio.h>
#include <string.h>

void run() {
    FILE* fp = fopen("fscanf_example.txt", "r+");
    char data[100];

    if (fp == NULL) {
        printf("���� ���� ����! \n");
        return;
    }

    while (fscanf(fp, "%s", data) != EOF) {
        if (strcmp(data, "this") == 0) {
            fseek(fp, -(long)strlen("this"), SEEK_CUR);
            fputs("that", fp);

            fflush(fp);
        }
    }

    fclose(fp);
}