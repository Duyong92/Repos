#pragma once
#pragma warning(disable:4996)
/* fopen �� "r+" ���� �̿��غ��� */
#include <stdio.h>
void run() {
	FILE* fp = fopen("some_data.txt", "r+");
	char data[100];

	fgets(data, 100, fp);
	printf("���� ���Ͽ� �ִ� ���� : %s \n", data);

	fseek(fp, 5, SEEK_SET);

	fputs("is nothing on this file", fp);

	fclose(fp);
}