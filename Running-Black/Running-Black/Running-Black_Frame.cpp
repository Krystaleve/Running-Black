/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black_Frame.cpp
* 摘	要：跑酷游戏工程框架函数定义
*
* 当前版本：1.5
* 作	者: Krystal/甘茂霖
* 完成日期：2015年12月6日
*
* 取代版本：1.4
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年12月5日
*/

#include "stdafx.h"
#include "Running-Black.h"

Hero g_hero[HEROS_NUM];
Building g_buildings[BUILDINGS_NUM];
Tool g_tools[TOOLS_NUM];
Background g_backgrounds[BACKGROUND_NUM];
GameStatus g_gameStatus;

UINT hero_img[] = {IDB_HERO_0, IDB_HERO_1, IDB_HERO_2, IDB_HERO_3};
UINT background_img[] = {IDB_BACKGROUND_0, IDB_BACKGROUND_1, IDB_BACKGROUND_2, IDB_BACKGROUND_3, IDB_BACKGROUND_4, IDB_BACKGROUND_5};
UINT building_img[] = {IDB_BUILDINGS};
UINT tool_img[] = {IDB_TOOL_0, IDB_TOOL_1, IDB_TOOL_2, IDB_TOOL_3, IDB_TOOL_4, IDB_TOOL_5, IDB_TOOL_6, IDB_TOOL_7, IDB_TOOL_8};

BOOL g_keyState[256];
UINT g_times;
DOUBLE headX;
POINTF preBuilding;
DOUBLE toolX;
UINT building_now;
UINT tool_gap_min;
UINT tool_gap_max;
BOOL toolCreate;
UINT tool_id[TOOLS_TYPE][TOOLS_NUM / TOOLS_TYPE + 1];
BOOL g_flag;
UINT tool_start;
Bmp hero_bmps[3 * HEROS_NUM];
DOUBLE moveX;
DOUBLE backgroundMove;

Bmp hero_select_0;
Bmp hero_select_1;
Bmp button_start_0;
Bmp button_start_1;
Bmp button_start_2;
Bmp button_return;
Bmp button_pause_0;
Bmp button_pause_1;
Bmp author;

POINTF info_0_pos;
POINTF info_1_pos;
POINTF title_pos;
POINTF hint_pos;
POINTF score_pos;
POINTF coin_pos;
POINTF life_pos;
POINTF help_pos;
POINTF death_pos;
POINTF restart_pos;

SIZE help_size;
SIZE death_size;

