#include <iostream>
#include <list>
#include <thread>
#include <chrono>
#include <windows.h>
#include <cwchar>
#include "Voltage.h"

#define CURRENT_TIME std::chrono::system_clock::now()
const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 29;

using namespace std::chrono_literals;

int main()
{
	wchar_t* screen = screenBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);
	HANDLE hConsole = consoleScreenBuffer();
	DWORD dwBytesWritten = 0;

	 while (1) {
		Beep(1400, 100);
		Beep(1600, 100);
		
		std::list<Point2D> snake = { {60,15},{61,15},{62,15},{63,15} };
		Point2D food = { 30,15 };
		Direction snakeDir = Left;
		bool isDead = false;
		bool bKeyLeft = false, bKeyRight = false, bKeyUp = false, bKeyDown = false;
		int score = 0;

	 	 while (!isDead) {

			//////////////// CONTROLLER ////////////////
			auto time = CURRENT_TIME; 
			while ((CURRENT_TIME - time < ((snakeDir % 2 == 1) ? 70ms : 120ms))) {
				bKeyRight = getKeyDown('\x27') || getKeyDown('\x44');
				bKeyLeft = getKeyDown('\x25') || getKeyDown('\x41');
				bKeyUp = getKeyDown('\x26') || getKeyDown('\x57');
				bKeyDown = getKeyDown('\x28') || getKeyDown('\x53');

				if (bKeyRight && snakeDir != Left) snakeDir = Right;
				if (bKeyLeft && snakeDir != Right) snakeDir = Left;
				if (bKeyUp && snakeDir != Down) snakeDir = Up;
				if (bKeyDown && snakeDir != Up) snakeDir = Down;
				if (getKeyDown('\x1b')) return 0; // [ESC]
			}

			//////////////// DIRECTION HANDLER ////////////////
			switch (snakeDir) {
			case 0: snake.push_front({ snake.front().x, snake.front().y - 1 }); break; // UP
			case 1: snake.push_front({ snake.front().x + 1, snake.front().y }); break; // RIGHT
			case 2: snake.push_front({ snake.front().x, snake.front().y + 1 }); break; // DOWN
			case 3: snake.push_front({ snake.front().x - 1, snake.front().y }); break; // LEFT
			}
			//////////////// COLLISION ////////////////
	 		if (snake.front().x == food.x && snake.front().y == food.y) {
	 			score++;
				Beep(2600, 100);
	 			while (screen[food.y * SCREEN_WIDTH + food.x] != L' ') {
	 				food.x = rand() % SCREEN_WIDTH;
	 				food.y = (rand() % (SCREEN_HEIGHT - 3)) + 3;
	 			}
	 			for (int i = 0; i < 5; i++) snake.push_back({ snake.back().x, snake.back().y });	
	 		}
	 		if (snake.front().x < 0 || snake.front().x >= SCREEN_WIDTH) isDead = true;
	 		if (snake.front().y < 3 || snake.front().y >= SCREEN_HEIGHT) isDead = true;
	 		
	 		for (std::list<Point2D>::iterator i = snake.begin(); i != snake.end(); i++)
	 			if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
	 				isDead = true;

	 		snake.pop_back();
	 		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

			//////////////// STATS ////////////////
			for (int i = 0; i < SCREEN_WIDTH; i++) {
				screen[i] = L'=';
	 			screen[2 * SCREEN_WIDTH + i] = L'=';
	 		}
	 		wsprintf(&screen[SCREEN_WIDTH + 5], stats, score);
	 		for (auto s : snake) screen[s.y * SCREEN_WIDTH + s.x] = isDead ? L'*' : L'o';
	 		screen[snake.front().y * SCREEN_WIDTH + snake.front().x] = isDead ? L'X' : L'0';
	 		screen[food.y * SCREEN_WIDTH + food.x] = L'■';
	 		if (isDead) wsprintf(&screen[15 * SCREEN_WIDTH + 40], gameover);
	 		WriteConsoleOutputCharacter(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0,0 }, &dwBytesWritten);
	 	 }

		Beep(400, 130);
		Beep(300, 130);
		Beep(200, 130);
	 	while (!getKeyDown('\x52')); // [R]
	 }

	return 0;
}

