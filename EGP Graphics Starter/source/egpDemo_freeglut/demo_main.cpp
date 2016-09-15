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
const char *win_name = "EGP Graphics Demo Window - D. Buckstein";
const char win_close = 27;	// escape key closes window

double fps = 30.0;
double spf = 1.0 / fps;
double mspf = 1000.0 / fps;



//-----------------------------------------------------------------------------
// our game objects
// good practice: default values for everything

////****VBO handles for 1B
unsigned int testSquareVBOs[16] = { 0 };
const unsigned int testSquareAttribs[16] = { demo::A_POSITION, demo::A_COLOR0 };


////****VBO handle for 2A, 2B, 2C
unsigned int testSquareInterleavedVBO = 0;


////****VAO handle for 2B, 2C
unsigned int testSquareVAO = 0;


////****IBO handle for 2C
unsigned int testSquareIBO = 0;



//-----------------------------------------------------------------------------
// game functions

// initialize game objects
//	****mainly for good memory management, handling ram and vram
int initGame()
{
	////****SETUP 1B
	const float vertices[] =
	{
		-0.75f, -0.75f, -0.75f,	// bottom left
		0.75f, -0.75f, -0.75f,	// bottom right
		-0.75f,  0.75f, -0.75f,	// top left
		0.75f,  0.75f, -0.75f,	// top right
	};

	const float colours[] =
	{
		0.5f, 0.5f, 0.5f,		// grey
		1.0f, 0.5f, 0.5f,		// pale red
		0.5f, 1.0f, 0.5f,		// pale green
		1.0f, 1.0f, 0.5f,		// pale yellow
	};

	// stuff both of the above into one array
	const float *allAttribData[2] = { vertices, colours };

	// create VBO
	demo::createMultipleVBOs(4, 2, allAttribData, testSquareVBOs);


	////****SETUP 2A using above data
//	testSquareInterleavedVBO = demo::createInterleavedVBO(4, 2, allAttribData);


	////****SETUP 2B using above; comment out 2A
//	testSquareVAO = demo::createVAO(4, 2, allAttribData, testSquareAttribs, &testSquareInterleavedVBO);


	////****SETUP 2C using above; comment out 2B
//	const unsigned int indices[] = {};

	// create VAO, VBO and IBO
//	testSquareVAO = demo::createIndexedVAO(4, 6, 2, allAttribData, 
//		testSquareAttribs, indices, &testSquareInterleavedVBO, &testSquareIBO);


	// done
	return 1;
}

// destroy game objects (mem)
int termGame()
{
	// good practice to do this in reverse order of creation
	//	in case something is referencing something else

	////****CLEAN 2C
	demo::deleteBufferObject(testSquareIBO);


	////****CLEAN 2B/2C
	demo::deleteVAO(testSquareVAO);


	////****CLEAN 2A/2B/2C
	demo::deleteBufferObject(testSquareInterleavedVBO);


	////****CLEAN 1B
	demo::deleteMultipleVBOs(2, testSquareVBOs);


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



	// test immediate mode
//	demo::drawTestTriangle();
//	demo::drawTestRect();
//	demo::drawTestAxes();



	////****TEST 1A
//	demo::drawTriangleAttribs();
//	demo::drawSquareAttribs();


	////****TEST 1B
	demo::drawMultipleVBOs(4, 2, GL_TRIANGLE_STRIP, testSquareVBOs, testSquareAttribs);


	////****TEST 2A
//	demo::drawInterleavedVBO(4, 2, GL_TRIANGLE_STRIP, testSquareInterleavedVBO, testSquareAttribs);


	////****TEST 2B
//	demo::drawVAO(4, GL_TRIANGLE_STRIP, testSquareVAO);


	////****TEST 2C
//	demo::drawIndexedVAO(6, GL_TRIANGLES, GL_UNSIGNED_INT, testSquareVAO);


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
