
// ReportAlertDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ReportAlert.h"
#include "ReportAlertDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CSettingDLG.h"

int Day = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString path = NULL;
CString strFilePath = NULL;

CString INIREADString(CString strAppName, CString strKeyName, CString strFilePath) {
	WCHAR szReturnString[1024] = { 0, };
	memset(szReturnString, NULL, 1024);
	GetPrivateProfileString(strAppName, strKeyName, L"", szReturnString, 1024, strFilePath);

	CString str = szReturnString;
	return str;
}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReportAlertDlg 대화 상자

CReportAlertDlg::CReportAlertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPORTALERT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportAlertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditName);
	DDX_Control(pDX, IDC_EDIT2, m_EditWhere);
	DDX_Control(pDX, IDC_STATIC_FILE, m_StaticFile);
	DDX_Control(pDX, IDC_STATIC_CPPATH, m_StaticCPPath);
}

BEGIN_MESSAGE_MAP(CReportAlertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_TRAYICON_MSG, CReportAlertDlg::TrayIconMessage)
	ON_COMMAND(ID_OPEN_ASDF, &CReportAlertDlg::OnOpenTest)
	ON_COMMAND(ID_OPEN_FDSA, &CReportAlertDlg::OnOpenFdsa)
	ON_COMMAND(ID_OPEN_EXIT, &CReportAlertDlg::OnOpenExit)
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReportAlertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CReportAlertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReportAlertDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CReportAlertDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CReportAlertDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

void CReportAlertDlg::TraySetting(void)
{
	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON_MSG;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	lstrcpy(nid.szTip, L"ReportAlert");
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_bTrayStatus = true;
}
// CReportAlertDlg 메시지 처리기

BOOL CReportAlertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bTrayStatus = FALSE;
	TraySetting();

	strFilePath = L"C:\\Users\\TERUTEN\\Desktop\\Data.ini";

	CString OriginFile = INIREADString(L"Setting", L"path", strFilePath);
	CString CPPath = INIREADString(L"Setting", L"CPPath", strFilePath);
	CString Name = INIREADString(L"Setting", L"name", strFilePath);
	CString Team = INIREADString(L"Setting", L"team", strFilePath);
	
	if (OriginFile.IsEmpty() == TRUE || Name.IsEmpty() == TRUE || Team.IsEmpty() == TRUE || CPPath.IsEmpty() == TRUE) {
		AfxMessageBox(L"Open 후 초기값 세팅이 필요합니다");
	}
	if (OriginFile.IsEmpty() == FALSE) {
		m_StaticFile.SetWindowTextW(OriginFile);
	}
	if (Name.IsEmpty() == FALSE) {
		m_EditName.SetWindowTextW(Name);
	}
	if (Team.IsEmpty() == FALSE) {
		m_EditWhere.SetWindowTextW(Team);
	}
	if (CPPath.IsEmpty() == FALSE) {
		m_StaticCPPath.SetWindowTextW(CPPath);
	}

	CButton* button;
	button = (CButton*)GetDlgItem(IDCANCEL);
	button->DestroyWindow();

	button = (CButton*)GetDlgItem(IDOK);
	button->DestroyWindow();

	SetTimer(1, 60000, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CReportAlertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CReportAlertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CReportAlertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CReportAlertDlg::TrayIconMessage(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDBLCLK) {
		ShowWindow(SW_SHOW);
	}
	else if (lParam == WM_RBUTTONDOWN) {
		CMenu menu, *pSubMenu;

		if (!menu.LoadMenu(IDR_MENU_POPUP))
			return 0;
		if (!(pSubMenu = menu.GetSubMenu(0)))
			return 0;

		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();

		pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
		menu.DestroyMenu();
	}
	return 0;
}

void CReportAlertDlg::OnOpenTest()
{
	ShowWindow(SW_SHOW);
	PostMessage(WM_SHOWWINDOW, TRUE, SW_OTHERZOOM);
}

void CReportAlertDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTrayStatus) {
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}

void INIWriteString(CString strAppName, CString strKeyName, CString strValue, CString strFilePath) {
	WritePrivateProfileString(strAppName, strKeyName, strValue, strFilePath);
}

void CReportAlertDlg::OnOpenExit()
{
	DWORD dwExitCode;
	DWORD dwPID = GetCurrentProcessId();

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPID);

	if (NULL != hProcess)
	{
		GetExitCodeProcess(hProcess, &dwExitCode);
		TerminateProcess(hProcess, dwExitCode);
		WaitForSingleObject(hProcess, INFINITE);
		CloseHandle(hProcess);
	}
}

void CReportAlertDlg::OnOpenFdsa()
{
	CSettingDLG SettingDLG;
	SettingDLG.DoModal();
}

void CReportAlertDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString OriginFile = INIREADString(L"Setting", L"path", strFilePath);
	CString CPPath = INIREADString(L"Setting", L"CPPath", strFilePath);
	CString Name = INIREADString(L"Setting", L"name", strFilePath);
	CString Team = INIREADString(L"Setting", L"team", strFilePath);

	CTime now = CTime::GetCurrentTime();
	int min = now.GetMinute();
	int DayOfWeek = now.GetDayOfWeek();
	int hour = now.GetHour();

	if (min == 38 && now.GetDay() != Day && DayOfWeek == 4 && hour == 15) {

		Day = now.GetDay();
		int Year = now.GetYear();
		Year = Year % 100;
		int Month = now.GetMonth();

		CString temp;
		temp.Format(L"%d%d%d", Year, Month, Day);
		CString str = CPPath + L"\\" + temp + Team + L"_주간보고_" + Name + L".xlsx";

		::CopyFile(OriginFile, str, FALSE);

		CString LastQuery = L"EXCEL " + str;

		WCHAR *wszProgID = T2W(LastQuery.GetBuffer());
		STARTUPINFO StartupInfo = { 0 };
		PROCESS_INFORMATION ProcessInfo;
		StartupInfo.cb = sizeof(STARTUPINFO);
		::CreateProcess(L"C:\\Program Files\\Microsoft Office\\Office16\\EXCEL.EXE", wszProgID, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
	}
	return;
}

void CReportAlertDlg::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);

	if (IDOK == dlg.DoModal()){
		path = dlg.GetPathName();
		INIWriteString(L"Setting", L"path", path, strFilePath);

		m_StaticFile.SetWindowTextW(path);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CReportAlertDlg::OnBnClickedButton2()
{
	CString name, team;
	m_EditName.GetWindowTextW(name);
	m_EditWhere.GetWindowTextW(team);
	INIWriteString(L"Setting", L"name", name, strFilePath);
	INIWriteString(L"Setting", L"team", team, strFilePath);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CReportAlertDlg::OnBnClickedButton3()
{
	TraySetting();
	ShowWindow(SW_SHOWMINIMIZED);
	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CReportAlertDlg::OnBnClickedButton4()
{
	BROWSEINFO BrInfo;
	WCHAR szBuffer[MAX_PATH];

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, MAX_PATH);

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("파일이 저장될 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);

	CString str;
	str = szBuffer;
	INIWriteString(L"Setting", L"CPPath", str, strFilePath);
	m_StaticCPPath.SetWindowTextW(str);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CReportAlertDlg::OnBnClickedButton5()
{
	CSettingDLG SettingDLG;
	SettingDLG.DoModal();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
