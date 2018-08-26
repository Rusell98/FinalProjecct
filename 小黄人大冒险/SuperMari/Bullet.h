#pragma once
#include "stdfx.h"
#define bullet_distance 200 //子弹的移动速度
class CBullet
{
public:
	CBullet();
	~CBullet();
	//绘制子弹
	void Draw(void);
private:
	//子弹DC
	HDC hBuDc;
	//处理背景
	HDC hMaskDc;
	struct BULLET
	{
		int init_x;
		int init_y;
		int x;
		int y;
		int type;
		bool life;
		bool bMove;
		bool visble;
	}temp[2];//冰子弹与普通子弹
public:
	// 刷新子弹
	void Update(void);
private:
	// 子弹移动
	void Move(int);
	//子弹获得
public:
	// 与怪物进行碰撞
	int collideWithMonster(int ix, int iy);
public:
	// 杀死怪物
	void killMonster(int index);
public:
	// 重置子弹数据
	void Reset(void);
};
