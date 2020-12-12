#pragma once
#include <iostream>
#include <Windows.h>
#include <string.h>

using namespace std;
#define MAX_STRING_SIZE 260
#define HEASDER_FILE_VERSION 2
#pragma warning(disable : 4996)



static char* U2G(const char* utf8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
static char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//获取打开的文件名
char* gfn1() {

	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//定义完了对话框
	GetOpenFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;

}

//获取打开的文件名,并将对话框作为子窗体
char* gfn1_child(HWND hwnd) {

	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//定义完了对话框
	GetOpenFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;
}

BOOL LoadFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF) {
			LPSTR pszFileText;
			pszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (pszFileText != NULL) {
				DWORD dwRead;
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL)) {
					pszFileText[dwFileSize] = 0; // Null terminator
					if (SetWindowText(hEdit, pszFileText))
						bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}//dev cpp中生成的 loadfile 
BOOL SaveFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(hEdit);
		if (dwTextLength > 0) {
			LPSTR pszText;
			pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			if (pszText != NULL) {
				if (GetWindowText(hEdit, pszText, dwTextLength + 1)) {
					DWORD dwWritten;
					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}//dev cpp中生成的 Savefile

void alert(const char str[], const char captain[]) {
	MessageBox(NULL, str, captain, NULL | MB_OK);
}
bool confirm(const char str[], const char captain[]) {
	int result = MessageBox(NULL, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}
void alertA(const char str[], const char captain[]) {
	MessageBox(NULL, str, captain, NULL | MB_OK);
}
class window_ {
public:
	WNDCLASSEX wc; /* A properties struct of our window							窗口的属性结构 */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window			一个“句柄”，因此是H，或者指向我们窗口的指针  */
	MSG msg; /* A temporary location for all messages							 所有消息的临时位置*/
	HINSTANCE his;
	char caption[256] = "Form";
	window_(/*WNDPROC , HINSTANCE*/);
	void histance_(HINSTANCE);
	void callback_(WNDPROC);
	bool create_wind(int width, int height);
	void alert(const char str[], const char captain[]);
	bool confirm(const char str[], const char captain[]);
	void setText(const char str[]);
protected:
	void sett(const char str[], HWND hedit);
	char* getText();
};
window_::window_(/*WNDPROC wndproc , HINSTANCE handle*/) {
	//构造函数
	memset(&this->wc, 0, sizeof(this->wc));
	this->wc.cbSize = sizeof(WNDCLASSEX);
	//this->wc.lpfnWndProc = WndProc; /* This is where we will send messages to		我们将向这里发送信息 */
	//this->wc.hInstance = hInstance;
	this->wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it
	白色，彩色窗口只是一个系统颜色的定义，请尝试按住Ctrl键并单击它  */
	this->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	this->wc.lpszClassName = "WindowClass_";
	this->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon	加载标准图标 */
	this->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon 使用名称“A”来使用项目图标 */



}
void window_::callback_(WNDPROC wndproc) {
	this->wc.lpfnWndProc = wndproc;

}
void window_::histance_(HINSTANCE handle) {
	this->wc.hInstance = handle;
	his = handle;
}
bool window_::create_wind(int width, int height) {
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass_", caption, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		width, /* width */
		height, /* height */
		NULL, NULL, this->wc.hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	while (GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... 如果没有收到错误  */
		TranslateMessage(&msg); /* Translate key codes to chars if present 	将密钥代码转换为字符（如果存在）*/
		DispatchMessage(&msg); /* Send it to WndProc 发送给WndProc。*/
	}
	return msg.wParam;
}
void window_::alert(const char str[], const char captain[]) {
	MessageBox(this->hwnd, str, captain, NULL | MB_OK);
}
bool window_::confirm(const char str[], const char captain[]) {
	int result = MessageBox(this->hwnd, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}
void window_::sett(const char str[], HWND hedit) {
	SetWindowText(hedit, str);
}
void window_::setText(const char str[]) {
	sett(str, hwnd);
}
char* window_::getText() {

	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}

class BasicControl {
public:
	HWND getHwnd();
	int getId();
	HWND hwnd_parent;
	//void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt);
	char* getText();
	void setText(const char* str);

protected:
	HWND hwnd;
	unsigned int id;
};
HWND BasicControl::getHwnd() {
	return this->hwnd;
}
int BasicControl::getId() {
	return this->id;
}
void BasicControl::setLocation(int x, int y, int width, int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
char* BasicControl::getText() {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
void BasicControl::setText(const char* str) {
	SetWindowText(this->hwnd, str);
}

class ListBasicControl {
public:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
	//void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt);

};

class Text_ :public BasicControl {
public:
	void create(const char str[], unsigned int Handle, HWND hparent);
};
void Text_::create(const char str[], unsigned int Handle, HWND hparent) {
	hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	hwnd_parent = hparent;
	id = Handle;

	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

}

class SimpleText_ : public Text_ {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

	}
};

class BorderText_ : public Text_ {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};
