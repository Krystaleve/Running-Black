/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black_Defination.cpp
* 摘	要：跑酷游戏工程函数定义
*
* 当前版本：1.0
* 作	者: Krystal/甘茂霖
* 完成日期：2015年11月14日
*
* 取代版本：1.0
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年11月14日
*/

#include "stdafx.h"
#include "Running-Black.h"
#include "try.h"

Hero g_hero;
Building g_buildings[BUILDINGS_NUM];
Barrier g_barriers[BARRIERS_NUM];
Tool g_tools[TOOLS_NUM];
Background g_backgrounds[BACKGROUND_NUM];
GameStatus g_gameStatus;

UINT hero_img[] = {IDB_BITMAP6, IDB_BITMAP7, IDB_BITMAP8};
UINT background_img[] = {IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3};
UINT building_img[] = {IDB_BITMAP5};
UINT barrier_img[] = {IDB_BITMAP4};
UINT tool_img[] = {IDB_BITMAP9, IDB_BITMAP10, IDB_BITMAP11, IDB_BITMAP12, IDB_BITMAP13, IDB_BITMAP14, IDB_BITMAP15};

//窗口初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载位图
	HBITMAP tmp;
	BITMAP bmpinfo;
	int k;
	tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(hero_img[0]));
	g_hero.img = tmp;
	g_hero.img_size.cx = 90;
	g_hero.img_size.cy = 70;
	g_hero.img_point.x = 60;
	g_hero.img_point.y = 20;
	for (k = 0;k < BACKGROUND_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(background_img[k]));
		g_backgrounds[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_backgrounds[k].img_size.cx = bmpinfo.bmWidth;
		g_backgrounds[k].img_size.cy = bmpinfo.bmHeight;
		g_backgrounds[k].img_point.x = 0;
		g_backgrounds[k].img_point.y = 0;
	}
	for (k = 0;k < BUILDINGS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(building_img[0]));
		g_buildings[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_buildings[k].roof_size.cx = 64;
		g_buildings[k].roof_size.cy = 60;
		g_buildings[k].roof_point.x = 7 * 64;
		g_buildings[k].roof_point.y = 2 * 64;
		g_buildings[k].block_size.cx = 64;
		g_buildings[k].block_size.cy = 64;
		g_buildings[k].block_point.x = 3 * 64;
		g_buildings[k].block_point.y = 0;
	}
	for (k = 0;k < BARRIERS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(barrier_img[0]));
		g_barriers[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_barriers[k].img_size.cx = bmpinfo.bmWidth;
		g_barriers[k].img_size.cy = bmpinfo.bmHeight;
		g_barriers[k].img_point.x = 0;
		g_barriers[k].img_point.y = 0;
	}
	for (k = 0;k < TOOLS_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(tool_img[k % 7]));
		g_tools[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_tools[k].img_size.cx = bmpinfo.bmWidth;
		g_tools[k].img_size.cy = bmpinfo.bmHeight;
		g_tools[k].img_point.x = 0;
		g_tools[k].img_point.y = 0;
	}
	InitGame(hWnd);
}

//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HeroUpdate(g_hero);
	GameStatusUpdate(g_gameStatus);
	int k;
	for(k = 0;k < BACKGROUND_NUM;k++)
		BackgroundUpdate(g_backgrounds[k]);
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingUpdate(g_buildings[k]);
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierUpdate(g_barriers[k]);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolUpdate(g_tools[k]);
	InvalidateRect(hWnd, NULL, FALSE);
}

//绘制事件
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
	
	int k;
	for(k = 0;k < BACKGROUND_NUM;k++)
		BackgroundPaint(hdcBuffer, hdcBmp, g_backgrounds[k]);
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingPaint(hdcBuffer, hdcBmp, g_buildings[k]);
/*	
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierPaint(hdcBuffer, hdcBmp, g_barriers[k]);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolPaint(hdcBuffer, hdcBmp, g_tools[k]);	
*/
	HeroPaint(hdcBuffer, hdcBmp, g_hero);

	BitBlt(hdc, 0, 0, WIDTH * GRID, HEIGHT * GRID, hdcBuffer, 0, 0, SRCCOPY);

	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	EndPaint(hWnd, &ps);
}

//窗口摧毁
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

//游戏初始化
VOID InitGame(HWND hWnd)
{
	HeroInit(g_hero);
	int k;
	for(k = 0;k < BACKGROUND_NUM;k++)
		BackgroundInit(g_backgrounds[k]);
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingInit(g_buildings[k], k);
	for(k = 0;k < BARRIERS_NUM;k++)
		BarrierInit(g_barriers[k], k);
	for(k = 0;k < TOOLS_NUM;k++)
		ToolInit(g_tools[k], k);
	GameStatusInit(g_gameStatus);
	//启动计时器
	SetTimer(hWnd, 1, g_gameStatus.m_frequency, NULL);
}

