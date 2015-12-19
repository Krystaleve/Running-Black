/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black_Tool.cpp
* 摘	要：跑酷游戏工程工具函数定义
*
* 当前版本：2.1
* 作	者: Krystal/甘茂霖
* 完成日期：2015年12月18日
*
* 取代版本：1.6
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年12月16日
*/

#include "stdafx.h"
#include "Running-Black.h"

//绘制纯色背景，不带边框
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	SelectObject(hdcBuffer, hBrush);
	Rectangle(hdcBuffer, x, y, x + width, y + height);
	DeleteObject(hBrush);
}

//绘制边框
VOID NullBackgroundPaint(HDC hdcBuffer, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height, COLORREF penColor)
{
	HBRUSH hBrush;
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(hdcBuffer, hBrush);
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 3, penColor);
	Rectangle(hdcBuffer, x, y, x + width, y + height);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

//绘制纯色背景，带边框
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height, COLORREF penColor)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	SelectObject(hdcBuffer, hBrush);
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 3, penColor);
	Rectangle(hdcBuffer, x, y, x + width, y + height);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

//设置文字大小，颜色，字体
HFONT SetFont(HDC hdcBuffer, LONG size, COLORREF color, BYTE family = GB2312_CHARSET)
{
	LOGFONT logfont;
	ZeroMemory(&logfont, sizeof(LOGFONT));
	logfont.lfCharSet = family;
	logfont.lfHeight = size;
	lstrcpy(logfont.lfFaceName, _T("华文行楷"));
	HFONT hFont = CreateFontIndirect(&logfont);

	SetTextColor(hdcBuffer, color);
	SetBkMode(hdcBuffer, TRANSPARENT);
	SelectObject(hdcBuffer, hFont);
	return hFont;
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
	g_gameStatus.m_state = 4;return;
	if(g_times < 25)
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
	else if(g_times < 89)	//淡入淡出效果
	{
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		HFONT font = SetFont(hdcBuffer, 80, RGB(4*(g_times-25),4*(g_times-25),4*(g_times-25)));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
		DeleteObject(font);
	}
	else if(g_times < 100)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(0,0,0), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		HFONT font = SetFont(hdcBuffer, 80, RGB(255,255,255));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
		DeleteObject(font);
	}
	else if(g_times < 164)
	{
		SolidBackgroundPaint(hdcBuffer, RGB(4*(g_times-100),4*(g_times-100),4*(g_times-100)), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		HFONT font = SetFont(hdcBuffer, 80, RGB(255,255,255));
		TextOut(hdcBuffer, info_0_pos.x, info_0_pos.y, _T("Author:"), 7);
		TextOut(hdcBuffer, info_1_pos.x, info_1_pos.y, _T("Krystal(甘茂霖)"), 12);
		DeleteObject(font);
	}
	else if(g_times < 189)	//移入效果
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
	else if(g_times < 300)	//神烦狗镇楼
	{
		SolidBackgroundPaint(hdcBuffer, RGB(255,255,255), 0, 0, WIDTH * GRID, HEIGHT * GRID);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, 0.2 * WIDTH * GRID, 0.1 * HEIGHT * GRID, 0.6 * WIDTH * GRID, 0.8 * HEIGHT * GRID,
			hero_select_1.img_point.x, hero_select_1.img_point.y, hero_select_1.img_size.cx, hero_select_1.img_size.cy);
	}
	else //进入开始界面
	{
		g_gameStatus.m_state = 4;
	}
}

