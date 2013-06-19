
// Image Retrieval SystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image Retrieval System.h"
#include "Image Retrieval SystemDlg.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include "CvvImage.h"
#include "io.h"

using namespace std;
using namespace cv;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageRetrievalSystemDlg �Ի���

CIRSystemDlg::CIRSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIRSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIRSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ImagePath, uiImagePath);  
	DDX_Text(pDX, IDC_ImageDBPath, uiImageLibPath);   
	DDX_Text(pDX, IDC_FeatureFilePath, uiFeatureFilePath); 
	DDX_Control(pDX, IDC_ImagePic, uiImagePic); 
	DDX_Control(pDX,IDC_BUTTON_FeatureExtraction, uiExtractButton);
	DDX_Control(pDX,IDC_BUTTON_Search, uiSearchButton);
	DDX_Control(pDX,IDC_BUTTON_FrontPage, uiFrontPageButton);
	DDX_Control(pDX,IDC_BUTTON_NextPage, uiNextPageButton);
	DDX_Control(pDX, IDC_RADIO_COLORTEXTURE, uiMethodRadio);
}

BEGIN_MESSAGE_MAP(CIRSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ChooseImage, &CIRSystemDlg::OnBnClickedButtonChooseImage)
	ON_BN_CLICKED(IDC_BUTTON_ChooseImageDB, &CIRSystemDlg::OnBnClickedButtonChooseImageDB)
	ON_BN_CLICKED(IDC_BUTTON_FeatureExtraction, &CIRSystemDlg::OnBnClickedButtonFeatureExtraction)
	ON_BN_CLICKED(IDC_BUTTON_LoadFeatureFile, &CIRSystemDlg::OnBnClickedButtonLoadFeatureFile)
	ON_BN_CLICKED(IDC_BUTTON_Search, &CIRSystemDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_FrontPage, &CIRSystemDlg::OnBnClickedButtonFrontPage)
	ON_BN_CLICKED(IDC_BUTTON_NextPage, &CIRSystemDlg::OnBnClickedButtonNextPage)
	//ON_BN_CLICKED(IDC_RADIO_COLOR, &CIRSystemDlg::OnBnClickedRadioColor)
	//ON_BN_CLICKED(IDC_RADIO_TEXTURE, &CIRSystemDlg::OnBnClickedRadioTexture)
	//ON_BN_CLICKED(IDC_RADIO_GRADIENT, &CIRSystemDlg::OnBnClickedRadioGradient)
	//ON_BN_CLICKED(IDC_RADIO_COLORTEXTURE, &CIRSystemDlg::OnBnClickedRadioColortexture)
END_MESSAGE_MAP()


// CImageRetrievalSystemDlg ��Ϣ�������

