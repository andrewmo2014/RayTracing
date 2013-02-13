#include "Sphere.h"

using namespace std;

bool Sphere::intersect( const Ray& r , Hit& h , float tmin){
	    //Ray-Sphere Intersection
	    //t = (-b +- sqrt(b^2 - 4ac)) / 2a
	    //a = (R_d . R_d)
	    //b = 2(R_d . R_o)
	    //c = (R_o . R_o) - r^2

	    Vector3f R_o = r.getOrigin() - this->center;
	    Vector3f R_d = r.getDirection();
		
	    float a = R_d.absSquared();
	    float b = 2.0*Vector3f::dot(R_d, R_o);
	    float c = R_o.absSquared() - pow(this->radius, 2);
	    float discrim = pow(b,2) - (4*a*c);

	    if (discrim >= 0){

		//Want closest positive, therefore try t(-) first
	        float t = (-1.0*b - sqrt(discrim)) / (2.0*a);
		if (t >= tmin && t <= h.getT()){
		    Vector3f normalNew = (r.getOrigin() + t*R_d - this->center).normalized();
		    h.set(t, this->material, normalNew);
		    return true;
		}

		//Then try t(+)
		t = (-1.0*b + sqrt(discrim)) / (2.0*a);
		if (t >= tmin && t <= h.getT()){
		    Vector3f normalNew = (r.getOrigin() + t*R_d - this->center).normalized();
		    h.set(t, this->material, normalNew);
		    return true;
		}
	    }
	    return false;
}
