#pragma once


// CImgdialog 对话框

class CImgdialog : public CDialogEx
{
	DECLARE_DYNAMIC(CImgdialog)

public:
	CImgdialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImgdialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
