#include <Windows.h>
#include "SoftwareDefinition.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return 1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100,
		500, 250, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;


	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		case OnButtonClicked:
			SetWindowTextA(hEditControl, "");
			break;
		case OnLoadFile:
			if (GetOpenFileNameA(&ofn)) { LoadData(filename); }
			break;
		default: break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Open");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("static", "Window!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 490, 20, hWnd, NULL, NULL, NULL);

	hEditControl = CreateWindowA("edit", "hello", WS_VISIBLE | WS_CHILD, 5, 50, 490, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnButtonClicked, NULL, NULL);
}

void LoadData(LPCSTR path)
{
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);
	SetWindowTextA(hEditControl, Buffer);
	CloseHandle(FileToLoad);
}

void SetOpenFileParams(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:/Users/Кристина/source/repos/Компьютерная графика/LW2";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}


//HRESULT Load(LPCTSTR szFile)
//{
//	// Create IImgCtx object
//	HRESULT hr = ::CoCreateInstance(CLSID_IImgCtx, NULL, CLSCTX_ALL, IID_IImgCtx, (void**)&m_pImage);
//	if (SUCCEEDED(hr))
//	{
//		// Load URL
//		USES_CONVERSION;
//		hr = m_pImage->Load(
//			T2COLE(szFile),            // [in] URL
//			0                        // [in] Flags and preffered color format
//		);
//	}
//
//	return hr;
//}
//
//HRESULT DrawImg(HDC hdc, RECT& rcBounds)
//{
//	if (m_pImage)
//	{
//		// Check download state
//		DWORD dwState = 0;
//		HRESULT hr = m_pImage->GetStateInfo(&dwState, NULL, true);
//		if (SUCCEEDED(hr))
//		{
//			if (IMGLOAD_LOADING & dwState)
//			{
//				// Still loading - wait 50 msec and request again
//				::DrawText(hdc, _T("Loading, please wait..."), -1, &rcBounds, DT_SINGLELINE);
//				::Sleep(50);
//				Invalidate(false);
//
//				hr = S_FALSE;
//			}
//			else if (IMGLOAD_COMPLETE & dwState)
//			{
//				// Download successfully complete
//				hr = m_pImage->Draw(
//					hdc,                // [in] Handle of device context on which to render the image
//					&rcBounds            // [in] Position and dimensions
//				);
//			}
//			else
//			{
//				// Download failed
//				hr = E_UNEXPECTED;
//			}
//		}
//		return hr;
//	}
//
//	return E_UNEXPECTED;
//}
