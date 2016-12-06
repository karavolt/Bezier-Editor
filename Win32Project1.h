#pragma once

#include "resource.h"

// ������
typedef struct _Point2d {
	int x;
	int y;
}Point2d;

// ������ Ŀ�� �ϳ� ����.
typedef struct _BezierCurve {
	vector<Point2d> BCurve;
	COLORREF BColor;
	bool isModifing;
}BezierCurve;

typedef struct _BezierCurves {
	vector<BezierCurve> BezierAlphabet;
	int AllocationAlphabet;
}BezierCurves;

// ���ĺ�, �迭�� ����� ���ؼ�..
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

// ��ü ������ Ŀ�� �����̳�
vector<BezierCurves> bezierContainer;		// �����Ҷ�
vector<BezierCurves> SavedbezierContainer;	// �����ϰ� �����Ҷ�

// ���� �������� ���ĺ�.
int CurAllocAlpha = AlphaBetA;
// ���� �������� ȹ��
int CurActiveLineNumber = 0;

// ���� On/Off
bool bShowLine = true;

// �̸����ǵ� ��
const COLORREF WHITE = 0xFFFFFF;
const COLORREF BLACK = 0x000000;
const COLORREF RED = 0xFF0000;
const COLORREF GREEN = 0x00FF00;
const COLORREF BLUE = 0x0000FF;

// Color Dialog Box
CHOOSECOLOR curPickColor;
DWORD curRgb;
COLORREF acrCustClr[16];	// �̸����ǵ� ��
// �Լ� ����
void DrawBezier(HDC hdc, char AllocAlpha);