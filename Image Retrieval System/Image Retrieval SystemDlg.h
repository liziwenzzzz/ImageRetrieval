
// Image Retrieval SystemDlg.h : ͷ�ļ�

#pragma once
#include "ImagePreProcessFunc.h"
#include "Feature.h"
#include <fstream>
#include "afxwin.h"

//�˴�����ֵӦ������Ļ�ֱ������ 
#define uiImageHeight 180
#define uiImageWidth 180
#define uiResultHeight 120
#define uiResultWidth 120
#define IMAGE_CHANNEL_NUM 3

// CImageRetrievalSystemDlg �Ի���
class CIRSystemDlg : public CDialogEx
{
// ����
public:
	CIRSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

	Feature sampleImgFeature;

	bool isImageLibReady;
	bool isImageSampleReady;

// �Ի�������
	enum { IDD = IDD_IMAGERETRIEVALSYSTEM_DIALOG };

	CString uiImagePath;
	CString uiImageLibPath;
	CString uiFeatureFilePath;

	CStatic uiImagePic;
	CButton uiExtractButton;
	CButton uiSearchButton;
	CButton uiNextPageButton;
	CButton uiFrontPageButton;

	CButton uiMethodRadio;

	IplImage*  image;
	IplImage*  result1;
	IplImage*  result2;
	IplImage*  result3;
	IplImage*  result4;
	IplImage*  result5;
	IplImage*  result6;
	IplImage*  result7;
	IplImage*  result8;
	IplImage*  result9;

	int currentPage;
	int totalPage;
	int totalImgNum;
	vector<CString> imageLibVector;
	int* idx_min2max ;//�洢��Ӧ������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void ResizeImage1(IplImage* img);
	void ResizeImage2(IplImage* img, IplImage* myImg);
	void ShowImage( IplImage* img, unsigned int uiID ) ;
	//void scanDir(CString dirPath, ofstream& imgDBfeaturesFile);
	 void scanDir(CString dirPath, vector<CString> & imageLibVector);

	afx_msg void OnBnClickedButtonChooseImage();
	afx_msg void OnBnClickedButtonChooseImageDB();
	afx_msg void OnBnClickedButtonFeatureExtraction();
	afx_msg void OnBnClickedButtonLoadFeatureFile();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonFrontPage();
	afx_msg void OnBnClickedButtonNextPage();
	//afx_msg void OnBnClickedRadioColor();
	//afx_msg void OnBnClickedRadioTexture();
	//afx_msg void OnBnClickedRadioGradient();
	//afx_msg void OnBnClickedRadioColortexture();

};
