#include "Monster.h"
#include "Player.h"

extern CPlayer * player;
extern int stage;
extern int bufferX;
extern int bufferY;
extern int mapIndex[2800];
extern int gameStep;
extern int difficulty;
extern HDC hMemDc;
extern HINSTANCE hInstance;

CMonster::CMonster(void)
: monsterNumber(3)
, flatLoop(0)
{
	HBITMAP hMonBitmap;
	BITMAP bmp;
	hMonDc = CreateCompatibleDC(hMemDc);
	hMonBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_MONSTER));
	SelectObject(hMonDc,hMonBitmap);
	SetBkColor(hMonDc,RGB(255,255,255));
	GetObject(hMonBitmap,sizeof(BITMAP),&bmp);

	hMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hMaskDc,CreateBitmap(bmp.bmWidth,bmp.bmHeight,1,1,NULL));
	BitBlt(hMaskDc,0,0,bmp.bmWidth,bmp.bmHeight,hMonDc,0,0,SRCCOPY);

	Reset();
}

CMonster::~CMonster(void)
{
	DeleteDC(hMonDc);
	DeleteDC(hMaskDc);
}

// 绘制怪物
void CMonster::Draw(void)
{
	if (gameStep == GAME_RUN)
	{
		for(int i = 0;i < monsterNumber;i++)
		{
			if(temp[i].visble)
				drawMonster(temp[i].type,temp[i].x,temp[i].y);
			if (temp[i].type == 1)
			{
				flatLoop++;
				if (flatLoop ==2)
				{
					temp[i].visble = false;
					flatLoop = 0;
				}
			}
		}
	}
}

// 画不同种类的怪
void CMonster::drawMonster(int type,int x,int y)
{
	if (type==0)
	{
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,30,42,hMonDc,33*type,0,SRCINVERT);
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,30,42,hMaskDc,33*type,0,SRCAND);
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,30,42,hMonDc,33*type,0,SRCINVERT);
	}
	else if(type==2)
	{
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,25,42,hMonDc,33*type,0,SRCINVERT);
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,25,42,hMaskDc,33*type,0,SRCAND);
		BitBlt(hMemDc,x+bufferX,y+bufferY-12,25,42,hMonDc,33*type,0,SRCINVERT);
	}
	else if (type == 4)
	{
		BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 25, 42, hMonDc, 30 * type, 0, SRCINVERT);
		BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 25, 42, hMaskDc, 30 * type, 0, SRCAND);
		BitBlt(hMemDc, x + bufferX, y + bufferY - 12, 25, 42, hMonDc, 30 * type, 0, SRCINVERT);
	}
	else if(type==1)
	{
		BitBlt(hMemDc, x + bufferX, y + bufferY-12, 30, 42, hMonDc, 33 * type, 0, SRCINVERT);
		BitBlt(hMemDc, x + bufferX, y + bufferY-12, 30, 42, hMaskDc, 33 * type, 0, SRCAND);
		BitBlt(hMemDc, x + bufferX, y + bufferY-12, 30, 42, hMonDc, 33 * type, 0, SRCINVERT);
	}
}

// 刷新怪物
void CMonster::Update(void)
{
	int px,collodeResult;
	px = player->getX();
	if (temp[0].life && px > 125)
	{
		temp[0].bMove = true;
	}
	if (temp[2].life && px > 2400)
	{
		temp[2].bMove = true;
	}
	for (int i = 0;i < monsterNumber;i++)
	{
		if (temp[i].life)
		{
			Move(i);
		}
	}
}

// 怪物移动
void CMonster::Move(int index)
{
	MONTSTER mM;
	int monster_x_speed = 0;
	int monster_y_speed = 0;
	switch (difficulty)
	{
	case 0:
		monster_x_speed = 2;
		monster_y_speed = 4;
		break;
	case 1:
		monster_x_speed = 6;
		monster_y_speed = 8;
		break;
	case 2:
		monster_x_speed = 10;
		monster_y_speed = 12;
		break;
	case 3:
		monster_x_speed = 20;
		monster_y_speed = 16;
		break;
	default:
		break;
	}
	mM = temp[index];
	switch(mM.type)
	{
	case 0:
	case 2:
		if (mM.bMove)
		{
			if(mM.x > -30)
			{
				if (mapIndex[(mM.x+29)/30+(mM.y+30)/30*200] == 0 && mapIndex[(mM.x+5)/30+(mM.y+30)/30*200] == 0 )
				{
					mM.y += monster_y_speed;
					if(mM.y>CLIENT_HEIGHT)
						mM.life = false;
				}
				else 
					mM.x -= monster_x_speed;
			}
			else
			{
				mM.bMove = false;
			}
		}
		break;
	case 4:
		if (mM.bMove)
		{
			if (mM.y<150)
			{
				mM.bMove = false;
			}
			else
				mM.y -= monster_y_speed;
		}
		else
		{
			if (mM.y>CLIENT_HEIGHT-30)
			{
				mM.bMove = true;
			}
			else
				mM.y += monster_y_speed;
		}
		break;
	}
	temp[index] = mM;
}

// 重置怪物数据
void CMonster::Reset(void)
{
	temp[0].type = 0;
	temp[0].x = 690;
	temp[0].y = CLIENT_HEIGHT-210;
	temp[0].life = true;
	temp[0].bMove = false;
	temp[0].visble = true;

	temp[1].type =4;
	temp[1].x = 2070;
	temp[1].y = CLIENT_HEIGHT-30;
	temp[1].life = true;
	temp[1].bMove = true;
	temp[1].visble = true;

	temp[2].type =2;
	temp[2].x = 2700;
	temp[2].y = CLIENT_HEIGHT-90;
	temp[2].life = true;
	temp[2].bMove = false;
	temp[2].visble = (stage != 2);
}

// 与怪物进行碰撞
int CMonster::collideWithMonster(int ix, int iy)
{
	int loop;
	MONTSTER * pTmp;
	for(loop = 0;loop < monsterNumber;loop++)
	{
		pTmp = &temp[loop];
		if (pTmp->visble == false || pTmp->type==1)
		{
			continue;
		}
		if ((ix>=pTmp->x && ix<=pTmp->x+29 && iy>=pTmp->y && iy<=pTmp->y+29) ||
			(ix+16>=pTmp->x && ix+16<=pTmp->x+29 && iy>=pTmp->y && iy<=pTmp->y+29) ||
			(ix+16>=pTmp->x && ix+16<=pTmp->x+29 && iy+29>=pTmp->y && iy+29<=pTmp->y+29) ||
			(ix>=pTmp->x && ix<=pTmp->x+29 && iy+29>=pTmp->y && iy+29<=pTmp->y+29))
		{
			return loop;
		}
	}
	return -1;//未碰撞
}

// 杀死怪物
void CMonster::killMonster(int index)
{
	if (index>=0 && index<monsterNumber)
	{
		if (temp[index].type ==4)
		{
			return;
		}
		PlaySound("humi.wav",NULL,SND_ASYNC);
		temp[index].life = false;
		temp[index].bMove = false;
		if (temp[index].type == 0)
		{
			temp[index].type =1;
		}
		else
			temp[index].visble = false;
	}
}
