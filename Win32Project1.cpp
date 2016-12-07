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


   // ���� ������ �ڵ� ����� ���� ����
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
	// ��������� ���� -->
	BezierCurves a;
	BezierCurve b1;
	Point2d pos;
	// ��������� ���� <--
    switch (message)
    {
	case WM_CREATE:		
		
		// �ʱ� ����� ���ĺ� 26�ڿ� ���ؼ� �ʱ�ȭ ���� -->
		b1.BColor = 0x000000;
		b1.isModifing = true;
		a.BezierAlphabet.push_back(b1);
		for (int i = 0; i < 26; i++)
		{
			// ������Ǹ� ���� 'a' == 0���� ����Ϸ��� enum���
			a.AllocationAlphabet = AlphabetMap::AlphaBetA + i;			
			bezierContainer.push_back(a);
		}
		// �ʱ� ����� ���ĺ� 26�ڿ� ���ؼ� �ʱ�ȭ ���� <--


		// color Dialog setting -->
		curRgb = 0x000000;
		ZeroMemory(&curPickColor, sizeof(curPickColor));
		curPickColor.lStructSize = sizeof(curPickColor);
		curPickColor.hwndOwner = hWnd;
		curPickColor.lpCustColors = (LPDWORD)acrCustClr;
		curPickColor.rgbResult = curRgb;
		curPickColor.Flags = CC_FULLOPEN | CC_RGBINIT;
		// color Dialog setting <--

		break;
	case WM_LBUTTONDOWN:
		// �������� ������ ���� -->
		pos.x = LOWORD(lParam) * xRatio;
		pos.y = HIWORD(lParam) * yRatio;
		bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.push_back(pos);
		// �������� ������ ���� <--
		InvalidateRect(hWnd, 0, true);	// ������ �ٽñ׸���(���� �����ϴ� �ּ�)
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		// �����ϸ��� ������ � �̵����� �������� �ڵ� -->
		case VK_UP:
			yOffset -= 10.0;
			break;
		case VK_DOWN:
			yOffset += 10.0;			
			break;
		case VK_LEFT:
			xOffset -= 10.0;			
			break;
		case VK_RIGHT:
			xOffset += 10.0;
			break;
		// �����ϸ��� ������ � �̵����� �������� �ڵ� <--

		// ������, ���� �ʱ�ȭ -->
		case VK_SPACE:
			xOffset = 0.0;
			yOffset = 0.0;
			xRatio = 0.0;
			yRatio = 0.0;
		// ������, ���� �ʱ�ȭ <--
			break;
		}
		InvalidateRect(hWnd, 0, true);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		// Ȯ�� ��� -->
		case 'W':
		case 'w':
			xRatio += 0.25;
			yRatio += 0.25;
			break;
		case 'S':
		case 's':
			xRatio -= 0.25;
			yRatio -= 0.25;
			break;
		// Ȯ�� ��� <--

		// Ŀ�� �߰� ����Ű -->
		case 'A':
		case 'a':
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

			b1.BColor = curRgb;
			b1.isModifing = true;
			bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);			
			CurActiveLineNumber++;
		// Ŀ�� �߰� ����Ű <--
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
			
			// ���ĺ� ���� ���̾�α� �˾�~
			case IDM_CHANGECHAR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
				break;

			// Ŀ�� �߰�~
			case IDM_ADDCURVE:
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

				b1.BColor = curRgb;
				b1.isModifing = true;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				CurActiveLineNumber++;
				break;

			// ���� �������� Ŀ�� ����
			case IDM_REMOVEONE:
				if (bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.size() == 0)
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.clear();
				InvalidateRect(hWnd, 0, true);
				break;

			// ���� ���ĺ��� ��� Ŀ�� ����
			case IDM_REMOVEALL:
				bezierContainer[CurAllocAlpha].BezierAlphabet.clear();
				CurActiveLineNumber = 0;
				b1.BColor = 0x000000;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				InvalidateRect(hWnd, 0, true);
				break;

			// ���������� �߰��� �� ����
			case IDM_REMOVELAST:
				if (!bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.empty())
					bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.pop_back();
				InvalidateRect(hWnd, 0, true);
				break;

			// LineTo�� �׸� ���� On/Off
			case IDM_LINE:
				bShowLine = !bShowLine;
				InvalidateRect(hWnd, 0, true);
				break;
			
			// �÷� ���� ���̾�α� �˾�
			case IDM_PICKCOLOR:
				if (ChooseColor(&curPickColor) == true)
				{
					// ���õ� ���� ���� ������ ����~
					curRgb = curPickColor.rgbResult;
					InvalidateRect(hWnd, 0, true);
				}
				break;

			//����~
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
            // ������ � �׸���
			DrawBezier(hdc);
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
		// ���̾�α� �ʱ�ȭ �ϸ鼭 a~z���� �޺��ڽ��� �ֱ�
		hwndCombo = GetDlgItem(hDlg, IDC_COMBO1);
		for (int i = 0; i < 26; i++)
		{
			SendMessage(hwndCombo, CB_ADDSTRING, 0,(LPARAM) Alphabet[i]);
		}
		// ���� �������� ���ĺ����� ��Ŀ�� ����
		SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) CurAllocAlpha, (LPARAM) 0);
        return (INT_PTR)TRUE;
		break;
    case WM_COMMAND:
		if (LOWORD(wParam) == IDC_COMBO1)
		{		
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				// �޺��ڽ� �����Ѱ� �ٲ�� �������ִ� ó��
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

void DrawBezier(HDC hdc)
{
	// ���� �������� ���ĺ��� ��������
	BezierCurves cur = bezierContainer[CurAllocAlpha];
	// �ݺ� ������ ���~
	vector<BezierCurve>::iterator it;
	for (it = cur.BezierAlphabet.begin(); it < cur.BezierAlphabet.end(); it++)
	{
		// ���� ���� ������ �������
		int degree = it->BCurve.size();
		// t�� [0,1], 0.001�������� �����
		for (double t = 0.0; t < 1.0; t += 0.001)
		{
			// ������ � ����� x,y��ǥ
			double xt = 0.0, yt = 0.0;
			// ������ŭ �˾Ƽ� ����Ѵ�
			for (int i = 0; i < degree; i++)
			{
				// �������� �޾ƿ� Ȯ������� ���Ѵ�
				double xPos = it->BCurve[0 + i].x * xRatio,
				   	   yPos = it->BCurve[0 + i].y * yRatio;
				// ��ó���� �Ǹ������� ������ŭ ������ ����.
				if (i == 0 || i == degree - 1)
				{
					xt += pow(t, i)  * pow(1 - t, degree - 1 - i) * (xPos);
					yt += pow(t, i)  * pow(1 - t, degree - 1 - i) * (yPos);
				}
				else
				{
					xt += (degree - 1) * pow(t, i)  *pow(1 - t, degree - 1 - i) * (xPos);
					yt += (degree - 1) * pow(t, i)  *pow(1 - t, degree - 1 - i) * (yPos);
				}
			}
			// �������ΰͰ� ����Ȱ� ������
			COLORREF usingColor = (it->isModifing ? curRgb : it->BColor);
			// ���� ������ offset�� ���ļ�~
			SetPixel(hdc, xt + xOffset, yt + yOffset, usingColor);
		}


		// �����׸��� On�϶��� �׸���
		if (!it->BCurve.empty() && bShowLine)
		{
			// �ݺ�������
			vector<Point2d>::iterator pit;
			// ���������� �̵��Ҷ��� offset~
			MoveToEx(hdc, it->BCurve[0].x * xRatio + xOffset, it->BCurve[0].y * yRatio + yOffset, NULL);
			for (pit = it->BCurve.begin(); pit < it->BCurve.end(); pit++)
			{
				// ���� �׸����� offset~
				LineTo(hdc, pit->x * xRatio + xOffset, pit->y * yRatio + yOffset);
			}
		}
	}	
}