//开始界面
VOID BeginStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	int state = g_gameStatus.m_state % 4;
	if(state == 0)	//选择菜单界面
	{
		HFONT font = SetFont(hdcBuffer, 80, RGB(220,0,255));
		TextOut(hdcBuffer, title_pos.x, title_pos.y, _T("罗小黑历险记"), 6);
		DeleteObject(font);
		PicturePaint(hdcBuffer, hdcBmp, button_start_0.img, button_start_0.dst_point.x, button_start_0.dst_point.y, button_start_0.dst_size.cx, button_start_0.dst_size.cy,
			button_start_0.img_point.x, button_start_0.img_point.y, button_start_0.img_size.cx, button_start_0.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_start_1.img, button_start_1.dst_point.x, button_start_1.dst_point.y, button_start_1.dst_size.cx, button_start_1.dst_size.cy,
			button_start_1.img_point.x, button_start_1.img_point.y, button_start_1.img_size.cx, button_start_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_start_2.img, button_start_2.dst_point.x, button_start_2.dst_point.y, button_start_2.dst_size.cx, button_start_2.dst_size.cy,
			button_start_2.img_point.x, button_start_2.img_point.y, button_start_2.img_size.cx, button_start_2.img_size.cy);
	}
	else if(state == 1)	//选择人物界面
	{
		HFONT font = SetFont(hdcBuffer, 60, RGB(123,0,255));
		TextOut(hdcBuffer, hint_pos.x, hint_pos.y, _T("选择人物"), 4);
		DeleteObject(font);
		NullBackgroundPaint(hdcBuffer, hero_select_1.dst_point.x, hero_select_1.dst_point.y, hero_select_1.dst_size.cx, hero_select_1.dst_size.cy, RGB(255,255,255));
		NullBackgroundPaint(hdcBuffer, hero_select_0.dst_point.x, hero_select_0.dst_point.y, hero_select_0.dst_size.cx, hero_select_0.dst_size.cy, RGB(255,255,255));
		PicturePaint(hdcBuffer, hdcBmp, hero_select_1.img, hero_select_1.dst_point.x, hero_select_1.dst_point.y, hero_select_1.dst_size.cx, hero_select_1.dst_size.cy,
			hero_select_1.img_point.x, hero_select_1.img_point.y, hero_select_1.img_size.cx, hero_select_1.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, hero_select_0.img, hero_select_0.dst_point.x, hero_select_0.dst_point.y, hero_select_0.dst_size.cx, hero_select_0.dst_size.cy,
			hero_select_0.img_point.x, hero_select_0.img_point.y, hero_select_0.img_size.cx, hero_select_0.img_size.cy);
		PicturePaint(hdcBuffer, hdcBmp, button_return.img, button_return.dst_point.x, button_return.dst_point.y, button_return.dst_size.cx, button_return.dst_size.cy,
			button_return.img_point.x, button_return.img_point.y, button_return.img_size.cx, button_return.img_size.cy);
	}
	else if(state == 2)	//关于游戏界面
	{
		HFONT font = SetFont(hdcBuffer, 60, RGB(21,0,255));
		TextOut(hdcBuffer, hint_pos.x, hint_pos.y, _T("关于游戏"), 4);
		DeleteObject(font);
		NullBackgroundPaint(hdcBuffer, help_pos.x, help_pos.y, help_size.cx, help_size.cy, RGB(255,0,0));
		font = SetFont(hdcBuffer, 20, RGB(255,67,0));
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 20, _T("本游戏为横板跑酷游戏，无最终关卡，可不断挑战更高难度"),26);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 40, _T("游戏操作：空格键跳跃"),11);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 60, _T("游戏道具："), 5);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 80, _T("减速蘑菇（蓝），加速蘑菇（红），爱心，西瓜（飞起）"), 25);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 100, _T("死亡条件：掉落悬崖/碰到飞镖"), 14);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 120, _T("注:开局以及死亡时会有一定时间的无敌状态，不惧飞镖"), 25);
		TextOut(hdcBuffer, help_pos.x + 20, help_pos.y + 140, _T("祝您玩得愉快！"), 7);
		DeleteObject(font);
		PicturePaint(hdcBuffer, hdcBmp, button_return.img, button_return.dst_point.x, button_return.dst_point.y, button_return.dst_size.cx, button_return.dst_size.cy,
			button_return.img_point.x, button_return.img_point.y, button_return.img_size.cx, button_return.img_size.cy);
	}
	else if(state == 3) //关于作者界面
	{
		HFONT font = SetFont(hdcBuffer, 60, RGB(0,161,255));
		TextOut(hdcBuffer, hint_pos.x, hint_pos.y, _T("关于作者"), 4);
		DeleteObject(font);
		NullBackgroundPaint(hdcBuffer, author.dst_point.x, author.dst_point.y, author.dst_size.cx, author.dst_size.cy, RGB(0,0,0));
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
	HFONT font = SetFont(hdcBuffer, 20, RGB(181,114,124));
	TCHAR	szBuffer[30];
	TextOut(hdcBuffer, score_pos.x, score_pos.y, szBuffer, wsprintf(szBuffer, _T("得分:%d"), int(g_gameStatus.m_score)));
	TextOut(hdcBuffer, coin_pos.x, coin_pos.y, szBuffer, wsprintf(szBuffer, _T("金币:%d"), g_gameStatus.m_coins));
	TextOut(hdcBuffer, life_pos.x, life_pos.y, szBuffer, wsprintf(szBuffer, _T("生命:%d"), g_gameStatus.life));
	DeleteObject(font);
}

