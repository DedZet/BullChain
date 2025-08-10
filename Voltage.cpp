#include <Windows.h>

bool getKeyDown(char key) {
	return (0x8000 & GetAsyncKeyState((unsigned char)(key))) != false;
}

wchar_t* screenBuffer(const int WIDTH, const int HEIGHT) {
	wchar_t* screen = new wchar_t[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) screen[i] = L' ';
	return screen;
}

HANDLE consoleScreenBuffer() {
	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	return console;
}