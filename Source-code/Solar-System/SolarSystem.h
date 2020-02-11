#ifndef _SOLARSYSTEM_H
#define _SOLARSYSTEM_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>

#include "planet.h"

class SolarSystem {
private:
	// Lưu lại 9 Planet trong không gian vũ trụ
	std::vector<Planet> planets;

public:
	// Constructer
	SolarSystem();

	// Cập nhật lại trạng thái của Solar System sau khoảng thời gian time tính từ thời điểm ban đầu (= 0)
	void updateStatus(float time);

	// Thêm 1 Planet vào Solar System 
	void addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Thêm 1 Moon của 1 Planet trong Solar System 
	void addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Vẽ Solar System ra không gian 3D
	void render();

	// Vẽ quỹ đạo của tất cả Planets trong Solar System
	void renderOrbits();

	// Lấy tọa độ của 1 Planet thứ index lưu vào vec[3]
	void getPlanetPosition(int index, float vec[3]);

	// Lấy bán kính của 1 Planet thứ index
	float getRadiusOfPlanet(int index);

	// Vẽ duy nhất hành tinh vị trí index ra màn hình
	void renderPlanet(int index);
};

#endif