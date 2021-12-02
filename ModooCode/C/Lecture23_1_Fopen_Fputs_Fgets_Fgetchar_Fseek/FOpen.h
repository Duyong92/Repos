#pragma once
/* a.txt 에 내용을 기록한다. */
#include <stdio.h>

void run() {
    FILE* fp;
    // 상대 경로로 해당 프로젝트에 있는 디렉토리에서 시작된다.
    // w 는 쓰기만 사용할 경우이다.
    fp = fopen("a.txt", "w");

    

    // fp 가 가끔씩 NULL을 부르게 되는데 전처리로 미리 배제시킨다.
    if (fp == NULL) {
        printf("Write Error!!\n");
        return;
    }

    fputs("Hello World!!! \n", fp);

    // 동적 메모리 할당에서 free 로 메모리를 반환해 주어야 한다.
    fclose(fp);

    FILE* fp_absolute_path;
    // 절대 경로로 쓸 경우에는 '\\' 처럼 두번 사용해줘야한다.
    // 경로를 엔터키로 끊어서 입력 시에 fopen 에서 NULL 이 생길 수 있다.
    fp_absolute_path = 
        fopen("C:\\Users\\User\\source\\Repos\\ModooCode\\C\\Lecture23_1_Fopen_Fputs_Fgets_Fgetchar_Fseek\\a_apsolute_path.txt", "w");
    
    if (fp_absolute_path == NULL) {
        printf("Write Error!!\n");
        return;
    }

    fputs("Hello World!!! \n from a.abolute_path \n", fp);

    fclose(fp_absolute_path);

    // 표준 스트림들도 닫을 수 있다.
    fclose(stdout);
    // 에러가 나니 실행해보지는 말 것
    //printf("aaa");
    return;
}