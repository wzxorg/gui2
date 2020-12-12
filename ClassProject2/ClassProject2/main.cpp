#include "func.h"

Window_ win1;
TextBox t1;
BorderText t2;
SimpleText t3;
Button b1[10];
Label l1;
void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);



void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	win1.alert(win1.getText(), "");
	char dest[MAX_STRING_SIZE] = "";
	char* txt = win1.getText();
	//alert(txt,"");
	strcat(dest, txt);
	strcat(dest, "+");
	win1.setText(dest);
}
void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	//alert("", "");
	t1.create("", 1001, hwnd);
	b1[0].create("0", 2000, hwnd);
	b1[1].create("1",2001,hwnd);
	b1[2].create("2", 2002, hwnd);
	b1[3].create("3", 2003, hwnd);
	b1[4].create("4", 2004, hwnd);
	b1[5].create("5", 2005, hwnd);
	b1[6].create("6", 2006, hwnd);
	l1.create("", 1002, hwnd);
}
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	t1.setLocation(0, 0, 100, 50);
	b1[0].setLocation(110, 0, 50, 30);
	b1[1].setLocation(200,0,50,30);
	b1[2].setLocation(250,0,50,30);
	l1.setLocation(60, 0, 100, 50);
}
void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (wParam)
	{
		//list an example
		
	case 2001: {
		win1.alert(t1.getText(), "");
		break;
	}
	case 2000: {
		t1.setText("");
		break;
	}
	case 2002: {
		
	}
	default: {

		break;
	}
	}
}
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}

void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE: { //�������  case WM_CREATE ��ǰ��
		if (wParam != SIZE_MINIMIZED) {
			wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {//��������ʱ��Ӧ
		wm_create(hwnd, Message, wParam, lParam);
		break;

	}
	case WM_CONTEXTMENU:		//�һ���Ļʱ�������˵�
	{
		wm_contextMenu(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_COMMAND: {//��Ӧ�¼������еİ�ť��Ӧȫ���⡣
		wm_command(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_KEYDOWN: {//��Ӧ���̰���
		
		wm_keyDown(hwnd, Message, wParam, lParam);
		break;
	}
	case WM_CHAR: {
		wm_char(hwnd, Message, wParam, lParam);
		break;
	}
	//case WM_PAINT: {wm_paint(hwnd, Message, wParam, lParam);break;}
	//case WM_CLOSE: {wm_close(hwnd, Message, wParam, lParam);break;}
	
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	win1.histance_(hInstance);
	win1.callback_(WndProc);
	///alert("", "");
	win1.create_wind(640, 480);
	return 0;
}