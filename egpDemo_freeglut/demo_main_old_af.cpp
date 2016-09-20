///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////	EGP Graphics Demo using Freeglut
////	By Dan Buckstein
////	August 2016
////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "IL/ilut.h"

#include "demo_utils.h"



//-----------------------------------------------------------------------------
// globals

int win_x = 0;
int win_y = 0;
int win_w = 1280;
int win_h = 720;
int win_handle;
float win_aspect;
const char *win_name = "EGP Graphics Demo Window - T. Van Ollefen";
const char win_close = 27;	// escape key closes window

double fps = 60.0;
double spf = 1.0 / fps;
double mspf = 1000.0 / fps;

unsigned int handles[16];
unsigned int attribIndex[] = { 0, 3 };



//-----------------------------------------------------------------------------
// game functions

// initialize game objects
//	****mainly for good memory management, handling ram and vram
int initGame()
{
	const float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	const float verts[] =
	{
		-0.4f, -0.5f, -0.5f,
		0.4f, -0.5f, 0.0f,
		0.0f, 0.5f, 1.0f
	};

	const float *data[] = { verts, colors };
	demo::createMultipleVBOs(3, 2, data, handles);
	// done
	return 1;
}

// destroy game objects (mem)
int termGame()
{
	demo::deleteMultipleVBOs(2, handles);
	// done
	return 1;
}


// game update to perform each frame
void update(float dt)
{
	// update game state using the time since the last update (dt) in seconds
}

// draw frame
//	****DRAWING AND UPDATING SHOULD BE SEPARATE (good practice)
void render()
{
	// typically begin frame by clearing buffers
	// alternatively, just redraw the background - clearing is expensive :)



	//demo::drawTestTriangle();
	//demo::drawTestRect();
	//demo::drawTestAxes();

	//demo::drawTriangleAttribs();
	//demo::drawSquareAttribs();
	
	demo::drawMultipleVBOs(3, 2, GL_TRIANGLES, handles, attribIndex);


	// end frame by swapping buffers
	glutSwapBuffers();
}



//-----------------------------------------------------------------------------
// callbacks

// display - refers to the actual display refreshing, not draw time
void onDisplay()
{
	// ****DO NOT USE
}

// trigger new frame
void onTimer(int value)
{
	// trigger update and render
	update((float)spf);
	render();

	// reset timer
	glutTimerFunc((int)mspf, onTimer, 1);
}

// window closed
void onCloseWindow()
{
	// clean up
	termGame();
}

// window resized
void onResizeWindow(int w, int h)
{
	win_w = w;
	win_h = h;
	win_aspect = ((float)w) / ((float)h);
}

// window moved
void onPositionWindow(int x, int y)
{
	win_x = x;
	win_y = y;
}

// key pressed (with cursor position)
void onKeyboard(unsigned char key, int x, int y)
{
	if (key != win_close)
	{

	}
	else
	{
		// quit button pressed, stop game loop
		glutLeaveMainLoop();
	}
}

// key released
void onKeyboardUp(unsigned char key, int x, int y)
{

}

// mouse button pressed or released (with cursor)
void onMouseButton(int button, int state, int x, int y)
{

}

// mouse moved
void onMouseMove(int x, int y)
{

}



//-----------------------------------------------------------------------------
// core functions

// initialize OpenGL using freeglut and GLEW
int initGL(int argc, char **argv)
{
	// create a window with double-buffering, RGBA colour and depth buffer
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(win_x, win_y);
	glutInitWindowSize(win_w, win_h);
	win_handle = glutCreateWindow(win_name);

	// check version
	int version[2];
	glGetIntegerv(GL_MAJOR_VERSION, version);
	glGetIntegerv(GL_MINOR_VERSION, version + 1);
	printf("\n GL version: %d.%d", *(version), *(version + 1));

	// initialize extensions
	int init = glewInit();
	if (init == GLEW_OK)
	{
		// check version again to confirm initialization was successful
		// should be higher than the previous check if default is not highest
		glGetIntegerv(GL_MAJOR_VERSION, version);
		glGetIntegerv(GL_MINOR_VERSION, version + 1);
		printf("\n GL version: %d.%d", *(version), *(version + 1));

		// set callbacks
		glutDisplayFunc(onDisplay);
		glutTimerFunc(0, onTimer, 0);
		glutCloseFunc(onCloseWindow);
		glutReshapeFunc(onResizeWindow);
		glutPositionFunc(onPositionWindow);
		glutKeyboardFunc(onKeyboard);
		glutKeyboardUpFunc(onKeyboardUp);
		glutMouseFunc(onMouseButton);
		glutMotionFunc(onMouseMove);
		glutPassiveMotionFunc(onMouseMove);

		// set states
		// backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		// turn off depth (for now)
		glDisable(GL_DEPTH_TEST);
	//	glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		// alpha blending
		// result = ( new*[new alpha]) + (old*[1 - new alpha] )
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// done
		return 1;
	}
	
	// fail
	return 0;
}

// initialize third-party image handling using DevIL
int initIL()
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	// done
	return 1;
}

// entry function
int main(int argc, char **argv)
{
	// initialize graphics library
	if (initGL(argc, argv))
	{
		// initialize image library
		if (initIL())
		{
			// initialize game objects (pre-start)
			if (initGame())
			{
				// start loop (launch game)
				glutMainLoop();
			}
		}
	}

//	printf("\n\n");
//	system("pause");
}



//-----------------------------------------------------------------------------