//窗口初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	srand((unsigned)time(NULL));
	g_times = 0;
	tool_gap_min = 5;
	tool_gap_max = 12;
	moveX = 0.2;
	backgroundMove = 0.05;
	g_flag = TRUE;
	InitPos();
	//初始化keyState
	int k;
	for(k = 0;k < 256;k++)
		g_keyState[k] = FALSE;
	//加载位图
	HBITMAP tmp;
	BITMAP bmpinfo;
	hero_select_0.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HERO_SELECT_0));
	hero_select_0.img_point.x = hero_select_0.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	hero_select_0.img_size.cx = bmpinfo.bmWidth;
	hero_select_0.img_size.cy = bmpinfo.bmHeight;
	hero_select_1.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_HERO_SELECT_1));
	hero_select_1.img_point.x = hero_select_1.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	hero_select_1.img_size.cx = bmpinfo.bmWidth;
	hero_select_1.img_size.cy = bmpinfo.bmHeight;
	button_start_0.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_START_0));
	button_start_0.img_point.x = button_start_0.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_start_0.img_size.cx = bmpinfo.bmWidth;
	button_start_0.img_size.cy = bmpinfo.bmHeight;
	button_start_1.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_START_1));
	button_start_1.img_point.x = button_start_1.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_start_1.img_size.cx = bmpinfo.bmWidth;
	button_start_1.img_size.cy = bmpinfo.bmHeight;
	button_start_2.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_START_2));
	button_start_2.img_point.x = button_start_2.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_start_2.img_size.cx = bmpinfo.bmWidth;
	button_start_2.img_size.cy = bmpinfo.bmHeight;
	button_pause_0.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_PAUSE_0));
	button_pause_0.img_point.x = button_pause_0.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_pause_0.img_size.cx = bmpinfo.bmWidth;
	button_pause_0.img_size.cy = bmpinfo.bmHeight;
	button_pause_1.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_PAUSE_1));
	button_pause_1.img_point.x = button_pause_1.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_pause_1.img_size.cx = bmpinfo.bmWidth;
	button_pause_1.img_size.cy = bmpinfo.bmHeight;
	button_return.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BUTTON_RETURN));
	button_return.img_point.x = button_return.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	button_return.img_size.cx = bmpinfo.bmWidth;
	button_return.img_size.cy = bmpinfo.bmHeight;
	author.img = tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_AUTHOR));
	author.img_point.x = author.img_point.y = 0;
	GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
	author.img_size.cx = bmpinfo.bmWidth;
	author.img_size.cy = bmpinfo.bmHeight;
	for(k = 0;k < HEROS_NUM;k++){
		hero_bmps[k * 3].img = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(hero_img[k * 3]));
		if(k == 0)
		{
			hero_bmps[k + 1].img = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(hero_img[k + 1]));
			hero_bmps[k + 2].img = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(hero_img[k + 2]));
		}
		g_hero[k].img = hero_bmps[k * 3].img;
		g_hero[k].img_size.cx = 100;
		g_hero[k].img_size.cy = 100;
		if(k == 1)
		{
			g_hero[k].img_size.cx = 82;
			g_hero[k].img_size.cy = 85;
		}
		g_hero[k].img_point.x = 0;
		g_hero[k].img_point.y = 0;
	}
	for (k = 0;k < BACKGROUND_NUM;k++){
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(background_img[k]));
		g_backgrounds[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_backgrounds[k].img_size.cx = bmpinfo.bmWidth;
		g_backgrounds[k].img_size.cy = bmpinfo.bmHeight;
		g_backgrounds[k].img_point.x = 0;
		g_backgrounds[k].img_point.y = 0;
		g_backgrounds[k].visible = FALSE;
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
	for (k = 0;k < TOOLS_TYPE;k++)
		tool_id[k][0] = TOOLS_NUM / TOOLS_TYPE;
	for (k = 0;k < TOOLS_NUM;k++){
		g_tools[k].id = k;
		tmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(tool_img[k % TOOLS_TYPE]));
		g_tools[k].img = tmp;
		GetObject((HGDIOBJ)tmp, sizeof(bmpinfo), &bmpinfo);
		g_tools[k].img_size.cx = bmpinfo.bmWidth;
		g_tools[k].img_size.cy = bmpinfo.bmHeight;
		g_tools[k].img_point.x = 0;
		g_tools[k].img_point.y = 0;
		g_tools[k].img_state = 0;
		g_tools[k].m_type = k % TOOLS_TYPE;
		g_tools[k].solid = FALSE;
		g_tools[k].down = TRUE;
		g_tools[k].disappear = FALSE;
		tool_id[k % TOOLS_TYPE][k / TOOLS_TYPE + 1] = k;
		if(g_tools[k].m_type == 1 || g_tools[k].m_type == 3)
			g_tools[k].solid = TRUE;
		if(g_tools[k].m_type > 3 || g_tools[k].m_type == 0)
			g_tools[k].disappear = TRUE;
		if(g_tools[k].m_type == 1)
			g_tools[k].img_size.cy -= 28;
		if(g_tools[k].m_type == 3)
			g_tools[k].img_size.cy -= 10;
		if(g_tools[k].m_type == 7)
			g_tools[k].img_size.cx = g_tools[k].img_size.cy = 128;
	}
	InitGame();	
	//启动计时器
	SetTimer(hWnd, 1, g_gameStatus.m_frequency, NULL);
}

