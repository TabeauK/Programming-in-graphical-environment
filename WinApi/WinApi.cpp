// WinApi.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinApi.h"

HINSTANCE hInst;    // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];
HWND Parent;
struct background Background;
struct tank Tank;
struct tank Tank2;
struct coin Coin;
struct ground Ground;
wchar_t s[MAX_LOADSTRING];
static int tick = 0;
ULONG_PTR m_gdiplusToken;
Bar redBar, blueBar, greyBar;
static bool GamePaused = false;
static bool GameON = false;
struct MainWindow Main;
int CMD;
static bool TextBlockHover1 = false;
static bool TextBlockHover2 = false;
static bool TextBlockHover3 = false;
static int winner = 0;
// Global Variables:

// Forward declarations of functions included in this code module:


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);
	MyRegisterParent(hInstance);
	MyRegisterMainWindow(hInstance);
	MyRegisterBar(hInstance);
	MyRegisterGround(hInstance);
	MyRegisterTank(hInstance);
	MyRegisterCoin(hInstance);
	MyRegisterBullet(hInstance);
	MyRegisterTank2(hInstance);
	MyRegisterRedBar(hInstance);
	MyRegisterBlueBar(hInstance);
	MyRegisterGreyBar(hInstance);
	MyRegisterRedHealthBar(hInstance);
	MyRegisterRedAmmoBar(hInstance);
	MyRegisterRedPointBar(hInstance);
	MyRegisterBlueHealthBar(hInstance);
	MyRegisterBlueAmmoBar(hInstance);
	MyRegisterBluePointBar(hInstance);
	MyRegisterTextBlock(hInstance);
	MyRegisterTextBlock2(hInstance);
	MyRegisterTextBlock3(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}