//死亡界面
VOID DeathStatePaint(HDC hdcBuffer, HDC hdcBmp)
{
	int score = 0;
	int coin = 0;
	FILE *fp;
	if(fp=fopen(".history","rb"))
	{
		fscanf(fp, "%d%d", &score, &coin);
		fclose(fp);
	}
	NullBackgroundPaint(hdcBuffer, death_pos.x, death_pos.y, death_size.cx, death_size.cy, RGB(255,255,255));
	TCHAR	szBuffer[30];
	HFONT font = SetFont(hdcBuffer, 40, RGB(255,0,0));
	TextOut(hdcBuffer, death_pos.x + death_size.cx * 0.4, death_pos.y + 20, _T("Game Over"), 9);
	DeleteObject(font);
	font = SetFont(hdcBuffer, 20, RGB(181,114,124));
	TextOut(hdcBuffer, death_pos.x + 20, death_pos.y + 50, szBuffer, wsprintf(szBuffer, _T("得分:%d"), int(g_gameStatus.m_score)));
	TextOut(hdcBuffer, death_pos.x + 20, death_pos.y + 70, szBuffer, wsprintf(szBuffer, _T("金币:%d"), g_gameStatus.m_coins));
	TextOut(hdcBuffer, death_pos.x + 20, death_pos.y + 90, szBuffer, wsprintf(szBuffer, _T("历史得分记录;%d"), score));
	TextOut(hdcBuffer, death_pos.x + 20, death_pos.y + 110, szBuffer, wsprintf(szBuffer, _T("历史金币记录;%d"), coin));
	DeleteObject(font);
	BOOL flag = FALSE;
	int new_score = score, new_coin = coin;
	if(g_gameStatus.m_score > score)
	{
		new_score = g_gameStatus.m_score;
		flag = TRUE;
	}
	if(g_gameStatus.m_coins > coin)
	{
		new_coin = g_gameStatus.m_coins;
		flag = TRUE;
	}
	if(flag)
	{
		if(fp=fopen(".history", "wb"))
		{
			fprintf(fp, "%d %d", new_score, new_coin);
			fclose(fp);
		}
	}
	if(g_times % 10 < 5)
	{
		HFONT font = SetFont(hdcBuffer, 50, RGB(255,255,255));
		TextOut(hdcBuffer, restart_pos.x, restart_pos.y, _T("Press Enter To Restart"), 22);
		DeleteObject(font);
	}
}

//Hero移动处理
VOID HeroMove(Hero& hero)
{
	//TODO
	if(g_gameStatus.hero_type == 1)	//神烦狗，只有一种状态
	{
		hero.img_state += g_gameStatus.moveX * 2;
		if(hero.img_state >= 9)
			hero.img_state -= 9;
	}
	else{
		if(hero.m_state == 0) //罗小黑，正常行进状态
		{
			hero.img_state += g_gameStatus.moveX * 2.5;
			if(hero.img_state >= 12)
				hero.img_state -= 12;
		}
		else if(hero.m_state == 1) //罗小黑，加速奔跑状态
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 5)
				hero.img_state -= 5;
		}
		else if(hero.m_state == 2) //罗小黑，滚动状态
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 6)
				hero.img_state -= 6;
		}
		else if(hero.m_state == 3) //罗小黑，减速状态
		{
			hero.img_state += g_gameStatus.moveX * 1.25;
			if(hero.img_state >= 12)
				hero.img_state -= 12;
		}
	}
	if(hero.pos.x < g_gameStatus.basic_x) //落后基础位置，默默往前赶
		hero.pos.x += g_gameStatus.moveX / 5;
}

