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
	case WM_SIZE: { //�������  case WM_CREATE ��ǰ��
		if (wParam != SIZE_MINIMIZED) {
			wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {//��������ʱ��Ӧ
		wm_create(hwnd, Message, wParam, lParam); break;
	}
	case WM_CONTEXTMENU:		//�һ���Ļʱ�������˵�
	{
		wm_contextMenu(hwnd, Message, wParam, lParam); break;
	}
	case WM_PAINT: {
		wm_paint(hwnd, Message, wParam, lParam); break;
	}
	case WM_COMMAND: {//��Ӧ�¼������еİ�ť��Ӧȫ���⡣
		wm_command(hwnd, Message, wParam, lParam); break;
	}
	case WM_KEYDOWN: {//��Ӧ���̰���
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

