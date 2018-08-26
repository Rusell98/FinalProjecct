#include "Scence.h"
int mapIndex[2800];
extern int gameStep;
extern HDC hMemDc;
extern HINSTANCE hInstance;
extern CPlayer * player;
extern int bufferX;
extern int bufferY;
extern int stage;
extern int begin_count;
extern int begin_second_count;//二级菜单编号
extern int difficulty_degree;//难度
extern int begin_choose_count;
extern int music_switch;//音乐开关 1:开 -1：关
extern int out_type;
extern MCIDEVICEID back_id;
extern void PlayMusic(LPCTSTR file, MCIDEVICEID & m_id);
extern void CloseMusic(MCIDEVICEID m_id);
extern	int coin;
extern int accelerate_count;//加速剂个数
extern int blind_count;//复明剂个数
extern int protect_count;//保护剂个数
extern int life_count;//生命剂个数
extern int bullet_shop_number;//商店购买的子弹数
CScence::CScence()
: loopQues(0)
, dieLoop(0)
, loopCoin(0)
{	
	HBITMAP hBitmap,hWallBit,hTitleBit,hBeginBit,hCursorBit,hDifficultyBit,hLevelBit,hSetupBit,hSwitchBit,hSwitchoffBit,hCoinBit,hBlindBit,hDieBit,hOverBit,hPlayerBit,hBulletBit;//场景bmp句柄
	HBITMAP hSpeedBit, hLifetimeBit,hProtectBit,hShopBit;
	BITMAP bmp,coinBmp;
	hDc = CreateCompatibleDC(hMemDc);
	hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SENCE));
	SelectObject(hDc,hBitmap);
	SetBkColor(hDc,RGB(0,0,255));
	GetObject(hBitmap,sizeof(BITMAP),&bmp);
	hMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hMaskDc,CreateBitmap(bmp.bmWidth,bmp.bmHeight,1,1,NULL));
	BitBlt(hMaskDc,0,0,bmp.bmWidth,bmp.bmHeight,hDc,0,0,SRCCOPY);

	hWallDc = CreateCompatibleDC(hMemDc);
	hWallBit = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_WALL));
	SelectObject(hWallDc,hWallBit);

	hTitleDc = CreateCompatibleDC(hMemDc);
	hTitleBit = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_TITLE));
	SelectObject(hTitleDc,hTitleBit);
	GetObject(hTitleBit,sizeof(BITMAP),&titleBmp);

	hCursorDc = CreateCompatibleDC(hMemDc);
	hCursorBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	SelectObject(hCursorDc, hCursorBit);
	GetObject(hCursorBit, sizeof(BITMAP), &CursorBmp);

	hBeginDc = CreateCompatibleDC(hMemDc);
	hBeginBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	SelectObject(hBeginDc, hBeginBit);
	GetObject(hBeginBit, sizeof(BITMAP), &BeginBmp);

	hDifficultyDc = CreateCompatibleDC(hMemDc);
	hDifficultyBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	SelectObject(hDifficultyDc, hDifficultyBit);
	GetObject(hDifficultyBit, sizeof(BITMAP), &DifficultyBmp);

	hLevelDc = CreateCompatibleDC(hMemDc);
	hLevelBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
	SelectObject(hLevelDc, hLevelBit);
	GetObject(hLevelBit, sizeof(BITMAP), &LevelBmp);

	hSetupDc = CreateCompatibleDC(hMemDc);
	hSetupBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5));
	SelectObject(hSetupDc, hSetupBit);
	GetObject(hSetupBit, sizeof(BITMAP), &SetupBmp);

	hShopDc = CreateCompatibleDC(hMemDc);
	hShopBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8));
	SelectObject(hShopDc, hShopBit);
	GetObject(hShopBit, sizeof(BITMAP), &ShopBmp);

	hSwitchDc = CreateCompatibleDC(hMemDc);
	hSwitchBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP6));
	SelectObject(hSwitchDc, hSwitchBit);
	GetObject(hSwitchBit, sizeof(BITMAP), &SwitchBmp);
    
	hSwitchoffDc = CreateCompatibleDC(hMemDc);
	hSwitchoffBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7));
	SelectObject(hSwitchoffDc, hSwitchoffBit);
	GetObject(hSwitchoffBit, sizeof(BITMAP), &SwitchoffBmp);

	hSpeedDc = CreateCompatibleDC(hMemDc);
	hSpeedBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP9));
	SelectObject(hSpeedDc, hSpeedBit);
	GetObject(hSpeedBit, sizeof(BITMAP), &SpeedBmp);

	hBlindDc = CreateCompatibleDC(hMemDc);
	hBlindBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP10));
	SelectObject(hBlindDc, hBlindBit);
	GetObject(hBlindBit, sizeof(BITMAP), &BlindBmp);

	hLifetimeDc = CreateCompatibleDC(hMemDc);
	hLifetimeBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP11));
	SelectObject(hLifetimeDc, hLifetimeBit);
	GetObject(hLifetimeBit, sizeof(BITMAP), &LifetimeBmp);

	hProtectDc = CreateCompatibleDC(hMemDc);
	hProtectBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP12));
	SelectObject(hProtectDc, hProtectBit);
	GetObject(hProtectBit, sizeof(BITMAP), &ProtectBmp);

	hBulletDc = CreateCompatibleDC(hMemDc);
	hBulletBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP14));
	SelectObject(hBulletDc, hBulletBit);
	GetObject(hBulletBit, sizeof(BITMAP), &BulletBmp);

	hDieDc = CreateCompatibleDC(hMemDc);
	hDieBit = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_DIE));
	SelectObject(hDieDc,hDieBit);
	GetObject(hDieBit,sizeof(BITMAP),&dieBmp);

	hOverDc = CreateCompatibleDC(hMemDc);
	hOverBit = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_GAMEOVER));
	SelectObject(hOverDc,hOverBit);
	GetObject(hOverBit,sizeof(BITMAP),&overBmp);

	hCoinDC = CreateCompatibleDC(hMemDc);
	hCoinBit = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_COIN));
	SelectObject(hCoinDC,hCoinBit);
	GetObject(hCoinBit,sizeof(BITMAP),&coinBmp);

	hPlayerDc = CreateCompatibleDC(hMemDc);
	hPlayerBit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_PLAYER));
	SelectObject(hPlayerDc, hPlayerBit);
	GetObject(hPlayerBit, sizeof(BITMAP), &PlayerBmp);

	hPlayerMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hPlayerMaskDc, CreateBitmap(PlayerBmp.bmWidth, PlayerBmp.bmHeight, 1, 1, NULL));
	BitBlt(hPlayerMaskDc, 0, 0, PlayerBmp.bmWidth, PlayerBmp.bmHeight, hPlayerDc, 0, 0, SRCCOPY);

	hCoinMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hCoinMaskDc,CreateBitmap(coinBmp.bmWidth,coinBmp.bmHeight,1,1,NULL));
	BitBlt(hCoinMaskDc,0,0,coinBmp.bmWidth,coinBmp.bmHeight,hCoinDC,0,0,SRCCOPY);

	hSpeedMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hSpeedMaskDc, CreateBitmap(SpeedBmp.bmWidth, SpeedBmp.bmHeight, 1, 1, NULL));
	BitBlt(hSpeedMaskDc, 0, 0, SpeedBmp.bmWidth, SpeedBmp.bmHeight, hSpeedDc, 0, 0, SRCCOPY);

	hBlindMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hBlindMaskDc, CreateBitmap(BlindBmp.bmWidth, BlindBmp.bmHeight, 1, 1, NULL));
	BitBlt(hBlindMaskDc, 0, 0, BlindBmp.bmWidth, BlindBmp.bmHeight, hBlindDc, 0, 0, SRCCOPY);

	hLifetimeMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hLifetimeMaskDc, CreateBitmap(LifetimeBmp.bmWidth, LifetimeBmp.bmHeight, 1, 1, NULL));
	BitBlt(hLifetimeMaskDc, 0, 0, LifetimeBmp.bmWidth, LifetimeBmp.bmHeight, hLifetimeDc, 0, 0, SRCCOPY);

	hProtectMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hProtectMaskDc, CreateBitmap(ProtectBmp.bmWidth, ProtectBmp.bmHeight, 1, 1, NULL));
	BitBlt(hProtectMaskDc, 0, 0, ProtectBmp.bmWidth, ProtectBmp.bmHeight, hProtectDc, 0, 0, SRCCOPY);

	hBulletMaskDc = CreateCompatibleDC(hMemDc);
	SelectObject(hBulletMaskDc, CreateBitmap(BulletBmp.bmWidth, BulletBmp.bmHeight, 1, 1, NULL));
	BitBlt(hBulletMaskDc, 0, 0, BulletBmp.bmWidth, BulletBmp.bmHeight, hBulletDc, 0, 0, SRCCOPY);

	titleRect.bottom = CLIENT_HEIGHT/3+65;
	titleRect.left = (CLIENT_WIDTH-titleBmp.bmWidth)/2+40;
	titleRect.right = titleRect.left+5;
	titleRect.top = CLIENT_HEIGHT/3;

	DeleteObject(hWallBit);
	DeleteObject(hBitmap);
	DeleteObject(hTitleBit);
	DeleteObject(hDieBit);
	DeleteObject(hOverBit);
	Reset();
}
CScence::~CScence()
{
	DeleteDC(hMaskDc);
	DeleteDC(hDc);
	DeleteDC(hWallDc);
}
//绘制场景自己
void CScence::Draw()
{
	switch(gameStep)
	{
	case GAME_MAIN:
		FillRect(hMemDc,&titleRect, CreateSolidBrush(RGB(160,180,250)));
		switch (begin_choose_count)
		{
		    case 0:
			BitBlt(hMemDc, (CLIENT_WIDTH - BeginBmp.bmWidth) / 2, CLIENT_HEIGHT / 6, BeginBmp.bmWidth, BeginBmp.bmHeight, hBeginDc, 0, 0, SRCCOPY);
			drawCursor(360, 107 + begin_count * 27);
			break;
			case 1:
			BitBlt(hMemDc, (CLIENT_WIDTH - DifficultyBmp.bmWidth) / 2, CLIENT_HEIGHT / 6, DifficultyBmp.bmWidth, DifficultyBmp.bmHeight, hDifficultyDc, 0, 0, SRCCOPY);
			drawCursor(360, 72+ begin_second_count * 31);
			break;
			case 2:
			BitBlt(hMemDc, (CLIENT_WIDTH - LevelBmp.bmWidth) / 2, CLIENT_HEIGHT / 6, LevelBmp.bmWidth, LevelBmp.bmHeight, hLevelDc, 0, 0, SRCCOPY);
			drawCursor(360, 72 + begin_second_count * 22);
			break;
			case 3:
			BitBlt(hMemDc, (CLIENT_WIDTH - SetupBmp.bmWidth) / 2, CLIENT_HEIGHT / 6, SetupBmp.bmWidth, SetupBmp.bmHeight, hSetupDc, 0, 0, SRCCOPY);
			drawCursor(360, 72 + begin_second_count * 37);
			if (music_switch == 1)
			{
				PlayMusic("back_music.mp3", back_id);
				BitBlt(hMemDc, 280, CLIENT_HEIGHT / 6, 30, 30, hSwitchDc, 0, 0, SRCCOPY);
			}
			if (music_switch == -1)
			{
				CloseMusic(back_id);
				BitBlt(hMemDc, 280, CLIENT_HEIGHT / 6, 30, 30, hSwitchoffDc, 0, 0, SRCCOPY);
			}
			break;
			case 4:
			break;
			case 5:
			char coinS[12];
			BitBlt(hMemDc, (CLIENT_WIDTH - ShopBmp.bmWidth) / 2, CLIENT_HEIGHT / 6, ShopBmp.bmWidth, ShopBmp.bmHeight, hShopDc, 0, 0, SRCCOPY);
			sprintf(coinS, ":%d", coin);
			TextOut(hMemDc, 350, 80, coinS, strlen(coinS));
			sprintf(coinS, "%d", accelerate_count);
			TextOut(hMemDc, 300, 115, coinS, strlen(coinS));
			sprintf(coinS, "%d", life_count);
			TextOut(hMemDc, 300, 150, coinS, strlen(coinS));
			sprintf(coinS, "%d", protect_count);
			TextOut(hMemDc, 300, 185, coinS, strlen(coinS));
			sprintf(coinS, "%d", blind_count);
			TextOut(hMemDc, 300, 220, coinS, strlen(coinS));
			sprintf(coinS, "%d",bullet_shop_number);
			TextOut(hMemDc, 300, 255, coinS, strlen(coinS));
			drawCursor(360, 110 + begin_second_count * 35);
			break;
		}
        titleRect.left = titleRect.right>(CLIENT_WIDTH-titleBmp.bmWidth)/2+330 ? (CLIENT_WIDTH-titleBmp.bmWidth)/2+40 : titleRect.left+5;
		titleRect.right = titleRect.left+5;

		drawGrass(CLIENT_WIDTH/2,SKYLINE);
		drawHill(CLIENT_WIDTH-150,SKYLINE);
		drawCloud(CLIENT_WIDTH-200,30);
		for (int i = 0;i*30<CLIENT_WIDTH;i++)
		{
			drawWall(30*i,CLIENT_HEIGHT-30,5);
			drawWall(30*i,CLIENT_HEIGHT-60,4);
		}
		break;
	case GAME_END:
		TextOut(hMemDc,CLIENT_WIDTH/2,CLIENT_HEIGHT/2,"恭喜过关",strlen("恭喜过关"));
		break;
	case GAME_LOSE:
		dieLoop = (dieLoop+1)%20;
		if (dieLoop <10)
		{
			BitBlt(hMemDc,(CLIENT_WIDTH-overBmp.bmWidth)/2,CLIENT_HEIGHT/3,overBmp.bmWidth,overBmp.bmHeight/2,hOverDc,0,0,SRCCOPY);
		}else
			BitBlt(hMemDc,(CLIENT_WIDTH-overBmp.bmWidth)/2,CLIENT_HEIGHT/3,overBmp.bmWidth,overBmp.bmHeight/2,hOverDc,0,overBmp.bmHeight/2,SRCCOPY);
		break;
	case GAME_PAUSE:
		TextOut(hMemDc,CLIENT_WIDTH/2,CLIENT_HEIGHT/2,"游戏暂停",strlen("游戏暂停"));
		goto run;
	case GAME_DIE:
		dieLoop = (dieLoop+1)%20;
		if (dieLoop <10)
		{
			BitBlt(hMemDc,(CLIENT_WIDTH-dieBmp.bmWidth)/2,CLIENT_HEIGHT/3,dieBmp.bmWidth,dieBmp.bmHeight/2,hDieDc,0,0,SRCCOPY);
		}else
			BitBlt(hMemDc,(CLIENT_WIDTH-dieBmp.bmWidth)/2,CLIENT_HEIGHT/3,dieBmp.bmWidth,dieBmp.bmHeight/2,hDieDc,0,dieBmp.bmHeight/2,SRCCOPY);
		//break;
run:
	case GAME_RUN:
		if(stage == 0)//是第一关
		{
			drawHill(MAP_WIDTH-150,SKYLINE);
			drawCloud(CLIENT_WIDTH+200,30);
			drawGrass(200,CLIENT_HEIGHT-60);
			drawTree(400,CLIENT_HEIGHT-60);
			drawHose(2050, CLIENT_HEIGHT - 60, 2);//画水管
			drawFlag(MAP_WIDTH-CLIENT_WIDTH+150,CLIENT_HEIGHT-60);		//旗子
			drawTemple(MAP_WIDTH-CLIENT_WIDTH/2+50,CLIENT_HEIGHT-60);//终点塔
		}
		if(stage==1)
			drawHose(2050, CLIENT_HEIGHT - 60, 2);//画水管
		if(stage==2)
			drawHose(2050, CLIENT_HEIGHT - 30, 2);//画水管
		for (int i = 0;i < 2800;i++)
		{
			switch (mapIndex[i])
			{
			    case 7:
				drawSpeed(i % 200 * 30, i / 200 * 30);
				break;
				case 8:
				drawBlind(i % 200 * 30, i / 200 * 30);
				break;
				case 15:
				drawCoin(i % 200 * 30, i / 200 * 30, loopCoin);
				break;
				case 32:
				drawLife(i % 200 * 30, i / 200 * 30);
				break;
				case 33:
				drawProtect(i % 200 * 30, i / 200 * 30);
				break;
				default:
				drawWall(i % 200 * 30, i / 200 * 30, mapIndex[i] - 1);
				break;
			}
		}
		drawCoin(-bufferX,0-bufferY,4);//画金币计数处的金币
		drawSpeed(-bufferX,30- bufferY);
		drawBlind(50 - bufferX, 0 - bufferY);
		drawLife(50 - bufferX, 30 - bufferY);
		drawProtect(100 - bufferX, 0 - bufferY);
		drawBullet(105-bufferX, 35-bufferY);
		if (outCoin.frame < 4)
		{
		switch (out_type)
		 {
		    case 15:
			drawCoin(outCoin.x, outCoin.y, outCoin.frame);
			outCoin.frame++;
			break;
		case 7:
			drawSpeed(outCoin.x, outCoin.y);
			outCoin.frame++;
			break;
		case 8:
			drawBlind(outCoin.x, outCoin.y);
			outCoin.frame++;
			break;
		case 32:
			drawLife(outCoin.x, outCoin.y);
			outCoin.frame++;
			break;
		case 33:
			drawProtect(outCoin.x, outCoin.y);
			outCoin.frame++;
			break;
		default:
             break;
		 }
		}
        /************************************************************************/
		/* 以下为画砖块被撞碎效果                                  */
		/************************************************************************/
		SMALL_WALL * pTmp, * pLast;
		pTmp = head;
		pLast = NULL;
		while(pTmp)
		{
			for (int i = 0;i < 4;i++)
			{
				switch (stage)
				{
				case 0:
					BitBlt(hMemDc, pTmp->x[i] + bufferX, pTmp->y[i] + bufferY, pTmp->frame + 5, pTmp->frame + 5, hWallDc, 0, 0, SRCCOPY);
					break;
				case 1:
					BitBlt(hMemDc, pTmp->x[i] + bufferX, pTmp->y[i] + bufferY, pTmp->frame + 5, pTmp->frame + 5, hWallDc, 0, 33, SRCCOPY);
					break;
				case 2:
					BitBlt(hMemDc, pTmp->x[i] + bufferX, pTmp->y[i] + bufferY, pTmp->frame + 5, pTmp->frame + 5, hWallDc, 0, 66, SRCCOPY);
					break;
				}
			}
			pTmp->frame -= 2;
			pTmp->x[0]--;pTmp->y[0]--;
			pTmp->x[1]++;pTmp->y[1]--;
			pTmp->x[2]++;pTmp->y[2]++;
			pTmp->x[3]--;pTmp->y[3]++;
			if (pTmp->frame<=0)
			{
				if (pLast)
				{
					pLast->next = pTmp->next;
					pTmp = pTmp->next;
				}
				else
				{
					head = NULL;
					pTmp = NULL;
				}
			}
			else
			{
				pLast = pTmp;
				pTmp = pTmp->next;
			}
		}
		break;
	}
}

