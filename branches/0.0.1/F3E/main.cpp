
#define EXPORTDLL
#include "f3emain.h"

BOOL WINAPI DllMain( HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
		{
			case DLL_PROCESS_ATTACH:
				//startWindow(hDLL);
				
			break;

			case DLL_THREAD_ATTACH:
			break;

			case DLL_THREAD_DETACH:
			break;

			case DLL_PROCESS_DETACH:
			break;
		}


	return TRUE;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
			std::cout << "paint";
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int DLL start(F3EIApplication* app)
{
	//g_App = app;
	return wxEntry(0 /*hInstance*/);//, hPrevInstance, lpCmdLine, nCmdShow);
}

int DLL WindowSetup() {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = NULL;
    wincl.lpszClassName = "aaa";
    wincl.lpfnWndProc = WndProc;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl)) return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           "aaa",				/* Classname */
           "F3E Application Window",				/* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           NULL,//hThisInstance,/* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

		AllocConsole();
	SetConsoleTitle("Debug Window");
	HANDLE __hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD co = {300,300};
	SetConsoleScreenBufferSize(__hStdOut, co);


    ShowWindow (hwnd, SW_SHOW);

    /* Create Hook */
    //StartHook();

 //   while (GetMessage (&messages, NULL, 0, 0)) 
	//{
 //       TranslateMessage(&messages);
 //       DispatchMessage(&messages);
 //   }

	

	MSG msg = {0};
while (GetMessage(&msg, NULL, 0, 0))
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
	UpdateWindow((HWND)__hStdOut);
}

//    while( WM_QUIT != msg.message )
//    {
//        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
//        {
//            TranslateMessage( &msg );
//            DispatchMessage( &msg );
//        }
//        //else
//        //{
//        //    Render();
//      //  }
//    }
    return 0;//msg.wParam;
}

void WindowUpdate()
{
	//MSG msg = {0};
	//GetMessage(&msg, NULL, 0, 0);

 //   TranslateMessage(&msg);
 //   DispatchMessage(&msg);
}