BOOL CIRSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CvSize size;
	size.height = uiImageHeight;//IMAGE_HEIGHT;
	size.width = uiImageWidth;//IMAGE_WIDTH;
	image = cvCreateImage( size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );

	size.height = uiResultHeight;
	size.width = uiResultWidth;
	result1 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result2 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result3 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result4 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result5 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result6 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result7 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result8 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result9 = cvCreateImage(size, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );

	/*m_flag_edit1 = false;
	m_flag_edit2 = false;*/

	CDialog::UpdateWindow();
	// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	ShowImage( image, IDC_ImagePic );
	ShowImage( result1, IDC_Result1 );
	ShowImage( result2, IDC_Result2 );
	ShowImage( result3, IDC_Result3 );
	ShowImage( result4, IDC_Result4 );
	ShowImage( result5, IDC_Result5 );
	ShowImage( result6, IDC_Result6 );
	ShowImage( result7, IDC_Result7 );
	ShowImage( result8, IDC_Result8 );
	ShowImage( result9, IDC_Result9 );

	isImageLibReady=false;
	isImageSampleReady=false;

	uiExtractButton.EnableWindow(false);
	uiSearchButton.EnableWindow(false);
	uiNextPageButton.EnableWindow(false);
	uiFrontPageButton.EnableWindow(false);

	uiMethodRadio.SetCheck(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIRSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIRSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIRSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIRSystemDlg::ResizeImage1(IplImage* img)
{
	// ��ȡͼƬ�Ŀ�͸�
	int w = img->width;
	int h = img->height;

	// �ҳ���͸��еĽϴ�ֵ��
	int max = (w > h)? w: h;

	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	float scale = (float)((float)max/(float)uiImageHeight);

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(w/scale);
	int nh = (int)(h/scale);

	// Ϊ�˽����ź��ͼƬ���� image �����в�λ�������ͼƬ�� image ���Ͻǵ���������ֵ
	int tlx = (nw > nh)?0:(int)(uiImageHeight-nw)/2;
	int tly = (nw > nh)?(int)(uiImageHeight-nh)/2:0;

	// ���� image �� ROI ������������ͼƬ img
	cvSetImageROI(image, cvRect(tlx, tly, nw, nh));

	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize(img, image);

	// ���� image �� ROI ׼��������һ��ͼƬ
	cvResetImageROI(image);

}

void CIRSystemDlg::ResizeImage2(IplImage* img, IplImage* myImg)
{
	// ��ȡͼƬ�Ŀ�͸�
	int w = img->width;
	int h = img->height;

	// �ҳ���͸��еĽϴ�ֵ��
	int max = (w > h)? w: h;

	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	float scale = (float)((float)max/(float)uiResultHeight);

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(w/scale);
	int nh = (int)(h/scale);

	// Ϊ�˽����ź��ͼƬ���� TheImage �����в�λ�������ͼƬ�� TheImage ���Ͻǵ���������ֵ
	int tlx = (nw > nh)? 0: (int)(uiResultHeight-nw)/2;
	int tly = (nw > nh)? (int)(uiResultHeight-nh)/2: 0;

	// ���� TheImage �� ROI ������������ͼƬ img
	cvSetImageROI( myImg, cvRect( tlx, tly, nw, nh) );

	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize( img, myImg );

	// ���� TheImage �� ROI ׼��������һ��ͼƬ
	cvResetImageROI( myImg );
}

void CIRSystemDlg::ShowImage( IplImage* img, unsigned int uiID )
{
	// �����ʾ�ؼ��� DC
	CDC* pDC = GetDlgItem( uiID ) ->GetDC();
	// ��ȡ HDC(�豸���) �����л�ͼ����		
	HDC hDC = pDC ->GetSafeHdc();				

	CRect rect;
	GetDlgItem(uiID) ->GetClientRect( &rect );
	// ���ͼƬ�ؼ��Ŀ�͸�
	int rw = rect.right - rect.left;			
	int rh = rect.bottom - rect.top;
	// ��ȡͼƬ�Ŀ�͸�
	int iw = img->width;	
	int ih = img->height;
	// ʹͼƬ����ʾλ�������ڿؼ�������
	int tx = (int)(rw - iw)/2;	
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );
	// ����ͼƬ
	CvvImage cimg;
	cimg.CopyOf( img );
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������	
	cimg.DrawToHDC( hDC, &rect );	

	ReleaseDC( pDC );
}

void CIRSystemDlg::OnBnClickedButtonChooseImage()
{
	//* load image */
	CString FilePathName;
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal()==IDOK)
		FilePathName=dlg.GetPathName();

	IplImage* src=cvLoadImage(FilePathName.GetBuffer(),CV_LOAD_IMAGE_COLOR);
	while(src==NULL)
	{
		MessageBox(TEXT("����ͼƬʧ�ܣ�������ѡ��"));
		if(dlg.DoModal()==IDOK)
		{
			FilePathName=dlg.GetPathName();
			src=cvLoadImage(FilePathName.GetBuffer(),CV_LOAD_IMAGE_COLOR);
		}
		else
			break;
	}
	if(src!=NULL)
	{
		uiImagePath=FilePathName;
		UpdateData(FALSE);

		// ����һ����ʾ��ͼƬ��������
		if(image)	
			cvZero(image);

		// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
		ResizeImage1(src);	
		// ������ʾͼƬ����
		ShowImage(image, IDC_ImagePic);
		// �ͷ� ipl ռ�õ��ڴ�	
		cvReleaseImage(&src);

		isImageSampleReady=true;
	}
	else
	{
		isImageSampleReady=false;
	}

	if(isImageLibReady==true&&isImageSampleReady==true)
		uiSearchButton.EnableWindow(true);
}

