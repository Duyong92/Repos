#pragma once
#pragma warning(disable:4996)
/* fopen �� 'append' ��� ���*/
#include <stdio.h>
void run() {
    FILE* fp = fopen("some_data.txt", "a");
    char c;
    if (fp == NULL) {
        printf("���� ���⸦ �����Ͽ����ϴ�! \n");
        return;
    }
    /* �Ʒ� ������ ���� �ڿ� ���ٿ�����.*/
    // fput + s �� string, fput + c �� char �� ���ڷ� ��������.
    fputs("IS ADDED HAHAHAHA", fp);
    fclose(fp);
}