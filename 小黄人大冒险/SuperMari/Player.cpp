#include "Player.h"
#include "Scence.h"
#include "Monster.h"
extern void PlayMusic(LPCTSTR file,MCIDEVICEID & m_id);
extern void CloseMusic(MCIDEVICEID m_id);
extern void PauseMusic(MCIDEVICEID m_id);
extern void StopMusic(MCIDEVICEID m_id);
extern int mapIndex[2800];
extern int gameStep;
extern HDC hMemDc;
extern HINSTANCE hInstance;
extern MCIDEVICEID back_id;
extern CScence * scence;
extern CMonster * monster;
extern int stage;
extern int accelerate_count;//加速剂个数
extern int blind_count;//复明剂个数
extern int protect_count;//保护剂个数
extern int life_count;//生命剂个数
extern int bullet_number;//子弹数目
extern bool bullet_flag;//子弹的发射标志位
int bufferY;
int bufferX;//滚屏缓冲距离
int difficulty = 0;
int accelerate_time;// 加速维持时间
int blind_time;// 致盲时间
bool blind_flag = 0;//不致盲
int lifetime =1;//一关的生命数
int protecttime = 0;//保护罩维持时间数
int seed = 0;//随机数种子
int out_type = 0;//问号箱子的种类
bool Monster_Collide_flag = 0;//置1表示和怪物碰撞且依旧有生命值
int coin;
CPlayer::CPlayer()
: animalLoop(0)
, dltaXLoop(0)
{
	hDc = CreateCompatibleDC(hMemDc);
	hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_PLAYER));
	SelectObject(hDc,hBitmap);
	SetBkColor(hDc,RGB(0,0,255));
	BITMAP bmp;
	GetObject(hBitmap,sizeof(BITMAP),&bmp);
	hMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hMaskDc,CreateBitmap(bmp.bmWidth,bmp.bmHeight,1,1,NULL));
	BitBlt(hMaskDc,0,0,bmp.bmWidth,bmp.bmHeight,hDc,0,0,SRCCOPY);

	lifeNumber = 3;
	accelerate_time = 0;//无加速时间
}
CPlayer::~CPlayer(void)
{
	DeleteDC(hMaskDc);
	DeleteDC(hDc);
	DeleteObject(hBitmap);
}

int CPlayer::getX()
{
	return x;
}
int CPlayer::getY()
{
	return y;
}
int CPlayer::getdeltaX()
{
	return dltaX;
}
void CPlayer::Update()
{
	switch(gameStep)
	{
	case GAME_MAIN:
		x = 125;
		bufferX = 0;
		break;
	case GAME_END:
		if(x<MAP_WIDTH-CLIENT_WIDTH/2+90)
			x++;
		else if(x>MAP_WIDTH-CLIENT_WIDTH/2+90)
			x--;
		frame = 18;
		break;
	case GAME_DIE:
		frame = 19;
		if (y<CLIENT_HEIGHT)
		{
			y += 8;
		}
		break;
	case GAME_RUN:
		if (accelerate_time > 0)
		{
			switch (difficulty)
			{
			case 0:
				speed = speed_degree_1*2;//简单
				break;
			case 1:
				speed = speed_degree_2*4;//中等
				break;
			case 2:
				speed = speed_degree_3*6;//困难
				break;
			case 3:
				speed = speed_degree_4*8;//疯狂
				break;
			}
		}
		if (accelerate_time <= 0)
		{
			switch (difficulty)
			{
			case 0:
				speed = speed_degree_1;//简单
				break;
			case 1:
				speed = speed_degree_2;//中等
				break;
			case 2:
				speed = speed_degree_3;//困难
				break;
			case 3:
				speed = speed_degree_4;//疯狂
				break;
			}
		}
		if (blind_time > 0)
		{
			blind_flag = 1;//致盲标志位开启
		}
		if (blind_time <= 0)
		{
			blind_flag = 0;//致盲标志位关闭
		}
		moveMari();
		MariAnimal();
		if (x<=CLIENT_WIDTH/2)
			bufferX = 0;
		else if (x >= MAP_WIDTH-CLIENT_WIDTH/2)
		{
			bufferX = CLIENT_WIDTH-MAP_WIDTH;
			if (bLanded)
			{
				if (stage<2)
				{
					stage++;
					gameStep = GAME_END;
				}else
					gameStep = GAME_WIN;
			}
		}
		else 
			bufferX = CLIENT_WIDTH/2-x;
		if (y<0)
		{
			bufferY = -y;
		}else
			bufferY = 0;
		break;
	}
}

