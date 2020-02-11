#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <cmath>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\gl.h>
#include <gl\glut.h>
#include <GL\glu.h>

#include "TGA.h"
#include "SolarSystem.h"
#include "Camera.h"
#include "Global.h"

class Program {
private:
	SolarSystem solarSystem;
	Camera camera;

	// Kích thước cửa sổ OpenGL
	int screenWidth, screenHeight;

	// Texture hỗ trợ vẽ bản hướng dẫn sử dụng, không gian vũ trụ, và Mặt Trăng
	TGA* help, *galaxy, *moon;

	// Cờ hiện bản hướng dẫn
	bool helpDialogue = true;

	// Cờ hiện quỹ đạo của Planets trong vũ trụ
	bool showOrbits = true;

	// Hành tinh được chọn: đánh số từ 0 -> 9
	int planetSelected = 1;

	// Thời gian toàn Solar System
	double time;

	// Thời gian về tốc độ quay của các Planet trong Solar System
	double timeSpeed;

	// Điều khiển vị trí Camera
	Control controlsCamera;

	// Điều khiển Điểm nhìn của Camera
	Control controlsPointView;

public:
	Program();
	~Program();

	// timer function called every 10ms or more
	void timer(int);
	void init();
	void drawCube();
	void display();
	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void reshape(int w, int h);

	void run();
};

#endif