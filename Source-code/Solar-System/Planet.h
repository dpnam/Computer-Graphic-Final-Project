#ifndef _PLANET_H
#define _PLANET_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>
#include "moon.h"

class Planet {
private:
	/*Đơn vị tính: km
	distanceFromSun: Khoảng cách từ Planet đến Sun
	radius: Bán kính của Planet
	*/
	float distanceFromSun, radius;

	/* Đơn vị tính: ngày ở Trái Đất
	- orbitTime: Thời gian để Planet hoàn thành 1 chu kỳ quỹ đạo quay quanh Mặt Trời
	- rotationTime: Thời gian để Planet tự quay 360 độ quanh nó
	*/
	float orbitTime, rotationTime;

	// Ảnh được phủ lên bề mặt Planet
	GLuint textureHandle;

	// Tọa độ (x,y,z) của Planet so với Sun mà nó quay quanh
	float position[3];

	// Góc mà Planet tự quanh 360 độ quanh nó
	float rotation;

	// Danh sách các Moon xung quanh Planet
	std::vector<Moon> moons;

public:
	// Constructor
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Cập nhật lại trạng thái của Planet sau khoảng thời gian time tính từ thời điểm ban đầu (= 0)
	void updateStatus(float time);

	// Vẽ Planet ra không gian vũ trụ
	void render();

	// Vẽ quỹ đạo quay quanh Sun của Planet ra không gian vũ trụ
	void renderOrbit();

	// Các getting
	void getPosition(float vec[3]);
	float getRadius();

	// Thêm 1 Moon vào danh sách moons quay quanh Planet
	void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Vẽ hành tinh tự quay 360 độ quanh mình mà không quay quanh Mặt Trời
	void renderOnly();
};

#endif