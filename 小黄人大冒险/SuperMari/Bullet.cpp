#include "Bullet.h"
#include "Player.h"
#include "Monster.h"
extern CPlayer * player;
extern int stage;
extern int bufferX;
extern int bufferY;
extern int mapIndex[2800];
extern int gameStep;
extern HDC hMemDc;
extern HINSTANCE hInstance;
extern CMonster * monster;
extern int bullet_shop_number;
bool bullet_flag = 0;//子弹的发射标志位
int bullet_number = 1;//子弹数目
CBullet::CBullet(void)
{
	HBITMAP hBuBitmap;
	BITMAP bmp;
	hBuDc = CreateCompatibleDC(hMemDc);
	hBuBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP14));//待修改
	SelectObject(hBuDc, hBuBitmap);
	SetBkColor(hBuDc, RGB(255, 255, 255));
	GetObject(hBuBitmap, sizeof(BITMAP), &bmp);

	hMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hMaskDc, CreateBitmap(bmp.bmWidth, bmp.bmHeight, 1, 1, NULL));
	BitBlt(hMaskDc, 0, 0, bmp.bmWidth, bmp.bmHeight, hBuDc, 0, 0, SRCCOPY);
    Reset();
}
CBullet::~CBullet(void)
{
	DeleteDC(hBuDc);
	DeleteDC(hMaskDc);
}
void CBullet::Draw(void)
{
	if (gameStep == GAME_RUN&& bullet_flag==1)//子弹发射了
	{
		int x = temp[0].x; int y = temp[0].y;
		if (temp[0].visble)
		{
			BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 30, 42, hBuDc, 0, 0, SRCINVERT);
			BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 30, 42, hMaskDc, 0, 0, SRCAND);
			BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 30, 42, hBuDc, 0, 0, SRCINVERT);
		}
	}
}
//刷新子弹
void CBullet::Update(void)
{
	int px, collodeResult;
	if (temp[0].bMove==FALSE&& bullet_flag==1)
	{
		px = player->getX();
		temp[0].x = px + 20;
		temp[0].y = player->getY()+20;
		temp[0].init_x = temp[0].x;//初始坐标
		temp[0].bMove = true;
	}
	for (int i = 0; i <1; i++)
	{
		if (temp[i].life)
		{
			Move(i);
		}
	}
}
//子弹移动
void CBullet::Move(int index)
{
	BULLET mM;
	int bullet_x_speed =10;
	int bullet_y_speed = 0;
	int rd = 0;
	mM = temp[0];
		if (mM.bMove&&bullet_flag ==1)
		{
			if ((mM.x- mM.init_x )<= bullet_distance)//子弹距离足够
			{
					mM.x += bullet_x_speed;//反方向移动
					rd = monster->collideWithMonster(mM.x,mM.y);
					if (rd >= 0)
					{
						monster->killMonster(rd);
						bullet_flag = 0;
						mM.bMove = false;
					}
			}
			else//子弹距离超过了
			{
				mM.bMove = false;
				bullet_flag = 0;//子弹停止移动
			}
		}
	temp[0] = mM;
}
// 重置子弹数据
void CBullet::Reset(void)
{
	temp[0].type = 0;
	temp[0].x = 0;
	temp[0].y = CLIENT_HEIGHT - 80;
	temp[0].life = true;
	temp[0].bMove = false;
	temp[0].visble = true;
}