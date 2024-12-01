#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#pragma warning(disable:4996)
#pragma warning(disable:4805)
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

/// <summary>
/// TEXTURE DECLARATION
/// </summary>
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
/// <summary>
/// END OF TEXTURE
/// </summary>

float angleScreen = 0, headCylinderAngle = 0;
float angle = 0.0;
float angleRightHand1 = 0.0, angleLeftHand1 = 0.0, angleRightHand2 = 0.0, angleLeftHand2 = 0.0, angleRightHand3 = 0.0, angleLeftHand3 = 0.0;
float angleRightLeg1 = 0.0, angleRightLeg2 = 0.0, angleLeftLeg1 = 0.0, angleLeftLeg2 = 0.0, angleGun = 0.00, angleRotate = 0.0;
float angleHead = 0;
float moveX = 0.0, moveY = 0.0, moveZ = 0.0, camX = 0.0, camY = -2.5, camZ = 0.0, bulletX = 0, bulletY = 0, bulletZ = 0;
int walkCount = 0, ulti1Count = 0, ulti2Count = 0, bulletCount = 0;
boolean checkRightHand2 = true, checkLeftHand2 = true, checkRightHand3 = true, checkLeftHand3 = true;
boolean checkLeftLeg1 = true, checkRightLeg1 = true, checkLeftLeg2 = true, checkRightLeg2 = true;
boolean checkWalk = false, checkWeapon = false, checkWeapon1 = false, checkUlti1 = false, checkUlti2 = false, camRotateCW = false, camRotateACW = false, checkBullet = false;
boolean openHead = false;

//LIGHT DECLARATION
float x = 0, y = 1, z = 0.5;
float amb[] = { 1, 1, 1, 1 };
float pos[] = { x, y, z };
float diff[] = { 1, 1, 1, 1 };
boolean openLight = false;

//Perspective
float isPerspective = true;

//moving range
void movingXYZ(float range) {

	if (angleRotate == 180.0) {//Walk to Back

		moveZ -= range;

	}
	if (angleRotate == 270.0) {//Walk to Left

		moveX -= range;

	}
	if (angleRotate == 0.0) {//Walk to Front

		moveZ += range;

	}
	if (angleRotate == 90.0) {//Walk to Right

		moveX += range;

	}

}

//reset angle
void resetAngle() {

	angleRightHand1 = 0.0;
	angleLeftHand1 = 0.0;
	angleRightHand2 = 0.0;
	angleLeftHand2 = 0.0;
	angleRightHand3 = 0.0;
	angleLeftHand3 = 0.0;
	angleRightLeg1 = 0.0;
	angleRightLeg2 = 0.0;
	angleLeftLeg1 = 0.0;
	angleLeftLeg2 = 0.0;
	moveX = 0.0;
	moveY = 0.0;
	moveZ = 0.0;
	camX = 0.0;
	camY = -2.5;
	camZ = 0.0;
	checkWalk = false;
	checkWeapon = false;
	checkWeapon1 = false;
	checkUlti1 = false;
	checkUlti2 = false;
	camRotateCW = false;
	camRotateACW = false;
	checkBullet = false;
	angleHead = 0;
	openHead = false;
	angleScreen = 0;
	x = 0;
	y = 1;
	z = 0.5;
	openLight = false;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x34) {//Light to left:4
			x -= 0.1;
		}
		else if (wParam == 0x35) {//Light to right:5
			x += 0.1;
		}
		else if (wParam == 0x36) {//Light to up:6
			y += 0.1;
		}
		else if (wParam == 0x37) {//Light to doen:7
			y -= 0.1;
		}
		else if (wParam == 0x38) {//Light to far:8
			z -= 0.1;
		}
		else if (wParam == 0x39) {//Light to near:9
			z += 0.1;
		}
		else if (wParam == VK_SHIFT) {//Change view: Shift
			if (isPerspective) {
				isPerspective = false;
			}
			else {
				isPerspective = true;
			}
		}
		else if (wParam == 0x46) {//Left Upper Arm: F

			angleRightHand1 += 10;

		}
		else if (wParam == 0x4A) {//Right Upper Arm: J

			angleLeftHand1 += 10;

		}
		else if (wParam == 0x47) {//Left Lower Arm: G

			if (checkRightHand2) {
				angleRightHand2 += 10;
			}
			else {
				angleRightHand2 -= 10;
			}
			if (angleRightHand2 >= 100.0) {
				checkRightHand2 = false;
			}
			else if (angleRightHand2 <= 00.0) {
				checkRightHand2 = true;
			}

		}
		else if (wParam == 0x4B) {//Right Lower Arm: K

			if (checkLeftHand2) {
				angleLeftHand2 += 10;
			}
			else {
				angleLeftHand2 -= 10;
			}
			if (angleLeftHand2 >= 100.0) {
				checkLeftHand2 = false;
			}
			else if (angleLeftHand2 <= 00.0) {
				checkLeftHand2 = true;
			}

		}
		else if (wParam == 0x4C) {//Right Arms: L

			if (checkLeftHand3) {
				angleLeftHand3 += 10;
			}
			else {
				angleLeftHand3 -= 10;
			}
			if (angleLeftHand3 >= 70.0) {
				checkLeftHand3 = false;
			}
			else if (angleLeftHand3 <= 00.0) {
				checkLeftHand3 = true;
			}

		}
		else if (wParam == 0x48) {//Left Arms: H

			if (checkRightHand3) {
				angleRightHand3 += 10;
			}
			else {
				angleRightHand3 -= 10;
			}
			if (angleRightHand3 >= 70.0) {
				checkRightHand3 = false;
			}
			else if (angleRightHand3 <= 00.0) {
				checkRightHand3 = true;
			}

		}
		else if (wParam == 0x55) {//Left Upper Leg: U

			if (checkLeftLeg1) {
				angleLeftLeg1 += 10;
			}
			else {
				angleLeftLeg1 -= 10;
			}
			if (angleLeftLeg1 >= 60.0) {
				checkLeftLeg1 = false;
			}
			else if (angleLeftLeg1 <= -60.0) {
				checkLeftLeg1 = true;
			}

		}
		else if (wParam == 0x4F) {//Right Upper Leg: O

			if (checkRightLeg1) {
				angleRightLeg1 += 10;
			}
			else {
				angleRightLeg1 -= 10;
			}
			if (angleRightLeg1 >= 60.0) {
				checkRightLeg1 = false;
			}
			else if (angleRightLeg1 <= -60.0) {
				checkRightLeg1 = true;
			}

		}
		else if (wParam == 0x49) {//Left Lower Leg: I

			if (checkLeftLeg2) {
				angleLeftLeg2 += 10;
			}
			else {
				angleLeftLeg2 -= 10;
			}
			if (angleLeftLeg2 >= 10.0) {
				checkLeftLeg2 = false;
			}
			else if (angleLeftLeg2 <= -60.0) {
				checkLeftLeg2 = true;
			}

		}
		else if (wParam == 0x50) {//Right Lower Leg: P

			if (checkRightLeg2) {
				angleRightLeg2 += 10;
			}
			else {
				angleRightLeg2 -= 10;
			}
			if (angleRightLeg2 >= 10.0) {
				checkRightLeg2 = false;
			}
			else if (angleRightLeg2 <= -60.0) {
				checkRightLeg2 = true;
			}

		}
		else if (wParam == 0x30) {//Open Head: 0
			if (openHead) {
				openHead = false;
			}
			else {
				openHead = true;
			}
		}
		else if (wParam == 0x31) {//Walk: 1

			moveY = 0.0;
			angleLeftHand3 = 0.0;
			angleRightHand3 = 0.0;
			if (walkCount == 0) {

				//hand
				angleLeftHand1 = -5;
				angleLeftHand2 = 5;
				angleRightHand1 = 5;
				angleRightHand2 = 5;
				//leg
				angleLeftLeg1 = 0;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 10;
				angleRightLeg2 = -20;

			}
			else if (walkCount == 1) {

				//hand
				angleLeftHand1 = -15;
				angleLeftHand2 = 15;
				angleRightHand1 = 15;
				angleRightHand2 = 15;
				//leg
				angleLeftLeg1 = -5;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 20;
				angleRightLeg2 = -40;

			}
			else if (walkCount == 2) {

				//hand
				angleLeftHand1 = -25;
				angleLeftHand2 = 30;
				angleRightHand1 = 25;
				angleRightHand2 = 25;
				//leg
				angleLeftLeg1 = -10;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 30;
				angleRightLeg2 = -50;

			}
			else if (walkCount == 3) {

				//hand
				angleLeftHand1 = -15;
				angleLeftHand2 = 15;
				angleRightHand1 = 15;
				angleRightHand2 = 15;
				//leg
				angleLeftLeg1 = -15;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 20;
				angleRightLeg2 = -20;

			}
			else if (walkCount == 4) {

				//hand
				angleLeftHand1 = -5;
				angleLeftHand2 = 5;
				angleRightHand1 = 5;
				angleRightHand2 = 5;
				//leg
				angleLeftLeg1 = -5;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 10;
				angleRightLeg2 = -10;

			}
			else if (walkCount == 5) {

				movingXYZ(0.1);
				//hand
				angleLeftHand1 = 0;
				angleLeftHand2 = 0;
				angleRightHand1 = 0;
				angleRightHand2 = 0;
				//leg
				angleLeftLeg1 = 0;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 0;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 6) {

				//hand
				angleLeftHand1 = 5;
				angleLeftHand2 = 5;
				angleRightHand1 = -5;
				angleRightHand2 = 5;
				//leg
				angleLeftLeg1 = 10;
				angleLeftLeg2 = -20;
				angleRightLeg1 = 0;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 7) {

				//hand
				angleLeftHand1 = 15;
				angleLeftHand2 = 15;
				angleRightHand1 = -15;
				angleRightHand2 = 15;
				//leg
				angleLeftLeg1 = 20;
				angleLeftLeg2 = -40;
				angleRightLeg1 = -5;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 8) {

				//hand
				angleLeftHand1 = 25;
				angleLeftHand2 = 25;
				angleRightHand1 = -25;
				angleRightHand2 = 25;
				//leg
				angleLeftLeg1 = 30;
				angleLeftLeg2 = -50;
				angleRightLeg1 = -10;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 9) {

				//hand
				angleLeftHand1 = 15;
				angleLeftHand2 = 15;
				angleRightHand1 = -15;
				angleRightHand2 = 15;
				//leg
				angleLeftLeg1 = 20;
				angleLeftLeg2 = -20;
				angleRightLeg1 = -15;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 10) {

				//hand
				angleLeftHand1 = 5;
				angleLeftHand2 = 5;
				angleRightHand1 = -5;
				angleRightHand2 = 5;
				//leg
				angleLeftLeg1 = 10;
				angleLeftLeg2 = -10;
				angleRightLeg1 = -5;
				angleRightLeg2 = 0;

			}
			else if (walkCount == 11) {

				movingXYZ(0.1);
				//hand
				angleLeftHand1 = 0;
				angleLeftHand2 = 0;
				angleRightHand1 = 0;
				angleRightHand2 = 0;
				//leg
				angleLeftLeg1 = 0;
				angleLeftLeg2 = 0;
				angleRightLeg1 = 0;
				angleRightLeg2 = 0;

			}

			walkCount++;
			if (walkCount > 11) {
				walkCount = 0;
			}

		}
		else if (wParam == 0x32) {//Ulti 1 Shoryuken: 2

			checkUlti1 = true;

		}
		else if (wParam == 0x33) {//Ulti 2 Hurricane Kick: 3

			checkUlti2 = true;

		}
		else if (wParam == 0x43) {//Melee Weapon: C

			if (checkWeapon1 == true) {
				checkWeapon1 = false;
				angleLeftHand1 = 0;
				angleLeftHand2 = 0;
				angleLeftHand3 = 0;
				angleRightHand1 = 0;
				angleRightHand2 = 0;
				angleRightHand3 = 0;
			}

			if (checkWeapon == true) {
				checkWeapon = false;
				angleLeftHand1 = 0;
				angleLeftHand2 = 0;
				angleLeftHand3 = 0;
				angleRightHand1 = 0;
				angleRightHand2 = 0;
				angleRightHand3 = 0;
			}
			else if (checkWeapon == false) {
				checkWeapon = true;
				angleLeftHand1 = 30;
				angleLeftHand2 = 60;
				angleLeftHand3 = 15;
				angleRightHand1 = 40;
				angleRightHand2 = 60;
				angleRightHand3 = 10;
			}

		}
		else if (wParam == 0x56) {//Ranged Weapon: V

			if (checkWeapon == true) {
				checkWeapon = false;
				angleLeftHand1 = 0;
				angleLeftHand2 = 0;
				angleLeftHand3 = 0;
				angleRightHand1 = 0;
				angleRightHand2 = 0;
				angleRightHand3 = 0;
			}

			if (checkWeapon1 == true) {
				checkWeapon1 = false;
				angleLeftHand1 = 0;
				angleRightHand1 = 0;
				angleLeftHand2 = 0;
				angleLeftHand3 = 0;
				angleRightHand2 = 0;
				angleRightHand3 = 0;
			}
			else if (checkWeapon1 == false) {
				checkWeapon1 = true;
				angleLeftHand1 = 90;
				angleRightHand1 = 90;
				angleLeftHand2 = 0;
				angleLeftHand3 = 0;
				angleRightHand2 = 0;
				angleRightHand3 = 0;
			}

		}
		else if (wParam == 0x57) {//Rotate to Back: W

			if (angleRotate == 180.0) {
				checkWalk = true;
			}
			else {
				angleRotate = 180.0;
			}

		}
		else if (wParam == 0x41) {//Rotate to Left: A

			if (angleRotate == 270.0) {
				checkWalk = true;
			}
			else {
				angleRotate = 270.0;
			}

		}
		else if (wParam == 0x53) {//Rotate to Front: S

			if (angleRotate == 0.0) {
				checkWalk = true;
			}
			else {
				angleRotate = 0.0;
			}

		}
		else if (wParam == 0x44) {//Rotate to Right: D

			if (angleRotate == 90.0) {
				checkWalk = true;
			}
			else {
				angleRotate = 90.0;
			}

		}
		else if (wParam == VK_SPACE) {
			if (openLight) {
				openLight = false;
			}
			else {
				openLight = true;
			}
		}
		else if (wParam == VK_UP) {//Move camera up: Up

			camY -= 0.1;

		}
		else if (wParam == VK_DOWN) {//Move camera down: Down

			camY += 0.1;

		}
		else if (wParam == VK_LEFT) {//Move camera to left: Left

			camX += 0.1;

		}
		else if (wParam == VK_RIGHT) {//Move camera to right: Right

			camX -= 0.1;

		}
		else if (wParam == 0x51) {//Zoom camera in: Q

			camZ += 0.1;

		}
		else if (wParam == 0x45) {//Zoom camera out: E

			camZ -= 0.1;

		}
		else if (wParam == VK_OEM_COMMA) {//Rotate camera clockwise: <
			if (camRotateACW) {
				camRotateACW = false;
			}
			if (camRotateCW) {
				camRotateCW = false;
			}
			else {
				camRotateCW = true;
			}
		}
		else if (wParam == VK_OEM_PERIOD) {//Rotate camera clockwise: >
			if (camRotateCW) {
				camRotateCW = false;
			}
			if (camRotateACW) {
				camRotateACW = false;
			}
			else {
				camRotateACW = true;
			}
		}
		else if (wParam == VK_RETURN) {//Reset everything: Enter
			resetAngle();
		}
		else if (wParam == 0x42) {//Shoot bullet: B

			if (checkWeapon1) {

				if (checkBullet) {
					checkBullet = false;
				}
				else {
					checkBullet = true;
				}

			}

		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawFilledCircle(float x1, float y1, float radius) {
	float x2, y2;
	float angle;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 0);

	for (angle = 0.0f; angle < 3.142f * 2; angle += 0.001f) {
		x2 = x1 + sinf(angle) * radius;
		y2 = y1 + cosf(angle) * radius;
		glVertex3f(x2, y2, 0);
	}
	glEnd();
}

void drawHalfCircle(float x1, float y1, float radius) {
	float angle;

	glBegin(GL_POINTS);

	for (angle = 3.142f / 2; angle < 3.142f * 1.5; angle += 0.001f) {
		glVertex2f(x1 + (sinf(angle) * radius), y1 + (cosf(angle) * radius));
	}
	glEnd();
}

void drawFilledRectangle(float x1, float y1, float x2, float y2) {
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
}

void drawTextureCube(float x1, float y1, float z1, float x2, float y2, float z2) {
	// Face 1 - front
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y1, z2);

	// Face 2 - back
	glTexCoord2f(0, 0);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y2, z2);

	// Face 3 - left
	glTexCoord2f(0, 0);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(1, 0);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y2, z2);

	// Face 4 - right
	glTexCoord2f(0, 0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(0, 1);
	glVertex3f(x2, y2, z2);

	// Face 5 - down
	glTexCoord2f(0, 0);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(1, 1);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y2, z2);

	// Face 6 - up
	glTexCoord2f(0, 0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(1, 1);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y2, z1);
	glEnd();
}

void drawCube(float x1, float y1, float z1, float x2, float y2, float z2) {
	// Face 1 - front
	glBegin(GL_QUADS);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);

	// Face 2 - back
	glVertex3f(x1, y2, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);

	// Face 3 - left
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);

	// Face 4 - right
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y2, z2);

	// Face 5 - down
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);

	// Face 6 - up
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y2, z1);
	glEnd();
}

void drawLineCube(float x1, float y1, float z1, float x2, float y2, float z2) {

	glLineWidth(3);

	// Face 1 - front
	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glEnd();

	// Face 2 - back
	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y2, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);
	glEnd();

	// Face 3 - left
	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glEnd();

	// Face 4 - right
	glBegin(GL_LINE_LOOP);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y2, z2);
	glEnd();

	// Face 5 - down
	glBegin(GL_LINE_LOOP);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y2, z2);
	glEnd();

	// Face 6 - up
	glBegin(GL_LINE_LOOP);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y2, z1);
	glEnd();
}

