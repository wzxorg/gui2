#include "main.h"

/*
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	//��������ΪWM_PAINT��׼��

	switch (Message) {

		
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE: { //�������  case WM_CREATE ��ǰ��
		if (wParam != SIZE_MINIMIZED) {

			//TODO:MoveWindow�Ⱥ��������⡣

		}
		break;
	}
	case WM_CREATE: {//��������ʱ��Ӧ

		break;
	}
	case WM_CONTEXTMENU:		//�һ���Ļʱ�������˵�
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		//TrackPopupMenu(g_hRKeyMenu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, hwnd, &rect);

		break;

	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		//TODO:�ڴ˷��ô���


		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_COMMAND: {//��Ӧ�¼������еİ�ť��Ӧȫ���⡣
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
	case WM_KEYDOWN: {//��Ӧ���̰���

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
	case WM_SIZE: { //�������  case WM_CREATE ��ǰ��
		if (wParam != SIZE_MINIMIZED) {
			//wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {//��������ʱ��Ӧ
		//wm_create(hwnd, Message, wParam, lParam);
		break;

	}
	case WM_CONTEXTMENU:		//�һ���Ļʱ�������˵�
	{
		//wm_contextMenu(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_PAINT: {
		//wm_paint(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_COMMAND: {//��Ӧ�¼������еİ�ť��Ӧȫ���⡣
		//wm_command(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_KEYDOWN: {//��Ӧ���̰���
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