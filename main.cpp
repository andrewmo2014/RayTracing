#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include "Group.h"
#include "Hit.h"
#include "Ray.h"
#include "RayTracer.h"
#include <string.h>

using namespace std;

//float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.
  char* in;
  char* out;
  int width;
  int height;
  bool depth_ON = false;
  float depthMin;
  float depthMax;
  char* depthOut;
  char* normalsOut;
  bool normals_ON = false;
  
  int stats = 0;
  int bounces = 4;
  int shadows = 0;

  // sampling
  int jitter = 0;
  int filter = 0;

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for( int argNum = 1; argNum < argc; ++argNum )
    {
      std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
	
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  for( int ind = 1; ind < argc; ind++ ){
        if (strcmp(argv[ind], "-input") == 0){
            in = argv[ind+1];
	    ind+=1;
        }
	else if (strcmp(argv[ind], "-output") == 0){
            out = argv[ind+1];
	    ind+=1;
        }
	else if (strcmp(argv[ind], "-normals") == 0){
            normals_ON = true;
	    normalsOut = argv[ind+1];
	    ind+=1;
        }
	else if (strcmp(argv[ind], "-size") == 0){
            width = atoi(argv[ind+1]);
	    height = atoi(argv[ind+2]);
	    ind+=2;
        }
	else if (strcmp(argv[ind], "-depth") == 0){
            depth_ON = true;
	    depthMin = atof(argv[ind+1]);
	    depthMax = atof(argv[ind+2]);
	    depthOut = argv[ind+3];
	    ind+=3;
        }

	else if (strcmp(argv[ind], "-shadows") == 0){
            shadows = 1;
        }

	else if (strcmp(argv[ind], "-bounces") == 0){
	    bounces = atoi(argv[ind+1]);
	    ind+=1;
        }

	else if (strcmp(argv[ind], "-jitter") == 0){
            jitter = 1;
        }
	else if (strcmp(argv[ind], "-filter") == 0){
            filter = 1;
        }
	else{
	    std::cout << "Error Parsing" << std::endl;
	    return -1;
	}
  }

  //Analyze the scene
  SceneParser scene = SceneParser(in);
  RayTracer rayTrace = RayTracer( &scene, bounces, shadows);

  Image myIMG = Image(width, height);
  //myIMG.SetAllPixels(scene.getBackgroundColor());
  
  if (!jitter && !filter){
  for (int i = 0; i<width; i++){
  	for (int j = 0; j<height; j++){
	    Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	    Ray r = scene.getCamera()->generateRay(coord);
	    Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));
	    Vector3f pixCol = rayTrace.traceRay(r, scene.getCamera()->getTMin(), 0, 1.0f, h);

	    myIMG.SetPixel(j, i, pixCol);
	}
  }
  }
  

  else{
  //Jitter High Res
  int widthHighRes = width*3;
  int heightHighRes = height*3;
  vector<Vector3f> pixColors;
  vector<Vector3f> pixColorsBlurH;
  vector<Vector3f> pixColorsBlurV;
  const float K[] = {0.1201f, 0.2339f, 0.2931f, 0.2339f, 0.1201f};

  for (int i = 0; i<widthHighRes; i++){
  	for (int j = 0; j<heightHighRes; j++){
	    Vector2f coord = Vector2f( (2*float(i) / (widthHighRes-1)) -1 , (2*float(j) / (heightHighRes-1)) -1 );
	    float r_i = (float)rand()/(float)RAND_MAX - 0.5f;
	    float r_j = (float)rand()/(float)RAND_MAX - 0.5f;
	    Vector2f newCoord = Vector2f(coord[0] + r_i, coord[1] + r_j);
	    Ray r = scene.getCamera()->generateRay(coord);
	    Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));
	    Vector3f origColor = rayTrace.traceRay(r, scene.getCamera()->getTMin(), 0, 1.0f, h);
	    pixColors.push_back(origColor);
	}
  }

  //Gaussian High Res horizontal blur
  for (int i = 0; i<widthHighRes; i++){
  	for (int j = 0; j<heightHighRes; j++){
	    if (j == 0){
	        pixColorsBlurH.push_back(pixColors[i*heightHighRes+j  ]*K[2] + 
				       pixColors[i*heightHighRes+j+1]*K[3] + 
				       pixColors[i*heightHighRes+j+2]*K[4] );   
	    }
	    else if (j == 1){
	        pixColorsBlurH.push_back(pixColors[i*heightHighRes+j-1]*K[1] +
				       pixColors[i*heightHighRes+j  ]*K[2] + 
				       pixColors[i*heightHighRes+j+1]*K[3] + 
				       pixColors[i*heightHighRes+j+2]*K[4] );   
	    }
	    else if (j == heightHighRes-1){
	        pixColorsBlurH.push_back(pixColors[i*heightHighRes+j  ]*K[2] + 
				       pixColors[i*heightHighRes+j-1]*K[1] + 
				       pixColors[i*heightHighRes+j-2]*K[0] );   
	    }
	    else if (j == heightHighRes-2){
	        pixColorsBlurH.push_back(pixColors[i*heightHighRes+j+1]*K[3] +
				       pixColors[i*heightHighRes+j  ]*K[2] + 
				       pixColors[i*heightHighRes+j-1]*K[1] + 
				       pixColors[i*heightHighRes+j-2]*K[0] );   
	    }
	    else{
	        pixColorsBlurH.push_back(pixColors[i*heightHighRes+j-2]*K[0] +
				       pixColors[i*heightHighRes+j-1]*K[1] +
				       pixColors[i*heightHighRes+j  ]*K[2] + 
				       pixColors[i*heightHighRes+j+1]*K[3] + 
				       pixColors[i*heightHighRes+j+2]*K[4] );   
	    }
	}
  }

  //Gaussian High Res vertical blur
  for (int j = 0; j<heightHighRes; j++){
  	for (int i = 0; i<widthHighRes; i++){
	    if (i == 0){
	        pixColorsBlurV.push_back(pixColorsBlurH[j*widthHighRes+i  ]*K[2] + 
				         pixColorsBlurH[j*widthHighRes+i+1]*K[3] + 
				         pixColorsBlurH[j*widthHighRes+i+2]*K[4] );   
	    }
	    else if (i == 1){
	        pixColorsBlurV.push_back(pixColorsBlurH[j*widthHighRes+i-1]*K[1] + 
					 pixColorsBlurH[j*widthHighRes+i  ]*K[2] + 
				         pixColorsBlurH[j*widthHighRes+i+1]*K[3] + 
				         pixColorsBlurH[j*widthHighRes+i+2]*K[4] );     
	    }
	    else if (i == widthHighRes-1){
	        pixColorsBlurV.push_back(pixColorsBlurH[j*widthHighRes+i  ]*K[2] + 
				         pixColorsBlurH[j*widthHighRes+i-1]*K[1] + 
				         pixColorsBlurH[j*widthHighRes+i-2]*K[0] );    
	    }
	    else if (i == widthHighRes-2){
	        pixColorsBlurV.push_back(pixColorsBlurH[j*widthHighRes+i+1]*K[3] + 
					 pixColorsBlurH[j*widthHighRes+i  ]*K[2] + 
				         pixColorsBlurH[j*widthHighRes+i-1]*K[1] + 
				         pixColorsBlurH[j*widthHighRes+i-2]*K[0] );  
	    }
	    else{
	        pixColorsBlurV.push_back(pixColorsBlurH[j*widthHighRes+i-2]*K[0] +
				         pixColorsBlurH[j*widthHighRes+i-1]*K[1] +
				         pixColorsBlurH[j*widthHighRes+i  ]*K[2] + 
				         pixColorsBlurH[j*widthHighRes+i+1]*K[3] + 
				         pixColorsBlurH[j*widthHighRes+i+2]*K[4] );    
	    }
	}
  }

  //DownSample
  for (int i = 0; i<width; i++){
  	for (int j = 0; j<height; j++){
	    Vector3f finalPixCol = pixColorsBlurV[3*(i+widthHighRes*j)+0] + 
			  pixColorsBlurV[3*(i+widthHighRes*j)+1] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+2] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+widthHighRes+0] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+widthHighRes+1] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+widthHighRes+2] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+2*widthHighRes+0] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+2*widthHighRes+1] +
			  pixColorsBlurV[3*(i+widthHighRes*j)+2*widthHighRes+2];
	    Vector3f finalPixColAVG = finalPixCol/9.0f;
	    myIMG.SetPixel(i, j, finalPixColAVG);
	}
  }
  }

  myIMG.SaveTGA(out);

  //Depth Implementation
  if (depth_ON){
	Image imgDepth = Image(width, height);
	imgDepth.SetAllPixels(Vector3f(0.0f, 0.0f, 0.0f));
	for (int i = 0; i<width; i++){
  	    for (int j = 0; j<height; j++){
	        Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	        Ray r = scene.getCamera()->generateRay(coord);
	        Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));

		if(scene.getGroup()->intersect(r, h, scene.getCamera()->getTMin())){
		    if (depthOut != NULL){
		        if (h.getT() < depthMin){
			    imgDepth.SetPixel(j, i, Vector3f(1.0f, 1.0f, 1.0f));
			}
			else if (h.getT() > depthMax) {
			    imgDepth.SetPixel(j, i, Vector3f(0.0f, 0.0f, 0.0f));
			}
			else{
			    float grayScale = (depthMax - h.getT()) / (depthMax - depthMin);
			    imgDepth.SetPixel(j, i, Vector3f(grayScale, grayScale, grayScale));
			}
		    }
		}
	    }
	}
	imgDepth.SaveTGA(depthOut);  
  }

  //Normal Implementation
  if (normals_ON){
	Image imgNormals = Image(width, height);
	imgNormals.SetAllPixels(Vector3f(0.0f, 0.0f, 0.0f));
	for (int i = 0; i<width; i++){
  	    for (int j = 0; j<height; j++){
	        Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	        Ray r = scene.getCamera()->generateRay(coord);
	        Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));

		if(scene.getGroup()->intersect(r, h, 0.0f)){
		    Vector3f pixColNorm = h.getNormal().normalized();
		    for (int x = 0; x < 3; x++){
			if (pixColNorm[x] < 0){
			    pixColNorm[x] = pixColNorm[x] * -1.0f;
			}
		    }
		    imgNormals.SetPixel(j, i, pixColNorm);
		}
	    }
	}
	imgNormals.SaveTGA(normalsOut);
  }
  
 /*
  ///TODO: below demonstrates how to use the provided Image class
  ///Should be removed when you start
  Vector3f pixelColor (1.0f,0,0);
  //width and height
  Image image( 10 , 15 );
  image.SetPixel( 5,5, pixelColor );
  image.SaveImage("demo.bmp");
 */

  return 0;
}

