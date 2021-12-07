#pragma once

//#ifdef _MYSTRING_COPY_ELISION_
//void MyString_Copy_Elision();
//#endif
//#ifndef MYSTRING_COPY_ELISION_TEST
//#ifndef LVALUE
//#endif
//#endif

// 사용하고 싶은 CPP 파일의 #define 주석을 풀어주면 된다.

//#define MYSTRING_COPY_ELISION_TEST
//#define LVALUE
//#define RVALUE
#define VECTOR_NOEXCEPT
void MyString_Copy_Elision_test();
void LValue(); 
void RValue();
void Vector_NoExcept();