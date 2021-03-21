#include "main.h"
#include "func.h"
#include "resource.h"
#include "extstr.h"
//#include "resource.h"
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
childMenu cm4;
TreeBox treeb1;
childMenu cm5;
ProgressBar pb1;
childMenu cm6;
CheckBox ch1;
childMenu cm7;
CheckBox3 ch2;
childMenu cm8;
childMenu cm9;
MDIClient mdi1;
HINSTANCE mdiHins;
StatusBar st1;
ToolBar tool1;
void wm_create(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_command(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_char(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_keyDown(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void wm_notify(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);


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
	b1[1].create("1", 2001, hwnd);
	b1[2].create("2", 2002, hwnd);
	b1[3].create("3", 2003, hwnd);
	b1[4].create("4", 2004, hwnd);
	b1[5].create("5", 2005, hwnd);
	b1[6].create("6", 2006, hwnd);
	l1.create("", 1002, hwnd);
	m1.addItem(3001, "Change Icon I");
	m1.addItem(3002, "Reset the icon");
	m1.addItem(3003, "change image");
	m1.addItem(3101, "Enable");
	m1.addItem(3102, "disable");

	cm1.create(top1.h_menu, "ListBox");
	cm1.addItem(3004, "Add 123");
	cm1.addItem(3005, "Add");
	cm2.create(top1.h_menu, "IO");
	cm2.addItem(3006, "SaveFile");
	cm3.create(top1.h_menu, "Tablebox");
	cm3.addItem(3007, "Add Colume");
	cm3.addItem(3008, "Add Item");
	cm3.addItem(3009, "Get Index");
	cm3.addItem(3010, "Clear");
	cm3.addItem(3011, "Count");
	cm3.addItem(3012, "Delete");
	cm3.addItem(3013, "getRow");
	cm3.addItem(3014, "setText");
	cm3.addItem(3015, "GetSelCount");
	cm3.addItem(3016, "SelIf");
	//cm3.addItem(3017, "Inset");

	cm4.create(top1.h_menu, "Thread");
	cm4.addItem(3017, "Show lv.cpp");
	cm4.addItem(3018, "SHow tree.cpp");
	

	cm5.create(top1.h_menu, "TreeView");
	cm5.addItem(3019, "Add");
	cm5.addItem(3020, "Set");
	cm5.addItem(3021, "Delete");
	cm5.addItem(3022, "Get");

	cm4.addItem(3023, "Show progress.cpp");

	cm6.create(top1.h_menu, "Progress Bar");
	cm6.addItem(3024,"Begin");
	cm6.addItem(3025,"Get Range");
	cm7.create(top1.h_menu, "Check Box");
	cm7.addItem(3026, "CheckIf");
	cm7.addItem(3027, "Checked");
	cm7.addItem(3028, "Uncheck");
	cm7.addItem(3029, "IndeterminateIF");
	cm7.addItem(3030, "Indeterminate");
	cm7.addItem(3031, "getState");

	cm3.addItem(4001, "delete all including col");
	cm3.addItem(4002, "get colname");
	cm3.addItem(4003, "get count");

	cm9.create(top1.h_menu, "MDI");
	cm9.addItem(4004, "create");
	top1.show(hwnd);


	list1.create(4001, hwnd);

	ta1.create(1003, hwnd);
	treeb1.create(1004, hwnd);
	pb1.create(1005, hwnd);

	ch1.create(1006,hwnd);
	ch1.setText("123");
	ch2.create(1007, hwnd);
	ch2.setText("456");

	
	mdi1.create(4777, hwnd,all_hins,50000,NULL);
	st1.create(4778, hwnd);
	int widths[] = {100,200,100};
	st1.setParts(widths, 3);
	st1.setText(1, "1123");
	char * str = st1.getText(1);
	//alert(str, "");
	st1.setText(0, str);
	//HICON hIcon = LoadIcon(win1.his, MAKEINTRESOURCE(IDI_ICON1));
	//SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	//win1.setIcon(MAKEINTRESOURCE(IDI_ICON1));
	tool1.create(4779,hwnd);
	tool1.addStdBitmap();
	TBBUTTON tbb[2];
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = 11001;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = 11002;
	tool1.addButtons(tbb,2);

	//自定义图标
	int bitmapSize = 20;
	HBITMAP bitmap = (HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, bitmapSize, bitmapSize, NULL);
	HIMAGELIST hImageList=ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
		ILC_COLOR24 | ILC_MASK,   // Ensures transparent background.
		1, 0);
	ImageList_Add(hImageList, bitmap, 0);
	ImageList_Add(hImageList, bitmap, 0);

	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = 11001;

	tbb[1].iBitmap = 1;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = 11002;

	tool1.addBitmapList(0, hImageList);
	tool1.addButtons(tbb, 2);
}
void wm_size(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	t1.setLocation(0, 30, 100, 120);
	b1[0].setLocation(110, 30, 50, 30);
	b1[1].setLocation(200, 30, 50, 30);
	b1[2].setLocation(250, 30, 50, 30);
	b1[3].setLocation(300, 30, 50, 30);
	b1[5].setLocation(350, 30, 50, 30);
	l1.setLocation(0, 150, 100, 40);
	list1.setLocation(0, 200, 200, 200);
	b1[4].setLocation(200, 200, 50, 30);
	ta1.setLocation(300, 60, 250, 150);
	treeb1.setLocation(300, 250, 250, 150);
	pb1.setLocation(300, 410, 250, 40);
	ch1.setLocation(300, 450, 250, 20);
	
	ch2.setLocation(300, 480, 250, 20);
	mdi1.setLocation(600, 30, 350, 500);
	st1.setLocation(0, WindowHeight-30, 500, 30);
	tool1.setLocation(0, 600, 100, 20);
	//MoveWindow(mdi1.getHwnd(), 600, 0,350 ,400, TRUE);
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
		t1.setText(readFile_char(CHAR_ToLPSTR(gfn(hwnd,gfn_textFileA,gfn_richTextFileEx))));
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
		t1.setText(list1.getItemText(list1.getIndex(), 260));
		break;
	}
	case 2005: {
		string str = intTOstr(123);
		char *p = (char*)str.data();
		alert(p,"");
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
		SaveFile_char(t1.getText(), gfn_save(hwnd,gfn_textFileA,gfn_textFileEx));
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
		ta1.setColume(cols, 3);
		break;
	}
	case 3008: {
		UI_Lvitem item;
		item.subItem[0].value = "0";
		item.subItem[1].value = "Tom";
		item.subItem[2].value = "America";
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
		t1.setText(ta1.getItemText(ta1.getIndex(), 2));
		break;
	}
	case 3014: {
		ta1.setItemText(ta1.getIndex(), 1, t1.getText());
		break;
	}
	case 3015: {
		cout << ta1.getSelCount();
		break;
	}
	case 3016: {
		//cout << "||" << ta1.getSelIf(0) << "|" << ta1.getSelIf(1) << "|" << ta1.getSelIf(2) << "||";
		cout << "项";
		for (int i = 0; i < ta1.getCount(); i++)if (ta1.getSelIf(i))cout << i << ",";
		cout << "被选中";
		break;
	}
	case 3017: {
		thread task1(LvMain, all_hins, all_lpCmdLine, all_nShowCmd);
		task1.detach();
		break;
	}
	case 3018: {
		thread task2(TreeMain, all_hins, all_lpCmdLine, all_nShowCmd);
		task2.detach();
		break;
	}
	case 3019: {

		treeb1.add(treeb1.getSelItem(), t1.getText());
		break;
	}
	case 3020: {
		treeb1.setItemText(treeb1.getSelItem(),t1.getText());
		break;
	}
	case 3021: {
		treeb1.removeItem(treeb1.getSelItem());
		break;
	}
	case 3022: {
		t1.setText(treeb1.getItemText(treeb1.getSelItem()));
		break;
	}
	case 3023: {
		thread task3(PMain, all_hins, all_lpCmdLine, all_nShowCmd);
		task3.detach();
		break;
	}
	case 3024: {
		pb1.setRange(1000);
		for (int i = 0; i < 1001;i=i+50) {
			Sleep(1000);
			pb1.setPos(i);
			string str = intTOstr(pb1.getPos());
			char *p = (char*)str.data();
			t1.setText(p);
		};
		alert("Done","");
		break;
	}
	case 3025: {
		string str = intTOstr(pb1.getHighLimit());
		char *p = (char*)str.data();
		alert(p,"");
		str = intTOstr(pb1.getLowLimit());
		p = (char*)str.data();
		alert(p, "");
		break;
	}
	case 3026: {
		if (ch1.getCheckIf())alert("1","");
		else alert("0","");
		break;
	}
	case 3027: {
		ch1.setCheck();
		break;
	}
	case 3028: {
		ch1.setUnchecked();
		break;
	}
	case 3029: {
		if (ch2.getIndeterminateIf())alert("1", "");
		else alert("0", "");
		break;
	}
	case 3030: {
		ch2.setIndeterminate();
		break;
	}
	case 3031: {
		string str = intTOstr(ch2.getState());
		char *p = (char*)str.data();
		alert(p, "");
		break;
	}
	case 3101: {
		EnableWindow(t1.getHwnd(), true);
		
		break;
	}
	case 3102: {
		EnableWindow(t1.getHwnd(), false);

		break;
	}
	case 4001: {
		ta1.clearAll();
		break;
	}
	case 4002: {
		alert(ta1.getColumeText(0), "");
		alert(ta1.getColumeText(1), "");
		alert(ta1.getColumeText(2), "");
		break;
	}
	case 4003: {
		int c = ta1.getColCount();
		String strC = intTOstr(c);
		char*p = (char*)strC.data();
		alert(p, "");
		
		break;
	}
	case 4004: {
		mdi1.createChildWindow(all_hins, "childClass1", "Form1");
		break;
	}
	case 11001: {
		alert("toolbar0","");
		break;
	}
	default: {
		if (LOWORD(wParam) >= 50000) {
			DefFrameProc(hwnd, mdi1.getHwnd(), Message, wParam, lParam);
		}
		else {
			HWND hChild;
			hChild = (HWND)SendMessage(mdi1.getHwnd(), WM_MDIGETACTIVE, 0, 0);
			if (hChild) {
				SendMessage(hChild, WM_COMMAND, wParam, lParam);
			}
		}
	}

	}
}
void wm_rtClick(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}

