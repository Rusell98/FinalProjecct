#pragma once
#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#include <Windows.h>
#include "resource.h" //��Դ�ļ�
// C ����ʱͷ�ļ�
#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <string.h>
#include <stdio.h>
#include <MMSystem.h> //playMusic
#include <Digitalv.h>
#define  WINDOW_CLASS_NAME "SuperMari"
#define CLIENT_HEIGHT 420	//�û�����߶�
#define CLIENT_WIDTH 600	//�û�������
#define FRAME_HEIGHT 30		//����ͼƬÿ֡�߶�
#define SKYLINE 360	//��ƽ��
#define MAP_WIDTH 6000//200
//��Ϸ״̬����
#define GAME_EXIT 0 //�˳���Ϸ
#define  GAME_MAIN 1 //��Ϸ��ʼ
#define GAME_RUN 2//��Ϸ������
#define GAME_DIE 3//����
#define GAME_END 4//ͨ��һ��
#define GAME_LOSE 5 //��Ϸʧ��
#define GAME_WIN 6 //��Ϸʤ��
#define GAME_PAUSE 7 //��ͣ��Ϸ