void drawSword() {

	glPushMatrix();
	glScalef(0.85, 1.0, 0.85);

	glPushMatrix();

	glScalef(1.0, 1.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(-0.2, 0.5, 0.1, 0.2, -0.5, -0.1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(-0.2, 0.5, 0.1, 0.2, -0.5, -0.1);

	glPopMatrix();


	glPushMatrix();

	glTranslatef(0.0, -0.75, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(-0.145, 0.145, 0.1, 0.145, -0.145, -0.1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(-0.145, 0.145, 0.1, 0.145, -0.145, -0.1);

	glPopMatrix();

	glPopMatrix();

}

void drawBullet() {
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.2);
	glTranslatef(bulletX, bulletY, bulletZ);
	glRotatef(angleGun, 0, 0, 1);

	glPushMatrix();

	glTranslatef(0.0, 0.0, -0.2);
	//main muzzle
	GLUquadricObj* sphereB = NULL;
	sphereB = gluNewQuadric();
	gluQuadricTexture(sphereB, true);
	//gluQuadricDrawStyle(sphereB, GLU_FILL);
	gluSphere(sphereB, 0.075, 10, 10);
	gluDeleteQuadric(sphereB);


	GLUquadricObj* sphereBL = NULL;
	sphereBL = gluNewQuadric();
	//gluQuadricTexture(sphereBL, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL, GLU_LINE);
	gluSphere(sphereBL, 0.075, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.15, 0.0, 0.0);
	GLUquadricObj* sphereB1 = NULL;
	sphereB1 = gluNewQuadric();
	gluQuadricTexture(sphereB1, true);
	//gluQuadricDrawStyle(sphereB1, GLU_FILL);
	gluSphere(sphereB1, 0.045, 10, 10);
	gluDeleteQuadric(sphereB1);

	GLUquadricObj* sphereBL1 = NULL;
	sphereBL1 = gluNewQuadric();
	//gluQuadricTexture(sphereBL1, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL1, GLU_LINE);
	gluSphere(sphereBL1, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL1);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.15, 0.0, -0.24);
	GLUquadricObj* sphereB2 = NULL;
	sphereB2 = gluNewQuadric();
	gluQuadricTexture(sphereB2, true);
	//gluQuadricDrawStyle(sphereB2, GLU_FILL);
	gluSphere(sphereB2, 0.045, 10, 10);
	gluDeleteQuadric(sphereB2);

	GLUquadricObj* sphereBL2 = NULL;
	sphereBL2 = gluNewQuadric();
	//gluQuadricTexture(sphereBL2, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL2, GLU_LINE);
	gluSphere(sphereBL2, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL2);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, 0.15, -0.36);
	GLUquadricObj* sphereB3 = NULL;
	sphereB3 = gluNewQuadric();
	gluQuadricTexture(sphereB3, true);
	//gluQuadricDrawStyle(sphereB3, GLU_FILL);
	gluSphere(sphereB3, 0.045, 10, 10);
	gluDeleteQuadric(sphereB3);

	GLUquadricObj* sphereBL3 = NULL;
	sphereBL3 = gluNewQuadric();
	//gluQuadricTexture(sphereBL3, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL3, GLU_LINE);
	gluSphere(sphereBL3, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL3);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, -0.15, -0.12);
	GLUquadricObj* sphereB4 = NULL;
	sphereB4 = gluNewQuadric();
	gluQuadricTexture(sphereB3, true);
	//gluQuadricDrawStyle(sphereB4, GLU_FILL);
	gluSphere(sphereB4, 0.045, 10, 10);
	gluDeleteQuadric(sphereB4);

	GLUquadricObj* sphereBL4 = NULL;
	sphereBL4 = gluNewQuadric();
	//gluQuadricTexture(sphereBL4, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL4, GLU_LINE);
	gluSphere(sphereBL4, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL4);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, 0.115, -0.42);
	GLUquadricObj* sphereB5 = NULL;
	sphereB5 = gluNewQuadric();
	gluQuadricTexture(sphereB5, true);
	//gluQuadricDrawStyle(sphereB5, GLU_FILL);
	gluSphere(sphereB5, 0.045, 10, 10);
	gluDeleteQuadric(sphereB5);

	GLUquadricObj* sphereBL5 = NULL;
	sphereBL5 = gluNewQuadric();
	//gluQuadricTexture(sphereBL5, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL5, GLU_LINE);
	gluSphere(sphereBL5, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL5);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, 0.115, -0.30);
	GLUquadricObj* sphereB6 = NULL;
	sphereB6 = gluNewQuadric();
	gluQuadricTexture(sphereB6, true);
	//gluQuadricDrawStyle(sphereB6, GLU_FILL);
	gluSphere(sphereB6, 0.045, 10, 10);
	gluDeleteQuadric(sphereB6);

	GLUquadricObj* sphereBL6 = NULL;
	sphereBL6 = gluNewQuadric();
	//gluQuadricTexture(sphereBL6, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL6, GLU_LINE);
	gluSphere(sphereBL6, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL6);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, -0.115, -0.06);
	GLUquadricObj* sphereB7 = NULL;
	sphereB7 = gluNewQuadric();
	gluQuadricTexture(sphereB7, true);
	//gluQuadricDrawStyle(sphereB7, GLU_FILL);
	gluSphere(sphereB7, 0.045, 10, 10);
	gluDeleteQuadric(sphereB7);

	GLUquadricObj* sphereBL7 = NULL;
	sphereBL7 = gluNewQuadric();
	//gluQuadricTexture(sphereBL7, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL7, GLU_LINE);
	gluSphere(sphereBL7, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL7);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, -0.115, -0.18);
	GLUquadricObj* sphereB8 = NULL;
	sphereB8 = gluNewQuadric();
	gluQuadricTexture(sphereB8, true);
	//gluQuadricDrawStyle(sphereB8, GLU_FILL);
	gluSphere(sphereB8, 0.045, 10, 10);
	gluDeleteQuadric(sphereB8);

	GLUquadricObj* sphereBL8 = NULL;
	sphereBL8 = gluNewQuadric();
	//gluQuadricTexture(sphereBL8, true);
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(sphereBL8, GLU_LINE);
	gluSphere(sphereBL8, 0.045, 10, 10);
	glColor3f(1, 1, 1);
	gluDeleteQuadric(sphereBL8);

	glPopMatrix();

	glPopMatrix();

}

void drawGunLine() {



	glPushMatrix();

	//Handler 1
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.5);
	GLUquadricObj* cylinderGL9 = NULL;
	cylinderGL9 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL9, true);
	gluQuadricDrawStyle(cylinderGL9, GLU_LINE);
	gluCylinder(cylinderGL9, 0.225, 0.225, 0.1, 5, 5);
	gluDeleteQuadric(cylinderGL9);

	drawFilledCircle(0.0, 0.0, 0.225);
	glTranslatef(0.0, 0.0, 0.1);
	drawFilledCircle(0.0, 0.0, 0.225);

	glPopMatrix();

	//Handler 2
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.2);
	GLUquadricObj* cylinderGL10 = NULL;
	cylinderGL10 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL10, true);
	gluQuadricDrawStyle(cylinderGL10, GLU_LINE);
	gluCylinder(cylinderGL10, 0.225, 0.225, 0.1, 5, 5);
	gluDeleteQuadric(cylinderGL10);

	glPopMatrix();

	//Handler 3
	glPushMatrix();

	glTranslatef(0.0, 0.0, -0.1);
	GLUquadricObj* cylinderGL11 = NULL;
	cylinderGL11 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL11, true);
	gluQuadricDrawStyle(cylinderGL11, GLU_LINE);
	gluCylinder(cylinderGL11, 0.225, 0.225, 0.1, 5, 5);
	gluDeleteQuadric(cylinderGL11);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.225, 0.0, 0.0);
	drawLineCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.225, 0.0, 0.0);
	drawLineCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.225, 0.0);
	glRotatef(90, 0, 0, 1);
	drawLineCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.225, 0.0);
	glRotatef(90, 0, 0, 1);
	drawLineCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPopMatrix();

	//small muzzle
	glPushMatrix();

	glTranslatef(0.0, 0.0, -0.2);
	glRotatef(angleGun, 0, 0, 1);

	glPushMatrix();

	//main muzzle
	GLUquadricObj* cylinderGL = NULL;
	cylinderGL = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL, true);
	gluQuadricDrawStyle(cylinderGL, GLU_LINE);
	gluCylinder(cylinderGL, 0.075, 0.075, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.15, 0.0, 0.0);
	GLUquadricObj* cylinderGL1 = NULL;
	cylinderGL1 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL1, true);
	gluQuadricDrawStyle(cylinderGL1, GLU_LINE);
	gluCylinder(cylinderGL1, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL1);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.15, 0.0, 0.0);
	GLUquadricObj* cylinderGL2 = NULL;
	cylinderGL2 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL2, true);
	gluQuadricDrawStyle(cylinderGL2, GLU_LINE);
	gluCylinder(cylinderGL2, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL2);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, 0.15, 0.0);
	GLUquadricObj* cylinderGL3 = NULL;
	cylinderGL3 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL3, true);
	gluQuadricDrawStyle(cylinderGL3, GLU_LINE);
	gluCylinder(cylinderGL3, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL3);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, -0.15, 0.0);
	GLUquadricObj* cylinderGL4 = NULL;
	cylinderGL4 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL4, true);
	gluQuadricDrawStyle(cylinderGL4, GLU_LINE);
	gluCylinder(cylinderGL4, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL4);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, 0.115, 0.0);
	GLUquadricObj* cylinderGL5 = NULL;
	cylinderGL5 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL5, true);
	gluQuadricDrawStyle(cylinderGL5, GLU_LINE);
	gluCylinder(cylinderGL5, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL5);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, 0.115, 0.0);
	GLUquadricObj* cylinderGL6 = NULL;
	cylinderGL6 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL6, true);
	gluQuadricDrawStyle(cylinderGL6, GLU_LINE);
	gluCylinder(cylinderGL6, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL6);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, -0.115, 0.0);
	GLUquadricObj* cylinderGL7 = NULL;
	cylinderGL7 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL7, true);
	gluQuadricDrawStyle(cylinderGL7, GLU_LINE);
	gluCylinder(cylinderGL7, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL7);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, -0.115, 0.0);
	GLUquadricObj* cylinderGL8 = NULL;
	cylinderGL8 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	//gluQuadricTexture(cylinderGL8, true);
	gluQuadricDrawStyle(cylinderGL8, GLU_LINE);
	gluCylinder(cylinderGL8, 0.045, 0.045, 0.7, 10, 10);
	gluDeleteQuadric(cylinderGL8);

	glPopMatrix();

	glPopMatrix();



}

void drawGun() {

	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();

	//Handler 1
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.5);
	GLUquadricObj* cylinderG9 = NULL;
	cylinderG9 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG9, true);
	//gluQuadricDrawStyle(cylinderG9, GLU_FILL);
	gluCylinder(cylinderG9, 0.225, 0.225, 0.1, 20, 20);
	gluDeleteQuadric(cylinderG9);

	drawFilledCircle(0.0, 0.0, 0.225);
	glTranslatef(0.0, 0.0, 0.1);
	drawFilledCircle(0.0, 0.0, 0.225);

	glPopMatrix();

	//Handler 2
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.2);
	GLUquadricObj* cylinderG10 = NULL;
	cylinderG10 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG10, true);
	//gluQuadricDrawStyle(cylinderG9, GLU_FILL);
	gluCylinder(cylinderG10, 0.225, 0.225, 0.1, 20, 20);
	gluDeleteQuadric(cylinderG10);

	glPopMatrix();

	//Handler 3
	glPushMatrix();

	glTranslatef(0.0, 0.0, -0.1);
	GLUquadricObj* cylinderG11 = NULL;
	cylinderG11 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG11, true);
	//gluQuadricDrawStyle(cylinderG11, GLU_FILL);
	gluCylinder(cylinderG11, 0.225, 0.225, 0.1, 20, 20);
	gluDeleteQuadric(cylinderG11);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.225, 0.0, 0.0);
	drawTextureCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.225, 0.0, 0.0);
	drawTextureCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.225, 0.0);
	glRotatef(90, 0, 0, 1);
	drawTextureCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.225, 0.0);
	glRotatef(90, 0, 0, 1);
	drawTextureCube(-0.01, 0.05, 0.6, 0.01, -0.05, -0.1);
	glPopMatrix();

	glPopMatrix();

	//small muzzle
	glPushMatrix();

	glTranslatef(0.0, 0.0, -0.2);
	glRotatef(angleGun, 0, 0, 1);

	glPushMatrix();

	//main muzzle
	GLUquadricObj* cylinderG = NULL;
	cylinderG = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG, true);
	//gluQuadricDrawStyle(cylinderG, GLU_FILL);
	gluCylinder(cylinderG, 0.075, 0.075, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.15, 0.0, 0.0);
	GLUquadricObj* cylinderG1 = NULL;
	cylinderG1 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG1, true);
	//gluQuadricDrawStyle(cylinderG1, GLU_FILL);
	gluCylinder(cylinderG1, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG1);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.15, 0.0, 0.0);
	GLUquadricObj* cylinderG2 = NULL;
	cylinderG2 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG2, true);
	//gluQuadricDrawStyle(cylinderG2, GLU_FILL);
	gluCylinder(cylinderG2, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG2);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, 0.15, 0.0);
	GLUquadricObj* cylinderG3 = NULL;
	cylinderG3 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG3, true);
	//gluQuadricDrawStyle(cylinderG3, GLU_FILL);
	gluCylinder(cylinderG3, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG3);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, -0.15, 0.0);
	GLUquadricObj* cylinderG4 = NULL;
	cylinderG4 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG4, true);
	//gluQuadricDrawStyle(cylinderG4, GLU_FILL);
	gluCylinder(cylinderG4, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG4);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, 0.115, 0.0);
	GLUquadricObj* cylinderG5 = NULL;
	cylinderG5 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG5, true);
	//gluQuadricDrawStyle(cylinderG5, GLU_FILL);
	gluCylinder(cylinderG5, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG5);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, 0.115, 0.0);
	GLUquadricObj* cylinderG6 = NULL;
	cylinderG6 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG6, true);
	//gluQuadricDrawStyle(cylinderG6, GLU_FILL);
	gluCylinder(cylinderG6, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG6);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.115, -0.115, 0.0);
	GLUquadricObj* cylinderG7 = NULL;
	cylinderG7 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG7, true);
	//gluQuadricDrawStyle(cylinderG7, GLU_FILL);
	gluCylinder(cylinderG7, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG7);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.115, -0.115, 0.0);
	GLUquadricObj* cylinderG8 = NULL;
	cylinderG8 = gluNewQuadric();
	//glColor3f(0.0, 0.0, 0.0);
	gluQuadricTexture(cylinderG8, true);
	//gluQuadricDrawStyle(cylinderG8, GLU_FILL);
	gluCylinder(cylinderG8, 0.045, 0.045, 0.7, 20, 20);
	gluDeleteQuadric(cylinderG8);

	glPopMatrix();

	glPopMatrix();

	if (checkBullet) {
		drawBullet();
	}

}

void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 20, stackNo = 20;
	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{

		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawStickMan() {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glPushMatrix();
	glTranslatef(0, 0.07, 0);
	gluSphere(sphere, 0.01, 50, 50);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(0, 0.06, 0);
	glVertex3f(0, 0.02, 0);

	glVertex3f(0, 0.06, 0);
	glVertex3f(-0.02, 0.03, 0);

	glVertex3f(0, 0.06, 0);
	glVertex3f(0.02, 0.03, 0);

	glVertex3f(0, 0.02, 0);
	glVertex3f(-0.02, 0, 0);

	glVertex3f(0, 0.02, 0);
	glVertex3f(0.02, 0, 0);
	glEnd();
}

void drawLineHead() {


	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0, 0, -0.3);
	glRotatef(-angleHead, 1, 0, 0);
	glTranslatef(0, 0, 0.3);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.2, 0.2, 0.3, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.2, 0.3, 0.15, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0.125);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, -0.125);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.3, 0.1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0.125);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, -0.125);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();

	
	glPopMatrix();

	//
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 0.1, 0.1);
	glVertex3f(0.15, 0.05, 0.1);
	glVertex3f(0.08, 0.05, 0.15);
	glVertex3f(0.08, 0.1, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, 0.1, 0.15);
	glVertex3f(0.08, 0.05, 0.15);
	glVertex3f(0.02, 0.05, 0.15);
	glVertex3f(0.02, 0.1, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.1, 0.15);
	glVertex3f(0.02, 0.05, 0.15);
	glVertex3f(0.02, 0.05, 0.1);
	glVertex3f(0.02, 0.1, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.1, 0.1);
	glVertex3f(0.02, 0.05, 0.1);
	glVertex3f(0.15, 0.05, 0.1);
	glVertex3f(0.15, 0.1, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 0.1, 0.1);
	glVertex3f(0.08, 0.1, 0.15);
	glVertex3f(0.02, 0.1, 0.15);
	glVertex3f(0.02, 0.1, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.1, 0.1);
	glVertex3f(-0.15, 0.05, 0.1);
	glVertex3f(-0.08, 0.05, 0.15);
	glVertex3f(-0.08, 0.1, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0.1, 0.15);
	glVertex3f(-0.08, 0.05, 0.15);
	glVertex3f(-0.02, 0.05, 0.15);
	glVertex3f(-0.02, 0.1, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.1, 0.15);
	glVertex3f(-0.02, 0.05, 0.15);
	glVertex3f(-0.02, 0.05, 0.1);
	glVertex3f(-0.02, 0.1, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.1, 0.1);
	glVertex3f(-0.02, 0.05, 0.1);
	glVertex3f(-0.15, 0.05, 0.1);
	glVertex3f(-0.15, 0.1, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.1, 0.1);
	glVertex3f(-0.08, 0.1, 0.15);
	glVertex3f(-0.02, 0.1, 0.15);
	glVertex3f(-0.02, 0.1, 0.1);
	glEnd();
	//

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.05, 0.33);
	glVertex3f(0.2, 0.05, 0.33);
	glVertex3f(0.38, 0.05, 0.15);
	glVertex3f(0.4, 0.05, 0);
	glVertex3f(0.38, 0.05, -0.15);
	glVertex3f(0.2, 0.05, -0.33);
	glVertex3f(0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.05, 0.33);
	glVertex3f(-0.2, 0.05, 0.33);
	glVertex3f(-0.38, 0.05, 0.15);
	glVertex3f(-0.4, 0.05, 0);
	glVertex3f(-0.38, 0.05, -0.15);
	glVertex3f(-0.2, 0.05, -0.33);
	glVertex3f(-0.02, 0.05, -0.33);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.05, 0.33);
	glVertex3f(0.02, -0.1, 0.38);
	glVertex3f(0.2, -0.15, 0.38);
	glVertex3f(0.2, 0.05, 0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.05, 0.33);
	glVertex3f(-0.02, -0.1, 0.38);
	glVertex3f(-0.2, -0.15, 0.38);
	glVertex3f(-0.2, 0.05, 0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.05, 0.33);
	glVertex3f(0.2, -0.15, 0.38);
	glVertex3f(0.38, -0.1, 0.2);
	glVertex3f(0.38, 0.05, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, 0.05, 0.33);
	glVertex3f(-0.2, -0.15, 0.38);
	glVertex3f(-0.38, -0.1, 0.2);
	glVertex3f(-0.38, 0.05, 0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.05, -0.33);
	glVertex3f(0.02, -0.13, -0.38);
	glVertex3f(0.2, -0.15, -0.38);
	glVertex3f(0.2, 0.05, -0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.05, -0.33);
	glVertex3f(0.2, -0.15, -0.38);
	glVertex3f(0.38, -0.1, -0.2);
	glVertex3f(0.38, 0.05, -0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.05, -0.33);
	glVertex3f(-0.02, -0.13, -0.38);
	glVertex3f(-0.2, -0.15, -0.38);
	glVertex3f(-0.2, 0.05, -0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, 0.05, -0.33);
	glVertex3f(-0.2, -0.15, -0.38);
	glVertex3f(-0.38, -0.1, -0.2);
	glVertex3f(-0.38, 0.05, -0.15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.05, 0.33);
	glVertex3f(0.02, -0.1, 0.38);
	glVertex3f(0.02, -0.13, -0.38);
	glVertex3f(0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.05, 0.33);
	glVertex3f(-0.02, -0.1, 0.38);
	glVertex3f(-0.02, -0.13, -0.38);
	glVertex3f(-0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, 0.05, 0.3);
	glVertex3f(0.02, -0.1, 0.33);
	glVertex3f(-0.02, -0.1, 0.33);
	glVertex3f(-0.02, 0.05, 0.3);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.05, -0.3);
	glVertex3f(-0.02, -0.13, -0.33);
	glVertex3f(0.02, -0.13, -0.33);
	glVertex3f(0.02, 0.05, -0.3);
	glEnd();

	/// <summary>
	/// /
	/// </summary>


}

