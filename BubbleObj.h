#pragma once

//颜色库
#ifndef WINFDI_H
#define WINFDI_H
#include <wingdi.h>
#endif // !WINFDI_H

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif // !STDLIB_H

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif // !TIME_H

#ifndef THREAD_
#define THREAD_
#include <thread>
#endif // !THREAD_

#ifndef _EASYX_H
#define _EASYX_H
#include "easyx/graphics.h"
#endif // !_EASYX_H



#ifndef _BUBBLE_OBJ_H
#define _BUBBLE_OBJ_H

/**
* 气泡POJO类
*/

class Bubble{
public:
	Bubble();
	~Bubble();
	unsigned int getX();
	unsigned int getY();
	unsigned short getRadius();
	COLORREF getColor();
	bool setX(unsigned int x);
	bool setY(unsigned int y);
	bool setRadius(unsigned short radius);
	bool setColor(COLORREF color);
private:
	unsigned int X;
	unsigned int Y;
	unsigned short radius;
	COLORREF color;
};

Bubble::Bubble(){
	this->radius = 66;
	this->X = this->radius;
	this->Y = this->radius;
	this->color = RGB((BYTE)255, (BYTE)255, (BYTE)255);
	this->color = RGB((BYTE)255, (BYTE)0, (BYTE)0);
}

Bubble::~Bubble(){
}

unsigned int Bubble::getX() {
	return this->X;
}
unsigned int Bubble::getY() {
	return this->Y;
}
unsigned short Bubble::getRadius() {
	return this->radius;
}
COLORREF Bubble::getColor() {
	return this->color;
}

bool Bubble::setX(unsigned int x) {
	this->X = x;
	return true;
}
bool Bubble::setY(unsigned int y) {
	this->Y = y;
	return true;
}
bool Bubble::setRadius(unsigned short radius) {
	this->radius = radius;
	return true;
}
bool Bubble::setColor(COLORREF color) {
	this->color = color;
	return true;
}

#endif // !_BUBBLE_OBJ_H

#ifndef _BUBBLE_FACTORY_H
#define _BUBBLE_FACTORY_H

/**
* 气泡工厂
*/
class BubbleFactory {
public:
	static Bubble* random();
};
Bubble* BubbleFactory::random() {
	Bubble* bubble = new Bubble();

	srand(clock());
	BYTE R = rand() % 128 + 128;
	BYTE G = rand() % 128 + 128;
	BYTE B = rand() % 128 + 128;
	bubble->setColor(RGB(R, G, B));
	srand(time(0) + rand() * clock());
	bubble->setX(rand() % (GetSystemMetrics(SM_CXSCREEN) - 2 * bubble->getRadius()) + bubble->getRadius());
	bubble->setY(GetSystemMetrics(SM_CYSCREEN) + 2 * bubble->getRadius());

	return bubble;
}

#endif // !_BUBBLE_FACTORY_H

#ifndef _MOVE_H
#define _MOVE_H
/**
* 气泡移动类
*/
class Move {
public:
	Move();
	void start(Bubble* bubble);
	void end();
	void setFps(unsigned short fps);
private:
	unsigned short fps;
	bool is;
	void work(Bubble* bubble);
	static void workS(Move* context, Bubble* bubble);
};

Move::Move():is(false), fps(1000) {};

void Move::start(Bubble* bubble) {
	this->is = true; 
	std::thread m(workS, this, bubble);
	m.detach();
}

void Move::end() {
	this->is = false;
}
//自动移动线程
void Move::work(Bubble* bubble) {
	while (this->is) {
		Sleep(1000 / fps);
		//cleardevice();

		int y = bubble->getY() - 1;

		if (y < -bubble->getRadius() * 2) {
			srand(time(0) + clock());
			bubble->setY(GetSystemMetrics(SM_CYSCREEN) + 2 * bubble->getRadius());
			bubble->setX(rand() % GetSystemMetrics(SM_CXSCREEN));
			continue;
		}

		bubble->setY(y);
	}
}

void Move::workS(Move* context, Bubble* bubble) {
	context->work(bubble);
}

void Move::setFps(unsigned short fps) {
	this->fps = fps;
}

#endif // !_MOVE_H