void CPlayer::Draw()
{
	switch(gameStep)
	{
	case GAME_MAIN:
		scence->drawPlayer(125,330,0);
		break;
	case GAME_END:
	case GAME_PAUSE:
	case GAME_DIE:
	case GAME_RUN:
		char coinS[8];
		sprintf(coinS,":%d",coin);
		COLORREF oldColor;
		oldColor = SetTextColor(hMemDc,0X00FFFF);
		TextOut(hMemDc,30,7,coinS,strlen(coinS));
		sprintf(coinS, ":%d", accelerate_time);
		TextOut(hMemDc,30, 37, coinS, strlen(coinS));
		sprintf(coinS, ":%d", blind_time);
		TextOut(hMemDc, 80, 7, coinS, strlen(coinS));
		sprintf(coinS, ":%d", lifetime);
		TextOut(hMemDc, 80, 37, coinS, strlen(coinS));
		sprintf(coinS, ":%d", protecttime);
		TextOut(hMemDc, 130, 7, coinS, strlen(coinS));
		sprintf(coinS, ":%d", bullet_number);
		TextOut(hMemDc, 130, 37, coinS, strlen(coinS));
		SetTextColor(hMemDc, oldColor);
		if (blind_flag == 0)
		{
			scence->drawPlayer(x + bufferX, y + bufferY,frame);
		}
		break;
	}
}

void  CPlayer::keyDown(WPARAM wparam)
{
	switch(wparam)
	{
	case VK_RIGHT:
	case 'D':
		bRightKey = true;
		if (dltaX >= 0)
		{
			direction = 1;
		}
		break;
	case VK_LEFT:
	case 'A':
		bLeftKey = true;
		if (dltaX <= 0)
		{
			direction = -1;
		}
		break;
	case VK_UP:
	case 'W':
		bUpKey = true;
		break;
	case '1':
		if (accelerate_count > 0)
		{
			accelerate_count -= 1;
			accelerate_time += 5;
		}
		else if ((coin - 2) >= 0)
		{
			coin -= 2;
			accelerate_time += 5;
		}
		break;
	case '2':
		if (blind_count > 0)
		{
			blind_count -= 1;
			blind_time -= 5;
		}
		else if ((coin - 3) >= 0)
		{
			coin -= 3;
			blind_time -= 5;
			if (blind_time < 0)
				blind_time = 0;
		}
		break;
	case '3':
		if (life_count > 0)
		{
			life_count -= 1;
			lifetime++;
		}
		else if ((coin - 2) >= 0)
		{
			coin -= 2;
			lifetime++;
		}
		break;
	case '4':
		if (protect_count > 0)
		{
			protect_count -= 1;
			protecttime += 5;
		}
		else if ((coin - 3) >= 0)
		{
			coin -= 3;
			protecttime += 5;
		}
		break;
	case '5':
		if ((coin - 2) > 0)
		{
			coin -= 2;
			bullet_number += 1;
		}
		break;
	case VK_SPACE://按下空格键,发射子弹
		if (bullet_number > 0 && bullet_flag == 0)
		{
			bullet_number--;
			bullet_flag = 1;//发射子弹
		}
		break;
	case VK_CONTROL:
		bControlKey = true;
		break;
	}
}

void  CPlayer::keyUp(WPARAM wparam)
{
	switch(wparam)
	{
	case VK_RIGHT:
	case 'D':
		bRightKey = false;
		break;
	case VK_LEFT:
	case 'A':
		bLeftKey = false;
		break;
	case VK_CONTROL:
		bControlKey = false;
		break;
	case VK_UP:
	case 'W':
		bUpKey = false;
		break;
	}
}

