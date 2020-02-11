#include "Planet.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "Global.h"

float planetSizeScale = 0.000005f;

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

void Planet::updateStatus(float time)
{
	// Đơn vị của time: ngày ở Trái Đất
	// Xác định góc mà Planet quay được sao thời gian time so với Sun
	// orbitTime -> pi radian
	// time      -> ? radian
	float angle = time * 3.1419f / orbitTime;

	// Cập nhật lại vị trí của Planet so với Sun
	position[0] = sin(angle) * distanceFromSun; // x
	position[1] = cos(angle) * distanceFromSun; // y
	position[2] = 0; // z

	// Xác định góc mà Planet tự quanh quanh nó
	// rotationTime -> 360 độ
	// time         -> ? độ
	rotation = time * 360 / rotationTime;

	// Tính toán lại các trạng thái của moons xung quanh Planet
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].updateStatus(time);
	}
}

void Planet::render()
{
	glPushMatrix();

	// Phủ hình ảnh lên bề mặt Planet
	//glBindTexture(GL_TEXTURE_2D, textureHandle);

	// Cập nhật vị trí của Planet trên quỹ đạo quay quanh Sun, và vị trí quay 360 độ quanh nó
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	// Vẽ các các moons xung quanh Planet
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].render();
	}

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// Cập nhật vị trí quay của Planet 360 độ quanh nó
	//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	if (radius == 6371)// Trái Đất
	{
		//glRotatef(rotation, 0.45f, 0.0f, 1.0f);

		glRotatef(24.3f, 1.0f, 0.0f, 1.0f);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);

		//Vẽ trục quay Trái Đất
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, radius * planetSizeScale + 0.05);
		glVertex3f(0.0, 0.0, -(radius * planetSizeScale + 0.05));
		glEnd();
	}
	else
	{
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	}


	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	glRotatef(180, 0.0f, 1.0f, 0.0f);
	if (distanceFromSun < 0.001f)
	{
		// Xử lý trường hợp Sun

		// Kích thước của Sun quá lớn so với các hành tinh
		// nên ta phải cập nhật lại kích thước tương đối nhỏ để vẽ minh họa
		// nhưng phải đảm bảo Sun trong vũ trụ là to nhất
		float radiusScaled = radius * planetSizeScale;
		if (radiusScaled > 0.5f) radiusScaled = 0.5f;

		// Sun là hành tinh duy chất không bị chiếu sáng
		// mà nó sẽ chiếu sáng cho tất cả cách hành tinh khác trong vũ trụ
		glDisable(GL_LIGHTING);

		// Vẽ Sun ra không gian
		gluSphere(quadric, radiusScaled, 30, 30);

		// Đồng thời bật chế độ chiếu sáng trở lại cho các Plane khác
		glEnable(GL_LIGHTING);

	}
	else
	{
		// Vẽ Planet ra không gian
		gluSphere(quadric, radius * planetSizeScale, 30, 30);
	}


	glPopMatrix();
}

void Planet::renderOrbit()
{
	// Quỹ đạo là 1 đường tròn
	// Ta vẽ đường tròn bằng cách vi phân nó thành những đoạn thẳng tương đối nhỏ (mà mắt thường khó phát hiện được)
	// Sau đó ta chỉ việc vẽ cái đoạn thẳng này và nối đỉnh đầu đoạn thứ i + 1 với đỉnh cuối của đoạn thứ i
	// Chọn chế độ vẽ các đường thẳng liên tục


	glBegin(GL_LINE_STRIP);

	// Tiến hành vẽ quỹ đạo là hình tròn
	// vẽ các đoạn thẳng liên tiếp rất nhỏ dựa vào góc (từ 0 đến 2pi, bước nhảy là 0.05)
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.005f)
	{
		glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale, 0.0f);
	}

	// nối điểm đầu tiên và điểm cuối cùng lại với nhau
	glVertex3f(0.0f, distanceFromSun * distanceScale, 0.0f);

	glEnd();


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Vẽ các quỹ đạo của các Moon xung quanh Planet
	glPushMatrix();

	// do vị trí của các Moon là khoảng cách tính từ nó đến Planet
	// nên ta phải cập nhật lại gốc tọa độ là tâm của Planet
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	// tiến hành vẽ các quỹ đạo moons
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].renderOrbit();
	}
	glPopMatrix();

}


// Get its position in 3d world space units (after scaling) and put it into the 3d vector
void Planet::getPosition(float vec[3])
{
	vec[0] = position[0] * distanceScale;
	vec[1] = position[1] * distanceScale;
	vec[2] = position[2] * distanceScale;
}

float Planet::getRadius()
{
	return radius;
}

void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}

void Planet::renderOnly()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0, 0, 0.0, 0.0, 0.0, 0, 0, 1);

	glPushMatrix();
	glTranslatef(0, 0.3, -0.1);
	glRotatef(180, 0.0f, 1.0f, 0.0f);

	// Phủ hình ảnh lên bề mặt Planet
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// Cập nhật vị trí quay của Planet 360 độ quanh nó
	if (radius == 6371)//Trái Đất
	{
		glRotatef(24.3f, 1.0f, 0.0f, 1.0f);
		glRotatef(rotation / 15, 0.0f, 0.0f, 1.0f);

		//glRotatef(rotation / 15, 0.4512f, 0.0f, 1.0f);
		//glRotatef(-rotation / 15, 0.0f, 0.0f, 1.0f);


	}
	else {
		glRotatef(rotation / 15, 0.0f, 0.0f, 1.0f);
	}

	//Vẽ trục quay của hành tinh
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.5);
	glVertex3f(0.0, 0.0, -0.5);
	glEnd();

	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	glDisable(GL_LIGHTING);
	gluSphere(quadric, 0.3, 30, 30);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}
