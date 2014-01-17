#include <Windows.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
struct Vec2 { int x; int y; Vec2():x(0), y(0) {} Vec2(int x, int y):x(x), y(y) {} };
int main() {
	timeBeginPeriod(0);
	srand((unsigned int)time(nullptr));
	HANDLE output = (HANDLE)::GetStdHandle(STD_OUTPUT_HANDLE), input = (HANDLE)::GetStdHandle(STD_INPUT_HANDLE);
	SMALL_RECT windowSize = {0, 0, 70 - 1, 35 - 1};
	COORD bufferSize = {70, 35}, bufferCoord = {0, 0};
	SMALL_RECT region = {0, 0, 70 - 1, 35 - 1};
	CHAR_INFO outputBuffer[70 * 35];	
	bool isGameDone = false;
	Vec2 applePosition = Vec2(10, 10), snake[100], snakeDirection(-1, 0);
	DWORD numberOfEvents, numberOfEventsRead;
	INPUT_RECORD* eventBuffer = nullptr;
	unsigned int currentTime = timeGetTime(), previousTime = currentTime, elapsedTime = 0, milliSecondsPerMovement = 100, movementTimer = 0, snakeLength = 1;
	float delta = 0.0f;
	for (unsigned int i = 0; i < snakeLength; ++i) { snake[i] = Vec2(70 / 2, 35 / 2); }
	::SetConsoleTitleA("ASCII_Snake");
	::SetConsoleWindowInfo(output, TRUE, &windowSize);
	::SetConsoleScreenBufferSize(output, bufferSize);
	while (!isGameDone) {
		previousTime = currentTime;
		currentTime = timeGetTime();
		elapsedTime = currentTime - previousTime;
		for (int i = 0; i < 70 * 35; ++i) { outputBuffer[i].Char.AsciiChar = ' '; outputBuffer[i].Attributes = 0; }
		::GetNumberOfConsoleInputEvents(input, &numberOfEvents);
		if (numberOfEvents) { eventBuffer = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * numberOfEvents); ReadConsoleInput(input, eventBuffer, numberOfEvents, &numberOfEventsRead); }
		for (unsigned int i = 0; i < numberOfEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT) {
				if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) { if (!(snakeDirection.x == 1 && snakeDirection.y == 0)) { snakeDirection.x = -1; snakeDirection.y = 0; } } 
				if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) { if (!(snakeDirection.x == -1 && snakeDirection.y == 0)) { snakeDirection.x = 1; snakeDirection.y = 0; }  }
				if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) { if (!(snakeDirection.x == 0 && snakeDirection.y == 1)) { snakeDirection.x = 0; snakeDirection.y = -1; }  }
				if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) { if (!(snakeDirection.x == 0 && snakeDirection.y == -1)) { snakeDirection.x = 0; snakeDirection.y = 1; } }
			}
		}
		if (numberOfEvents > 0) { free(eventBuffer); }
		if ((movementTimer += elapsedTime) > milliSecondsPerMovement) { for (int i = snakeLength - 1; i > 0; --i) { snake[i].x = snake[i - 1].x; snake[i].y = snake[i - 1].y; } snake[0].x += snakeDirection.x; snake[0].y += snakeDirection.y; movementTimer = 0; }
		for (unsigned int i = 1; i < snakeLength - 1; ++i) { if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) { isGameDone = true; } }
		if (snake[0].x < 0 || snake[0].x > 70 - 1 || snake[0].y < 0 || snake[0].y > 35 - 1) { break; }
		if (snake[0].x == applePosition.x && snake[0].y == applePosition.y) {		
			while (true) {
				bool foundGoodSpot = true;
				applePosition.x = rand() % 70;
				applePosition.y = rand() % 35;
				for (unsigned int i = 0; i < snakeLength; ++i) { if (snake[i].x == applePosition.x && snake[i].y == applePosition.y) { foundGoodSpot = false; } }
				if (foundGoodSpot) { break; }
			}
			snake[snakeLength++] = Vec2(snake[snakeLength - 1].x, snake[snakeLength - 1].y);
			milliSecondsPerMovement -= (milliSecondsPerMovement < 50) ? 0 : 10;
		}
		outputBuffer[applePosition.y * 70 + applePosition.x].Char.AsciiChar = '@';
		outputBuffer[applePosition.y * 70 + applePosition.x].Attributes = FOREGROUND_RED;	
		for (unsigned int i = 0; i < snakeLength; ++i) {
			outputBuffer[snake[i].y * 70 + snake[i].x].Char.AsciiChar = '#';
			outputBuffer[snake[i].y * 70 + snake[i].x].Attributes = FOREGROUND_GREEN;
		}		
		::WriteConsoleOutputA(output, outputBuffer, bufferSize, bufferCoord, &region);
	}
	timeEndPeriod(0);
	return 0;
}