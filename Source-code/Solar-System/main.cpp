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

#pragma comment (lib, "glut32")

void drawCube(void); //vẽ khối hình lập phương
void renderOxyz(); //vẽ trục tọa độ

int screenWidth, screenHeight;// kích thước cửa sổ

//Các biến dùng để lưu texture
TGA* help, *galaxy, *moon;
TGA* information[10]; //texture thể hiện thông tin của các hành tin
TGA* infoSolarSystem;

int index = -1;// đại diện cho hành tinh thứ mấy được chọn

//Các cờ hiệu show các đối tượng 3D ra màn hình
bool isInfoSolarSystem = false;
bool showSolarSystem = true;
bool helpDialogue = false;
bool showOrbits = false;
bool drawOxyz = false;

SolarSystem solarSystem; // Khai báo hệ mặt trời
Camera camera; // Khai báo camera

// Thời gian của hệ mặt Trời (giúp cập nhật trạng thái)
double time;
double timeSpeed;

// struct điều khiển từ người dùng
struct ControlUser
{
	bool forward, backward, left, right, up, down;
};

ControlUser controlsCamera; //Điều khiển camera
ControlUser controlsPointVeiw; //Điều khiển điểm nhìn

// timer function called every 10ms or more
void timer(int)
{
	glutPostRedisplay(); // post for display func
	glutTimerFunc(10, timer, 0); // limit frame drawing to 100fps
}


// Hàm khởi tạo các giá trị cho Hệ Mặt Trời
void initSolarSystem() 
{
	// Load tất cả các hình ảnh cho các đội tượng
	help = new TGA("images/help.tga");
	galaxy = new TGA("images/galaxy.tga");
	moon = new TGA("images/moon.tga");
	
	//Texture: https://es.dreamstime.com/stock-de-ilustraci%C3%B3n-venus-planeta-hoja-de-datos-t%C3%A9cnica-corte-de-la-secci%C3%B3n-image45061509
	// Phần texture chưa thông tin của các hành tinh
	infoSolarSystem = new TGA("Information_Planet/info.tga");

	information[0] = new TGA("Information_Planet/sun.tga");
	information[1] = new TGA("Information_Planet/mercury.tga");
	information[2] = new TGA("Information_Planet/venus.tga");
	information[3] = new TGA("Information_Planet/earth.tga");
	information[4] = new TGA("Information_Planet/mars.tga");
	information[5] = new TGA("Information_Planet/jupiter.tga");
	information[6] = new TGA("Information_Planet/saturn.tga");
	information[7] = new TGA("Information_Planet/uranus.tga");
	information[8] = new TGA("Information_Planet/neptune.tga");
	information[9] = new TGA("Information_Planet/pluto.tga");

	//Data texture: https://www.solarsystemscope.com/textures/
	TGA* sun = new TGA("images/sun.tga");
	TGA* mercury = new TGA("images/mercury.tga");
	TGA* venus = new TGA("images/venus.tga");
	TGA* earth = new TGA("images/earth.tga");
	TGA* mars = new TGA("images/mars.tga");
	TGA* jupiter = new TGA("images/jupiter.tga");
	TGA* saturn = new TGA("images/saturn.tga");
	TGA* uranus = new TGA("images/uranus.tga");
	TGA* neptune = new TGA("images/neptune.tga");
	TGA* pluto = new TGA("images/pluto.tga");

	// Thêm Planets, và moons vào Solar System
	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureHandle()); // Sun
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureHandle()); // Mercury
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureHandle()); // Venus
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle()); // Earth
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureHandle()); // Mars
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle()); // Jupiter
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle()); // Saturn
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); // Uranus
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle()); // Neptune
	solarSystem.addPlanet(5906380000, 90616, 6.39, 1137, pluto->getTextureHandle()); // Pluto

	solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle()); // Moon của Earth
}


