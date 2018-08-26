#pragma once
#include "stdfx.h"

class CMonster
{
public:
	CMonster(void);
	~CMonster(void);
	// 绘制怪物
	void Draw(void);
private:
	// 怪物DC
	HDC hMonDc;
	// 处理背景透明的遮罩DC
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
	// 画不同种类的怪
	void drawMonster(int type,int x,int y);
public:
	// 刷新怪物
	void Update(void);
private:
	// 怪物移动
	void Move(int);
public:
	// 重置怪物数据
	void Reset(void);
public:
	// 与怪物进行碰撞
	int collideWithMonster(int ix, int iy);
	// 怪物总数
	int monsterNumber;
public:
	// 杀死怪物
	void killMonster(int index);
	// 怪物被压扁后显示的时间帧数控制
	int flatLoop;
};