//Hero跳跃处理
VOID HeroJump(Hero& hero)
{
	//TODO
	if(GetKeyState(VK_SPACE) < 0  && !g_keyState[VK_SPACE] && hero.times > 0) //按下空格，且仍然能够跳
	{
		hero.m_a = -1.0;
		hero.m_speed = 0;
		hero.times -= 1;
	}
	else
		hero.m_a = 0.15;
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
		//T判断g_buildings[k]与hero接触
			//被挡住
		if(hero.pos.x + hero.size.cx > g_buildings[k].pos.x + 0.00001 && hero.pos.x + 0.4 * hero.size.cx < g_buildings[k].pos.x - 0.00001 && hero.pos.y + hero.size.cy > g_buildings[k].pos.y + 0.00001)
 			hero.pos.x = g_buildings[k].pos.x - hero.size.cx;
			//下落到草地上
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
		//判断g_tools[k]与hero接触
			//吃了道具状态
		if(hero.m_state == 2)
		{
			//吸引金币
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
			//道具为实体，不能穿透
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
			//道具会消失(被吃掉)
			if(g_tools[k].disappear)
				g_tools[k].size.cx = -1;
			if(g_tools[k].m_type == 0 && hero.invincible_time == 0)	//碰到道具0_飞镖，掉血
			{
				hero.invincible_time = 100;
				g_gameStatus.life--;
				tool_start = g_times;
				if(g_gameStatus.life == 0) //英雄死亡
				{
					g_gameStatus.m_state = 12;
					if(g_gameStatus.hero_type == 0)
						PlaySound((LPCWSTR)IDR_DIE_0, NULL, SND_RESOURCE | SND_ASYNC);
					else
						PlaySound((LPCWSTR)IDR_DIE_1, NULL, SND_RESOURCE | SND_ASYNC);
				}
			}
			else if(g_tools[k].m_type == 4) //吃到道具4_生命
				g_gameStatus.life++;
			else if(g_tools[k].m_type == 5) //吃到道具5_加速蘑菇
			{
				if(hero.m_state == 3) //减速状态，恢复正常
				{
					g_gameStatus.moveX = moveX;
					g_gameStatus.backgroundMove = backgroundMove;
					hero.m_state = 0;
					hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
				}
				else //进入加速状态
				{
					tool_start = g_times;
					g_gameStatus.moveX = 2 * moveX;;
					g_gameStatus.backgroundMove = 2 * backgroundMove;
					hero.m_state = 1;
					if(g_gameStatus.hero_type == 0)
						hero.img = hero_bmps[1].img;
				}
			}
			else if(g_tools[k].m_type == 6) //吃到道具6_减速蘑菇
			{
				if(hero.m_state == 1) //加速状态，恢复正常
				{
					g_gameStatus.moveX = moveX;
					g_gameStatus.backgroundMove = backgroundMove;
					hero.m_state = 0;
					hero.img = hero_bmps[g_gameStatus.hero_type * 3].img;
				}
				else //进入减速状态
				{
					tool_start = g_times;
					g_gameStatus.moveX = moveX / 1.5;
					g_gameStatus.backgroundMove = backgroundMove / 1.5;
					hero.m_state = 3;
					if(g_gameStatus.hero_type == 0)
						hero.img = hero_bmps[0].img;
				}
			}
			else if(g_tools[k].m_type == 7) //吃到道具7_金币
				g_gameStatus.m_coins += 1;
			else if(g_tools[k].m_type == 8) //吃到道具8_飞起来
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
	if(toolCreate) return;
	toolCreate = TRUE;
	DOUBLE gap = 0.08 - (g_gameStatus.m_score / 1000 * 0.8);
	if(gap < 0.005)
		gap = 0.005;
	while(abs(g_buildings[building_now].pos.y - preBuilding.y) > 0.00001 || abs(g_buildings[building_now].pos.x + g_buildings[building_now].size.cx - preBuilding.x) > 0.00001)
	{
		DOUBLE tmp = random(1);
		if(tmp < 0.2) //生成tool_7 金币
		{
			int id = FindNextToolByType(7);
			int i = 0, j = 0;
			ToolInit(g_tools[id]);
			if(g_tools[id].size.cx == -1) break;
			toolX = g_tools[id].pos.x + 4;
			tmp = random(1);
			//生成多种组合
			if(tmp < 0.15) 
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 1;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y - 2 + abs(i - 2), 1, 1);
				}
			}
			else if(tmp < 0.3)
			{
				g_tools[id].pos.y = g_buildings[building_now].pos.y - 3;
				for(i = 1;i < 5;i++)
				{
					j = FindNextToolByType(7);
					ToolInit(g_tools[j], g_tools[id].pos.x + i, g_tools[id].pos.y + 2 - abs(i - 2), 1, 1);
				}
			}
			else if(tmp < 0.45)
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
			else if(tmp < 0.6)
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
			else if(tmp < 0.75)
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
			if(g_tools[id].m_type == 6)
				g_times++;
		}
		else if(tmp < 0.28)
			ToolInit(g_tools[FindNextToolByType(5)]);
		else if(tmp < 0.36)
			ToolInit(g_tools[FindNextToolByType(6)]);
		else if(tmp < 0.56)
			ToolInit(g_tools[FindNextToolByType(1)]);
		else if(tmp < 0.76)
			ToolInit(g_tools[FindNextToolByType(3)]);
		else if(tmp < 0.76 + gap)
			ToolInit(g_tools[FindNextToolByType(4)]);
		else if(tmp < 0.76 + 2* gap)
			ToolInit(g_tools[FindNextToolByType(8)]);
		else
		{
			if(g_buildings[building_now].size.cx != WIDTH)
			ToolInit(g_tools[FindNextToolByType(0)]);
		}
	}
	toolCreate = FALSE;
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