void CIRSystemDlg::OnBnClickedButtonChooseImageDB()
{
	isImageLibReady=false;

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = "ѡ��ͼ����ļ���";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	//bi.iImage=IDI_ICON2;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(pIDList)
	{
		//ȡ���ļ���·����Buffer��
		SHGetPathFromIDList(pIDList, Buffer);
		uiImageLibPath=Buffer;
		UpdateData(FALSE);

		uiExtractButton.EnableWindow(true);
	}
	else
	{
		uiImageLibPath="";
		UpdateData(FALSE);

		uiExtractButton.EnableWindow(false);
	}
	isImageLibReady=false;

	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	//�ͷ��ڴ�
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
}

void CIRSystemDlg::scanDir(CString dirPath, vector<CString> & imageLibVector)
{
	_finddata64i32_t fileInfo;
	CString filename=dirPath+"\\*.*";

	long handle=_findfirst64i32(filename.GetBuffer(),&fileInfo);
	if(handle==-1)
	{
		return;
	}
	do 
	{
		if(strcmp(fileInfo.name,".")==0||strcmp(fileInfo.name,"..")==0)
		{
			continue;
		}
		CString subDirPath=dirPath+"\\"+fileInfo.name;
		if((fileInfo.attrib&_A_SUBDIR)==_A_SUBDIR)
		{
			scanDir(subDirPath,imageLibVector);
		}
		else
		{
			//������ܴ�ͼƬ,�����imageLibVector����֮����
			IplImage* test=cvLoadImage(subDirPath,CV_LOAD_IMAGE_COLOR);
			if(test)
			{
				imageLibVector.push_back(subDirPath);
			}
		}
	}
	while(!(_findnext64i32(handle,&fileInfo)));

	_findclose(handle);
}

void CIRSystemDlg::OnBnClickedButtonFeatureExtraction()
{
	imageLibVector.clear();
	scanDir(uiImageLibPath,imageLibVector);
	CString featuresFileName="..\\�����ɵ������ļ�\\ImageDB_features.txt";
	ofstream featuresLib(featuresFileName);
	//filename<<imageLibVector.size()<<endl;

	Feature feature;
	UpdateData(true);

	float* featuredata=new float[COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM];
	for(int i=0;i<imageLibVector.size();i++)
	{
		featuresLib<<imageLibVector[i]<<endl;
		feature.m_GetFeature(imageLibVector[i],featuredata);
		for (int j=0; j<COLOR_FEATURE_DIM+TEXTURE_FEATURE_DIM; j++)
		{
			featuresLib<<*(featuredata+j)<<endl;
		}
	}
	//imageLibVector.clear();
	featuresLib.close();

	uiFeatureFilePath=featuresFileName;
	UpdateData(FALSE);

	isImageLibReady=true;
	MessageBox(TEXT("������ȡ��ɣ�"));
	if(isImageLibReady==true&&isImageSampleReady==true)
		uiSearchButton.EnableWindow(true);
}


void CIRSystemDlg::OnBnClickedButtonLoadFeatureFile()
{
	CString FilePathName;
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		ifstream imageLibFeatures(FilePathName);
		if(!imageLibFeatures)
		{
			MessageBox(TEXT("����ʧ�ܣ������ļ���ʽ�Ƿ���ȷ��"));
			isImageLibReady=false;
		}
		else
		{
			imageLibVector.clear();
			char temp[MAX_PATH];
			while(!imageLibFeatures.eof())
			{
				imageLibFeatures.getline(temp,MAX_PATH);
				imageLibVector.push_back(temp);
				for(int i=0;i<COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM;i++)
				{
					imageLibFeatures.getline(temp,MAX_PATH);
				}
				
			}
			uiFeatureFilePath=FilePathName;
			UpdateData(FALSE);
			isImageLibReady=true;

			if(isImageLibReady==true&&isImageSampleReady==true)
				uiSearchButton.EnableWindow(true);
		}
		imageLibFeatures.close();
	}
}

