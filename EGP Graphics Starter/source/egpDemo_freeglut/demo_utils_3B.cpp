#include "demo_utils.h"


#include "GL/glew.h"




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// PART 2A: create interleaved VBO
unsigned int demo::createInterleavedVBO(unsigned int numVerts, unsigned int attribCount, const float **data)
{
	const unsigned int sizeoffloat = sizeof(float);
	const unsigned int floatsPerAttrib = 3;
	unsigned int numFloats, floatsPerVertex;

	// validate
	if ((numVerts > 0) && (attribCount > 0) && (attribCount <= ATTRIB_COUNT) && (data))
	{
		//create

		unsigned int handle;
		glGenBuffers(1, &handle);

		//bind
		glBindBuffer(GL_ARRAY_BUFFER, handle);

		//create array for attribute datas
		//number of floats = numVerts * numAttribs * numFloatsPerAttrib
		//**not all attribs have 3 floats
		numFloats = numVerts * attribCount * floatsPerAttrib;
		float *interleavedData = new float[numFloats];

		//num floats for single vertex
		//the stride
		floatsPerVertex = attribCount * floatsPerAttrib;

		//iter through attribs and copy data
		//count attribs, index to where each attrib starts
		for (unsigned int i = 0, attribStart = 0;
			i < attribCount;
			++i, attribStart += floatsPerAttrib)
		{
			const float *dataPtr = data[i];

			for (unsigned int j = 0,
				interleavedIndex = attribStart, rawDataIndex = 0;
				j < numVerts;
				++j, interleavedIndex += (floatsPerVertex - floatsPerAttrib))
			{
				//copy data
				interleavedData[interleavedIndex++] = dataPtr[rawDataIndex++];
				interleavedData[interleavedIndex++] = dataPtr[rawDataIndex++];
				interleavedData[interleavedIndex++] = dataPtr[rawDataIndex++];
			}
		}

		glBufferData(GL_ARRAY_BUFFER, (numFloats * sizeoffloat),
			interleavedData, GL_STATIC_DRAW);

		//unbind and delete
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		delete[] interleavedData;
	
		//success
		return handle;
	}
	return 0;
}

void demo::drawInterleavedVBO(unsigned int numVerts, unsigned int attribCount, 
	unsigned int primType, unsigned int handle, const unsigned int *attribIndex)
{
	const unsigned int sizeoffloat = sizeof(float);
	const unsigned int floatsPerAttrib = 3;

	if ((numVerts > 0) && (attribCount > 0) && (attribCount <= ATTRIB_COUNT) && 
		handle && attribIndex)
	{
		
	}
}

void demo::deleteBufferObject(unsigned int handle)
{
	if (handle)
	{
		glDeleteBuffers(1, &handle);
	}
}



//-----------------------------------------------------------------------------
// PART 2B: tie interleaved VBO to VAO and draw VAO
unsigned int demo::createVAO(unsigned int numVerts, unsigned int attribCount, 
	const float **data, const unsigned int *attribIndex, unsigned int *vboHandleOut)
{
	const unsigned int sizeoffloat = sizeof(float);
	const unsigned int floatsPerAttrib = 3;

	if (vboHandleOut)
	{
		
	}
	
	// fail
	return 0;
}

void demo::drawVAO(unsigned int numVerts, unsigned int primType, unsigned int vaoHandle)
{
	// the VAO is already configured, so just bind it and call draw!
	if (numVerts && vaoHandle)
	{
		
	}
}

void demo::deleteVAO(unsigned int handle)
{
	if (handle)
	{
		
	}
}



//-----------------------------------------------------------------------------
// PART 2C: create VAO with IBO
unsigned int demo::createIndexedVAO(unsigned int numVerts, unsigned int numIndices, 
	unsigned int attribCount, const float **data, const unsigned int *attribIndex, 
	const unsigned int *indexData, unsigned int *vboHandleOut, unsigned int *iboHandleOut)
{
	return 0;
}

void demo::drawIndexedVAO(unsigned int numIndices, unsigned int primType, 
	unsigned int indexType, unsigned int vaoHandle)
{
	if (numIndices && vaoHandle)
	{
		
	}
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
