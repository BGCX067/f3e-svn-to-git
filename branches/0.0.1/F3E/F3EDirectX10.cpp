#include "F3EDirectX10.h"

#include <d3d10.h>
#include <d3dx10.h>

F3EDirectX10::F3EDirectX10(void)
{

}

F3EDirectX10::~F3EDirectX10(void)
{
}

//
////--------------------------------------------------------------------------------------
//// Register class and create window
////--------------------------------------------------------------------------------------
//void F3EDirectX10::initWindow( HINSTANCE hInstance, int nCmdShow )
//{
//    // Register class
//    WNDCLASSEX wcex;
//    wcex.cbSize = sizeof( WNDCLASSEX );
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
//    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
//    wcex.lpszMenuName = NULL;
//    wcex.lpszClassName = L"TutorialWindowClass";
//    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    
//	if( !RegisterClassEx( &wcex ) )
//        return E_FAIL;
//
//    // Create window
//    g_hInst = hInstance;
//    RECT rc = { 0, 0, 640, 480 };
//    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
//    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 10 Tutorial 1: Direct3D 10 Basics", WS_OVERLAPPEDWINDOW,
//                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
//                           NULL );
//    if( !g_hWnd )
//        return E_FAIL;
//
//    ShowWindow( g_hWnd, nCmdShow );
//
//    return S_OK;
//}
//
//
////--------------------------------------------------------------------------------------
//// Called every time the application receives a message
////--------------------------------------------------------------------------------------
//LRESULT CALLBACK F3EDirectX10::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
//{
//    PAINTSTRUCT ps;
//    HDC hdc;
//
//    switch( message )
//    {
//        case WM_PAINT:
//            hdc = BeginPaint( hWnd, &ps );
//            EndPaint( hWnd, &ps );
//            break;
//
//        case WM_DESTROY:
//            PostQuitMessage( 0 );
//            break;
//
//        default:
//            return DefWindowProc( hWnd, message, wParam, lParam );
//    }
//
//    return 0;
//}
