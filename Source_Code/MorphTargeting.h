#pragma once
#include "MathClass.h"
#include "objLoader.h"

static void morphTarget(objLoader *src, objLoader *start, objLoader *end, float dt);

//stores the info for each keyframe
struct MorphTargetInfo
{
	// need to know the WHICH keyframe is 
	//	referenced at the current moment
	// again, this is managed by whatever 
	//	is using this animation controller
	// **** 
	int index;

	// how long does this keyframe last?
	// **** 
	float duration;

	//the model used as the keyframe
	objLoader *target; 
};


//holds attributes that are needed for morphing
class morph
{
public:
	morph()
	{
		numFrames = 0;
		t = 0.0f;
		numFrames = 20;

		keyFrameIndex = 0;

		done = false;

		loop = true;
		doneAnimation = false;
	}

	~morph()
	{
	}

	void addKeyFrame(char *objfilename, int maxTriangles)
	{
		MorphTargetInfo temp;

		temp.target = new objLoader();
		temp.target->LoadOBJ(objfilename, maxTriangles, true);
		/*temp.index = index;
		temp.duration = duration;*/

		MorphInfo.push_back(temp);
	}

	//int numKeyFrames is the number of keyFrames that make up the animation
	//obj src is the current model/keyFrame being renderd
	//animate is used to animate a list of more than 2 keyframes
	void animate(int numKeyFrames, objLoader *src, float dt)
	{
		if(dt < 1.0f && !doneAnimation)
		{
			done = true;

			t += (dt*10) * 0.80f;
		
			//go to next keyFrame in the animation	
			if((t >= 1.0f) && (keyFrameIndex < numKeyFrames - 1))
			{

				keyFrameIndex++;
				t = 0;
			}
		
			//if we are on the last keyframe of the animation
			if(keyFrameIndex >= numKeyFrames - 1)
			{

				//loop from the last keyframe to the first keyframe of the animation
				if(loop)
				{
					morphTarget(src, MorphInfo[keyFrameIndex].target, MorphInfo[0].target, t);
				}
			
				//resets the animation
				if(t >= 1.0f)
				{
					if(loop)
					{
						reset();
					}
					else
					{
						doneAnimation = true;
					}
				}
			}

			//morph between keyframes
			else
			{
				morphTarget(src, MorphInfo[keyFrameIndex].target, MorphInfo[keyFrameIndex+1].target, t);
			}
		}
		
	}

	//int numKeyFrames is the number of keyFrames that make up the animation
	//obj src is the current model/keyFrame being renderd
	//animate2 is used to animate a list between 2 keyframes only
	void animate2(objLoader *src, objLoader *to, float dt)
	{
		if(done && dt < 1.0f)
		{
			/*if(keyFrameIndex > 0)
			{
				t += ((dt*10) * 0.25f)/keyFrameIndex;
			}
			else
			{
				t += ((dt*10) * 0.25f);
			}*/
			t += ((dt*10.0f) * 0.25f);
			
			//loop from the last keyframe to the first keyframe of the animation
			morphTarget(src, MorphInfo[keyFrameIndex].target, to, t);

			//resets the animation
			if(t >= 1.0f && loop)
			{
				done = false;
				reset();
			}

			
		}
				
	}
	
	//resets the animation to the first keyFrame
	void reset()
	{
		keyFrameIndex = 0;
		t = 0;
	}

	std::vector<MorphTargetInfo> MorphInfo;
	float t;
	int keyFrameIndex; 

	bool done;
	bool doneAnimation;

	int numFrames; //the number of frames between each keyframe, should be the same as in maya

	bool loop; //if the animaiton loops
};

//src is the current model that in being rendered
//dest is the model that needs to become the current model
static void morphTarget(objLoader *src, objLoader *start, objLoader *dest, float dt)
{
	int i = 0;
	for(int t = 0; t < src->numTriangles; t++, i+=9)
	{
		src->f_vertexIndex = src->model.triangle[t].t_vertexIndex;
		src->f_normalIndex = src->model.triangle[t].t_normalIndex;

		////first vertex of the triangle
		src->vertex[i]		 = LERP(start->model.points[src->f_vertexIndex.x-1].vertex.x, dest->model.points[src->f_vertexIndex.x-1].vertex.x, dt);
		src->vertex[i + 1]	 = LERP(start->model.points[src->f_vertexIndex.x-1].vertex.y, dest->model.points[src->f_vertexIndex.x-1].vertex.y, dt);
		src->vertex[i + 2]	 = LERP(start->model.points[src->f_vertexIndex.x-1].vertex.z, dest->model.points[src->f_vertexIndex.x-1].vertex.z, dt);

		src->normals[i]		 = LERP(start->model.points[src->f_normalIndex.x-1].normal.x, dest->model.points[src->f_normalIndex.x-1].normal.x, dt);
		src->normals[i + 1]	 = LERP(start->model.points[src->f_normalIndex.x-1].normal.y, dest->model.points[src->f_normalIndex.x-1].normal.y, dt);
		src->normals[i + 2]	 = LERP(start->model.points[src->f_normalIndex.x-1].normal.z, dest->model.points[src->f_normalIndex.x-1].normal.z, dt);
																  
		////second vertex of the triangle						  
		src->vertex[i + 3]	 = LERP(start->model.points[src->f_vertexIndex.y-1].vertex.x, dest->model.points[src->f_vertexIndex.y-1].vertex.x, dt);
		src->vertex[i + 4]	 = LERP(start->model.points[src->f_vertexIndex.y-1].vertex.y, dest->model.points[src->f_vertexIndex.y-1].vertex.y, dt);
		src->vertex[i + 5]	 = LERP(start->model.points[src->f_vertexIndex.y-1].vertex.z, dest->model.points[src->f_vertexIndex.y-1].vertex.z, dt);

		src->normals[i + 3]	 = LERP(start->model.points[src->f_normalIndex.y-1].normal.x, dest->model.points[src->f_normalIndex.y-1].normal.x, dt);
		src->normals[i + 4]	 = LERP(start->model.points[src->f_normalIndex.y-1].normal.y, dest->model.points[src->f_normalIndex.y-1].normal.y, dt);
		src->normals[i + 5]	 = LERP(start->model.points[src->f_normalIndex.y-1].normal.z, dest->model.points[src->f_normalIndex.y-1].normal.z, dt);
																  
		////third vertex of the triangle						  
		src->vertex[i + 6]	 = LERP(start->model.points[src->f_vertexIndex.z-1].vertex.x, dest->model.points[src->f_vertexIndex.z-1].vertex.x, dt);
		src->vertex[i + 7]	 = LERP(start->model.points[src->f_vertexIndex.z-1].vertex.y, dest->model.points[src->f_vertexIndex.z-1].vertex.y, dt);
		src->vertex[i + 8]	 = LERP(start->model.points[src->f_vertexIndex.z-1].vertex.z, dest->model.points[src->f_vertexIndex.z-1].vertex.z, dt);

		src->normals[i + 6]	 = LERP(start->model.points[src->f_normalIndex.z-1].normal.x, dest->model.points[src->f_normalIndex.z-1].normal.x, dt);
		src->normals[i + 7]	 = LERP(start->model.points[src->f_normalIndex.z-1].normal.y, dest->model.points[src->f_normalIndex.z-1].normal.y, dt);
		src->normals[i + 8]	 = LERP(start->model.points[src->f_normalIndex.z-1].normal.z, dest->model.points[src->f_normalIndex.z-1].normal.z, dt);

	}

	src->vbo->AddVertices(src->vertex);
	src->vbo->AddNormals(src->normals);
}

