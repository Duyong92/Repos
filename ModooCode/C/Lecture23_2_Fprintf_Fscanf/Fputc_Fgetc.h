#pragma once
#pragma warning(disable:4996)
/* Ư���� ������ �Է� �޾Ƽ� �ҹ��ڸ� �빮�ڷ�, �빮�ڸ� �ҹ��ڷ� �ٲٴ�
 * ���α׷�*/
#include <stdio.h>
void run() {
    FILE* fp = fopen("some_data2.txt", "r+");
    char c;

    if (fp == NULL) {
        printf("���� ���⸦ �����Ͽ����ϴ�! \n");
        return;
    }

    while ((c = fgetc(fp)) != EOF) {
        /* c �� �빮���� ��� */
        if (65 <= c && c <= 90) {
            /* �� ĭ �ڷ� ����*/
            fseek(fp, -1, SEEK_CUR);
            /* �ҹ��ڷ� �ٲ� c �� ����Ѵ�*/
            fputc(c + 32, fp);
            /*
            ���� - �б� ��� ��ȯ�� ���ؼ��� ������
            fseek �Լ��� ���� ���� ��ġ ������ ���� �Լ�����
            ȣ���ؾ� �Ѵ�.

            ���⿡�� �б� �۾����� �ٲٱ� ���� �Լ��� ȣ���� �� ���̴�.
            */
            // fflush(fp) �� ��ü�� �����ϴ�
            fseek(fp, 0, SEEK_CUR);
        }
        /* c �� �ҹ����� ���*/
        else if (97 <= c && c <= 122) {
            fseek(fp, -1, SEEK_CUR);
            fputc(c - 32, fp);
            fseek(fp, 0, SEEK_CUR);
        }
    }

    fclose(fp);
}