void CScence::Update()//刷新场景状态
{
	if(loopQues==2)
	{
		for (int i = 0;i < 2800;i++)
		{
			if (mapIndex[i]==2 || mapIndex[i]==10 || mapIndex[i]== 18)
			{
				mapIndex[i] = (mapIndex[i]+8)%24;
			}
		}
	}
	else if (loopQues%4 == 0)
	{
		loopCoin = (loopCoin+1)%4;
	}
	loopQues = (loopQues+1)%8;
}

void CScence::imageA(int x, int y,  int cx,  int cy, int x1,  int y1)//背景透明处理
{
	BitBlt(hMemDc,x,y,cx,cy,hDc,x1,y1,SRCINVERT);
	BitBlt(hMemDc,x,y,cx,cy,hMaskDc,x1,y1,SRCAND);
	BitBlt(hMemDc,x,y,cx,cy,hDc,x1,y1,SRCINVERT);
}

void CScence::drawHill(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y-88+bufferY,150,90,0,0);
}

void CScence::drawTemple(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y-84+bufferY,96,90,3,95);
}

void CScence::drawFlag(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y-324+bufferY,30,90,0,185);
	for (int i = 0;i < 9;i++)
	{
		imageA(x+bufferX,y-27-30*i+bufferY,30,30,0,210);
	}
}
void CScence::drawGrass(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y-27+bufferY,60,30,155,0);
}

