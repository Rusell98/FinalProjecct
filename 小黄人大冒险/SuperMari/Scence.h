#pragma once
#include "stdfx.h"
#include "Player.h"
class CScence
{
public:
	CScence();
	void Draw();//绘制场景自己
	void Update();//刷新场景状态
	~CScence();
private:
	void imageA( int x, int y,  int cx,  int cy, int x1,  int y1);//背景透明处理
	void drawHill(int x,int y);
	void drawTemple(int x,int y);
	void drawFlag(int x,int y);
	void drawGrass(int x,int y);
	void drawCloud(int x,int y);
	void drawTree(int x,int y);
	void drawWall(int x,int y,int index);
	void drawHose(int x,int y,int height=1);//画水管
	void drawCursor(int x, int y);//画光标
	int duceDraw(int x1);//判断是否超出屏幕，超出则不画
	HDC hDc,hWallDc;	//场景DC句柄
	HDC hMaskDc;	//处理透明效果的遮罩dc句柄
	HDC hTitleDc,hTitleMaskDc,hBeginDc,hCursorDc,hDifficultyDc,hLevelDc,hSetupDc,hSwitchDc, hSwitchoffDc,hSpeedDc,hBlindDc,hLifetimeDc,hProtectDc,hPlayerDc,hShopDc,hBulletDc;//添加了开始画面dc句柄
	HDC hCoinDC,hCoinMaskDc,hSpeedMaskDc,hBlindMaskDc,hLifetimeMaskDc,hProtectMaskDc,hPlayerMaskDc, hBulletMaskDc;
	BITMAP titleBmp,dieBmp,overBmp,BeginBmp,CursorBmp,DifficultyBmp,LevelBmp,SetupBmp,SwitchBmp, SwitchoffBmp,SpeedBmp,BlindBmp,LifetimeBmp,ProtectBmp,PlayerBmp,ShopBmp,BulletBmp;
	// 控制问号动画循环
	int loopQues;
public:
	// 重置地图数据
	void Reset(void);
private:
	void drawCoin(int x, int y,int frame);// 画金币
	void coinBitBlt(int x, int y, int width,int frame);
	void drawSpeed(int x, int y);//画加速符
	void drawBlind(int x, int y);//画致盲符
	void drawLife(int x, int y);//画生命符
	void drawProtect(int x, int y);//画保护符
	void drawBullet(int x, int y);//画子弹
public:
	// 与水管进行碰撞判断
	int collideWithHose(int ix, int iy);
	void drawPlayer(int x, int y, int frame);//画玩家
private:
	// 死亡图片DC
	HDC hDieDc;
	//游戏结束图片DC
	HDC hOverDc;
	// 控制死亡图片动画
	int dieLoop;
	// 做标题动画遮罩的区域
	RECT titleRect;
	// 控制金币动画帧数
	int loopCoin;
public:
	// 控制砖块破碎动画
	void boom(int ix, int iy);
private:
	struct SMALL_WALL
	{
		int x[4];
		int y[4];
		int frame;
		SMALL_WALL * next;
	} *head;
	struct COIN_OUT
	{
		int x;
		int y;
		int frame;
	}outCoin;
public:
	// 撞出金币动画
	void coinOut(int ix, int iy);
};
