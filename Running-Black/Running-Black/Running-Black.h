/*
* Copyright 2015.407A������
* All rights reserved.
*
* �ļ����ƣ�Running-Black.h
* ժ	Ҫ���ܿ���Ϸ���������ļ�
*
* ��ǰ�汾��2.1
* ��	��: Krystal/��ï��
* ������ڣ�2015��12��18��
*
* ȡ���汾��1.6
* ԭ����  ��Krystal/��ï��
* ������ڣ�2015��12��16��
*/

#pragma once

#pragma comment(lib, "msimg32.lib")

#ifndef RunningBlack_H
#define RunningBlack_H

#include "resource.h"

typedef double DOUBLE;

/* �ṹ�嶨�� */
//ʵ����ṹ��
typedef struct
{
	DOUBLE x;
	DOUBLE y;
}POINTF;

//Ӣ�۽ṹ�壬Ӣ��λͼ��λͼ״̬��λ�á���С�����͡��ٶȡ����ٶȡ�������״̬��n�����������޵�ʱ��
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
	UINT		m_state; //0:������1:���٣�2:����,3:����
	UINT		times; //ʣ�������Ծ�Ĵ���
	UINT		invincible_time; //ʣ���޵�ʱ��
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


//���߽ṹ�壬����λͼ��λ�á���С������Ƿ�Ϊʵ�ġ��Ƿ����ʧ���Ƿ���ء������˶�ʱ��
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
	LONG		left_time;
}Tool;

//�����ṹ�壬����λͼ��λ�á���С���Ƿ�ɼ�
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINT		img_point;
	POINTF		pos;
	SIZE		size;
	BOOL		visible;
}Background;

//��Ϸ״̬�ṹ�壬�÷֡���ͣ��Ƶ�ʡ�״̬�������߶ȡ�������������������ƶ��ٶȡ������ƶ��ٶ�
typedef struct
{
	DOUBLE		m_score;
	BOOL		isPaused;
	UINT		m_frequency;
	UINT		m_state; //m_state / 4��ʾ4��״̬:��ʼ�Ķ�������ʼ���桢��Ϸ״̬������֮����m_state % 4��ʾ����ľ���״̬��8��ʾruning,9��ʾpaused
	UINT		hero_type;
	UINT		basic_high;
	UINT		basic_x;
	UINT		life;
	UINT		m_coins;
	DOUBLE		moveX; 
    DOUBLE      backgroundMove;
}GameStatus;

//λͼ���ؽṹ�塢����λ��
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

extern BOOL g_keyState[256];	//����״̬��TRUE��ʾ������
extern UINT g_times;	//����������������ʵ��֡����
extern DOUBLE headX;	//�������ɽ�����(�ݵ�)
extern POINTF preBuilding;	//�������ɽ�����(�ݵ�)
extern DOUBLE toolX;	//�������ɵ���
extern UINT building_now;	//�������ɵ���
extern UINT tool_gap_min;	//���߼��_��Сֵ
extern UINT tool_gap_max;	//���߼��_���ֵ
extern BOOL toolCreate;	//�Ƿ������µ�������״̬
extern UINT tool_id[TOOLS_TYPE][TOOLS_NUM / TOOLS_TYPE + 1];	//���õ��ߵ��±�����
extern BOOL g_flag;	//��һ����ʱ�¼��Ƿ���ɣ����ڷ�ֹ�����¼�����ʱ������������¼�ײ��
extern UINT tool_start; //������Чʱ��
extern Bmp hero_bmps[3 * HEROS_NUM]; //Ӣ��λͼ
extern DOUBLE moveX; //���������ƶ��ٶ�
extern DOUBLE backgroundMove; //���������ƶ��ٶ�

extern Bmp hero_select_0; //Ӣ��ѡ��_0_��С��
extern Bmp hero_select_1; //Ӣ��ѡ��_1_�񷳹�
extern Bmp button_start_0; //��ʼҳ��_0_start
extern Bmp button_start_1; //��ʼҳ��_1_about game
extern Bmp button_start_2; //��ʼҳ��_2_about writer
extern Bmp button_return; //���ذ�ť
extern Bmp button_pause_0; //��ͣ��ť_��ͣ״̬
extern Bmp button_pause_1; //��ͣ��ť_����״̬
extern Bmp author; //����ͼƬ

extern POINTF info_0_pos; //pos_������Ϣ_0_author
extern POINTF info_1_pos; //pos_������Ϣ_1_Krystal
extern POINTF title_pos; //pos_title_��С�����ռ�
extern POINTF hint_pos; //pos_hint_��ʼ��Ϸ/ѡ������/������Ϸ/��������
extern POINTF score_pos; 
extern POINTF coin_pos; 
extern POINTF life_pos; 
extern POINTF help_pos; 
extern POINTF death_pos;
extern POINTF restart_pos; //pos_restart_"press enter to start"

extern SIZE help_size; //�������С
extern SIZE death_size; //����������С

//���ڳ�ʼ��
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//��ʱ���¼�
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//��굥���¼�
VOID MouseClickEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
//�����¼�
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam);
//���ڴݻ�
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
//StaticԪ��λ�ó�ʼ��
VOID InitPos();
//��Ϸ���ݳ�ʼ��
VOID InitGame();
//Hero��ʼ��
VOID HeroInit(Hero& hero);
//GameStatus��ʼ��
VOID GameStatusInit(GameStatus& gameStatus);
//Background��ʼ��
VOID BackgroundInit(Background& background);
//Building��ʼ��������������ɽ�����(�ݵ�)
VOID BuildingInit(Building& building);
//Tool��ʼ��������������ɵ���
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
//���ƴ�ɫ����,�����߿�
VOID SolidBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height);
//���ƴ�ɫ���������߿�
VOID NullBackgroundPaint(HDC hdcBuffer, COLORREF color, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height, COLORREF penColor);
//���Ʊ߿�
VOID NullBackgroundPaint(HDC hdcBuffer, DOUBLE x, DOUBLE y, DOUBLE width, DOUBLE height, COLORREF penColor);
//�������ִ�С����ɫ������
HFONT SetFont(HDC hdcBuffer, LONG size, COLORREF color, BYTE family);
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