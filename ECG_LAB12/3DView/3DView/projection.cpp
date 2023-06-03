//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"
#include "include/SDL_render.h"
#include "transform.h"

namespace egc {
    //define the viewport transformation matrix
    //see section 3 from the laboratory work
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
		mat4 viewTransformMatrix;
        mat4 mvp;
      

        mvp.at(0, 0) = width / 2;
        mvp.at(1, 1) = -height / 2;
        mvp.at(2, 2) = 1;
        mvp.at(3, 3) = 1;
        mvp.at(0, 3) = width / 2;
        mvp.at(1, 3) = height / 2;
        mvp = translate(startX, startY, 0) *mvp;
        viewTransformMatrix = mvp;
        return viewTransformMatrix; 
    }
    
    //define the camera transformation matrix
    //see section 4 from the laboratory work
    mat4 defineCameraMatrix(Camera mc)
    {
        mat4 cameraMatrix;
        mat4 m1;
        mat4 m2;
        vec3 g = mc.cameraTarget - mc.cameraPosition;
        vec3 w = -(g.normalize());
        vec3 auxu = crossProduct(mc.cameraUp, w);
        vec3 u = auxu.normalize();
        vec3 v = crossProduct(w, u);
        m1.at(0, 0) = u.x;
        m1.at(0, 1) = u.y;
        m1.at(0, 2) = u.z;
        m1.at(1, 0) = v.x;
        m1.at(1, 1) = v.y;
        m1.at(1, 2) = v.z;
        m1.at(2, 0) = w.x;
        m1.at(2, 1) = w.y;
        m1.at(2, 2) = w.z;
        m1.at(3, 3) = 1;
        m2.at(0, 0) = 1;
        m2.at(1, 1) = 1;
        m2.at(2, 2) = 1;
        m2.at(3, 3) = 1;
        m2.at(0, 3) = -mc.cameraPosition.x;
        m2.at(1, 3) = -mc.cameraPosition.y;
        m2.at(2, 3) = -mc.cameraPosition.z;
        cameraMatrix = m1 * m2;
	
        return cameraMatrix;
    }
    
    //define the projection transformation matrix
    //see section 5 from the laboratory work
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveProjectionMatrix;
        perspectiveProjectionMatrix.at(0, 0) = -1/( aspect * tan(fov));
            perspectiveProjectionMatrix.at(1, 1) = -1/( tan(fov / 2));
            perspectiveProjectionMatrix.at(2, 2) = (zFar+zNear)/(zNear-zFar);
            perspectiveProjectionMatrix.at(2, 3) = (2*zFar*zNear)/(zFar-zNear);
            perspectiveProjectionMatrix.at(3, 2) = 1;
        return perspectiveProjectionMatrix;
    }
    
    //define the perspective divide operation
    //see section 5 from the laboratory work
    void perspectiveDivide(vec4 &iv)
    {
      iv=  iv* (1 / iv.w);
		
    }

    //check if a point should be clipped
    //see section 9 from the laboratory work
    bool clipPointInHomogeneousCoordinate(const egc::vec4 &vertex)
    {

        -vertex.w <= vertex.x <= vertex.w;
        -vertex.w <= vertex.y <= vertex.w;
        -vertex.w <= vertex.z <= vertex.w;

        return false;
    }

    //check if a triangle should be clipped
    //clip only those triangles for which all vertices are outside the viewing volume
    bool clipTriangleInHomegeneousCoordinates(const std::vector<egc::vec4> &triangle)
    {
        return false;
    }

    //compute the normal vector to a triangle
    //see section 7 from the laboratory work
    egc::vec3 findNormalVectorToTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec3 n;
        
        return n;
    }

    //compute the coordinates of the triangle's center
    //(we will use this point to display the normal vector)
    egc::vec4 findCenterPointOfTriangle(const std::vector<egc::vec4> &triangle)
    {
        egc::vec4 triangleCenter;
        
        return triangleCenter;
    }

    //check if the triangle is visible (front facing)
    //see section 8 from the laboratory work
    bool isTriangleVisible(const std::vector<egc::vec4> &triangle, const egc::vec3 &normalVector)
    {
        return true;
    }

    //display the normal vector of a triangle
    //see section 7 from the laboratory work
    //use the SDL_RenderDrawLine to draw the normal vector
	void displayNormalVectors(egc::vec3 &normalVector, egc::vec4 &triangleCenter, SDL_Renderer *renderer, egc::mat4 viewTransformMatrix, egc::mat4 perspectiveMatrix)
    {
        
    }
}
