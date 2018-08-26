#pragma once
#include "stdfx.h"
#include "Player.h"
class CScence
{
public:
	CScence();
	void Draw();//���Ƴ����Լ�
	void Update();//ˢ�³���״̬
	~CScence();
private:
	void imageA( int x, int y,  int cx,  int cy, int x1,  int y1);//����͸������
	void drawHill(int x,int y);
	void drawTemple(int x,int y);
	void drawFlag(int x,int y);
	void drawGrass(int x,int y);
	void drawCloud(int x,int y);
	void drawTree(int x,int y);
	void drawWall(int x,int y,int index);
	void drawHose(int x,int y,int height=1);//��ˮ��
	void drawCursor(int x, int y);//�����
	int duceDraw(int x1);//�ж��Ƿ񳬳���Ļ�������򲻻�
	HDC hDc,hWallDc;	//����DC���
	HDC hMaskDc;	//����͸��Ч��������dc���
	HDC hTitleDc,hTitleMaskDc,hBeginDc,hCursorDc,hDifficultyDc,hLevelDc,hSetupDc,hSwitchDc, hSwitchoffDc,hSpeedDc,hBlindDc,hLifetimeDc,hProtectDc,hPlayerDc,hShopDc,hBulletDc;//����˿�ʼ����dc���
	HDC hCoinDC,hCoinMaskDc,hSpeedMaskDc,hBlindMaskDc,hLifetimeMaskDc,hProtectMaskDc,hPlayerMaskDc, hBulletMaskDc;
	BITMAP titleBmp,dieBmp,overBmp,BeginBmp,CursorBmp,DifficultyBmp,LevelBmp,SetupBmp,SwitchBmp, SwitchoffBmp,SpeedBmp,BlindBmp,LifetimeBmp,ProtectBmp,PlayerBmp,ShopBmp,BulletBmp;
	// �����ʺŶ���ѭ��
	int loopQues;
public:
	// ���õ�ͼ����
	void Reset(void);
private:
	void drawCoin(int x, int y,int frame);// �����
	void coinBitBlt(int x, int y, int width,int frame);
	void drawSpeed(int x, int y);//�����ٷ�
	void drawBlind(int x, int y);//����ä��
	void drawLife(int x, int y);//��������
	void drawProtect(int x, int y);//��������
	void drawBullet(int x, int y);//���ӵ�
public:
	// ��ˮ�ܽ�����ײ�ж�
	int collideWithHose(int ix, int iy);
	void drawPlayer(int x, int y, int frame);//�����
private:
	// ����ͼƬDC
	HDC hDieDc;
	//��Ϸ����ͼƬDC
	HDC hOverDc;
	// ��������ͼƬ����
	int dieLoop;
	// �����⶯�����ֵ�����
	RECT titleRect;
	// ���ƽ�Ҷ���֡��
	int loopCoin;
public:
	// ����ש�����鶯��
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
	// ײ����Ҷ���
	void coinOut(int ix, int iy);
};
