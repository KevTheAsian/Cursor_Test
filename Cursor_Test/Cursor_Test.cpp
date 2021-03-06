#include "pch.h"
//#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace std;

/*https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes*/
//for vitual key references

void LeftClick()	//how to write?
{
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void RightClick()	//how to write?
{
	INPUT    Input = { 0 };
	// right down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// right up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void MoveMouse()
{
	int x, y;	// (0, 0) is top left corner. Check later for screen conventions
	x = 20;		//starting point

	//moves mouse along path
	do
	{
		y = 200;	//starting point
		do
		{
			SetCursorPos(x, y);	//check out API later
			y++;
			printf("%d, %d\n", x, y);
			if ((y % 3) == 0)	//clicks in intervals
			{
				LeftClick();
			}
		} while (y < 500);
		x++;
	} while (x < 200);
}

void GetLocation()
{
	for (;;)	//retrieves cursor location actively
	{
		POINT p;

		if (GetCursorPos(&p))
		{
			system("CLS");
			printf("%d, %d\n", p.x, p.y);
			Sleep(75);	//makes system wait to slow down update time
		}
	}
}

void KeyboardPress(char letter)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;	//hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	//press "A" key
	if (letter == 'a')
	{
		ip.ki.wVk = 0x41;	//key for "a"
	}
	else if (letter == 'b')
	{
		ip.ki.wVk = 0x42;	//key for "b"
	}
	ip.ki.dwFlags = 0;	//0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	//release "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP;	//for key release
	SendInput(1, &ip, sizeof(INPUT));
}

void HideConsole()	//read up on syntax
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return (::IsWindowVisible(::GetConsoleWindow()) != FALSE);
}

int main()
{
	HideConsole();
	/*
	POINT p;
	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y
	}

	if (ScreenToClient(hwnd, &p))
	{
		//p.x and p.y are now relative to hwnd's client area
	}
	*/		
	Sleep(2000);
	int hex;
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	input.ki.wVk = VK_LWIN;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	input.ki.wVk = 0x52;
	SendInput(1, &input, sizeof(INPUT));

	input.ki.wVk = VK_LWIN;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));

	input.ki.wVk = 0x52;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));

	return 0;
}