#pragma once

#include "resource.h"

// 점정보
typedef struct _Point2d {
	int x;
	int y;
}Point2d;

// 베지어 커브 하나 저장.
typedef struct _BezierCurve {
	vector<Point2d> BCurve;
	COLORREF BColor;
	bool isModifing;
}BezierCurve;

typedef struct _BezierCurves {
	vector<BezierCurve> BezierAlphabet;
	int AllocationAlphabet;
}BezierCurves;

// 알파벳, 배열간 사용을 위해서..
enum AlphabetMap
{
	AlphaBetA = 0,
	AlphaBetB = 1,
	AlphaBetC = 2,
	AlphaBetD = 3,
	AlphaBetE = 4,
	AlphaBetF = 5,
	AlphaBetG = 6,
	AlphaBetH = 7,
	AlphaBetI = 8,
	AlphaBetJ = 9,
	AlphaBetK = 10,
	AlphaBetL = 11,
	AlphaBetM = 12,
	AlphaBetN = 13,
	AlphaBetO = 14,
	AlphaBetP = 15,
	AlphaBetQ = 16,
	AlphaBetR = 17,
	AlphaBetS = 18,
	AlphaBetT = 19,
	AlphaBetU = 20,
	AlphaBetV = 21,
	AlphaBetW = 22,
	AlphaBetX = 23,
	AlphaBetY = 24,
	AlphaBetZ = 25
};

// 전체 베지어 커브 컨테이너
vector<BezierCurves> bezierContainer;		// 수정할때
vector<BezierCurves> SavedbezierContainer;	// 수정하고 저장할때

// 현재 수정중인 알파벳.
int CurAllocAlpha = AlphaBetA;
// 현재 수정중인 획수
int CurActiveLineNumber = 0;

// 직선 On/Off
bool bShowLine = true;

//축소 확대 비율
double xRatio = 3.0;
double yRatio = 3.0;
// 미리정의된 색
const COLORREF WHITE = 0xFFFFFF;
const COLORREF BLACK = 0x000000;
const COLORREF RED = 0xFF0000;
const COLORREF GREEN = 0x00FF00;
const COLORREF BLUE = 0x0000FF;

// Color Dialog Box
CHOOSECOLOR curPickColor;
DWORD curRgb;
COLORREF acrCustClr[16];	// 미리정의된 색

HWND g_hWnd = NULL;
HWND hwndCombo = NULL;
TCHAR Alphabet[26][2] = { TEXT("a"), TEXT("b"), TEXT("c"), TEXT("d"), TEXT("e"), TEXT("f"), TEXT("g"), TEXT("h"), TEXT("i"),
						  TEXT("j"), TEXT("k"), TEXT("l"), TEXT("m"), TEXT("n"), TEXT("o"), TEXT("p"), TEXT("q"), TEXT("r"), 
						  TEXT("s"), TEXT("t"), TEXT("u"), TEXT("v"), TEXT("w"), TEXT("x"), TEXT("y"), TEXT("z") };
// 함수 원형
void DrawBezier(HDC hdc, char AllocAlpha);

