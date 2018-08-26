#include "SuperMari.h"
MCIDEVICEID back_id;
CPlayer * player;
CScence * scence;
CMonster * monster;
CBullet * bullet;
int stage;
int begin_count = 0;//һ���˵����
int begin_second_count = 0;//�����˵����
int difficulty_degree = 0;//�Ѷ�
int begin_choose_count = 0;
int music_switch = 1;//���ֿ��� 1:�� -1����
int second_count = 0;//�����
int accelerate_count = 0;//���ټ�����
int blind_count = 0;//����������
int protect_count = 0;//����������
int life_count = 0;//����������
int bullet_shop_number = 0;//�̵깺����ӵ���
extern int bullet_number;//�ӵ���
extern int difficulty;//�Ѷ�
extern int accelerate_time;//����ʱ��
extern int blind_time;//��äʱ��
extern int protecttime;//������ʱ��
extern int lifetime;//һ�ص�������
extern int coin;//�����
void PlayMusic(LPCTSTR file,MCIDEVICEID & m_id);
void CloseMusic(MCIDEVICEID m_id);
void PauseMusic(MCIDEVICEID m_id);
void StopMusic(MCIDEVICEID m_id);
//������
void read_memory(void)//ȡ
{
	char t1[10];
	FILE *fp1;
	fp1 = fopen("memory.txt", "r");//ֻ����ʽ���ļ�memory.txt
	fgets(t1, 10, fp1);
	coin = atoi(t1);
	fclose(fp1);//�ر��ļ�memory.txt���д򿪾�Ҫ�йر�
}

