/*
* Copyright 2015.407A工作室
* All rights reserved.
*
* 文件名称：Running-Black.h
* 摘	要：跑酷游戏工程声明文件
*
* 当前版本：1.5
* 作	者: Krystal/甘茂霖
* 完成日期：2015年12月6日
*
* 取代版本：1.4
* 原作者  ：Krystal/甘茂霖
* 完成日期：2015年12月5日
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
//英雄结构体，英雄位图、位图状态、位置、大小、类型、速度、加速度、生命、状态
typedef struct
{
	HBITMAP		img;
	POINT		img_point;
	SIZE		img_size;
	DOUBLE		img_state;
	POINTF		pos;
	SIZE		size;
	DOUBLE		m_speed;
	DOUBLE		m_a;
	UINT		m_state;
	UINT		times;
}Hero;

//建筑物结构体，建筑位图、位置、大小
typedef struct
{
	HBITMAP		img;
	POINT		roof_point;
	SIZE		roof_size;
	SIZE		block_size;
	POINT		block_point;
	POINTF		pos;
	SIZE		size;
}Building;


//道具结构体，道具位图、位置、大小、类别、是否为实心、是否落地
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINT		img_point;
	DOUBLE		img_state;
	POINTF		pos;
	SIZE		size;
	UINT		id;
	UINT		m_type;
	BOOL		solid;
	BOOL		disappear;
	BOOL		down;
}Tool;

//背景结构体，背景位图、位置、大小
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINT		img_point;
	POINTF		pos;
	SIZE		size;
	BOOL		visible;
}Background;

//游戏状态结构体，得分、暂停、频率、状态、基础高度、生命
typedef struct
{
	DOUBLE		m_score;
	BOOL		isPaused;
	UINT		m_frequency;
	UINT		m_state;
	UINT		hero_type;
	UINT		basic_high;
	UINT		basic_x;
	UINT		life;
	UINT		m_coins;
	DOUBLE		moveX; 
    DOUBLE      backgroundMove;
}GameStatus;

//位图加载结构体
typedef struct
{
	HBITMAP img;
	POINT img_point;
	SIZE img_size;
	POINTF dst_point;
	SIZE dst_size;
} Bmp;

/* 宏定义 */
#define MAX_LOADSTRING 100
#define BUILDINGS_NUM 50
#define BACKGROUND_NUM 6
#define HEROS_NUM 2
#define TOOLS_NUM 4500
#define TOOLS_TYPE 9
#define WIDTH 30
#define HEIGHT 20
#define GRID 30

/* 函数声明 */
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/* 全局变量声明 */
extern Hero g_hero[HEROS_NUM];
extern Building g_buildings[BUILDINGS_NUM];
extern Tool g_tools[TOOLS_NUM];
extern Background g_backgrounds[BACKGROUND_NUM];
extern GameStatus g_gameStatus;

extern UINT hero_img[];
extern UINT background_img[];
extern UINT building_img[];
extern UINT tool_img[];

extern BOOL g_keyState[256];
extern UINT g_times;
extern DOUBLE headX;
extern POINTF preBuilding;
extern DOUBLE toolX;
extern UINT building_now;
extern UINT tool_gap_min;
extern UINT tool_gap_max;
extern BOOL toolCreate;
extern UINT tool_id[TOOLS_TYPE][TOOLS_NUM / TOOLS_TYPE + 1];
extern BOOL g_flag;
extern UINT tool_start;
extern Bmp hero_bmps[3 * HEROS_NUM];
extern DOUBLE moveX;
extern DOUBLE backgroundMove;

extern Bmp hero_select_0;
extern Bmp hero_select_1;
extern Bmp button_start_0;
extern Bmp button_start_1;
extern Bmp button_start_2;
extern Bmp button_return;
extern Bmp button_pause_0;
extern Bmp button_pause_1;
extern Bmp author;

extern POINTF info_0_pos;
extern POINTF info_1_pos;
extern POINTF title_pos;
extern POINTF hint_pos;
extern POINTF score_pos;
extern POINTF coin_pos;
extern POINTF life_pos;
extern POINTF help_pos;
extern POINTF death_pos;
extern POINTF restart_pos;

extern SIZE help_size;
extern SIZE death_size;

//窗口初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//鼠标事件
VOID MouseClickEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
//绘制事件
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam);
//窗口摧毁
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
//Static元素位置初始化
VOID InitPos();
//游戏初始化
VOID InitGame();
//Hero初始化
VOID HeroInit(Hero& hero);
//GameStatus初始化
VOID GameStatusInit(GameStatus& gameStatus);
//Background初始化
VOID BackgroundInit(Background& background);
//Building初始化
VOID BuildingInit(Building& building);
//Tool初始化
VOID ToolInit(Tool& tool);
//Tool带参数初始化
VOID ToolInit(Tool& tool, DOUBLE x, DOUBLE y, UINT cx, UINT cy);
//Hero更新
VOID HeroUpdate(Hero& hero);
//GameStatus更新
VOID GameStatusUpdate(GameStatus& gameStatus);
//Background更新
VOID BackgroundUpdate(Background& background);
//Building更新
VOID BuildingUpdate(Building& building);
//Tool更新
VOID ToolUpdate(Tool& tool);
//定时查看按键状态
VOID KeyUpdate();
//Hero绘制
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero);
//Background绘制
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background);
//Building绘制
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building);
//Tool绘制
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool);
//Before介绍界面
VOID BeforeStatePaint(HDC hdcBuffer, HDC hdcBmp);
//开始界面
VOID BeginStatePaint(HDC hdcBuffer, HDC hdcBmp);
//游戏进行界面
VOID RunStatePaint(HDC hdcBuffer, HDC hdcBmp);
//死亡界面
VOID DeathStatePaint(HDC hdcBuffer, HDC hdcBmp);
//绘制纯色背景
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height);
//设置文字大小，颜色，字体
VOID SetFont(HDC hdcBuffer, LONG size, COLORREF color, BYTE family);
//绘制图片
VOID PicturePaint(HDC hdcBuffer, HDC hdcBmp, HBITMAP bmp, DOUBLE x, DOUBLE y, UINT width, UINT height, UINT sx, UINT sy, UINT sw, UINT sh);
//Hero移动处理
VOID HeroMove(Hero& hero);
//Hero跳跃处理
VOID HeroJump(Hero& hero);
//Hero碰撞处理
VOID HeroTouch(Hero& hero);
//生成道具
VOID CreateTool();
//POS初始化
VOID _PointF(POINTF& pos, DOUBLE x, DOUBLE y);
//SIZE初始化
VOID _Size(SIZE& size, UINT cx, UINT cy);
//生成[a,b]之间的随机数
UINT random(UINT a, UINT b);
//生成(0,b)之间的随机数
DOUBLE random(DOUBLE b);
//随机生成草地的最高高度
UINT Highest(DOUBLE x, POINTF pre);
//超出视野范围
BOOL outView(Building& building);
BOOL outView(Tool& tool);
BOOL outView(Background& background);
//查找下一个可用的道具下标
UINT FindNextToolByType(UINT type);
//判断某点是否在某区域内
BOOL InArea(DOUBLE x, DOUBLE y, POINTF lPoint, SIZE size);

#endif