void CIRSystemDlg::OnBnClickedButtonSearch()
{
	Feature feature;
	UpdateData(TRUE);
    
	float* imageFeature = new float[COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM];
	feature.m_GetFeature(uiImagePath, imageFeature);

	ifstream featuresFile(uiFeatureFilePath);
	//ofstream test("C:\\Users\\zhang yalin\\Desktop\\test.txt");

	char libImagePath[MAX_PATH];
	float* libImageFeature = new float[COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM];

	float* distances=new float[imageLibVector.size()]();  
	char* temp=new char[MAX_PATH];
	for (int i=0; i<imageLibVector.size(); i++)
	{
		featuresFile.getline(libImagePath,MAX_PATH);
		//test<<libImagePath<<endl;

		//featuresFile.getline((char*)featuresLine,(COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM)*sizeof(float));
		for(int j=0;j<COLOR_FEATURE_DIM + TEXTURE_FEATURE_DIM;j++)
		{
			featuresFile >> libImageFeature[j];
			//featuresFile.getline(temp,MAX_PATH);
			//memcpy(&libImageFeature[j],featuresLine+j,sizeof(float));
			//featuresFile.getline(libImagePath,MAX_PATH);
			//test<<libImageFeature[j]<<endl;
		}
		featuresFile.getline(libImagePath,MAX_PATH);
		distances[i]=feature.m_ManhattanDis(imageFeature, libImageFeature, COLOR_FEATURE_DIM+TEXTURE_FEATURE_DIM);
	}
	featuresFile.close();

	//�Եõ��ľ������������С����
	idx_min2max =new int[imageLibVector.size()]();               
	int* flag = new int[imageLibVector.size()]();                                     
	int minIdx = 0;
	for (int j=0; j<imageLibVector.size(); j++)
	{ 
		for (int i1=0; i1<imageLibVector.size(); i1++)
		{
		    if (flag[i1] == 0)
		    {
				minIdx = i1;
				break;
		    }
		}
		for (int i2=0; i2<imageLibVector.size(); i2++)
		{
			if (0 == flag[i2])
			{
				if (distances[i2]<distances[minIdx])
				{
					minIdx = i2;
				}
			}
			
		}
		flag[minIdx] = 1;
		idx_min2max[j] = minIdx;
	}

	//��ʾ���
	int outputNum = imageLibVector.size()>9? 9:imageLibVector.size();
  
	currentPage = 1;
	totalImgNum=imageLibVector.size();
	totalPage=totalImgNum/9;
	if ( 0!=(totalImgNum%9) )
	{
		totalPage ++;
	}

	if(imageLibVector.size() > 9)
		uiNextPageButton.EnableWindow(TRUE);

   	CString pageShow;
	pageShow.Format("%d/%d",currentPage,totalPage);
	GetDlgItem(IDC_PageNum)->SetWindowText(pageShow);

   	for (int i=0; i<outputNum; i++)
   	{
	   	// �ػ�Ի���
		CDialog::UpdateWindow();
		// ��ȡͼƬ,���浽һ���ֲ����� ipl ��
		IplImage* result = cvLoadImage( imageLibVector.at(idx_min2max[i]), CV_LOAD_IMAGE_COLOR );

		// �ж��Ƿ�ɹ���ȡͼƬ	
		if( ! result )			
			return;

		switch (i)
		{
		case 0:
			// ����һ����ʾ��ͼƬ��������
			cvZero(result1);
			// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
			ResizeImage2( result, result1 );	
			// ������ʾͼƬ����
			ShowImage( result1, IDC_Result1);
			break;
		case 1:
			cvZero(result2);
			ResizeImage2( result, result2 );	
			ShowImage( result2, IDC_Result2 );
			break;
		case 2:
			cvZero(result3);
			ResizeImage2( result, result3 );	
			ShowImage( result3, IDC_Result3 );
			break;
		case 3:
			cvZero(result4);
			ResizeImage2( result, result4 );	
			ShowImage( result4, IDC_Result4 );
			break;
		case 4:
			cvZero(result5);
			ResizeImage2( result, result5 );	
			ShowImage( result5, IDC_Result5 );
			break;
		case 5:
			cvZero(result6);
			ResizeImage2( result, result6 );	
			ShowImage( result6, IDC_Result6 );
			break;
		case 6:
			cvZero(result7);
			ResizeImage2( result, result7 );	
			ShowImage( result7, IDC_Result7 );
			break;
		case 7:
			cvZero(result8);
			ResizeImage2( result, result8 );	
			ShowImage( result8, IDC_Result8 );
			break;
		case 8:
			cvZero(result9);
			ResizeImage2( result, result9 );	
			ShowImage( result9, IDC_Result9 );
			break;
		}
		// �ͷ� result ռ�õ��ڴ�	
		cvReleaseImage( & result );
   	}

	delete [] libImageFeature;
	delete [] flag;
	delete [] distances;
	delete [] imageFeature;
	delete [] temp;
}


