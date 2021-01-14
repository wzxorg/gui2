#include "func.h"
#include "main.h"
#include "resource.h"
#include "extstr.h"
#define pb_setMax 0
#define pb_setMin 1
#define pb_hwnd GetDlgItem(hwnd, IDC_PROGRESS1)
TextBox ttt;
bool setRange(HWND hwnd,int value ) {
	return SendMessage(hwnd, PBM_SETRANGE32, 0, (LPARAM)value);
}
bool setPos(HWND hwnd, int value) {
	return SendMessage(hwnd, PBM_SETPOS, (WPARAM)value, 0);
}
unsigned int getPos(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETPOS, 0, 0);
}
unsigned int getHignLimit(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETRANGE, 0, 0);
}
unsigned int getLowLimit(HWND hwnd) {
	return SendMessage(hwnd, PBM_GETRANGE, 1, 0);
}

void d3_wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	//alert(intToChar(23),"");
	ttt.setHWND(GetDlgItem(hwnd, IDC_EDIT1));
}
bool d3_wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
	{
		
		EndDialog(hwnd, LOWORD(wParam));
		PostQuitMessage(1);
		return TRUE;
	}
	switch (wParam)
	{
		//list an example
	case IDC_BUTTON1: {
		setRange(pb_hwnd,1000);
		//SendMessage(hwnd, PBM_SETRANGE, 0, HIWORD(1000)| LOWORD(0));
		break;
	}
	case IDC_BUTTON2: {
		String str;
		str = ttt.getText();
		int Int = strTOint(str);
		setPos(pb_hwnd, Int);
		break;
	}
	case IDC_BUTTON3: {
		string str = intTOstr(getPos(pb_hwnd));
		char *p = (char*)str.data();
		alert(p, "");
		break;
	}
	case IDC_BUTTON4: {
		string str = intTOstr(getHignLimit(pb_hwnd));
		char *p = (char*)str.data();
		alert(p, "");
		break;
	}
	case IDC_BUTTON5: {
		string str = intTOstr(getLowLimit(pb_hwnd));
		char *p = (char*)str.data();
		alert(p, "");
		break;
	}

	}
}
void d3_wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){

}
void d3_wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
}
void d3_wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
}
void d3_wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
}
void d3_wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
}
void d3_wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
}
void d3_wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	PostQuitMessage(1);
}

LRESULT CALLBACK WndProc_d3(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {PostQuitMessage(0); break; }
	case WM_INITDIALOG: {d3_wm_create(hwnd, Message, wParam, lParam); break; }
	case WM_CONTEXTMENU: {d3_wm_contextMenu(hwnd, Message, wParam, lParam); break; }
	case WM_COMMAND: {d3_wm_command(hwnd, Message, wParam, lParam); break; }
	case WM_KEYDOWN: {d3_wm_keyDown(hwnd, Message, wParam, lParam); break; }
	case WM_CHAR: {d3_wm_char(hwnd, Message, wParam, lParam); break; }
				  //¿ÉÑ¡£º
				  //case WM_PAINT: {d3_wm_paint(hwnd, Message, wParam, lParam);break;}
				  case WM_CLOSE: {d3_wm_close(hwnd, Message, wParam, lParam);break;}

	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
void WINAPI PMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd) {
	dlg2.hinst(hInstance);
	dlg2.create(WndProc_d3, IDD_DIALOG3, win1.hwnd);
	return ;

}
