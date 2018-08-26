#pragma once
#include "stdfx.h"
#define speed_degree_1 20
#define speed_degree_2 10
#define speed_degree_3 5
#define speed_degree_4 2
class CPlayer
{
public:
	CPlayer();
	void Draw();//绘制玩家自己
	void keyDown(WPARAM wparam);
	void keyUp(WPARAM wparam);
	void Update();//刷新玩家状态
	int getX();//获取玩家X坐标
	int getY();
	int getdeltaX();
	~CPlayer();
private:
	//玩家世界X坐标
	int x;
	//玩家世界y坐标
	int y;	
	//玩家正常水平移动速度
	int speed;	
	//控制动画的帧数
	int frame; 
	//是否在下降过程
	bool bFalling;
	//上下左右键是否被按下
	bool bRightKey,bLeftKey,bUpKey,bDownKey;
	// Control键是否被按下
	bool bControlKey;
	//玩家DC句柄
	HDC hDc;	
	//玩家bmp句柄
	HBITMAP hBitmap;
	//处理透明效果的遮罩dc句柄
	HDC hMaskDc;	
	// 玛丽将在X轴上移动的距离
	int dltaX;
	// 玛丽在Y轴的移动距离
	int daltY;
	// 控制动画帧
	int animalLoop;
	// 控制水平加速度
	int dltaXLoop;
	// 移动玛丽
	void moveMari(void);
	// 设置玛丽动画
	void MariAnimal(void);
	// 处理玛丽的碰撞
	void collide(void);
	//水平移动函数
	void walk();
	// 玩家是否着地
	bool bLanded;
	// 玩家方向,-1表示向左,-2表示向右,0表示向前
	int direction;
	// 玩家上升函数
	void mariRising(void);
	// 玩家下落过程
	void mariFalling(void);
	// 玩家是否正在上升
	bool bRising;
public:
	// 重置玩家数据
	bool Reset(void);
private:
	// 玩家生命数量
	int lifeNumber;
	// 获取的金币数量
	// 表示可以高跳的距离控制
	int _g;
	// 控制玩家跳跃的加速度效果
	int g;
	// 获取金币并且播放金币声音
	void getCoin(int index);
	//玩家速度增加时间并播放声音
	void getSpeed(int index);
	//玩家致盲时间增加
	void getBlind(int index);
	//玩家生命数增加
	void getLifetime(int index);
	//玩家保护时间数增加
	void getProtecttime(int index);
public:
	// 玩家死亡
	void killMari(void);
};
