#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
void run() {
	/* ���� fp �� abcdef �� ����ִ� ����*/
	FILE* fp = fopen("abcdef.txt", "r");
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	/* d ���� �Է¹޾����� ���� ��ġ�����ڴ� ���� e �� ����Ű�� �ִ� */
	// SEEK_SET �� �ش� index �� ��ġ�� �����ش�.
	// SEEK_CUR : ���� ��ġ
	// SEEK_END : ������ ��ġ
	fseek(fp, 0, SEEK_SET);
	printf("�ٽ� ���� ó������ �Է� �޴´ٸ� : %c \n", fgetc(fp));
	fclose(fp);

	fp = fopen("a.txt", "w");
	fputs("Psi is an excellent C programmer", fp);
	fseek(fp, 0, SEEK_SET);
	fputs("is Psi", fp);
	fclose(fp);

	return;
}