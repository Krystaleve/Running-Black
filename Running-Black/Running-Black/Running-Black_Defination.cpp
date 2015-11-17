/*
* Copyright 2015.407A������
* All rights reserved.
*
* �ļ����ƣ�Running-Black_Defination.cpp
* ժ	Ҫ���ܿ���Ϸ���̺�������
*
* ��ǰ�汾��1.0
* ��	��: Krystal/��ï��
* ������ڣ�2015��11��14��
*
* ȡ���汾��1.0
* ԭ����  ��Krystal/��ï��
* ������ڣ�2015��11��14��
*/

#include "stdafx.h"
#include "Running-Black.h"

Hero g_hero;
Building g_buildings[BUILDINGS_NUM];
Barrier g_barriers[BARRIERS_NUM];
Tool g_tools[TOOLS_NUM];
Background g_background;
GameStatus g_gameStatus;

//���ڳ�ʼ��
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//����λͼ
	HBITMAP tmp, tmp_0;
	BITMAP bmpinfo;
	tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP4));
	g_hero.img = tmp;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	g_hero.img_size.cx = bmpinfo.bmWidth;
	g_hero.img_size.cy = bmpinfo.bmHeight;
	tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	g_background.img = tmp;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	g_background.img_size.cx = bmpinfo.bmWidth;
	g_background.img_size.cy = bmpinfo.bmHeight;
	int k;
	for (k = 0;k < BUILDINGS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP6));
		tmp_0 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP3));
		g_buildings[k].roof_img = tmp;
		g_buildings[k].block_img = tmp_0;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_buildings[k].roof_size.cx = bmpinfo.bmWidth;
		g_buildings[k].roof_size.cy = bmpinfo.bmHeight;
		GetObject((HGDIOBJ)tmp_0, sizeof(bmpinfo), &bmpinfo);
		g_buildings[k].block_size.cx = bmpinfo.bmWidth;
		g_buildings[k].block_size.cy = bmpinfo.bmHeight;
	}
	for (k = 0;k < BARRIERS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
		g_barriers[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_barriers[k].img_size.cx = bmpinfo.bmWidth;
		g_barriers[k].img_size.cy = bmpinfo.bmHeight;
	}
	for (k = 0;k < TOOLS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BITMAP5));
		g_tools[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_tools[k].img_size.cx = bmpinfo.bmWidth;
		g_tools[k].img_size.cy = bmpinfo.bmHeight;
	}
	InitGame(hWnd);
}

//��ʱ���¼�
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HeroUpdate(g_hero);
	GameStatusUpdate(g_gameStatus);
	BackgroundUpdate(g_background);
	int k;
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingUpdate(g_buildings[k]);
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierUpdate(g_barriers[k]);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolUpdate(g_tools[k]);
	InvalidateRect(hWnd, NULL, FALSE);
}

//�����¼�
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdcBmp, hdcBuffer;
	HBITMAP cptBmp;

	hdc = BeginPaint(hWnd, &ps);

	cptBmp = CreateCompatibleBitmap(hdc, WIDTH * GRID, HEIGHT * GRID);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	SelectObject(hdcBuffer, cptBmp);
	
	BackgroundPaint(hdcBuffer, hdcBmp, g_background);
	int k;
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingPaint(hdcBuffer, hdcBmp, g_buildings[k]);
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierPaint(hdcBuffer, hdcBmp, g_barriers[k]);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolPaint(hdcBuffer, hdcBmp, g_tools[k]);
	HeroPaint(hdcBuffer, hdcBmp, g_hero);

	BitBlt(hdc, 0, 0, WIDTH * GRID, HEIGHT * GRID, hdcBuffer, 0, 0, SRCCOPY);

	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	EndPaint(hWnd, &ps);
}

//���ڴݻ�
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

//��Ϸ��ʼ��
VOID InitGame(HWND hWnd)
{
	HeroInit(g_hero);
	BackgroundInit(g_background);
	int k;
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingInit(g_buildings[k], k);
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierInit(g_barriers[k], k);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolInit(g_tools[k], k);
	GameStatusInit(g_gameStatus);
	//������ʱ��
	SetTimer(hWnd, 1, g_gameStatus.m_frequency, NULL);
}

//Hero��ʼ��
VOID HeroInit(Hero& hero)
{
	hero.pos.x = 0;
	hero.pos.y = 13;
	hero.size.cx = 1;
	hero.size.cy = 1;
	hero.m_type = 0;
	hero.m_speed = 0;
	hero.m_a = 0;
	hero.m_life = 1;
	hero.m_state = 0;
	hero.basic_high = 13;
	hero.img_state = 0;
}