//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if(!g_flag) return;
	g_flag = FALSE;
	g_times = (g_times + 1) % INT_MAX;
	GameStatusUpdate(g_gameStatus);
	if(g_gameStatus.m_state == 8)
	{
		headX -= g_gameStatus.moveX;
		preBuilding.x -= g_gameStatus.moveX;
		if(abs(toolX + tool_gap_min + 3) > 0.00001)
			toolX -= g_gameStatus.moveX;
		int k;
		for(k = 0;k < BACKGROUND_NUM;k++)
			BackgroundUpdate(g_backgrounds[k]);
		for(k = 0;k < TOOLS_NUM;k++)
			ToolUpdate(g_tools[k]);
		for(k = 0;k < BUILDINGS_NUM;k++)
			BuildingUpdate(g_buildings[k]);
	}
	HeroUpdate(g_hero[g_gameStatus.hero_type]);
	KeyUpdate();
	InvalidateRect(hWnd, NULL, FALSE);
}

//鼠标事件
VOID MouseClickEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	POINTS pos = MAKEPOINTS(lParam);
	int state_0 = g_gameStatus.m_state / 4;
	int state_1 = g_gameStatus.m_state % 4;
	if(state_0 == 1)
	{
		if(state_1 == 0)
		{
			if(InArea(pos.x, pos.y, button_start_0.dst_point, button_start_0.dst_size))
				g_gameStatus.m_state = 5;
			else if(InArea(pos.x, pos.y, button_start_1.dst_point, button_start_1.dst_size))
				g_gameStatus.m_state = 6;
			else if(InArea(pos.x, pos.y, button_start_2.dst_point, button_start_2.dst_size))
				g_gameStatus.m_state = 7;
		}
		else if(state_1 == 1)
		{
			if(InArea(pos.x, pos.y, hero_select_0.dst_point, hero_select_0.dst_size))
			{
				g_gameStatus.m_state = 8;
				g_gameStatus.hero_type = 0;
				HeroInit(g_hero[0]);
				headX = WIDTH;
				preBuilding.x = 30;
				preBuilding.y = g_gameStatus.basic_high;
				toolX = -(DOUBLE)tool_gap_min-3;
				building_now = 0;
				int i;
				for(i = 1;i < BUILDINGS_NUM;i++)
				{
					BuildingInit(g_buildings[i]);
				}
				CreateTool();
 				toolCreate = TRUE;
			}
			else if(InArea(pos.x, pos.y, hero_select_1.dst_point, hero_select_1.dst_size))
			{
				g_gameStatus.m_state = 8;
				g_gameStatus.hero_type = 1;
				HeroInit(g_hero[1]);
				headX = 0;
				preBuilding.x = -1;
				preBuilding.y = g_gameStatus.basic_high;
				toolX = -(DOUBLE)tool_gap_min-3;
				building_now = 0;
				int i;
				for(i = 1;i < BUILDINGS_NUM;i++)
				{
					BuildingInit(g_buildings[i]);
				}
				CreateTool();
 				toolCreate = TRUE;
			}
			else if(InArea(pos.x, pos.y, button_return.dst_point, button_return.dst_size))
				g_gameStatus.m_state = 4;
		}
		else
			if(InArea(pos.x, pos.y, button_return.dst_point, button_return.dst_size))
				g_gameStatus.m_state = 4;
	}
	else if(state_0 == 2)
		if(InArea(pos.x, pos.y, button_pause_0.dst_point, button_pause_0.dst_size))
			g_gameStatus.m_state = 17 - g_gameStatus.m_state;
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
	for(k = 0;k < TOOLS_NUM;k++)
		ToolPaint(hdcBuffer, hdcBmp, g_tools[k]);	
	for(k = 0;k < BUILDINGS_NUM;k++)
		BuildingPaint(hdcBuffer, hdcBmp, g_buildings[k]);
	HeroPaint(hdcBuffer, hdcBmp, g_hero[g_gameStatus.hero_type]);


	if(g_gameStatus.m_state / 4 == 0) //Before介绍界面
		BeforeStatePaint(hdcBuffer, hdcBmp);
	else if(g_gameStatus.m_state / 4 == 1) //开始界面
		BeginStatePaint(hdcBuffer, hdcBmp);
	else if(g_gameStatus.m_state / 4 == 2) //游戏进行界面
		RunStatePaint(hdcBuffer, hdcBmp);
	else if(g_gameStatus.m_state / 4 == 3) //死亡界面
		DeathStatePaint(hdcBuffer, hdcBmp);

	BitBlt(hdc, 0, 0, WIDTH * GRID, HEIGHT * GRID, hdcBuffer, 0, 0, SRCCOPY);

	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	EndPaint(hWnd, &ps);
	g_flag = TRUE;
}

