/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black_Tool.cpp
* 摘	要：跑酷游戏工程工具函数定义
*
* 当前版本：1.3
* 作	者: Krystal/甘茂霖
* 完成日期：2015年12月7日
*
* 取代版本：1.2
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年12月6日
*/

#include "stdafx.h"
#include "Running-Black.h"

//绘制纯色背景
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	SelectObject(hdcBuffer, hBrush);
	Rectangle(hdcBuffer, x, y, x + width, y + height);
}

//设置文字大小，颜色，字体
VOID SetFont(HDC hdcBuffer, LONG size, COLORREF color, BYTE family = GB2312_CHARSET)
{
	LOGFONT logfont;
	ZeroMemory(&logfont, sizeof(LOGFONT));
	logfont.lfCharSet = family;
	logfont.lfHeight = size;
	HFONT hFont = CreateFontIndirect(&logfont);

	SetTextColor(hdcBuffer, color);
	SetBkMode(hdcBuffer, TRANSPARENT);
	SelectObject(hdcBuffer, hFont);
}

//绘制图片
VOID PicturePaint(HDC hdcBuffer, HDC hdcBmp, HBITMAP bmp, DOUBLE x, DOUBLE y, UINT width, UINT height, UINT sx, UINT sy, UINT sw, UINT sh)
{
	SelectObject(hdcBmp, bmp);
	TransparentBlt(hdcBuffer, x, y, width, height, hdcBmp, sx, sy, sw, sh, RGB(255,255,255));
}

//Before介绍界面
VOID BeforeStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	if(g_times < 25)
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
	else if(g_times < 89)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		SetFont(hdcBuffer, 80, RGB(4*(g_times-25),4*(g_times-25),4*(g_times-25)));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
	}
	else if(g_times < 100)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		SetFont(hdcBuffer, 80, RGB(255,255,255));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
	}
	else if(g_times < 164)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(4*(g_times-100),4*(g_times-100),4*(g_times-100)), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		SetFont(hdcBuffer, 80, RGB(255,255,255));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
	}
	else if(g_times < 189)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(255,255,255), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, -WIDTH * GRID * 0.1 + (g_times - 164) * (WIDTH * GRID * 0.45 / 25), (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_1.img_point.x, hero_select_1.img_point.y, 
			hero_select_1.img_size.cx, hero_select_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_0.img, WIDTH * GRID - (g_times - 164) * (WIDTH * GRID * 0.45 / 25), (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_0.img_point.x, hero_select_0.img_point.y, 
			hero_select_0.img_size.cx, hero_select_0.img_size.cy);
	}	
	else if(g_times < 200)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(255,255,255), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, -WIDTH * GRID * 0.1 + WIDTH * GRID * 0.45, (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_1.img_point.x, hero_select_1.img_point.y, 
			hero_select_1.img_size.cx, hero_select_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_0.img, WIDTH * GRID - WIDTH * GRID * 0.45, (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_0.img_point.x, hero_select_0.img_point.y, 
			hero_select_0.img_size.cx, hero_select_0.img_size.cy);
	}
	else if(g_times < 264)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(255-4*(g_times-200),255-4*(g_times-200),255-4*(g_times-200)), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, -WIDTH * GRID * 0.1 + WIDTH * GRID * 0.45, (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2 - (g_times-200) * HEIGHT * GRID * 0.5 / 30,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_1.img_point.x, hero_select_1.img_point.y, 
			hero_select_1.img_size.cx, hero_select_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_0.img, WIDTH * GRID - WIDTH * GRID * 0.45, (HEIGHT * GRID - WIDTH * GRID * 0.1) / 2 + (g_times-200) * HEIGHT * GRID * 0.5 / 30,
			WIDTH * GRID * 0.1, WIDTH * GRID * 0.1, hero_select_0.img_point.x, hero_select_0.img_point.y, 
			hero_select_0.img_size.cx, hero_select_0.img_size.cy);
	}
	else if(g_times < 300)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(255,255,255), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, 0.2 * WIDTH * GRID, 0.1 * HEIGHT * GRID, 0.6 * WIDTH * GRID, 0.8 * HEIGHT * GRID,
			hero_select_1.img_point.x, hero_select_1.img_point.y, hero_select_1.img_size.cx, hero_select_1.img_size.cy);
	}
	else
	{
		g_gameStatus.m_state = 4;
	}
}

