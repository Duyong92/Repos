#pragma once
/* a.txt �� ������ ����Ѵ�. */
#include <stdio.h>

void run() {
    FILE* fp;
    // ��� ��η� �ش� ������Ʈ�� �ִ� ���丮���� ���۵ȴ�.
    // w �� ���⸸ ����� ����̴�.
    fp = fopen("a.txt", "w");

    

    // fp �� ������ NULL�� �θ��� �Ǵµ� ��ó���� �̸� ������Ų��.
    if (fp == NULL) {
        printf("Write Error!!\n");
        return;
    }

    fputs("Hello World!!! \n", fp);

    // ���� �޸� �Ҵ翡�� free �� �޸𸮸� ��ȯ�� �־�� �Ѵ�.
    fclose(fp);

    FILE* fp_absolute_path;
    // ���� ��η� �� ��쿡�� '\\' ó�� �ι� ���������Ѵ�.
    // ��θ� ����Ű�� ��� �Է� �ÿ� fopen ���� NULL �� ���� �� �ִ�.
    fp_absolute_path = 
        fopen("C:\\Users\\User\\source\\Repos\\ModooCode\\C\\Lecture23_1_Fopen_Fputs_Fgets_Fgetchar_Fseek\\a_apsolute_path.txt", "w");
    
    if (fp_absolute_path == NULL) {
        printf("Write Error!!\n");
        return;
    }

    fputs("Hello World!!! \n from a.abolute_path \n", fp);

    fclose(fp_absolute_path);

    // ǥ�� ��Ʈ���鵵 ���� �� �ִ�.
    fclose(stdout);
    // ������ ���� �����غ����� �� ��
    //printf("aaa");
    return;
}