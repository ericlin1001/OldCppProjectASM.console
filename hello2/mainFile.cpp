#include<windows.h>
#include"resource.h"
char * g_szWindowClassName="abce";
char * g_szApplicationName="dfadf";
const int WINDOW_WIDTH=200;
const int WINDOW_HEIGHT=200;
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT msg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch(msg){
	case WM_CREATE:
		{
			MessageBox(NULL,"starting...","start",0);
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd,&ps);
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;

		}
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}
int WINAPI WinMain( HINSTANCE hInstace,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	HINSTANCE hInstance;
	HWND hWnd;
	MessageBox(0,"Hello World!","hellomsgbox",MB_ICONSTOP);
	WNDCLASSEX winclass;
	winclass.cbSize=sizeof(WNDCLASSEX);
	winclass.style=CS_HREDRAW|CS_VREDRAW;
	winclass.lpfnWndProc=WindowProc;
	winclass.cbClsExtra=0;
	winclass.cbWndExtra=0;
	winclass.hInstance=hInstance;
	winclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	winclass.hCursor=LoadCursor(NULL,"IDI_ARROW");
	winclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName=NULL;
	winclass.lpszClassName=g_szWindowClassName;
	winclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	if(!RegisterClassEx(&winclass)){
		MessageBox(NULL,"Class Registration Failed!","Error",0);
		return 0;
	}
	hWnd=CreateWindowEx(NULL,
						g_szWindowClassName,
						g_szApplicationName,
						WS_OVERLAPPEDWINDOW,
						0,
						0,
						WINDOW_WIDTH,
						WINDOW_HEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);
	ShowWindow(hWnd,nCmdShow);

	//

	UpdateWindow(hWnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//
	UnregisterClass(g_szWindowClassName,hInstance);
	return 0;
}