void wm_contextMenu(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	m1.showRectMenu(hwnd, lParam);
}
void wm_paint(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_close(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

}
void wm_notify(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	/*
	if ((int)wParam!=1003)return;//10482432
	if ((int)lParam ==  10482432)return;//19919824
	if ((int)lParam == 19919824)return;//3732800
	if ((int)lParam == 3732800)return;//9695280
	if ((int)lParam == 9695280)return;//11792400
	if ((int)lParam == 11792400)return;//
	if ((int)lParam == 12448128)return;//
	if ((int)lParam == 7336800)return;//
	if ((int)lParam == 11530912)return;//
	if ((int)lParam == 13627328)return;//
	if ((int)lParam == 5239672)return;//
	if ((int)lParam == 18084168)return;//
	if ((int)lParam == 17822832)return;//
	if ((int)lParam == 2093968)return;//
	if ((int)lParam == 9434584)return;//
	if ((int)lParam == 17823328)return;//
	if ((int)lParam == 1700136)return;//
	if ((int)lParam == 11530008)return;//
	if ((int)lParam == 5238728)return;//
	if ((int)lParam == 7336672)return;//
	if ((int)lParam == 14480792)return;//
	if ((int)lParam == 14872752)return;//
	if ((int)lParam == 7336112)return;//
	if ((int)lParam == 14087560)return;//
	bool doIt=false;
	if ((int)lParam == 5500976)doIt = true;
	//if(doIt == true){
	String wp = intTOstr(wParam);
	char* p = (char*)wp.data();
	//alert(p,"");
	String lp = intTOstr(lParam);
	char*p1 = (char*)lp.data();
	//alert(p1,"");
	String str;
	str = t1.getText();
	str += "\r\n";
	str += wp;
	str += "||";
	str += lp;
	char* p3 = (char*)str.data();
	t1.setText(p3);
	//}
	*/
	//
	NM_LISTVIEW* pnmv = (NM_LISTVIEW FAR *) lParam;
	if (pnmv->hdr.code == LVN_COLUMNCLICK)t1.setText("1");//点击了列。表头

	if (pnmv->hdr.code == LVN_ITEMACTIVATE)t1.setText("2");//激活列表里的某一项，也就是行，双击鼠标左键。

	if (pnmv->hdr.code == NM_CLICK)t1.setText("3");//单击列表里的某一项，
				
}


LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: {
		char szFileName[MAX_PATH];
		HWND hEdit,H1;
		
		hEdit = CreateWindowEx(/*WS_EX_CLIENTEDGE*/ NULL, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd, (HMENU)1001, NULL/*all_hins*/, NULL);

		SendMessage(hEdit, WM_SETFONT,
			(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
		
		H1 = createTextBox("", 1002, hwnd);
		set_Win_Text(H1 , "123");

		break;
	}
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
			MoveWindow(GetDlgItem(hwnd, 1001), 0, 0, LOWORD(lParam), HIWORD(lParam)/2, TRUE);
		setWinLocation(UIgetDlgItem(1002),0, WindowHeight / 2, WindowWidth, WindowHeight / 2);
		break;
	case WM_MDIACTIVATE: {
		bool EnableFlag;
		if (hwnd == (HWND)lParam) {      //being activated
			EnableFlag = TRUE;
		}
		else {
			EnableFlag = FALSE;    //being de-activated
		}
		if (EnableFlag) {
			st1.setText(0, get_Win_Text(hwnd));
		}
		//DrawMenuBar(g_hMainWindow);

		break;
	}
	case WM_SETFOCUS:
		//SetFocus(GetDlgItem(hwnd, 1001));
		SetFocus(UIgetDlgItem(1001));
		break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {


		}
		return 0;
	}
	}
	return DefMDIChildProc(hwnd, Message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {
	case WM_DESTROY: {PostQuitMessage(0); break; }
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {
			wm_size(hwnd, Message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE: {wm_create(hwnd, Message, wParam, lParam); break; }
	case WM_CONTEXTMENU: {wm_contextMenu(hwnd, Message, wParam, lParam); break; }
	case WM_COMMAND: {wm_command(hwnd, Message, wParam, lParam); break; }
	case WM_KEYDOWN: {wm_keyDown(hwnd, Message, wParam, lParam); break; }
	case WM_CHAR: {wm_char(hwnd, Message, wParam, lParam); break; }
				  //可选：
				  //case WM_PAINT: {wm_paint(hwnd, Message, wParam, lParam);break;}
				  //case WM_CLOSE: {wm_close(hwnd, Message, wParam, lParam);break;}
				  case WM_NOTIFY: {wm_notify(hwnd, Message, wParam, lParam);break;}

	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain/* main*/(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	InitCommonControls();
	win1.histance_(hInstance);
	win1.callback_(WndProc);
	win1.wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	win1.wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	
	MdiChildWindowClass wch1;
	wch1.registerWindowClass(hInstance, MDIChildWndProc, "childClass1");

	all_hins = hInstance;
	all_lpCmdLine = lpCmdLine;
	all_nShowCmd = nCmdShow;

	mdiHins = hInstance;

	win1.create_wind(1000, 700);
	return 0;
}