void write_memory(void)//��
{
	FILE *fp1;
	char t2[10] = { 0 };
	fp1 = fopen("memory.txt", "w");//ֻд��ʽ���ļ�memory.txt
	itoa(coin, t2, 10);
	fwrite(t2, sizeof(t2), 1, fp1);
	fclose(fp1);//�ر��ļ�memory.txt���д򿪾�Ҫ�йر�
}
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int ncmdshow)
{  
	WNDCLASSEX winclass;
	HWND hwnd;
	MSG msg;

	winclass.cbSize = sizeof(WNDCLASSEX);//�������С
	winclass.style = CS_HREDRAW | CS_VREDRAW;//��������
	winclass.lpfnWndProc = windowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor = LoadCursor(NULL,IDC_HAND);
	winclass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_ICON1));

	if(!RegisterClassEx(&winclass))
		return 0;
	if(!(hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"С���˴�ð��",
		WS_SYSMENU|WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN)-CLIENT_WIDTH)/2,(GetSystemMetrics(SM_CYSCREEN)-CLIENT_HEIGHT)/2,
		CLIENT_WIDTH,CLIENT_HEIGHT,
		NULL,NULL,hinstance,NULL)))
		return (0);	
	GetClientRect(hwnd,&winRect);
	MoveWindow(hwnd,
		(GetSystemMetrics(SM_CXSCREEN)-CLIENT_WIDTH)/2,(GetSystemMetrics(SM_CYSCREEN)-CLIENT_HEIGHT)/2,
		CLIENT_WIDTH*2-winRect.right,CLIENT_HEIGHT*2-winRect.bottom,true);
	ShowWindow(hwnd,SW_SHOWNORMAL);//���û��ʲô����
	UpdateWindow(hwnd);
	hMainWnd = hwnd;
	hInstance = hinstance;
	gameInit();
	while(gameStep>0)//�˳���Ϸ��0
	{

		DWORD start_time = GetTickCount();
		if(PeekMessage(&msg,hwnd,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);//������������ذ����ļ��
			DispatchMessage(&msg);
		}
		gameMain();
		gamePaint();
		second_count++;
		if (second_count == 30)
		{
			second_count = 0;
			accelerate_time--;
			blind_time--;
			protecttime--;
			if (accelerate_time < 0)
			accelerate_time = 0;
			if (blind_time < 0)
				blind_time = 0;
			if (protecttime < 0)
				protecttime = 0;
        }
		while(GetTickCount()-start_time<33);//�ǳ���Ҫ
		write_memory();
	}
	return (int)msg.wParam;
}
int gameInit()
{
	HDC hdc;
	hdc = GetDC(hMainWnd);
	GetClientRect(hMainWnd,&winRect);

	gameStep = GAME_MAIN;
	hBlueBrush = CreateSolidBrush(RGB(160,180,250));
	hBlackBrush = CreateSolidBrush(RGB(100,100,100));

	hMemDc = CreateCompatibleDC(hdc);
	hMemBmp = CreateCompatibleBitmap(hdc,CLIENT_WIDTH,CLIENT_HEIGHT);
	SelectObject(hMemDc,hMemBmp);
	SetBkMode(hMemDc,TRANSPARENT);

	player = new CPlayer();
	scence = new CScence();
	monster = new CMonster();
	bullet = new CBullet();
	stage = 0;
	time = 0;
	read_memory();//��ȡ��һ����Ϸ�Ľ�Ǯ��
	PlayMusic("back_music.mp3",back_id);

	ReleaseDC(hMainWnd,hdc);
	return 0;
}
int gameMain()
{
	if (gameStep != GAME_PAUSE)
	{
		scence->Update();
		player->Update();
		monster->Update();
		bullet->Update();
		if (gameStep == GAME_LOSE)
		{
			time++;
		}
	}
	return 0;
}
int gamePaint()
{
	HDC hdc = GetDC(hMainWnd);
		if (stage == 2 && (gameStep == GAME_RUN || gameStep == GAME_PAUSE))
		{
			FillRect(hMemDc, &winRect, hBlackBrush);
		}
		else
			FillRect(hMemDc, &winRect, hBlueBrush);//����ɫ
	monster->Draw();
	scence->Draw();
	player->Draw();
	bullet->Draw();
	BitBlt(hdc,0,0,CLIENT_WIDTH,CLIENT_HEIGHT,hMemDc,0,0,SRCCOPY);
	ReleaseDC(hMainWnd,hdc);
	return 0;
}
LRESULT CALLBACK windowProc(HWND hWnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch(msg)
	{
	case WM_KEYUP:
		if (gameStep == GAME_RUN)
		{
			if(wparam == VK_ESCAPE)
			{
				gameStep = GAME_PAUSE;
				PauseMusic(back_id);
			}
		else
			player->keyUp(wparam);
		}
		else if (gameStep == GAME_PAUSE)
		{
			if(wparam == VK_ESCAPE)
			{
				gameStep = GAME_RUN;
				mciSendCommand(back_id,MCI_PLAY,MCI_NOTIFY|MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&m_play);
			}
		}
		break;
	case WM_KEYDOWN:
		switch(gameStep)
		{
		case GAME_MAIN:
			switch (wparam)
			{
			    case VK_ESCAPE : 
				DestroyWindow(hWnd);//�˳���Ϸ
				break;
				case VK_RETURN :
					switch (begin_choose_count)
					{
					    case 0:
							switch (begin_count)
							{
							case 0:
								bullet_number += bullet_shop_number;
								gameStep = GAME_RUN;
								mciSendCommand(back_id, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_play);
								player->Reset();
								monster->Reset();
								scence->Reset();
								bullet->Reset();
								break;
							case 1:
								begin_choose_count = 1;
								break;
							case 2:
								begin_choose_count = 2;
								break;
							case 3:
								begin_choose_count = 3;
								break;
							case 4:
								break;
							case 5:
								begin_choose_count = 5;
								break;
							case 6:
								DestroyWindow(hWnd);//�˳���Ϸ
								break;
							default:
								break;
							}
						break;
						case 1:
							switch (begin_second_count)
							{
							case 0:
								difficulty = 0;//��
							    break;
							case 1:
								difficulty =1;//�е�
								break;
							case 2:
								difficulty = 2;//����
								break;
							case 3:
								difficulty = 3;//���
								break;
							case 4:
								begin_choose_count = 0;
								begin_count = 0;
								begin_second_count = 0;
								break;
							}
						break;
						case 2:
							switch (begin_second_count)
							{
							case 0:
								stage = 0;
								break;
							case 1:
								stage = 1;
								break;
							case 2:
								stage = 2;
								break;
							case 3:
							default:
								begin_choose_count = 0;
								begin_count = 0;
								begin_second_count = 0;
								break;
							}
						break;
						case 3:
							switch (begin_second_count)
							{
							case 0:
								music_switch *= -1;
								break;
							case 1:
								begin_choose_count = 0;
								begin_count = 0;
								begin_second_count = 0;
								break;
							default:
								break;
							 }
						break;
						case 4:
							break;
						case 5:
							switch (begin_second_count)
							{
							case 0:
								if ((coin - 2) >= 0)
								{
									accelerate_count += 1;
									coin -= 2;
								}
								break;
							case 1:
								if ((coin - 3) >= 0)
								{
									life_count += 1;
									coin -= 3;
							    }
								break;
							case 2:
								if ((coin - 3) >= 0)
								{
									protect_count += 1;
									coin -= 3;
								}
								break;
							case 3:
								if ((coin - 2) >= 0)
								{
									blind_count += 1;
									coin -= 2;
								}
								break;
							case 4:
								if ((coin - 2) >= 0)
								{
									bullet_shop_number++;
									coin -= 2;
								}
								break;
							case 5:
								begin_choose_count = 0;
								begin_count = 0;
								begin_second_count = 0;
								break;
							default:
								break;
							}
						break;
					}
				break;
				case VK_DOWN:
				case 's':
				switch (begin_choose_count)
				{
				   case 0:
				   begin_count++;
				   if (begin_count == begin_number)
				   begin_count = 0;
				   break;
				   case 1:
				   begin_second_count++;
				   if (begin_second_count == 5)
				   begin_second_count = 0;
				   break;
				   case 2:
				   begin_second_count++;
				   if (begin_second_count == 4)
				   begin_second_count = 0;
				   break;
				   case 3:
				   begin_second_count++;
				   if (begin_second_count == 2)
				   begin_second_count = 0;
				   break;
				   case 4://˵��
				   break;
				   case 5://�̵�
				   begin_second_count++;
				   if (begin_second_count == 6)
				   begin_second_count = 0;
				   break;
				}
			    break;
				case 'w':
				case VK_UP:
			    switch (begin_choose_count)
				{
				case 0:
				begin_count--;
				if (begin_count == -1)
				begin_count =begin_number-1;
				break;
			    case 1:
				begin_second_count--;
				if (begin_second_count == -1)
				begin_second_count = 4;
				break;
				case 2:
				begin_second_count--;
				if (begin_second_count == -1)
				begin_second_count = 3;
				break;
				case 3:
				begin_second_count--;
				if (begin_second_count == -1)
				begin_second_count = 1;
				break;
				case 4:
				break;
				case 5:
				begin_second_count--;
				if (begin_second_count == -1)
					begin_second_count = 5;
				break;
				}
				break;
				default:
				break;
            }
		case GAME_RUN:
			player->keyDown(wparam);
			break;
		case GAME_LOSE:
			if (time*33>2000)
			{
				DestroyWindow(hWnd);
			}
			break;
		case GAME_END:
			if (wparam == VK_RETURN || wparam == VK_ESCAPE)
			{
				gameStep = GAME_MAIN;
			}
			break;
		case GAME_DIE:
			 if(wparam == VK_RETURN)
			 {
				 mciSendCommand(back_id,MCI_PLAY,MCI_NOTIFY|MCI_DGV_PLAY_REPEAT,(DWORD)(LPVOID)&m_play);
				 if(player->Reset())
				 {
					 monster->Reset();
					 scence->Reset();
					 lifetime = 1;
					 gameStep = GAME_RUN;
				 }
				 else
				 {
					 gameStep = GAME_LOSE;
				 }
			 }
			break;
		}
		break;
	case WM_DESTROY:
		game_shutdown();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wparam, lparam);
		break;
	}
	return(0);
}

int game_shutdown()
{
	DeleteObject(hBlueBrush);
	DeleteObject(hBlackBrush);
	DeleteDC(hMemDc);
	DeleteObject(hMemBmp);
	gameStep = GAME_EXIT;
	return 0;
}

void PlayMusic(LPCTSTR file,MCIDEVICEID & m_id)
{
	if (music_switch == 1)
	{
		mciSendCommand(m_id, MCI_CLOSE, NULL, NULL);
		m_open.lpstrElementName = file; //�ļ�·��
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_open);
		mciSendCommand(m_open.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_play);
		m_id = m_open.wDeviceID;
	}
}
void CloseMusic(MCIDEVICEID m_id)
{
	mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
}

void PauseMusic(MCIDEVICEID m_id)
{
	mciSendCommand(m_id,MCI_PAUSE,0,(DWORD)(LPVOID)&m_play);
}

void StopMusic(MCIDEVICEID m_id)
{
	mciSendCommand(m_id,MCI_STOP,NULL,NULL);
}