// CSettingDLG.cpp: 구현 파일
//

#include "stdafx.h"
#include "ReportAlert.h"
#include "CSettingDLG.h"
#include "afxdialogex.h"
#include "resource.h"


// CSettingDLG 대화 상자

IMPLEMENT_DYNAMIC(CSettingDLG, CDialogEx)

CSettingDLG::CSettingDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDLG::~CSettingDLG()
{
}

void CSettingDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettingDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSettingDLG::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSettingDLG 메시지 처리기

static BOOL SetRegistyStartProgram(BOOL bAutoExec, LPCWSTR lpValueName, WCHAR* lpExeFileName)
{
	HKEY hKey;
	LONG lRes;
	LONG lRes2;
	if (bAutoExec)
	{
		if (lpValueName == NULL || lpExeFileName == NULL)
			return FALSE;
		lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);

		int n = wcslen(lpExeFileName);
		
		if (lRes == ERROR_SUCCESS){
			lRes2 = RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpExeFileName, wcslen(lpExeFileName) * 2);
			RegCloseKey(hKey);

			if(lRes2 == ERROR_SUCCESS)
				return TRUE;
			else {
				AfxMessageBox(L"Set Error");
				return FALSE;
			}
		}

		else if (lRes == ERROR_ACCESS_DENIED) {
			AfxMessageBox(L"권한 없음");
			return FALSE;
		}

		else {
			AfxMessageBox(L"Error");
			return FALSE;
		}
	}
	else
	{
		lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
		if (lRes == ERROR_SUCCESS) {
			
			lRes2 = RegDeleteValue(hKey, lpValueName);
			RegCloseKey(hKey);

			if (lRes2 == ERROR_SUCCESS) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		else if (lRes == ERROR_ACCESS_DENIED) {
			AfxMessageBox(L"권한 없음");
			return FALSE;
		}

		else
			return FALSE;
	}

	return FALSE;
}

void CSettingDLG::OnBnClickedButton1()
{
	WCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	BOOL Result = SetRegistyStartProgram(TRUE, L"ReportAlert", path);
	if (Result == TRUE) {
		AfxMessageBox(L"Success");
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSettingDLG::OnBnClickedButton2()
{
	BOOL Result = SetRegistyStartProgram(FALSE, L"ReportAlert", NULL);
	if (Result == TRUE) {
		AfxMessageBox(L"Success");
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