// Hàm khởi tạo các tham số ban đầu cho OpenGL
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // Xóa màu màn hình (màu đen)
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D); // Bật chế độ texture 2D

	glEnable(GL_LIGHTING); 	// Bật chế độ chiếu sáng
	glMatrixMode(GL_MODELVIEW); // Ma trận modelview
	glLoadIdentity(); // Load ma trận đơn vị

	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // Ánh sáng phản chiếu bị phản xạ
	GLfloat matAmbience[] = { 0.5, 0.5, 0.5, 1.0 }; // Ánh sáng môi trường bị phản xạ
	GLfloat matShininess[] = { 30.0 }; // Độ bóng vật liệu

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	//Thiết lập vật liệu
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.5, 0.5, 0.5, 1.0 }; // Xác định ánh sáng môi trường
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Tạo ánh sáng khuếch tán cho đối tượng (Trắng)
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // Tạo ánh sáng phản xạ cho đối tượng (Trắng)

	// Khởi tạo nguồn sáng 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);// Bật công tắc mở đèn
	glEnable(GL_LIGHT0); // Bóng đèn thứ 0 được mở
	glDisable(GL_LIGHTING); // Tắt công tắc đèn

	initSolarSystem();

	//khơỉ tạo thời gian chuyển động của hệ Mặt Trời
	time = 2.552f;
	//time = 4.1f;
	timeSpeed = 0.1f;

	// Khởi tạo các giá trị điều khiển camera vá điểm nhìn = false
	controlsCamera.forward = false;
	controlsCamera.backward = false;
	controlsCamera.left = false;
	controlsCamera.right = false;
	controlsCamera.up = false;
	controlsCamera.down = false;

	controlsPointVeiw.forward = false;
	controlsPointVeiw.backward = false;
	controlsPointVeiw.left = false;
	controlsPointVeiw.right = false;
	controlsPointVeiw.up = false;
	controlsPointVeiw.down = false;
	timer(0);
}

