#include "Camera.h"

OrthoCamera::OrthoCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float imgSize){
	    this->center = center;
	    this->w = direction.normalized();
	    this->u = (Vector3f::cross(w, up)).normalized();
	    this->v = (Vector3f::cross(this->u, this->w)).normalized();
	    this->imgSize = imgSize;
}

Ray OrthoCamera::generateRay( const Vector2f& point){
	    Vector3f start = this->center + this->v*point[0]*this->imgSize/2.0f + this->u*point[1]*imgSize/2.0f;
	    Ray r = Ray(start, this->w);
	    return r;
}