void drawHead() {


	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();
	glPushMatrix();

	glTranslatef(0, 0, -0.3);
	glRotatef(-angleHead, 1, 0, 0);
	glTranslatef(0, 0, 0.3);

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricTexture(cylinder, true);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.2, 0.2, 0.3, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricTexture(cylinder, true);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.2, 0.3, 0.15, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0.125);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, -0.125);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0.125);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.125, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, -0.125);
	glRotatef(180, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.0375, 0.1, 18, 2);
	glPopMatrix();
	glPopMatrix();

	//
	glPushMatrix();
	glColor3f(0, 0, 0);

	glPushMatrix();
	glTranslatef(0.085, 0.05, 0.07);
	glScalef(2, 2, 2);
	drawStickMan();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.085, 0.05, 0.07);
	glScalef(2, 2, 2);
	drawStickMan();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPopMatrix();

	glBegin(GL_QUADS);
	glVertex3f(0.15, 0.1, 0.1);
	glVertex3f(0.15, 0.05, 0.1);
	glVertex3f(0.08, 0.05, 0.15);
	glVertex3f(0.08, 0.1, 0.15);

	glVertex3f(0.08, 0.1, 0.15);
	glVertex3f(0.08, 0.05, 0.15);
	glVertex3f(0.02, 0.05, 0.15);
	glVertex3f(0.02, 0.1, 0.15);

	glVertex3f(0.02, 0.1, 0.15);
	glVertex3f(0.02, 0.05, 0.15);
	glVertex3f(0.02, 0.05, 0.1);
	glVertex3f(0.02, 0.1, 0.1);

	glVertex3f(0.02, 0.1, 0.1);
	glVertex3f(0.02, 0.05, 0.1);
	glVertex3f(0.15, 0.05, 0.1);
	glVertex3f(0.15, 0.1, 0.1);

	glVertex3f(0.15, 0.1, 0.1);
	glVertex3f(0.08, 0.1, 0.15);
	glVertex3f(0.02, 0.1, 0.15);
	glVertex3f(0.02, 0.1, 0.1);

	glVertex3f(-0.15, 0.1, 0.1);
	glVertex3f(-0.15, 0.05, 0.1);
	glVertex3f(-0.08, 0.05, 0.15);
	glVertex3f(-0.08, 0.1, 0.15);

	glVertex3f(-0.08, 0.1, 0.15);
	glVertex3f(-0.08, 0.05, 0.15);
	glVertex3f(-0.02, 0.05, 0.15);
	glVertex3f(-0.02, 0.1, 0.15);

	glVertex3f(-0.02, 0.1, 0.15);
	glVertex3f(-0.02, 0.05, 0.15);
	glVertex3f(-0.02, 0.05, 0.1);
	glVertex3f(-0.02, 0.1, 0.1);

	glVertex3f(-0.02, 0.1, 0.1);
	glVertex3f(-0.02, 0.05, 0.1);
	glVertex3f(-0.15, 0.05, 0.1);
	glVertex3f(-0.15, 0.1, 0.1);

	glVertex3f(-0.15, 0.1, 0.1);
	glVertex3f(-0.08, 0.1, 0.15);
	glVertex3f(-0.02, 0.1, 0.15);
	glVertex3f(-0.02, 0.1, 0.1);
	glEnd();
	//

	glBegin(GL_POLYGON);
	glVertex3f(0.02, 0.05, 0.33);
	glVertex3f(0.2, 0.05, 0.33);
	glVertex3f(0.38, 0.05, 0.15);
	glVertex3f(0.4, 0.05, 0);
	glVertex3f(0.38, 0.05, -0.15);
	glVertex3f(0.2, 0.05, -0.33);
	glVertex3f(0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.02, 0.05, 0.33);
	glVertex3f(-0.2, 0.05, 0.33);
	glVertex3f(-0.38, 0.05, 0.15);
	glVertex3f(-0.4, 0.05, 0);
	glVertex3f(-0.38, 0.05, -0.15);
	glVertex3f(-0.2, 0.05, -0.33);
	glVertex3f(-0.02, 0.05, -0.33);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.1, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.15, 0.38);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.05, 0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.1, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.15, 0.38);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.05, 0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.15, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.38, -0.1, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.38, 0.05, 0.15);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.15, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.38, -0.1, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.38, 0.05, 0.15);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.05, -0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.13, -0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.15, -0.38);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.05, -0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.05, -0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.15, -0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.38, -0.1, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.38, 0.05, -0.15);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.05, -0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.13, -0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.15, -0.38);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.05, -0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.05, -0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.15, -0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.38, -0.1, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.38, 0.05, -0.15);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.1, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, -0.13, -0.38);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.05, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.1, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, -0.13, -0.38);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.05, -0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.05, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.1, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, -0.1, 0.33);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.05, 0.3);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.05, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.13, -0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, -0.13, -0.33);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.05, -0.3);
	glEnd();

	/// <summary>
	/// /
	/// </summary>


}

void drawLineBody() {

	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();

	/// <summary>
	/// RIGHT
	/// </summary>
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(0, -0.3, 0.33);
	glVertex3f(0.03, -0.3, 0.33);
	glVertex3f(0.03, -0.14, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.03, -0.14, 0.36);
	glVertex3f(0.03, -0.3, 0.33);
	glVertex3f(0.08, -0.27, 0.3);
	glVertex3f(0.08, -0.11, 0.3);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(0.03, -0.14, 0.36);
	glVertex3f(0.08, -0.11, 0.3);
	glVertex3f(0.03, -0.11, 0.27);
	glVertex3f(0, -0.11, 0.27);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.11, 0.3);
	glVertex3f(0.08, -0.27, 0.3);
	glVertex3f(0.25, -0.25, 0.2);
	glVertex3f(0.25, -0.09, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.25, -0.09, 0.2);
	glVertex3f(0.25, -0.25, 0.2);
	glVertex3f(0.25, -0.25, -0.2);
	glVertex3f(0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.14, -0.3);
	glVertex3f(0.08, -0.3, -0.3);
	glVertex3f(0.25, -0.25, -0.2);
	glVertex3f(0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.17, -0.36);
	glVertex3f(0.03, -0.17, -0.36);
	glVertex3f(0.08, -0.14, -0.3);
	glVertex3f(0.03, -0.14, -0.27);
	glVertex3f(0, -0.14, -0.27);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.03, -0.17, -0.36);
	glVertex3f(0.03, -0.33, -0.33);
	glVertex3f(0.08, -0.3, -0.3);
	glVertex3f(0.08, -0.14, -0.3);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.17, -0.36);
	glVertex3f(0, -0.33, -0.33);
	glVertex3f(0.03, -0.33, -0.33);
	glVertex3f(0.03, -0.17, -0.36);
	glEnd();
	//////LEFT////
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(0, -0.3, 0.33);
	glVertex3f(-0.03, -0.3, 0.33);
	glVertex3f(-0.03, -0.14, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.03, -0.14, 0.36);
	glVertex3f(-0.03, -0.3, 0.33);
	glVertex3f(-0.08, -0.27, 0.3);
	glVertex3f(-0.08, -0.11, 0.3);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(-0.03, -0.14, 0.36);
	glVertex3f(-0.08, -0.11, 0.3);
	glVertex3f(-0.03, -0.11, 0.27);
	glVertex3f(0, -0.11, 0.27);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.11, 0.3);
	glVertex3f(-0.08, -0.27, 0.3);
	glVertex3f(-0.25, -0.25, 0.2);
	glVertex3f(-0.25, -0.09, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, -0.09, 0.2);
	glVertex3f(-0.25, -0.25, 0.2);
	glVertex3f(-0.25, -0.25, -0.2);
	glVertex3f(-0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.14, -0.3);
	glVertex3f(-0.08, -0.3, -0.3);
	glVertex3f(-0.25, -0.25, -0.2);
	glVertex3f(-0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0, -0.17, -0.36);
	glVertex3f(-0.03, -0.17, -0.36);
	glVertex3f(-0.08, -0.14, -0.3);
	glVertex3f(-0.03, -0.14, -0.27);
	glVertex3f(-0, -0.14, -0.27);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.03, -0.17, -0.36);
	glVertex3f(-0.03, -0.33, -0.33);
	glVertex3f(-0.08, -0.3, -0.3);
	glVertex3f(-0.08, -0.14, -0.3);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.17, -0.36);
	glVertex3f(0, -0.33, -0.33);
	glVertex3f(-0.03, -0.33, -0.33);
	glVertex3f(-0.03, -0.17, -0.36);
	glEnd();


	////////RIGHT/////////
	glPushMatrix();
	glTranslatef(0.08, -0.21, 0.35);
	glRotatef(40, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.02, 18, 2);
	glTranslatef(0, 0, 0.02);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.04, 0.02, 18, 2);
	glPopMatrix();

	//1
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.25, 0.38);
	glVertex3f(0.1, -0.17, 0.38);
	glVertex3f(0.2, -0.14, 0.33);
	glVertex3f(0.2, -0.22, 0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.17, 0.38);
	glVertex3f(0.2, -0.14, 0.33);
	glVertex3f(0.18, -0.13, 0.31);
	glVertex3f(0.08, -0.16, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.16, 0.36);
	glVertex3f(0.18, -0.13, 0.31);
	glVertex3f(0.18, -0.13, 0.29);
	glVertex3f(0.08, -0.16, 0.35);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.25, 0.38);
	glVertex3f(0.2, -0.22, 0.33);
	glVertex3f(0.18, -0.23, 0.31);
	glVertex3f(0.08, -0.26, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.26, 0.36);
	glVertex3f(0.18, -0.23, 0.31);
	glVertex3f(0.18, -0.23, 0.29);
	glVertex3f(0.08, -0.26, 0.35);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.26, 0.35);
	glVertex3f(0.18, -0.23, 0.29);
	glVertex3f(0.18, -0.13, 0.29);
	glVertex3f(0.08, -0.16, 0.35);
	glEnd();

	//2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, -0.14, 0.33);
	glVertex3f(0.2, -0.22, 0.33);
	glVertex3f(0.3, -0.19, 0.18);
	glVertex3f(0.3, -0.11, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.18, -0.13, 0.31);
	glVertex3f(0.2, -0.14, 0.33);
	glVertex3f(0.3, -0.11, 0.18);
	glVertex3f(0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.18, -0.13, 0.29);
	glVertex3f(0.18, -0.13, 0.31);
	glVertex3f(0.28, -0.1, 0.16);
	glVertex3f(0.26, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, -0.22, 0.33);
	glVertex3f(0.3, -0.19, 0.18);
	glVertex3f(0.28, -0.2, 0.18);
	glVertex3f(0.18, -0.23, 0.31);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.28, -0.2, 0.18);
	glVertex3f(0.18, -0.23, 0.31);
	glVertex3f(0.18, -0.23, 0.29);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.18, -0.13, 0.29);
	glVertex3f(0.26, -0.1, 0.16);
	glVertex3f(0.26, -0.2, 0.18);
	glVertex3f(0.18, -0.23, 0.29);
	glEnd();

	//3
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, -0.11, 0.18);
	glVertex3f(0.3, -0.19, 0.18);
	glVertex3f(0.3, -0.16, -0.2);
	glVertex3f(0.3, -0.08, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, -0.11, 0.18);
	glVertex3f(0.3, -0.08, -0.2);
	glVertex3f(0.28, -0.07, -0.2);
	glVertex3f(0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.28, -0.07, -0.2);
	glVertex3f(0.28, -0.1, 0.16);
	glVertex3f(0.26, -0.1, 0.16);
	glVertex3f(0.26, -0.07, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, -0.19, 0.18);
	glVertex3f(0.3, -0.16, -0.2);
	glVertex3f(0.28, -0.17, -0.2);
	glVertex3f(0.28, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.28, -0.2, 0.18);
	glVertex3f(0.28, -0.17, -0.2);
	glVertex3f(0.26, -0.17, -0.2);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.26, -0.1, 0.16);
	glVertex3f(0.26, -0.07, -0.2);
	glVertex3f(0.26, -0.17, -0.2);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	//Change to polygon
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.26, -0.17, -0.2);
	glVertex3f(0.28, -0.17, -0.2);
	glVertex3f(0.3, -0.16, -0.2);
	glVertex3f(0.3, -0.08, -0.2);
	glVertex3f(0.28, -0.07, -0.2);
	glVertex3f(0.26, -0.07, -0.2);
	glEnd();

	///////LEFT//////
	glPushMatrix();
	glTranslatef(-0.08, -0.21, 0.35);
	glRotatef(-40, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.05, 0.02, 18, 2);
	glTranslatef(0, 0, 0.02);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.05, 0.04, 0.02, 18, 2);
	glPopMatrix();

	//1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.38);
	glVertex3f(-0.1, -0.17, 0.38);
	glVertex3f(-0.2, -0.14, 0.33);
	glVertex3f(-0.2, -0.22, 0.33);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.17, 0.38);
	glVertex3f(-0.2, -0.14, 0.33);
	glVertex3f(-0.18, -0.13, 0.31);
	glVertex3f(-0.08, -0.16, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.16, 0.36);
	glVertex3f(-0.18, -0.13, 0.31);
	glVertex3f(-0.18, -0.13, 0.29);
	glVertex3f(-0.08, -0.16, 0.35);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.38);
	glVertex3f(-0.2, -0.22, 0.33);
	glVertex3f(-0.18, -0.23, 0.31);
	glVertex3f(-0.08, -0.26, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.26, 0.36);
	glVertex3f(-0.18, -0.23, 0.31);
	glVertex3f(-0.18, -0.23, 0.29);
	glVertex3f(-0.08, -0.26, 0.35);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.26, 0.35);
	glVertex3f(-0.18, -0.23, 0.29);
	glVertex3f(-0.18, -0.13, 0.29);
	glVertex3f(-0.08, -0.16, 0.35);
	glEnd();

	//2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -0.14, 0.33);
	glVertex3f(-0.2, -0.22, 0.33);
	glVertex3f(-0.3, -0.19, 0.18);
	glVertex3f(-0.3, -0.11, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.18, -0.13, 0.31);
	glVertex3f(-0.2, -0.14, 0.33);
	glVertex3f(-0.3, -0.11, 0.18);
	glVertex3f(-0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.18, -0.13, 0.29);
	glVertex3f(-0.18, -0.13, 0.31);
	glVertex3f(-0.28, -0.1, 0.16);
	glVertex3f(-0.26, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -0.22, 0.33);
	glVertex3f(-0.3, -0.19, 0.18);
	glVertex3f(-0.28, -0.2, 0.18);
	glVertex3f(-0.18, -0.23, 0.31);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.2, 0.18);
	glVertex3f(-0.18, -0.23, 0.31);
	glVertex3f(-0.18, -0.23, 0.29);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.18, -0.13, 0.29);
	glVertex3f(-0.26, -0.1, 0.16);
	glVertex3f(-0.26, -0.2, 0.18);
	glVertex3f(-0.18, -0.23, 0.29);
	glEnd();

	//3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, -0.11, 0.18);
	glVertex3f(-0.3, -0.19, 0.18);
	glVertex3f(-0.3, -0.16, -0.2);
	glVertex3f(-0.3, -0.08, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, -0.11, 0.18);
	glVertex3f(-0.3, -0.08, -0.2);
	glVertex3f(-0.28, -0.07, -0.2);
	glVertex3f(-0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.07, -0.2);
	glVertex3f(-0.28, -0.1, 0.16);
	glVertex3f(-0.26, -0.1, 0.16);
	glVertex3f(-0.26, -0.07, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, -0.19, 0.18);
	glVertex3f(-0.3, -0.16, -0.2);
	glVertex3f(-0.28, -0.17, -0.2);
	glVertex3f(-0.28, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.2, 0.18);
	glVertex3f(-0.28, -0.17, -0.2);
	glVertex3f(-0.26, -0.17, -0.2);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.26, -0.1, 0.16);
	glVertex3f(-0.26, -0.07, -0.2);
	glVertex3f(-0.26, -0.17, -0.2);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	//Change to polygon
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.26, -0.17, -0.2);
	glVertex3f(-0.28, -0.17, -0.2);
	glVertex3f(-0.3, -0.16, -0.2);
	glVertex3f(-0.3, -0.08, -0.2);
	glVertex3f(-0.28, -0.07, -0.2);
	glVertex3f(-0.26, -0.07, -0.2);
	glEnd();
}

void drawBody() {

	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);

	/// <summary>
	/// RIGHT
	/// </summary>
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.14, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.3, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.3, 0.33);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.14, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.14, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.3, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, -0.27, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.11, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(0.03, -0.14, 0.36);
	glVertex3f(0.08, -0.11, 0.3);
	glVertex3f(0.03, -0.11, 0.27);
	glVertex3f(0, -0.11, 0.27);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.11, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.08, -0.27, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -0.25, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -0.09, 0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.25, -0.09, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.25, -0.25, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -0.25, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.14, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.08, -0.3, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -0.25, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.17, -0.36);
	glVertex3f(0.03, -0.17, -0.36);
	glVertex3f(0.08, -0.14, -0.3);
	glVertex3f(0.03, -0.14, -0.27);
	glVertex3f(0, -0.14, -0.27);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.17, -0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.33, -0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, -0.3, -0.3);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.14, -0.3);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.17, -0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.33, -0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.33, -0.33);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.17, -0.36);
	glEnd();

	//////LEFT////
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.14, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.3, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.3, 0.33);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.14, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.14, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.3, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, -0.27, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.11, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.14, 0.36);
	glVertex3f(-0.03, -0.14, 0.36);
	glVertex3f(-0.08, -0.11, 0.3);
	glVertex3f(-0.03, -0.11, 0.27);
	glVertex3f(0, -0.11, 0.27);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.11, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.08, -0.27, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, -0.25, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -0.09, 0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, -0.09, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, -0.25, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, -0.25, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.14, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.08, -0.3, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, -0.25, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, -0.09, -0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0, -0.17, -0.36);
	glVertex3f(-0.03, -0.17, -0.36);
	glVertex3f(-0.08, -0.14, -0.3);
	glVertex3f(-0.03, -0.14, -0.27);
	glVertex3f(-0, -0.14, -0.27);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.17, -0.36);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.33, -0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, -0.3, -0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.14, -0.3);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.17, -0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.33, -0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.33, -0.33);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.17, -0.36);
	glEnd();


	////////RIGHT/////////
	glPushMatrix();
	glTranslatef(0.08, -0.21, 0.35);
	glRotatef(40, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.02, 18, 2);
	glTranslatef(0, 0, 0.02);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.04, 0.02, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.08, -0.21, 0.38);
	glRotatef(40, 0, 1, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	//1
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, -0.25, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, -0.17, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.14, 0.33);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, -0.22, 0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, -0.17, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.14, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.13, 0.31);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.16, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.16, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.13, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.13, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.16, 0.35);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, -0.25, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.22, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.23, 0.31);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.26, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.26, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.23, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.23, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.26, 0.35);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.26, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.23, 0.29);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.13, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.16, 0.35);
	glEnd();

	//2
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.14, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.22, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, -0.19, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, -0.11, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.18, -0.13, 0.31);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.14, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, -0.11, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.18, -0.13, 0.29);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.13, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.1, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.22, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, -0.19, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.2, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.18, -0.23, 0.31);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.28, -0.2, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.23, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.23, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.18, -0.13, 0.29);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, -0.1, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, -0.2, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.18, -0.23, 0.29);
	glEnd();

	//3
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, -0.11, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, -0.19, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, -0.16, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, -0.08, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, -0.11, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, -0.08, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.07, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.28, -0.07, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.28, -0.1, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, -0.1, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.07, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, -0.19, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, -0.16, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.28, -0.2, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.28, -0.17, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, -0.1, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, -0.07, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.2, 0.18);
	glEnd();

	//Change to polygon
	glBegin(GL_POLYGON);
	glVertex3f(0.26, -0.17, -0.2);
	glVertex3f(0.28, -0.17, -0.2);
	glVertex3f(0.3, -0.16, -0.2);
	glVertex3f(0.3, -0.08, -0.2);
	glVertex3f(0.28, -0.07, -0.2);
	glVertex3f(0.26, -0.07, -0.2);
	glEnd();

	///////LEFT//////
	glPushMatrix();
	glTranslatef(-0.08, -0.21, 0.35);
	glRotatef(-40, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.05, 0.02, 18, 2);
	glTranslatef(0, 0, 0.02);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.05, 0.04, 0.02, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, -0.21, 0.38);
	glRotatef(-40, 0, 1, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	//1
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.17, 0.38);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.14, 0.33);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -0.22, 0.33);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.17, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.14, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.13, 0.31);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.16, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.16, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.13, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.13, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.16, 0.35);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.38);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.22, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.23, 0.31);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.26, 0.36);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.26, 0.36);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.23, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.23, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.26, 0.35);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.26, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.23, 0.29);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.13, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.16, 0.35);
	glEnd();

	//2
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.14, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.22, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.19, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, -0.11, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, -0.13, 0.31);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.14, 0.33);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.11, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, -0.13, 0.29);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.13, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.1, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.22, 0.33);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, -0.19, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.2, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.18, -0.23, 0.31);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.28, -0.2, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.23, 0.31);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.23, 0.29);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, -0.13, 0.29);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, -0.1, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, -0.2, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.18, -0.23, 0.29);
	glEnd();

	//3
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, -0.11, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, -0.19, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.16, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, -0.08, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, -0.11, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, -0.08, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.07, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, -0.1, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.28, -0.07, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.28, -0.1, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, -0.1, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.07, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, -0.19, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, -0.16, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.28, -0.2, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.28, -0.17, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, -0.1, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, -0.07, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, -0.17, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.2, 0.18);
	glEnd();

	//Change to polygon
	glBegin(GL_POLYGON);
	glVertex3f(-0.26, -0.17, -0.2);
	glVertex3f(-0.28, -0.17, -0.2);
	glVertex3f(-0.3, -0.16, -0.2);
	glVertex3f(-0.3, -0.08, -0.2);
	glVertex3f(-0.28, -0.07, -0.2);
	glVertex3f(-0.26, -0.07, -0.2);
	glEnd();
}