void CScence::drawCloud(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y+bufferY,70,42,150,30);
}

void CScence::drawTree(int x,int y)
{
	if(duceDraw(x))
		return;
	imageA(x+bufferX,y-47+bufferY,30,60,220,10);
	imageA(x+25+bufferX,y-36+bufferY,30,60,250,0);
}

void CScence::drawWall(int x,int y,int index)
{
	if(duceDraw(x))
		return;
	BitBlt(hMemDc,x+bufferX,y+bufferY,30,30,hWallDc,index%8*33,index/8*33,SRCCOPY);
}

void CScence::drawHose(int x,int y,int height)
{
	if(duceDraw(x))
		return;
	if (height==1)
	{
		imageA(x+bufferX,y-64+bufferY,70,45,70,205);
		imageA(x+bufferX+10,y-30+bufferY,60,30,245,205);
	}else
	{
		imageA(x+bufferX,y-89+bufferY,70,45,70,205);
		imageA(x+bufferX+10,y-55+bufferY,60,30,245,205);
		imageA(x+bufferX+10,y-30+bufferY,60,30,245,205);
	}
}

int CScence::duceDraw(int x)
{
	int px;
	px = player->getX();
	if (x>px)
		px = x-px;
	else
		px = px-x;
	if(px>CLIENT_WIDTH+16)
		return true;
	else
		return false;
}

