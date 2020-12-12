#pragma once
#include "func1.h"
/*
class CallBackProcFunc {
public:
	//bool create(int width, int height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

};
LRESULT CALLBACK CallBackProcFunc::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {
		PostQuitMessage(0); break;
	}
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {
			wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {//创建窗口时响应
		wm_create(hwnd, Message, wParam, lParam); break;
	}
	case WM_CONTEXTMENU:		//右击屏幕时，弹出菜单
	{
		wm_contextMenu(hwnd, Message, wParam, lParam); break;
	}
	case WM_PAINT: {
		wm_paint(hwnd, Message, wParam, lParam); break;
	}
	case WM_COMMAND: {//相应事件，所有的按钮响应全在这。
		wm_command(hwnd, Message, wParam, lParam); break;
	}
	case WM_KEYDOWN: {//响应键盘按下
		wm_keyDown(hwnd, Message, wParam, lParam); break;
	}
	case WM_CHAR: {
		wm_char(hwnd, Message, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
void CallBackProcFunc::wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void CallBackProcFunc::wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
}
void CallBackProcFunc::wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
}
void CallBackProcFunc::wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void CallBackProcFunc::wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void CallBackProcFunc::wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void CallBackProcFunc::wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void CallBackProcFunc::wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
*/
void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