void drawLowerBody() {

	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.55, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.55, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.55, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.07, -0.55, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.07, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, -0.55, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.035, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, -0.48, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, -0.4, 0.205);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.4, 0.205);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.48, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.165, -0.44, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.155, -0.39, 0.17);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.155, -0.39, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.165, -0.44, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.41, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, -0.39, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.08, -0.4, 0.205);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.39, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.39, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.19, -0.37, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.165, -0.44, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.48, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.165, -0.44, 0.095);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, -0.41, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.39, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.41, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.41, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, -0.39, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.19, -0.37, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.39, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.39, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.19, -0.37, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.41, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.165, -0.44, 0.095);
	glTexCoord2f(1, 1);
	glVertex3f(0.165, -0.44, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, -0.41, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.165, -0.44, 0.095);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.48, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.165, -0.44, -0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.48, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, -0.55, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.12, -0.48, -0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.44, -0.255);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.55, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, -0.55, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.44, -0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.44, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, -0.55, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, -0.42, -0.22);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.075, -0.42, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.48, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.145, -0.46, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.39, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.41, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.145, -0.46, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.41, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.165, -0.44, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.145, -0.46, -0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.19, -0.37, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.39, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.44, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, -0.42, -0.22);
	glEnd();

	////
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.55, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.56, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.56, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.6, 0.19);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.6, 0.19);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.56, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.6, 0.19);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.62, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.62, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.6, 0.19);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.62, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.63, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.63, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.62, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.63, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.7, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.022, -0.7, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.63, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.7, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.72, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.72, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.022, -0.7, 0.17);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.72, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.73, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.047, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.72, 0.16);
	glEnd();

	//

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.55, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.105, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, -0.55, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.07, -0.55, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.105, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.11, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, -0.55, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.105, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.095, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.11, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.085, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.07, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.09, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.105, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.07, -0.64, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(0.047, -0.73, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.105, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.125, -0.64, 0.13);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.07, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.085, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.07, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.07, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.085, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.055, -0.64, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.72, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.047, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, -0.64, 0.13);
	glEnd();

	//
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.6, 0.19);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.62, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.62, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.63, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.63, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.022, -0.7, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.72, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, -0.64, 0.13);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.55, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.58, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(0.095, -0.58, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.075, -0.55, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.095, -0.58, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.58, -0.21);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.61, -0.19);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, -0.61, -0.19);
	glTexCoord2f(0, 1);
	glVertex3f(0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.11, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.095, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, -0.61, -0.19);
	glTexCoord2f(0, 1);
	glVertex3f(0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.61, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.7, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.61, -0.19);
	glEnd();



	////Right////
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.55, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.55, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, -0.55, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.07, -0.55, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.07, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, -0.55, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.035, -0.42, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, -0.42, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, -0.48, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, -0.4, 0.205);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.4, 0.205);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.48, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.165, -0.44, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.155, -0.39, 0.17);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.155, -0.39, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.165, -0.44, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.41, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, -0.39, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.08, -0.4, 0.205);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.39, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.39, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.19, -0.37, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.165, -0.44, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.48, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.165, -0.44, 0.095);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, -0.41, 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.39, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.41, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.41, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, -0.39, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.19, -0.37, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.39, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.39, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.19, -0.37, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.41, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.165, -0.44, 0.095);
	glTexCoord2f(1, 1);
	glVertex3f(-0.165, -0.44, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, -0.41, -0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.165, -0.44, 0.095);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.48, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.165, -0.44, -0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.48, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, -0.55, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, -0.55, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.12, -0.48, -0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.44, -0.255);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.55, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, -0.55, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.44, -0.25);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.44, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, -0.55, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, -0.42, -0.22);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, -0.42, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.48, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.145, -0.46, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.39, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.41, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.145, -0.46, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.41, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.165, -0.44, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, -0.48, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.145, -0.46, -0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.19, -0.37, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.39, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.44, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, -0.42, -0.22);
	glEnd();

	////
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.55, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.56, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.56, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.6, 0.19);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.6, 0.19);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.56, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.6, 0.19);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.62, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.62, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.6, 0.19);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.62, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.63, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.63, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.62, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.63, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.7, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.022, -0.7, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.63, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.7, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.72, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.72, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.022, -0.7, 0.17);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.72, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.73, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.047, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.72, 0.16);
	glEnd();

	//

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.55, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.105, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, -0.55, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.07, -0.55, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.105, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.11, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, -0.55, 0.16);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.105, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.09, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.095, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.11, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.07, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.105, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.07, -0.64, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.047, -0.73, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.105, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.125, -0.64, 0.13);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.07, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.085, -0.6, 0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.07, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.07, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.085, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, -0.64, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.72, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.047, -0.73, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, -0.64, 0.13);
	glEnd();

	//
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.56, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.6, 0.19);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.62, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.62, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.63, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, -0.64, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.63, 0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.022, -0.7, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.72, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, -0.64, 0.13);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.55, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.58, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(-0.095, -0.58, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, -0.55, 0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.11, -0.6, 0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.095, -0.58, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.58, -0.21);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.61, -0.19);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, -0.61, -0.19);
	glTexCoord2f(0, 1);
	glVertex3f(-0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, -0.6, 0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.095, -0.64, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, -0.61, -0.19);
	glTexCoord2f(0, 1);
	glVertex3f(-0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0, -0.61, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(-0, -0.7, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.7, -0.21);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.61, -0.19);
	glEnd();

	/////
	glPushMatrix();
	glTranslatef(0.1, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.13, 0.13, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.075, 0.09, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.15, 0.15, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.13, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	drawFilledCircle(0, 0, 0.13);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.13, 0.13, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.075, 0.09, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.15, 0.15, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.13, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	drawFilledCircle(0, 0, 0.13);
	glPopMatrix();


}

void drawLineLowerBody() {

	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.42, 0.25);
	glVertex3f(0, -0.55, 0.18);
	glVertex3f(0.05, -0.55, 0.18);
	glVertex3f(0.02, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.02, -0.42, 0.25);
	glVertex3f(0.05, -0.55, 0.18);
	glVertex3f(0.07, -0.55, 0.16);
	glVertex3f(0.03, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.03, -0.42, 0.25);
	glVertex3f(0.07, -0.55, 0.16);
	glVertex3f(0.075, -0.55, 0.16);
	glVertex3f(0.035, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.035, -0.42, 0.25);
	glVertex3f(0.075, -0.55, 0.16);
	glVertex3f(0.12, -0.48, 0.17);
	glVertex3f(0.08, -0.4, 0.205);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.4, 0.205);
	glVertex3f(0.12, -0.48, 0.17);
	glVertex3f(0.165, -0.44, 0.17);
	glVertex3f(0.155, -0.39, 0.17);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.155, -0.39, 0.17);
	glVertex3f(0.165, -0.44, 0.17);
	glVertex3f(0.21, -0.41, 0.1);
	glVertex3f(0.21, -0.39, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.08, -0.4, 0.205);
	glVertex3f(0.155, -0.39, 0.17);
	glVertex3f(0.21, -0.39, 0.1);
	glVertex3f(0.19, -0.37, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.165, -0.44, 0.17);
	glVertex3f(0.12, -0.48, 0.17);
	glVertex3f(0.165, -0.44, 0.095);
	glVertex3f(0.21, -0.41, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.21, -0.39, 0.1);
	glVertex3f(0.21, -0.41, 0.1);
	glVertex3f(0.21, -0.41, -0.16);
	glVertex3f(0.21, -0.39, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.19, -0.37, 0.1);
	glVertex3f(0.21, -0.39, 0.1);
	glVertex3f(0.21, -0.39, -0.16);
	glVertex3f(0.19, -0.37, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.21, -0.41, 0.1);
	glVertex3f(0.165, -0.44, 0.095);
	glVertex3f(0.165, -0.44, -0.14);
	glVertex3f(0.21, -0.41, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.165, -0.44, 0.095);
	glVertex3f(0.12, -0.48, 0.16);
	glVertex3f(0.12, -0.48, -0.18);
	glVertex3f(0.165, -0.44, -0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.12, -0.48, 0.17);
	glVertex3f(0.075, -0.55, 0.16);
	glVertex3f(0.075, -0.55, -0.2);
	glVertex3f(0.12, -0.48, -0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.44, -0.255);
	glVertex3f(0, -0.55, -0.2);
	glVertex3f(0.075, -0.55, -0.2);
	glVertex3f(0.03, -0.44, -0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.03, -0.44, -0.25);
	glVertex3f(0.075, -0.55, -0.2);
	glVertex3f(0.12, -0.48, -0.18);
	glVertex3f(0.075, -0.42, -0.22);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.075, -0.42, -0.22);
	glVertex3f(0.12, -0.48, -0.18);
	glVertex3f(0.145, -0.46, -0.18);
	glVertex3f(0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.21, -0.39, -0.16);
	glVertex3f(0.21, -0.41, -0.16);
	glVertex3f(0.145, -0.46, -0.18);
	glVertex3f(0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.21, -0.41, -0.16);
	glVertex3f(0.165, -0.44, -0.14);
	glVertex3f(0.12, -0.48, -0.18);
	glVertex3f(0.145, -0.46, -0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.19, -0.37, -0.16);
	glVertex3f(0.21, -0.39, -0.16);
	glVertex3f(0.1, -0.44, -0.2);
	glVertex3f(0.075, -0.42, -0.22);
	glEnd();

	////
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.55, 0.18);
	glVertex3f(0, -0.56, 0.18);
	glVertex3f(0.04, -0.56, 0.18);
	glVertex3f(0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.56, 0.18);
	glVertex3f(0, -0.6, 0.19);
	glVertex3f(0.03, -0.6, 0.19);
	glVertex3f(0.04, -0.56, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.6, 0.19);
	glVertex3f(0, -0.62, 0.18);
	glVertex3f(0.05, -0.62, 0.18);
	glVertex3f(0.03, -0.6, 0.19);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.62, 0.18);
	glVertex3f(0, -0.63, 0.18);
	glVertex3f(0.03, -0.63, 0.18);
	glVertex3f(0.05, -0.62, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.63, 0.18);
	glVertex3f(0, -0.7, 0.17);
	glVertex3f(0.022, -0.7, 0.17);
	glVertex3f(0.03, -0.63, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.7, 0.17);
	glVertex3f(0, -0.72, 0.16);
	glVertex3f(0.03, -0.72, 0.16);
	glVertex3f(0.022, -0.7, 0.17);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.72, 0.16);
	glVertex3f(0, -0.73, 0.16);
	glVertex3f(0.047, -0.73, 0.16);
	glVertex3f(0.03, -0.72, 0.16);
	glEnd();

	//

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.55, 0.18);
	glVertex3f(0.085, -0.6, 0.14);
	glVertex3f(0.105, -0.6, 0.14);
	glVertex3f(0.07, -0.55, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.07, -0.55, 0.16);
	glVertex3f(0.105, -0.6, 0.14);
	glVertex3f(0.11, -0.6, 0.14);
	glVertex3f(0.075, -0.55, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.105, -0.6, 0.14);
	glVertex3f(0.09, -0.64, 0.13);
	glVertex3f(0.095, -0.64, 0.13);
	glVertex3f(0.11, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.085, -0.6, 0.14);
	glVertex3f(0.07, -0.64, 0.13);
	glVertex3f(0.09, -0.64, 0.13);
	glVertex3f(0.105, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.07, -0.64, 0.13);
	glVertex3f(0.047, -0.73, 0.16);
	glVertex3f(0.105, -0.73, 0.16);
	glVertex3f(0.125, -0.64, 0.13);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.04, -0.56, 0.18);
	glVertex3f(0.07, -0.6, 0.14);
	glVertex3f(0.085, -0.6, 0.14);
	glVertex3f(0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.07, -0.6, 0.14);
	glVertex3f(0.055, -0.64, 0.13);
	glVertex3f(0.07, -0.64, 0.13);
	glVertex3f(0.085, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.055, -0.64, 0.13);
	glVertex3f(0.03, -0.72, 0.16);
	glVertex3f(0.047, -0.73, 0.16);
	glVertex3f(0.07, -0.64, 0.13);
	glEnd();

	//
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.04, -0.56, 0.18);
	glVertex3f(0.03, -0.6, 0.19);
	glVertex3f(0.05, -0.62, 0.18);
	glVertex3f(0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.62, 0.18);
	glVertex3f(0.03, -0.63, 0.18);
	glVertex3f(0.055, -0.64, 0.13);
	glVertex3f(0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.03, -0.63, 0.18);
	glVertex3f(0.022, -0.7, 0.17);
	glVertex3f(0.03, -0.72, 0.16);
	glVertex3f(0.055, -0.64, 0.13);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.55, -0.2);
	glVertex3f(0, -0.58, -0.21);
	glVertex3f(0.095, -0.58, -0.21);
	glVertex3f(0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.075, -0.55, 0.16);
	glVertex3f(0.11, -0.6, 0.14);
	glVertex3f(0.095, -0.58, -0.21);
	glVertex3f(0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.58, -0.21);
	glVertex3f(0, -0.61, -0.19);
	glVertex3f(0.08, -0.61, -0.19);
	glVertex3f(0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.11, -0.6, 0.14);
	glVertex3f(0.095, -0.64, 0.13);
	glVertex3f(0.08, -0.61, -0.19);
	glVertex3f(0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.61, -0.19);
	glVertex3f(0, -0.7, -0.21);
	glVertex3f(0.03, -0.7, -0.21);
	glVertex3f(0.05, -0.61, -0.19);
	glEnd();



	////Right////
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.42, 0.25);
	glVertex3f(0, -0.55, 0.18);
	glVertex3f(-0.05, -0.55, 0.18);
	glVertex3f(-0.02, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, -0.42, 0.25);
	glVertex3f(-0.05, -0.55, 0.18);
	glVertex3f(-0.07, -0.55, 0.16);
	glVertex3f(-0.03, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.03, -0.42, 0.25);
	glVertex3f(-0.07, -0.55, 0.16);
	glVertex3f(-0.075, -0.55, 0.16);
	glVertex3f(-0.035, -0.42, 0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.035, -0.42, 0.25);
	glVertex3f(-0.075, -0.55, 0.16);
	glVertex3f(-0.12, -0.48, 0.17);
	glVertex3f(-0.08, -0.4, 0.205);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.4, 0.205);
	glVertex3f(-0.12, -0.48, 0.17);
	glVertex3f(-0.165, -0.44, 0.17);
	glVertex3f(-0.155, -0.39, 0.17);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.155, -0.39, 0.17);
	glVertex3f(-0.165, -0.44, 0.17);
	glVertex3f(-0.21, -0.41, 0.1);
	glVertex3f(-0.21, -0.39, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, -0.4, 0.205);
	glVertex3f(-0.155, -0.39, 0.17);
	glVertex3f(-0.21, -0.39, 0.1);
	glVertex3f(-0.19, -0.37, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.165, -0.44, 0.17);
	glVertex3f(-0.12, -0.48, 0.17);
	glVertex3f(-0.165, -0.44, 0.095);
	glVertex3f(-0.21, -0.41, 0.1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.21, -0.39, 0.1);
	glVertex3f(-0.21, -0.41, 0.1);
	glVertex3f(-0.21, -0.41, -0.16);
	glVertex3f(-0.21, -0.39, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.19, -0.37, 0.1);
	glVertex3f(-0.21, -0.39, 0.1);
	glVertex3f(-0.21, -0.39, -0.16);
	glVertex3f(-0.19, -0.37, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.21, -0.41, 0.1);
	glVertex3f(-0.165, -0.44, 0.095);
	glVertex3f(-0.165, -0.44, -0.14);
	glVertex3f(-0.21, -0.41, -0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.165, -0.44, 0.095);
	glVertex3f(-0.12, -0.48, 0.16);
	glVertex3f(-0.12, -0.48, -0.18);
	glVertex3f(-0.165, -0.44, -0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.12, -0.48, 0.17);
	glVertex3f(-0.075, -0.55, 0.16);
	glVertex3f(-0.075, -0.55, -0.2);
	glVertex3f(-0.12, -0.48, -0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.44, -0.255);
	glVertex3f(0, -0.55, -0.2);
	glVertex3f(-0.075, -0.55, -0.2);
	glVertex3f(-0.03, -0.44, -0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.03, -0.44, -0.25);
	glVertex3f(-0.075, -0.55, -0.2);
	glVertex3f(-0.12, -0.48, -0.18);
	glVertex3f(-0.075, -0.42, -0.22);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.075, -0.42, -0.22);
	glVertex3f(-0.12, -0.48, -0.18);
	glVertex3f(-0.145, -0.46, -0.18);
	glVertex3f(-0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.21, -0.39, -0.16);
	glVertex3f(-0.21, -0.41, -0.16);
	glVertex3f(-0.145, -0.46, -0.18);
	glVertex3f(-0.1, -0.44, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.21, -0.41, -0.16);
	glVertex3f(-0.165, -0.44, -0.14);
	glVertex3f(-0.12, -0.48, -0.18);
	glVertex3f(-0.145, -0.46, -0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.19, -0.37, -0.16);
	glVertex3f(-0.21, -0.39, -0.16);
	glVertex3f(-0.1, -0.44, -0.2);
	glVertex3f(-0.075, -0.42, -0.22);
	glEnd();

	////
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.55, 0.18);
	glVertex3f(0, -0.56, 0.18);
	glVertex3f(-0.04, -0.56, 0.18);
	glVertex3f(-0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.56, 0.18);
	glVertex3f(0, -0.6, 0.19);
	glVertex3f(-0.03, -0.6, 0.19);
	glVertex3f(-0.04, -0.56, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.6, 0.19);
	glVertex3f(0, -0.62, 0.18);
	glVertex3f(-0.05, -0.62, 0.18);
	glVertex3f(-0.03, -0.6, 0.19);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.62, 0.18);
	glVertex3f(0, -0.63, 0.18);
	glVertex3f(-0.03, -0.63, 0.18);
	glVertex3f(-0.05, -0.62, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.63, 0.18);
	glVertex3f(0, -0.7, 0.17);
	glVertex3f(-0.022, -0.7, 0.17);
	glVertex3f(-0.03, -0.63, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.7, 0.17);
	glVertex3f(0, -0.72, 0.16);
	glVertex3f(-0.03, -0.72, 0.16);
	glVertex3f(-0.022, -0.7, 0.17);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.72, 0.16);
	glVertex3f(0, -0.73, 0.16);
	glVertex3f(-0.047, -0.73, 0.16);
	glVertex3f(-0.03, -0.72, 0.16);
	glEnd();

	//

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.05, -0.55, 0.18);
	glVertex3f(-0.085, -0.6, 0.14);
	glVertex3f(-0.105, -0.6, 0.14);
	glVertex3f(-0.07, -0.55, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.07, -0.55, 0.16);
	glVertex3f(-0.105, -0.6, 0.14);
	glVertex3f(-0.11, -0.6, 0.14);
	glVertex3f(-0.075, -0.55, 0.16);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.105, -0.6, 0.14);
	glVertex3f(-0.09, -0.64, 0.13);
	glVertex3f(-0.095, -0.64, 0.13);
	glVertex3f(-0.11, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.085, -0.6, 0.14);
	glVertex3f(-0.07, -0.64, 0.13);
	glVertex3f(-0.09, -0.64, 0.13);
	glVertex3f(-0.105, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.07, -0.64, 0.13);
	glVertex3f(-0.047, -0.73, 0.16);
	glVertex3f(-0.105, -0.73, 0.16);
	glVertex3f(-0.125, -0.64, 0.13);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.04, -0.56, 0.18);
	glVertex3f(-0.07, -0.6, 0.14);
	glVertex3f(-0.085, -0.6, 0.14);
	glVertex3f(-0.05, -0.55, 0.18);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.07, -0.6, 0.14);
	glVertex3f(-0.055, -0.64, 0.13);
	glVertex3f(-0.07, -0.64, 0.13);
	glVertex3f(-0.085, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.055, -0.64, 0.13);
	glVertex3f(-0.03, -0.72, 0.16);
	glVertex3f(-0.047, -0.73, 0.16);
	glVertex3f(-0.07, -0.64, 0.13);
	glEnd();

	//
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.04, -0.56, 0.18);
	glVertex3f(-0.03, -0.6, 0.19);
	glVertex3f(-0.05, -0.62, 0.18);
	glVertex3f(-0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.05, -0.62, 0.18);
	glVertex3f(-0.03, -0.63, 0.18);
	glVertex3f(-0.055, -0.64, 0.13);
	glVertex3f(-0.07, -0.6, 0.14);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.03, -0.63, 0.18);
	glVertex3f(-0.022, -0.7, 0.17);
	glVertex3f(-0.03, -0.72, 0.16);
	glVertex3f(-0.055, -0.64, 0.13);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.55, -0.2);
	glVertex3f(0, -0.58, -0.21);
	glVertex3f(-0.095, -0.58, -0.21);
	glVertex3f(-0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.075, -0.55, 0.16);
	glVertex3f(-0.11, -0.6, 0.14);
	glVertex3f(-0.095, -0.58, -0.21);
	glVertex3f(-0.075, -0.55, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.58, -0.21);
	glVertex3f(0, -0.61, -0.19);
	glVertex3f(-0.08, -0.61, -0.19);
	glVertex3f(-0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.11, -0.6, 0.14);
	glVertex3f(-0.095, -0.64, 0.13);
	glVertex3f(-0.08, -0.61, -0.19);
	glVertex3f(-0.095, -0.58, -0.21);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.61, -0.19);
	glVertex3f(0, -0.7, -0.21);
	glVertex3f(-0.03, -0.7, -0.21);
	glVertex3f(-0.05, -0.61, -0.19);
	glEnd();

	/////
	glPushMatrix();
	glTranslatef(0.1, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.13, 0.13, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.075, 0.09, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.15, 0.15, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.13, 0.13, 0.03, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.075, 0.09, 0.1, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, -0.03);
	glRotatef(-90, 0, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.15, 0.15, 0.03, 18, 2);
	glPopMatrix();

}

