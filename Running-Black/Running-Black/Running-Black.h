/*
* Copyright 2015.407A������
* All rights reserved.
*
* �ļ����ƣ�Running-Black.h
* ժ	Ҫ���ܿ���Ϸ���������ļ�
*
* ��ǰ�汾��1.5
* ��	��: Krystal/��ï��
* ������ڣ�2015��12��6��
*
* ȡ���汾��1.4
* ԭ����  ��Krystal/��ï��
* ������ڣ�2015��12��5��
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

/* �ṹ�嶨�� */
//Ӣ�۽ṹ�壬Ӣ��λͼ��λͼ״̬��λ�á���С�����͡��ٶȡ����ٶȡ�������״̬
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

//������ṹ�壬����λͼ��λ�á���С
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


//���߽ṹ�壬����λͼ��λ�á���С������Ƿ�Ϊʵ�ġ��Ƿ����
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

//�����ṹ�壬����λͼ��λ�á���С
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINT		img_point;
	POINTF		pos;
	SIZE		size;
	BOOL		visible;
}Background;

//��Ϸ״̬�ṹ�壬�÷֡���ͣ��Ƶ�ʡ�״̬�������߶ȡ�����
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

//λͼ���ؽṹ��
typedef struct
{
	HBITMAP img;
	POINT img_point;
	SIZE img_size;
	POINTF dst_point;
	SIZE dst_size;
} Bmp;

/* �궨�� */
#define MAX_LOADSTRING 100
#define BUILDINGS_NUM 50
#define BACKGROUND_NUM 6
#define HEROS_NUM 2
#define TOOLS_NUM 4500
#define TOOLS_TYPE 9
#define WIDTH 30
#define HEIGHT 20
#define GRID 30

/* �������� */
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/* ȫ�ֱ������� */
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

//���ڳ�ʼ��
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//��ʱ���¼�
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//����¼�
VOID MouseClickEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
//�����¼�
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam);
//���ڴݻ�
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
//StaticԪ��λ�ó�ʼ��
VOID InitPos();
//��Ϸ��ʼ��
VOID InitGame();
//Hero��ʼ��
VOID HeroInit(Hero& hero);
//GameStatus��ʼ��
VOID GameStatusInit(GameStatus& gameStatus);
//Background��ʼ��
VOID BackgroundInit(Background& background);
//Building��ʼ��
VOID BuildingInit(Building& building);
//Tool��ʼ��
VOID ToolInit(Tool& tool);
//Tool��������ʼ��
VOID ToolInit(Tool& tool, DOUBLE x, DOUBLE y, UINT cx, UINT cy);
//Hero����
VOID HeroUpdate(Hero& hero);
//GameStatus����
VOID GameStatusUpdate(GameStatus& gameStatus);
//Background����
VOID BackgroundUpdate(Background& background);
//Building����
VOID BuildingUpdate(Building& building);
//Tool����
VOID ToolUpdate(Tool& tool);
//��ʱ�鿴����״̬
VOID KeyUpdate();
//Hero����
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero);
//Background����
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background);
//Building����
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building);
//Tool����
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool);
//Before���ܽ���
VOID BeforeStatePaint(HDC hdcBuffer, HDC hdcBmp);
//��ʼ����
VOID BeginStatePaint(HDC hdcBuffer, HDC hdcBmp);
//��Ϸ���н���
VOID RunStatePaint(HDC hdcBuffer, HDC hdcBmp);
//��������
VOID DeathStatePaint(HDC hdcBuffer, HDC hdcBmp);
//���ƴ�ɫ����
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height);
//�������ִ�С����ɫ������
VOID SetFont(HDC hdcBuffer, LONG size, COLORREF color, BYTE family);
//����ͼƬ
VOID PicturePaint(HDC hdcBuffer, HDC hdcBmp, HBITMAP bmp, DOUBLE x, DOUBLE y, UINT width, UINT height, UINT sx, UINT sy, UINT sw, UINT sh);
//Hero�ƶ�����
VOID HeroMove(Hero& hero);
//Hero��Ծ����
VOID HeroJump(Hero& hero);
//Hero��ײ����
VOID HeroTouch(Hero& hero);
//���ɵ���
VOID CreateTool();
//POS��ʼ��
VOID _PointF(POINTF& pos, DOUBLE x, DOUBLE y);
//SIZE��ʼ��
VOID _Size(SIZE& size, UINT cx, UINT cy);
//����[a,b]֮��������
UINT random(UINT a, UINT b);
//����(0,b)֮��������
DOUBLE random(DOUBLE b);
//������ɲݵص���߸߶�
UINT Highest(DOUBLE x, POINTF pre);
//������Ұ��Χ
BOOL outView(Building& building);
BOOL outView(Tool& tool);
BOOL outView(Background& background);
//������һ�����õĵ����±�
UINT FindNextToolByType(UINT type);
//�ж�ĳ���Ƿ���ĳ������
BOOL InArea(DOUBLE x, DOUBLE y, POINTF lPoint, SIZE size);

#endif