void PaintCoin()
{
	PAINTSTRUCT ps;
	Gdiplus::Rect rec(0, 0, CoinSize, CoinSize);
	Image image(L"Textures\\coin.png");
	Image image1(L"Textures\\ammo.png");
	Image image2(L"Textures\\emergency-kit.png");
	HDC hdc = BeginPaint(Coin.hCoin, &ps);
	Graphics graphics(hdc);
	if (Coin.type == 0)
	{
		graphics.DrawImage(&image, rec);
	}
	if (Coin.type == 1)
	{
		graphics.DrawImage(&image1, rec);
	}
	if (Coin.type == 2)
	{
		graphics.DrawImage(&image2, rec);
	}
	EndPaint(Coin.hCoin, &ps);
}
void Declare()
{
	srand(time(NULL));

	Tank.x = 0;
	Tank.y = Y / 2 - TankSize / 2;
	Tank2.x = X - TankSize;
	Tank2.y = Y / 2 + TankSize / 2;

	Background.x = GetSystemMetrics(SM_CXSCREEN) / 2 - X / 2;
	Background.y = GetSystemMetrics(SM_CYSCREEN) / 2 - Y / 2;

	RECT wr = { 0, 0, X, Y };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	Background.sizeX = wr.right - wr.left;
	Background.sizeY = wr.bottom - wr.top;
	Coin.x = Tank.x + sizeDiff;
	Coin.y = Tank.y + sizeDiff;
	while ((Tank.x == Coin.x - sizeDiff && Tank.y == Coin.y - sizeDiff) || (Tank2.x == Coin.x - sizeDiff && Tank2.y == Coin.y - sizeDiff))
	{
		Coin.x = (rand() % (X / TankSize)) * TankSize + sizeDiff;
		Coin.y = (rand() % ((Y / TankSize)) - 1) * TankSize + sizeDiff;
	}
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}
bool MakeGame(int nCmdShow)
{
	HWND hBar = CreateWindow(L"Bar", L"bar", WS_VISIBLE | WS_CHILD, 0, 0, X, BarHeight, Background.hBack, (HMENU)0, hInst, NULL);
	HWND hRedBar = CreateWindow(L"RedBar", L"redBar", WS_VISIBLE | WS_CHILD, 0, 0, UserBar, BarHeight, hBar, (HMENU)0, hInst, NULL);
	redBar.hHealth = CreateWindow(L"RedHealthBar", L"redHealthBar", WS_VISIBLE | WS_CHILD, 0, 0, InfoBar, BarHeight, hRedBar, (HMENU)0, hInst, NULL);
	redBar.hAmmo = CreateWindow(L"RedAmmoBar", L"redAmmoBar", WS_VISIBLE | WS_CHILD, InfoBar, 0, InfoBar, BarHeight, hRedBar, (HMENU)0, hInst, NULL);
	redBar.hPoints = CreateWindow(L"RedPointBar", L"redPointBar", WS_VISIBLE | WS_CHILD, UserBar - InfoBar, 0, InfoBar, BarHeight, hRedBar, (HMENU)0, hInst, NULL);
	greyBar.hPoints = CreateWindow(L"GreyBar", L"greyBar", WS_VISIBLE | WS_CHILD, UserBar, 0, X - UserBar - UserBar, BarHeight, hBar, (HMENU)0, hInst, NULL);
	HWND hBlueBar = CreateWindow(L"BlueBar", L"blueBar", WS_VISIBLE | WS_CHILD, X - UserBar, 0, UserBar, BarHeight, hBar, (HMENU)0, hInst, NULL);
	blueBar.hPoints = CreateWindow(L"BluePointBar", L"bluePointBar", WS_VISIBLE | WS_CHILD, 0, 0, InfoBar, BarHeight, hBlueBar, (HMENU)0, hInst, NULL);
	blueBar.hAmmo = CreateWindow(L"BlueAmmoBar", L"blueAmmoBar", WS_VISIBLE | WS_CHILD, InfoBar, 0, InfoBar, BarHeight, hBlueBar, (HMENU)0, hInst, NULL);
	blueBar.hHealth = CreateWindow(L"BlueHealthBar", L"blueHealthBar", WS_VISIBLE | WS_CHILD, 2 * InfoBar, 0, InfoBar, BarHeight, hBlueBar, (HMENU)0, hInst, NULL);
	Ground.hGround = CreateWindow(L"Ground", L"ground", WS_VISIBLE | WS_CHILD, 0, BarHeight, X, Y - BarHeight, Background.hBack, (HMENU)0, hInst, NULL);
	Tank.hTank = CreateWindow(L"Tank", L"tank", WS_CHILD | WS_VISIBLE, Tank.x, Tank.y, TankSize, TankSize, Ground.hGround, NULL, hInst, NULL);
	SetWindowContextHelpId(Tank.hTank, TankRight);
	Tank2.hTank = CreateWindow(L"Tank2", L"tank2", WS_CHILD | WS_VISIBLE, Tank2.x, Tank2.y, TankSize, TankSize, Ground.hGround, NULL, hInst, NULL);
	SetWindowContextHelpId(Tank2.hTank, Tank2Left);
	Coin.hCoin = CreateWindow(L"Coin", L"coin", WS_CHILD | WS_VISIBLE, Coin.x, Coin.y, CoinSize, CoinSize, Ground.hGround, NULL, hInst, NULL);
	if (!Background.hBack || !Tank.hTank || !Ground.hGround || !hBar || !Tank2.hTank || !redBar.hAmmo || !redBar.hHealth || !greyBar.hPoints)
	{
		return FALSE;
	}

	if (!blueBar.hHealth || !blueBar.hAmmo || !blueBar.hPoints || !hRedBar || !hBlueBar || !redBar.hPoints)
	{
		return FALSE;
	}



	return TRUE;
}
void ResetGame()
{
	Tank.x = 0;
	Tank.y = Y / 2 - TankSize / 2;
	Tank2.x = X - TankSize;
	Tank2.y = Y / 2 + TankSize / 2;
	while ((Tank.x == Coin.x - sizeDiff && Tank.y == Coin.y - sizeDiff) || (Tank2.x == Coin.x - sizeDiff && Tank2.y == Coin.y - sizeDiff))
	{
		Coin.x = (rand() % (X / TankSize)) * TankSize + sizeDiff;
		Coin.y = (rand() % ((Y / TankSize)) - 1) * TankSize + sizeDiff;
	}
	DestroyWindow(Tank.hTank);
	DestroyWindow(Tank2.hTank);
	Tank.hTank = CreateWindow(L"Tank", L"tank", WS_CHILD | WS_VISIBLE, Tank.x, Tank.y, TankSize, TankSize, Ground.hGround, NULL, hInst, NULL);
	SetWindowContextHelpId(Tank.hTank, TankRight);
	Tank2.hTank = CreateWindow(L"Tank2", L"tank2", WS_CHILD | WS_VISIBLE, Tank2.x, Tank2.y, TankSize, TankSize, Ground.hGround, NULL, hInst, NULL);
	SetWindowContextHelpId(Tank2.hTank, Tank2Left);
	tick = 0;
	GameON = true;
	GamePaused = false;
	InvalidateRect(Coin.hCoin, NULL, TRUE);
	UpdateWindow(Coin.hCoin);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	CMD = nCmdShow;
	hInst = hInstance; // Store instance handle in our global variable
	Declare();
	//Parent = CreateWindowW(L"Parent", L"", myStyle, Background.x, Background.y, Background.sizeX, Background.sizeY, nullptr, nullptr, hInstance, nullptr);
	Background.hBack = CreateWindowW(L"Background", L"", myStyle, Background.x, Background.y, Background.sizeX, Background.sizeY, nullptr, nullptr, hInst, nullptr);
	SetWindowText(Background.hBack, L"Tanks");
	MakeGame(CMD);
	ShowWindow(Background.hBack, CMD);
	UpdateWindow(Background.hBack);
	MoveCoin();
	RECT rec;
	GetWindowRect(redBar.hHealth, &rec);
	Main.hWindow = CreateWindow(L"MainWindow", L"mainWindow", WS_VISIBLE | WS_EX_TOPMOST | WS_POPUPWINDOW , rec.left, rec.top,X,Y, Background.hBack, nullptr, hInst, nullptr);
	SetFocus(Main.hWindow);
	//if (!Parent)
	//	return FALSE;
	return TRUE;
}
void ResetRedTank()
{
	Tank.health = StartHealth;
	Tank.ammo = StartAmmo;
	Tank.x = Tank2.x;
	Tank.y = Tank2.y;
	while ((Coin.x - sizeDiff == Tank.x && Tank.y == Coin.y - sizeDiff) || (Tank2.x == Tank.x && Tank2.y == Tank.y))
	{
		Tank.x = (rand() % (X / TankSize)) * TankSize;
		Tank.y = (rand() % ((Y / TankSize) - 1)) * TankSize;
	}
	MoveWindow(Tank.hTank, Tank.x, Tank.y, TankSize, TankSize, true);
	InvalidateRect(Tank.hTank, NULL, TRUE);
	InvalidateRect(redBar.hAmmo, NULL, true);
	InvalidateRect(redBar.hHealth, NULL, true);
	InvalidateRect(redBar.hPoints, NULL, true);
	UpdateWindow(Tank.hTank);
	UpdateWindow(redBar.hAmmo);
	UpdateWindow(redBar.hHealth);
	UpdateWindow(redBar.hPoints);
}
void ResetRedTank2()
{
	Tank2.health = StartHealth;
	Tank2.ammo = StartAmmo;
	Tank2.x = Tank.x;
	Tank2.y = Tank.y;
	while ((Coin.x - sizeDiff == Tank2.x && Tank2.y == Coin.y - sizeDiff) || (Tank2.x == Tank.x && Tank2.y == Tank.y))
	{
		Tank2.x = (rand() % (X / TankSize)) * TankSize;
		Tank2.y = (rand() % ((Y / TankSize) - 1)) * TankSize;
	}
	MoveWindow(Tank2.hTank, Tank2.x, Tank2.y, TankSize, TankSize, true);
	InvalidateRect(Tank2.hTank, NULL, TRUE);
	InvalidateRect(blueBar.hAmmo, NULL, TRUE);
	InvalidateRect(blueBar.hHealth, NULL, TRUE);
	InvalidateRect(blueBar.hPoints, NULL, TRUE);
	UpdateWindow(Tank2.hTank);
	UpdateWindow(blueBar.hAmmo);
	UpdateWindow(blueBar.hHealth);
	UpdateWindow(blueBar.hPoints);
}
void MoveCoin()
{
	srand(time(NULL));
	Coin.type = rand() % 3;
	while ((Coin.x - sizeDiff == Tank.x && Tank.y == Coin.y - sizeDiff) || (Tank2.x == Coin.x - sizeDiff && Tank2.y == Coin.y - sizeDiff))
	{
		Coin.x = (rand() % (X / TankSize)) * TankSize + sizeDiff;
		Coin.y = (rand() % ((Y / TankSize) - 1)) * TankSize + sizeDiff;
	}
	MoveWindow(Coin.hCoin, Coin.x, Coin.y, CoinSize, CoinSize, true);
	InvalidateRect(Coin.hCoin, NULL, TRUE);
	PaintCoin();
}
void TakeRedCoin()
{
	wchar_t ss[MAX_LOADSTRING];
	if (Coin.type == 0)
	{
		Tank.points += CoinPoint;
		InvalidateRect(redBar.hPoints, NULL, true);
		UpdateWindow(redBar.hPoints);
	}
	else if (Coin.type == 1)
	{
		Tank.ammo += CoinAmmo;
		InvalidateRect(redBar.hAmmo, NULL, true);
		UpdateWindow(redBar.hAmmo);
	}
	else if (Coin.type == 2)
	{
		Tank.health += CoinHealth;
		InvalidateRect(redBar.hHealth, NULL, true);
		UpdateWindow(redBar.hHealth);
	}
}
void TakeBlueCoin()
{
	wchar_t ss[MAX_LOADSTRING];
	if (Coin.type == 0)
	{
		Tank2.points += CoinPoint;
		InvalidateRect(blueBar.hPoints, NULL, true);
		UpdateWindow(blueBar.hPoints);
	}
	else if (Coin.type == 1)
	{
		Tank2.ammo += CoinAmmo;
		InvalidateRect(blueBar.hAmmo, NULL, true);
		UpdateWindow(blueBar.hAmmo);
	}
	else if (Coin.type == 2)
	{
		Tank2.health += CoinHealth;
		InvalidateRect(blueBar.hHealth, NULL, true);
		UpdateWindow(blueBar.hHealth);
	}
}
LRESULT CALLBACK BulletProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 50, NULL);
		break;
	}
	case WM_TIMER:
	{
		RECT r;
		GetWindowRect(Ground.hGround, &r);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		if (GetWindowContextHelpId(hWnd) == TankDown)
		{
			if (rect.left - r.left - sizeDiffB == Tank2.x && rect.top - r.top + TankSize - sizeDiffB == Tank2.y)
			{
				Tank2.health -= HitHealth;
				Tank.points += HitPoint;
				if (Tank2.health <= 0)
				{
					ResetRedTank2();
					Tank.points += KillPoint;
				}
				InvalidateRect(redBar.hPoints, NULL, true);
				InvalidateRect(blueBar.hHealth, NULL, true);
				UpdateWindow(redBar.hPoints);
				UpdateWindow(blueBar.hHealth);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.top += TankSize;
				rect.bottom += TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Down)
		{
			if (rect.left - r.left - sizeDiffB == Tank.x && rect.top - r.top + TankSize - sizeDiffB == Tank.y)
			{
				Tank.health -= HitHealth;
				Tank2.points += HitPoint;
				if (Tank.health <= 0)
				{
					ResetRedTank();
					Tank2.points += KillPoint;
				}
				InvalidateRect(redBar.hHealth, NULL, true);
				InvalidateRect(blueBar.hPoints, NULL, true);
				UpdateWindow(redBar.hHealth);
				UpdateWindow(blueBar.hPoints);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.top += TankSize;
				rect.bottom += TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == TankUp)
		{
			if (rect.left - r.left - sizeDiffB == Tank2.x && rect.top - r.top - TankSize - sizeDiffB == Tank2.y)
			{
				Tank2.health -= HitHealth;
				Tank.points += HitPoint;
				if (Tank2.health <= 0)
				{
					ResetRedTank2();
					Tank.points += KillPoint;
				}
				InvalidateRect(redBar.hPoints, NULL, true);
				InvalidateRect(blueBar.hHealth, NULL, true);
				UpdateWindow(redBar.hPoints);
				UpdateWindow(blueBar.hHealth);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.top -= TankSize;
				rect.bottom -= TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Up)
		{
			if (rect.left - r.left - sizeDiffB == Tank.x && rect.top - r.top - TankSize - sizeDiffB == Tank.y)
			{
				Tank.health -= HitHealth;
				Tank2.points += HitPoint;
				if (Tank.health <= 0)
				{
					ResetRedTank();
					Tank2.points += KillPoint;
				}
				InvalidateRect(redBar.hHealth, NULL, true);
				InvalidateRect(blueBar.hPoints, NULL, true);
				UpdateWindow(redBar.hHealth);
				UpdateWindow(blueBar.hPoints);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.top -= TankSize;
				rect.bottom -= TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == TankLeft)
		{
			if (rect.left - r.left - TankSize - sizeDiffB == Tank2.x && rect.top - r.top - sizeDiffB == Tank2.y)
			{
				Tank2.health -= HitHealth;
				Tank.points += HitPoint;
				if (Tank2.health <= 0)
				{
					ResetRedTank2();
					Tank.points += KillPoint;
				}
				InvalidateRect(redBar.hPoints, NULL, true);
				InvalidateRect(blueBar.hHealth, NULL, true);
				UpdateWindow(redBar.hPoints);
				UpdateWindow(blueBar.hHealth);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.left -= TankSize;
				rect.right -= TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Left)
		{
			if (rect.left - r.left - TankSize - sizeDiffB == Tank.x && rect.top - r.top - sizeDiffB == Tank.y)
			{
				Tank.health -= HitHealth;
				Tank2.points += HitPoint;
				if (Tank.health <= 0)
				{
					ResetRedTank();
					Tank2.points += KillPoint;
				}
				InvalidateRect(redBar.hHealth, NULL, true);
				InvalidateRect(blueBar.hPoints, NULL, true);
				UpdateWindow(redBar.hHealth);
				UpdateWindow(blueBar.hPoints);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.left -= TankSize;
				rect.right -= TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == TankRight)
		{
			if (rect.left - r.left + TankSize - sizeDiffB == Tank2.x && rect.top - r.top - sizeDiffB == Tank2.y)
			{
				Tank2.health -= HitHealth;
				Tank.points += HitPoint;
				if (Tank2.health <= 0)
				{
					ResetRedTank2();
					Tank.points += KillPoint;
				}
				InvalidateRect(redBar.hPoints, NULL, true);
				InvalidateRect(blueBar.hHealth, NULL, true);
				UpdateWindow(redBar.hPoints);
				UpdateWindow(blueBar.hHealth);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.left += TankSize;
				rect.right += TankSize;
			}
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Right)
		{
			if (rect.left - r.left + TankSize - sizeDiffB == Tank.x && rect.top - r.top - sizeDiffB == Tank.y)
			{
				Tank.health -= HitHealth;
				Tank2.points += HitPoint;
				if (Tank.health <= 0)
				{
					ResetRedTank();
					Tank2.points += KillPoint;
				}
				InvalidateRect(redBar.hHealth, NULL, true);
				InvalidateRect(blueBar.hPoints, NULL, true);
				UpdateWindow(redBar.hHealth);
				UpdateWindow(blueBar.hPoints);
				DestroyWindow(hWnd);
			}
			else
			{
				rect.left += TankSize;
				rect.right += TankSize;
			}
		}
		if (rect.right< r.left || rect.top>r.bottom || rect.bottom < r.top || rect.left>r.right)
		{
			DestroyWindow(hWnd);
		}
		MoveWindow(hWnd, rect.left - r.left, rect.top - r.top, BulletSize, BulletSize, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_DESTROY:

		break;
	case WM_PAINT:
	{
		Image image(L"Textures\\bullet.png");
		PAINTSTRUCT ps;
		if (GetWindowContextHelpId(hWnd) == TankDown || GetWindowContextHelpId(hWnd) == Tank2Down)
		{
			image.RotateFlip(Rotate90FlipX);
		}
		if (GetWindowContextHelpId(hWnd) == TankUp || GetWindowContextHelpId(hWnd) == Tank2Up)
		{
			image.RotateFlip(Rotate90FlipY);
		}
		if (GetWindowContextHelpId(hWnd) == TankLeft || GetWindowContextHelpId(hWnd) == Tank2Left)
		{
			image.RotateFlip(Rotate180FlipY);
		}
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		RECT Crec, Brec;
		GetWindowRect(Coin.hCoin, &Crec);
		GetWindowRect(hWnd, &Brec);
		//if (Crec.left - sizeDiff == Brec.left - sizeDiffB && Crec.top - sizeDiff == Brec.top - sizeDiffB)
		//{
		//	BitBlt(GetDC(Coin.hCoin), 0, 0, BulletSize, BulletSize,hdc, 0, 0, PATPAINT);
		//}
		graphics.DrawImage(&image, 0, 0, BulletSize, BulletSize);
		EndPaint(hWnd, &ps);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK TankProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		Tank.points = 0;
		Tank.health = 100;
		Tank.ammo = 50;
		InvalidateRect(redBar.hAmmo, NULL, true);
		InvalidateRect(redBar.hHealth, NULL, true);
		InvalidateRect(redBar.hPoints, NULL, true);
		UpdateWindow(redBar.hAmmo);
		UpdateWindow(redBar.hHealth);
		UpdateWindow(redBar.hPoints);
		break;
	}
	case WM_KEYDOWN:
	{
		if (wParam == TankLeft)
		{
			SetWindowContextHelpId(Tank.hTank, wParam);
			if (Tank.x >= TankSize && !(Tank.x == Tank2.x + TankSize && Tank.y == Tank2.y)) // A
				Tank.x -= TankSize;

		}
		if (wParam == TankDown)
		{
			SetWindowContextHelpId(Tank.hTank, wParam);
			if (Tank.y < Y - TankSize - BarHeight && !(Tank.x == Tank2.x && Tank.y == Tank2.y - TankSize)) // S
				Tank.y += TankSize;

		}
		if (wParam == TankRight)
		{
			SetWindowContextHelpId(Tank.hTank, wParam);
			if (Tank.x < X - TankSize && !(Tank.x == Tank2.x - TankSize && Tank.y == Tank2.y)) // D
				Tank.x += TankSize;

		}
		if (wParam == TankUp)
		{
			SetWindowContextHelpId(Tank.hTank, wParam);
			if (Tank.y >= TankSize && !(Tank.x == Tank2.x && Tank.y == Tank2.y + TankSize)) // W
				Tank.y -= TankSize;

		}

		if (Tank.x == Coin.x - sizeDiff && Tank.y == Coin.y - sizeDiff)
		{
			TakeRedCoin();
			MoveCoin();
		}
		MoveWindow(hWnd, Tank.x, Tank.y, TankSize, TankSize, true);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(Tank.hTank);

		if (wParam == TankShoot && Tank.ammo > 0) // Space
		{
			Tank.ammo--;
			InvalidateRect(redBar.hAmmo, NULL, true);
			UpdateWindow(redBar.hAmmo);
			struct bullet Bullet;
			Bullet.x = Tank.x + sizeDiffB;
			Bullet.y = Tank.y + sizeDiffB;
			Bullet.way = GetWindowContextHelpId(hWnd);
			if (Bullet.way == TankDown) Bullet.y += TankSize;
			if (Bullet.way == TankUp) Bullet.y -= TankSize;
			if (Bullet.way == TankLeft) Bullet.x -= TankSize;
			if (Bullet.way == TankRight) Bullet.x += TankSize;
			if (Bullet.x == Tank2.x + sizeDiffB && Bullet.y == Tank2.y + sizeDiffB)
			{
				Tank2.health -= HitHealth;
				Tank.points += HitPoint;
				if (Tank2.health <= 0)
				{
					ResetRedTank2();
					Tank.points += KillPoint;
				}
				InvalidateRect(blueBar.hHealth, NULL, true);
				InvalidateRect(redBar.hPoints, NULL, true);
				UpdateWindow(blueBar.hHealth);
				UpdateWindow(redBar.hPoints);
				break;
			}

			Bullet.hBullet = CreateWindow(L"Bullet", L"bullet", WS_CHILD | WS_VISIBLE, Bullet.x, Bullet.y, BulletSize, BulletSize, Ground.hGround, NULL, hInst, (LPVOID)&Bullet);
			SetWindowContextHelpId(Bullet.hBullet, Bullet.way);
		}

	}
	case WM_PAINT:
	{
		Image image(L"Textures\\tank_red.png");
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		if (GetWindowContextHelpId(hWnd) == TankUp)
		{
			graphics.RotateTransform(-90.0f);
			graphics.DrawImage(&image, -TankSize, 0, TankSize, TankSize);
		}
		if (GetWindowContextHelpId(hWnd) == TankDown)
		{
			graphics.RotateTransform(90.0f);
			graphics.DrawImage(&image, 0, -TankSize, TankSize, TankSize);
		}
		if (GetWindowContextHelpId(hWnd) == TankLeft)
		{
			graphics.RotateTransform(180.0f);
			graphics.DrawImage(&image, -TankSize, -TankSize, TankSize, TankSize);
		}
		if (GetWindowContextHelpId(hWnd) == TankRight)
		{
			graphics.DrawImage(&image, 0, 0, TankSize, TankSize);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK Tank2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		Tank2.points = 0;
		Tank2.health = 100;
		Tank2.ammo = 50;
		InvalidateRect(blueBar.hAmmo, NULL, true);
		InvalidateRect(blueBar.hHealth, NULL, true);
		InvalidateRect(blueBar.hPoints, NULL, true);
		UpdateWindow(blueBar.hAmmo);
		UpdateWindow(blueBar.hHealth);
		UpdateWindow(blueBar.hPoints);
		break;
	}
	case WM_KEYDOWN:
	{
		if (wParam == Tank2Left)
		{
			SetWindowContextHelpId(Tank2.hTank, wParam);
			if (Tank2.x >= TankSize && !(Tank.x == Tank2.x - TankSize && Tank.y == Tank2.y)) // 6
				Tank2.x -= TankSize;
		}
		if (wParam == Tank2Down)
		{
			SetWindowContextHelpId(Tank2.hTank, wParam);
			if (Tank2.y < Y - TankSize - BarHeight && !(Tank.x == Tank2.x && Tank.y == Tank2.y + TankSize)) // 5
				Tank2.y += TankSize;
		}
		if (wParam == Tank2Right)
		{
			SetWindowContextHelpId(Tank2.hTank, wParam);
			if (Tank2.x < X - TankSize && !(Tank.x == Tank2.x + TankSize && Tank.y == Tank2.y)) // 8
				Tank2.x += TankSize;
		}
		if (wParam == Tank2Up)
		{
			SetWindowContextHelpId(Tank2.hTank, wParam);
			if (Tank2.y >= TankSize && !(Tank.x == Tank2.x && Tank.y == Tank2.y - TankSize)) // 4
				Tank2.y -= TankSize;
		}

		if (Tank2.x == Coin.x - sizeDiff && Tank2.y == Coin.y - sizeDiff)
		{
			TakeBlueCoin();
			MoveCoin();
		}
		MoveWindow(hWnd, Tank2.x, Tank2.y, TankSize, TankSize, true);
		UpdateWindow(hWnd);

		if (wParam == Tank2Shoot && Tank2.ammo > 0) // Space
		{
			Tank2.ammo--;
			InvalidateRect(blueBar.hAmmo, NULL, true);
			UpdateWindow(blueBar.hAmmo);
			struct bullet Bullet;
			Bullet.x = Tank2.x + sizeDiffB;
			Bullet.y = Tank2.y + sizeDiffB;
			Bullet.way = GetWindowContextHelpId(hWnd);
			if (Bullet.way == Tank2Down) Bullet.y += TankSize;
			if (Bullet.way == Tank2Up) Bullet.y -= TankSize;
			if (Bullet.way == Tank2Left) Bullet.x -= TankSize;
			if (Bullet.way == Tank2Right) Bullet.x += TankSize;

			if (Bullet.x == Tank.x + sizeDiffB && Bullet.y == Tank.y + sizeDiffB)
			{
				Tank.health -= HitHealth;
				Tank2.points += HitPoint;
				if (Tank.health <= 0)
				{
					ResetRedTank();
					Tank2.points += KillPoint;
				}
				wchar_t ss[MAX_LOADSTRING];
				InvalidateRect(redBar.hHealth, NULL, true);
				InvalidateRect(blueBar.hPoints, NULL, true);
				UpdateWindow(redBar.hHealth);
				UpdateWindow(blueBar.hPoints);
				break;
			}

			Bullet.hBullet = CreateWindow(L"Bullet", L"bullet", WS_CHILD | WS_VISIBLE, Bullet.x, Bullet.y, BulletSize, BulletSize, Ground.hGround, NULL, hInst, (LPVOID)&Bullet);
			SetWindowContextHelpId(Bullet.hBullet, Bullet.way);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}
	break;
	case WM_PAINT:
	{
		Image image(L"Textures\\tank_blue.png");
		PAINTSTRUCT ps;
		if (GetWindowContextHelpId(hWnd) == Tank2Down)
		{
			image.RotateFlip(Rotate90FlipX);
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Up)
		{
			image.RotateFlip(Rotate90FlipY);
		}
		if (GetWindowContextHelpId(hWnd) == Tank2Left)
		{
			image.RotateFlip(Rotate180FlipY);
		}
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, 0, 0, TankSize, TankSize);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_KILLFOCUS:
		//{
		//	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) |
		//		WS_EX_LAYERED);
		//	// Make this window 50% alpha
		//	SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
		//	//GameBackgrounded = true;
		//}break;

		//case WM_SETFOCUS:
		//{
		//	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) |
		//		WS_EX_LAYERED);
		//	// Make this window 100% alpha
		//	SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
		//	//GameBackgrounded = false;
		//	//player.left_move = player.right_move = false;
		//}break;
	case WM_ERASEBKGND:
	{
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ESC:
		{
			if (GameON && !GamePaused)
			{
				GamePaused = true;
				TextBlockHover1 = false;
				TextBlockHover2 = false;
				TextBlockHover3 = false;
				RECT rec;
				GetWindowRect(redBar.hHealth, &rec);
				Main.hWindow = CreateWindow(L"MainWindow", L"mainWindow", WS_VISIBLE | WS_EX_TOPMOST | WS_POPUPWINDOW, rec.left, rec.top,X,Y, nullptr, nullptr, hInst, nullptr);
				SetFocus(Main.hWindow);
				break;
			}
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_MOVING: //https://softwareengineering.stackexchange.com/questions/266940/why-is-win32-apis-wm-move-being-called-while-dragging-the-window
	{
		//tutorial
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, 123, LWA_ALPHA);
		UpdateWindow(hWnd);
		break;
	}
	case WM_KEYDOWN:
	{
		TankProc(Tank.hTank, message, wParam, lParam);
		Tank2Proc(Tank2.hTank, message, wParam, lParam);
	}
	break;
	case WM_EXITSIZEMOVE: //https://softwareengineering.stackexchange.com/questions/266940/why-is-win32-apis-wm-move-being-called-while-dragging-the-window
	{
		//tutorial
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
		UpdateWindow(hWnd);
		break;
	}
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 1000, NULL);
		break;
	}
	case WM_TIMER:
	{
		//tutorial
		if (GameON && !GamePaused)
		{
			tick++;
			if (tick >= 60)
			{
				if (Tank.points > Tank2.points) winner = 2;
				else if (Tank.points < Tank2.points) winner = 3;
				else winner = 1;
				GamePaused = false;
				GameON = false;
				TextBlockHover1 = false;
				TextBlockHover2 = false;
				TextBlockHover3 = false;
				RECT rec;
				GetWindowRect(redBar.hHealth, &rec);
				Main.hWindow = CreateWindow(L"MainWindow", L"mainWindow", WS_VISIBLE | WS_EX_TOPMOST | WS_POPUPWINDOW, rec.left, rec.top, X, Y, nullptr, nullptr, hInst, nullptr);
				SetFocus(Main.hWindow);
			}
			InvalidateRect(greyBar.hPoints, NULL, true);
			UpdateWindow(greyBar.hPoints);
		}
		break;
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		GroundProc(Ground.hGround, message, wParam, lParam);
		TankProc(Tank.hTank, message, wParam, lParam);
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (TextBlockHover2)
		{
			GameON = true;
			DestroyWindow(Main.hWindow);
			InvalidateRect(Background.hBack, NULL, true);
		}
	}
	case WM_MOUSEMOVE:
	{
		POINT p;
		GetCursorPos(&p);
		RECT rec;
		GetClientRect(Main.HReturn, &rec);
		if (!PtInRect(&rec, p) && TextBlockHover1)
			SendNotifyMessageW(Main.HReturn, WM_MOUSELEAVE, wParam, lParam);

		GetClientRect(Main.hNewGame, &rec);
		if (!PtInRect(&rec, p) && TextBlockHover2)
			SendNotifyMessageW(Main.hNewGame, WM_MOUSELEAVE, wParam, lParam);

		GetClientRect(Main.hTop10, &rec);
		if (!PtInRect(&rec, p) && TextBlockHover3)
			SendNotifyMessageW(Main.hTop10, WM_MOUSELEAVE, wParam, lParam);
		break;
	}
	case WM_SETFOCUS:
	{
		UpdateWindow(hWnd);
	}
	//case WM_ERASEBKGND:
	//{
	//	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//	SetLayeredWindowAttributes(hWnd, 0, 123, LWA_ALPHA);
	//	break;
	//}
	case WM_CREATE:
	{
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, 123, LWA_ALPHA);
		if (GameON && GamePaused)
		{
			Main.HReturn = CreateWindow(L"TextBlock", L"Return", WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST, (X - ButtonSizeX) / 2, (Y - ButtonSizeY * 5) / 2, ButtonSizeX, ButtonSizeY, hWnd, NULL, GetModuleHandle(NULL), NULL);
		}
		Main.hTop10 = CreateWindow(L"TextBlock3", L"Top 10", WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST, (X - ButtonSizeX) / 2, (Y + ButtonSizeY) / 2, ButtonSizeX, ButtonSizeY, hWnd, NULL, GetModuleHandle(NULL), NULL);
		Main.hNewGame = CreateWindow(L"TextBlock2", L"New Game", WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST, (X - ButtonSizeX) / 2, (Y - ButtonSizeY * 2) / 2, ButtonSizeX, ButtonSizeY, hWnd, NULL, GetModuleHandle(NULL), NULL);
		UpdateWindow(hWnd);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, COLORREF(RGB(0, 0, 0)));
		auto hFont = CreateFont(40, 15, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		RECT rc;
		GetClientRect(hWnd, &rc);
		rc.bottom /= 2;
		if (winner == 1)
		{
			SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
			TCHAR s[] = _T("DRAW");
			DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if(winner == 2)
		{
			SetTextColor(hdc, COLORREF(RGB(255, 0, 0)));
			TCHAR s[] = _T("RED WIN");
			DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (winner == 3)
		{
			SetTextColor(hdc, COLORREF(RGB(0, 0, 255)));
			TCHAR s[] = _T("BLUE WIN");
			DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TANK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Background";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TANK));
	return RegisterClassExW(&wcex);
}
LRESULT CALLBACK GroundProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK CoinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PaintCoin();
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK RedHealthBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		InvalidateRect(hWnd, NULL, true);
		Image image(L"Textures\\emergency-kit.png");
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank.health);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK RedAmmoBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank.ammo);
		Image image(L"Textures\\ammo.png");
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK RedPointBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank.points);
		Image image(L"Textures\\score.png");
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK BlueHealthBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		Image image(L"Textures\\emergency-kit.png");
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank2.health);
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(InfoBar - BarHeight + iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(0, 0, 255)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK BlueAmmoBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		Image image(L"Textures\\ammo.png");
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank2.ammo);
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(InfoBar - BarHeight + iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(0, 0, 255)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK BluePointBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"%02d", Tank2.points);
		Image image(L"Textures\\score.png");
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(InfoBar - BarHeight + iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(255, 255, 255)));
		SetBkColor(hdc, COLORREF(RGB(0, 0, 255)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 3);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK GreyBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		Image image(L"Textures\\timer.png");
		wchar_t ss[MAX_LOADSTRING];
		swprintf_s(ss, MAX_LOADSTRING, L"    %02d:%02d", tick / 60, tick % 60);
		//InvalidateRect(hWnd, NULL, true);
		PAINTSTRUCT ps;
		Gdiplus::Rect rec(iconDiff, iconDiff, BarHeight - iconDiff - iconDiff, BarHeight - iconDiff - iconDiff);
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics graphics(hdc);
		graphics.DrawImage(&image, rec);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(0, 0, 0)));
		SetBkColor(hdc, COLORREF(RGB(50, 50, 50)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TextOutW(hdc, BarHeight, BarHeight / 4, ss, 10);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK TextBlockProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		TextBlockHover1 = true;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_MOUSELEAVE:
	{
		TextBlockHover1 = false;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (TextBlockHover1 && GamePaused && GameON)
		{
			GamePaused = false;
			DestroyWindow(Main.hWindow);
			InvalidateRect(Background.hBack, NULL, true);
		}
	}
	case WM_PAINT:
	{
		if (TextBlockHover1)
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(255, 0, 0))));
		}
		else
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(50, 50, 50))));
		}
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_LEFT);
		if (TextBlockHover1)
		{
			SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		}
		else
		{
			SetBkColor(hdc, COLORREF(RGB(50, 50, 50)));
		}
		SetTextColor(hdc, COLORREF(RGB(0, 0, 0)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TCHAR s[] = _T("RETURN");
		RECT rc;
		GetClientRect(hWnd, &rc);
		DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK TextBlock2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		TextBlockHover2 = true;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_MOUSELEAVE:
	{
		TextBlockHover2 = false;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (TextBlockHover2)
		{
			GameON = true;
			DestroyWindow(Main.hWindow);
			InvalidateRect(Background.hBack, NULL, true);
			ResetGame();
			winner = 0;
		}
	}
	case WM_PAINT:
	{
		if (TextBlockHover2)
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(255, 0, 0))));
		}
		else
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(50, 50, 50))));
		}
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_LEFT);
		SetTextColor(hdc, COLORREF(RGB(0, 0, 0)));
		if (TextBlockHover2)
		{
			SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		}
		else
		{
			SetBkColor(hdc, COLORREF(RGB(50, 50, 50)));

		}
		auto hFont = CreateFont(0, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TCHAR s[] = _T("NEW GAME");
		RECT rc;
		GetClientRect(hWnd, &rc);
		DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK TextBlock3Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		TextBlockHover3 = true;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_MOUSELEAVE:
	{
		TextBlockHover3 = false;
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	}
	case WM_PAINT:
	{
		if (TextBlockHover3)
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(255, 0, 0))));
		}
		else
		{
			SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(COLORREF(RGB(50, 50, 50))));
		}
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_LEFT);
		if (TextBlockHover3)
		{
			SetBkColor(hdc, COLORREF(RGB(255, 0, 0)));
		}
		else
		{
			SetBkColor(hdc, COLORREF(RGB(50, 50, 50)));
		}
		SetTextColor(hdc, COLORREF(RGB(0, 0, 0)));
		auto hFont = CreateFont(0, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		SelectObject(hdc, hFont);
		TCHAR s[] = _T("TOP 10");
		RECT rc;
		GetClientRect(hWnd, &rc);
		DrawText(hdc, s, (int)_tcslen(s), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
LRESULT CALLBACK ParentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}