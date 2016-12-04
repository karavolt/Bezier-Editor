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
}BezierCurve;

typedef struct _BezierCurves {
	vector<BezierCurve> BezierAlphabet;
	char AllocationAlphabet;
}BezierCurves;

// 전체 베지어 커브 컨테이너
vector<BezierCurves> bezierContainer;		// 수정할때
vector<BezierCurves> SavedbezierContainer;	// 수정하고 저장할때

// 현재 수정중인 알파벳.
char CurAllocAlpha = 'a';
// 현재 수정중인 획수
int CurActiveLineNumber = 0;

// 직선 On/Off
bool bShowLine = true;

// 미리정의된 색
const COLORREF WHITE = 0xFFFFFF;
const COLORREF BLACK = 0x000000;
const COLORREF RED = 0xFF0000;
const COLORREF GREEN = 0x00FF00;
const COLORREF BLUE = 0x0000FF;

// 함수 원형
void DrawBezier(HDC hdc, char AllocAlpha);
BezierCurves FindAllocAlphabet(char key);