//开始界面
VOID BeginStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	int state = g_gameStatus.m_state % 4;
	if(state == 0)
	{
		SetFont(hdcBuffer, 80, RGB(86,170,255));
		TextOut(hdcBuffer, title_pos.x, title_pos.y, _T("罗小黑历险记"), 6);
		PicturePaint(hdcBuffer, hdcBmp, button_start_0.img, button_start_0.dst_point.x, button_start_0.dst_point.y, button_start_0.dst_size.cx, button_start_0.dst_size.cy,
			button_start_0.img_point.x, button_start_0.img_point.y, button_start_0.img_size.cx, button_start_0.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_start_1.img, button_start_1.dst_point.x, button_start_1.dst_point.y, button_start_1.dst_size.cx, button_start_1.dst_size.cy,
			button_start_1.img_point.x, button_start_1.img_point.y, button_start_1.img_size.cx, button_start_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_start_2.img, button_start_2.dst_point.x, button_start_2.dst_point.y, button_start_2.dst_size.cx, button_start_2.dst_size.cy,
			button_start_2.img_point.x, button_start_2.img_point.y, button_start_2.img_size.cx, button_start_2.img_size.cy);
	}
	else if(state == 1)
	{
		SetFont(hdcBuffer, 60, RGB(255,170,86));
		TextOut(hdcBuffer, hint_pos.x, hint_pos.y, _T("选择人物"), 4);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, hero_select_1.dst_point.x, hero_select_1.dst_point.y, hero_select_1.dst_size.cx, hero_select_1.dst_size.cy,
			hero_select_1.img_point.x, hero_select_1.img_point.y, hero_select_1.img_size.cx, hero_select_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_0.img, hero_select_0.dst_point.x, hero_select_0.dst_point.y, hero_select_0.dst_size.cx, hero_select_0.dst_size.cy,
			hero_select_0.img_point.x, hero_select_0.img_point.y, hero_select_0.img_size.cx, hero_select_0.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_return.img, button_return.dst_point.x, button_return.dst_point.y, button_return.dst_size.cx, button_return.dst_size.cy,
			button_return.img_point.x, button_return.img_point.y, button_return.img_size.cx, button_return.img_size.cy);
	}
	else if(state == 2)
	{
		SetFont(hdcBuffer, 60, RGB(255,170,86));
		TextOut(hdcBuffer, hint_pos.x, hint_pos.y, _T("游戏帮助"), 4);
		SolidBackgroundPaint(hdcBuffer, RGB(220,220,220), help_pos.x, help_pos.y, help_size.cx, help_size.cy);
		SetFont(hdcBuffer, 30, RGB(0,0,0));
		TextOut(hdcBuffer, help_pos.x * 1.1, help_pos.y * 1.1, _T("我是游戏帮助"), 6);
		PicturePaint(hdcBuffer, hdcBmp, button_return.img, button_return.dst_point.x, button_return.dst_point.y, button_return.dst_size.cx, button_return.dst_size.cy,
			button_return.img_point.x, button_return.img_point.y, button_return.img_size.cx, button_return.img_size.cy);
	}
	else if(state == 3)
	{
		SetFont(hdcBuffer, 60, RGB(255,170,86));
		TextOut(hdcBuffer, WIDTH * GRID * 0.25, HEIGHT * GRID * 0.2, _T("关于作者"), 4);
		PicturePaint(hdcBuffer, hdcBmp, author.img, author.dst_point.x, author.dst_point.y, author.dst_size.cx, author.dst_size.cy,
			author.img_point.x, author.img_point.y, author.img_size.cx, author.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_return.img, button_return.dst_point.x, button_return.dst_point.y, button_return.dst_size.cx, button_return.dst_size.cy,
			button_return.img_point.x, button_return.img_point.y, button_return.img_size.cx, button_return.img_size.cy);
	}
}

