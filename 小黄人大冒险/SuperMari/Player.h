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
	void Draw();//��������Լ�
	void keyDown(WPARAM wparam);
	void keyUp(WPARAM wparam);
	void Update();//ˢ�����״̬
	int getX();//��ȡ���X����
	int getY();
	int getdeltaX();
	~CPlayer();
private:
	//�������X����
	int x;
	//�������y����
	int y;	
	//�������ˮƽ�ƶ��ٶ�
	int speed;	
	//���ƶ�����֡��
	int frame; 
	//�Ƿ����½�����
	bool bFalling;
	//�������Ҽ��Ƿ񱻰���
	bool bRightKey,bLeftKey,bUpKey,bDownKey;
	// Control���Ƿ񱻰���
	bool bControlKey;
	//���DC���
	HDC hDc;	
	//���bmp���
	HBITMAP hBitmap;
	//����͸��Ч��������dc���
	HDC hMaskDc;	
	// ��������X�����ƶ��ľ���
	int dltaX;
	// ������Y����ƶ�����
	int daltY;
	// ���ƶ���֡
	int animalLoop;
	// ����ˮƽ���ٶ�
	int dltaXLoop;
	// �ƶ�����
	void moveMari(void);
	// ������������
	void MariAnimal(void);
	// ������������ײ
	void collide(void);
	//ˮƽ�ƶ�����
	void walk();
	// ����Ƿ��ŵ�
	bool bLanded;
	// ��ҷ���,-1��ʾ����,-2��ʾ����,0��ʾ��ǰ
	int direction;
	// �����������
	void mariRising(void);
	// ����������
	void mariFalling(void);
	// ����Ƿ���������
	bool bRising;
public:
	// �����������
	bool Reset(void);
private:
	// �����������
	int lifeNumber;
	// ��ȡ�Ľ������
	// ��ʾ���Ը����ľ������
	int _g;
	// ���������Ծ�ļ��ٶ�Ч��
	int g;
	// ��ȡ��Ҳ��Ҳ��Ž������
	void getCoin(int index);
	//����ٶ�����ʱ�䲢��������
	void getSpeed(int index);
	//�����äʱ������
	void getBlind(int index);
	//�������������
	void getLifetime(int index);
	//��ұ���ʱ��������
	void getProtecttime(int index);
public:
	// �������
	void killMari(void);
};
