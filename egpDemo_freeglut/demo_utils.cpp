#include "demo_utils.h"


#include "GL/glew.h"



void demo::drawTestTriangle()
{
	// immediate mode coloured triangle... DO NOT USE IMMEDIATE MODE!!!!
	glBegin(GL_TRIANGLES);
		glColor3f(  1.0f, 0.0f, 0.0f   );
		glVertex3f( -0.4f, -0.5f, -0.5f);
		glColor3f(  0.0f, 1.0f, 0.0f   );
		glVertex3f( 0.4f, -0.5f, 0.0f  );
		glColor3f(  0.0f, 0.0f, 1.0f   );
		glVertex3f( 0.0f, 0.5f, 1.0f  );
	glEnd();
}

void demo::drawTestRect()
{
	// immediate mode coloured rectangle... DO NOT USE IMMEDIATE MODE!!!!
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f( 0.0f, 0.0f, 1.0f  );
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f( 1.0f, 0.0f, 1.0f  );
		glVertex3f(0.5f, -0.5f, 0.0f );
		glColor3f( 0.0f, 1.0f, 1.0f  );
		glVertex3f(-0.5f, 0.5f, 0.0f );
		glColor3f( 1.0f, 1.0f, 1.0f  );
		glVertex3f(0.5f, 0.5f, 0.0f  );
	glEnd();
}

void demo::drawTestAxes()
{
	// immediate mode axes; r = x, g = y, b = z... DO NOT USE IMMEDIATE MODE!!!!
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


// default indices for attributes
// these are what OpenGL uses for built-in attributes
// if you align your data correctly with these, you 
//	will not need to use a shader (programmed pipe)!!!
enum ATTRIB_INDEX
{
	A_POSITION,
	A_BLANK1,
	A_NORMAL,
	A_COLOR0,
	A_COLOR1,
	A_BLANK2,
	A_PTSZ,
	A_BLANK3,
	A_TEXCOORD0,

	ATTRIB_COUNT	// 16
};



// PART 1A: start using draw arrays
void demo::drawTriangleAttribs()
{
	
	const float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	
	const float verts[]=
	{
		-0.4f, -0.5f, -0.5f,		
		0.4f, -0.5f, 0.0f,		
		0.0f, 0.5f, 1.0f 
	};

	//enable "retained" drawing
	glEnableVertexAttribArray(A_POSITION);
	glEnableVertexAttribArray(A_COLOR0);

	//send data to GPU
	glVertexAttribPointer(A_POSITION, 3, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(A_COLOR0, 3, GL_FLOAT, GL_FALSE, 0, colors);

	//draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//disable retained
	glDisableVertexAttribArray(A_POSITION);
	glDisableVertexAttribArray(A_COLOR0);
}

void demo::drawSquareAttribs()
{
	const float colors[] =
	{
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	
	const float verts[] =
	{
		- 0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		- 0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
		
	//enable "retained" drawing
	glEnableVertexAttribArray(A_POSITION);
	glEnableVertexAttribArray(A_COLOR0);

	//send data to GPU
	glVertexAttribPointer(A_POSITION, 3, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(A_COLOR0, 3, GL_FLOAT, GL_FALSE, 0, colors);

	//draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//disable retained
	glDisableVertexAttribArray(A_POSITION);
	glDisableVertexAttribArray(A_COLOR0);
}



//-----------------------------------------------------------------------------
// PART 1B: general vbo
unsigned int demo::createMultipleVBOs(unsigned int numVerts, unsigned int attribCount, const float **data, unsigned int *handlesOut)
{
	const unsigned sizeofFloat = sizeof(float);
	const unsigned int floatsPerAttrib = 3;

	if ((numVerts > 0) && (attribCount > 0) && (attribCount <= 16) && data && handlesOut)
	{
		//create buffers per attrib
		//per each attrib
		//send data to GPU

		glGenBuffers(attribCount, handlesOut);

		for (unsigned int i = 0; i < attribCount; ++i)
		{
			glBindBuffer(GL_ARRAY_BUFFER, handlesOut[i]);

			//total bytes = num verts * elems * bytesPerElem
			glBufferData(GL_ARRAY_BUFFER, numVerts * floatsPerAttrib * sizeofFloat, data[i], GL_STATIC_DRAW);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return attribCount;
	}

	// failed
	return 0;
}

void demo::drawMultipleVBOs(unsigned int numVerts, unsigned int attribCount, unsigned int primType, const unsigned int *handles, const unsigned int *attribIndex)
{
	const unsigned sizeofFloat = sizeof(float);
	const unsigned int floatsPerAttrib = 3;

	if ((numVerts > 0) && (attribCount > 0) && (attribCount <= 16) && handles && attribIndex)
	{
		//enable and setup
		for (unsigned int i = 0; i < attribCount; ++i)
		{
			//activate attrib buffer
			glBindBuffer(GL_ARRAY_BUFFER, handles[i]);

			//enable it
			glEnableVertexAttribArray(attribIndex[i]);

			//config
			glVertexAttribPointer(attribIndex[i], 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		//draw
		glDrawArrays(primType, 0, numVerts);
		
		//disable
		for (unsigned int i = 0; i < attribCount; ++i)
		{
			glDisableVertexAttribArray(attribIndex[i]);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void demo::deleteMultipleVBOs(unsigned int attribCount, unsigned int *handles)
{
	if (attribCount && handles)
		glDeleteBuffers(attribCount, handles);
}