// 移动玛丽
void CPlayer::moveMari(void)
{
	if (bUpKey)
	{
		if (!bFalling && !bRising)
		{
			g = 10;
			bRising = true;
			bLanded = false;
			PlaySound("jump.wav",NULL,SND_ASYNC);
		}
		else if (bRising && g>8)
		{
			_g = 6;
		}
	}
	else
	{
		_g=0;
	}
	if (bRising)
	{
		mariRising();
	}
	else
	{
		mariFalling();
	}
	if(y>CLIENT_HEIGHT)
	{
		y = CLIENT_HEIGHT;
		killMari();//玩家摔死
		return;	
	}
	walk();
}

// 玩家上升函数
void CPlayer::mariRising(void)
{
	int i,ru,lu,cu;
	bool bCoin;//是否碰到金币
	bCoin = false;
	daltY = 0;
	for (i=0; i< g+_g; i++)
	{
		daltY--;
		if (y+daltY < 0)
		{
			continue;
		}
		ru = (x+12)/30+((y+daltY)/30)*200;
		lu = (x+3)/30+((y+daltY)/30)*200;
		 
		if(mapIndex[ru] != 0  || mapIndex[lu] != 0)
		{
			cu = (x+7)/30+((y+daltY)/30)*200;
			switch(mapIndex[cu])
			{
			case 1:
			case 9:
			case 17:
				mapIndex[cu] = 0;
				PlaySound("brockbreak.wav",NULL,SND_ASYNC);
				scence->boom(cu%200*30,cu/200*30);
				break;
			case 2:
			case 10:
			case 18:
				seed = GetTickCount();
				srand(seed);
				seed=rand()%10;
				mapIndex[cu] = 3;
				if (seed ==2||seed==4)
				{
					coin++;
					out_type =15;//种类为金币
				}
				if (seed == 0 || seed == 1)
				{
					accelerate_time += 10;
					out_type = 7;
                }
				PlaySound("coin.wav", NULL, SND_ASYNC);
				scence->coinOut(cu % 200 * 30, cu / 200 * 30);
				if (seed == 3 || seed == 5||seed==7)
				{
					blind_time += 5;
					out_type = 8;
				}
				if (seed == 8 || seed == 9)
				{
					lifetime += 1;
					out_type = 32;
				}
				if (seed == 6)
				{
					protecttime += 5;
					out_type = 33;
				}
				break;
			case 15:
				bCoin = true;
				getCoin(cu);
				break;
			case 7:
				getSpeed(cu);
				break;
			case 8:
				getBlind(cu);
				break;
			case 32:
				getLifetime(cu);
				break;
			case 33:
				getProtecttime(cu);
				break;
			default:
				break;
			}
			if (bCoin)
			{
				bCoin = false;
				break;
			}
			daltY++;
			g = 0;
			bFalling = true;
			bRising = false;
			break;
		}
	}
	if (g>0)
	{
		g--;
	} 
	else if(g == 0)
	{
		if (_g == 0)
		{
			bFalling = true;
			bRising = false;
		}else
			_g--;
	}
	y += daltY;
}

// 玩家下落过程
void CPlayer::mariFalling(void)
{
	int i,ld,rd;
	daltY = 0;
	for (i=0; i< g; i++)
	{
		daltY++;
		if (g>1)
		{
			rd = monster->collideWithMonster(x,y+daltY);
			if (rd >= 0)
			{
				monster->killMonster(rd);//踩死怪物
			}
		}
		rd = (x+12)/30+((y+29+daltY)/30)*200;
		ld = (x+3)/30+((y+29+daltY)/30)*200;
		if(0<y+29+daltY && (mapIndex[ld] != 0  || mapIndex[rd] != 0 || scence->collideWithHose(x+3,y+29+daltY)!=0 || scence->collideWithHose(x+12,y+29+daltY)!=0))
		{
			switch (mapIndex[ld])
			{
				case 15:
					if (g>1)
					{
						getCoin(ld);
					}
					continue;
				break;
				case 7:
					if (g > 1)
					{
						getSpeed(ld);
					}
					continue;
				break;
				case 8:
					if (g > 1)
					{
						getBlind(ld);
					}
					continue;
					break;
				case 32:
					if (g > 1)
					{
						getLifetime(ld);
					}
					continue;
					break;
				case 33:
					if (g > 1)
					{
						getProtecttime(ld);
					}
					continue;
					break;
				default:
					break;
			}
			switch (mapIndex[rd])
			{
			case 15:
				if (g>1)
				{
					getCoin(rd);
				}
				continue;
				break;
			case 7:
				if (g > 1)
				{
					getSpeed(rd);
				}
				continue;
				break;
			case 8:
				if (g > 1)
				{
					getBlind(rd);
				}
				continue;
				break;
			case 32:
				if (g > 1)
				{
					getLifetime(rd);
				}
				continue;
				break;
			case 33:
				if (g > 1)
				{
					getProtecttime(rd);
				}
			continue;
			break;
			default:
				break;
			}
			daltY--;
			bFalling = false;
			bLanded = true;
			g = 0;
			break;
		}
		bFalling = true;
	}
	g++;
	y += daltY;
}

