#include "Global.h"

void drawCube(void)
{
	double len = 200;

	glBegin(GL_QUADS);

	//Vẽ mặt trước
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-len, -len, len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(len, -len, len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(len, len, len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-len, len, len);

	//Vẽ mặt sau
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(len, len, len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(len, len, -len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(len, -len, -len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(len, -len, len);

	//Vẽ mặt bên phải
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(len, len, -len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-len, len, -len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-len, -len, -len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(len, -len, -len);

	//Vẽ mặt bên trái
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-len, -len, -len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-len, -len, len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-len, len, len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-len, len, -len);

	//Vẽ mặt trên
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-len, len, -len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(len, len, -len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(len, len, len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-len, len, len);

	//Vẽ mặt dưới
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-len, -len, -len);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(len, -len, -len);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(len, -len, len);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-len, -len, len);

	glEnd();
}

void renderOxyz() {
	int b = 100; //Độ dài từng trục

	glLineWidth(2); // chọn kích thước nét vẽ

	glBegin(GL_LINES); //OX
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(b, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES); //OY
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, b, 0.0);
	glEnd();

	glBegin(GL_LINES); //OZ
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, b);
	glEnd();

	glFlush();
}