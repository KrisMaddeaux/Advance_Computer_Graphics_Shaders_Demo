#pragma once 
#include "Include\CBMini\CBMiniFW.h"
#include "texture.h"
#include "Include/SFML/Graphics.hpp"
#include "Include/SFML/OpenGL.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "MathClass.h"
#include <list>

//First, let’s create a data structure to hold our object's data
typedef struct objData
{
	Vec3f vertex;
	Vec3f normal;
	Vec3f uvCoord;
}DATA;

//Then, our simplest primitive: a triangle (stores the indinces of the data)
typedef struct objTriangles
{
	sf::Vector3i t_vertexIndex;
	sf::Vector3i t_uvIndex;
	sf::Vector3i t_normalIndex;
}TRIANGLE;

//Finally, our object
typedef struct objOject
{
	int maxTriangles;
	TRIANGLE *triangle;
	DATA *points; 
}OBJECT;

/////////////////////////////////////////////////////////////////////////////////

class objLoader
{
public:
	objLoader()
	{
		numTriangles = 0;
		vbo = new cbmini::cbfw::VertexBuffer;
	}
	~objLoader()
	{
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadOBJ(char *filename, int maxTriangles, bool morphTarget = false)
	{	
		objFile = fopen(filename, "r");
		//When the file cannot be opened (e.g., we don't have permission or it doesn't exist when opening for reading), fopen() will return NULL.
		if (objFile == NULL)
		{
			std::cout << "ERROR, could not open OBJ file" << std::endl;
			//fclose(objFile);
			return;
		}

		model.triangle = new TRIANGLE[maxTriangles + 5];	//plus 5 to prevent stack overflow
		model.points = new DATA[maxTriangles * 3]; 
		model.maxTriangles = maxTriangles;

		//dynamically intialize arrays, saves memory
		vertex = new float[(maxTriangles * 3) * 3]; 
		normals = new float[(maxTriangles * 3) * 3];
		texcoords = new float[(maxTriangles * 3) * 2];

		vertexIndex = 0;
		normalIndex = 0;
		uvIndex = 0;
		_textUV.z = 0.0f;

		
		while(1)	//while true
		{
			int res = fscanf(objFile, "%s", line);
			//checks for end of file (EOF)
			if(res == EOF)
			{
				break;
			}

			//vertices
			else if(strcmp(line, "v") == 0)
			{
				fscanf(objFile, "%f %f %f\n", &XYZ.x, &XYZ.y, &XYZ.z);
				model.points[vertexIndex].vertex = XYZ;
				vertexIndex++;
			}
			//texture coordinates
			else if(strcmp(line, "vt") == 0)
			{
				fscanf(objFile, "%f %f\n", &_textUV.x, &_textUV.y);
				model.points[uvIndex].uvCoord = _textUV;
				uvIndex++;
			}

			//normals
			else if(strcmp(line, "vn") == 0)
			{
				fscanf(objFile, "%f %f %f\n", &_normal.x, &_normal.y, &_normal.z);
				model.points[normalIndex].normal = _normal; 
				normalIndex++;
			}

			//faces
			else if(strcmp(line, "f") == 0)
			{
				int triangluated = fscanf(objFile, "%i/%i/%i %i/%i/%i %i/%i/%i\n", &f_vertexIndex.x, &f_uvIndex.x, &f_normalIndex.x, &f_vertexIndex.y, &f_uvIndex.y, &f_normalIndex.y, &f_vertexIndex.z, &f_uvIndex.z, &f_normalIndex.z);
				//checks to see if the model is triangulated
				if(triangluated%3 != 0)
				{
					cout << "ERROR, file is not triangulated" << endl;
					return;
				}

				model.triangle[numTriangles].t_vertexIndex = f_vertexIndex;
				model.triangle[numTriangles].t_uvIndex = f_uvIndex;
				model.triangle[numTriangles].t_normalIndex = f_normalIndex;

				numTriangles++;
			}
			
		}

		//sort into arrays to be rendered
		int i = 0;
		int k = 0;
		int t = 0;
		for(; t < numTriangles; t++, i+=9, k+=6)
		{
			f_vertexIndex = model.triangle[t].t_vertexIndex;
			f_uvIndex = model.triangle[t].t_uvIndex;
			f_normalIndex = model.triangle[t].t_normalIndex;

			//first vertex
			normals[i] = model.points[f_normalIndex.x-1].normal.x;	
			normals[i + 1] = model.points[f_normalIndex.x-1].normal.y;
			normals[i + 2] = model.points[f_normalIndex.x-1].normal.z;
				
			texcoords[k] = model.points[f_uvIndex.x-1].uvCoord.x;
			texcoords[k + 1] = model.points[f_uvIndex.x-1].uvCoord.y;

			vertex[i] = model.points[f_vertexIndex.x-1].vertex.x;
			vertex[i + 1] = model.points[f_vertexIndex.x-1].vertex.y;
			vertex[i + 2] = model.points[f_vertexIndex.x-1].vertex.z;
				
			//second vertex
			normals[i + 3] = model.points[f_normalIndex.y-1].normal.x;	
			normals[i + 4] = model.points[f_normalIndex.y-1].normal.y;
			normals[i + 5] = model.points[f_normalIndex.y-1].normal.z;
				
			texcoords[k + 2] = model.points[f_uvIndex.y-1].uvCoord.x;
			texcoords[k + 3] = model.points[f_uvIndex.y-1].uvCoord.y;

			vertex[i + 3] = model.points[f_vertexIndex.y-1].vertex.x;
			vertex[i + 4] = model.points[f_vertexIndex.y-1].vertex.y;
			vertex[i + 5] = model.points[f_vertexIndex.y-1].vertex.z;

			//third vertex
			normals[i + 6] = model.points[f_normalIndex.z-1].normal.x;	
			normals[i + 7] = model.points[f_normalIndex.z-1].normal.y;
			normals[i + 8] = model.points[f_normalIndex.z-1].normal.z;
				
			texcoords[k + 4] = model.points[f_uvIndex.z-1].uvCoord.x;
			texcoords[k + 5] = model.points[f_uvIndex.z-1].uvCoord.y;

			vertex[i + 6] = model.points[f_vertexIndex.z-1].vertex.x;
			vertex[i + 7] = model.points[f_vertexIndex.z-1].vertex.y;
			vertex[i + 8] = model.points[f_vertexIndex.z-1].vertex.z;
		}
		
		if(!morphTarget){
			vbo->Initialize(numTriangles * 3, true, true, false, false);
		}
		else{
			vbo->Initialize(numTriangles * 3, true, true, false, true);
		}
		vbo->AddVertices(vertex);
		vbo->AddNormals(normals);
		vbo->AddTexcoords(texcoords);

		fclose(objFile);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	void drawModel()
	{
		vbo->ActivateAndRender();
		vbo->Deactivate();
	}

	cbmini::cbfw::VertexBuffer *vbo;

	//these arrays represent the final sorted data to be sent to the vbo
	float *vertex; //3 values per vertex
	float *normals;//3 values per vertex
	float *texcoords;//2 values per vertex

	int vertexIndex;
	int numTriangles;
	int normalIndex;
	int uvIndex;

	//for loading data from file
	OBJECT model;
	FILE *objFile;
	Vec3f XYZ;
	Vec3f _normal;
	Vec3f _textUV;
	sf::Vector3i f_vertexIndex;	
	sf::Vector3i f_uvIndex;
	sf::Vector3i f_normalIndex;
	char line[255];
	char info;	//info that is needed to determine where the input will be stored. 
};

