#include "Pipe.h"

using namespace std;

//Helper Functions
bool intersectCylinder( const Ray& r , const Vector3f& center, float radius, float height, float& t, Vector3f& normal){
	    //Ray- Finite Cylinder Intersection
	    //t = (-b +- sqrt(b^2 - 4ac)) / 2a
	    //a = (R_dx)^2 + (R_dz)^2
	    //b = 2(R_dx)(R_ox) + 2(R_dz)(R_oz)
	    //c = (R_ox)(R_ox) + (R_oz)(R_oz) - r^2

	    Vector3f R_o = r.getOrigin();
	    Vector3f R_d = r.getDirection();
		
	    float a = R_d.x()*R_d.x() + R_d.z()*R_d.z();
	    float b = 2.0*(R_d.x()*R_o.x() + R_d.z()*R_o.z());
	    float c = R_o.x()*R_o.x() + R_o.z()*R_o.z() - pow(radius, 2);
	    float discrim = pow(b,2) - (4*a*c);

	    if (discrim < 0){
	        return false;
	    }

	    float t1 = (-1.0*b - sqrt(discrim)) / (2.0*a);
	    float t2 = (-1.0*b + sqrt(discrim)) / (2.0*a);

	    Vector3f p = r.pointAtParameter(t1);
	    t = t1;

	    if (t < 0 || (p.y() > center.y() + height/2.0f) || (p.y() < center.y() - height/2.0f)){
	        t=t2;
	    }

	    Vector3f pt = r.pointAtParameter(t);

	    if (t < 0 || (pt.y() > center.y() + height/2.0f) || (pt.y() < center.y() - height/2.0f)){
	        return false;
	    }

	    normal = Vector3f(pt.x()-center.x(), 0.0f, pt.z()-center.z()).normalized();
	    return true;
}

bool intersectCircle( const Ray& r , const Vector3f& center, float innerRad, float outerRad, float& t, Vector3f& normal){
	    
	    Vector3f R_o = r.getOrigin();
	    Vector3f R_d = r.getDirection();
		
	    t = (center.y() - R_o.y()) / R_d.y();

	    if (t < 0){
	        return false;
	    }

	    Vector3f pt = r.pointAtParameter(t);

	    float tprime = sqrt( (pt.x()-center.x()) * (pt.x()-center.x()) + (pt.z()-center.z()) * (pt.z()-center.z()) );
	    if (tprime < innerRad || tprime > outerRad){
		return false;
	    }

	    normal = Vector3f(0.0f, 1.0f, 0.0f);
	    return true;
}

bool Pipe::intersect( const Ray& r , Hit& h , float tmin){

	bool intersection = false;

	//Four parts of intersection (IN, OUT, TOP, BOTTOM)
	float tOut;
	Vector3f normalOut;
	float tIn;
	Vector3f normalIn;
	float tTop;
	Vector3f normalTop;
	float tBottom;
	Vector3f normalBottom;

	bool out = intersectCylinder(r,center,outerR,height,tOut,normalOut);
	bool in = intersectCylinder(r,center,innerR,height,tIn,normalIn);
	bool top = intersectCircle(r, (center+Vector3f(0.0f, height/2.0f, 0.0f)),innerR,outerR,tTop,normalTop);
	bool bottom = intersectCircle(r, (center-Vector3f(0.0f, height/2.0f, 0.0f)),innerR,outerR,tBottom,normalBottom);

	//Get lowest/closest t
	if (out && (tOut >= tmin) && (tOut <= h.getT())){
	    h.set(tOut, this->material, normalOut);
	    intersection = true;
	}
	if (in && (tIn >= tmin) && (tIn <= h.getT())){
	    h.set(tIn, this->material, normalIn);
	    intersection = true;
	}
	if (top && (tTop >= tmin) && (tTop <= h.getT())){
	    h.set(tTop, this->material, normalTop);
	    intersection = true;
	}
	if (bottom && (tBottom >= tmin) && (tBottom <= h.getT())){
	    h.set(tBottom, this->material, normalBottom);
	    intersection = true;
	}

	return intersection;

}

