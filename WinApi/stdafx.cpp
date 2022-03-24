#include "stdafx.h"





ATOM MyRegisterCoin(HINSTANCE hInstance)
{

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CoinProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Coin";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBullet(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BulletProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Bullet";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GroundProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Bar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterRedBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GroundProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"RedBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterRedAmmoBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = RedAmmoBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"RedAmmoBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}
ATOM MyRegisterRedPointBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = RedPointBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"RedPointBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}
ATOM MyRegisterRedHealthBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = RedHealthBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 0, 0)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"RedHealthBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBlueBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GroundProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"BlueBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBlueAmmoBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BlueAmmoBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"BlueAmmoBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBlueHealthBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BlueHealthBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"BlueHealthBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterBluePointBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BluePointBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 255)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"BluePointBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterGreyBar(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GreyBarProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GreyBar";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterGround(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GroundProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Ground";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}


ATOM MyRegisterTank(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TankProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Tank";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterTank2(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Tank2Proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Tank2";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterMainWindow(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
	wcex.hbrBackground = BackGroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MainWindow";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterTextBlock(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TextBlockProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"TextBlock";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterTextBlock2(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TextBlock2Proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"TextBlock2";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterTextBlock3(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TextBlock3Proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"TextBlock3";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

ATOM MyRegisterParent(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ParentProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(50, 50, 50)));
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"Parent";
	wcex.hIconSm = NULL;
	return RegisterClassExW(&wcex);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}