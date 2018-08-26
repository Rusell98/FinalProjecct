#pragma once
#include "stdfx.h"

class CMonster
{
public:
	CMonster(void);
	~CMonster(void);
	// ���ƹ���
	void Draw(void);
private:
	// ����DC
	HDC hMonDc;
	// ������͸��������DC
	HDC hMaskDc;
	struct MONTSTER
	{
		int x;
		int y;
		int type;
		bool life;
		bool bMove;
		bool visble;
	}temp[10];
	// ����ͬ����Ĺ�
	void drawMonster(int type,int x,int y);
public:
	// ˢ�¹���
	void Update(void);
private:
	// �����ƶ�
	void Move(int);
public:
	// ���ù�������
	void Reset(void);
public:
	// ����������ײ
	int collideWithMonster(int ix, int iy);
	// ��������
	int monsterNumber;
public:
	// ɱ������
	void killMonster(int index);
	// ���ﱻѹ�����ʾ��ʱ��֡������
	int flatLoop;
};
