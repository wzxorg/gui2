#pragma once
#include <iostream>
#include <windows.h>
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

#define getFileName_char			gfn
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

#define gfn_allFiles		"All Files (*.*)\0*.*\0\0"
#define gfn_allFilesEx		""
#define gfn_textFile		"Text Files (*.txt)\0*.txt\0\0"
#define gfn_textFileA		"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0"
#define gfn_textFileEx		"txt"
#define gfn_richTextFile	"Rich Text Files (*.rtf)\0*.rtf\0\0"
#define gfn_richTextFileA	"Rich Text Files (*.rtf)\0*.rtf\0All Files (*.*)\0*.*\0\0"
#define gfn_richTextFileEx	"rtf"

inline char* gfn(HWND Hparent,const char * fileType,const char * ext) {

	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Hparent;
	ofn.lpstrFilter = fileType;
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = ext;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//定义完了对话框
	GetOpenFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;

}
inline char* gfn1_child(HWND hwnd) {

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
inline char* gfn_save(HWND hwnd,const char* fileType,const char* ext) {
	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = fileType;
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = ext;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	ofn.lpstrTitle = "另存为";
	//定义完了对话框
	GetSaveFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;
}
inline bool LoadFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	bool bSuccess = FALSE;

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
inline bool SaveFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	bool bSuccess = FALSE;

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
inline bool deleteFile(const char* Path) {
	if (remove(Path) == 0)return true;
	return false;
}

inline void alert(const char str[], const char captain[]) {
	MessageBox(NULL, str, captain, NULL | MB_OK);
}
inline bool confirm(const char str[], const char captain[]) {
	int result = MessageBox(NULL, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}


class Window {
public:
	WNDCLASSEX wc; /* A properties struct of our window							窗口的属性结构 */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window			一个“句柄”，因此是H，或者指向我们窗口的指针  */
	MSG msg; /* A temporary location for all messages							 所有消息的临时位置*/
	HINSTANCE his;
	char caption[256] = "Form";
	Window(/*WNDPROC , HINSTANCE*/) {
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
	void histance_(HINSTANCE handle) {
		this->wc.hInstance = handle;
		his = handle;
	}
	void callback_(WNDPROC wndproc) {
		this->wc.lpfnWndProc = wndproc;

	}
	bool create_wind(int width, int height) {
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
	void alert(const char str[], const char captain[]) {
		MessageBox(this->hwnd, str, captain, NULL | MB_OK);
	}
	bool confirm(const char str[], const char captain[]) {
		int result = MessageBox(this->hwnd, str, captain, NULL | MB_YESNO);
		if (result == IDYES)
			return true;

		return false;
	}
	void setText(const char str[]) {
		sett(str, hwnd);
	}
	char* getText() {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(this->hwnd);
		LPSTR pszText;
		pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		GetWindowText(this->hwnd, pszText, dwTextLength + 1);
		return (char*)pszText;
	}

protected:
	void sett(const char str[], HWND hedit) {
		SetWindowText(hedit, str);
	}
};

class BasicControl {
public:
	HWND getHwnd(){
		return this->hwnd;
	}
	unsigned int getId() {
		return this->id;
	}
	HWND getHwndParent() {
		return this->hwnd_parent;
	}
	void setHWND(HWND hWnd) {
		hwnd = hWnd;
	}
	//void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt) {
		MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
	}
	char* getText() {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(this->hwnd);
		LPSTR pszText;
		pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		GetWindowText(this->hwnd, pszText, dwTextLength + 1);
		return (char*)pszText;
	}
	void setText(const char* str) {
		SetWindowText(this->hwnd, str);
	}

protected:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
};

class ListBasicControl {
public:
	HWND getHwnd() {
		return this->hwnd;
	}
	unsigned int getId() {
		return this->id;
	}
	HWND getHwndParent() {
		return this->hwnd_parent;
	}
	void setHWND(HWND hWnd) {
		hwnd = hWnd;
	}
	//void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt) {
		MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
	}
protected:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;

};


class TextBox :public BasicControl {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

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


class Button : public BasicControl {
public:
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("BUTTON", captain, WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}

};

class Label :public BasicControl {
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
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_BITMAP | SS_ICON,
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

	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VSCROLL | WS_TABSTOP | LBS_STANDARD | /*LBS_OWNERDRAWFIXED | */LBS_HASSTRINGS | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

	}
	void add(const char str[]) {
		SendMessage(this->hwnd, LB_ADDSTRING, 0, (LPARAM)str);
	}
	char* getText(int size) {
		if (size <= 0)return false;
		int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
		char* str = new char[size];
		ZeroMemory(str, size);
		if (lbItem > -1)
			SendMessage(this->hwnd, LB_GETTEXT, lbItem, (LPARAM)str);
		else return false;
		return str;
	}
	int getIndex() {
		int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
		return lbItem;
	}
	void removeItem(int index) {
		SendMessage(this->hwnd, LB_DELETESTRING, index, 0);
	}
	void insertItem(int index, const char str[]) {
		SendMessage(this->hwnd, LB_INSERTSTRING, index, (LPARAM)str);
	}
	void setItemText(int index, const char str[]) {
		this->removeItem(index);
		this->insertItem(index, str);
	}
	char* getItemText(int index, int size) {
		if (size <= 0)return false;
		char* str = new char[size];
		ZeroMemory(str, size);
		if (index > -1)
			SendMessage(this->hwnd, LB_GETTEXT, index, (LPARAM)str);
		else return false;
		return str;
	}
	void clean() {
		SendMessage(this->hwnd, LB_RESETCONTENT, 0, 0);
	}
	int getCount() {
		return (int)SendMessage(hwnd, LB_GETCOUNT, 0, 0);
	}
};

class ComboBox :public ListBasicControl {
public:

	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL | CBS_HASSTRINGS,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	void add(const char str[]) {
		SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)str);
	}
	char* getText(int size) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(this->hwnd);
		LPSTR pszText;
		pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
		GetWindowText(this->hwnd, pszText, dwTextLength + 1);
		return (char*)pszText;
	}
	int getIndex() {
		int lbItem = (int)SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
		return lbItem;
	}
	void removeItem(int index) {
		SendMessage(hwnd, CB_DELETESTRING, index, 0);
	}
	void insertItem(int index, const char str[]) {
		SendMessage(hwnd, CB_INSERTSTRING, index, (LPARAM)str);
	}
	void setItemText(int index, const char str[]) {
		this->removeItem(index);
		this->insertItem(index, str);
	}
	char* getItemText(int index, int size) {
		if (size <= 0)return false;
		char* str = new char[size];
		ZeroMemory(str, size);
		if (index > -1)
			SendMessage(this->hwnd, CB_GETLBTEXT, index, (LPARAM)str);
		else return false;
		return str;
	}
	void clean() {
		SendMessage(this->hwnd, CB_RESETCONTENT, 0, 0);
	}
	int getCount() {
		return (int)SendMessage(hwnd, CB_GETCOUNT, 0, 0);
	}

	//char* getText_s();
};

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
	void show(HWND hparent) {
		SetMenu(hparent, this->h_menu);
	}
};

