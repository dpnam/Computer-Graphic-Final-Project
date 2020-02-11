#ifndef _MOON_H
#define _MOON_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>

/*Mỗi một hành hành tinh có thể có các moon quay quanh nó.
Việc này tương tự như các hành tinh có thể quay quanh Mặt Trời.
Mặt trăng không phải là 1 hành tinh trong vũ trụ, nó không quay quanh Mặt Trời, mà lại quay quanh Trái Đất*/

class Moon {
private:
	/* Đơn vị tính: km
	- distanceFromPlanet: Khoảng cách từ moon đến Planet
	- radius: Bán kính của Moon
	*/
	float distanceFromPlanet, radius;

	/* Đơn vi tính: ngày ở Trái Đất
	- orbitTime: Thời gian để Moon hoàn thành 1 chu kỳ quỹ đạo quay quanh Planet
	- rotationTime: Thời gian để Moon tự quay 360 độ quanh nó
	*/
	float orbitTime, rotationTime;


	// Ảnh được phủ lên bề mặt Moon
	GLuint textureHandle;

	// Tọa độ (x,y,z) của Moon so với Planet mà nó quay quanh
	float position[3];

	// Góc mà Moon tự quanh quanh nó
	float rotation;

public:
	// Contructer
	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Cập nhật lại trạng thái của Moon sau khoảng thời gian time tính từ thời điểm ban đầu (= 0)
	void updateStatus(float time);

	// Vẽ Moon ra không gian vũ trụ
	void render();

	// Vẽ quỹ đạo quay của Moon ra không gian vũ trụ
	void renderOrbit();
};

#endif