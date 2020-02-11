#include "moon.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "Global.h"

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromPlanet = distanceFromPlanet;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

void Moon::updateStatus(float time)
{
	// Đơn vị của time: ngày ở Trái Đất
	// Xác định góc mà moon quay được sao thời gian time so với planet
	// orbitTime -> pi radian
	// time      -> ? radian
	float angle = time * 3.1419f / orbitTime;

	// Cập nhật lại vị trí của moon so với planet
	position[0] = sin(angle) * distanceFromPlanet; // x
	position[1] = cos(angle) * distanceFromPlanet; // y
	position[2] = 0; // z

	// Xác định góc mà moon tự quanh quanh nó
	// rotationTime -> 360 độ
	// time         -> ? độ
	rotation = time * 360 / rotationTime;
}

void Moon::render()
{
	glPushMatrix();
	glRotatef(24.3f, 1.0f, 0.0f, 1.0f);

	// Phủ hình ảnh lên bề mặt moon
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// Cập nhật vị trí của moon trên quỹ đạo quay quanh planet, và vị trí quay 360 độ quanh nó
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	glRotatef(-rotation, 0.0f, 0.0f, 1.0f);//Quay quanh trục z
	
    // render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	// Vẽ moon ra màn hình
	gluSphere(quadric, radius * planetSizeScale, 30, 30);

	glPopMatrix();

}


void Moon::renderOrbit()
{
	// Quỹ đạo là 1 đường tròn
	// Ta vẽ đường tròn bằng cách vi phân nó thành những đoạn thẳng tương đối nhỏ (mà mắt thường khó phát hiện được)
	// Sau đó ta chỉ việc vẽ cái đoạn thẳng này và nối đỉnh đầu đoạn thứ i + 1 với đỉnh cuối của đoạn thứ i
	glPushMatrix();
	/*glRotatef(-24.3, 1, 0, 1);*/
	glRotatef(24.3f, 1.0f, 0.0f, 1.0f);

	// Chọn chế độ vẽ các đường thẳng liên tục
	glBegin(GL_LINE_STRIP);

	// Tiến hành vẽ quỹ đạo là hình tròn
	// vẽ các đoạn thẳng liên tiếp rất nhỏ dựa vào góc (từ 0 đến 2pi, bước nhảy là 0.1)
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
	{
		glVertex3f(sin(angle) * distanceFromPlanet * distanceScale, cos(angle) * distanceFromPlanet * distanceScale, 0.0f);
	}
	// nối điểm đầu tiên và điểm cuối cùng lại với nhau
	glVertex3f(0.0f, distanceFromPlanet * distanceScale, 0.0f);

	glEnd();
	glPopMatrix();
}