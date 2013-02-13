#include "Plane.h"

using namespace std;

Plane::Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
	this->normal = normal.normalized();
	this->d = d;
}

bool Plane::intersect( const Ray& r , Hit& h , float tmin){
	//Ray-Plane Intersection
	//t = -(D + n . R_o) / (n . R_d)


	Vector3f R_o = r.getOrigin();
	Vector3f R_d = r.getDirection().normalized();
	float nDotR_d = Vector3f::dot(this->normal, R_d);

	if (nDotR_d == 0){
	    return false;
	}

	float nDotR_o = Vector3f::dot(this->normal, R_o);
	float t = -1.0*(-1.0*this->d + nDotR_o)/(nDotR_d);

	if (t > tmin && t < h.getT()){
	    h.set(t, this->material, this->normal);
	    return true;	
	} 
	else{
	    return false;
	} 	
}
