// Lab2.2.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Lab2.2.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING]= _T("Title2");					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING] = _T("Windowclass2");
int flag1 = 0;
int flag2 = 0;
int mov = 0;
int vverh = 1;
int vniz = 0;
RECT clientRect;

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_LAB22, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB22));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB22));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB22);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_USER+1:
		{
			flag1 = 1;
			flag2 = 0;
			InvalidateRect(hWnd, 0, FALSE);
		}
		break;
	case WM_USER+2:
		{
			flag2 = 1;
			flag1 = 0;
			mov = 0;
			vverh = 1;
			vniz = 0;
			InvalidateRect(hWnd, 0, FALSE);
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ����� ��� ���������...
		if (flag1)
		{
			RECT WinCoord = {};
			GetClientRect(hWnd, &clientRect);
			Ellipse(hdc, clientRect.right/2 - 20, clientRect.bottom - 40, clientRect.right/2 +20, clientRect.bottom);
		}
		if (flag2)
		{
			RECT WinCoord = {};
			GetClientRect(hWnd, &clientRect);
			if (vverh)
			{
				Ellipse(hdc, clientRect.right/2 - 20, clientRect.bottom - 40 - mov, clientRect.right/2 +20, clientRect.bottom - mov);
				Sleep (1);
				InvalidateRect(hWnd, 0 , TRUE);
				mov++;
				if ( clientRect.bottom - 40 - mov== -1)
				{
					vverh = 0;
					vniz = 1;
					mov--;
				}
			}
			if (vniz)
			{
				Ellipse(hdc, clientRect.right/2 - 20, clientRect.bottom - 40 - mov, clientRect.right/2 +20, clientRect.bottom - mov);
				Sleep (1);
				InvalidateRect(hWnd, 0 , TRUE);
				mov--;
				if ( mov == -1)
				{
					vverh = 1;
					vniz = 0;
					mov++;
				}
			}
		}
		//RECT WinCoord = {}; //������ ��������� ���� 
		//	GetWindowRect(hWnd, &WinCoord); //����� ����������
		//	Ellipse(hdc, WinCoord.left/2-100 , WinCoord.bottom/2-100, WinCoord.right/2 -100, WinCoord.bottom/2-100 );
		//	Ellipse(hdc, WinCoord.right - 200, WinCoord.bottom-100, WinCoord.right-300, WinCoord.bottom - 200);
		//	RECT WinCoord = {}; //������ ��������� ���� 
		//	GetWindowRect(hWnd, &WinCoord); //����� ����������
			//Ellipse(hdc, WinCoord.right + right, WinCoord.bottom-100, WinCoord.right+right-100, WinCoord.bottom - 200);
		//	Ellipse(hdc, left, top, right, bottom);
		//	Ellipse(hdc, WinCoord.right - 200, 20, WinCoord.right-300, 120);
		//	right -= 1;
		//	Sleep(500);
		//	InvalidateRect(hWnd, 0 , TRUE);

		EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
