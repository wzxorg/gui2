#pragma once
/**/
#pragma comment(linker,"\"/manifestdependency:type='win32' "\
						"name='Microsoft.Windows.Common-Controls' "\
						"version='6.0.0.0' processorArchitecture='*' "\
						"publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <thread>
#include "func.h"

void WINAPI LvMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd);
void WINAPI TreeMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd);
void WINAPI PMain(HINSTANCE hInstance, LPSTR lpCmdLine, int nShowCmd);

static HINSTANCE all_hins=NULL;
static LPSTR all_lpCmdLine = NULL;
static int all_nShowCmd = NULL;
static Window win1;
static Dialog dlg2;
