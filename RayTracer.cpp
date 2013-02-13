#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"
#include <cmath>
#include <iostream>

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
    return (normal*(2*(Vector3f::dot(normal, incoming))) - incoming).normalized();
}

bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming, 
        float index_n, float index_nt, 
        Vector3f& transmitted)
{
    float n_r = index_n / index_nt;
    float NDotD = Vector3f::dot(normal,incoming);
    float radical = (1.0f - n_r*n_r*(1.0f-NDotD*NDotD));
    
    if (radical < 0){
        return false;
    }
    
    transmitted = normal*(n_r*NDotD-sqrt(radical)) - (incoming*n_r);
    transmitted.normalized();

    return true;
}

RayTracer::RayTracer( SceneParser * scene, int max_bounces, bool my_shadows
  //more arguments if you need...
                      ) :
  m_scene(scene)

{
  g=scene->getGroup();
  m_maxBounces = max_bounces;
  m_shadows = my_shadows;
}

RayTracer::~RayTracer()
{
}

Vector3f RayTracer::traceRay( Ray& ray, float tmin, int bounces,
        float refr_index, Hit& hit ) const
{

    if (g->intersect(ray, hit, tmin)){
	Vector3f pixCol = Vector3f(0.0f, 0.0f, 0.0f);

	//Ambient color
	pixCol = pixCol + hit.getMaterial()->getDiffuseColor()*m_scene->getAmbientLight();
	
	//Diffuse color + SHADOWS
	for (int indL = 0; indL < m_scene->getNumLights(); indL++){
	    Light* lit = m_scene->getLight(indL);
	    Vector3f litDir;
	    Vector3f litCol;
	    float distToLit;

	    lit->getIllumination(ray.pointAtParameter(hit.getT()), litDir, litCol, distToLit);

	    //cast shadows
	    if (m_shadows){
	        Ray shadowRay = Ray(ray.pointAtParameter(hit.getT()), litDir);
	        Hit shadowHit = Hit(distToLit, NULL, NULL);

	        if (!g->intersect(shadowRay, shadowHit, EPSILON)){
	            Vector3f shadingCol = hit.getMaterial()->Shade(ray, hit, litDir, litCol);
	            pixCol = pixCol + shadingCol;	        
	        }
	    }
	    else{
		Vector3f shadingCol = hit.getMaterial()->Shade(ray, hit, litDir, litCol);
	        pixCol = pixCol + shadingCol;
	    } 

	}

        if (bounces>m_maxBounces-1){
	    return pixCol;
	}

	//Reflectance
	Vector3f mirrDir = mirrorDirection( hit.getNormal().normalized(), -1.0f*ray.getDirection());
	Ray mirrRay = Ray(ray.pointAtParameter(hit.getT()), mirrDir);
	Hit mirrHit = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));
	Vector3f mirrColor = hit.getMaterial()->getSpecularColor()*traceRay( mirrRay, EPSILON, bounces+1, refr_index, mirrHit );
	//pixCol = pixCol + mirrColor;


	//Refraction 
	float new_refr_index;
	Vector3f normal = hit.getNormal().normalized();
	if (Vector3f::dot(ray.getDirection(), normal) > 0){
	    new_refr_index = 1.0f;
	    normal = normal*-1.0f;
	}
	else{
	    new_refr_index = hit.getMaterial()->getRefractionIndex();
	}	

	//check if not total reflection
	Vector3f transmitted;
	if (transmittedDirection( normal, -1.0f*ray.getDirection(), refr_index, new_refr_index, transmitted)){

	    Ray transRay = Ray(ray.pointAtParameter(hit.getT()), transmitted);
	    Hit transHit = Hit();

	    Vector3f transColor = hit.getMaterial()->getSpecularColor()*traceRay( transRay, EPSILON, bounces+1, new_refr_index, transHit );	

	    float R_0 = pow((new_refr_index - refr_index)/(new_refr_index + refr_index), 2);
	    //std::cout << R_0 << std::endl;

	    float c;
	    if (refr_index <= new_refr_index){
	        c = abs(Vector3f::dot(-1.0f*ray.getDirection(), normal));
	    }
	    else{
		c = abs(Vector3f::dot(transmitted, normal));
	    }

	    float R = R_0 + (1-R_0)*pow(1-c, 5);
	    //std::cout << c << std::endl;
	    //R = 0;

	    pixCol = pixCol + (1-R)*transColor + (R)*mirrColor;
	}
	
	//total relfection instead
	else{
	    pixCol = pixCol + mirrColor;
	}
	
	return pixCol;
    }
    
    else{
        return m_scene->getBackgroundColor(ray.getDirection());
    }
}