// 重置地图数据
void CScence::Reset(void)
{
	FILE * file;
	head = NULL;
	switch(stage)
	{
	case 1:
		file = fopen("1.map", "rb+");
		break;
	case 2:
		file = fopen("0.map", "rb+");
		break;
	default:
		file = fopen("2.map", "rb+");
		break;
	}
	fread(&mapIndex,2800*sizeof(int),1,file);
	fclose(file);
	int i;
	for (i = 0;i < 2800;i++)
	{
		if (mapIndex[i]==2)
		{
			mapIndex[i] = mapIndex[i]+8*(i%2);//这样问号箱子可以多种多样
		}
	}
}
void CScence::coinBitBlt(int x,int y,int width,int frame)//这个函数主要是因为香蕉的长度不一
{
	BitBlt(hMemDc, x, y, 30, 30, hCoinDC, width * frame, 0, SRCINVERT);
	BitBlt(hMemDc, x, y, 30, 30, hCoinMaskDc, width * frame, 0, SRCAND);
	BitBlt(hMemDc, x, y, 30, 30, hCoinDC, width * frame, 0, SRCINVERT);
}
// 画金币
void CScence::drawCoin(int x, int y,int frame)
{
	if(duceDraw(x))//超过玩家视野
		return;
	int mapX,mapY;
	mapX = x+bufferX;
	mapY = y+bufferY;//bufferY没有什么影响
	//coinBitBlt(mapX, mapY, 35, frame);
	switch (frame)
	{
	case 0:
		coinBitBlt(mapX, mapY, 0, 0);
		break;
	case 1:
		coinBitBlt(mapX, mapY, 30, 1);
		break;
	case 2:
		coinBitBlt(mapX, mapY, 30, 2);
		break;
    case 3:
		coinBitBlt(mapX, mapY, 27, 3);
		break;
	case 4:
		coinBitBlt(mapX, mapY, 28, 4);
	}
	
}
void CScence::drawPlayer(int x, int y, int frame)
{
	BitBlt(hMemDc, x, y, 16, 30, hPlayerDc, 16 * frame, 0, SRCINVERT);
	BitBlt(hMemDc, x, y, 16, 30, hPlayerMaskDc, 16 * frame, 0, SRCAND);
	BitBlt(hMemDc, x, y, 16, 30, hPlayerDc, 16 * frame, 0, SRCINVERT);
}
void CScence::drawSpeed(int x, int y)
{
	if (duceDraw(x))//超过玩家视野
		return;
	int mapX, mapY;
	mapX = x + bufferX;
	mapY = y + bufferY;//bufferY没有什么影响
	BitBlt(hMemDc, mapX, mapY, 30, 30, hSpeedDc, 0, 0, SRCINVERT);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hSpeedMaskDc, 0, 0, SRCAND);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hSpeedDc, 0, 0, SRCINVERT);
}
void CScence::drawBlind(int x, int y)
{
	if (duceDraw(x))//超过玩家视野
		return;
	int mapX, mapY;
	mapX = x + bufferX;
	mapY = y + bufferY;//bufferY没有什么影响
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBlindDc, 0, 0, SRCINVERT);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBlindMaskDc, 0, 0, SRCAND);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBlindDc, 0, 0, SRCINVERT);
}
void CScence::drawLife(int x, int y)
{
	if (duceDraw(x))//超过玩家视野
		return;
	int mapX, mapY;
	mapX = x + bufferX;
	mapY = y + bufferY;//bufferY没有什么影响
	BitBlt(hMemDc, mapX, mapY, 30, 30, hLifetimeDc, 0, 0, SRCINVERT);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hLifetimeMaskDc, 0, 0, SRCAND);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hLifetimeDc, 0, 0, SRCINVERT);
}
void CScence::drawProtect(int x, int y)
{
	if (duceDraw(x))//超过玩家视野
		return;
	int mapX, mapY;
	mapX = x + bufferX;
	mapY = y + bufferY;//bufferY没有什么影响
	BitBlt(hMemDc, mapX, mapY, 30, 30, hProtectDc, 0, 0, SRCINVERT);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hProtectMaskDc, 0, 0, SRCAND);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hProtectDc, 0, 0, SRCINVERT);
}
void CScence::drawBullet(int x, int y)
{
	if (duceDraw(x))//超过玩家视野
		return;
	int mapX, mapY;
	mapX = x + bufferX;
	mapY = y + bufferY;//bufferY没有什么影响
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBulletDc, 0, 0, SRCINVERT);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBulletMaskDc, 0, 0, SRCAND);
	BitBlt(hMemDc, mapX, mapY, 30, 30, hBulletDc, 0, 0, SRCINVERT);
}
// 与水管进行碰撞判断
int CScence::collideWithHose(int ix, int iy)
{
	if (stage == 2)
	{
		return 0;//第二关无此水管
	}
	if (ix>=2055 && ix<=2110 && iy>=CLIENT_HEIGHT-138 && iy<= CLIENT_HEIGHT-60)
	{
		return 1;//与水管碰撞
	}
	return 0;//未碰撞
}
// 控制砖块破碎动画
void CScence::boom(int ix, int iy)
{
	SMALL_WALL *pTmp;
	if (head == NULL)
	{
		head = new SMALL_WALL;
		head->x[0] = ix;head->y[0] = iy;
		head->x[1] = ix+15;head->y[1] = iy;
		head->x[2] = ix+15;head->y[2] = iy+15;
		head->x[3] = ix;head->y[3] = iy+15;
		head->frame = 15;
		head->next = NULL;
	}
	else
	{
		pTmp = head;
		while(pTmp)
		{
			pTmp = pTmp->next;
		}
		pTmp = new SMALL_WALL;
		pTmp->x[0] = ix;pTmp->y[0] = iy;
		pTmp->x[1] = ix-15;pTmp->y[1] = iy;
		pTmp->x[2] = ix+15;pTmp->y[2] = iy+15;
		pTmp->x[3] = ix;pTmp->y[3] = iy+15;
		pTmp->frame = 25;
		pTmp->next = NULL;
	}
}
// 撞出金币动画
void CScence::coinOut(int ix, int iy)
{
	outCoin.x = ix;
	outCoin.y = iy-30;
	outCoin.frame = 0;
}
void CScence::drawCursor(int x, int y)
{
	BitBlt(hMemDc,x, y, CursorBmp.bmWidth, CursorBmp.bmHeight, hCursorDc, 0, 0, SRCCOPY);
}
