#pragma once
#include "stdfx.h"
#define bullet_distance 200 //�ӵ����ƶ��ٶ�
class CBullet
{
public:
	CBullet();
	~CBullet();
	//�����ӵ�
	void Draw(void);
private:
	//�ӵ�DC
	HDC hBuDc;
	//������
	HDC hMaskDc;
	struct BULLET
	{
		int init_x;
		int init_y;
		int x;
		int y;
		int type;
		bool life;
		bool bMove;
		bool visble;
	}temp[2];//���ӵ�����ͨ�ӵ�
public:
	// ˢ���ӵ�
	void Update(void);
private:
	// �ӵ��ƶ�
	void Move(int);
	//�ӵ����
public:
	// ����������ײ
	int collideWithMonster(int ix, int iy);
public:
	// ɱ������
	void killMonster(int index);
public:
	// �����ӵ�����
	void Reset(void);
};
