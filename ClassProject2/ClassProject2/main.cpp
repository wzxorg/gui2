#include "main.h"
#include "resource.h"
Window_ win1;
TextBox t1;
BorderText t2;
SimpleText t3;
Button b1[10];
Label l1;
RtMenu m1;
RtMenu m2;
ListBox list1;
Topmenu top1;
childMenu cm1;
childMenu cm2;
TableBox ta1;
childMenu cm3;
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
	m1.addItem(3001, "Change Icon I");
	m1.addItem(3002,"Reset the icon");
	m1.addItem(3003, "change image");
	
	cm1.create(top1.h_menu, "ListBox");
	cm1.addItem(3004,"Add 123");
	cm1.addItem(3005, "Add");
	cm2.create(top1.h_menu,"IO");
	cm2.addItem(3006, "SaveFile");
	cm3.create(top1.h_menu, "Tablebox");
	cm3.addItem(3007,"Add Colume");
	cm3.addItem(3008,"Add Item");
	cm3.addItem(3009, "Get Index");
	cm3.addItem(3010, "Clear");
	cm3.addItem(3011, "Count");
	cm3.addItem(3012, "Delete");
	cm3.addItem(3013, "getRow");
	cm3.addItem(3014, "setText");
	top1.show(hwnd);


	list1.create(4001,hwnd);

	ta1.create(1003, hwnd);

	//HICON hIcon = LoadIcon(win1.his, MAKEINTRESOURCE(IDI_ICON1));
	//SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	//win1.setIcon(MAKEINTRESOURCE(IDI_ICON1));
	
}
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	t1.setLocation(0, 0, 100, 50);
	b1[0].setLocation(110, 0, 50, 30);
	b1[1].setLocation(200,0,50,30);
	b1[2].setLocation(250,0,50,30);
	b1[3].setLocation(300, 0, 50, 30);
	l1.setLocation(0, 60, 100, 100);
	list1.setLocation(0, 200, 200, 200);
	b1[4].setLocation(200, 200, 50, 30);
	ta1.setLocation(300,60,250,150);
	
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
		l1.setText(t1.getText());
		break;
	}
	case 2003: {
		t1.setText(readFile_char(CHAR_ToLPSTR(childGetFileNmae_char(hwnd))));
		break;
	}
	case 3001: {
		setWinIcon(NULL, hwnd, MAKEINTRESOURCE(IDI_ICON1));
		break;
	}
	case 3002: {
		setWinIcon(win1.his, hwnd, MAKEINTRESOURCE(IDI_ICON1));
		break;
	}
	case 3003: {
		setImage(win1.his, b1[0].getHwnd(), MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	}
	case 2004: {
		t1.setText(list1.getItemText(list1.getIndex(),260));
		break;
	}
	case 3004: {
		list1.add("123");
		break;
	}
	case 3005: {
		list1.add(t1.getText());
		break;
	}
	case 3006: {
		//alert(gfn_save(hwnd),"");
		//alert(gfn1_child(hwnd), "");
		SaveFile_char(t1.getText(), gfn_save(hwnd));
		break;
	}
	case 3007: {
		char* str = t1.getText();
		UI_LvPop cols;
		cols.cols[0].value = t1.getText();
		cols.cols[0].size = strlen(str) * 10;
		cols.cols[1].value = "Name";
		cols.cols[1].size = 60;
		cols.cols[2].value = "Class";
		cols.cols[2].size = 70;
		ta1.setColume(cols,3);
		break;
	}
	case 3008: {
		UI_Lvitem item;
		item.subItem[0].value = "0";
		item.subItem[1].value = "Adolf";
		item.subItem[2].value = "Germany";
		ta1.addItem(item, 3);
		break;
	}
	case 3009: {
		cout << ta1.getIndex();
		break;
	}
	case 3010: {
		ta1.clear();
		break;
	}
	case 3011: {
		cout << ta1.getCount();
		break;
	}
	case 3012: {
		ta1.removeItem(ta1.getIndex());
		break;
	}
	case 3013: {
		cout << ta1.getItemText(ta1.getIndex(), 0);
		cout << ta1.getItemText(ta1.getIndex(), 1);
		cout << ta1.getItemText(ta1.getIndex(), 2);
	}
	case 3014: {
		ta1.setItemText(ta1.getIndex(), 1, t1.getText());
		break;
	}
	default: {

		break;
	}
	}
}
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}

void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	m1.showRectMenu(hwnd,lParam);
}
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {PostQuitMessage(0);break;}
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {
			wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE:			{wm_create(hwnd, Message, wParam, lParam);break;}
	case WM_CONTEXTMENU:	{wm_contextMenu(hwnd, Message, wParam, lParam);break;}
	case WM_COMMAND:		{wm_command(hwnd, Message, wParam, lParam);break;}
	case WM_KEYDOWN:		{wm_keyDown(hwnd, Message, wParam, lParam);break;}
	case WM_CHAR:			{wm_char(hwnd, Message, wParam, lParam); break; }
	//可选：
	//case WM_PAINT: {wm_paint(hwnd, Message, wParam, lParam);break;}
	//case WM_CLOSE: {wm_close(hwnd, Message, wParam, lParam);break;}
	
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
int /*WINAPI WinMain */main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	InitCommonControls();
	win1.histance_(hInstance);
	win1.callback_(WndProc);
	win1.wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	win1.wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//win1.wc.style = CS_HREDRAW | CS_VREDRAW;
	///alert("", "");
	win1.create_wind(640, 480);
	return 0;
}