//Hero初始化
VOID HeroInit(Hero& hero)
{
	hero.pos.x = 0;
	hero.pos.y = 15;
	hero.size.cx = 2;
	hero.size.cy = 2;
	hero.m_type = 0;
	hero.m_speed = 0;
	hero.m_a = 0;
	hero.m_life = 1;
	hero.m_state = 0;
	hero.basic_high = 13;
	hero.img_state = 0;
}

//GameStatus初始化
VOID GameStatusInit(GameStatus& gameStatus)
{
	gameStatus.isPaused = FALSE;
	gameStatus.m_frequency = 30;
	gameStatus.m_score = 0;
	gameStatus.m_state = 0;
}

//Background初始化
VOID BackgroundInit(Background& background)
{
	background.pos.x = 0;
	background.pos.y = 0;
	background.size.cx = WIDTH;
	background.size.cy = HEIGHT;
}

//Building初始化
VOID BuildingInit(Building& building, UINT k)
{
	building.pos.x = k;
	building.pos.y = 17;
	building.size.cx = 1;
	building.size.cy = 3;
}

//Barrier初始化
VOID BarrierInit(Barrier& barrier, UINT k)
{
	barrier.pos.x = k * 3;
	barrier.pos.y = 15;
	barrier.size.cx = 2;
	barrier.size.cy = 2;
}

//Tool初始化
VOID ToolInit(Tool& tool, UINT k)
{
	tool.pos.x = 3 * k + 2;
	tool.pos.y = 16;
	tool.size.cx = 1;
	tool.size.cy = 1;
}

//Hero更新
VOID HeroUpdate(Hero& hero)         
{
	//TODO
}

//GameStatus更新
VOID GameStatusUpdate(GameStatus& gameStatus)
{
	//TODO
}

//Background更新
VOID BackgroundUpdate(Background& background)
{
	//TODO
}

//Building更新
VOID BuildingUpdate(Building& building)
{
	//TODO
}

//Barrier更新
VOID BarrierUpdate(Barrier& barrier)
{
	//TODO
}

//Tool更新
VOID ToolUpdate(Tool& tool)
{
	//TODO
	tool.pos.x = (tool.pos.x + 0.2);
	if(tool.pos.x > WIDTH) tool.pos.x -= WIDTH;
}

//道具动画
VOID ToolFlash(Tool& tool)
{
	//TODO
}

//开始页面
VOID BeginFlash()
{
	//TODO
}

//结束页面
VOID EndFlash()
{
	//TODO
}

//定时查看按键状态
VOID KeyUpdate()
{
	//TODO
}

//Hero绘制
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero)
{
	//TODO
	SelectObject(hdcBmp, hero.img);
	TransparentBlt(hdcBuffer, hero.pos.x * GRID, hero.pos.y * GRID, hero.size.cx * GRID, hero.size.cy * GRID, hdcBmp, hero.img_point.x, hero.img_point.y, hero.img_size.cx, hero.img_size.cy, RGB(255,255,255));
}

//Background绘制
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background)
{
	SelectObject(hdcBmp, background.img);
	TransparentBlt(hdcBuffer, background.pos.x * GRID, background.pos.y * GRID, background.size.cx * GRID, background.size.cy * GRID, hdcBmp, background.img_point.x, background.img_point.y, background.img_size.cx, background.img_size.cy, RGB(255,255,255));
}

//Building绘制
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building)
{
	//TODO
	SelectObject(hdcBmp, building.img);
	TransparentBlt(hdcBuffer, building.pos.x * GRID, building.pos.y * GRID, GRID, GRID, hdcBmp, building.roof_point.x, building.roof_point.y, building.roof_size.cx, building.roof_size.cy, RGB(255,255,255));
	int t;
	for (t = 1; t < building.size.cy;t++)
		TransparentBlt(hdcBuffer, building.pos.x * GRID, (building.pos.y + t) * GRID, GRID, GRID, hdcBmp, building.block_point.x, building.block_point.y, building.block_size.cx, building.block_size.cy, RGB(255,255,255));
}

//Barrier绘制
VOID BarrierPaint(HDC hdcBuffer, HDC hdcBmp, Barrier& barrier)
{
	//TODO
	SelectObject(hdcBmp, barrier.img);
	TransparentBlt(hdcBuffer, barrier.pos.x * GRID, barrier.pos.y * GRID, barrier.size.cx * GRID, barrier.size.cy * GRID, hdcBmp, barrier.img_point.x, barrier.img_point.y, barrier.img_size.cx, barrier.img_size.cy, RGB(255,255,255));
}

//Tool绘制
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool)
{
	//TODO
	SelectObject(hdcBmp, tool.img);
	TransparentBlt(hdcBuffer, tool.pos.x * GRID, tool.pos.y * GRID, tool.size.cx * GRID, tool.size.cy * GRID, hdcBmp, tool.img_point.x, tool.img_point.y, tool.img_size.cx, tool.img_size.cy, RGB(255,255,255));
}