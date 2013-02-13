#include "Group.h"
#include <iostream>

using  namespace std;

	
Group::Group( int num_objects ):Object3D(NULL){

}

bool Group::intersect( const Ray& r , Hit& h , float tmin ) {
    bool intersect = false;
    for (unsigned int i = 0; i < this->objects.size(); i++){
	Object3D* obj = objects[i];
	if (obj->intersect(r, h, tmin)){
	    intersect = true;
	}
    }
    return intersect;
}
	
void Group::addObject( int index , Object3D* obj ){
    this->objects.push_back(obj);
}

int Group::getGroupSize(){
    return this->objects.size(); 
  
}
	
