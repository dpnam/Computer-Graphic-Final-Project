#include "Program.h"

Program::Program() {}

Program::~Program() {}

void Program::timer(int)
{
	glutPostRedisplay(); // post for display func
						 //	glutTimerFunc(10, &this->timer, 0); // limit frame drawing to 100fps
}

void Program::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	// set up lighting
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matShininess[] = { 20.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// Load all image data
	help = new TGA("images/help.tga");
	galaxy = new TGA("images/stars.tga");
	moon = new TGA("images/moon.tga");

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

	// Add all the planets with accurate data. Distance measured in km, time measured in earth days.
	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureHandle()); // sun
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureHandle()); // mercury
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureHandle()); // venus
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle()); // earth
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureHandle()); // mars
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle()); // jupiter
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle()); // saturn
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); // uranus
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle()); // neptune
	solarSystem.addPlanet(5906380000, 90616, 6.39, 1137, pluto->getTextureHandle()); // pluto

	solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle()); // test moon for the earth

																				 // set up time
	time = 2.552f;
	timeSpeed = 0.1f;

	// reset controls
	controlsCamera.forward = false;
	controlsCamera.backward = false;
	controlsCamera.left = false;
	controlsCamera.right = false;
	controlsCamera.up = false;
	controlsCamera.down = false;
	timer(0);
}

void Program::drawCube()
{
	glBegin(GL_QUADS);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void Program::display()
{
	// update the logic and simulation
	time += timeSpeed;
	solarSystem.updateStatus(time);

	if (controlsCamera.forward) camera.forwardCamera();
	if (controlsCamera.backward) camera.backwardCamera();
	if (controlsCamera.right) camera.rightCamera();
	if (controlsCamera.left) camera.leftCamera();
	if (controlsCamera.up) camera.upCamera();
	if (controlsCamera.down) camera.downCamera();

	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	// set up the perspective matrix for rendering the 3d world
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Cập nhật Camera
	camera.set();

	//Toàn bộ hệ mặt trời được đặt trong 1 hình hộp
	// Ta chỉ việc vẽ không gian vũ trụ
	glBindTexture(GL_TEXTURE_2D, galaxy->getTextureHandle());
	drawCube();

	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// render the solar system
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	solarSystem.render();
	glDisable(GL_LIGHTING);

	// possibly render orbits
	if (showOrbits)
		solarSystem.renderOrbits();

	glDisable(GL_DEPTH_TEST);

	// set up ortho matrix for showing the UI (help dialogue)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, (GLdouble)screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw the help dialogue
	if (helpDialogue)
	{
		glBindTexture(GL_TEXTURE_2D, help->getTextureHandle());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(512.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(512.0f, 512.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(0.0f, 512.0f);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

void Program::keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; // half the rate of time passing
		break;
	case '=':
		timeSpeed *= 2.0f; // double the rate of time passing
		break;
	case 'h':
		helpDialogue = !helpDialogue; // toggle the dialogue
		break;
	case '[':
		planetSizeScale /= 1.2; // make planet scale smaller
		break;
	case ']':
		planetSizeScale *= 1.2; // make planet scale bigger
		break;
	case 'o':
		showOrbits = !showOrbits; // toggle show orbits
		break;
	case 'r':
		planetSizeScale = distanceScale;
		break;
	case ',':
		camera.speedDown(); // slow down camera
		break;
	case '.':
		camera.speedUp(); // speed up camera
		break;
		// these are all camera controls
	case 'w':
		controlsCamera.forward = true;
		break;
	case 's':
		controlsCamera.backward = true;
		break;
	case 'a':
		controlsCamera.left = true;
		break;
	case 'd':
		controlsCamera.right = true;
		break;
	default:
		break;
	}
}

void Program::keyUp(unsigned char key, int x, int y)
{
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
	default:
		break;
	}
}

void Program::reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Program::run()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 100);
	init();
	//glutDisplayFunc(&this->display);
	//glutReshapeFunc(&this->reshape);

	//glutKeyboardFunc(&this->keyDown);
	//glutKeyboardUpFunc(&this->keyUp);

	glutMainLoop();
}
