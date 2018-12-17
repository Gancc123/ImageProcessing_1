// 1View.cpp : CMy1View ���ʵ��
//

#include "stdafx.h"
#include "1.h"

#include "1Doc.h"
#include "1View.h"
#include "GlobalCommon.h"
#include "CImgdialog.h"
#include <vector>
#include <algorithm>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1View

IMPLEMENT_DYNCREATE(CMy1View, CView)

BEGIN_MESSAGE_MAP(CMy1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_IMAGEPROCESSING_DISPLAYFILEHEADER, &CMy1View::OnImageprocessingDisplayfileheader)
	ON_UPDATE_COMMAND_UI(ID_IMAGEPROCESSING_DISPLAYFILEHEADER, &CMy1View::OnUpdateImageprocessingDisplayfileheader)
	ON_COMMAND(ID_IMAGEPROCESSING_READPIXELVALUE, &CMy1View::OnImageprocessingReadpixelvalue)
	ON_COMMAND(ID_IMAGEPROCESSING_SETPIXELVALUE, &CMy1View::OnImageprocessingSetpixelvalue)
	ON_COMMAND(ID_GAUSSIANSMOOTHING, &CMy1View::OnGaussiansmoothing)
	ON_COMMAND(ID_IMAGEPROCESSING_MEDIANFILTERING32782, &CMy1View::OnImageprocessingMedianfiltering)
END_MESSAGE_MAP()

// CMy1View ����/����

CMy1View::CMy1View()
{
	// TODO: �ڴ˴���ӹ������

}

CMy1View::~CMy1View()
{
}

BOOL CMy1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

void CMy1View::OnDraw(CDC *pDC)
{
	CMy1Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	/**/
	if( pDoc->pFileBuf != NULL )
	{
// 		static int dispMode = -1;	//only used for grayscale images: 0=normal, 1/2/3=displayed in Red,Green,and Blue
// 		dispMode++;
		DisplayImage(pDC,pDoc->pFileBuf,50,50,0,0,0);
	}

}

BOOL CMy1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy1View ���

#ifdef _DEBUG
void CMy1View::AssertValid() const
{
	CView::AssertValid();
}

