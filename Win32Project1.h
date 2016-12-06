#pragma once

#include "resource.h"

// 점정보
typedef struct _Point2d {
	double x;
	double y;
}Point2d;

// 베지어 커브 하나 저장.
typedef struct _BezierCurve {
	vector<Point2d> BCurve;
	COLORREF BColor;
	bool isModifing;
}BezierCurve;

// 베지어 곡선으로 이루어진 알파벳 저장
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

// 현재 수정중인 알파벳.
int CurAllocAlpha = AlphaBetA;
// 현재 수정중인 획수
int CurActiveLineNumber = 0;

// 직선 On/Off
bool bShowLine = true;

//축소 확대 비율
double xRatio = 1.0;
double yRatio = 1.0;

// 축소 확대 offset
double xOffset = 0.0;
double yOffset = 0.0;

// 컬러픽커다이얼로그를 위해서..
CHOOSECOLOR curPickColor;	// 선택한 컬러정보를 담기위한것
DWORD curRgb;				// RGB정보만 가져오려고
COLORREF acrCustClr[16];	// 없으면 에러나니 추가해줌

HWND g_hWnd = NULL;			// 전역 윈도우 핸들
HWND hwndCombo = NULL;		// 알파벳 선택하는 콤보박스 핸들
TCHAR Alphabet[26][2] = { TEXT("a"), TEXT("b"), TEXT("c"), TEXT("d"), TEXT("e"), TEXT("f"), TEXT("g"), TEXT("h"), TEXT("i"),
						  TEXT("j"), TEXT("k"), TEXT("l"), TEXT("m"), TEXT("n"), TEXT("o"), TEXT("p"), TEXT("q"), TEXT("r"), 
						  TEXT("s"), TEXT("t"), TEXT("u"), TEXT("v"), TEXT("w"), TEXT("x"), TEXT("y"), TEXT("z") };
// 함수 원형
void DrawBezier(HDC hdc, char AllocAlpha);

