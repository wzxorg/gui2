#include "func.h"
#include "main.h"
#include "resource.h"
HWND Htree = GetDlgItem(dlg2.hwnd, IDC_TREE1);
TextBox tt;
LRESULT CALLBACK dlg2_cb(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: {
		Htree = GetDlgItem(dlg2.hwnd, IDC_TREE1);
		tt.setHWND(GetDlgItem(hwnd, IDCD_EDIT1));
		break;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			PostQuitMessage(1);
			return TRUE;
			break;
		}


		switch (wParam)
		{
		case IDCD_BUTTON1: {
			TVITEM item;
			item.pszText = (LPSTR)"123";

			//alert("","");
			tagTVINSERTSTRUCTA tvitem1;
			tvitem1.hParent = NULL;
			tvitem1.hInsertAfter = TVI_ROOT;
			tvitem1.itemex.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM | TVIF_CHILDREN;
			tvitem1.itemex.pszText = (LPSTR)"123";

			HTREEITEM tvi1 = TreeView_InsertItem(GetDlgItem(hwnd, IDC_TREE1), &tvitem1);

			tagTVINSERTSTRUCTA tvitem2;
			tvitem2.hParent = tvi1;
			tvitem2.hInsertAfter = TVI_SORT;
			tvitem2.itemex.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_DI_SETITEM | TVIF_PARAM;
			tvitem2.itemex.pszText = (LPSTR)"456";
			TreeView_InsertItem(GetDlgItem(hwnd, IDC_TREE1), &tvitem2);

			break;//添加


		}
		case IDCD_BUTTON2: {
			//alert("","");
			//tt.setText("123");
			TVITEM itt;
			char temp[TableBoxMaxSting];

			HWND hTree = GetDlgItem(hwnd, IDC_TREE1);
			HTREEITEM Selected = TreeView_GetSelection(hTree);

			itt.hItem = Selected;
			itt.mask = TVIF_TEXT | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			itt.cchTextMax = TableBoxMaxSting;
			itt.pszText = temp;
			TreeView_GetItem(hTree, &itt);

			tt.setText(temp);//获取
			break;
		}
		case IDCD_BUTTON3: {
			HWND hTree = GetDlgItem(hwnd, IDC_TREE1);
			HTREEITEM hSelected = TreeView_GetSelection(hTree);

			TVITEM item;
			item.mask = TVIF_TEXT | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			item.pszText = tt.getText();
			item.hItem = hSelected;

			TreeView_SetItem(hTree, &item); //修改
			break;
		}
		case IDCD_BUTTON4: {

			HWND hTree = GetDlgItem(hwnd, IDC_TREE1);
			HTREEITEM hSelected = TreeView_GetSelection(hTree);
			if (hSelected == TVI_ROOT || hSelected == NULL)break;
			SendMessage(hTree, TVM_DELETEITEM, 0, (LPARAM)hSelected);//删除所选
			//TreeView_DeleteItem(hTree, hSelected);
			break;
		}
		case IDCD_BUTTON5: {

			HWND hTree = GetDlgItem(hwnd, IDC_TREE1);
			//HWND h树形标识符1 = GetDlgItem(hwnd, IDC_TREE1);
			SendMessage(hTree, TVM_DELETEITEM, 0, (LPARAM)NULL);//删除全部
			//TreeView_DeleteItem(hTree, hSelected);
			
			break;
		}
			

			break;
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
void WINAPI TreeMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd) {
	dlg2.hinst(hInstance);
	dlg2.create(dlg2_cb,IDD_DIALOG2,win1.hwnd);
}
