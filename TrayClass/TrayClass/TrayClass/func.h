#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;
#define WM_TRAY (WM_USER + 100)
#define WM_TASKBAR_CREATED RegisterWindowMessage(TEXT("TaskbarCreated"))

#define APP_NAME	TEXT("Tray Class by wzx000000@outlook")
#define APP_TIP		TEXT("Win32 API ʵ��ϵͳ���̳���")
class Tray {
public:
	
	//
	Tray();
	WNDCLASSEX wc = { 0 }; /* A properties struct of our window							���ڵ����Խṹ */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window			һ����������������H������ָ�����Ǵ��ڵ�ָ��  */
	MSG msg; /* A temporary location for all messages							 ������Ϣ����ʱλ��*/
	HINSTANCE his;

	UINT id;

	NOTIFYICONDATA nid;		//��������
	HMENU hMenu = CreatePopupMenu();			//���̲˵�
	void addItem(UINT command, const char * str);
	void initTray(HINSTANCE hInstance, HWND hwnd, UINT id, UINT IconId);
	

	int create(HINSTANCE hinsTance, WNDPROC callback, HINSTANCE iconHins, UINT this_id, int iconId,  int iCmdShow);
	void showTrayMsg(const char* str);
protected:

	//
};
Tray::Tray(){
	
}
void Tray::initTray(HINSTANCE hInstance, HWND hwnd ,UINT id ,UINT IconId) {
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = id;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_TRAY;
	nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IconId));
	lstrcpy(nid.szTip, APP_NAME);

	
	//Ϊ���̲˵��������ѡ��

	Shell_NotifyIcon(NIM_ADD, &nid);
}
void Tray::addItem(UINT command, const char * str) {
	AppendMenu(hMenu, MF_STRING, command, str);
}
void Tray::showTrayMsg(const char* str)
{
	lstrcpy(nid.szInfoTitle, APP_NAME);
	lstrcpy(nid.szInfo, str);
	nid.uTimeout = 1000;
	Shell_NotifyIcon(NIM_MODIFY, &nid);
}
int Tray::create(HINSTANCE hinsTance, WNDPROC callback,HINSTANCE iconHins,UINT this_id,int iconId,int iCmdShow) {
	wc.style = NULL;
	wc.hIcon = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinsTance;
	wc.lpfnWndProc = callback;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APP_NAME;
	wc.hCursor = NULL;

	if (!RegisterClass(&wc)) return 0;

	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, APP_NAME, APP_NAME, WS_POPUP, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinsTance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	id = this_id;
	initTray(iconHins, hwnd,id, iconId);			//ʵ��������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
