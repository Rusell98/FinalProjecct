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
int gameStep;//��Ϸ״̬
RECT winRect;//��������
HBRUSH hBlueBrush,hBlackBrush,hOldBrush,hWhiteBrush;
int time;
//int tox,toy;

LRESULT CALLBACK windowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);


int gameInit();//��Ϸ��ʼ��
int gameMain();//��Ϸ���߼�
int gamePaint();//����
int game_shutdown();//�˳���Ϸǰ������Դ
void PlayMusic(LPCTSTR file, MCIDEVICEID & m_id);
void CloseMusic(MCIDEVICEID m_id);

#define begin_number 7