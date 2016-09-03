// 2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Setting(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	 
//
	/*
		SetCursorPos()
		ClientToScreen(hWnd,point);
		ScreenToClient();
		*/
	//ShowCursor(false);
//	ClipCursor(rect);
//	ClipCursor(NULL);
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MY2);
	/*HCURSOR hcur=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	SetCursor(hcur);*/
	
	// Main message loop:
	bool bDone=false;
	while(!bDone){
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			if(msg.message==WM_QUIT){
				bDone=true;
				break;
			}else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		InvalidateRect(msg.hwnd,NULL,true);
		UpdateWindow(msg.hwnd);
	}
	VK_SPACE 
	MessageBox(NULL,"EXIT","",0);
	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MY2);
	wcex.hCursor		= LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);//NULL;
	wcex.lpszMenuName	= (LPCSTR)IDC_MY2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd=NULL;

   hInst = hInstance; // Store instance handle in our global variable
MessageBox(hWnd,"init0","",0);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
MessageBox(hWnd,"init1","",0);
   if (!hWnd)
   {
      return FALSE;
   }
	MessageBox(hWnd,"init2","",0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
//
  MessageBox(hWnd,"init3","",0);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
#include<time.h>
//#include<util.h>
//#include<utils.h>
//#include<CTimer.h>
int RandInt(int min,int max){
	return rand()%(max-min+1)+min;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//	itos(1);
	HINSTANCE hInstance;
	//
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	//
	static HPEN pen=CreatePen(PS_DOT,1,RGB(0,0,255));//blue
	static HPEN oldPen;
	static HBRUSH brush =CreateHatchBrush(HS_CROSS,RGB(0,100,100));
	static HBRUSH oldBrush; 
	//
	static const int iv=6;
	static POINT points[iv];
	static int cx;
	static int cy;
	int i=0;
	//
	HDC hdcBuffer;
	HBITMAP hBitmap;
	HBITMAP oldBitmap;
	//SetCursorPos(50,50);
	
	switch (message) 
	{
		
		
		case WM_LBUTTONDOWN:
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_SETTING:
					DialogBox(hInst,(LPCTSTR)IDD_Setting,hWnd,(DLGPROC)Setting);
					break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case IDSAVEA:
					MessageBox(hWnd,"a","save a",0);
					break;
				case IDSAVEB:
						MessageBox(hWnd,"b","save b",0);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
			case WM_SETCURSOR:
				//MessageBox(hWnd,"changeCurosr","",0);
				HCURSOR hcur;
				hcur=LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURSOR1));
				SetCursor(hcur);
				break;
			case WM_CREATE:
				
				//
				//SetCapture(hWnd);
				hInstance=((LPCREATESTRUCT)(lParam))->hInstance;
				//
				RECT rect;
				GetClientRect(hWnd,&rect);
				cx=rect.right;
				cy=rect.bottom;
				//
				 hdcBuffer=CreateCompatibleDC(NULL);
				 hdc=GetDC(hWnd);
				 hBitmap=CreateCompatibleBitmap(hdc,cx,cy);
				 oldBitmap=(HBITMAP)SelectObject(hdcBuffer,hBitmap);
				 ReleaseDC(hWnd,hdc);
				 //
				 SendMessage(hWnd,WM_KEYDOWN,VK_SPACE,lParam);
				 //
				 
				 MessageBox(hWnd,"create","",0);
				
				break;
			case WM_SIZE:
				cx=LOWORD(lParam);
				cy=HIWORD(lParam);
				//
				SelectObject(hdcBuffer,oldBitmap);
				DeleteObject(hBitmap);
				hdc=GetDC(hWnd);
				hBitmap=CreateCompatibleBitmap(hdc,cx,cy);
				oldBitmap=(HBITMAP)SelectObject(hdcBuffer,hBitmap);
				ReleaseDC(hWnd,hdc);
				//
			//	SendMessage(hWnd,WM_KEYDOWN,VK_SPACE,lParam);
				break;
			case WM_KEYDOWN:
				switch(wParam){
				case VK_SPACE:
			/*	for(i=0;i<iv;i++){
					points[i].x=RandInt(0,cx);
					points[i].y=RandInt(0,cy);
				}*/
					break;
				}
				break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//set graphics
			BitBlt(hdcBuffer,0,0,cx,cy,NULL,NULL,NULL,WHITENESS);
			//begin paint:
			oldPen=(HPEN)SelectObject(hdcBuffer,pen);
			oldBrush=(HBRUSH)SelectObject(hdcBuffer,brush);
			
			/**/
			for(i=0;i<iv;i++){
				char t[1];
				t[0]=(char)(i+49);
					TextOut(hdcBuffer,points[i].x,points[i].y,t,1);
			}
			Polygon(hdcBuffer,points,iv);
			/*Rectangle(hdcBuffer,0,0,cx,cy);*/
			BitBlt(hdc,0,0,cx,cy,hdcBuffer,0,0,SRCCOPY);
			SelectObject(hdcBuffer,oldBrush);
			SelectObject(hdcBuffer,oldPen);
			
			//
		/*	RECT rt;
			GetClientRect(hWnd, &rt);
			char buffer[10];
			strcpy(buffer,"buffer");
			Rectangle(hdc,10,10,200,200);
			SetTextColor(hdc,RGB(255,0,0));
			//SetBkColor(hdc,RGB(0,255,0));
			//SetBkMode(hdc,TRANSPARENT);
			TextOut(hdc,20,20,buffer,6);*/
			//end paint.
			
			EndPaint(hWnd, &ps);
		//	Sleep(500);
			break;
		case WM_DESTROY:
			SelectObject(hdcBuffer,oldBitmap);
			DeleteDC(hdcBuffer);
			DeleteObject(hBitmap);
			//
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
LRESULT CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		/**/case WM_INITDIALOG:
				return TRUE;
	
		case WM_COMMAND:
			switch(LOWORD(wParam)){
			case IDOK:
				break;
			case IDCANCEL:
				break;
			case ID_SETTING_SAVE:
				break;
			}
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}