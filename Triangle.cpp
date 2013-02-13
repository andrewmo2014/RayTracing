#include "Triangle.h"
#include <iostream>

using namespace std;

bool Triangle::intersect( const Ray& r , Hit& h , float tmin){

	Vector3f R_o = r.getOrigin();
	Vector3f R_d = r.getDirection();

	Matrix3f A( this->a.x()-this->b.x() , this->a.x()-this->c.x() , R_d.x() ,
		    this->a.y()-this->b.y() , this->a.y()-this->c.y() , R_d.y() ,
		    this->a.z()-this->b.z() , this->a.z()-this->c.z() , R_d.z()  );

	Matrix3f BetaM( this->a.x()-R_o.x() , this->a.x()-this->c.x() , R_d.x() ,
		        this->a.y()-R_o.y() , this->a.y()-this->c.y() , R_d.y() ,
		        this->a.z()-R_o.z() , this->a.z()-this->c.z() , R_d.z()  );
	
	float beta = BetaM.determinant() / A.determinant();

	Matrix3f GammaM( this->a.x()-this->b.x() , this->a.x()-R_o.x() , R_d.x() ,
		         this->a.y()-this->b.y() , this->a.y()-R_o.y() , R_d.y() ,
		         this->a.z()-this->b.z() , this->a.z()-R_o.z() , R_d.z()  );
	
	float gamma = GammaM.determinant() / A.determinant();

	float alpha = 1.0f - beta - gamma;

	Matrix3f tM( this->a.x()-this->b.x() , this->a.x()-this->c.x() , this->a.x()-R_o.x() ,
		     this->a.y()-this->b.y() , this->a.y()-this->c.y() , this->a.y()-R_o.y() ,
		     this->a.z()-this->b.z() , this->a.z()-this->c.z() , this->a.z()-R_o.z()  );
	
	float t = tM.determinant() / A.determinant();

	if (beta + gamma > 1){
	    return false;
	} 
	if (beta < 0){
	    return false;
	} 
	if (gamma < 0){
	    return false;
	} 

	if (t > tmin && t < h.getT()){

	    Vector3f newNormal = (alpha*this->normals[0] + beta*this->normals[1] + gamma*this->normals[2]).normalized();
	    h.set(t, this->material, newNormal);

	    Vector2f newTexCoord = (alpha*this->texCoords[0] + beta*this->texCoords[1] + gamma*this->texCoords[2]);
	    h.setTexCoord(newTexCoord);

	    return true;	
	} 
	else{
	    return false;
	} 
}
