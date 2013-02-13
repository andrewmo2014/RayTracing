#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f center; 
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;

};

class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle);

	virtual Ray generateRay( const Vector2f& point);

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
	Vector3f center; 
	Vector3f w;
	Vector3f u;
	Vector3f v;
	float angle;

};

class OrthoCamera: public Camera
{
public:
	OrthoCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float imgSize);

	virtual Ray generateRay( const Vector2f& point);

	virtual float getTMin() const { 
		return -FLT_MAX;
	}

private:
	Vector3f center; 
	Vector3f w;
	Vector3f u;
	Vector3f v;
	float imgSize;

};

#endif //CAMERA_H
