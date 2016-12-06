// Win32Project1.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1024, 768, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BezierCurves a;
	BezierCurve b1;
	Point2d pos;
    switch (message)
    {
	case WM_CREATE:		
		
		b1.BColor = BLACK;
		b1.isModifing = true;
		a.BezierAlphabet.push_back(b1);
		for (int i = 0; i < 26; i++)
		{
			a.AllocationAlphabet = AlphabetMap::AlphaBetA + i;			
			bezierContainer.push_back(a);
		}

		// color Dialog
		curRgb = 0x000000;
		ZeroMemory(&curPickColor, sizeof(curPickColor));
		curPickColor.lStructSize = sizeof(curPickColor);
		curPickColor.hwndOwner = hWnd;
		curPickColor.lpCustColors = (LPDWORD)acrCustClr;
		curPickColor.rgbResult = curRgb;
		curPickColor.Flags = CC_FULLOPEN | CC_RGBINIT;

		break;
	case WM_LBUTTONDOWN:
		pos.x = LOWORD(lParam);
		pos.y = HIWORD(lParam);
		bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.push_back(pos);
		InvalidateRect(hWnd, 0, true);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'W':
		case 'w':
			xRatio += 0.5;
			yRatio += 0.5;
			break;
		case 'S':
		case 's':
			xRatio -= 0.5;
			yRatio -= 0.5;
			break;
		case 'A':
		case 'a':
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

			b1.BColor = curRgb;
			b1.isModifing = true;
			bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);			
			CurActiveLineNumber++;
			break;
		}		
		InvalidateRect(hWnd, 0, true);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {			
            case IDM_CHANGECHAR:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
                break;
			case IDM_ADDCURVE:
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

				b1.BColor = curRgb;
				b1.isModifing = true;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				CurActiveLineNumber++;
				break;
				break;
			case IDM_REMOVEONE:
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.clear();
				InvalidateRect(hWnd, 0, true);
				break;
			case IDM_REMOVEALL:
				bezierContainer[CurAllocAlpha].BezierAlphabet.clear();
				CurActiveLineNumber = 0;
				b1.BColor = BLACK;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				InvalidateRect(hWnd, 0, true);
				break;
			case IDM_REMOVELAST:
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.pop_back();
				InvalidateRect(hWnd, 0, true);
				break;
			case IDM_LINE:
				bShowLine = !bShowLine;
				InvalidateRect(hWnd, 0, true);
				break;
			case IDM_PICKCOLOR:
				if (ChooseColor(&curPickColor) == true)
				{
					curRgb = curPickColor.rgbResult;
					InvalidateRect(hWnd, 0, true);
				}
				break;
			case IDM_CHANGEALPHA:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			DrawBezier(hdc,CurAllocAlpha);
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


// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	
    switch (message)
    {
    case WM_INITDIALOG:
		hwndCombo = GetDlgItem(hDlg, IDC_COMBO1);
		for (int i = 0; i < 26; i++)
		{
			SendMessage(hwndCombo, CB_ADDSTRING, 0,(LPARAM) Alphabet[i]);
		}
		SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) CurAllocAlpha, (LPARAM) 0);
        return (INT_PTR)TRUE;
		break;
    case WM_COMMAND:
		if (LOWORD(wParam) == IDC_COMBO1)
		{		
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int ItemIndex = SendMessage((HWND)hwndCombo, (UINT)CB_GETCURSEL,
					(WPARAM)0, (LPARAM)0);
				CurAllocAlpha = ItemIndex;
				CurActiveLineNumber = bezierContainer[CurAllocAlpha].BezierAlphabet.size() - 1;
				
			}
		}
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
			InvalidateRect(g_hWnd, 0, true);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawBezier(HDC hdc, char AllocAlpha)
{
	int i;
	double t;
	BezierCurves cur = bezierContainer[CurAllocAlpha];

	// ���;ȿ� ����Ǿ� �������� �� ��.
	if (!cur.BezierAlphabet.empty())
	{
		vector<BezierCurve>::iterator it;
		for (it = cur.BezierAlphabet.begin(); it < cur.BezierAlphabet.end(); it++)
		{
			int degree = it->BCurve.size();
			for (t = 0.0; t < 1.0; t += 0.0005)
			{
				double xt = 0.0, yt = 0.0;
				for (int i = 0; i < degree; i++)
				{
					if (i == 0 || i == degree - 1)
					{
						xt += pow(t, i)  * pow(1 - t, degree - 1 - i) * (it->BCurve[0 + i].x * xRatio);
						yt += pow(t, i)  * pow(1 - t, degree - 1 - i) * (it->BCurve[0 + i].y * yRatio);
					}
					else
					{
						xt += (degree - 1) * pow(t, i)  *pow(1 - t, degree - 1 - i) * (it->BCurve[0 + i].x * xRatio);
						yt += (degree - 1) * pow(t, i)  *pow(1 - t, degree - 1 - i) * (it->BCurve[0 + i].y * yRatio);
					}
				}

				COLORREF usingColor = (it->isModifing ? curRgb : it->BColor);
				SetPixel(hdc, xt, yt, usingColor);
			}



			if (!it->BCurve.empty() && bShowLine)
			{
				vector<Point2d>::iterator pit;
				// ���������� �̵�
				MoveToEx(hdc, it->BCurve[0].x * xRatio, it->BCurve[0].y * yRatio, NULL);
				for (pit = it->BCurve.begin(); pit < it->BCurve.end(); pit++)
				{
					LineTo(hdc, pit->x * xRatio, pit->y * yRatio);
				}
			}
		}
	}
}