//游戏进行界面
VOID RunStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	if(g_gameStatus.isPaused)
		PicturePaint(hdcBuffer, hdcBmp, button_pause_0.img, button_pause_0.dst_point.x, button_pause_0.dst_point.y, button_pause_0.dst_size.cx, button_pause_0.dst_size.cy,
		button_pause_0.img_point.x, button_pause_0.img_point.y, button_pause_0.img_size.cx, button_pause_0.img_size.cy);
	else
		PicturePaint(hdcBuffer, hdcBmp, button_pause_1.img, button_pause_1.dst_point.x, button_pause_1.dst_point.y, button_pause_1.dst_size.cx, button_pause_1.dst_size.cy,
		button_pause_1.img_point.x, button_pause_1.img_point.y, button_pause_1.img_size.cx, button_pause_1.img_size.cy);
	SetFont(hdcBuffer, 20, RGB(255,255,255));
	TCHAR	szBuffer[30];
	TextOut(hdcBuffer, score_pos.x, score_pos.y, szBuffer, wsprintf(szBuffer, _T("得分:%d"), int(g_gameStatus.m_score)));
	TextOut(hdcBuffer, coin_pos.x, coin_pos.y, szBuffer, wsprintf(szBuffer, _T("金币:%d"), g_gameStatus.m_coins));
	TextOut(hdcBuffer, life_pos.x, life_pos.y, szBuffer, wsprintf(szBuffer, _T("生命:%d"), g_gameStatus.life));
}

//死亡界面
VOID DeathStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	SolidBackgroundPaint(hdcBuffer, RGB(255,255,255), death_pos.x, death_pos.y, death_size.cx, death_size.cy);
	SetFont(hdcBuffer, 40, RGB(255,255,255));
	TCHAR	szBuffer[30];
	TextOut(hdcBuffer, score_pos.x, score_pos.y, szBuffer, wsprintf(szBuffer, _T("得分:%d"), int(g_gameStatus.m_score)));
	TextOut(hdcBuffer, coin_pos.x, coin_pos.y, szBuffer, wsprintf(szBuffer, _T("金币:%d"), g_gameStatus.m_coins));
	TextOut(hdcBuffer, life_pos.x, life_pos.y, szBuffer, wsprintf(szBuffer, _T("生命:%d"), g_gameStatus.life));
	if(g_times % 10 < 5)
	{
		SetFont(hdcBuffer, 50, RGB(255,255,255));
		TextOut(hdcBuffer, restart_pos.x, restart_pos.y, _T("Press Enter To Restart"), 22);
	}
}

//Hero移动处理
VOID HeroMove(Hero& hero)
{
	//TODO
	if(g_gameStatus.hero_type == 1)
	{
		hero.img_state += g_gameStatus.moveX * 2;
		if(hero.img_state >= 9)
			hero.img_state -= 9;
	}
	else{
		if(hero.m_state == 0)
		{
			hero.img_state += g_gameStatus.moveX * 2.5;
			if(hero.img_state >= 12)
				hero.img_state -= 12;
		}
		else if(hero.m_state == 1)
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 5)
				hero.img_state -= 5;
		}
		else if(hero.m_state == 2)
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 6)
				hero.img_state -= 6;
		}
		else if(hero.m_state == 3)
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 12)
				hero.img_state -= 12;
		}
	}
	if(hero.pos.x < g_gameStatus.basic_x)
		hero.pos.x += g_gameStatus.moveX / 5;
}

//Hero跳跃处理
VOID HeroJump(Hero& hero)
{
	//TODO
	if(GetKeyState(VK_SPACE) < 0  && !g_keyState[VK_SPACE] && hero.times > 0)
	{
		hero.m_a = -1.6;
		hero.m_speed = 0;
		hero.times -= 1;
	}
	else
		hero.m_a = 0.2;
	hero.m_speed += hero.m_a;
	hero.pos.y += hero.m_speed;
}

