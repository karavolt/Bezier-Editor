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
}BezierCurve;

typedef struct _BezierCurves {
	vector<BezierCurve> BezierAlphabet;
	char AllocationAlphabet;
}BezierCurves;

// ��ü ������ Ŀ�� �����̳�
vector<BezierCurves> bezierContainer;		// �����Ҷ�
vector<BezierCurves> SavedbezierContainer;	// �����ϰ� �����Ҷ�

// ���� �������� ���ĺ�.
char CurAllocAlpha = 'a';
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

// �Լ� ����
void DrawBezier(HDC hdc, char AllocAlpha);
BezierCurves FindAllocAlphabet(char key);