void drawLineRightUpperArm() {

	glPushMatrix();
	glRotatef(180, 0, 1, 0);//

	//Upper Shoulder
	glPushMatrix();

	glPushMatrix();
	drawFilledCircle(0, 0, 0.25);
	GLUquadricObj* cylinderR1 = NULL;
	cylinderR1 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR1, GLU_LINE);
	gluCylinder(cylinderR1, 0.25, 0.25, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawFilledCircle(0, 0, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-25, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-50, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-100, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-125, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-150, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-175, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-200, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-225, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Lower Shoulder
	glPushMatrix();

	glScalef(0.8, 0.8, 0.9);
	glTranslatef(-0.04, -0.7, 0.3);
	glRotatef(180, 0, 1, 0);//

	glPushMatrix();
	glTranslatef(0.0, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, -0.32, 0);
	glRotatef(-130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.09, -0.32, 0);
	glRotatef(130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00, -0.43, 0);
	glScalef(0.35, 0.35, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, 0.26, 0);
	glRotatef(-35, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0.295, 0);
	glScalef(0.58, 0.58, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void drawLineRightLowerArm() {

	glPushMatrix();
	glRotatef(180, 0, 1, 0);//

	//Joint
	glPushMatrix();

	drawFilledCircle(0, 0, 0.15);
	GLUquadricObj* cylinderR3 = NULL;
	cylinderR3 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR3, GLU_LINE);
	gluCylinder(cylinderR3, 0.15, 0.15, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR3);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.15);

	glPopMatrix();

	//Upper
	glPushMatrix();

	glTranslatef(0, -0.28, 0);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.2, 0.15, 0.3, -0.2, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar1
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR4 = NULL;
	cylinderR4 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR4, GLU_LINE);
	gluCylinder(cylinderR4, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR5 = NULL;
	cylinderR5 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR5, GLU_LINE);
	gluCylinder(cylinderR5, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR6 = NULL;
	cylinderR6 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR6, GLU_LINE);
	gluCylinder(cylinderR6, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar2
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR7 = NULL;
	cylinderR7 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR7, GLU_LINE);
	gluCylinder(cylinderR7, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR8 = NULL;
	cylinderR8 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR8, GLU_LINE);
	gluCylinder(cylinderR8, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR8);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR9 = NULL;
	cylinderR9 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR9, GLU_LINE);
	gluCylinder(cylinderR9, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar3
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR10 = NULL;
	cylinderR10 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR10, GLU_LINE);
	gluCylinder(cylinderR10, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR11 = NULL;
	cylinderR11 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR11, GLU_LINE);
	gluCylinder(cylinderR11, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR11);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR12 = NULL;
	cylinderR12 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR12, GLU_LINE);
	gluCylinder(cylinderR12, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar4
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR13 = NULL;
	cylinderR13 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR13, GLU_LINE);
	gluCylinder(cylinderR13, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR13);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR14 = NULL;
	cylinderR14 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR14, GLU_LINE);
	gluCylinder(cylinderR14, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR14);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR15 = NULL;
	cylinderR15 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR15, GLU_LINE);
	gluCylinder(cylinderR15, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Wrist 1
	glPushMatrix();

	glTranslatef(0.0, -0.8, 0.0);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.2, 0.25, 0.3, -0.2, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Wrist 2
	glPushMatrix();

	glTranslatef(0.0, -1.22, 0.0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();

	glScalef(2.0, 1.2, 1.4);
	glTranslatef(-0.075, 0.0, -0.15);
	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glScalef(1.0, 1.2, 1.0);
	glTranslatef(-0.15, -0.15, -0.15);
	drawFilledCircle(0, 0, 0.1);
	GLUquadricObj* cylinderR16 = NULL;
	cylinderR16 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR16, GLU_LINE);
	gluCylinder(cylinderR16, 0.1, 0.1, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR16);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.1);

	glPopMatrix();

	glPopMatrix();

	//Fingers
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	glRotatef(180, 0, 1, 0);//

	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, -0.18);
	glRotatef(-10, 1, 0, 0);

	//Finger1
	glPushMatrix();

	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 2
	glPushMatrix();

	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 3
	glPushMatrix();

	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 4
	glPushMatrix();

	glTranslatef(-0.6, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//Thumb
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, -0.07);
	//glRotatef(-90, 0, 1, 0);


	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.6);
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, 0.945);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.55);
	glRotatef(25, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void drawLineLeftUpperArm() {

	//Upper Shoulder
	glPushMatrix();

	glPushMatrix();
	drawFilledCircle(0, 0, 0.25);
	GLUquadricObj* cylinderL1 = NULL;
	cylinderL1 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL1, GLU_LINE);
	gluCylinder(cylinderL1, 0.25, 0.25, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawFilledCircle(0, 0, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-25, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-50, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-100, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-125, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-150, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-175, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-200, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-225, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Lower Shoulder
	glPushMatrix();

	glScalef(0.8, 0.8, 0.9);
	glTranslatef(-0.04, -0.7, 0.015);

	glPushMatrix();
	glTranslatef(0.0, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, -0.32, 0);
	glRotatef(-130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.09, -0.32, 0);
	glRotatef(130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00, -0.43, 0);
	glScalef(0.35, 0.35, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, 0.26, 0);
	glRotatef(-35, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0.295, 0);
	glScalef(0.58, 0.58, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPopMatrix();

}

void drawLineLeftLowerArm() {

	//Joint
	glPushMatrix();

	drawFilledCircle(0, 0, 0.15);
	GLUquadricObj* cylinderL3 = NULL;
	cylinderL3 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL3, GLU_LINE);
	gluCylinder(cylinderL3, 0.15, 0.15, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL3);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.15);

	glPopMatrix();

	//Upper
	glPushMatrix();

	glTranslatef(0, -0.28, 0);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.2, 0.15, 0.3, -0.2, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar1
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL4 = NULL;
	cylinderL4 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL4, GLU_LINE);
	gluCylinder(cylinderL4, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL5 = NULL;
	cylinderL5 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL5, GLU_LINE);
	gluCylinder(cylinderL5, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL6 = NULL;
	cylinderL6 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL6, GLU_LINE);
	gluCylinder(cylinderL6, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar2
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL7 = NULL;
	cylinderL7 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL7, GLU_LINE);
	gluCylinder(cylinderL7, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL8 = NULL;
	cylinderL8 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL8, GLU_LINE);
	gluCylinder(cylinderL8, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL8);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL9 = NULL;
	cylinderL9 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL9, GLU_LINE);
	gluCylinder(cylinderL9, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar3
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL10 = NULL;
	cylinderL10 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL10, GLU_LINE);
	gluCylinder(cylinderL10, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL11 = NULL;
	cylinderL11 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL11, GLU_LINE);
	gluCylinder(cylinderL11, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL11);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL12 = NULL;
	cylinderL12 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL12, GLU_LINE);
	gluCylinder(cylinderL12, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar4
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL13 = NULL;
	cylinderL13 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL13, GLU_LINE);
	gluCylinder(cylinderL13, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL13);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL14 = NULL;
	cylinderL14 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL14, GLU_LINE);
	gluCylinder(cylinderL14, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL14);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL15 = NULL;
	cylinderL15 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL15, GLU_LINE);
	gluCylinder(cylinderL15, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Wrist 1
	glPushMatrix();

	glTranslatef(0.0, -0.8, 0.0);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.2, 0.25, 0.3, -0.2, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Wrist 2
	glPushMatrix();

	glTranslatef(0.0, -1.22, 0.0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();

	glScalef(2.0, 1.2, 1.4);
	glTranslatef(-0.075, 0.0, -0.15);
	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glScalef(1.0, 1.2, 1.0);
	glTranslatef(-0.15, -0.15, -0.15);
	drawFilledCircle(0, 0, 0.1);
	GLUquadricObj* cylinderL16 = NULL;
	cylinderL16 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL16, GLU_LINE);
	gluCylinder(cylinderL16, 0.1, 0.1, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL16);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.1);

	glPopMatrix();

	glPopMatrix();

	//Fingers
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, 0.57);
	glRotatef(180, 1, 0, 0);

	//Finger1
	glPushMatrix();

	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 2
	glPushMatrix();

	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 3
	glPushMatrix();

	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 4
	glPushMatrix();

	glTranslatef(-0.6, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//Thumb
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, 0.47);
	glRotatef(180, 0, 1, 0);


	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.6);
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, 0.945);
	glRotatef(10, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.55);
	glRotatef(25, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void drawLineRightUpperLeg() {

	//Joint connect body to leg
	glPushMatrix();

	glScalef(0.9, 1.2, 0.75);
	glTranslatef(0.0, 0.05, 0.0);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	GLUquadricObj* cylinderRL1 = NULL;
	cylinderRL1 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL1, GLU_LINE);
	gluCylinder(cylinderRL1, 0.075, 0.075, 0.8, 20, 20);
	gluDeleteQuadric(cylinderRL1);
	glPopMatrix();

	glPopMatrix();

	//Thigh
	glPushMatrix();

	glScalef(1.4, 0.5, 1.1);
	glTranslatef(0.0, -0.35, -0.05);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();


	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.295, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(-0.15, 0.15, 0.05, 0.15, -0.15, -0.35);

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.595, 0.25);
	glRotatef(180, 1, 0, 0);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

}

void drawLineRightLowerLeg() {

	//Joint
	glPushMatrix();

	glTranslatef(0.0, -0.345, -0.09);

	glPushMatrix();
	GLUquadricObj* cylinderRL2 = NULL;
	cylinderRL2 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL2, GLU_LINE);
	gluCylinder(cylinderRL2, 0.15, 0.15, 0.4, 20, 20);
	gluDeleteQuadric(cylinderRL2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(40, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(80, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(140, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(160, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glTranslatef(0.0, 0.0, -0.125);
	GLUquadricObj* cylinderRL3 = NULL;
	cylinderRL3 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL3, GLU_LINE);
	gluCylinder(cylinderRL3, 0.085, 0.085, 0.45, 20, 20);
	gluDeleteQuadric(cylinderRL3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.025);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.425);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPopMatrix();

	//xiao tui
	glPushMatrix();

	glScalef(0.8, 1.1, 0.8);
	glTranslatef(0.025, -0.25, 0.13);
	glRotatef(-angleRightLeg2, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	drawLineCube(-0.25, 0.0, 0.25, 0.2, 0.0, -0.25);

	//front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.25, -0.325);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(0.05, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(0.05, -0.25, -0.325);
	glVertex3f(0.05, -1.35, -0.2);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, -0.25);
	glVertex3f(-0.25, 0.00, -0.25);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(0.05, -0.25, -0.325);
	glEnd();

	//back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.25, 0.325);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(0.05, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(0.05, -0.25, 0.325);
	glVertex3f(0.05, -1.35, 0.2);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, 0.25);
	glVertex3f(-0.25, 0.00, 0.25);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(0.05, -0.25, 0.325);
	glEnd();

	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.275, -0.25, 0.1);
	glVertex3f(0.15, -1.35, 0.1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.15, -1.35, -0.1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.275, -0.25, 0.1);
	glVertex3f(0.15, -1.35, 0.1);
	glVertex3f(0.15, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, 0.25);
	glVertex3f(0.2, 0.00, -0.25);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.275, -0.25, 0.1);
	glEnd();

	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.325, -0.25, 0.1);
	glVertex3f(-0.2, -1.35, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.2, -1.35, -0.1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.325, -0.25, 0.1);
	glVertex3f(-0.2, -1.35, 0.1);
	glVertex3f(-0.2, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.00, 0.25);
	glVertex3f(-0.25, 0.00, -0.25);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.325, -0.25, 0.1);
	glEnd();

	//Jiao Huai - left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.55, -1.35, -0.1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.55, -1.35, 0.1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	//Jiao Huai - front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(-0.1, -0.95, -0.275);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(-0.1, -0.95, -0.275);
	glVertex3f(-0.2, -1.35, -0.275);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(0.15, -1.35, -0.275);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.275);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(0.15, -1.35, -0.275);
	glVertex3f(-0.2, -1.35, -0.275);
	glEnd();

	//Jiao Huai - back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(-0.1, -0.95, 0.275);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(-0.1, -0.95, 0.275);
	glVertex3f(-0.2, -1.35, 0.275);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(0.15, -1.35, 0.275);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.275);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(0.15, -1.35, 0.275);
	glVertex3f(-0.2, -1.35, 0.275);
	glEnd();

	//Foot
	drawLineCube(-0.9, -1.35, 0.295, 0.275, -1.5, -0.295);

	glPopMatrix();

}

void drawLineLeftUpperLeg() {

	//Joint connect body to leg
	glPushMatrix();

	glScalef(0.9, 1.2, 0.75);
	glTranslatef(0.0, 0.05, 0.3);
	glRotatef(180, 0, 1, 0);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	GLUquadricObj* cylinderRL1 = NULL;
	cylinderRL1 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL1, GLU_LINE);
	gluCylinder(cylinderRL1, 0.075, 0.075, 0.8, 20, 20);
	gluDeleteQuadric(cylinderRL1);
	glPopMatrix();

	glPopMatrix();

	//Thigh
	glPushMatrix();

	glScalef(1.4, 0.5, 1.1);
	glTranslatef(0.0, -0.35, -0.05);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.295, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(-0.15, 0.15, 0.05, 0.15, -0.15, -0.35);

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.595, 0.25);
	glRotatef(180, 1, 0, 0);

	//Front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(-0.1, 0.15, 0.0);
	glVertex3f(-0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.3);
	glVertex3f(0.1, 0.15, 0.0);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, 0.35);
	glVertex3f(0.15, -0.15, -0.05);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

}