//Hero碰撞处理
VOID HeroTouch(Hero& hero)
{
	//TODO
	int k;
	for(k = 0;k < BUILDINGS_NUM;k++)
	{
		if(g_buildings[k].size.cx == -1) continue;
		//TODO 判断g_buildings[k]与hero接触
		if(hero.pos.x + hero.size.cx > g_buildings[k].pos.x + 0.00001 && hero.pos.x + 0.5 * hero.size.cx < g_buildings[k].pos.x - 0.00001 && hero.pos.y + hero.size.cy > g_buildings[k].pos.y + 0.00001)
		{
 			hero.pos.x = g_buildings[k].pos.x - hero.size.cx;
		}
		else if(hero.pos.x + hero.size.cx > g_buildings[k].pos.x + 0.00001 && hero.pos.x < g_buildings[k].pos.x + g_buildings[k].size.cx - 0.00001 && hero.pos.y + hero.size.cy > g_buildings[k].pos.y + 0.00001 && hero.pos.y + hero.size.cy - hero.m_speed < g_buildings[k].pos.y + 0.00001)
		{
			hero.m_a = 0;
			hero.m_speed = 0;
			hero.pos.y = g_buildings[k].pos.y - hero.size.cy;
			hero.times = 2;
		}
	}
	for(k = 0;k < TOOLS_NUM;k++)
	{
		if(g_tools[k].size.cx == -1) continue;
		//TODO 判断g_tools[k]与hero接触
		if(hero.m_state == 2)
		{
			if(g_tools[k].m_type == 7 && g_tools[k].pos.x < hero.pos.x + 5)
			{
				g_tools[k].pos.x -= (g_tools[k].pos.x - hero.pos.x) * 0.2;
				g_tools[k].pos.y -= (g_tools[k].pos.y - hero.pos.y) * 0.2;
				if(g_tools[k].pos.x - hero.pos.x < 1 && g_tools[k].pos.y - hero.pos.y < 0.5)
				{
					g_gameStatus.m_coins += 1;
					g_tools[k].size.cx = -1;
				}
			}
		}
		else if(InArea(g_tools[k].pos.x, g_tools[k].pos.y, hero.pos, hero.size) || InArea(g_tools[k].pos.x + g_tools[k].size.cx, g_tools[k].pos.y, hero.pos, hero.size) 
			|| InArea(g_tools[k].pos.x, g_tools[k].pos.y + g_tools[k].size.cy, hero.pos, hero.size) 
			|| InArea(g_tools[k].pos.x + g_tools[k].size.cx, g_tools[k].pos.y + g_tools[k].size.cy, hero.pos, hero.size))
		{
 			if(g_tools[k].solid)
			{
				if(hero.pos.x + hero.size.cx > g_tools[k].pos.x + 0.00001 && hero.pos.x + 0.5 * hero.size.cx < g_tools[k].pos.x - 0.00001)
					hero.pos.x = g_tools[k].pos.x - hero.size.cx;
				else if(hero.pos.x + hero.size.cx > g_tools[k].pos.x + 0.00001 && hero.pos.x < g_tools[k].pos.x + g_tools[k].size.cx - 0.00001)
				{
					hero.m_a = 0;
					hero.m_speed = 0;
					hero.pos.y = g_tools[k].pos.y - hero.size.cy;
					hero.times = 2;
				}
			}
			if(g_tools[k].disappear)
				g_tools[k].size.cx = -1;
			if(g_tools[k].m_type == 0)
			{
				g_gameStatus.life--;
				if(g_gameStatus.life == 0)
				{
					g_gameStatus.m_state = 12;
					if(g_gameStatus.hero_type == 0)
						PlaySound((LPCWSTR)IDR_DIE_0, NULL, SND_RESOURCE | SND_ASYNC);
					else
						PlaySound((LPCWSTR)IDR_DIE_1, NULL, SND_RESOURCE | SND_ASYNC);
				}
			}
			else if(g_tools[k].m_type == 4)
				g_gameStatus.life++;
			else if(g_tools[k].m_type == 5)
			{
				if(hero.m_state == 3)
				{
					g_gameStatus.moveX = moveX;
					g_gameStatus.backgroundMove = backgroundMove;
					hero.m_state = 0;
					hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
				}
				else
				{
					tool_start = g_times;
					g_gameStatus.moveX = 2 * moveX;;
					g_gameStatus.backgroundMove = 2 * backgroundMove;
					hero.m_state = 1;
					if(g_gameStatus.hero_type == 0)
						hero.img = hero_bmps[1].img;
				}
			}
			else if(g_tools[k].m_type == 6)
			{
				if(hero.m_state == 1)
				{
					g_gameStatus.moveX = moveX;
					g_gameStatus.backgroundMove = backgroundMove;
					hero.m_state = 0;
					hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
				}
				tool_start = g_times;
				g_gameStatus.moveX = moveX / 2;
				g_gameStatus.backgroundMove = backgroundMove / 2;
				hero.m_state = 3;
				if(g_gameStatus.hero_type == 0)
					hero.img = hero_bmps[0].img;
			}
			else if(g_tools[k].m_type == 7)
				g_gameStatus.m_coins += 1;
			else if(g_tools[k].m_type == 8)
			{
				tool_start = g_times;
				g_gameStatus.moveX = 3 * moveX;
				g_gameStatus.backgroundMove = 3 * backgroundMove;
				hero.m_state = 2;
				if(g_gameStatus.hero_type == 0)
					hero.img = hero_bmps[2].img;
			}
		}
	}
}

