#include "zbuffer.h"

namespace egc {

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) {
		//The same as that from last week ==> please replace the content
		//This function is to be used in "drawTriangleInZBuffer" to help you compute the coordinates of the points inside the triangle

	}


	void drawTriangleInZBuffer(std::vector<egc::vec4> triangle, float depthBuffer[WINDOW_HEIGHT][WINDOW_WIDTH], float& zmin, float& zmax) {

		//TO DO  -  implement the "drawing" of the triangle inside the depth buffer
		//The buffer has the same dimension as the screen - use it to fill in not the pixel color of each pixel in the triangel - but the pixel depth (Z component)
		//So you are going to fill in the Z of each pixel inside the triangle - use the algorithm from last week to access the inside of the triangle

		//While you compute the z for each pixel, you can also determine the zmin and zmax values ===> from all the points of the rabbit 
		//zmin and zmax are the minimum and maximum Z values FROM ALL THE VERICES OF THE RABBIT

	}

}