//窗口摧毁
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

//Static元素位置初始化
VOID InitPos()
{
	int w = WIDTH * GRID;
	int h = HEIGHT * GRID;
	_PointF(hero_select_0.dst_point, w * 0.55, h * 0.3);
	_Size(hero_select_0.dst_size, w * 0.25, h * 0.4);

	_PointF(hero_select_1.dst_point, w * 0.2, h * 0.3);
	_Size(hero_select_1.dst_size, w * 0.25, h * 0.4);

	_PointF(author.dst_point, w * 0.3, h * 0.35);
	_Size(author.dst_size, w * 0.4, h * 0.4);

	_PointF(button_start_0.dst_point, w * 0.4, h * 0.25);
	_Size(button_start_0.dst_size, w * 0.2, h * 0.15);

	_PointF(button_start_1.dst_point, w * 0.4, h * 0.475);
	_Size(button_start_1.dst_size, w * 0.2, h * 0.15);

	_PointF(button_start_2.dst_point, w * 0.4, h * 0.75);
	_Size(button_start_2.dst_size, w * 0.2, h * 0.15);

	_PointF(button_return.dst_point, w * 0.45, h * 0.8);
	_Size(button_return.dst_size, w * 0.1, h * 0.1);

	_PointF(button_pause_0.dst_point, w * 0.1, h * 0.1);
	_Size(button_pause_0.dst_size, w * 0.1, h * 0.1);

	_PointF(button_pause_1.dst_point, w * 0.1, h * 0.1);
	_Size(button_pause_1.dst_size, w * 0.1, h * 0.1);

	_PointF(info_0_pos, w * 0.3, h * 0.3);
	_PointF(info_1_pos, w * 0.2, h * 0.4);
	_PointF(title_pos, w * 0.2, h * 0.1);
	_PointF(hint_pos, w * 0.3, h * 0.2);
	_PointF(score_pos, w * 0.88, h * 0.15);
	_PointF(coin_pos, w * 0.88, h * 0.2);
	_PointF(life_pos, w * 0.88, h * 0.25);
	_PointF(help_pos, w * 0.3, h * 0.35);
	_PointF(death_pos, w * 0.3, h * 0.2);
	_PointF(restart_pos, 0.3, 0.7);

	_Size(help_size, w * 0.4, h * 0.4);
	_Size(death_size, w * 0.4, h * 0.4);
}

