#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
void run() {
	/* 현재 fp 에 abcdef 가 들어있는 상태*/
	FILE* fp = fopen("abcdef.txt", "r");
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	/* d 까지 입력받았으니 파일 위치지정자는 이제 e 를 가리키고 있다 */
	// SEEK_SET 은 해당 index 의 위치로 보내준다.
	// SEEK_CUR : 현재 위치
	// SEEK_END : 마지막 위치
	fseek(fp, 0, SEEK_SET);
	printf("다시 파일 처음에서 입력 받는다면 : %c \n", fgetc(fp));
	fclose(fp);

	fp = fopen("a.txt", "w");
	fputs("Psi is an excellent C programmer", fp);
	fseek(fp, 0, SEEK_SET);
	fputs("is Psi", fp);
	fclose(fp);

	return;
}