#include "func.h"
#include "main.h"
#include "resource.h"
void UI_insertLvItem(UI_Lvitem item, int colNum, HWND hwnd) {
	LVITEM p1 = { 0 };
	p1.mask = LVIF_TEXT | LVIF_STATE;
	p1.state = INDEXTOSTATEIMAGEMASK(1);

	p1.pszText = (LPSTR)item.subItem[0].value;
	SendMessageA(hwnd, LVM_INSERTITEM, 0, (LPARAM)&p1);

	for (int i = 1; i < colNum; i++) {
		p1.iSubItem = i;
		p1.pszText = (LPSTR)item.subItem[i].value;
		SendMessageA(hwnd, LVM_SETITEMTEXT, 0, (LPARAM)&p1);

	}
}

void InsertColumn(HWND hwnd)
{
	//t1.create("",2001,hwnd);
	//t1.setLocation(0,188,220,20);
	LV_COLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.pszText = (LPSTR)"学号";
	lvc.cx = 60;
	SendMessage(hwnd, LVM_INSERTCOLUMN, 0, (long)&lvc);
	lvc.pszText = (LPSTR)"姓名";
	lvc.cx = 80;
	SendMessage(hwnd, LVM_INSERTCOLUMN, 1, (long)&lvc);

}
LRESULT CALLBACK About(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: {
		InsertColumn(GetDlgItem(hwnd, IDC_LIST1));
		//return TRUE;
		break;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			PostQuitMessage(1);
			return TRUE;
		}


		switch (wParam)
		{
		case IDC_BUTTON1: {
			UI_Lvitem item1;
			item1.subItem[0].value = get_Win_Text(GetDlgItem(hwnd, IDC_EDIT1));//第一列
			item1.subItem[1].value = get_Win_Text(GetDlgItem(hwnd, IDC_EDIT2));//第二列

			UI_insertLvItem(item1, 2, GetDlgItem(hwnd, IDC_LIST1));

		}
		}

		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(1);
		return TRUE;
	}
	}
	return FALSE;
}

void WINAPI LvMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hAbout = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),win1.hwnd, (DLGPROC)About);
	ShowWindow(hAbout, SW_SHOW);
	UpdateWindow(hAbout);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ;
}