//游戏初始化
VOID InitGame()
{
	PlaySound((LPCWSTR)IDR_BACKGROUND, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	toolCreate = FALSE;
	g_backgrounds[random(0, BACKGROUND_NUM-1)].visible = TRUE;
	int k;
	for(k = 0;k < HEROS_NUM;k++)
		g_hero[k].size.cx = -1;
	for(k = 0;k < BACKGROUND_NUM;k++)
		g_backgrounds[k].size.cx = -1;
	for(k = 0;k < BUILDINGS_NUM;k++)
		g_buildings[k].size.cx = -1;
	for(k = 0;k < TOOLS_NUM;k++)
		g_tools[k].size.cx = -1;
	GameStatusInit(g_gameStatus);
	HeroInit(g_hero[g_gameStatus.hero_type]);
	for(k = 0;k < BACKGROUND_NUM;k++)
		BackgroundInit(g_backgrounds[k]);
	g_buildings[0].pos.x = 0;
	g_buildings[0].pos.y = g_gameStatus.basic_high;
	g_buildings[0].size.cx = WIDTH;
	g_buildings[0].size.cy = HEIGHT - g_buildings[0].pos.y;
}

//Hero初始化
VOID HeroInit(Hero& hero)
{
	hero.size.cx = 2;
	hero.size.cy = 2;
	hero.pos.x = WIDTH / 3;
	hero.pos.y = g_gameStatus.basic_high - hero.size.cy;
	hero.m_speed = 0;
	hero.m_a = 0;
	hero.m_state = 0;
	hero.img_state = 0;
	hero.times = 2;
	hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
}

//GameStatus初始化
VOID GameStatusInit(GameStatus& gameStatus)
{
	gameStatus.isPaused = FALSE;
	gameStatus.m_frequency = 40;
	gameStatus.m_score = 0;
	gameStatus.m_state = 0;
	gameStatus.hero_type = 0;
	gameStatus.basic_high = 15;
	gameStatus.basic_x = WIDTH / 3;
	gameStatus.life = 1;
	gameStatus.m_coins = 0;
	gameStatus.moveX = moveX;
	gameStatus.backgroundMove = backgroundMove;
}

//Background初始化
VOID BackgroundInit(Background& background)
{
	background.pos.x = 0;
	background.pos.y = 0;
	background.size.cy = HEIGHT;
	background.size.cx = background.img_size.cx * background.size.cy / background.img_size.cy;
}

//Building初始化
VOID BuildingInit(Building& building)
{
	int tmp;
	while(TRUE)
	{
		tmp = random(0,2);
		if(tmp == 0)	//生成空段
		{
			if(abs(preBuilding.x - headX) > 0.00001)
				continue;
			headX += random(2,4);	//空段长度范围
			continue;
		}
		else if(tmp == 1)	//生成长草地
			building.size.cx = random(10,15);	//长草地长度范围
		else    //生成短草地
			building.size.cx = random(2,4);		//短草地长度范围
		break;
	}
	building.pos.x = headX;
	building.pos.y = random(Highest(headX, preBuilding), HEIGHT-1);
	building.size.cy = HEIGHT - building.pos.y;
	headX += building.size.cx;
	preBuilding.x = headX;
	preBuilding.y = building.pos.y;
	if(toolCreate)
 		CreateTool();
}

//Tool初始化
VOID ToolInit(Tool& tool)
{
	int cx;
	if(tool.m_type == 1 || tool.m_type == 3)
		cx = 2;
	else
		cx = 1;
	if(toolX + tool_gap_min + 1 + cx > g_buildings[building_now].pos.x + g_buildings[building_now].size.cx - 0.00001)
	{	
		building_now = (building_now + 1) % BUILDINGS_NUM;
		toolX = -(DOUBLE)tool_gap_min - 3;
	}
	if(abs(g_buildings[building_now].pos.y - preBuilding.y) < 0.00001 && abs(g_buildings[building_now].pos.x + g_buildings[building_now].size.cx - preBuilding.x) < 0.00001) return;
	if(tool.m_type == 1 || tool.m_type == 3)
	{
		tool.size.cx = 2;
		tool.size.cy = 2;
	}
	else
	{
		tool.size.cx = 1;
		tool.size.cy = 1;
	}
	DOUBLE max = (DOUBLE)tool_gap_max;	//两个道具的最大间隔
	if(abs(toolX+tool_gap_min+3) < 0.00001)
	{
		toolX = g_buildings[building_now].pos.x - tool.size.cx;
		if(g_buildings[building_now].size.cx - tool.size.cx + g_buildings[building_now].pos.x - toolX - tool.size.cx < max)
			max = g_buildings[building_now].size.cx - tool.size.cx + g_buildings[building_now].pos.x - toolX - tool.size.cx;
		tool.pos.x = random(max) + toolX + tool.size.cx;
	}
	else
	{
		if(g_buildings[building_now].size.cx - tool.size.cx + g_buildings[building_now].pos.x - toolX - tool.size.cx - tool_gap_min < max)	// 3为两个道具的最小间隔
			max = g_buildings[building_now].size.cx - tool.size.cx + g_buildings[building_now].pos.x - toolX - tool.size.cx - tool_gap_min;
		tool.pos.x = random(max) + toolX + tool.size.cx + tool_gap_min;
	}
	if(tool.down)
		tool.pos.y = g_buildings[building_now].pos.y - tool.size.cy;
	else
		tool.pos.y = g_buildings[building_now].pos.y - tool.size.cy - random(3);	//3为道具离地最高高度
	toolX = tool.pos.x;
}

//Tool带参数初始化
VOID ToolInit(Tool& tool, DOUBLE x, DOUBLE y, UINT cx, UINT cy)
{
	tool.pos.x = x;
	tool.pos.y = y;
	tool.size.cx = cx;
	tool.size.cy = cy;
}

//Hero更新
VOID HeroUpdate(Hero& hero)         
{
	//TODO
	if(hero.size.cx == -1) return;
	if(g_gameStatus.m_state / 4 == 0 || g_gameStatus.m_state / 4 == 3 || g_gameStatus.m_state == 9) return;
	if(hero.m_state != 0 && (((g_times < tool_start) && (g_times + INT_MAX - tool_start > 250)) || (g_times - tool_start > 250)))
	{
		g_gameStatus.moveX = moveX;
		g_gameStatus.backgroundMove = backgroundMove;
		hero.m_state = 0;
		hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
	}
	//Move
	HeroMove(hero);
	//Jump
	if(hero.m_state == 2)
		hero.pos.y = 1;
	else
		HeroJump(hero);
	//Touch
	HeroTouch(hero);
	if(hero.pos.y > HEIGHT - 0.00001)
	{
		g_gameStatus.m_state = 12;
		if(g_gameStatus.hero_type == 0)
			PlaySound((LPCWSTR)IDR_DIE_0, NULL, SND_RESOURCE | SND_ASYNC);
		else
			PlaySound((LPCWSTR)IDR_DIE_1, NULL, SND_RESOURCE | SND_ASYNC);
	}
}

//GameStatus更新
VOID GameStatusUpdate(GameStatus& gameStatus)
{
	//TODO
	//游戏重新开始
	if(g_gameStatus.m_state / 4 == 3 && g_keyState[VK_RETURN])
	{
		g_gameStatus.m_state = 4;
		InitGame();
	}
	//游戏进行中
	if(g_gameStatus.m_state / 4 == 2)
		g_gameStatus.m_score += g_gameStatus.m_frequency * 50 / 1000;
}

//Background更新
VOID BackgroundUpdate(Background& background)
{
	//TODO
	if(background.size.cx == -1) return;
	if(!background.visible) return;
	background.pos.x -= g_gameStatus.backgroundMove;
	if(background.pos.x + background.size.cx < WIDTH + 0.00001 && background.pos.x + background.size.cx + g_gameStatus.backgroundMove > WIDTH)
	{
		int id = 0;
		for(id = 0;id < BACKGROUND_NUM;id++)
			if(g_backgrounds[id].visible)
				break;
		int i = random(0, BACKGROUND_NUM-1);
		while(i == id)
			i = random(0, BACKGROUND_NUM-1);
		g_backgrounds[i].visible = TRUE;
		int j, k;
		for(j = 0;j < HEIGHT;j++)
		{
			k = FindNextToolByType(2);
			ToolInit(g_tools[k], background.pos.x + background.size.cx, j, 1, 1);
		}
		g_backgrounds[i].pos.x = background.pos.x + background.size.cx + 1;
	}
	if(background.pos.x + background.size.cx < 0)
	{
		background.pos.x = 0;
		background.visible = FALSE;
	}
}

//Building更新
VOID BuildingUpdate(Building& building)
{
	//TODO
	if(building.size.cx == -1) return;
	if(g_gameStatus.m_state <= 0) return;
	building.pos.x -= g_gameStatus.moveX;
	if(building.pos.x + building.size.cx < 0)
		BuildingInit(building);
}

//Tool更新
VOID ToolUpdate(Tool& tool)
{
	//TODO
	if(tool.size.cx == -1) return;
	if(tool.m_type == 7)
	{
		tool.img_state += 0.5;
		if(tool.img_state >= 8)
			tool.img_state -= 8;
	}
	if(tool.m_type == 2)
		tool.pos.x -= g_gameStatus.backgroundMove;
	else
		tool.pos.x -= g_gameStatus.moveX;
	if(tool.m_type == 0)
	{
		double tmp = random(1);
		if(tmp < 0.3)
			tool.pos.x -= g_gameStatus.moveX * 0.2;
		else if(tmp < 0.6)
			tool.pos.x += g_gameStatus.moveX * 0.2;
	}
	if(tool.pos.x + tool.size.cx < 0)
	{
 		tool.size.cx = -1;
		tool_id[tool.m_type][0]++;
		tool_id[tool.m_type][tool_id[tool.m_type][0]] = tool.id;
	}
}

//定时查看按键状态
VOID KeyUpdate()
{
	//TODO
	int k;
	for(k = 1;k < 255;k++)
		if(GetKeyState(k) < 0)
			g_keyState[k] = TRUE;
		else
			g_keyState[k] = FALSE;
}

//Hero绘制
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero)
{
	if(hero.size.cx == -1) return;
	if(g_gameStatus.m_state / 4 == 0) return;
	PicturePaint(hdcBuffer, hdcBmp, hero.img, hero.pos.x * GRID, hero.pos.y * GRID, hero.size.cx * GRID, hero.size.cy * GRID, hero.img_point.x, int(hero.img_state) * hero.img_size.cy, hero.img_size.cx, hero.img_size.cy - 20);
}

