// ��ó���� ��� �Ŀ��� �������� C4996 ������ �����.
#pragma warning(disable:4996)
// Ȥ�� _CRT_SECURE_NO_WARNINGS �� define ���־ �ȴ�.
#pragma once

/* fgets �� a.txt ���� ������ �Է� �޴´�. */
#include <stdio.h>
void run() {
    FILE* fp = fopen("a.txt", "r");
    char buf[20];  // ������ �Է¹��� ��
    if (fp == NULL) {
        printf("READ ERROR !! \n");
        return;
    }
    // scanf �� ���� �ش� �޸� �Ҵ� ���� �� ���� �޴� �����÷ο찡 ������ �ʴ´�.
    fgets(buf, 20, fp);
    printf("�Է¹޴� ���� : %s \n", buf);

    // fgets ���� ������ ������� ���� �ٽ� ������ �Է� �޴´�.
    if (fgetc(fp) == EOF) {
        fp = fopen("a.txt", "r");
        printf("�ش� ������ ��� fp �� �ٽ� �Է��Ѵ�. \n");
    }

    char c;
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    // �� ������ �����ϴ� �����̴� get �Լ����� ����ϰ� �Ǹ� fp�� ������ �ٽ� �޾ƾ��Ѵ�.
    //fp = fopen("a.txt", "r");
    int size = 0;

    while (fgetc(fp) != EOF) {
        size++;
    }

    printf("�� ������ ũ��� : %d bytes \n", size);

    fclose(fp);
    return;
}