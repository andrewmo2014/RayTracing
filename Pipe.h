#ifndef PIPE_H
#define PIPE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;


class Pipe: public Object3D
{
public:
	Pipe(){ 
	}

	Pipe( Vector3f center , float height, float innerR, float outerR, Material* material ):Object3D(material){
	    this->center = center;
	    this->height = height;
	    this->innerR = innerR;
	    this->outerR = outerR;
	    this->material = material;
	}

	~Pipe(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin);

protected:

	Vector3f center;
	float height;
	float innerR;
	float outerR;
};


#endif