void drawLineLeftLowerLeg() {

	//Joint
	glPushMatrix();

	glTranslatef(0.0, -0.345, -0.09);

	glPushMatrix();
	GLUquadricObj* cylinderRL2 = NULL;
	cylinderRL2 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL2, GLU_LINE);
	gluCylinder(cylinderRL2, 0.15, 0.15, 0.4, 20, 20);
	gluDeleteQuadric(cylinderRL2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(40, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(80, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(140, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(160, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.0);
	drawLineCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glTranslatef(0.0, 0.0, -0.125);
	GLUquadricObj* cylinderRL3 = NULL;
	cylinderRL3 = gluNewQuadric();
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderRL3, GLU_LINE);
	gluCylinder(cylinderRL3, 0.085, 0.085, 0.45, 20, 20);
	gluDeleteQuadric(cylinderRL3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.025);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.425);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPopMatrix();

	//xiao tui
	glPushMatrix();

	glScalef(0.8, 1.1, 0.8);
	glTranslatef(0.025, -0.25, 0.13);
	glRotatef(-angleLeftLeg2, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	drawLineCube(-0.25, 0.0, 0.25, 0.2, 0.0, -0.25);

	//front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.25, -0.325);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(0.05, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(0.05, -0.25, -0.325);
	glVertex3f(0.05, -1.35, -0.2);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, -0.25);
	glVertex3f(-0.25, 0.00, -0.25);
	glVertex3f(-0.1, -0.25, -0.325);
	glVertex3f(0.05, -0.25, -0.325);
	glEnd();

	//back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.25, 0.325);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(0.05, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(0.05, -0.25, 0.325);
	glVertex3f(0.05, -1.35, 0.2);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, 0.25);
	glVertex3f(-0.25, 0.00, 0.25);
	glVertex3f(-0.1, -0.25, 0.325);
	glVertex3f(0.05, -0.25, 0.325);
	glEnd();

	//right
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, 0.25);
	glVertex3f(0.275, -0.25, 0.1);
	glVertex3f(0.15, -1.35, 0.1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.0, -0.25);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.15, -1.35, -0.1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.275, -0.25, 0.1);
	glVertex3f(0.15, -1.35, 0.1);
	glVertex3f(0.15, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.2, 0.00, 0.25);
	glVertex3f(0.2, 0.00, -0.25);
	glVertex3f(0.275, -0.25, -0.1);
	glVertex3f(0.275, -0.25, 0.1);
	glEnd();

	//left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, 0.25);
	glVertex3f(-0.325, -0.25, 0.1);
	glVertex3f(-0.2, -1.35, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.0, -0.25);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.2, -1.35, -0.1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.325, -0.25, 0.1);
	glVertex3f(-0.2, -1.35, 0.1);
	glVertex3f(-0.2, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.25, 0.00, 0.25);
	glVertex3f(-0.25, 0.00, -0.25);
	glVertex3f(-0.325, -0.25, -0.1);
	glVertex3f(-0.325, -0.25, 0.1);
	glEnd();

	//Jiao Huai - left
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.55, -1.35, -0.1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.55, -1.35, 0.1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, -0.1);
	glVertex3f(-0.2, -1.35, -0.2);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.255, -0.85, 0.1);
	glVertex3f(-0.2, -1.35, 0.2);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	//Jiao Huai - front
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.15, -1.35, -0.2);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(-0.1, -0.95, -0.275);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.245);
	glVertex3f(-0.1, -0.95, -0.275);
	glVertex3f(-0.2, -1.35, -0.275);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.95, -0.245);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(0.15, -1.35, -0.275);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, -0.275);
	glVertex3f(0.05, -0.95, -0.275);
	glVertex3f(0.15, -1.35, -0.275);
	glVertex3f(-0.2, -1.35, -0.275);
	glEnd();

	//Jiao Huai - back
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.15, -1.35, 0.2);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(-0.1, -0.95, 0.275);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.245);
	glVertex3f(-0.1, -0.95, 0.275);
	glVertex3f(-0.2, -1.35, 0.275);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.05, -0.95, 0.245);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(0.15, -1.35, 0.275);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.95, 0.275);
	glVertex3f(0.05, -0.95, 0.275);
	glVertex3f(0.15, -1.35, 0.275);
	glVertex3f(-0.2, -1.35, 0.275);
	glEnd();

	//Foot
	drawLineCube(-0.9, -1.35, 0.295, 0.275, -1.5, -0.295);

	glPopMatrix();

}

void drawRightUpperArm() {

	glPushMatrix();
	glRotatef(180, 0, 1, 0);//

	//Upper Shoulder
	glPushMatrix();

	glPushMatrix();
	drawFilledCircle(0, 0, 0.25);
	GLUquadricObj* cylinderR1 = NULL;
	cylinderR1 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR1, true);
	//gluQuadricDrawStyle(cylinderR1, GLU_FILL);
	gluCylinder(cylinderR1, 0.25, 0.25, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawFilledCircle(0, 0, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-25, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-50, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-100, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-125, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-150, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-175, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-200, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-225, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Lower Shoulder
	glPushMatrix();

	glScalef(0.8, 0.8, 0.9);
	glTranslatef(-0.04, -0.7, 0.3);
	glRotatef(180, 0, 1, 0);//


	glPushMatrix();
	glTranslatef(0.0, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, -0.32, 0);
	glRotatef(-130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.09, -0.32, 0);
	glRotatef(130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00, -0.43, 0);
	glScalef(0.35, 0.35, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, 0.26, 0);
	glRotatef(-35, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0.295, 0);
	glScalef(0.58, 0.58, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void drawRightLowerArm() {

	glPushMatrix();
	glRotatef(180, 0, 1, 0);//

	//Joint
	glPushMatrix();

	drawFilledCircle(0, 0, 0.15);
	GLUquadricObj* cylinderR3 = NULL;
	cylinderR3 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR3, true);
	//gluQuadricDrawStyle(cylinderR3, GLU_FILL);
	gluCylinder(cylinderR3, 0.15, 0.15, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR3);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.15);

	glPopMatrix();

	//Upper
	glPushMatrix();

	glTranslatef(0, -0.28, 0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.2, 0.15, 0.3, -0.2, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar1
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR4 = NULL;
	cylinderR4 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR4, true);
	//gluQuadricDrawStyle(cylinderR4, GLU_FILL);
	gluCylinder(cylinderR4, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR5 = NULL;
	cylinderR5 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR5, true);
	//gluQuadricDrawStyle(cylinderR5, GLU_FILL);
	gluCylinder(cylinderR5, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR6 = NULL;
	cylinderR6 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR6, true);
	//gluQuadricDrawStyle(cylinderR6, GLU_FILL);
	gluCylinder(cylinderR6, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar2
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR7 = NULL;
	cylinderR7 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR7, true);
	//gluQuadricDrawStyle(cylinderR7, GLU_FILL);
	gluCylinder(cylinderR7, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR8 = NULL;
	cylinderR8 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR8, true);
	//gluQuadricDrawStyle(cylinderR8, GLU_FILL);
	gluCylinder(cylinderR8, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR8);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR9 = NULL;
	cylinderR9 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR9, true);
	//gluQuadricDrawStyle(cylinderR9, GLU_FILL);
	gluCylinder(cylinderR9, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar3
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR10 = NULL;
	cylinderR10 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR10, true);
	//gluQuadricDrawStyle(cylinderR10, GLU_FILL);
	gluCylinder(cylinderR10, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR11 = NULL;
	cylinderR11 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR11, true);
	//gluQuadricDrawStyle(cylinderR11, GLU_FILL);
	gluCylinder(cylinderR11, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR11);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR12 = NULL;
	cylinderR12 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR12, true);
	//gluQuadricDrawStyle(cylinderR12, GLU_FILL);
	gluCylinder(cylinderR12, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar4
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR13 = NULL;
	cylinderR13 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR13, true);
	//gluQuadricDrawStyle(cylinderR13, GLU_FILL);
	gluCylinder(cylinderR13, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderR13);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR14 = NULL;
	cylinderR14 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR14, true);
	//gluQuadricDrawStyle(cylinderR14, GLU_FILL);
	gluCylinder(cylinderR14, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR14);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderR15 = NULL;
	cylinderR15 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR15, true);
	//gluQuadricDrawStyle(cylinderR15, GLU_FILL);
	gluCylinder(cylinderR15, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderR15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Wrist 1
	glPushMatrix();

	glTranslatef(0.0, -0.8, 0.0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.2, 0.25, 0.3, -0.2, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Wrist 2
	glPushMatrix();

	glTranslatef(0.0, -1.22, 0.0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();

	glScalef(2.0, 1.2, 1.4);
	glTranslatef(-0.075, 0.0, -0.15);
	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	if (checkWeapon) {
		glPushMatrix();
		glScalef(0.55, 1.6, 0.85);
		glTranslatef(-0.25, -0.5, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		drawSword();//here
		glPopMatrix();
	}

	if (checkWeapon1) {
		glPushMatrix();
		glScalef(1.55, 2.2, 1.55);
		glTranslatef(-0.1, -0.5, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		drawGunLine();
		drawGun();//here
		glPopMatrix();
	}

	glScalef(1.0, 1.2, 1.0);
	glTranslatef(-0.15, -0.15, -0.15);
	drawFilledCircle(0, 0, 0.1);
	GLUquadricObj* cylinderR16 = NULL;
	cylinderR16 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderR16, true);
	//gluQuadricDrawStyle(cylinderR16, GLU_FILL);
	gluCylinder(cylinderR16, 0.1, 0.1, 0.3, 20, 20);
	gluDeleteQuadric(cylinderR16);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.1);

	glPopMatrix();

	glPopMatrix();

	//Fingers
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	glRotatef(180, 0, 1, 0);//

	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, -0.18);
	glRotatef(-10, 1, 0, 0);

	//Finger1
	glPushMatrix();

	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 2
	glPushMatrix();

	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 3
	glPushMatrix();

	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 4
	glPushMatrix();

	glTranslatef(-0.6, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//Thumb
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, -0.07);
	//glRotatef(-90, 0, 1, 0);


	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.6);
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, 0.945);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.55);
	glRotatef(25, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void drawLeftUpperArm() {

	//Upper Shoulder
	glPushMatrix();

	glPushMatrix();
	drawFilledCircle(0, 0, 0.25);
	GLUquadricObj* cylinderL1 = NULL;
	cylinderL1 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL1, true);
	//gluQuadricDrawStyle(cylinderL1, GLU_FILL);
	gluCylinder(cylinderL1, 0.25, 0.25, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.3);
	drawFilledCircle(0, 0, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-25, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-50, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-100, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-125, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-150, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-175, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-200, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-225, 0, 0, 1);
	glTranslatef(-0.125, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.06, 0.3, -0.165, -0.06, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Lower Shoulder
	glPushMatrix();

	glScalef(0.8, 0.8, 0.9);
	glTranslatef(-0.04, -0.7, 0.015);

	glPushMatrix();
	glTranslatef(0.0, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, -0.32, 0);
	glRotatef(-130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.09, -0.32, 0);
	glRotatef(130, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.00, -0.43, 0);
	glScalef(0.35, 0.35, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, 0.26, 0);
	glRotatef(-35, 0, 0, 1);
	glScalef(0.5, 0.5, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.125, 0.295, 0);
	glScalef(0.58, 0.58, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.3, 0.3, 0.3, -0.3, -0.3, 0.0);
	glPopMatrix();

	glPopMatrix();

}

void drawLeftLowerArm() {

	//Joint
	glPushMatrix();

	drawFilledCircle(0, 0, 0.15);
	GLUquadricObj* cylinderL3 = NULL;
	cylinderL3 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL3, true);
	//gluQuadricDrawStyle(cylinderL3, GLU_FILL);
	gluCylinder(cylinderL3, 0.15, 0.15, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL3);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.15);

	glPopMatrix();

	//Upper
	glPushMatrix();

	glTranslatef(0, -0.28, 0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.2, 0.15, 0.3, -0.2, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.15, 0.3, -0.15, -0.15, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar1
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL4 = NULL;
	cylinderL4 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL4, true);
	//gluQuadricDrawStyle(cylinderL4, GLU_FILL);
	gluCylinder(cylinderL4, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL5 = NULL;
	cylinderL5 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL5, true);
	//gluQuadricDrawStyle(cylinderL5, GLU_FILL);
	gluCylinder(cylinderL5, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL6 = NULL;
	cylinderL6 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL6, true);
	//gluQuadricDrawStyle(cylinderL6, GLU_FILL);
	gluCylinder(cylinderL6, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar2
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.028);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL7 = NULL;
	cylinderL7 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL7, true);
	//gluQuadricDrawStyle(cylinderL7, GLU_FILL);
	gluCylinder(cylinderL7, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL7);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL8 = NULL;
	cylinderL8 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL8, true);
	//gluQuadricDrawStyle(cylinderL8, GLU_FILL);
	gluCylinder(cylinderL8, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL8);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL9 = NULL;
	cylinderL9 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL9, true);
	//gluQuadricDrawStyle(cylinderL9, GLU_FILL);
	gluCylinder(cylinderL9, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar3
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL10 = NULL;
	cylinderL10 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL10, true);
	//gluQuadricDrawStyle(cylinderL10, GLU_FILL);
	gluCylinder(cylinderL10, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL11 = NULL;
	cylinderL11 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL11, true);
	//gluQuadricDrawStyle(cylinderL11, GLU_FILL);
	gluCylinder(cylinderL11, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL11);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL12 = NULL;
	cylinderL12 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL12, true);
	//gluQuadricDrawStyle(cylinderL12, GLU_FILL);
	gluCylinder(cylinderL12, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Metal Bar4
	glPushMatrix();

	glTranslatef(0, -0.28, 0);
	glTranslatef(-0.09, -0.15, 0.267);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL13 = NULL;
	cylinderL13 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL13, true);
	//gluQuadricDrawStyle(cylinderL13, GLU_FILL);
	gluCylinder(cylinderL13, 0.025, 0.025, 0.12, 20, 20);
	gluDeleteQuadric(cylinderL13);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL14 = NULL;
	cylinderL14 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL14, true);
	//gluQuadricDrawStyle(cylinderL14, GLU_FILL);
	gluCylinder(cylinderL14, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL14);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* cylinderL15 = NULL;
	cylinderL15 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL15, true);
	//gluQuadricDrawStyle(cylinderL15, GLU_FILL);
	gluCylinder(cylinderL15, 0.04, 0.04, 0.02, 20, 20);
	gluDeleteQuadric(cylinderL15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	glRotatef(90, 1, 0, 0);
	drawFilledCircle(0, 0, 0.04);
	glPopMatrix();

	glPopMatrix();

	//Wrist 1
	glPushMatrix();

	glTranslatef(0.0, -0.8, 0.0);

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.2, 0.25, 0.3, -0.2, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.06);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, -0.12);
	glRotatef(45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, -0.12);
	glRotatef(-45, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(-0.64, 0.0, 1.23);
	glRotatef(135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.27, 1.0, 0.27);
	glTranslatef(0.64, 0.0, 1.23);
	glRotatef(-135, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.15, 0.25, 0.3, -0.15, -0.25, 0.0);
	glPopMatrix();

	glPopMatrix();

	//Wrist 2
	glPushMatrix();

	glTranslatef(0.0, -1.22, 0.0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();

	glScalef(2.0, 1.2, 1.4);
	glTranslatef(-0.075, 0.0, -0.15);
	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPopMatrix();

	if (checkWeapon) {
		glPushMatrix();
		glScalef(0.55, 1.6, 0.85);
		glTranslatef(-0.25, -0.5, 0.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		drawSword();//here
		glPopMatrix();
	}

	if (checkWeapon1) {
		glPushMatrix();
		glScalef(1.55, 2.2, 1.55);
		glTranslatef(-0.1, -0.5, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		drawGunLine();
		drawGun();//here
		glPopMatrix();
	}

	glPushMatrix();

	glScalef(1.0, 1.2, 1.0);
	glTranslatef(-0.15, -0.15, -0.15);
	drawFilledCircle(0, 0, 0.1);
	GLUquadricObj* cylinderL16 = NULL;
	cylinderL16 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderL16, true);
	//gluQuadricDrawStyle(cylinderL16, GLU_FILL);
	gluCylinder(cylinderL16, 0.1, 0.1, 0.3, 20, 20);
	gluDeleteQuadric(cylinderL16);

	glTranslatef(0.0, 0.00, 0.3);
	drawFilledCircle(0, 0, 0.1);

	glPopMatrix();

	glPopMatrix();

	//Fingers
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, 0.57);
	glRotatef(180, 1, 0, 0);

	//Finger1
	glPushMatrix();

	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 2
	glPushMatrix();

	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 3
	glPushMatrix();

	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	//Finger 4
	glPushMatrix();

	glTranslatef(-0.6, 0.0, 0.0);
	glRotatef(15, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.0);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, -0.04);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.45, 0.65);
	glTranslatef(0.0, -0.37, 0.06);
	glRotatef(-20, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.31, 0.115);
	glRotatef(-30, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//Thumb
	glPushMatrix();

	glScalef(0.5, 0.65, 0.75);
	glTranslatef(0.3, -2.58, 0.47);
	glRotatef(180, 0, 1, 0);


	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.33, 0.6);
	glRotatef(-10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.85, 0.44, 0.65);
	glTranslatef(0.0, 0.38, 0.945);
	glRotatef(10, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.55);
	glRotatef(25, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.1, 0.15, 0.05, -0.1, -0.15, -0.05);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void drawRightUpperLeg() {

	//Joint connect body to leg
	glPushMatrix();

	glScalef(0.9, 1.2, 0.75);
	glTranslatef(0.0, 0.05, 0.0);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	GLUquadricObj* cylinderRL1 = NULL;
	cylinderRL1 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL1, true);
	gluQuadricDrawStyle(cylinderRL1, GLU_FILL);
	gluCylinder(cylinderRL1, 0.075, 0.075, 0.8, 20, 20);
	gluDeleteQuadric(cylinderRL1);
	glPopMatrix();

	glPopMatrix();

	//Thigh
	glPushMatrix();

	glScalef(1.4, 0.5, 1.1);
	glTranslatef(0.0, -0.35, -0.05);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();


	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.295, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(-0.15, 0.15, 0.05, 0.15, -0.15, -0.35);

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.595, 0.25);
	glRotatef(180, 1, 0, 0);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

}

void drawRightLowerLeg() {

	//Joint
	glPushMatrix();

	glTranslatef(0.0, -0.345, -0.09);
	glPushMatrix();
	GLUquadricObj* cylinderRL2 = NULL;
	cylinderRL2 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL2, true);
	//gluQuadricDrawStyle(cylinderRL2, GLU_FILL);
	gluCylinder(cylinderRL2, 0.15, 0.15, 0.4, 20, 20);
	gluDeleteQuadric(cylinderRL2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(40, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(80, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(140, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(160, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glTranslatef(0.0, 0.0, -0.125);
	GLUquadricObj* cylinderRL3 = NULL;
	cylinderRL3 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL3, true);
	//gluQuadricDrawStyle(cylinderRL3, GLU_FILL);
	gluCylinder(cylinderRL3, 0.085, 0.085, 0.45, 20, 20);
	gluDeleteQuadric(cylinderRL3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.025);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.425);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPopMatrix();

	//xiao tui
	glPushMatrix();

	glScalef(0.8, 1.1, 0.8);
	glTranslatef(0.025, -0.25, 0.13);
	glRotatef(-angleRightLeg2, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	drawTextureCube(-0.25, 0.0, 0.25, 0.2, 0.0, -0.25);

	//front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.25, -0.325);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.25, -0.325);
	glEnd();

	//back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.25, 0.325);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.25, 0.325);
	glEnd();

	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.275, -0.25, 0.1);
	glEnd();

	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.325, -0.25, 0.1);
	glEnd();

	//Jiao Huai - left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0.5, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0.5, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	//Jiao Huai - front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.95, -0.275);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.275);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.275);
	glEnd();

	//Jiao Huai - back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.95, 0.275);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.275);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.275);
	glEnd();

	//Foot
	drawTextureCube(-0.9, -1.35, 0.295, 0.275, -1.5, -0.295);

	glPopMatrix();

}

void drawLeftUpperLeg() {

	//Joint connect body to leg
	glPushMatrix();

	glScalef(0.9, 1.2, 0.75);
	glTranslatef(0.0, 0.05, 0.3);
	glRotatef(180, 0, 1, 0);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.3);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.3);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	GLUquadricObj* cylinderRL1 = NULL;
	cylinderRL1 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL1, true);
	//gluQuadricDrawStyle(cylinderRL1, GLU_FILL);
	gluCylinder(cylinderRL1, 0.075, 0.075, 0.8, 20, 20);
	gluDeleteQuadric(cylinderRL1);
	glPopMatrix();

	glPopMatrix();

	//Thigh
	glPushMatrix();

	glScalef(1.4, 0.5, 1.1);
	glTranslatef(0.0, -0.35, -0.05);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.295, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(-0.15, 0.15, 0.05, 0.15, -0.15, -0.35);

	glPopMatrix();

	glPushMatrix();

	glScalef(1.4, 1.75, 1.1);
	glTranslatef(0.0, -0.595, 0.25);
	glRotatef(180, 1, 0, 0);

	//Front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();
	//Back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, 0.35);
	glEnd();
	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.15, 0.35);
	glEnd();
	//top
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.15, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.0);
	glEnd();
	//bottom
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.15, 0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.15, 0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.15, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.15, -0.05);
	glEnd();

	glPopMatrix();

}