void CIRSystemDlg::OnBnClickedButtonFrontPage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CvSize ImgSize;
	ImgSize.height = uiResultHeight;
	ImgSize.width = uiResultWidth;
	result1 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result2 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result3 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result4 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result5 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result6 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result7 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result8 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result9 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );

	// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	CDialog::UpdateWindow();
	ShowImage( result1, IDC_Result1 );
	ShowImage( result2, IDC_Result2 );
	ShowImage( result3, IDC_Result3 );
	ShowImage( result4, IDC_Result4 );
	ShowImage( result5, IDC_Result5 );
	ShowImage( result6, IDC_Result6 );
	ShowImage( result7, IDC_Result7 );
	ShowImage( result8, IDC_Result8 );
	ShowImage( result9, IDC_Result9 );

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int start = (currentPage-2)*9;
	int end = start + 9;

	for (int i=start; i<end; i++)
	{
		// �ػ�Ի���
		CDialog::UpdateWindow();
		// ��ȡͼƬ,���浽һ���ֲ����� ipl ��
		IplImage* result = cvLoadImage( imageLibVector.at(idx_min2max[i]), CV_LOAD_IMAGE_COLOR );

		// �ж��Ƿ�ɹ���ȡͼƬ	
		if( ! result )			
			return;

		switch (i%9)
		{
		case 0:
			// ����һ����ʾ��ͼƬ��������
			if( result1 )	
				cvZero(result1);
			// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
			ResizeImage2( result, result1 );	
			// ������ʾͼƬ����
			ShowImage( result1, IDC_Result1);
			break;
		case 1:
			if( result2 )	
				cvZero(result2);
			ResizeImage2( result, result2 );	
			ShowImage( result2, IDC_Result2 );
			break;
		case 2:
			if( result3 )	
				cvZero(result3);
			ResizeImage2( result, result3 );	
			ShowImage( result3, IDC_Result3 );
			break;
		case 3:
			if( result4 )	
				cvZero(result4);
			ResizeImage2( result, result4 );	
			ShowImage( result4, IDC_Result4 );
			break;
		case 4:
			if( result5 )	
				cvZero(result5);
			ResizeImage2( result, result5 );	
			ShowImage( result5, IDC_Result5 );
			break;
		case 5:
			if( result6 )	
				cvZero(result6);
			ResizeImage2( result, result6 );	
			ShowImage( result6, IDC_Result6 );
			break;
		case 6:
			if( result7 )	
				cvZero(result7);
			ResizeImage2( result, result7 );	
			ShowImage( result7, IDC_Result7 );
			break;
		case 7:
			if( result8 )	
				cvZero(result8);
			ResizeImage2( result, result8 );	
			ShowImage( result8, IDC_Result8 );
			break;
		case 8:
			if( result9 )	
				cvZero(result9);
			ResizeImage2( result, result9 );	
			ShowImage( result9, IDC_Result9 );
			break;
		}
		// �ͷ� result ռ�õ��ڴ�	
		cvReleaseImage( & result );
	}
	// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	CDialog::UpdateWindow();
	UpdateData(false);

	currentPage -= 1;
	CString pageShow;
	pageShow.Format("%d/%d",currentPage,totalPage);
	GetDlgItem(IDC_PageNum)->SetWindowText(pageShow);
	if (1 == currentPage)
	{
		uiFrontPageButton.EnableWindow(FALSE);
	}

	if (currentPage < totalPage)
	{
		uiNextPageButton.EnableWindow(TRUE);
	}
}


