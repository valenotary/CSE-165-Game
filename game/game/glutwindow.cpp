#include <iostream>
#include <stdlib.h>

#include "glutwindow.h"

static glutwindow* singleton;

glutwindow::glutwindow(int argc, char** argv, int width, int height, const char* title) {
	singleton = this;

	this->width = width;
	this->height = height;
	this->title = title;

	this->interval = 1000;
	this->timerOn = false;

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow(this->title);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(4);
	glLineWidth(2);


	// Set callback for drawing the scene
	glutDisplayFunc(glutDisplayCB);

	// Set callback for resizing th window
	glutReshapeFunc(glutResizeCB);

	// Set callback to handle mouse clicks
	glutMouseFunc(glutMouseCB);

	// Set callback to handle mouse dragging
	glutMotionFunc(glutMotionCB);

	// Set callback to handle keyboard down events
	glutKeyboardFunc(glutKeyDownCB);

	// Set callback to handle keyboard down events
	glutKeyboardUpFunc(glutKeyUpCB);

	// Set callback to handle special key down events
	glutSpecialFunc(glutSpecialKeyDownCB);

	// Set callback to handle special key up events
	glutSpecialUpFunc(glutSpecialKeyUpCB);

	// Setup callback for idle
	glutIdleFunc(glutIdleCB);

	//Setup timer function
	glutTimerFunc(interval, glutTimerCB, 0);

}

static void cleanup() {
	delete singleton;
}

void glutwindow::run() {
	//just tells us what to do when we exit, then calls the cleanup function to perform the exiting
	atexit(cleanup);

	glutMainLoop();
}

void glutwindow::redraw() {
	glutPostRedisplay();
}

void glutwindow::timerStart() {
	timerOn = true;
}

void glutwindow::timerSetInterval(int millis) {
	interval = millis;
}

void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(singleton->width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(singleton->height)));
}


void glutwindow::glutResizeCB(int w, int h) {
	// Window size has changed
	singleton->width = w;
	singleton->height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}

void glutwindow::glutDisplayCB() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw stuff here
	singleton->draw();

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

void glutwindow::glutKeyDownCB(unsigned char key, int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	singleton->keyDown(key, mx, my);
}

void glutwindow::glutKeyUpCB(unsigned char key, int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	singleton->keyUp(key, mx, my);
}

void glutwindow::glutMouseCB(int b, int s, int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	if (b == 0) {
		// Left button
		if (s == 0) {
			// Down
			singleton->leftMouseDown(mx, my);
		}
		else if (s == 1) {
			// Up
			singleton->leftMouseUp(mx, my);
		}
	}
	else if (b == 2) {
		// Right button
		if (s == 0) {
			// Down
			singleton->rightMouseDown(mx, my);
		}
		else if (s == 1) {
			// Up
			singleton->rightMouseUp(mx, my);
		}
	}
}

void glutwindow::glutMotionCB(int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	singleton->drag(mx, my);
}

void glutwindow::glutSpecialKeyDownCB(int key, int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	singleton->specialKeyDown(key, mx, my);
}

void glutwindow::glutSpecialKeyUpCB(int key, int x, int y) {
	// Convert from window to scene coordinates
	float mx = (float)x;
	float my = (float)y;
	windowToScene(mx, my);

	singleton->specialKeyUp(key, mx, my);
}

void glutwindow::glutIdleCB() {
	singleton->idle();
}


void glutwindow::glutTimerCB(int n) {
	if (singleton->timerOn) {
		singleton->timer();
		glutTimerFunc(singleton->interval, glutTimerCB, 0);
	}
}