void drawLeftLowerLeg() {

	//Joint
	glPushMatrix();

	glTranslatef(0.0, -0.345, -0.09);

	glPushMatrix();
	GLUquadricObj* cylinderRL2 = NULL;
	cylinderRL2 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL2, true);
	//gluQuadricDrawStyle(cylinderRL2, GLU_FILL);
	gluCylinder(cylinderRL2, 0.15, 0.15, 0.4, 20, 20);
	gluDeleteQuadric(cylinderRL2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(40, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(80, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(100, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(140, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(160, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	drawTextureCube(0.165, 0.03, 0.4, -0.165, -0.03, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	glTranslatef(0.0, 0.0, -0.125);
	GLUquadricObj* cylinderRL3 = NULL;
	cylinderRL3 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricTexture(cylinderRL3, true);
	//gluQuadricDrawStyle(cylinderRL3, GLU_FILL);
	gluCylinder(cylinderRL3, 0.085, 0.085, 0.45, 20, 20);
	gluDeleteQuadric(cylinderRL3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.025);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.425);
	drawFilledCircle(0, 0, 0.085);
	glPopMatrix();

	glPopMatrix();

	//xiao tui
	glPushMatrix();

	glScalef(0.8, 1.1, 0.8);
	glTranslatef(0.025, -0.25, 0.13);
	glRotatef(-angleLeftLeg2, 0, 0, 1);
	glTranslatef(0.0, -0.2, 0.0);
	drawTextureCube(-0.25, 0.0, 0.25, 0.2, 0.0, -0.25);

	//front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.25, -0.325);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.25, -0.325);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.25, -0.325);
	glEnd();

	//back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.25, 0.325);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.25, 0.325);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.25, 0.325);
	glEnd();

	//right
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.275, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.275, -0.25, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.275, -0.25, 0.1);
	glEnd();

	//left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.0, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.325, -0.25, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.00, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.25, 0.00, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.325, -0.25, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.325, -0.25, 0.1);
	glEnd();

	//Jiao Huai - left
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, -0.2);
	glTexCoord2f(0.5, 1);
	glVertex3f(-0.55, -1.35, -0.1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.255, -0.85, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -1.35, 0.2);
	glTexCoord2f(0.5, 1);
	glVertex3f(-0.55, -1.35, 0.1);
	glEnd();

	//Jiao Huai - front
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.95, -0.275);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.95, -0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, -0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, -0.275);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, -0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, -0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, -0.275);
	glEnd();

	//Jiao Huai - back
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.95, 0.275);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.95, 0.245);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -1.35, 0.2);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.95, 0.275);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.95, 0.275);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -1.35, 0.275);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -1.35, 0.275);
	glEnd();

	//Foot
	drawTextureCube(-0.9, -1.35, 0.295, 0.275, -1.5, -0.295);

	glPushMatrix();
	if (checkUlti2) {

		glTranslatef(0.0, -2.0, 0.0);
		glRotatef(90, 0, 1, 0);
		drawSword();

	}
	glPopMatrix();

	glPopMatrix();

}

void drawWarehouseSignWall() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "cherno.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//BACK WALL
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 0, -12);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 5, -12);
	glTexCoord2f(1, 1);
	glVertex3f(4, 5, -12);
	glTexCoord2f(1, 0);
	glVertex3f(4, 0, -12);
	glEnd();

	//FRONT WALL
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 0, 12);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 5, 12);
	glTexCoord2f(0, 1);
	glVertex3f(4, 5, 12);
	glTexCoord2f(0, 0);
	glVertex3f(4, 0, 12);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawWarehouseFloor() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "floorWood2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	for (int i = 0; i < 12; i++) {
		float z = -12;
		z = z + (i * 2);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-4, 0, z + 2);
		glTexCoord2f(0, 1);
		glVertex3f(-4, 0, z);
		glTexCoord2f(1, 1);
		glVertex3f(-2, 0, z);
		glTexCoord2f(1, 0);
		glVertex3f(-2, 0, z + 2);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-2, 0, z + 2);
		glTexCoord2f(0, 1);
		glVertex3f(-2, 0, z);
		glTexCoord2f(1, 1);
		glVertex3f(0, 0, z);
		glTexCoord2f(1, 0);
		glVertex3f(0, 0, z + 2);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, z + 2);
		glTexCoord2f(0, 1);
		glVertex3f(0, 0, z);
		glTexCoord2f(1, 1);
		glVertex3f(2, 0, z);
		glTexCoord2f(1, 0);
		glVertex3f(2, 0, z + 2);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(2, 0, z + 2);
		glTexCoord2f(0, 1);
		glVertex3f(2, 0, z);
		glTexCoord2f(1, 1);
		glVertex3f(4, 0, z);
		glTexCoord2f(1, 0);
		glVertex3f(4, 0, z + 2);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawWarehouseWall() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "WallCement.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(0.8, 0.8, 0.8);

	//RIGHT WALL
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(4, 0, 12);
	glTexCoord2f(1, 0);
	glVertex3f(4, 0, -12);
	glTexCoord2f(1, 1);
	glVertex3f(4, 5, -12);
	glTexCoord2f(0, 1);
	glVertex3f(4, 5, 12);
	glEnd();

	//LEFT WALL
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 0, 12);
	glTexCoord2f(1, 0);
	glVertex3f(-4, 0, -12);
	glTexCoord2f(1, 1);
	glVertex3f(-4, 5, -12);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 5, 12);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	drawWarehouseFloor();

	drawWarehouseSignWall();
}

void drawWarehouseRoof() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "RoofWood1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(0.588, 0.294, 0);

	//WoodRoof
	for (int i = 0; i < 12; i++) {
		float z[] = { -11.6, -11.4 };
		z[0] = z[0] + (2 * i);
		z[1] = z[1] + (2 * i);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-4, 4.7, z[0]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.7, z[0]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[0]);
		glTexCoord2f(0, 1);
		glVertex3f(-4, 4.4, z[0]);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-4, 4.7, z[1]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.7, z[1]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[1]);
		glTexCoord2f(0, 1);
		glVertex3f(-4, 4.4, z[1]);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-4, 4.4, z[0]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.4, z[0]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[1]);
		glTexCoord2f(0, 1);
		glVertex3f(-4, 4.4, z[1]);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(4, 4.7, z[0]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.7, z[0]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[0]);
		glTexCoord2f(0, 1);
		glVertex3f(4, 4.4, z[0]);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(4, 4.7, z[1]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.7, z[1]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[1]);
		glTexCoord2f(0, 1);
		glVertex3f(4, 4.4, z[1]);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(4, 4.4, z[0]);
		glTexCoord2f(1, 0);
		glVertex3f(0, 6.4, z[0]);
		glTexCoord2f(1, 1);
		glVertex3f(0, 6.4, z[1]);
		glTexCoord2f(0, 1);
		glVertex3f(4, 4.4, z[1]);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawWarehouseRoof1() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "RoofWood.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(222 / 255, 184 / 255, 135 / 255);

	for (int i = 0; i < 6; i++) {

		float x[] = { 0.1, 0.2 };
		float y[] = { 6.95, 6.85 };

		x[0] = x[0] + (i * 0.75);
		x[1] = x[1] + (i * 0.75);
		y[0] = y[0] - (i * 0.375);
		y[1] = y[1] - (i * 0.375);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x[0], y[0], 12);
		glTexCoord2f(0, 0);
		glVertex3f(x[1], y[1], 12);
		glTexCoord2f(0, 0);
		glVertex3f(x[1], y[1], -12);
		glTexCoord2f(0, 0);
		glVertex3f(x[0], y[0], -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x[0], y[0] - 0.3, 12);
		glTexCoord2f(1, 0);
		glVertex3f(x[1], y[1] - 0.3, 12);
		glTexCoord2f(1, 1);
		glVertex3f(x[1], y[1] - 0.3, -12);
		glTexCoord2f(0, 1);
		glVertex3f(x[0], y[0] - 0.3, -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x[1], y[1], -12);
		glTexCoord2f(1, 0);
		glVertex3f(x[1], y[1], 12);
		glTexCoord2f(1, 1);
		glVertex3f(x[1], y[1] - 0.3, 12);
		glTexCoord2f(0, 1);
		glVertex3f(x[1], y[1] - 0.3, -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(x[0], y[0] - 0.3, -12);
		glTexCoord2f(1, 0);
		glVertex3f(x[0], y[0] - 0.3, 12);
		glTexCoord2f(1, 1);
		glVertex3f(x[0], y[0], 12);
		glTexCoord2f(0, 1);
		glVertex3f(x[0], y[0], -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-x[0], y[0], 12);
		glTexCoord2f(1, 0);
		glVertex3f(-x[1], y[1], 12);
		glTexCoord2f(1, 1);
		glVertex3f(-x[1], y[1], -12);
		glTexCoord2f(0, 1);
		glVertex3f(-x[0], y[0], -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-x[0], y[0] - 0.3, 12);
		glTexCoord2f(1, 0);
		glVertex3f(-x[1], y[1] - 0.3, 12);
		glTexCoord2f(1, 1);
		glVertex3f(-x[1], y[1] - 0.3, -12);
		glTexCoord2f(0, 1);
		glVertex3f(-x[0], y[0] - 0.3, -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-x[1], y[1], -12);
		glTexCoord2f(1, 0);
		glVertex3f(-x[1], y[1], 12);
		glTexCoord2f(1, 1);
		glVertex3f(-x[1], y[1] - 0.3, 12);
		glTexCoord2f(0, 1);
		glVertex3f(-x[1], y[1] - 0.3, -12);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-x[0], y[0] - 0.3, -12);
		glTexCoord2f(1, 0);
		glVertex3f(-x[0], y[0] - 0.3, 12);
		glTexCoord2f(1, 1);
		glVertex3f(-x[0], y[0], 12);
		glTexCoord2f(0, 1);
		glVertex3f(-x[0], y[0], -12);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawWarehouseRoof2() {
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "RoofWood2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(0.663, 0.663, 0.663);

	//ROOF
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 5, -12);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 7, -12);
	glTexCoord2f(1, 0);
	glVertex3f(4, 5, -12);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 5, 12);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 7, 12);
	glTexCoord2f(1, 0);
	glVertex3f(4, 5, 12);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(4, 5, 12);
	glTexCoord2f(1, 0);
	glVertex3f(0, 7, 12);
	glTexCoord2f(1, 1);
	glVertex3f(0, 7, -12);
	glTexCoord2f(0, 1);
	glVertex3f(4, 5, -12);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-4, 5, 12);
	glTexCoord2f(1, 0);
	glVertex3f(0, 7, 12);
	glTexCoord2f(1, 1);
	glVertex3f(0, 7, -12);
	glTexCoord2f(0, 1);
	glVertex3f(-4, 5, -12);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawPalletBox() {

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "PalletBox.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, -0.8);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.5, 0, -0.75);
	glRotatef(5, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.3, 0.4, -0.6);
	glRotatef(-15, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.2, 0, -0.3);
	glRotatef(35, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.5, 0, -0.5);
	glRotatef(20, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.3, 0.4, -0.6);
	glRotatef(30, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	/*glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.3, 0, -0.5);
	glRotatef(45, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.2, 0, -0.3);
	glRotatef(40, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.2, 0.4, -0.6);
	glRotatef(70, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.5, 0.4, -0.4);
	glRotatef(50, 0, 1, 0);
	drawTextureCube(0.2, 0, 0.2, -0.2, 0.4, -0.2);
	glPopMatrix();*/

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawFarmWarehouse() {

	drawWarehouseWall();
	drawWarehouseRoof2();
	drawWarehouseRoof();
	drawWarehouseRoof1();

	glPushMatrix();
	glTranslatef(3, 0, -11);
	drawPalletBox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, -11);
	glRotatef(180, 0, 1, 0);
	drawPalletBox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 0, -11);
	glRotatef(40, 0, 1, 0);
	drawPalletBox();
	glPopMatrix();
}

