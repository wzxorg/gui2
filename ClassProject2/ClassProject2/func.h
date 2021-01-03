#pragma once
#pragma once
#include <iostream>
#include <windows.h>
#include <string>
/********************************************
*											*
*Coptright 2020								*
*Win32 API Graphic programming Class library*
*Made By wzx000000@outlook.com				*
*											*
********************************************/
using namespace std;
#pragma warning(disable : 4996)
#define MAX_STRING_SIZE				260
#define HEADER_FILE_VERSION			2
#define Unload						DestroyWindow
#define text_char					char*
#define const_text_char				const char*

#define getFileName_char			gfn1
#define childGetFileNmae_char		gfn1_child
#define getFileNameSave				gfn_save

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
char* gfn_save(HWND hwnd) {
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
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	ofn.lpstrTitle = "另存为";
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
}
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
}

void alert(const char str[], const char captain[]) {
	MessageBox(NULL, str, captain, NULL | MB_OK);
}
bool confirm(const char str[], const char captain[]) {
	int result = MessageBox(NULL, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}


class Window_ {
public:
	WNDCLASSEX wc; /* A properties struct of our window							窗口的属性结构 */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window			一个“句柄”，因此是H，或者指向我们窗口的指针  */
	MSG msg; /* A temporary location for all messages							 所有消息的临时位置*/
	HINSTANCE his;
	char caption[256] = "Form";
	Window_(/*WNDPROC , HINSTANCE*/);
	void histance_(HINSTANCE);
	void callback_(WNDPROC);
	bool create_wind(int width, int height);
	void alert(const char str[], const char captain[]);
	bool confirm(const char str[], const char captain[]);
	void setText(const char str[]);
	char* getText();
	
protected:
	void sett(const char str[], HWND hedit);
};
Window_::Window_(/*WNDPROC wndproc , HINSTANCE handle*/) {
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
void Window_::callback_(WNDPROC wndproc) {
	this->wc.lpfnWndProc = wndproc;

}
void Window_::histance_(HINSTANCE handle) {
	this->wc.hInstance = handle;
	his = handle;
}
bool Window_::create_wind(int width, int height) {
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
void Window_::alert(const char str[], const char captain[]) {
	MessageBox(this->hwnd, str, captain, NULL | MB_OK);
}
bool Window_::confirm(const char str[], const char captain[]) {
	int result = MessageBox(this->hwnd, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}
void Window_::sett(const char str[], HWND hedit) {
	SetWindowText(hedit, str);
}
void Window_::setText(const char str[]) {
	sett(str, hwnd);
}
char* Window_::getText() {
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
	unsigned int getId();
	HWND getHwndParent();
	//void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt);
	char* getText();
	void setText(const char* str);

protected:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
};
HWND BasicControl::getHwnd() {
	return this->hwnd;
}
unsigned int BasicControl::getId() {
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
HWND BasicControl::getHwndParent() {
	return this->hwnd_parent;
}

class ListBasicControl {
public:
	HWND getHwnd();
	unsigned int getId();
	HWND getHwndParent();
	void setLocation(int x, int y, int width, int heignt);
protected:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
};
void ListBasicControl::setLocation(int x, int y, int width, int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
HWND ListBasicControl::getHwnd() {
	return this->hwnd;
}
unsigned int ListBasicControl::getId() {
	return this->id;
}
HWND ListBasicControl::getHwndParent() {
	return this->hwnd_parent;
}


class TextBox :public BasicControl {
public:
	void create(const char str[], unsigned int Handle, HWND hparent);
};
void TextBox::create(const char str[], unsigned int Handle, HWND hparent) {
	hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	hwnd_parent = hparent;
	id = Handle;

	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

}

class SimpleText : public TextBox {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

	}
};

class BorderText : public TextBox {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};


class Button : public BasicControl{
public:
	void create(const char captain[], unsigned int Handle, HWND hparent);
	
};
void Button::create(const char captain[], unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd = CreateWindow("BUTTON", captain, WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}


class Label :public BasicControl{
public:

	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",
			captain,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,
			(HMENU)Handle,
			GetModuleHandle(NULL),
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	
};


class BorderLabel : public Label {
public:
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",
			captain,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,
			(HMENU)Handle,
			GetModuleHandle(NULL),
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class CenterLabel :public Label {
public:
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",
			captain,
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,
			(HMENU)Handle,
			GetModuleHandle(NULL),
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class BitmapLabel :public Label {
public:
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",
			captain,
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE| SS_BITMAP| SS_ICON,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,
			(HMENU)Handle,
			GetModuleHandle(NULL),
			NULL);
		//SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class ListBox :public ListBasicControl {
public:
	
	void create(unsigned int Handle, HWND hparent);
	void add(const char str[]);
	char* getText(int size);
	int getIndex();
	void removeItem(int index);
	void insertItem(int index, const char str[]);
	void setItemText(int index, const char str[]);
	char* getItemText(int index, int size);
	void clean();
	int getCount();
};
void ListBox::create(unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VSCROLL | WS_TABSTOP | LBS_STANDARD | /*LBS_OWNERDRAWFIXED | */LBS_HASSTRINGS | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

}
void ListBox::add(const char str[]) {

	SendMessage(this->hwnd, LB_ADDSTRING, 0, (LPARAM)str);

}
char* ListBox::getText(int size) {
	if (size <= 0)return false;
	int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
	char* str = new char[size];
	ZeroMemory(str, size);
	if (lbItem > -1)
		SendMessage(this->hwnd, LB_GETTEXT, lbItem, (LPARAM)str);
	else return false;
	return str;
}
int ListBox::getIndex() {
	int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
	return lbItem;
}
void ListBox::removeItem(int index) {
	SendMessage(this->hwnd, LB_DELETESTRING, index, 0);
}
void ListBox::insertItem(int index, const char str[]) {
	SendMessage(this->hwnd, LB_INSERTSTRING, index, (LPARAM)str);
}
void ListBox::setItemText(int index, const char str[]) {
	this->removeItem(index);
	this->insertItem(index, str);
}
char* ListBox::getItemText(int index, int size) {
	if (size <= 0)return false;
	char* str = new char[size];
	ZeroMemory(str, size);
	if (index > -1)
		SendMessage(this->hwnd, LB_GETTEXT, index, (LPARAM)str);
	else return false;
	return str;
}
void ListBox::clean() {
	SendMessage(this->hwnd, LB_RESETCONTENT, 0, 0);
}
int ListBox::getCount() {
	return (int)SendMessage(hwnd, LB_GETCOUNT, 0, 0);
}

class ComboBox :public ListBasicControl {
public:
	
	void create(unsigned int Handle, HWND hparent);
	void add(const char str[]);
	char* getText(int size);
	int getIndex();
	void removeItem(int index);
	void insertItem(int index, const char str[]);
	void setItemText(int index, const char str[]);
	char* getItemText(int index, int size);
	void clean();
	int getCount();

	//char* getText_s();
};
void ComboBox::create(unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL | CBS_HASSTRINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
void ComboBox::add(const char str[]) {
	SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)str);
}
char* ComboBox::getText(int size) {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
int ComboBox::getIndex() {
	int lbItem = (int)SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
	return lbItem;
}
char* ComboBox::getItemText(int index, int size) {
	if (size <= 0)return false;
	char* str = new char[size];
	ZeroMemory(str, size);
	if (index > -1)
		SendMessage(this->hwnd, CB_GETLBTEXT, index, (LPARAM)str);
	else return false;
	return str;
}
void ComboBox::removeItem(int index) {
	SendMessage(hwnd, CB_DELETESTRING, index, 0);
}
void ComboBox::insertItem(int index, const char str[]) {
	SendMessage(hwnd, CB_INSERTSTRING, index, (LPARAM)str);
}
void ComboBox::setItemText(int index, const char str[]) {
	this->removeItem(index);
	this->insertItem(index, str);
}
void ComboBox::clean() {
	SendMessage(this->hwnd, CB_RESETCONTENT, 0, 0);
}
int ComboBox::getCount() {
	return (int)SendMessage(hwnd, CB_GETCOUNT, 0, 0);
}


class ComboBoxList : public ComboBox {
public:
	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_HASSTRINGS,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class Topmenu {
public:
	HMENU h_menu = CreateMenu();
	void show(HWND hparent);
};
void Topmenu::show(HWND hparent) {
	SetMenu(hparent, this->h_menu);
}

class childMenu {
public:
	HMENU h_menu = CreateMenu();
	void create(HMENU parent, const char* str);
	void addItem(unsigned int Command, const char* str);

};
void childMenu::create(HMENU parent, const char* str) {
	AppendMenu(parent, MF_POPUP, (UINT)h_menu, str);
}
void childMenu::addItem(unsigned int Command, const char* str) {
	AppendMenu(this->h_menu, MF_STRING, Command, str);
}

class RtMenu {
public:
	HMENU h_menu = CreatePopupMenu();
	void addItem(unsigned int Command, const char* str);
	void showRectMenu(HWND h_parent, LPARAM lParam);
};
void RtMenu::addItem(unsigned int Command, const char* str) {
	AppendMenu(this->h_menu, MF_STRING, Command, str);
}
void RtMenu::showRectMenu(HWND h_parent, LPARAM lParam) {
	RECT rect;
	GetWindowRect(h_parent, &rect);
	TrackPopupMenu(this->h_menu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, h_parent, &rect);
}

char* get_Win_Text(HWND hwnd) {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
bool set_Win_Text(HWND hwnd, const char str[]) {
	return SetWindowText(hwnd, str);
}

int getVersionInt() { return HEADER_FILE_VERSION; }

bool setWinIcon(HINSTANCE hins ,HWND hParent ,LPSTR name) {
	HICON hIcon = LoadIcon(hins, name);
	return SendMessage(hParent, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

bool setImage(HINSTANCE hins, HWND hwnd,LPSTR name) {
	HBITMAP	hBmp;
	hBmp = LoadBitmap(hins,name);
	return SendMessage(hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
}

//IO

bool setDefFont(HWND hwnd) {
	return SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}

LPSTR CHAR_ToLPSTR(const char* str) {
	return (LPSTR)str;
}
char* LPSTRtoCHAR(LPSTR str) {
	return (CHAR*)str;
}

char* readFile_char(LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;
	char * filetext;
	filetext = (CHAR *)"";
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
					filetext = pszFileText;
					bSuccess = true;
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	if (bSuccess)return filetext;
	return 0;
}

BOOL SaveFile_char(char* fileText, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = strlen(fileText);
		if (dwTextLength > 0) {
			LPSTR pszText=CHAR_ToLPSTR(fileText);
			if (pszText != NULL) {
				DWORD dwWritten;
				if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
					bSuccess = TRUE;

				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}
