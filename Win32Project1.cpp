// Win32Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1024, 768, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }


   // 전역 윈도우 핸들 사용을 위해 저장
   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 벡터저장용 더미 -->
	BezierCurves a;
	BezierCurve b1;
	Point2d pos;
	// 벡터저장용 더미 <--
    switch (message)
    {
	case WM_CREATE:		
		
		// 초기 실행시 알파벳 26자에 대해서 초기화 진행 -->
		b1.BColor = 0x000000;
		b1.isModifing = true;
		a.BezierAlphabet.push_back(b1);
		for (int i = 0; i < 26; i++)
		{
			// 사용편의를 위해 'a' == 0으로 사용하려고 enum사용
			a.AllocationAlphabet = AlphabetMap::AlphaBetA + i;			
			bezierContainer.push_back(a);
		}
		// 초기 실행시 알파벳 26자에 대해서 초기화 진행 <--


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
		// 점찍으면 점정보 저장 -->
		pos.x = LOWORD(lParam) * xRatio;
		pos.y = HIWORD(lParam) * yRatio;
		bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.push_back(pos);
		// 점찍으면 점정보 저장 <--
		InvalidateRect(hWnd, 0, true);	// 윈도우 다시그리기(이하 생략하는 주석)
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		// 스케일링후 베지어 곡선 이동시켜 보기위한 코드 -->
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
		// 스케일링후 베지어 곡선 이동시켜 보기위한 코드 <--

		// 오프셋, 비율 초기화 -->
		case VK_SPACE:
			xOffset = 0.0;
			yOffset = 0.0;
			xRatio = 0.0;
			yRatio = 0.0;
		// 오프셋, 비율 초기화 <--
			break;
		}
		InvalidateRect(hWnd, 0, true);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		// 확대 축소 -->
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
		// 확대 축소 <--

		// 커브 추가 단축키 -->
		case 'A':
		case 'a':
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
			bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

			b1.BColor = curRgb;
			b1.isModifing = true;
			bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);			
			CurActiveLineNumber++;
		// 커브 추가 단축키 <--
			break;
		}		
		InvalidateRect(hWnd, 0, true);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {			
			
			// 알파벳 변경 다이얼로그 팝업~
			case IDM_CHANGECHAR:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
				break;

			// 커브 추가~
			case IDM_ADDCURVE:
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].isModifing = false;
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BColor = curRgb;

				b1.BColor = curRgb;
				b1.isModifing = true;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				CurActiveLineNumber++;
				break;

			// 현재 수정중인 커브 삭제
			case IDM_REMOVEONE:
				if (bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.size() == 0)
				bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.clear();
				InvalidateRect(hWnd, 0, true);
				break;

			// 현재 알파벳의 모든 커브 삭제
			case IDM_REMOVEALL:
				bezierContainer[CurAllocAlpha].BezierAlphabet.clear();
				CurActiveLineNumber = 0;
				b1.BColor = 0x000000;
				bezierContainer[CurAllocAlpha].BezierAlphabet.push_back(b1);
				InvalidateRect(hWnd, 0, true);
				break;

			// 마지막으로 추가된 점 삭제
			case IDM_REMOVELAST:
				if (!bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.empty())
					bezierContainer[CurAllocAlpha].BezierAlphabet[CurActiveLineNumber].BCurve.pop_back();
				InvalidateRect(hWnd, 0, true);
				break;

			// LineTo로 그린 직선 On/Off
			case IDM_LINE:
				bShowLine = !bShowLine;
				InvalidateRect(hWnd, 0, true);
				break;
			
			// 컬러 선택 다이얼로그 팝업
			case IDM_PICKCOLOR:
				if (ChooseColor(&curPickColor) == true)
				{
					// 선택된 색을 현재 색으로 저장~
					curRgb = curPickColor.rgbResult;
					InvalidateRect(hWnd, 0, true);
				}
				break;

			//종료~
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
            // 베지어 곡선 그리기
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


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	
    switch (message)
    {
    case WM_INITDIALOG:
		// 다이얼로그 초기화 하면서 a~z까지 콤보박스에 넣기
		hwndCombo = GetDlgItem(hDlg, IDC_COMBO1);
		for (int i = 0; i < 26; i++)
		{
			SendMessage(hwndCombo, CB_ADDSTRING, 0,(LPARAM) Alphabet[i]);
		}
		// 현재 수정중인 알파벳으로 포커스 수정
		SendMessage(hwndCombo, CB_SETCURSEL, (WPARAM) CurAllocAlpha, (LPARAM) 0);
        return (INT_PTR)TRUE;
		break;
    case WM_COMMAND:
		if (LOWORD(wParam) == IDC_COMBO1)
		{		
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				// 콤보박스 선택한게 바뀌면 변경해주는 처리
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
	// 현재 수정중인 알파벳을 가져오자
	BezierCurves cur = bezierContainer[CurAllocAlpha];

	// 반복 연산자 사용~
	vector<BezierCurve>::iterator it;
	for (it = cur.BezierAlphabet.begin(); it < cur.BezierAlphabet.end(); it++)
	{
		// 점의 수를 차수로 사용하자
		int degree = it->BCurve.size();

		// t는 [0,1], 0.001간격으로 점찍기
		for (double t = 0.0; t < 1.0; t += 0.001)
		{
			// 베지어 곡선 계산한 x,y좌표
			double xt = 0.0, yt = 0.0;

			// 차수만큼 알아서 계산한다
			for (int i = 0; i < degree; i++)
			{
				// 점정보를 받아와 확대비율을 곱한다
				double xPos = it->BCurve[0 + i].x * xRatio,
				   	   yPos = it->BCurve[0 + i].y * yRatio;

				// 맨처음과 맨마지막은 차수만큼 곱하지 않음.
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

			// 수정중인것과 저장된것 색선택
			COLORREF usingColor = (it->isModifing ? curRgb : it->BColor);

			// 점을 찍을땐 offset을 합쳐서~
			SetPixel(hdc, xt + xOffset, yt + yOffset, usingColor);
		}


		// 직선그리기 On일때만 그리자
		if (!it->BCurve.empty() && bShowLine)
		{
			// 반복연산자
			vector<Point2d>::iterator pit;
			// 시작점으로 이동할때도 offset~
			MoveToEx(hdc, it->BCurve[0].x * xRatio + xOffset, it->BCurve[0].y * yRatio + yOffset, NULL);
			for (pit = it->BCurve.begin(); pit < it->BCurve.end(); pit++)
			{
				// 직선 그릴때도 offset~
				LineTo(hdc, pit->x * xRatio + xOffset, pit->y * yRatio + yOffset);
			}
		}
	}	
}