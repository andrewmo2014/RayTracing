#include "Camera.h"

PerspectiveCamera::PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){
	    this->center = center;
	    this->w = direction.normalized();
	    this->u = (Vector3f::cross(w, up)).normalized();
	    this->v = (Vector3f::cross(this->u, this->w)).normalized();
	    this->angle = angle;
}

Ray PerspectiveCamera::generateRay( const Vector2f& point){
	    float alpha = 1.0f/tan(this->angle/2.0f);
	    Vector3f rayDirect = (((this->v*point[0] + this->u*point[1])) + alpha*this->w).normalized();
	    Ray r = Ray(this->center, rayDirect);
	    return r;
}
