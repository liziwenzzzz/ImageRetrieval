
// Image Retrieval System.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIRSystemApp:
// �йش����ʵ�֣������ Image Retrieval System.cpp
//

class CIRSystemApp : public CWinApp
{
public:
	CIRSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIRSystemApp theApp;