//生成道具
VOID CreateTool()
{
	while(abs(g_buildings[building_now].pos.y - preBuilding.y) > 0.00001 || abs(g_buildings[building_now].pos.x + g_buildings[building_now].size.cx - preBuilding.x) > 0.00001)
	{
		DOUBLE tmp = random(1);
		if(tmp < 0.3) //生成tool_7 金币
		{
			int id = FindNextToolByType(7);
			int i = 0, j = 0;
			ToolInit(g_tools[id]);
			if(g_tools[id].size.cx == -1) break;
			toolX = g_tools[id].pos.x + 4;
			tmp = random(1);
			if(tmp < 0.2)
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 1;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y - 2 + abs(i - 2), 1, 1);
				}
			}
			else if(tmp < 0.4)
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 3;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y + 2 - abs(i - 2), 1, 1);
				}
			}
			else if(tmp < 0.6)
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 3;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y + 2 - abs(i - 2), 1, 1);
				}
				for(i = 1;i < 4;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y - abs(i - 2), 1, 1);
				}
			}
			else if(tmp < 0.8)
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 3;
				for(i = 1;i < 3;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + 2 * i, g_tools[id].pos.y, 1, 1);
				}
				j = FindNextToolByType(7);
				ToolInit(g_tools[j], g_tools[id].pos.x + 2, g_tools[id].pos.y - 2, 1, 1);
				j = FindNextToolByType(7);
				ToolInit(g_tools[j], g_tools[id].pos.x + 1, g_tools[id].pos.y + 2, 1, 1);
				j = FindNextToolByType(7);
				ToolInit(g_tools[j], g_tools[id].pos.x + 3, g_tools[id].pos.y + 2, 1, 1);
			}
			else
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 3;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y + 2 - abs(i - 2), 1, 1);
				}
				for(i = 1;i < 4;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y - 2 + abs(i - 2), 1, 1);
				}
			}
		}
		else if(tmp < 0.375)
			ToolInit(g_tools[FindNextToolByType(5)]);
		else if(tmp < 0.45)
			ToolInit(g_tools[FindNextToolByType(6)]);
		else if(tmp < 0.525)
			ToolInit(g_tools[FindNextToolByType(4)]);
		else if(tmp < 0.6)
			ToolInit(g_tools[FindNextToolByType(8)]);
		else if(tmp < 0.8)
			ToolInit(g_tools[FindNextToolByType(0)]);
		else if(tmp < 0.9)
			ToolInit(g_tools[FindNextToolByType(1)]);
		else 
			ToolInit(g_tools[FindNextToolByType(3)]);
	}
}

//生成[a,b]之间的随机数
UINT random(UINT a, UINT b)
{
	if(a == b) return a;
	return rand() % (b-a+1) + a;
}

DOUBLE random(DOUBLE b)
{
	return (DOUBLE)rand() / RAND_MAX * b;
}

//随机生成草地的最高高度
UINT Highest(DOUBLE x, POINTF pre)
{
	//TODO
	return pre.y - 3;
}

//超出视野范围
BOOL outView(Building& building)
{
	return (building.pos.x >= WIDTH || building.pos.x + building.size.cx < 0);
}

BOOL outView(Tool& tool)
{
	return (tool.pos.x >= WIDTH || tool.pos.x + tool.size.cx < 0);
}

BOOL outView(Background& background)
{
	return (background.pos.x >= WIDTH || background.pos.x + background.size.cx < 0);
}

//查找下一个可用的道具下标
UINT FindNextToolByType(UINT type)
{
	UINT result = tool_id[type][tool_id[type][0]];
	tool_id[type][0]--;
	return result;
}

//判断某点是否在某区域内
BOOL InArea(DOUBLE x, DOUBLE y, POINTF lPoint, SIZE size)
{
	return (x > lPoint.x - 0.00001 && x < lPoint.x + size.cx + 0.00001 && y > lPoint.y - 0.00001 && y < lPoint.y + size.cy + 0.00001);
}

//POS初始化
VOID _PointF(POINTF& pos, DOUBLE x, DOUBLE y)
{
	pos.x = x;
	pos.y = y;
}

//SIZE初始化
VOID _Size(SIZE& size, UINT cx, UINT cy)
{
	size.cx = cx;
	size.cy = cy;
}