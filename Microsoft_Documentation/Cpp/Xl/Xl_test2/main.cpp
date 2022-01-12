#include "CXl.h"

int main() {
    CXl xl;
    xl.Open();
    xl.AddWorkBook();

    xl.AddActiveSheet();
    
    xl.SetRange("A1","P20");
    
     VARIANT arr;
     VariantInit(&arr);
     xl.SetSafeBound(arr, 1, 5000, 1, 5000);
    
    //���⼭���� ���� �۾��� ���ֽø� �˴ϴ�.
    // SafeArray�� �Ѿ�� �Ǹ� '�� ���� �����Դϴ�'��� ������ �߻��մϴ�.
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 20; j++) {
            // Create entry value for (i,j)
            VARIANT tmp;
            tmp.vt = VT_I4;
            tmp.lVal = i * j;

            xl.SetData(arr, tmp,i,j);
        }
    }

   xl.Print(arr);

   xl.Close();

    return 0;
}