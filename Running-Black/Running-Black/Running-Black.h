/*
* Copyright 2015.407A������
* All rights reserved.
*
* �ļ����ƣ�Running-Black.h
* ժ	Ҫ���ܿ���Ϸ���������ļ�
*
* ��ǰ�汾��1.0
* ��	��: Krystal/��ï��
* ������ڣ�2015��11��14��
*
* ȡ���汾��1.0
* ԭ����  ��Krystal/��ï��
* ������ڣ�2015��11��14��
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
//Ӣ�۽ṹ�壬Ӣ��λͼ��λͼ״̬��λ�á���С�����͡��ٶȡ����ٶȡ�������״̬�������߶�
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

//������ṹ�壬����λͼ��λ�á���С
typedef struct
{
	HBITMAP		roof_img;
	SIZE		roof_size;
	HBITMAP		block_img;
	SIZE		block_size;
	POINTF		pos;
	SIZE		size;
}Building;

//�ϰ���ṹ�壬�ϰ�λͼ��λ�á���С
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
}Barrier;

//���߽ṹ�壬����λͼ��λ�á���С�����
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
	UINT		m_type;
}Tool;

//�����ṹ�壬����λͼ��λ�á���С
typedef struct
{
	HBITMAP		img;
	SIZE		img_size;
	POINTF		pos;
	SIZE		size;
}Background;

//��Ϸ״̬�ṹ�壬�÷֡���ͣ��Ƶ�ʡ�״̬
typedef struct
{
	UINT		m_score;
	BOOL		isPaused;
	UINT		m_frequency;
	UINT		m_state;
}GameStatus;

/* �궨�� */
#define MAX_LOADSTRING 100
#define BUILDINGS_NUM 100
#define BARRIERS_NUM 100
#define TOOLS_NUM 100
#define WIDTH 30
#define HEIGHT 20
#define GRID 30

/* �������� */
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//���ڳ�ʼ��
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//��ʱ���¼�
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//�����¼�
VOID Render(HWND hWnd, WPARAM wParam, LPARAM lParam);
//���ڴݻ�
VOID Destroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
//��Ϸ��ʼ��
VOID InitGame(HWND hWnd);
//Hero��ʼ��
VOID HeroInit(Hero& hero);
//GameStatus��ʼ��
VOID GameStatusInit(GameStatus& gameStatus);
//Background��ʼ��
VOID BackgroundInit(Background& background);
//Building��ʼ��
VOID BuildingInit(Building& building, UINT k);
//Barrier��ʼ��
VOID BarrierInit(Barrier& barrier, UINT k);
//Tool��ʼ��
VOID ToolInit(Tool& tool, UINT k);
//Hero����
VOID HeroUpdate(Hero& hero);
//GameStatus����
VOID GameStatusUpdate(GameStatus& gameStatus);
//Background����
VOID BackgroundUpdate(Background& background);
//Building����
VOID BuildingUpdate(Building& building);
//Barrier����
VOID BarrierUpdate(Barrier& barrier);
//Tool����
VOID ToolUpdate(Tool& tool);
//���߶���
VOID ToolFlash(Tool& tool);
//��ʼҳ��
VOID BeginFlash();
//����ҳ��
VOID EndFlash();
//��ʱ�鿴����״̬
VOID KeyUpdate();
//Hero����
VOID HeroPaint(HDC hdcBuffer, HDC hdcBmp, Hero& hero);
//Background����
VOID BackgroundPaint(HDC hdcBuffer, HDC hdcBmp, Background& background);
//Building����
VOID BuildingPaint(HDC hdcBuffer, HDC hdcBmp, Building& building);
//Barrier����
VOID BarrierPaint(HDC hdcBuffer, HDC hdcBmp, Barrier& barrier);
//Tool����
VOID ToolPaint(HDC hdcBuffer, HDC hdcBmp, Tool& tool);

#endif