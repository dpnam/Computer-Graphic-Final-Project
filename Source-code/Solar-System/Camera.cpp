#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>
#include "Camera.h"


Camera::Camera()
{
	speedMove = 0.005f; //Tốc độ di chuyển lại gần hay ra xa điểm nhìn
	speedRotate = 3.14 / 320; //Tốc độ di chuyển xung quanh điểm nhìn 

	// Chọn vị trí đặt Camera hợp lý
	position[0] = 2;
	position[1] = -4;
	position[2] = 2;


	// Chọn điểm nhìn tại góc tọa độ
	pointView[0] = 0.0f;
	pointView[1] = 0.0f;
	pointView[2] = 0.0f;

	update();
}

void Camera::set() {
	// Nhìn từ trục Oz, cemara đặt theo trục z, do trục z hướng thẳng đứng
	gluLookAt(position[0], position[1], position[2], pointView[0], pointView[1], pointView[2], 0, 0, 1);
}


void Camera::update()
{
	int dx = position[0] - pointView[0];
	int dy = position[1] - pointView[1];
	int dz = position[2] - pointView[2];

	radius = (sqrt(dx*dx + dy*dy));
	angle = atan2(dx, dy);
}

void Camera::speedUp()
{
	if (speedMove < 1.0f)
		speedMove *= 2; //Tăng tốc độ lên gấp đôi
}

void Camera::speedDown()
{
	if (speedMove  > 0.000001f)
		speedMove /= 2; //Giảm tốc độ xuống một nửa
}

void Camera::forwardCamera()
{
	// Ban đầu
	// V(x1,y,1,z1), P(x2,y2,z2)
	// VP = (x2 - x1, y2 - y1, z2 - z1)

	// Sao khi dịch chuyển
	// V(x1,y,1,z1), P'(x2',y2',z2')
	// VP' = (x2' - x1, y2' - y1, z2' - z1)

	// VP > VP' với VP/VP' = 1/(1-speedMove)
	// VP' = (1-speedMove)*VP
	// x2' - x1 = (1-k)(x2-x1) => x2' = (1-k)*x2 + k*x1
	// Tương tự => y2', z2'

	for (int i = 0; i < 3; i++)
		position[i] = (1 - speedMove) * position[i] + speedMove * pointView[i];

	update();
}

void Camera::backwardCamera()
{
	//Tương tự forward Camera
	for (int i = 0; i < 3; i++)
		position[i] = (1 + speedMove) * position[i] - speedMove * pointView[i];

	update();
}

void Camera::rightCamera()
{
	// Điểm nhìn sẽ di chuyển xung quanh theo một đường tròn có song song với mặt Oxy
	angle -= speedRotate;

	position[0] = sin(angle) * radius + pointView[0];
	position[1] = cos(angle) * radius + pointView[1];
}

void Camera::leftCamera()
{
	// Điểm nhìn sẽ di chuyển xung quanh theo một đường tròn có song song với mặt Oxy
	angle += speedRotate;

	position[0] = sin(angle) * radius + pointView[0];
	position[1] = cos(angle) * radius + pointView[1];
}

void Camera::upCamera()
{
	position[2] += speedMove;
}

void Camera::downCamera()
{
	position[2] -= speedMove;
}


//Phần điểm nhìn tương tự camera
void Camera::forwardPointView()
{
	for (int i = 0; i < 3; i++)
		pointView[i] = (1 - speedMove) * pointView[i] + speedMove * position[i];

}

void Camera::backwardPointView()
{
	for (int i = 0; i < 3; i++)
		pointView[i] = (1 + speedMove) * pointView[i] - speedMove * position[i];
}

void Camera::rightPointView()
{
	pointView[0] += speedMove;
}

void Camera::leftPointView()
{
	pointView[0] -= speedMove;
}

void Camera::upPointView()
{
	pointView[2] += speedMove;
}

void Camera::downPointView()
{
	pointView[2] -= speedMove;
}