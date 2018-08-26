#pragma once
#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <Windows.h>
#include "resource.h" //资源文件
// C 运行时头文件
#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <string.h>
#include <stdio.h>
#include <MMSystem.h> //playMusic
#include <Digitalv.h>
#define  WINDOW_CLASS_NAME "SuperMari"
#define CLIENT_HEIGHT 420	//用户区域高度
#define CLIENT_WIDTH 600	//用户区域宽度
#define FRAME_HEIGHT 30		//场景图片每帧高度
#define SKYLINE 360	//地平线
#define MAP_WIDTH 6000//200
//游戏状态定义
#define GAME_EXIT 0 //退出游戏
#define  GAME_MAIN 1 //游戏初始
#define GAME_RUN 2//游戏进行中
#define GAME_DIE 3//死亡
#define GAME_END 4//通过一关
#define GAME_LOSE 5 //游戏失败
#define GAME_WIN 6 //游戏胜利
#define GAME_PAUSE 7 //暂停游戏