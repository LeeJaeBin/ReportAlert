
// ReportAlertDlg.h: 헤더 파일
//

#pragma once
#define  WM_TRAYICON_MSG WM_USER + 1

// CReportAlertDlg 대화 상자
class CReportAlertDlg : public CDialogEx
{
// 생성입니다.
public:
	CReportAlertDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	void TraySetting(void);
	LRESULT TrayIconMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BOOL m_bTrayStatus;
	void OnOpenTest();
	void OnOpenExit();
	void OnOpenFdsa();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORTALERT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_EditName;
	afx_msg void OnBnClickedButton2();
	CEdit m_EditWhere;
	CStatic m_StaticFile;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CStatic m_StaticCPPath;
	afx_msg void OnBnClickedButton5();
};
