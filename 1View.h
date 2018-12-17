// 1View.h : CMy1View 类的接口
//


#pragma once


class CMy1View : public CView
{
protected: // 仅从序列化创建
	CMy1View();
	DECLARE_DYNCREATE(CMy1View)

// 属性
public:
	CMy1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImageprocessingDisplayfileheader();
	afx_msg void OnUpdateImageprocessingDisplayfileheader(CCmdUI *pCmdUI);
	afx_msg void OnImageprocessingReadpixelvalue();
	afx_msg void OnImageprocessingSetpixelvalue();
	afx_msg void OnGaussiansmoothing();
	afx_msg void OnImageprocessingMedianfiltering();
};

#ifndef _DEBUG  // 1View.cpp 中的调试版本
inline CMy1Doc* CMy1View::GetDocument() const
   { return reinterpret_cast<CMy1Doc*>(m_pDocument); }
#endif

