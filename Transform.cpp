#include "Transform.h"

using namespace std;

Transform::Transform( const Matrix4f& m, Object3D* obj ):Object3D(NULL){
	this->matrix = m;
	this->o = obj;
}

bool Transform::intersect( const Ray& r , Hit& h , float tmin){
	Vector4f R_o4 = Vector4f(r.getOrigin(), 1.0f);
	Vector4f R_d4 = Vector4f(r.getDirection(), 0.0f);
	Vector4f R_o4_Trans = this->matrix.inverse() * R_o4;
	Vector4f R_d4_Trans = this->matrix.inverse() * R_d4;
	Vector3f R_o3_Trans = R_o4_Trans.xyz();
	Vector3f R_d3_Trans = R_d4_Trans.xyz();
	Ray rayNew = Ray(R_o3_Trans, R_d3_Trans);
	if (this->o->intersect(rayNew, h, tmin)){
		Vector4f normalTrans4 = Vector4f(h.getNormal(), 0.0f);
		Vector4f normal4 = (this->matrix.inverse().transposed() * normalTrans4).normalized();
		Vector3f normal = normal4.xyz();
		h.set(h.getT(), h.getMaterial(), normal);
		return true;
	}
	return false;
}