void CIRSystemDlg::OnBnClickedButtonNextPage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CvSize ImgSize;
	ImgSize.height = uiResultHeight;
	ImgSize.width = uiResultWidth;
	result1 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result2 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result3 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result4 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result5 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result6 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result7 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result8 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );
	result9 = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNEL_NUM );

	// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	CDialog::UpdateWindow();
	ShowImage( result1, IDC_Result1 );
	ShowImage( result2, IDC_Result2 );
	ShowImage( result3, IDC_Result3 );
	ShowImage( result4, IDC_Result4 );
	ShowImage( result5, IDC_Result5 );
	ShowImage( result6, IDC_Result6 );
	ShowImage( result7, IDC_Result7 );
	ShowImage( result8, IDC_Result8 );
	ShowImage( result9, IDC_Result9 );

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int start = currentPage*9;
	int end = start + 9;
	if (end > totalImgNum)
	{
		end = totalImgNum;
	}
	for (int i=start; i<end; i++)
	{
		// �ػ�Ի���
		CDialog::UpdateWindow();
		// ��ȡͼƬ,���浽һ���ֲ����� ipl ��
		IplImage* result = cvLoadImage( imageLibVector.at(idx_min2max[i]), CV_LOAD_IMAGE_COLOR );

		// �ж��Ƿ�ɹ���ȡͼƬ	
		if( ! result )			
			return;

		switch (i%9)
		{
		case 0:
			// ����һ����ʾ��ͼƬ��������
			if( result1 )	
				cvZero(result1);
			// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
			ResizeImage2( result, result1 );	
			// ������ʾͼƬ����
			ShowImage( result1, IDC_Result1);
			break;
		case 1:
			if( result2 )	
				cvZero(result2);
			ResizeImage2( result, result2 );	
			ShowImage( result2, IDC_Result2 );
			break;
		case 2:
			if( result3 )	
				cvZero(result3);
			ResizeImage2( result, result3 );	
			ShowImage( result3, IDC_Result3 );
			break;
		case 3:
			if( result4 )	
				cvZero(result4);
			ResizeImage2( result, result4 );	
			ShowImage( result4, IDC_Result4 );
			break;
		case 4:
			if( result5 )	
				cvZero(result5);
			ResizeImage2( result, result5 );	
			ShowImage( result5, IDC_Result5 );
			break;
		case 5:
			if( result6 )	
				cvZero(result6);
			ResizeImage2( result, result6 );	
			ShowImage( result6, IDC_Result6 );
			break;
		case 6:
			if( result7 )	
				cvZero(result7);
			ResizeImage2( result, result7 );	
			ShowImage( result7, IDC_Result7 );
			break;
		case 7:
			if( result8 )	
				cvZero(result8);
			ResizeImage2( result, result8 );	
			ShowImage( result8, IDC_Result8 );
			break;
		case 8:
			if( result9 )	
				cvZero(result9);
			ResizeImage2( result, result9 );	
			ShowImage( result9, IDC_Result9 );
			break;
		}
		// �ͷ� result ռ�õ��ڴ�	
		cvReleaseImage( & result );
	}
	// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	CDialog::UpdateWindow();
	UpdateData(false);

	currentPage += 1;

	CString pageShow;
	pageShow.Format("%d/%d",currentPage,totalPage);
	GetDlgItem(IDC_PageNum)->SetWindowText(pageShow);

	if (1 != currentPage)
	{
		uiFrontPageButton.EnableWindow(TRUE);
	}
	if (currentPage >= totalPage)
	{
		uiNextPageButton.EnableWindow(FALSE);
	}
}

//void CIRSystemDlg::OnBnClickedRadioColor()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(MB_OK==MessageBox(TEXT("���ļ����������ͼ������½���������ȡ���Ƿ������"),"��ʾ!",MB_OKCANCEL))
//	{
//		isImageLibReady=false;
//		uiSearchButton.EnableWindow(FALSE);
//		#define FEATURE_TYPE COLOR
//	}
//}
//
//
//void CIRSystemDlg::OnBnClickedRadioTexture()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(MB_OK==MessageBox(TEXT("���ļ����������ͼ������½���������ȡ���Ƿ������"),"��ʾ!",MB_OKCANCEL))
//	{
//		isImageLibReady=false;
//		uiSearchButton.EnableWindow(FALSE);
//		#define FEATURE_TYPE TEXTURE
//	}
//}
//
//
//void CIRSystemDlg::OnBnClickedRadioGradient()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(MB_OK==MessageBox(TEXT("���ļ����������ͼ������½���������ȡ���Ƿ������"),"��ʾ!",MB_OKCANCEL))
//	{
//		isImageLibReady=false;
//		uiSearchButton.EnableWindow(FALSE);
//		#define FEATURE_TYPE GRADIENT
//	}
//}
//
//
//void CIRSystemDlg::OnBnClickedRadioColortexture()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(MB_OK==MessageBox(TEXT("���ļ����������ͼ������½���������ȡ���Ƿ������"),"��ʾ!",MB_OKCANCEL))
//	{
//		isImageLibReady=false;
//		uiSearchButton.EnableWindow(FALSE);
//		#define FEATURE_TYPE COLOR_TEXTURE
//	}
//}
