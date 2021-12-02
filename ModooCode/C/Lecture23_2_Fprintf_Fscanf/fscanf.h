#pragma once
#pragma warning(disable:4996)
/* fscanf �̿��ϱ� */
#include <stdio.h>

void run() {
    FILE* fp = fopen("some_data.txt", "r");
    char data[100];

    if (fp == NULL) {
        printf("���� ���� ����! \n");
        return;
    }

    printf("---- �Է� ���� �ܾ�� ---- \n");

    // scanf �� stdin ������ �Է� �ް�,
    // fscanf �� ������ ��Ʈ�������� �Է� ���� �� �ִ�.
    // fscanf(stdin, "%s", data); �� scanf("%s", data); �� ���� �����̴�.
    while (fscanf(fp, "%s", data) != EOF) {
        printf("%s \n", data);
    }

    fclose(fp);
}