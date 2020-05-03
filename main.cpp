#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
RECT clientRect;//структура размера клиентского окна
	int flagSun = 1;
	int flagNight = 0;
	int flagStars = 0;
	const int nstar = 750;
	int star [nstar][2];


int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{ 
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	srand(time(NULL));
	for (int i = 0; i<nstar-1; i++)
	{
		star[i][1] = rand()%1920;
		star[i][2] = rand()%1080;
	}

	// Определение класса окна 
	wc.hInstance = This; 
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); 	// Заполнение окна белым цветом 


// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0; 	

// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
	_T("Звездочки"), 		// Заголовок окна 
	WS_OVERLAPPEDWINDOW, 		// Стиль окна 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 Размеры окна 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
	HWND_DESKTOP, 				// Дескриптор родительского окна 
	NULL, 						// Нет меню 
	This, 						// Дескриптор приложения 
	NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	} 

	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 

	//HDC hdc; 
	//hdc = GetDC(hWnd); 

	switch(message)		 // Обработчик сообщений
	{ 
		case WM_CREATE:
			/*MessageBox(hWnd, L"Здравствуйте, Мария Владимировна\nЯ сделяль", L"Лаба 1", MB_ICONINFORMATION);
			break;*/
			{
				   /* HBRUSH ColorOfFon = CreateSolidBrush(RGB(0,0,255));
					SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)ColorOfFon);*/
			}
			break;
		case WM_PAINT:
			{

					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hWnd, &ps);//дескрипотр контекста устройства, подготавливает окно для рисования и заполняет PAINTSTRUCT
					GetClientRect(hWnd, &clientRect);//загружаем текущие размеры окна


					if ((flagSun == 1) && (flagNight == 0) && (flagStars == 0))
					{
					
						int SizeOfSun = 100;//размер солнышка


						FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0,0,255)));
						HPEN newPen = CreatePen(PS_SOLID, 15, RGB(255,0,0));
						HBRUSH newBrush = CreateSolidBrush(RGB(255,0,0));

						HGDIOBJ oldBrush = SelectObject(hdc, newBrush);
						HGDIOBJ oldPen = SelectObject(hdc, newPen);//сохраняем предыдущий pen
						HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH));

						//рисуем линию
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);//рисуем лучи
						LineTo(hdc, 0, 0);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right, 0);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right/2, 0);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, 0, clientRect.bottom/2);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right, clientRect.bottom/2);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right/4, 0);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, 3*clientRect.right/4, 0);

						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, 0, 3*clientRect.bottom/4);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right, 3*clientRect.bottom/4);

						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, 0, clientRect.bottom);
						MoveToEx(hdc, clientRect.right/2, clientRect.bottom, NULL);
						LineTo(hdc, clientRect.right, clientRect.bottom);

					
						//рисуем солнышко
						Chord(
						hdc,
						clientRect.right/2 - SizeOfSun,//Координата x в логических координатах верхнего левого угла ограничительного прямоугольника.
						clientRect.bottom + SizeOfSun,//Координата y в логических координатах верхнего левого угла ограничительного прямоугольника.
						clientRect.right/2 + SizeOfSun,//Коорд  ината x в логических координатах нижнего правого угла ограничительного прямоугольника.
						clientRect.bottom - SizeOfSun,//Y-координата в логических координатах нижнего правого угла ограничительного прямоугольника.
						clientRect.right/2 + SizeOfSun,//Координата x в логических координатах конечной точки радиуса, определяющего начало хорды.
						clientRect.bottom,//Y-координата в логических координатах конечной точки радиуса, определяющего начало хорды.
						clientRect.right/2 - SizeOfSun,//Координата x в логических координатах конечной точки радиуса, определяющего конец хорды.
						clientRect.bottom);//Y-координата в логических координатах конечной точки радиуса, определяющего конец хорды.
					
						SelectObject(hdc, oldPen);
						SelectObject(hdc, oldBrush);

						DeleteObject(newPen); 
						DeleteObject(newBrush);
					}

					if ((flagSun == 0) && (flagNight == 0) && (flagStars == 0))
					{
						//HBRUSH newBrush = CreateSolidBrush(RGB(0,0,255));
						FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0,0,255)));
					}

					if ((flagSun == 0) && (flagNight == 1) && (flagStars == 0))
					{
						FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0,0,0)));
					}
					
					if ((flagSun == 0) && (flagNight == 1) && (flagStars == 1))
					{
						int i;
						//srand(time(NULL));
						//FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0,0,0)));
						for (i = 0; i< nstar-1; i++)
						{
						//	SetPixel(hdc, rand()%clientRect.right, rand()%clientRect.bottom, RGB(255,255,255));
							SetPixel(hdc, star[i][1],star[i][2] , RGB(255,255,255));
						}
					}

					EndPaint(hWnd, &ps);//завершение рисования
			}
			break;
		case WM_LBUTTONDOWN: 
		{
			if(flagSun == 1) 
			{
				GetClientRect(hWnd, &clientRect);
				flagSun = 0;
				InvalidateRect(hWnd, &clientRect, FALSE);
			}

		}
		break;
		case WM_RBUTTONDOWN: 
		{
			if ((flagStars == 0)&&(flagNight == 1)&&(flagSun == 0))
			{
				flagStars = 1;
				GetClientRect(hWnd, &clientRect);
				InvalidateRect(hWnd, &clientRect, FALSE);
			}
			if ((flagStars == 0)&&(flagNight == 0)&&(flagSun == 0))
			{
				flagNight = 1;
				GetClientRect(hWnd, &clientRect);
				InvalidateRect(hWnd, &clientRect, FALSE);
			}

		}
		break;



		case WM_DESTROY : 
			PostQuitMessage(0); 
			break; 			// Завершение программы 
		default : 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	} 
	return 0;
}
