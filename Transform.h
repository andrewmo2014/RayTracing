#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"

class Transform: public Object3D
{
public: 
  Transform(){}
 Transform( const Matrix4f& m, Object3D* obj );
  ~Transform(){
  }
  virtual bool intersect( const Ray& r , Hit& h , float tmin);

 protected:
  Object3D* o; //un-transformed object
  Matrix4f matrix;	
};

#endif //TRANSFORM_H
