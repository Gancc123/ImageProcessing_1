// 1Doc.h : CMy1Doc 类的接口
//


#pragma once


class CMy1Doc : public CDocument
{
protected: // 仅从序列化创建
	CMy1Doc();
	DECLARE_DYNCREATE(CMy1Doc)

// 属性
public:
	char *pFileBuf;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CMy1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImageprocessingOpenbmpfile();
	afx_msg void OnImageprocessingSavetonewbmpfile();
	afx_msg void OnImageprocessingImageinterpolation();
};


