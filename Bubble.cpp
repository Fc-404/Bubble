/**
* Fc-404
* 2020-11-05
* 模拟气泡屏保
*/

#include <iostream>
#include <thread>

#include <Windows.h>
#include <conio.h>

#include "BubbleObj.h"
#include "easyx/graphics.h"

constexpr auto BUBBLE_S = 20;


inline void draw(Bubble* bubble);
inline void startBubble(Bubble** bubble, Move** m);

int main(int args[]) {

	//获取屏幕宽高
	int windowHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowWidth = GetSystemMetrics(SM_CXSCREEN);
	//声明一个easyx窗口
	initgraph( windowWidth, windowHeight, EW_NOMINIMIZE);
	HWND window = GetHWnd();
	//设置窗口句柄，使其无title
	SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) - WS_CAPTION);
	//设置窗口句柄，使其full
	SetWindowPos(window, HWND_TOP, 0, 0, windowWidth, windowHeight, SWP_SHOWWINDOW);
	//SetWindowPos(window, HWND_TOP, 0, 0, 1000, 800, SWP_SHOWWINDOW);

	//建立绘制缓存
	BeginBatchDraw();

	Bubble* bubble[BUBBLE_S] = {};
	Move* m[BUBBLE_S] = {};
	for (int i = 0; i < BUBBLE_S; i++) {
		bubble[i] = BubbleFactory::random();
		srand(clock());
		Sleep(rand() % 66 + 20);
		m[i] = new Move();
	}

	std::thread run(startBubble, bubble, m);
	run.detach();

	while (!_kbhit()) {
		cleardevice();
		for (int i = 0; i < BUBBLE_S; i++)
			draw(bubble[i]);
		//绘制缓存
		FlushBatchDraw();
	}
	//关闭绘制缓存
	EndBatchDraw();

	for (int i = 0; i < BUBBLE_S; i++) {
		m[i]->end();
	}
	delete m;
	delete bubble;

	DestroyWindow(window);
}

void startBubble(Bubble** bubble, Move** m) {
	for (int i = 0; i < BUBBLE_S; i++) {
		m[i]->start(bubble[i]);
		srand(clock());
		Sleep(rand() % 3000 + 2000);
	}
}

inline void draw(Bubble* bubble) {
	setcolor(bubble->getColor());
	circle(bubble->getX(), bubble->getY(), bubble->getRadius());
}