// Hàm vẽ bảng thông tin hành tinh ra màn hình
void renderInformation(float height, float width, TGA* _tga)
{
	
	glBindTexture(GL_TEXTURE_2D, _tga->getTextureHandle());
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex2f(height, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex2f(height, width);
	glTexCoord2f(0.0f, 1.0f);	glVertex2f(0.0f, width);

	glEnd();
}

// Hàm hiển thị cho toàn bộ ứng dụng
void display(void)
{
	// update Hệ Mặt Trời
	time += timeSpeed;

	// Cập nhật lại toàn bộ hệ mặt trời
	solarSystem.updateStatus(time);

	// Cập nhật lại vị trí Camera
	if (controlsCamera.forward) camera.forwardCamera();
	if (controlsCamera.backward) camera.backwardCamera();
	if (controlsCamera.right) camera.rightCamera();
	if (controlsCamera.left) camera.leftCamera();
	if (controlsCamera.up) camera.upCamera();
	if (controlsCamera.down) camera.downCamera();

	// Cập nhật lại vị trí điểm nhìn Camera
	if (controlsPointVeiw.forward) camera.forwardPointView();
	if (controlsPointVeiw.backward) camera.backwardPointView();
	if (controlsPointVeiw.right) camera.rightPointView();
	if (controlsPointVeiw.left) camera.leftPointView();
	if (controlsPointVeiw.up) camera.upPointView();
	if (controlsPointVeiw.down) camera.downPointView();


	/////////////////////////////////////////////////////////////////////////////////////////
	// Vẽ không gian
	// Xóa màn hình
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	// Chọn phép hiếu phối cảnh
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);


	// Thiết lập camera tại ma trận modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.set(); 

	//Toàn bộ hệ mặt trời được đặt trong 1 hình hộp
	// Ta chỉ việc vẽ không gian vũ trụ
	glBindTexture(GL_TEXTURE_2D, galaxy->getTextureHandle());
	drawCube();


	//vị trí nguồn sáng tại tâm
	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Vẽ hệ Mặt Trời
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// Render hệ mặt trời
	if (showSolarSystem)
		solarSystem.render();

	// Render 1 hành tinh được chọn
	if (index != -1) {
		solarSystem.renderPlanet(index);
		//renderInformation(information[index]);
	}
	glDisable(GL_LIGHTING);

	// Render quỹ đạo các hành tinh
	if (showOrbits)
		solarSystem.renderOrbits();

	glDisable(GL_DEPTH_TEST);

	// Render hệ trục tọa độ
	if (drawOxyz)
		renderOxyz();

	// Thiết lập phép chiếu trực giao
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(60, (GLdouble)screenWidth, (GLdouble)screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);// đẻ load texture không bị mắt màu
	glLineWidth(1.0);

	// Render phần hướng dẫn sử dụng
	if (helpDialogue)
		renderInformation(500, 512, help);

	// Render bảng thông tin hành tin được chọn
	if (index != -1)
		renderInformation(630, 500, information[index]);

	// Render bảng thông tin toàn bộ hệ mặt trời
	if (isInfoSolarSystem)
		renderInformation(screenWidth, screenHeight, infoSolarSystem);

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; // giảm tốc độ xoay 1 nữa
		break;
	case '=':
		timeSpeed *= 2.0f; // tăng tốc độ xoay gấp đôi
		break;
	case 'h':
		helpDialogue = !helpDialogue; // hiện bảng hướng dẫn sử dụng
		break;
	case '[':
		planetSizeScale /= 1.2; // giảm tỉ lệ kích thước hành tinh 
		break;
	case ']':
		planetSizeScale *= 1.2; // tăng tỉ lệ kích thước hành tinh 
		break;
	case 'p':
		showOrbits = !showOrbits; // hiện quỹ đạo
		break;
	case 'r':
		planetSizeScale = distanceScale; // cho tỉ lệ kích thước = tỉ lệ khoảng cách
		break;
	case ',':
		camera.speedDown(); // giảm tốc độ camera
		break;
	case '.':
		camera.speedUp(); // tăng tốc độ camera
		break;
	case 'w':
		controlsCamera.forward = true; // camera đi thẳng về trước
		break;
	case 's':
		controlsCamera.backward = true; // camera lùi về sau
		break;
	case 'a':
		controlsCamera.left = true; // camera đi sang trái
		break;
	case 'd':
		controlsCamera.right = true; // camera đi sang phải
		break;
	case 'e':
		controlsCamera.up = true; // camera đi lên
		break;
	case 'q':
		controlsCamera.down = true; // camera đi xuống
		break;

	//Tương tự cho điểm nhìn
	case 'i':
		controlsPointVeiw.forward = true;
		break;
	case 'k':
		controlsPointVeiw.backward = true;
		break;
	case 'j':
		controlsPointVeiw.left = true;
		break;
	case 'l':
		controlsPointVeiw.right = true;
		break;
	case 'o':
		controlsPointVeiw.up = true;
		break;
	case 'u':
		controlsPointVeiw.down = true;
		break;

	// Hiện thông tin các hành tinh theo đánh số trước từ 0 đến 9
	case '0':
		index = 0;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '1':
		index = 1;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '2':
		index = 2;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '3':
		index = 3;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '4':
		index = 4;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '5':
		index = 5;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '6':
		index = 6;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '7':
		index = 7;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '8':
		index = 8;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;
	case '9':
		index = 9;
		showSolarSystem = false;
		showOrbits = false;
		isInfoSolarSystem = false;
		break;

	// Hiện hệ thống Mặt Trời ra
	case 'n':
		showSolarSystem = true;
		showOrbits = true;
		index = -1;
		isInfoSolarSystem = false;
		break;

	//Hiện thông tin của hệ thống Mặt Trời
	case 'f':
		isInfoSolarSystem = true;
		showSolarSystem = false;
		showOrbits =false;
		index = -1;
		break;

	case 'c':
		drawOxyz = !drawOxyz;

	default:
		break;
	}

}

void keyUp(unsigned char key, int x, int y)
{
	// Tắt các phím vừa nhấn ở trên
	switch (key)
	{
	case 'w':
		controlsCamera.forward = false;
		break;
	case 's':
		controlsCamera.backward = false;
		break;
	case 'a':
		controlsCamera.left = false;
		break;
	case 'd':
		controlsCamera.right = false;
		break;
	case 'e':
		controlsCamera.up = false;
		break;
	case 'q':
		controlsCamera.down = false;
		break;

	case 'i':
		controlsPointVeiw.forward = false;
		break;
	case 'k':
		controlsPointVeiw.backward = false;
		break;
	case 'j':
		controlsPointVeiw.left = false;
		break;
	case 'l':
		controlsPointVeiw.right = false;
		break;
	case 'o':
		controlsPointVeiw.up = false;
		break;
	case 'u':
		controlsPointVeiw.down = false;
		break;
	default:
		break;
	}
}

void reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char** argv)
{
	//Tạo kích thước của sổ openGL ban đầu, và tự động tương khích với full màn hình máy tính
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);


	init();

	//Các hàm tự cập nhật lại của glut khi có sự kiện bàn phím từ màn hình
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutMainLoop();
	return 0;
}

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