class childMenu {
public:
	HMENU h_menu = CreateMenu();
	void create(HMENU parent, const char* str){
		AppendMenu(parent, MF_POPUP, (UINT)h_menu, str);
	}
	void addItem(unsigned int Command, const char* str) {
		AppendMenu(this->h_menu, MF_STRING, Command, str);
	}

};

class RtMenu {
public:
	HMENU h_menu = CreatePopupMenu();
	void addItem(unsigned int Command, const char* str) {
		AppendMenu(this->h_menu, MF_STRING, Command, str);
	}
	void showRectMenu(HWND h_parent, LPARAM lParam) {
		RECT rect;
		GetWindowRect(h_parent, &rect);
		TrackPopupMenu(this->h_menu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, h_parent, &rect);
	}
};

inline char* get_Win_Text(HWND hwnd) {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
inline bool set_Win_Text(HWND hwnd, const char str[]) {
	return SetWindowText(hwnd, str);
}
inline int getVersionInt() { return HEADER_FILE_VERSION; }
inline bool setWinIcon(HINSTANCE hins, HWND hParent, LPSTR name) {
	HICON hIcon = LoadIcon(hins, name);
	return SendMessage(hParent, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}
inline bool setImage(HINSTANCE hins, HWND hwnd, LPSTR name) {
	HBITMAP	hBmp;
	hBmp = LoadBitmap(hins, name);
	return SendMessage(hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
}
inline bool setDefFont(HWND hwnd) {
	return SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
inline void setWinLocation(HWND hwnd, int x, int y, int width, int height) {
	MoveWindow(hwnd, x, y, width, height, TRUE);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
//IO

inline LPSTR CHAR_ToLPSTR(const char* str) {
	return (LPSTR)str;
}
inline char* LPSTRtoCHAR(LPSTR str) {
	return (CHAR*)str;
}

inline char* readFile_char(LPSTR pszFileName) {
	HANDLE hFile;
	bool bSuccess = FALSE;
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

inline bool SaveFile_char(char* fileText, LPSTR pszFileName) {
	HANDLE hFile;
	bool bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = strlen(fileText);
		if (dwTextLength > 0) {
			LPSTR pszText = CHAR_ToLPSTR(fileText);
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

//Control Marcos
inline HWND createTextBox(const char str[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createSimpleText(const char str[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_BORDER,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createBorderText(const char str[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_BORDER,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createLabel(const char captain[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow(
		"STATIC",
		captain,
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hparent,
		(HMENU)Handle,
		GetModuleHandle(NULL),
		NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createBorderLabel(const char captain[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow(
		"STATIC",
		captain,
		WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hparent,
		(HMENU)Handle,
		GetModuleHandle(NULL),
		NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createCenterLabel(const char captain[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow(
		"STATIC",
		captain,
		WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hparent,
		(HMENU)Handle,
		GetModuleHandle(NULL),
		NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createButton(const char captain[], unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("BUTTON", captain, WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createListBox(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VSCROLL | WS_TABSTOP | LBS_STANDARD | /*LBS_OWNERDRAWFIXED | */LBS_HASSTRINGS | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createComboBox(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL | CBS_HASSTRINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HWND createComboBoxList(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_HASSTRINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}

inline void Combo_add(HWND hwnd,const char str[]) {
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)str);
}
inline char* Combo_getText(HWND hwnd ,int size) {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
inline int Combo_getIndex(HWND hwnd) {
	int lbItem = (int)SendMessage(hwnd, CB_GETCURSEL, 0, 0);
	return lbItem;
}
inline void Combo_removeItem(HWND hwnd, int index) {
	SendMessage(hwnd, CB_DELETESTRING, index, 0);
}
inline void Combo_insertItem(HWND hwnd, int index, const char str[]) {
	SendMessage(hwnd, CB_INSERTSTRING, index, (LPARAM)str);
}
inline void Combo_setItemText(HWND hwnd, int index, const char str[]) {
	Combo_removeItem(hwnd,index);
	Combo_insertItem(hwnd,index, str);
}
inline char* Combo_getItemText(HWND hwnd, int index, int size) {
	if (size <= 0)return false;
	char* str = new char[size];
	ZeroMemory(str, size);
	if (index > -1)
		SendMessage(hwnd, CB_GETLBTEXT, index, (LPARAM)str);
	else return false;
	return str;
}
inline void Combo_clean(HWND hwnd) {
	SendMessage(hwnd, CB_RESETCONTENT, 0, 0);
}
inline int Combo_getCount(HWND hwnd) {
	return (int)SendMessage(hwnd, CB_GETCOUNT, 0, 0);
}

inline void ListBox_add(HWND hwnd, const char str[]) {
	SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)str);
}
inline char* ListBox_getText(HWND hwnd, int size) {
	if (size <= 0)return false;
	int lbItem = (int)SendMessage(hwnd, LB_GETCURSEL, 0, 0);
	char* str = new char[size];
	ZeroMemory(str, size);
	if (lbItem > -1)
		SendMessage(hwnd, LB_GETTEXT, lbItem, (LPARAM)str);
	else return false;
	return str;
}
inline int ListBox_getIndex(HWND hwnd) {
	int lbItem = (int)SendMessage(hwnd, LB_GETCURSEL, 0, 0);
	return lbItem;
}
inline void ListBox_removeItem(HWND hwnd, int index) {
	SendMessage(hwnd, LB_DELETESTRING, index, 0);
}
inline void ListBox_insertItem(HWND hwnd, int index, const char str[]) {
	SendMessage(hwnd, LB_INSERTSTRING, index, (LPARAM)str);
}
inline void ListBox_setItemText(HWND hwnd, int index, const char str[]) {
	ListBox_removeItem(hwnd, index);
	ListBox_insertItem(hwnd, index, str);
}
inline char* ListBox_getItemText(HWND hwnd, int index, int size) {
	if (size <= 0)return false;
	char* str = new char[size];
	ZeroMemory(str, size);
	if (index > -1)
		SendMessage(hwnd, LB_GETTEXT, index, (LPARAM)str);
	else return false;
	return str;
}
inline void ListBox_clean(HWND hwnd) {
	SendMessage(hwnd, LB_RESETCONTENT, 0, 0);
}
inline int ListBox_getCount(HWND hwnd) {
	return (int)SendMessage(hwnd, LB_GETCOUNT, 0, 0);
}

#define WindowWidth LOWORD(lParam)
#define WindowHeight HIWORD(lParam)
#define UIgetDlgItem(id) GetDlgItem(hwnd, id)

typedef Window			UIWindow;
typedef TextBox			UITextBox;
typedef SimpleText		UISimpleText;
typedef BorderText		UIBorderText;
typedef Button			UIButton;
typedef Label			UILabel;
typedef BorderLabel		UIBorderLabel;
typedef CenterLabel		UICenterLabel;
typedef ListBox			UIListBox;
typedef ComboBox		UIComboBox;
typedef ComboBoxList	UIComboBoxList;
typedef Topmenu			UITopmenu;
typedef childMenu		UIchildMenu;
typedef RtMenu			UIRtMenu;
#include <commctrl.h>
#include <stdio.h>
#pragma comment(lib, "comctl32.lib")

/********************************************************
*														*
*Coptright 2020-2021									*
*Win32 API Advanced Graphic programming Class library	*
*Made By wzx000000@outlook.com							*
*														*
********************************************************/

#define TableBoxMaxSting	4100//获取tablebox中字符串的最大长度(4 and 1/256 kBytes)，必要时可修改
#define TableBoxMaxCol		128//tablebox中字符串的最大列数 (128)，必要时可修改


class Dialog {
public:
	HWND hwnd;
	MSG msg;
	HINSTANCE hins;
	void create(WNDPROC callBack, unsigned int RC_int, HWND hParent) {
		hwnd = CreateDialog(hins, MAKEINTRESOURCE(RC_int), hParent, (DLGPROC)callBack);
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		ZeroMemory(&msg, sizeof(msg));

		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void hinst(HINSTANCE hins_) {
		hins = hins_;
	}

};
class UI_Lvsubitem {
public:
	UI_Lvsubitem() {
		this->value = "";
	}

	const char* value;

};
class UI_LvCol {
public:
	UI_LvCol() {
		this->value = "";
		size = 0;
	}
	const char* value;
	int size;

};

class UI_LvPop {
public:
	UI_LvCol cols[TableBoxMaxCol];
};
class UI_Lvitem {
public:
	UI_Lvsubitem  subItem[TableBoxMaxCol];
};
class TableBox : public  ListBasicControl {
public:
	void create(unsigned int Handle, HWND hparent) {
		//InitCommonControls();
		this->id = Handle;
		hwnd = CreateWindowEx(NULL, "SysListView32", 0, LVS_REPORT | WS_CHILD | WS_VISIBLE | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);

		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
		this->hwnd_parent = hparent;
		//Refresh();
	}
	void setColume(UI_LvPop cols, int numOfCol/*列的数量*/) {

		LV_COLUMN lvc;
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		for (int i = 0; i < numOfCol; i++) {
			lvc.pszText = (LPSTR)cols.cols[i].value;
			lvc.cx = cols.cols[i].size;
			SendMessage(this->hwnd, LVM_INSERTCOLUMN, i, (long)&lvc);
		}
	}
	void addItem(UI_Lvitem item, int numOfCol/*列的数量*/) {
		LVITEM p1 = { 0 };
		p1.mask = LVIF_TEXT | LVIF_STATE;
		p1.state = INDEXTOSTATEIMAGEMASK(1);

		p1.pszText = (LPSTR)item.subItem[0].value;

		SendMessageA(hwnd, LVM_INSERTITEM, 0, (LPARAM)&p1);

		for (int i = 1; i < numOfCol; i++) {
			p1.iSubItem = i;
			p1.pszText = (LPSTR)item.subItem[i].value;
			SendMessageA(hwnd, LVM_SETITEMTEXT, 0, (LPARAM)&p1);
		}
	}
	int getIndex() {
		return SendMessageA(hwnd, LVM_GETSELECTIONMARK, 0, 0);

	}
	void clear() {
		SendMessageA(hwnd, LVM_DELETEALLITEMS, 0, 0);
	}
	int getCount() {
		return SendMessageA(hwnd, LVM_GETITEMCOUNT, 0, 0);
	}
	bool removeItem(int index) {
		return SendMessageA(hwnd, LVM_DELETEITEM, index, 0);
	}
	char* getItemText(int index, int col) {
		LPSTR lpstr = NULL;
		char str[TableBoxMaxSting];
		ZeroMemory(str, TableBoxMaxSting);
		ListView_GetItemText(this->hwnd, index, col, str, TableBoxMaxSting);
		return (CHAR*)str;
	}
	bool setItemText(int index, int col, const char* str) {
		LVITEM p1 = { 0 };
		p1.mask = LVIF_TEXT | LVIF_STATE;
		p1.state = INDEXTOSTATEIMAGEMASK(1);
		p1.iSubItem = col;
		p1.pszText = (LPSTR)str;
		return SendMessageA(hwnd, LVM_SETITEMTEXT, index, (LPARAM)&p1);
	}

	int getSelCount() {
		return SendMessageA(hwnd, LVM_GETSELECTEDCOUNT, 0, 0);
	}
	bool getSelIf(int index) {/*判断某项是否被选中*/
		if (SendMessageA(hwnd, LVM_GETITEMSTATE, index, LVIS_SELECTED))return true;
		return false;
	}/*判断某项是否被选中*/
	void clearAll() {
		int nCols = 0;			//ListView列数
		HWND hWnd, hWndHeader;
		LVITEM lvItem;
		hWnd = hwnd;
		SendMessage(hWnd, LVM_DELETEALLITEMS, 0, 0);
		hWndHeader = (HWND)SendMessage(hWnd, LVM_GETHEADER, 0, 0);
		nCols = SendMessage(hWndHeader, HDM_GETITEMCOUNT, 0, 0);
		while (nCols)
		{
			SendMessage(hWnd, LVM_DELETECOLUMN, 0, (LPARAM)&lvItem);
			nCols--;
		}
	}
	char * getColumeText(int index) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_TEXT;
		lvc.cchTextMax = TableBoxMaxSting;
		lvc.iSubItem = index;
		char str[TableBoxMaxSting];
		lvc.pszText = str;
		ListView_GetColumn(hwnd, index, &lvc);
		return str;
	}
	int getColCount() {
		HWND hWndHeader = (HWND)SendMessage(this->hwnd, LVM_GETHEADER, 0, 0);
		return SendMessage(hWndHeader, HDM_GETITEMCOUNT, 0, 0);
	}
};

typedef Dialog		UIDialog;
typedef UI_LvPop	UILvPop;
typedef UI_Lvitem	UILvitem;
typedef TableBox	UITableBox;

#define UI_TVI HTREEITEM
#define TreeBoxMaxSting 4100//获取treebox中字符串的最大长度(4 and 1/256 kBytes)，必要时可修改
class TreeBox :public ListBasicControl {
public:
	void create(unsigned int Handle, HWND hparent) {
		InitCommonControls();
		this->id = Handle;
		hwnd = CreateWindowEx(NULL, "SysTreeView32", 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);

		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
		this->hwnd_parent = hparent;
	}
	HTREEITEM add(HTREEITEM itemParent,const char * str) {
		tagTVINSERTSTRUCTA tvitem1;
		tvitem1.hParent = itemParent;
		tvitem1.hInsertAfter = TVI_ROOT;
		tvitem1.itemex.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM ;
		tvitem1.itemex.pszText = (LPSTR)str;
		return TreeView_InsertItem(hwnd, &tvitem1);
	}
	HTREEITEM getSelItem() {
		HTREEITEM Selected = TreeView_GetSelection(hwnd);
		return Selected;
	}
	char* getItemText(HTREEITEM item) {
		TVITEM itt;
		char temp[TableBoxMaxSting];
		itt.hItem = item;
		itt.mask = TVIF_TEXT | TVIF_HANDLE ;
		itt.cchTextMax = TableBoxMaxSting;
		itt.pszText = temp;
		TreeView_GetItem(hwnd, &itt);
		return (CHAR*)temp;
	}
	void setItemText(HTREEITEM item,const char* str) {
		TVITEM item1;
		item1.mask = TVIF_TEXT | TVIF_HANDLE ;
		item1.pszText =(LPSTR)str;
		item1.hItem = item;

		TreeView_SetItem(hwnd, &item1);
	}
	bool removeItem(HTREEITEM item) {
		if (item == TVI_ROOT || item == NULL)return false;
		return SendMessage(hwnd, TVM_DELETEITEM, 0, (LPARAM)item);
	}
	bool clear() {
		return SendMessage(hwnd, TVM_DELETEITEM, 0, (LPARAM)NULL);
	}
};
class ProgressBar :public BasicControl {
public:
	void create(unsigned int Handle, HWND hparent) {
		InitCommonControls();
		this->id = Handle;
		hwnd = CreateWindowEx(NULL, "msctls_progress32", 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);

		ShowWindow(hwnd, SW_SHOW);
		this->hwnd_parent = hparent;
	}
	bool setRange(int value) {
		return SendMessage(hwnd, PBM_SETRANGE32, 0, (LPARAM)value);
	}
	bool setPos(int value) {
		return SendMessage(hwnd, PBM_SETPOS, (WPARAM)value, 0);
	}
	unsigned int getPos() {
		return SendMessage(hwnd, PBM_GETPOS, 0, 0);
	}
	unsigned int getHighLimit() {
		return SendMessage(hwnd, PBM_GETRANGE, 0, 0);
	}
	unsigned int getLowLimit() {
		return SendMessage(hwnd, PBM_GETRANGE, 1, 0);
	}
};

class CheckBox : public BasicControl {
public:
	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("BUTTON", "", BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	bool getCheckIf() {
		if(SendMessage(hwnd, BM_GETCHECK,0,0)== BST_CHECKED)return true;
		return false;
	}
	bool getUncheckIf() {
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_UNCHECKED)return true;
		return false;
	}
	bool setCheck() {
		return SendMessage(hwnd, BM_SETCHECK, BST_CHECKED, 0);
	}
	bool setUnchecked() {
		return SendMessage(hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
	}
};
class CheckBox3 : public CheckBox {
public:
	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("BUTTON", "", BS_AUTO3STATE | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	bool setIndeterminate() {
		return SendMessage(hwnd, BM_SETCHECK, BST_INDETERMINATE, 0);
	}
	bool getIndeterminateIf() {
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)return true;
		return false;
	}
	int getState() {
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)return BST_INDETERMINATE;
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED)return BST_CHECKED;
		return BST_UNCHECKED;
	}
};

class MdiChildWindowClass {
public:
	WNDCLASSEX wc;
	MdiChildWindowClass() {
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_3DSHADOW + 1);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.lpszMenuName = NULL;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	}
	bool registerWindowClass(HINSTANCE hinst,WNDPROC callback,LPCSTR className) {
		wc.lpfnWndProc = callback;
		wc.hInstance = hinst;
		wc.lpszClassName = className;
		if (!RegisterClassEx(&wc)) {
			//MessageBox(0, "Could Not Register Child Window", "Oh Oh...",MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
		return true;
	}
};

class MDIClient :public ListBasicControl{
public:
	
	void create(unsigned int Handle, HWND hparent,HINSTANCE hinst,int ID_MDI_FIRSTCHILD,void * HWindowMenu) {
		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = HWindowMenu;
		//ccs.hWindowMenu = NULL;
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;//第一个子窗体ID

		this->hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent, (HMENU)Handle, hinst, (LPVOID)&ccs);
		ShowWindow(this->hwnd, SW_SHOW);
		this->id = Handle;
		this->hwnd_parent = hparent;
	}
	bool createChildWindow(HINSTANCE hinst,LPCSTR classNmae,LPCSTR caption) {
		MDICREATESTRUCT mcs;
		HWND hChild;

		mcs.szTitle = caption;
		mcs.szClass = classNmae;
		mcs.hOwner = hinst;
		mcs.x = mcs.cx = CW_USEDEFAULT;
		mcs.y = mcs.cy = CW_USEDEFAULT;
		mcs.style = MDIS_ALLCHILDSTYLES;

		hChild = (HWND)SendMessage(this->hwnd, WM_MDICREATE, 0, (LPARAM)&mcs);
		if (!hChild) {
			return false;
		}
		return true;
	}
};

typedef MdiChildWindowClass		UIMdiChildWindowClass;
typedef MDIClient				UIMDIClient;

inline HWND createTableBox(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindowEx(NULL, "SysListView32", 0, LVS_REPORT | WS_CHILD | WS_VISIBLE | WS_BORDER,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline void TableBox_setColume(HWND hwnd, UI_LvPop cols, int numOfCol/*列的数量*/) {

	LV_COLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	for (int i = 0; i < numOfCol; i++) {
		lvc.pszText = (LPSTR)cols.cols[i].value;
		lvc.cx = cols.cols[i].size;
		SendMessage(hwnd, LVM_INSERTCOLUMN, i, (long)&lvc);
	}
}
inline void TableBox_addItem(HWND hwnd, UI_Lvitem item, int numOfCol/*列的数量*/) {
	LVITEM p1 = { 0 };
	p1.mask = LVIF_TEXT | LVIF_STATE;
	p1.state = INDEXTOSTATEIMAGEMASK(1);

	p1.pszText = (LPSTR)item.subItem[0].value;

	SendMessageA(hwnd, LVM_INSERTITEM, 0, (LPARAM)&p1);

	for (int i = 1; i < numOfCol; i++) {
		p1.iSubItem = i;
		p1.pszText = (LPSTR)item.subItem[i].value;
		SendMessageA(hwnd, LVM_SETITEMTEXT, 0, (LPARAM)&p1);
	}
}
inline int TableBox_getIndex(HWND hwnd) {
	return SendMessageA(hwnd, LVM_GETSELECTIONMARK, 0, 0);

}
inline void TableBox_clear(HWND hwnd) {
	SendMessageA(hwnd, LVM_DELETEALLITEMS, 0, 0);
}
inline int TableBox_getCount(HWND hwnd) {
	return SendMessageA(hwnd, LVM_GETITEMCOUNT, 0, 0);
}
inline bool TableBox_removeItem(HWND hwnd, int index) {
	return SendMessageA(hwnd, LVM_DELETEITEM, index, 0);
}
inline char* TableBox_getItemText(HWND hwnd, int index, int col) {
	LPSTR lpstr = NULL;
	char str[TableBoxMaxSting];
	ZeroMemory(str, TableBoxMaxSting);
	ListView_GetItemText(hwnd, index, col, str, TableBoxMaxSting);
	return (CHAR*)str;
}
inline bool TableBox_setItemText(HWND hwnd, int index, int col, const char* str) {
	LVITEM p1 = { 0 };
	p1.mask = LVIF_TEXT | LVIF_STATE;
	p1.state = INDEXTOSTATEIMAGEMASK(1);
	p1.iSubItem = col;
	p1.pszText = (LPSTR)str;
	return SendMessageA(hwnd, LVM_SETITEMTEXT, index, (LPARAM)&p1);
}
inline int TableBox_getSelCount(HWND hwnd) {
	return SendMessageA(hwnd, LVM_GETSELECTEDCOUNT, 0, 0);
}
inline bool TableBox_getSelIf(HWND hwnd, int index) {/*判断某项是否被选中*/
	if (SendMessageA(hwnd, LVM_GETITEMSTATE, index, LVIS_SELECTED))return true;
	return false;
}/*判断某项是否被选中*/
inline void TableBox_clearAll(HWND hwnd) {
	int nCols = 0;			//ListView列数
	HWND hWnd, hWndHeader;
	LVITEM lvItem;
	hWnd = hwnd;
	SendMessage(hWnd, LVM_DELETEALLITEMS, 0, 0);
	hWndHeader = (HWND)SendMessage(hWnd, LVM_GETHEADER, 0, 0);
	nCols = SendMessage(hWndHeader, HDM_GETITEMCOUNT, 0, 0);
	while (nCols)
	{
		SendMessage(hWnd, LVM_DELETECOLUMN, 0, (LPARAM)&lvItem);
		nCols--;
	}
}
inline char * TableBox_getColumeText(HWND hwnd, int index) {
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT;
	lvc.cchTextMax = TableBoxMaxSting;
	lvc.iSubItem = index;
	char str[TableBoxMaxSting];
	lvc.pszText = str;
	ListView_GetColumn(hwnd, index, &lvc);
	return str;
}
inline int TableBox_getColCount(HWND hwnd) {
	HWND hWndHeader = (HWND)SendMessage(hwnd, LVM_GETHEADER, 0, 0);
	return SendMessage(hWndHeader, HDM_GETITEMCOUNT, 0, 0);
}

inline HWND createTreeBox(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindowEx(NULL, "SysTreeView32", 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline HTREEITEM TreeBox_add(HWND hwnd, HTREEITEM itemParent, const char * str) {
	tagTVINSERTSTRUCTA tvitem1;
	tvitem1.hParent = itemParent;
	tvitem1.hInsertAfter = TVI_ROOT;
	tvitem1.itemex.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
	tvitem1.itemex.pszText = (LPSTR)str;
	return TreeView_InsertItem(hwnd, &tvitem1);
}
inline HTREEITEM TreeBox_getSelItem(HWND hwnd) {
	HTREEITEM Selected = TreeView_GetSelection(hwnd);
	return Selected;
}
inline char* TreeBox_getItemText(HWND hwnd, HTREEITEM item) {
	TVITEM itt;
	char temp[TableBoxMaxSting];
	itt.hItem = item;
	itt.mask = TVIF_TEXT | TVIF_HANDLE;
	itt.cchTextMax = TableBoxMaxSting;
	itt.pszText = temp;
	TreeView_GetItem(hwnd, &itt);
	return (CHAR*)temp;
}
inline void TreeBox_setItemText(HWND hwnd, HTREEITEM item, const char* str) {
	TVITEM item1;
	item1.mask = TVIF_TEXT | TVIF_HANDLE;
	item1.pszText = (LPSTR)str;
	item1.hItem = item;

	TreeView_SetItem(hwnd, &item1);
}
inline bool TreeBox_removeItem(HWND hwnd, HTREEITEM item) {
	if (item == TVI_ROOT || item == NULL)return false;
	return SendMessage(hwnd, TVM_DELETEITEM, 0, (LPARAM)item);
}
inline bool TreeBox_clear(HWND hwnd) {
	return SendMessage(hwnd, TVM_DELETEITEM, 0, (LPARAM)NULL);
}

inline HWND createCheckBox(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("BUTTON", "", BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline bool CheckBox_getCheckIf(HWND hwnd) {
	if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED)return true;
	return false;
}
inline bool CheckBox_getUncheckIf(HWND hwnd) {
	if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_UNCHECKED)return true;
	return false;
}
inline bool CheckBox_setCheck(HWND hwnd) {
	return SendMessage(hwnd, BM_SETCHECK, BST_CHECKED, 0);
}
inline bool CheckBox_setUnchecked(HWND hwnd) {
	return SendMessage(hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
}

inline HWND createCheckBox3(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindow("BUTTON", "", BS_AUTO3STATE | WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline bool CheckBox3_setIndeterminate(HWND hwnd) {
	return SendMessage(hwnd, BM_SETCHECK, BST_INDETERMINATE, 0);
}
inline bool CheckBox3_getIndeterminateIf(HWND hwnd) {
	if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)return true;
	return false;
}
inline int CheckBox3_getState(HWND hwnd) {
	if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)return BST_INDETERMINATE;
	if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED)return BST_CHECKED;
	return BST_UNCHECKED;
}

inline HWND createProgressBar(unsigned int Handle, HWND hparent) {
	HWND hwnd = CreateWindowEx(NULL, "msctls_progress32", 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}
inline bool ProgressBar_setRange(HWND hwnd, int value) {
	return SendMessage(hwnd, PBM_SETRANGE32, 0, (LPARAM)value);
}
inline bool ProgressBar_setPos(HWND hwnd, int value) {
	return SendMessage(hwnd, PBM_SETPOS, (WPARAM)value, 0);
}
inline unsigned int ProgressBar_getPos(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETPOS, 0, 0);
}
inline unsigned int ProgressBar_getHighLimit(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETRANGE, 0, 0);
}
inline unsigned int ProgressBar_getLowLimit(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETRANGE, 1, 0);
}

class RadioButton : public BasicControl {
public:
	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	bool getCheckIf() {
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED)return true;
		return false;
	}
	bool getUncheckIf() {
		if (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_UNCHECKED)return true;
		return false;
	}
	bool setCheck() {
		return SendMessage(hwnd, BM_SETCHECK, BST_CHECKED, 0);
	}
	bool setUnchecked() {
		return SendMessage(hwnd, BM_SETCHECK, BST_UNCHECKED, 0);
	}
};

inline HWND createRadioButton(unsigned int Handle, HWND hparent) {
	HWND hwnd= CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	return hwnd;
}

#define RadioButton_getCheckIf			CheckBox_getCheckIf
#define RadioButton_getUncheckIf		CheckBox_getUncheckIf
#define	RadioButton_setCheck			CheckBox_setCheck
#define	RadioButton_setUnchecked		CheckBox_setUnchecked

typedef RadioButton UIRadioButton;

class ToolBar : public ListBasicControl {
public:
	HWND create(unsigned int Handle, HWND hparent) {
		hwnd= CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
			hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;
		ShowWindow(hwnd, SW_SHOW);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
		SendMessage(hwnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
		return hwnd;
	}
	void addStdBitmap() {
		TBADDBITMAP tbab;
		tbab.hInst = HINST_COMMCTRL;
		tbab.nID = IDB_STD_SMALL_COLOR;
		SendMessage(hwnd, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	}
	void addButtons(TBBUTTON * tbb,int nButtons) {
		SendMessage(hwnd, TB_ADDBUTTONS, nButtons, (LPARAM)tbb);
	}
	void addBitmapList(const int ImageListID,HIMAGELIST g_hImageList) {
		SendMessage(hwnd, TB_SETIMAGELIST,
			(WPARAM)ImageListID,
			(LPARAM)g_hImageList);
	}
};

class StatusBar : public ListBasicControl {
public:
	HWND create(unsigned int Handle, HWND hparent) {
		this->hwnd=CreateWindowEx(0, "msctls_statusbar32", NULL,
			WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
			hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;
		ShowWindow(hwnd, SW_SHOW);
		SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
		return hwnd;
	}
	bool setParts(int iStatusWidths[], int cols) {
		return SendMessage(this->hwnd, SB_SETPARTS, cols, (LPARAM)iStatusWidths);
	}
	bool setText(int iSubitem,const char* str) {
		return SendMessage(this->hwnd, SB_SETTEXT, iSubitem, (LPARAM)str);
	}
	char* getText(int iSubitem) {
		char* str = NULL;
		int size = (int)SendMessage(this->hwnd, SB_GETTEXTLENGTH, iSubitem, 0);
		str = new char[size];
		SendMessage(this->hwnd, SB_GETTEXT, iSubitem, (LPARAM)str);
		return str;
	}
};

typedef ToolBar		UIToolBar;
typedef StatusBar	UIStatusBar;