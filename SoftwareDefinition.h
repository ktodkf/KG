#pragma once

#define OnMenuClicked  1
#define OnExitSoftware 2
#define OnButtonClicked 3
#define OnSaveFile 4
#define OnLoadFile 5
#define TextBufferSize 256 

char Buffer[TextBufferSize];

HWND hEditControl;

char filename[260];
OPENFILENAMEA ofn;


LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParams(HWND hWnd);
void LoadData(LPCSTR path);