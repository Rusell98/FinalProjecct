#include "stdfx.h"
#include "Player.h"
#include "Scence.h"
#include "Monster.h"
#include "Bullet.h"
MCI_OPEN_PARMS m_open;
MCI_PLAY_PARMS m_play;
HDC hMemDc;
HBITMAP hMemBmp;
HWND hMainWnd;
HINSTANCE hInstance;
int gameStep;//游戏状态
RECT winRect;//可视区域
HBRUSH hBlueBrush,hBlackBrush,hOldBrush,hWhiteBrush;
int time;
//int tox,toy;

LRESULT CALLBACK windowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);


int gameInit();//游戏初始化
int gameMain();//游戏主逻辑
int gamePaint();//绘制
int game_shutdown();//退出游戏前销毁资源
void PlayMusic(LPCTSTR file, MCIDEVICEID & m_id);
void CloseMusic(MCIDEVICEID m_id);

#define begin_number 7