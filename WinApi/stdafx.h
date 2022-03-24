// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <wingdi.h>
#include <objidl.h>
#include <wincodec.h>
#include <combaseapi.h>
#include <gdiplus.h>
#include <Windows.h>
using namespace Gdiplus;

#define X 800
#define Y 600
#define TankSize 40
#define BulletSize 20
#define MAX_LOADSTRING 100
#define CoinSize 30
#define TankUp 'W'
#define TankDown 'S'
#define TankLeft 'A'
#define TankRight 'D'
#define Tank2Up 'I'
#define Tank2Down 'K'
#define Tank2Left 'J'
#define Tank2Right 'L'
#define TankShoot ' '
#define Tank2Shoot 'P'
#define BarHeight 40
#define sizeDiff (TankSize - CoinSize)/2
#define sizeDiffB (TankSize - BulletSize) / 2
#define iconDiff 5
#define UserBar 330
#define InfoBar 110
#define KillPoint 10
#define HitPoint 1
#define HitHealth 20
#define StartAmmo 50
#define StartHealth 100
#define CoinPoint 5
#define CoinAmmo 20
#define CoinHealth 50
#define ButtonSizeX 140
#define ButtonSizeY 40
#define BackGroundBrush (HBRUSH) GetStockObject(BLACK_BRUSH);
#define myStyle  WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX //https://stackoverflow.com/questions/27402297/creating-window-frame-without-maximize-button-and-without-resizing-options

// the main window class name

// reference additional headers your program requires here
ATOM				MyRegisterTank(HINSTANCE hInstance);
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyRegisterParent(HINSTANCE hInstance);
ATOM				MyRegisterCoin(HINSTANCE hInstance);
ATOM				MyRegisterBullet(HINSTANCE hInstance);
ATOM				MyRegisterBar(HINSTANCE hInstance);
ATOM				MyRegisterRedBar(HINSTANCE hInstance);
ATOM				MyRegisterBlueBar(HINSTANCE hInstance);
ATOM				MyRegisterGreyBar(HINSTANCE hInstance);
ATOM				MyRegisterGround(HINSTANCE hInstance);
ATOM				MyRegisterTank2(HINSTANCE hInstance);
ATOM				MyRegisterRedHealthBar(HINSTANCE hInstance);
ATOM				MyRegisterRedAmmoBar(HINSTANCE hInstance);
ATOM				MyRegisterRedPointBar(HINSTANCE hInstance);
ATOM				MyRegisterBlueHealthBar(HINSTANCE hInstance);
ATOM				MyRegisterBlueAmmoBar(HINSTANCE hInstance);
ATOM				MyRegisterBluePointBar(HINSTANCE hInstance);
ATOM				MyRegisterMainWindow(HINSTANCE hInstance);
ATOM				MyRegisterTextBlock(HINSTANCE hInstance);
ATOM				MyRegisterTextBlock2(HINSTANCE hInstance);
ATOM				MyRegisterTextBlock3(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ParentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    CoinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	GroundProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	TankProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BulletProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	Tank2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	RedHealthBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	RedAmmoBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	RedPointBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BlueHealthBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BlueAmmoBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BluePointBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	GreyBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	TextBlockProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	TextBlock2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	TextBlock3Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void MoveCoin();




struct tank
{
	HWND hTank;
	int x;
	int y;
	int points;
	int health;
	int ammo;
};

struct coin
{
	HWND hCoin;
	int x;
	int y;
	int type;
};

struct bullet
{
	HWND hBullet;
	char way;
	int x;
	int y;
};

struct ground
{
	HWND hGround;
};

struct background
{
	HWND hBack;
	int x;
	int y;
	int sizeX;
	int sizeY;
};

struct Bar
{
	HWND hHealth;
	HWND hAmmo;
	HWND hPoints;
	HWND Htext;
	HWND Atext;
	HWND Ptext;
};

struct MainWindow
{
	HWND hWindow;
	HWND HReturn;
	HWND hNewGame;
	HWND hTop10;
};