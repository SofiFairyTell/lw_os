#include "FileCopeDialogHeader.h"

BOOL Copy(LPCTSTR lpszFileName, const LPWIN32_FILE_ATTRIBUTE_DATA lpFileAttributeData, LPVOID lpvParam)
{
	LPCTSTR lpTargetDirectory = (LPCTSTR)lpvParam; // �������, � ������� ����� ����������� ����/�������

	TCHAR szNewFileName[MAX_PATH]; // ����� ��� �����/��������
	StringCchPrintf(szNewFileName, _countof(szNewFileName), TEXT("%s\\%s"), (LPCTSTR)lpTargetDirectory, PathFindFileName(lpszFileName));

	if (lpFileAttributeData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // ����� ����������� �������
	{
		// ������ ����� ������� (�������� ����������)
		BOOL bRet = CreateDirectoryEx(lpszFileName, szNewFileName, NULL);

		if ((FALSE != bRet) || (GetLastError() == ERROR_ALREADY_EXISTS)) // (!) ������: ���������� ������� �������, ��� ��� �� ��� ����������. 
		{
			// ��������� ����� ������ ��������
			bRet = FileSearch(TEXT("*"), lpszFileName, Copy, szNewFileName);
		} // if

		return bRet;
	} // if

	// �������� ����
	return CopyFile(lpszFileName, szNewFileName, FALSE);
}

BOOL FileSearch(LPCTSTR lpszFileName, LPCTSTR path, LPSEARCHFUNC lpSearchFunc, LPVOID lpvParam)
{
	WIN32_FIND_DATA ffd;

	TCHAR szDir[MAX_PATH];
	//TCHAR Path[MAX_PATH];

	HANDLE hFind = INVALID_HANDLE_VALUE;
	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*.*"));
	hFind = FindFirstFile(szDir, &ffd);

	BOOL bRet = TRUE;

	if (INVALID_HANDLE_VALUE == hFind)
	{
		//error
	}
	do
	{
		if ((0 == lstrcmp(ffd.cFileName, L".")) || (0 == lstrcmp(ffd.cFileName, L"..")))//����������
		{
			continue;
		}
		// ��������� ������ ���� � �����
		StringCchPrintf(szDir, MAX_PATH, TEXT("%s\\%s"), path, ffd.cFileName);

		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			bRet = lpSearchFunc(szDir, (LPWIN32_FILE_ATTRIBUTE_DATA)&ffd, lpvParam);
			if (FALSE == bRet) break; // ��������� �����
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	return TRUE;
}

BOOL FileOperation(LPCTSTR lpszFileName, LPCTSTR lpTargetDirectory, LPSEARCHFUNC lpFunc)
{
	if (NULL != lpTargetDirectory)
	{
		DWORD dwFileAttributes = GetFileAttributes(lpTargetDirectory);

		if (INVALID_FILE_ATTRIBUTES == dwFileAttributes) // (!) ������
		{
			return FALSE;
		}
		else if ((dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) // (!) �� �������� ���������
		{
			SetLastError(ERROR_PATH_NOT_FOUND);
			return FALSE;
		}
	}

	WIN32_FILE_ATTRIBUTE_DATA fad;

	// ������� ������������ ���������� �����/��������
	BOOL bRet = GetFileAttributesEx(lpszFileName, GetFileExInfoStandard, &fad);

	if (FALSE != bRet)
	{
		bRet = lpFunc(lpszFileName, &fad, (LPVOID)lpTargetDirectory);
	}

	return bRet;
}


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{

	HINSTANCE relib = LoadLibrary(TEXT("riched32.dll"));    //load the dll don't forget this   
											//and don't forget to free it (see wm_destroy) 
	if (relib == NULL)
		MessageBox(NULL, TEXT("Failed to load riched32.dll!"), TEXT("Error"), MB_ICONEXCLAMATION);
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = MainWindowProc; // ������� ���������
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 2);
	
	wcex.lpszClassName = TEXT("MainWindowClass"); // ��� ������
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (0 == RegisterClassEx(&wcex)) // ������������ �����
	{
		return -1; // ��������� ������ ����������
	}

	LoadLibrary(TEXT("ComCtl32.dll"));//��� ��������� ������ �����������
	// ������� ������� ���� �� ������ ������ �������� ������
	

	HWND hWnd = CreateWindowEx(0, TEXT("MainWindowClass"), TEXT("Process"), WS_OVERLAPPEDWINDOW,
		100, 100, 10, 10, NULL, NULL, hInstance, NULL);

	if (NULL == hWnd)
	{
		return -1; // ��������� ������ ����������
	}

	ShowWindow(hWnd, nCmdShow); // ���������� ������� ����



	MSG  msg;
	BOOL Ret;

	for (;;)
	{


		// ��������� ��������� �� �������
		Ret = GetMessage(&msg, NULL, 0, 0);
		if (Ret == FALSE)
		{
			break; // �������� WM_QUIT, ����� �� �����
		}
		else if (!TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return (int)msg.wParam;
}


LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HINSTANCE hInstance = GetWindowInstance(hwnd);
		HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DialogProc);
		ShowWindow(hDlg, SW_SHOW);
	}
	break;
	
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR FileName[260];
	BROWSEINFO bi;//structure for open special box with folder in treview
	HDC hdc;
	LPITEMIDLIST pidl;
	LPMALLOC  pMalloc = NULL;
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		DWORD xPos, yPos, nSize;
		TCHAR szBuf[80];

		// ��������� ���������� ������� ����
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
	
		/*�������� ����� ��� ������ � ������ editbox 
		���� ��, �� ������� ��� ���������������� editbox ���� ��� �� ����������*/
		if ((xPos > 312 & xPos < 544)&(yPos>39&yPos<81))
		{
			//� ����� ���������� �����������
				//TextOut(hdc, xPos, yPos, szBuf, nSize);
				ZeroMemory(&bi, sizeof(bi));
				bi.hwndOwner = NULL;
				bi.pszDisplayName = FileName;
				bi.lpszTitle = TEXT("Select folder");
				bi.ulFlags = BIF_RETURNONLYFSDIRS;

				pidl = SHBrowseForFolder(&bi);//open window for select
				if (pidl)
				{
					SHGetPathFromIDList(pidl, FileName);//get path
				}
				SetDlgItemText(hwndDlg, IDC_EDIT_TO,FileName);
		}
		else 
			if ((xPos > 36 & xPos < 250)&(yPos > 39 & yPos < 81))
			{
					ZeroMemory(&bi, sizeof(bi));
					bi.hwndOwner = NULL;
					bi.pszDisplayName = FileName;
					bi.lpszTitle = TEXT("Select folder");
					bi.ulFlags = BIF_BROWSEINCLUDEFILES;
					pidl = SHBrowseForFolder(&bi);//open window for select
					if (pidl)
					{
						SHGetPathFromIDList(pidl, FileName);//get path
					}
					SetDlgItemText(hwndDlg, IDC_EDIT_FROM, FileName);
				}
	}break;
	case WM_INITDIALOG:
	{
		BOOL bRet = HANDLE_WM_INITDIALOG(hwndDlg, wParam, lParam, Dialog_OnInitDialog);
		return SetDlgMsgResult(hwndDlg, uMsg, bRet);
	}

	case WM_CLOSE:
		HANDLE_WM_CLOSE(hwndDlg, wParam, lParam, Dialog_OnClose);

		return TRUE;

	case WM_COMMAND:
		HANDLE_WM_COMMAND(hwndDlg, wParam, lParam, Dialog_OnCommand);
		return TRUE;
	} // switch

	return FALSE;
} // DialogProc

// ----------------------------------------------------------------------------------------------
BOOL Dialog_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return TRUE;
}

void Dialog_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCLOSE);
	DestroyWindow(hwnd); // ���������� ����
	PostQuitMessage(0); // ���������� ��������� WM_QUIT
}

void Dialog_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	
	case IDOK:
	{
		TCHAR FromName[260];
		TCHAR ToName[260];
		GetDlgItemText(hwnd, IDC_EDIT_FROM, FromName, _countof(FromName));
		GetDlgItemText(hwnd, IDC_EDIT_TO, ToName, _countof(ToName));
		BOOL bRet = FileOperation(FromName, ToName, Copy);
		if (!(bRet == FALSE))
		{

			MessageBox(hwnd, L"����� �����������. ��������� ����� ����������", L" �����!", MB_OK);
			SetDlgItemText(hwnd, IDC_EDIT_FROM, L"...");
		}
		else
		{
			MessageBox(hwnd, L"����� �� �����������.", L"������", MB_YESNO);
			SetDlgItemText(hwnd, IDC_EDIT_FROM, L"...");
		}
	}
	break;

	case IDCANCEL:
	{
		// ��������� ������ ����������� ����
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd); // ���������� ����
		PostQuitMessage(0);
	}
	break;
	}
}