void drawLineFarmWarehouse() {
	//RIGHT WALL
	glBegin(GL_LINE_LOOP);
	glVertex3f(4, 0, 12);
	glVertex3f(4, 0, -12);
	glVertex3f(4, 5, -12);
	glVertex3f(4, 5, 12);
	glEnd();

	//LEFT WALL
	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 0, 12);
	glVertex3f(-4, 0, -12);
	glVertex3f(-4, 5, -12);
	glVertex3f(-4, 5, 12);
	glEnd();

	//BACK WALL
	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 0, -12);
	glVertex3f(-4, 5, -12);
	glVertex3f(4, 5, -12);
	glVertex3f(4, 0, -12);
	glEnd();

	//FRONT WALL
	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 0, 12);
	glVertex3f(-4, 5, 12);
	glVertex3f(4, 5, 12);
	glVertex3f(4, 0, 12);
	glEnd();

	//FLOOR
	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 0, 12);
	glVertex3f(-4, 0, -12);
	glVertex3f(4, 0, -12);
	glVertex3f(4, 0, 12);
	glEnd();

	//ROOF
	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 5, -12);
	glVertex3f(0, 7, -12);
	glVertex3f(4, 5, -12);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 5, 12);
	glVertex3f(0, 7, 12);
	glVertex3f(4, 5, 12);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(4, 5, 12);
	glVertex3f(0, 7, 12);
	glVertex3f(0, 7, -12);
	glVertex3f(4, 5, -12);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-4, 5, 12);
	glVertex3f(0, 7, 12);
	glVertex3f(0, 7, -12);
	glVertex3f(-4, 5, -12);
	glEnd();

	//WoodRoof
	for (int i = 0; i < 12; i++) {
		float z[] = { -11.6, -11.4 };
		z[0] = z[0] + (2 * i);
		z[1] = z[1] + (2 * i);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-4, 4.7, z[0]);
		glVertex3f(0, 6.7, z[0]);
		glVertex3f(0, 6.4, z[0]);
		glVertex3f(-4, 4.4, z[0]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-4, 4.7, z[1]);
		glVertex3f(0, 6.7, z[1]);
		glVertex3f(0, 6.4, z[1]);
		glVertex3f(-4, 4.4, z[1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-4, 4.4, z[0]);
		glVertex3f(0, 6.4, z[0]);
		glVertex3f(0, 6.4, z[1]);
		glVertex3f(-4, 4.4, z[1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(4, 4.7, z[0]);
		glVertex3f(0, 6.7, z[0]);
		glVertex3f(0, 6.4, z[0]);
		glVertex3f(4, 4.4, z[0]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(4, 4.7, z[1]);
		glVertex3f(0, 6.7, z[1]);
		glVertex3f(0, 6.4, z[1]);
		glVertex3f(4, 4.4, z[1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(4, 4.4, z[0]);
		glVertex3f(0, 6.4, z[0]);
		glVertex3f(0, 6.4, z[1]);
		glVertex3f(4, 4.4, z[1]);
		glEnd();
	}

	for (int i = 0; i < 6; i++) {

		float x[] = { 0.1, 0.2 };
		float y[] = { 6.95, 6.85 };

		x[0] = x[0] + (i * 0.75);
		x[1] = x[1] + (i * 0.75);
		y[0] = y[0] - (i * 0.375);
		y[1] = y[1] - (i * 0.375);

		glBegin(GL_LINE_LOOP);
		glVertex3f(x[0], y[0], 12);
		glVertex3f(x[1], y[1], 12);
		glVertex3f(x[1], y[1], -12);
		glVertex3f(x[0], y[0], -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(x[0], y[0] - 0.3, 12);
		glVertex3f(x[1], y[1] - 0.3, 12);
		glVertex3f(x[1], y[1] - 0.3, -12);
		glVertex3f(x[0], y[0] - 0.3, -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(x[1], y[1], -12);
		glVertex3f(x[1], y[1], 12);
		glVertex3f(x[1], y[1] - 0.3, 12);
		glVertex3f(x[1], y[1] - 0.3, -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(x[0], y[0] - 0.3, -12);
		glVertex3f(x[0], y[0] - 0.3, 12);
		glVertex3f(x[0], y[0], 12);
		glVertex3f(x[0], y[0], -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-x[0], y[0], 12);
		glVertex3f(-x[1], y[1], 12);
		glVertex3f(-x[1], y[1], -12);
		glVertex3f(-x[0], y[0], -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-x[0], y[0] - 0.3, 12);
		glVertex3f(-x[1], y[1] - 0.3, 12);
		glVertex3f(-x[1], y[1] - 0.3, -12);
		glVertex3f(-x[0], y[0] - 0.3, -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-x[1], y[1], -12);
		glVertex3f(-x[1], y[1], 12);
		glVertex3f(-x[1], y[1] - 0.3, 12);
		glVertex3f(-x[1], y[1] - 0.3, -12);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-x[0], y[0] - 0.3, -12);
		glVertex3f(-x[0], y[0] - 0.3, 12);
		glVertex3f(-x[0], y[0], 12);
		glVertex3f(-x[0], y[0], -12);
		glEnd();
	}
}

void drawLineAx() {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(0.180, 0.075, 0);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	//gluQuadricTexture(cylinder, true);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.02, 0.04, 0.8, 20, 20);
	glPopMatrix();

	gluDeleteQuadric(cylinder);

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(0.24, -0.08, 0);
	glVertex3f(0.24, 0.18, 0);
	glVertex3f(-0.08, 0.1, 0.03);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(0.24, -0.08, 0);
	glVertex3f(0.24, 0.18, 0);
	glVertex3f(-0.08, 0.1, -0.03);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(-0.08, 0.1, 0.03);
	glVertex3f(-0.08, 0.1, -0.03);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(0.24, -0.08, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.08, 0.1, -0.03);
	glVertex3f(-0.08, 0.1, 0.03);
	glVertex3f(0.24, 0.18, 0);
	glEnd();

}

void drawAxStick() {


	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(0.294, 0.155, 0);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	//gluQuadricTexture(cylinder, true);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.02, 0.04, 0.8, 20, 20);
	glPopMatrix();

	gluDeleteQuadric(cylinder);

}

void drawAx() {

	glColor3f(0.5, 0.5, 0.5);

	glTranslatef(0, 0.8, 0);

	glBegin(GL_QUADS);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(0.24, -0.08, 0);
	glVertex3f(0.24, 0.18, 0);
	glVertex3f(-0.08, 0.1, 0.03);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(0.24, -0.08, 0);
	glVertex3f(0.24, 0.18, 0);
	glVertex3f(-0.08, 0.1, -0.03);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(-0.08, 0.1, 0.03);
	glVertex3f(-0.08, 0.1, -0.03);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.08, 0, -0.03);
	glVertex3f(-0.08, 0, 0.03);
	glVertex3f(0.24, -0.08, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.08, 0.1, -0.03);
	glVertex3f(-0.08, 0.1, 0.03);
	glVertex3f(0.24, 0.18, 0);
	glEnd();

	drawAxStick();
	drawLineAx();
}

void displayAx() {
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(0, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-45, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-90, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-135, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-180, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-225, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-270, 0, 0, 1);
	drawAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2, 2, 2);
	glRotatef(-305, 0, 0, 1);
	drawAx();
	glPopMatrix();
}

void drawHeadCylinder() {

	GLUquadric* cylinder = NULL;
	cylinder = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0, 0, -0.3);
	glRotatef(-angleHead, 1, 0, 0);
	glTranslatef(0, 0, 0.3);

	glColor3f(0, 0, 0);
	glLineWidth(1);

	glPushMatrix();
	glTranslatef(0.3, 0.1, -0.225);
	glRotatef(headCylinderAngle, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.0365, 0.019, 0.025, 12, 2);
	//gluCylinder(cylinder, 0.0365, 0.019, 0.025, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0.225);
	glRotatef(180, 0, 1, 0);
	glRotatef(headCylinderAngle, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.0365, 0.019, 0.025, 12, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, -0.225);
	glRotatef(headCylinderAngle, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.0365, 0.019, 0.025, 12, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0.225);
	glRotatef(180, 0, 1, 0);
	glRotatef(headCylinderAngle, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.0365, 0.019, 0.025, 12, 2);
	glPopMatrix();

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "yellow.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(1, 1, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);

	glPushMatrix();
	glTranslatef(-0.3, 0.1, 0.225);
	glRotatef(180, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.0375, 0.02, 0.025, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.1, -0.225);
	gluQuadricTexture(cylinder, true);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.0375, 0.02, 0.025, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, 0.225);
	glRotatef(180, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.0375, 0.02, 0.025, 18, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.1, -0.225);
	gluQuadricTexture(cylinder, true);
	//gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.0375, 0.02, 0.025, 18, 2);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glLineWidth(3);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void drawJaeger() {
	/// <summary>
	/// TEXTURE
	/// </summary>
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "Army.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	/////END OF TEXTURE////
	/// <summary>
	/// HEAD
	/// </summary>
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawHead();
	glColor3f(0, 0, 0);
	drawLineHead();
	glPopMatrix();

	/// <summary>
	/// BODY
	/// </summary>
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawBody();
	glColor3f(0, 0, 0);
	drawLineBody();

	glPushMatrix();
	glTranslatef(0, -0.18, 0);
	glScalef(0.8, 0.8, 0.8);
	glColor3f(1, 1, 1);
	drawBody();
	glColor3f(0, 0, 0);
	drawLineBody();
	glPopMatrix();
	glPopMatrix();


	/// <summary>
	/// LOWER BODY
	/// </summary>
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawLowerBody();
	glColor3f(0, 0, 0);
	drawLineLowerBody();
	glPopMatrix();

	/// <summary>
	/// RIGHT HAND
	/// </summary>
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.05, -1, 0);

	//Right Hand Joint
	glPushMatrix();

	glScalef(0.4, 0.4, 0.4);
	glTranslatef(-1.5, 2.5, 0.0);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	GLUquadricObj* cylinderR2 = NULL;
	cylinderR2 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricDrawStyle(cylinderR2, GLU_FILL);
	gluCylinder(cylinderR2, 0.15, 0.15, 0.75, 20, 20);
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderR2, GLU_LINE);
	gluCylinder(cylinderR2, 0.15, 0.15, 0.75, 20, 20);
	gluDeleteQuadric(cylinderR2);
	glPopMatrix();

	glPopMatrix();

	//Right Arm
	glPushMatrix();

	glScalef(0.4, 0.4, 0.4);
	glTranslatef(-1.18, 2.5, 0.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(angleRightHand1, 0, 0, 1);
	glRotatef(angleRightHand3, 1, 0, 0);

	//Right Upper Arm
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawRightUpperArm();
	glColor3f(0, 0, 0);
	drawLineRightUpperArm();
	glPopMatrix();

	//Right Lower Arm
	glPushMatrix();
	glTranslatef(-0.03, -1.1, 0.0);
	glRotatef(angleRightHand2, 0, 0, 0.1);
	glColor3f(1, 1, 1);
	drawRightLowerArm();
	glColor3f(0, 0, 0);
	drawLineRightLowerArm();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// <summary>
	/// LEFT HAND
	/// </summary>
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.18, -1, 0);

	//Left Hand Joint
	glPushMatrix();

	glScalef(0.4, 0.4, 0.4);
	glTranslatef(1.5, 2.5, 0.0);
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	GLUquadricObj* cylinderL2 = NULL;
	cylinderL2 = gluNewQuadric();
	glColor3f(1.0, 1.0, 1.0);
	gluQuadricDrawStyle(cylinderL2, GLU_FILL);
	gluCylinder(cylinderL2, 0.15, 0.15, 0.75, 20, 20);
	glColor3f(0.0, 0.0, 0.0);
	gluQuadricDrawStyle(cylinderL2, GLU_LINE);
	gluCylinder(cylinderL2, 0.15, 0.15, 0.75, 20, 20);
	gluDeleteQuadric(cylinderL2);
	glPopMatrix();

	glPopMatrix();

	//Left Arm
	glPushMatrix();

	glScalef(0.4, 0.4, 0.4);
	glTranslatef(1.5, 2.5, 0.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(angleLeftHand1, 0, 0, 1);
	glRotatef(-angleLeftHand3, 1, 0, 0);

	//Left Upper Arm
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawLeftUpperArm();
	glColor3f(0, 0, 0);
	drawLineLeftUpperArm();
	glPopMatrix();

	//Left Lower Arm
	glPushMatrix();
	glTranslatef(-0.03, -1.1, 0.0);
	glRotatef(angleLeftHand2, 0, 0, 0.1);
	glColor3f(1, 1, 1);
	drawLeftLowerArm();
	glColor3f(0, 0, 0);
	drawLineLeftLowerArm();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	//Right Leg
	glPushMatrix();

	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.225, -0.6, 0.025);
	glScalef(1.2, 1.1, 1.2);

	glPushMatrix();

	glScalef(0.35, 0.35, 0.35);
	glTranslatef(1.2, -0.5, 0.0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-angleRightLeg1, 0, 0, 1);

	//Upper Right Leg
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawRightUpperLeg();
	glColor3f(0, 0, 0);
	drawLineRightUpperLeg();
	glPopMatrix();

	//Right Lower Leg
	glPushMatrix();
	glTranslatef(0.00, -1.1, 0.0);
	glColor3f(1, 1, 1);
	drawRightLowerLeg();
	glColor3f(0, 0, 0);
	drawLineRightLowerLeg();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//Left Leg
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.1, -0.6, 0.025);
	glScalef(1.2, 1.1, 1.2);

	glPushMatrix();

	glScalef(0.35, 0.35, 0.35);
	glTranslatef(-0.7, -0.5, 0.0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-angleLeftLeg1, 0, 0, 1);

	//Upper Left Leg
	glPushMatrix();
	glColor3f(1, 1, 1);
	drawLeftUpperLeg();
	glColor3f(0, 0, 0);
	drawLineLeftUpperLeg();
	glPopMatrix();

	//Right Left Leg
	glPushMatrix();
	glTranslatef(0.00, -1.1, 0.0);
	glColor3f(1, 1, 1);
	drawLeftLowerLeg();
	glColor3f(0, 0, 0);
	drawLineLeftLowerLeg();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	drawHeadCylinder();
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (isPerspective) {
		gluPerspective(60, 1, 1, 50.0);
	}
	else {
		glOrtho(-5, 5, 0, 15, -0, 50);
		glTranslatef(0, 5, 0);
	}
	glMatrixMode(GL_MODELVIEW);

	////////LIGHT//////
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	////////END OF LIGHT/////////

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glLineWidth(1);
	glTranslatef(0, -0.5, -6);
	glRotatef(5, 1, 0, 0);
	glRotatef(angleScreen, 0, 1, 0);
	glPushMatrix();

	/////LIGHT//////
	glPushMatrix();

	glColor3f(1, 1, 0);
	glTranslatef(x, y, z);
	drawTextureCube(-0.01, -0.01, -0.01, 0.01, 0.01, 0.01);
	glPopMatrix();

	glEnable(GL_LIGHT0);
	if (openLight) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);

	glPopMatrix();

	glLineWidth(2);

	glPushMatrix();

	glTranslatef(camX, camY, camZ);

	glPushMatrix();

	glTranslatef(0, 4.15, -2);
	glScalef(2, 2, 2);

	glTranslatef(moveX, moveY, moveZ);
	glRotatef(angleRotate, 0, 1, 0);
	
	drawJaeger();

	glPopMatrix();

	

	/// <summary>
	/// DRAW BACKGROUND
	/// </summary>
	glPushMatrix();
	glScalef(1.5, 1.75, 1.5);
	drawFarmWarehouse();

	glPushMatrix();
	glTranslatef(-3.85, 0.5, -8);
	glRotatef(90, 0, 1, 0);

	displayAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.85, 0.5, -8);
	glRotatef(90, 0, 1, 0);
	displayAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.85, 0.5, 0);
	glRotatef(90, 0, 1, 0);
	displayAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.85, 0.5, 0);
	glRotatef(90, 0, 1, 0);
	displayAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.85, 0.5, 8);
	glRotatef(90, 0, 1, 0);
	displayAx();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.85, 0.5, 8);
	glRotatef(90, 0, 1, 0);
	displayAx();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//Open Head
	if (openHead) {
		if (angleHead < 20) {
			angleHead += 0.5;
		}
	}
	else {
		if (angleHead > 0) {
			angleHead -= 0.5;
		}
	}
	//Walk
	if (checkWalk == true) {

		moveY = 0.0;
		angleLeftHand3 = 0.0;
		angleRightHand3 = 0.0;
		if (walkCount == 0) {

			//hand
			angleLeftHand1 = -5;
			angleLeftHand2 = 5;
			angleRightHand1 = 5;
			angleRightHand2 = 5;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 10;
			angleRightLeg2 = -20;

		}
		else if (walkCount == 1) {

			//hand
			angleLeftHand1 = -15;
			angleLeftHand2 = 15;
			angleRightHand1 = 15;
			angleRightHand2 = 15;
			//leg
			angleLeftLeg1 = -5;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 20;
			angleRightLeg2 = -40;

		}
		else if (walkCount == 2) {

			//hand
			angleLeftHand1 = -25;
			angleLeftHand2 = 30;
			angleRightHand1 = 25;
			angleRightHand2 = 25;
			//leg
			angleLeftLeg1 = -10;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 30;
			angleRightLeg2 = -50;

		}
		else if (walkCount == 3) {

			//hand
			angleLeftHand1 = -15;
			angleLeftHand2 = 15;
			angleRightHand1 = 15;
			angleRightHand2 = 15;
			//leg
			angleLeftLeg1 = -15;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 20;
			angleRightLeg2 = -20;

		}
		else if (walkCount == 4) {

			//hand
			angleLeftHand1 = -5;
			angleLeftHand2 = 5;
			angleRightHand1 = 5;
			angleRightHand2 = 5;
			//leg
			angleLeftLeg1 = -5;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 10;
			angleRightLeg2 = -10;

		}
		else if (walkCount == 5) {

			movingXYZ(0.1);
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 0;
			angleRightHand1 = 0;
			angleRightHand2 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 6) {

			//hand
			angleLeftHand1 = 5;
			angleLeftHand2 = 5;
			angleRightHand1 = -5;
			angleRightHand2 = 5;
			//leg
			angleLeftLeg1 = 10;
			angleLeftLeg2 = -20;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 7) {

			//hand
			angleLeftHand1 = 15;
			angleLeftHand2 = 15;
			angleRightHand1 = -15;
			angleRightHand2 = 15;
			//leg
			angleLeftLeg1 = 20;
			angleLeftLeg2 = -40;
			angleRightLeg1 = -5;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 8) {

			//hand
			angleLeftHand1 = 25;
			angleLeftHand2 = 25;
			angleRightHand1 = -25;
			angleRightHand2 = 25;
			//leg
			angleLeftLeg1 = 30;
			angleLeftLeg2 = -50;
			angleRightLeg1 = -10;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 9) {

			//hand
			angleLeftHand1 = 15;
			angleLeftHand2 = 15;
			angleRightHand1 = -15;
			angleRightHand2 = 15;
			//leg
			angleLeftLeg1 = 20;
			angleLeftLeg2 = -20;
			angleRightLeg1 = -15;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 10) {

			//hand
			angleLeftHand1 = 5;
			angleLeftHand2 = 5;
			angleRightHand1 = -5;
			angleRightHand2 = 5;
			//leg
			angleLeftLeg1 = 10;
			angleLeftLeg2 = -10;
			angleRightLeg1 = -5;
			angleRightLeg2 = 0;

		}
		else if (walkCount == 11) {

			movingXYZ(0.1);
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 0;
			angleRightHand1 = 0;
			angleRightHand2 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}

		_sleep(50);
		walkCount++;
		if (walkCount > 11) {
			walkCount = 0;
			checkWalk = false;
		}

	}
	//Ulti 1: Shoryuken
	if (checkUlti1 == true) {

		if (ulti1Count == 0) {

			moveY = 0.05;
			angleRotate = -30;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 15;
			angleLeftHand3 = 10;
			angleRightHand1 = 0;
			angleRightHand2 = 15;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti1Count == 1) {

			moveY = 0.075;
			angleRotate = 00;
			//hand
			angleLeftHand1 = 20;
			angleLeftHand2 = 15;
			angleLeftHand3 = 25;
			angleRightHand1 = 0;
			angleRightHand2 = 30;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 20;
			angleRightLeg2 = -20;

		}
		else if (ulti1Count == 2) {

			moveY = 0.100;
			angleRotate = 60;
			//hand
			angleLeftHand1 = 40;
			angleLeftHand2 = 30;
			angleLeftHand3 = 35;
			angleRightHand1 = 0;
			angleRightHand2 = 60;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 50;
			angleRightLeg2 = -80;

		}
		else if (ulti1Count == 3) {

			moveY = 0.125;
			angleRotate = 90;
			//hand
			angleLeftHand1 = 70;
			angleLeftHand2 = 50;
			angleLeftHand3 = 25;
			angleRightHand1 = -5;
			angleRightHand2 = 80;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 70;
			angleRightLeg2 = -100;

		}
		else if (ulti1Count == 4) {

			moveY = 0.150;
			angleRotate = 120;
			//hand
			angleLeftHand1 = 110;
			angleLeftHand2 = 55;
			angleLeftHand3 = 10;
			angleRightHand1 = -10;
			angleRightHand2 = 100;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 90;
			angleRightLeg2 = -120;

		}
		else if (ulti1Count == 5) {

			moveY = 0.175;
			angleRotate = 150;
			//hand
			angleLeftHand1 = 180;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = -20;
			angleRightHand2 = 140;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = -0;
			angleRightLeg1 = 100;
			angleRightLeg2 = -120;
			checkWeapon = true;

		}
		else if (ulti1Count == 6) {

			_sleep(5);
			moveY = 0.2;
			angleRotate = 150;
			//hand
			angleLeftHand1 = 180;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = -20;
			angleRightHand2 = 140;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = -0;
			angleRightLeg1 = 100;
			angleRightLeg2 = -120;
			checkWeapon = true;

		}
		else if (ulti1Count == 7) {

			_sleep(5);
			moveY = 0.225;
			angleRotate = 150;
			//hand
			angleLeftHand1 = 180;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = -20;
			angleRightHand2 = 140;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = -0;
			angleRightLeg1 = 100;
			angleRightLeg2 = -120;
			checkWeapon = true;

		}
		else if (ulti1Count == 8) {

			moveY = 0.150;
			angleRotate = 180;
			//hand
			angleLeftHand1 = 110;
			angleLeftHand2 = 55;
			angleLeftHand3 = 10;
			angleRightHand1 = -10;
			angleRightHand2 = 100;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 90;
			angleRightLeg2 = -120;
			checkWeapon = false;

		}
		else if (ulti1Count == 9) {

			moveY = 0.125;
			angleRotate = 210;
			//hand
			angleLeftHand1 = 70;
			angleLeftHand2 = 50;
			angleLeftHand3 = 25;
			angleRightHand1 = -5;
			angleRightHand2 = 80;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 70;
			angleRightLeg2 = -100;

		}
		else if (ulti1Count == 10) {

			moveY = 0.100;
			angleRotate = 240;
			//hand
			angleLeftHand1 = 40;
			angleLeftHand2 = 30;
			angleLeftHand3 = 35;
			angleRightHand1 = 0;
			angleRightHand2 = 60;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 50;
			angleRightLeg2 = -80;

		}
		else if (ulti1Count == 11) {

			moveY = 0.075;
			angleRotate = 270;
			//hand
			angleLeftHand1 = 20;
			angleLeftHand2 = 15;
			angleLeftHand3 = 25;
			angleRightHand1 = 0;
			angleRightHand2 = 30;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 20;
			angleRightLeg2 = -20;

		}
		else if (ulti1Count == 12) {

			moveY = 0.05;
			angleRotate = 300;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 15;
			angleLeftHand3 = 10;
			angleRightHand1 = 0;
			angleRightHand2 = 15;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti1Count == 13) {

			moveY = 0.0;
			angleRotate = 330;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = 0;
			angleRightHand2 = 0;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti1Count == 14) {

			moveY = 0.0;
			angleRotate = 0;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = 0;
			angleRightHand2 = 0;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		_sleep(25);
		ulti1Count++;
		if (ulti1Count > 14) {
			ulti1Count = 0;
			checkUlti1 = false;
		}

	}
	//Ulti 2: Hurricane Kick
	if (checkUlti2 == true) {

		if (ulti2Count == 0) {

			moveY = 0.0;
			angleRotate = -30;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 70;
			angleLeftHand3 = 5;
			angleRightHand1 = 0;
			angleRightHand2 = 70;
			angleRightHand3 = 5;
			//leg
			angleLeftLeg1 = 45;
			angleLeftLeg2 = -50;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 1) {

			moveY = 0.05;
			angleRotate = 0;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = -100;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 2) {

			moveY = 0.1;
			angleRotate = 30;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = -50;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 3) {

			moveY = 0.15;
			angleRotate = 60;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 4) {

			moveY = 0.16;
			angleRotate = 90;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 5) {

			moveY = 0.17;
			angleRotate = 120;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 6) {

			moveY = 0.18;
			angleRotate = 150;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 7) {

			moveY = 0.19;
			angleRotate = 180;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 8) {

			moveY = 0.20;
			angleRotate = 210;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 8) {

			moveY = 0.21;
			angleRotate = 240;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 9) {

			moveY = 0.22;
			angleRotate = 270;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 10) {

			moveY = 0.23;
			angleRotate = 300;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 11) {

			moveY = 0.24;
			angleRotate = 330;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 12) {

			moveY = 0.24;
			angleRotate = 0;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 13) {

			moveY = 0.23;
			angleRotate = 30;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 14) {

			moveY = 0.22;
			angleRotate = 60;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 15) {

			moveY = 0.21;
			angleRotate = 90;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 16) {

			moveY = 0.20;
			angleRotate = 120;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 17) {

			moveY = 0.19;
			angleRotate = 150;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 18) {

			moveY = 0.18;
			angleRotate = 180;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 19) {

			moveY = 0.17;
			angleRotate = 210;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 20) {

			moveY = 0.16;
			angleRotate = 240;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 21) {

			moveY = 0.15;
			angleRotate = 270;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = -50;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 22) {

			moveY = 0.10;
			angleRotate = 300;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 140;
			angleLeftHand3 = 15;
			angleRightHand1 = 0;
			angleRightHand2 = 140;
			angleRightHand3 = 15;
			//leg
			angleLeftLeg1 = 90;
			angleLeftLeg2 = -100;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 23) {

			moveY = 0.05;
			angleRotate = 330;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 70;
			angleLeftHand3 = 5;
			angleRightHand1 = 0;
			angleRightHand2 = 70;
			angleRightHand3 = 5;
			//leg
			angleLeftLeg1 = 45;
			angleLeftLeg2 = -50;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}
		else if (ulti2Count == 24) {

			moveY = 0.0;
			angleRotate = 0;
			//hand
			angleLeftHand1 = 0;
			angleLeftHand2 = 0;
			angleLeftHand3 = 0;
			angleRightHand1 = 0;
			angleRightHand2 = 0;
			angleRightHand3 = 0;
			//leg
			angleLeftLeg1 = 0;
			angleLeftLeg2 = 0;
			angleRightLeg1 = 0;
			angleRightLeg2 = 0;

		}

		_sleep(15);
		ulti2Count++;
		if (ulti2Count > 24) {
			ulti2Count = 0;
			checkUlti2 = false;
		}

	}
	//Camera Rotate
	if (camRotateCW) {
		angleScreen += 1;
	}
	if (camRotateACW) {
		angleScreen -= 1;
	}
	//Bullet Fly
	if (checkBullet) {

		bulletZ -= 0.2;

		bulletCount++;
		if (bulletCount > 20) {
			checkBullet = false;
			bulletCount = 0;
			bulletZ = 0.0;
		}
	}
	else {
		bulletZ = 0;
	}

	angleGun += 10;
	headCylinderAngle += 3;

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}