//水平移动函数
void CPlayer::walk()
{
	if(dltaXLoop==1)
	{
		if(bLeftKey && !bRightKey)
		{
			if(bControlKey)
			{
				if(dltaX > -speed*2)
				{
					dltaX--;
				}
			}
			else
			{
				if (dltaX < -speed)
				{
					dltaX++;
				}
				else if (dltaX > -speed)
				{
					dltaX--;
				}
			}
		}
		else if(bRightKey && !bLeftKey)
		{
			if (bControlKey)
			{
				if (dltaX < speed*2)
				{
					dltaX++;
				}
			}
			else
			{
				if(dltaX < speed)
				{
					dltaX++;
				}
				else if(dltaX > speed)
				{
					dltaX--;
				}
			}
		}
		else if ((!bRightKey && !bLeftKey) || (bRightKey && bLeftKey))
		{
			if (dltaX<0)
				dltaX++;
			else if(dltaX>0)
				dltaX--;
		}
	}
	collide();
	x += dltaX;
	dltaXLoop = (dltaXLoop+1)%3;
}

// 设置玛丽动画
void CPlayer::MariAnimal(void)
{
	if (bLanded)
	{
		animalLoop = (animalLoop+1)%2;
		if(animalLoop == 1)
		{
			if(dltaX>0)
			{
				if(dltaX>=speed)
					frame = (frame+1)%4;
				else
					frame = (frame+1)%4+4;
			}
			else if(dltaX<0)
			{
				if(dltaX<=-speed)
					frame = (frame+1)%4+8;
				else
					frame = (frame+1)%4+12;
			}
			else if(dltaX==0)
			{
				if(direction == 1)
				{
					frame = 0;
				}
				else if (direction == -1)
				{
					frame = 15;
				}
			}
		}
	}
	else
	{
		if (direction == -1)
		{
			frame = 17;
		}
		else if (direction == 1)
		{
			frame = 16;
		}
	}
}

