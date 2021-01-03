#include "func.h" 
Tray t1;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: {

		break;
	}
	case WM_TRAY:
		switch (lParam)
		{
			t1.showTrayMsg("");

		case WM_RBUTTONDOWN:
		{
			//获取鼠标坐标
			POINT pt; GetCursorPos(&pt);

			//解决在菜单外单击左键菜单不消失的问题
			SetForegroundWindow(hWnd);

			//使菜单某项变灰
			//EnableMenuItem(hMenu, ID_SHOW, MF_GRAYED);	

			//显示并获取选中的菜单
			int cmd = TrackPopupMenu(t1.hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hWnd,
				NULL);
			if (cmd == 1001)
				MessageBox(hWnd, APP_TIP, APP_NAME, MB_OK);
			if (cmd == 1002)
				PostMessage(hWnd, WM_DESTROY, NULL, NULL);
		}
		break;
		case WM_LBUTTONDOWN:
			MessageBox(hWnd, APP_TIP, APP_NAME, MB_OK);
			break;
		case WM_LBUTTONDBLCLK:
			break;
		}
		break;
	case WM_DESTROY:
		//窗口销毁时删除托盘
		Shell_NotifyIcon(NIM_DELETE, &t1.nid);
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		t1.showTrayMsg("");
		KillTimer(hWnd, wParam);
		break;
	}
	if (uMsg == WM_TASKBAR_CREATED)
	{
		//系统Explorer崩溃重启时，重新加载托盘
		Shell_NotifyIcon(NIM_ADD, &t1.nid);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/, int iCmdShow) {
	t1.addItem(1001,"a");
	t1.addItem(1002, "1002");
	t1.create(hInstance, WndProc, NULL, 1000, 101, iCmdShow);
	return 0;
}