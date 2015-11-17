/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black.h
* 摘	要：跑酷游戏工程声明文件
*
* 当前版本：1.0
* 作	者: Krystal/甘茂霖
* 完成日期：2015年11月14日
*
* 取代版本：1.0
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年11月14日
*/

#pragma once

#pragma comment(lib, "msimg32.lib")

#ifndef RunningBlack_H
#define RunningBlack_H

#include "resource.h"

typedef double DOUBLE;

typedef struct
{
	DOUBLE x;
	DOUBLE y;
}POINTF;

/* 结构体定义 */
//英雄结构体，英雄位图、位图状态、位置、大小、类型、速度、加速度、生命、状态、基础高度
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	UINT		img_state;
	POINTF		pos;
	SIZE		size;
	UINT		m_type;
	DOUBLE		m_speed;
	DOUBLE		m_a;
	UINT	    m_life;
	UINT		m_state;
	UINT		basic_high;
}Hero;

//建筑物结构体，建筑位图、位置、大小
typedef struct
{
	HBITMAP		roof_img;
	SIZE		roof_size;
	HBITMAP		block_img;
	SIZE		block_size;
	POINTF		pos;
	SIZE		size;
}Building;

//障碍物结构体，障碍位图、位置、大小
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
}Barrier;

//道具结构体，道具位图、位置、大小、类别
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
	UINT		m_type;
}Tool;

//背景结构体，背景位图、位置、大小
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
}Background;

//游戏状态结构体，得分、暂停、频率、状态
typedef struct
{
	UINT		m_score;
	BOOL		isPaused;
	UINT		m_frequency;
	UINT		m_state;
}GameStatus;

/* 宏定义 */
#define MAX_LOADSTRING 100
#define BUILDINGS_NUM 100
#define BARRIERS_NUM 100
#define TOOLS_NUM 100
#define WIDTH 30
#define HEIGHT 20
#define GRID 30

/* 函数声明 */
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//窗口初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//绘制事件
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam);
//窗口摧毁
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
//游戏初始化
VOID InitGame(HWND hWnd);
//Hero初始化
VOID HeroInit(Hero& hero);
//GameStatus初始化
VOID GameStatusInit(GameStatus& gameStatus);
//Background初始化
VOID BackgroundInit(Background& background);
//Building初始化
VOID BuildingInit(Building& building, UINT k);
//Barrier初始化
VOID BarrierInit(Barrier& barrier, UINT k);
//Tool初始化
VOID ToolInit(Tool& tool, UINT k);
//Hero更新
VOID HeroUpdate(Hero& hero);
//GameStatus更新
VOID GameStatusUpdate(GameStatus& gameStatus);
//Background更新
VOID BackgroundUpdate(Background& background);
//Building更新
VOID BuildingUpdate(Building& building);
//Barrier更新
VOID BarrierUpdate(Barrier& barrier);
//Tool更新
VOID ToolUpdate(Tool& tool);
//道具动画
VOID ToolFlash(Tool& tool);
//开始页面
VOID BeginFlash();
//结束页面
VOID EndFlash();
//定时查看按键状态
VOID KeyUpdate();
//Hero绘制
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero);
//Background绘制
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background);
//Building绘制
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building);
//Barrier绘制
VOID BarrierPaint(HDC hdcBuffer, HDC hdcBmp, Barrier& barrier);
//Tool绘制
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool);

#endif