void CMy1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy1Doc* CMy1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Doc)));
	return (CMy1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy1View ��Ϣ�������

void CMy1View::OnImageprocessingDisplayfileheader()
{
	CMy1Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	if( pDoc->pFileBuf != NULL )
	{
		DisplayHeaderMessage(pDoc->pFileBuf);
	}
}

void CMy1View::OnUpdateImageprocessingDisplayfileheader(CCmdUI *pCmdUI)
{
	CMy1Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	pCmdUI->Enable(pDoc->pFileBuf != NULL);
}

void CMy1View::OnImageprocessingReadpixelvalue()
{
	int x = 100;
	int y = 100;
	RGBQUAD rgb;
	CMy1Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	if( pDoc->pFileBuf != NULL )
	{
		bool bGray;
		GetPixel(pDoc->pFileBuf, x, y, &rgb, &bGray);
		char buf[100];
		if( bGray )
			sprintf(buf, "(%d,%d) = %d", x, y, rgb.rgbReserved);
		else
			sprintf(buf, "(%d,%d) = (%d, %d, %d)", x, y, rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
		AfxMessageBox( buf );
	}
}

void CMy1View::OnImageprocessingSetpixelvalue()
{
	int x = 100;
	int y = 100;
	RGBQUAD rgb;
	rgb.rgbReserved = 255;
	rgb.rgbRed      = 255;
	rgb.rgbGreen    = 255;
	rgb.rgbBlue     = 255;
	CMy1Doc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	if( pDoc->pFileBuf != NULL )
	{
		SetPixel(pDoc->pFileBuf, x, y, rgb);
		ValidateRect(NULL);
	}
}

double generateGaussianTemplate(double * window, int ksize, double sigma)//���ɸ�˹ģ��
{
	double ret = 0.0;

	static const double pi = 3.1415926;
	int center = ksize / 2; // ģ�������λ�ã�Ҳ���������ԭ��
	double x2, y2;
	for (int i = 0; i < ksize; i++)
	{
		x2 = pow(i - center, 2);
		for (int j = 0; j < ksize; j++)
		{
			y2 = pow(j - center, 2);
			double g = exp(-(x2 + y2) / (2 * sigma * sigma));
			g /= 2 * pi * sigma;
			window[i * ksize + j] = g;
		}
	}
	double k = 1 / window[0]; // �����Ͻǵ�ϵ����һ��Ϊ1
	for (int i = 0; i < ksize; i++)
	{
		for (int j = 0; j < ksize; j++)
		{
			window[i * ksize + j] *= k;
			ret += window[i * ksize + j];
		}
	}

	return ret;
}

void CMy1View::OnGaussiansmoothing()
{
	// TODO: �ڴ���������������
	const int i_window_size = 3;
	const double d_sigma = 0.5;

	double GaussianTemplate[i_window_size * i_window_size];
	memset(GaussianTemplate, 0, i_window_size * i_window_size * sizeof(double));
	double d_sum = generateGaussianTemplate(GaussianTemplate, i_window_size, d_sigma);

	CMy1Doc *pDoc = GetDocument();//ȡ��ͼ���ļ�
	ASSERT_VALID(pDoc);
	if (!pDoc) return;//����ļ��Ƿ���Ч
	
	if (pDoc->pFileBuf != NULL)
	{
		int i_row = GetImageHeight(pDoc->pFileBuf);//��ȡ����
		int i_colum = GetImageWidth(pDoc->pFileBuf);//��ȡ����
		unsigned char * p = (unsigned char *)pDoc->pFileBuf;
		for (int i = 1; i < i_row - 1; i++)//(i,j)��Ҫ���������
		{
			for (int j = 1; j < i_colum - 1; j++)
			{
				int now = 0;
				double result = 0.0;
				for (int ii = i - 1; ii <= i + 1; ii++)
				{
					for (int jj = j - 1; jj <= j + 1; jj++)
					{
						result += p[ii * i_colum + jj] * GaussianTemplate[now++];
					}
				}
				p[i * i_colum + j] = result / d_sum;
			}
		}
		Invalidate();
		UpdateWindow();
	}
}

void InsertionSort(unsigned char * pArray, int iSize)
{
	for (int j = 1; j < iSize; j++)
	{
		unsigned char i_current_number = pArray[j];//jΪ��ǰҪ�����Ԫ��
		int i = j - 1;//�±�0~j-1��Ԫ�����ź���
		while (i >= 0 && pArray[i] > i_current_number)//�����ź����Ԫ�ص�ĩβ��ʼ���������Ԫ�رȽ�
		//���ȴ�����Ԫ�ش󣬽���Ԫ��������һ�Σ�ѭ����ֹʱҪô������Ԫ��С������Ԫ�أ�i=-1����Ҫô����
		//vec[i]С��vec[i+1]��ԭֵ��������vec[i+1]=vec[i]��vec[i+1]��Ϊ��ȷλ��
		{
			pArray[i + 1] = pArray[i];
			i--;
		}
		pArray[i + 1] = i_current_number;
	}
}

void CMy1View::OnImageprocessingMedianfiltering()
{
	// TODO: �ڴ���������������
	CMy1Doc *pDoc = GetDocument();//ȡ��ͼ���ļ�
	ASSERT_VALID(pDoc);
	if (!pDoc) return;//����ļ��Ƿ���Ч
	unsigned char grayv[9] = { 0 };
	if (pDoc->pFileBuf != NULL)
	{
		int i_row = GetImageHeight(pDoc->pFileBuf);//��ȡ����
		int i_colum = GetImageWidth(pDoc->pFileBuf);//��ȡ����
		unsigned char * p = (unsigned char*)pDoc->pFileBuf;
		for (int i = 1; i < i_row - 1; i++)//(i,j)��Ҫ���������
		{
			for (int j = 1; j < i_colum - 1; j++)
			{
				int now = 0;
				for (int ii = i - 1; ii <= i + 1; ii++)
					for (int jj = j - 1; jj <= j + 1; jj++)
						grayv[now++] = p[ii*i_colum + jj];
				InsertionSort(grayv, 9);
				p[i*i_colum + j] = grayv[4];
			}
		}
		Invalidate();
		UpdateWindow();
		// 		CImgdialog d;
		// 		d.DoModal();
	}
	// TODO: �ڴ���������������
}
