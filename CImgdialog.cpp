// CImgdialog.cpp: 实现文件
//

#include "stdafx.h"
#include "1.h"
#include "CImgdialog.h"
#include "afxdialogex.h"


// CImgdialog 对话框

IMPLEMENT_DYNAMIC(CImgdialog, CDialogEx)

CImgdialog::CImgdialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CImgdialog::~CImgdialog()
{
}

void CImgdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImgdialog, CDialogEx)
END_MESSAGE_MAP()


// CImgdialog 消息处理程序