//GameStatus��ʼ��
VOID GameStatusInit(GameStatus& gameStatus)
{
	gameStatus.isPaused = FALSE;
	gameStatus.m_frequency = 30;
	gameStatus.m_score = 0;
	gameStatus.m_state = 0;
}

//Background��ʼ��
VOID BackgroundInit(Background& background)
{
	background.pos.x = 0;
	background.pos.y = 0;
	background.size.cx = WIDTH;
	background.size.cy = HEIGHT;
}

//Building��ʼ��
VOID BuildingInit(Building& building, UINT k)
{
	building.pos.x = k;
	building.pos.y = 14;
	building.size.cx = 1;
	building.size.cy = 2;
}

//Barrier��ʼ��
VOID BarrierInit(Barrier& barrier, UINT k)
{
	barrier.pos.x = k;
	barrier.pos.y = 12;
	barrier.size.cx = 1;
	barrier.size.cy = 1;
}

//Tool��ʼ��
VOID ToolInit(Tool& tool, UINT k)
{
	tool.pos.x = 3 * k + 2;
	tool.pos.y = 13;
	tool.size.cx = 1;
	tool.size.cy = 1;
}

//Hero����
VOID HeroUpdate(Hero& hero)         
{
	//TODO
	if(GetKeyState(VK_SPACE) < 0){
		hero.pos.y -= 0.2;
	}
	else if (hero.pos.y < 13){
		hero.pos.y += 0.2;
	}
	if(GetKeyState(VK_RIGHT) < 0){
		hero.pos.x += 0.2;
	}
	if(GetKeyState(VK_LEFT) < 0){
		hero.pos.x -= 0.2;
	}
}

//GameStatus����
VOID GameStatusUpdate(GameStatus& gameStatus)
{
	//TODO
}

//Background����
VOID BackgroundUpdate(Background& background)
{
	//TODO
}

//Building����
VOID BuildingUpdate(Building& building)
{
	//TODO
}

//Barrier����
VOID BarrierUpdate(Barrier& barrier)
{
	//TODO
}

//Tool����
VOID ToolUpdate(Tool& tool)
{
	//TODO
	tool.pos.x = (tool.pos.x + 0.2);
	if(tool.pos.x > WIDTH) tool.pos.x -= WIDTH;
}

//���߶���
VOID ToolFlash(Tool& tool)
{
	//TODO
}

//��ʼҳ��
VOID BeginFlash()
{
	//TODO
}

//����ҳ��
VOID EndFlash()
{
	//TODO
}

//��ʱ�鿴����״̬
VOID KeyUpdate()
{
	//TODO
}

//Hero����
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero)
{
	//TODO
	SelectObject(hdcBmp, hero.img);
	TransparentBlt(hdcBuffer, hero.pos.x * GRID, hero.pos.y * GRID, hero.size.cx * GRID, hero.size.cy * GRID, hdcBmp, 0, 0, hero.img_size.cx, hero.img_size.cy, RGB(255,255,255));
}

//Background����
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background)
{
	SelectObject(hdcBmp, background.img);
	TransparentBlt(hdcBuffer, background.pos.x * GRID, background.pos.y * GRID, background.size.cx * GRID, background.size.cy * GRID, hdcBmp, 0, 0, background.img_size.cx, background.img_size.cy, RGB(255,255,255));
}

//Building����
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building)
{
	//TODO
	SelectObject(hdcBmp, building.roof_img);
	TransparentBlt(hdcBuffer, building.pos.x * GRID, building.pos.y * GRID, GRID, GRID, hdcBmp, 0, 0, building.roof_size.cx, building.roof_size.cy, RGB(255,255,255));
	SelectObject(hdcBmp, building.block_img);
	int t;
	for (t = 1; t < building.size.cy;t++)
		TransparentBlt(hdcBuffer, building.pos.x * GRID, (building.pos.y + t) * GRID, GRID, GRID, hdcBmp, 0, 0, building.block_size.cx, building.block_size.cy, RGB(255,255,255));
}

//Barrier����
VOID BarrierPaint(HDC hdcBuffer, HDC hdcBmp, Barrier& barrier)
{
	//TODO
	SelectObject(hdcBmp, barrier.img);
	TransparentBlt(hdcBuffer, barrier.pos.x * GRID, barrier.pos.y * GRID, barrier.size.cx * GRID, barrier.size.cy * GRID, hdcBmp, 0, 0, barrier.img_size.cx, barrier.img_size.cy, RGB(255,255,255));
}

//Tool����
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool)
{
	//TODO
	SelectObject(hdcBmp, tool.img);
	TransparentBlt(hdcBuffer, tool.pos.x * GRID, tool.pos.y * GRID, tool.size.cx * GRID, tool.size.cy * GRID, hdcBmp, 0, 0, tool.img_size.cx, tool.img_size.cy, RGB(255,255,255));
}