// 处理玛丽的水平碰撞
void CPlayer::collide(void)
{
	int cu;
	cu = monster->collideWithMonster(x+dltaX,y);
	if (cu >= 0&& Monster_Collide_flag==0&&protecttime==0)//且未和怪物碰撞过
	{
		lifetime--;
		Monster_Collide_flag = 1;
		return;
	}
	if (Monster_Collide_flag == 1 && cu < 0)
		Monster_Collide_flag = 0;
	if (lifetime == 0)
	{
		killMari(); //被怪碰到撞死
	}
	if(x<0)
		x=0;
	else if(x+16>MAP_WIDTH)
		x=MAP_WIDTH-16;
	if (y+29 >= 0)
	{
		if(dltaX>0)
		{
			while(mapIndex[(x+15+dltaX)/30+(y/30)*200] != 0  || mapIndex[(x+15+dltaX)/30+((y+29)/30)*200] != 0 ||
				scence->collideWithHose(x+15+dltaX,y)!=0 || scence->collideWithHose(x+15+dltaX,y+29)!=0)
			{
				cu = (x+15+dltaX)/30+((y+29)/30)*200;
				if (mapIndex[cu] == 15)
				{
					getCoin(cu);
					break;
				}
				if (mapIndex[cu] == 7)
				{
					getSpeed(cu);
					break;
				}
				if (mapIndex[cu] == 8)
				{
					getBlind(cu);
					break;
				}
				if (mapIndex[cu] == 32)
				{
					getLifetime(cu);
					break;
				}
				if (mapIndex[cu] == 33)
				{
					getProtecttime(cu);
					break;
				}
				cu = (x+15+dltaX)/30+(y/30)*200;
				if (mapIndex[cu] == 15)
				{
					getCoin(cu);
					break;
				}
				if (mapIndex[cu] == 7)
				{
					getSpeed(cu);
					break;
				}
				if (mapIndex[cu] == 8)
				{
					getBlind(cu);
					break;
				}
				if (mapIndex[cu] == 32)
				{
					getLifetime(cu);
					break;
				}
				if (mapIndex[cu] == 33)
				{
					getProtecttime(cu);
					break;
				}
				dltaX--;
			}
		}else if (dltaX<0)
		{
			while(mapIndex[(x+dltaX)/30+(y/30)*200] != 0  || mapIndex[(x+dltaX)/30+((y+29)/30)*200] != 0 ||
				scence->collideWithHose(x+dltaX,y)!=0 || scence->collideWithHose(x+dltaX,y+29)!=0)
			{
				cu = (x+dltaX)/30+(y/30)*200;
				if (mapIndex[cu] == 15)
				{
					getCoin(cu);
					break;
				}
				if (mapIndex[cu] == 7)
				{
					getSpeed(cu);
					break;
				}
				if (mapIndex[cu] == 8)
				{
					getBlind(cu);
					break;
				}
				if (mapIndex[cu] == 32)
				{
					getLifetime(cu);
					break;
				}
				if (mapIndex[cu] == 33)
				{
					getProtecttime(cu);
					break;
				}
				cu = (x+dltaX)/30+((y+29)/30)*200;
				if (mapIndex[cu] == 15)
				{
					getCoin(cu);
					break;
				}
				if (mapIndex[cu] == 7)
				{
					getSpeed(cu);
					break;
				}
				if (mapIndex[cu] == 7)
				{
					getBlind(cu);
					break;
				}
				if (mapIndex[cu] == 32)
				{
					getLifetime(cu);
					break;
				}
				if (mapIndex[cu] == 33)
				{
					getProtecttime(cu);
					break;
				}
				dltaX++;
				//x++;
			}
		}
	}
}
// 重置玩家数据
bool CPlayer::Reset(void)
{
	if (lifeNumber==0)
	{
		return false;
	}
	else
	{
		//x = x/CLIENT_WIDTH*CLIENT_WIDTH+125;
		if(stage == 2)
		{
			x = 30;
			y = 90;
		}
		else
		{
			x = 125;
			y = 330;
		}
		dltaX = 0;
		daltY = 0;
		bRising = false;
		bFalling = false;
		bLanded = true;
		bLeftKey = false;
		bRightKey =false;
		bUpKey = false;
		bFalling = false;
		bControlKey = false;
		g = 0;
		_g = 0;
		frame = 0;
		direction = 0;
		switch (difficulty)
		{
		case 0:
			speed = speed_degree_1;//简单
			break;
		case 1:
			speed = speed_degree_2;//中等
			break;
		case 2:
			speed = speed_degree_3;//困难
			break;
		case 3:
			speed = speed_degree_4;//疯狂
			break;
		}
		return true;
	}
}
// 播放金币声音
void CPlayer::getCoin(int index)
{
	coin++;
	mapIndex[index] = 0;
	PlaySound("coin.wav",NULL,SND_ASYNC);
}
void CPlayer::getSpeed(int index)
{
	accelerate_time+=10;//增加10秒加速时间
	mapIndex[index] = 0;//图标消失
}
void CPlayer::getBlind(int index)
{
	blind_time += 5;
	mapIndex[index] = 0;
}
void CPlayer::getLifetime(int index)
{
	lifetime++;
	mapIndex[index] = 0;
}
void CPlayer::getProtecttime(int index)
{
	protecttime += 5;
	mapIndex[index] = 0;
}
// 玩家死亡
void CPlayer::killMari(void)
{
	PauseMusic(back_id);
	PlaySound("mock.wav",NULL,SND_ASYNC);
	if(y<CLIENT_HEIGHT)
	{
		y -= 10;
	}
	lifeNumber--;
	if (lifeNumber == 0)
	{
		gameStep = GAME_LOSE;
	}
	else
	{
		gameStep = GAME_DIE;
	}
}