//Background绘制
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background)
{
	if(background.size.cx == -1) return;
	if(g_gameStatus.m_state / 4 == 0) return;
	if(!background.visible) return;
	if(outView(background)) return;
	PicturePaint(hdcBuffer, hdcBmp, background.img, background.pos.x * GRID, background.pos.y * GRID, background.size.cx * GRID, background.size.cy * GRID, background.img_point.x, background.img_point.y, background.img_size.cx, background.img_size.cy);
}

//Building绘制
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building)
{
	if(building.size.cx == -1) return;
	if(g_gameStatus.m_state / 4 == 0) return;
	if(outView(building)) return;
	int i, j;
	for(i = 0;i < building.size.cx;i++)
	{
		PicturePaint(hdcBuffer, hdcBmp, building.img, (building.pos.x + i) * GRID, building.pos.y * GRID, GRID, GRID, building.roof_point.x, building.roof_point.y, building.roof_size.cx, building.roof_size.cy);
		for(j = 1;j < building.size.cy;j++)
			PicturePaint(hdcBuffer, hdcBmp, building.img, (building.pos.x + i) * GRID, (building.pos.y + j) * GRID, GRID, GRID, building.block_point.x, building.block_point.y, building.block_size.cx, building.block_size.cy);
	}
}

//Tool绘制
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool)
{
	if(tool.size.cx == -1) return;
	if(outView(tool)) return;
	PicturePaint(hdcBuffer, hdcBmp, tool.img, tool.pos.x * GRID, tool.pos.y * GRID, tool.size.cx * GRID, tool.size.cy * GRID, tool.img_point.x, int(tool.img_state) * tool.img_size.cy, tool.img_size.cx, tool.img_size.cy);
}
