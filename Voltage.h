#pragma once
#include <Windows.h>

struct Point2D {
	int x;
	int y;
};

bool getKeyDown(char key);

wchar_t* screenBuffer(const int WIDTH, const int HEIGHT);

HANDLE consoleScreenBuffer();

enum Direction {
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

const wchar_t* stats = L"[ESC] Exit                                        Bull Chain                                        SCORE: %d";
const wchar_t* gameover = L"     PRESS [R] TO PLAY AGAIN    ";
