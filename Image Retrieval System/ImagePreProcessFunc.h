#include "StdAfx.h"
#include <cv.h>

using namespace std;





char* ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn);

//HBITMAP IplIamgeToDIB(IplImage *pImg); 




IplImage** RGB2HSVplanes(IplImage* image);

//void smooth(IplImage** plane);

//* using the method in <<����ɫ��������������ͼ�����>>,�����£���С��������毣���� */
void ColorQuantization(IplImage** planes, IplImage* quantized);
