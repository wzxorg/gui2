#include "main.h"

/*
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	//以上两行为WM_PAINT做准备

	switch (Message) {

		
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {

			//TODO:MoveWindow等函数放在这。

		}
		break;
	}
	case WM_CREATE: {//创建窗口时响应

		break;
	}
	case WM_CONTEXTMENU:		//右击屏幕时，弹出菜单
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		//TrackPopupMenu(g_hRKeyMenu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, hwnd, &rect);

		break;

	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		//TODO:在此放置代码


		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_COMMAND: {//相应事件，所有的按钮响应全在这。
		switch (wParam)
		{
			//list an example
		case 1001: {

			break;
		}
		default: {

			break;
		}
		}
		break;
	}
	case WM_KEYDOWN: {//响应键盘按下

		break;
	}
					
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
*/
//CallBackProcFunc callBk1;
window_ win1;


void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
}
void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
}
void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	alert("", "");
}
void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {
			//wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {//创建窗口时响应
		//wm_create(hwnd, Message, wParam, lParam);
		break;

	}
	case WM_CONTEXTMENU:		//右击屏幕时，弹出菜单
	{
		//wm_contextMenu(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_PAINT: {
		//wm_paint(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_COMMAND: {//相应事件，所有的按钮响应全在这。
		//wm_command(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_KEYDOWN: {//响应键盘按下
		alert("", "");
		//wm_keyDown(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_CHAR: {
		//wm_char(hwnd, Message, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	win1.histance_(hInstance);
	win1.callback_(WndProc);
	///alert("", "");
	win1.create_wind(640, 480);
	return 0;
}
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	
	return 0;
}