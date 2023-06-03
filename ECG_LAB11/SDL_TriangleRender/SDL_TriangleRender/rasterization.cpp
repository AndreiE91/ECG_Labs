#include "rasterization.h"

namespace egc {

	float minimum(float a, float b, float c) {
		float min = a;  // Assume 'a' is the minimum initially

		if (b < min) {
			min = b;  // Update 'min' if 'b' is smaller
		}
		if (c < min) {
			min = c;  // Update 'min' if 'c' is smaller
		}

		return min;  // Return the minimum value
	}

	float maximum(float a, float b, float c) {
		float max = a;  // Assume 'a' is the maximum initially

		if (b > max) {
			max = b;  // Update 'max' if 'b' is greater
		}
		if (c > max) {
			max = c;  // Update 'max' if 'c' is greater
		}

		return max;  // Return the maximum value
	}

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) 
	{
		//TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
		//Store the final results in the input parameters
		float fab_pixel = (triangleVertices.at(0).y - triangleVertices.at(1).y) * pixel.x + (triangleVertices.at(1).x - triangleVertices.at(0).x) * pixel.y + triangleVertices.at(0).x * triangleVertices.at(1).y - triangleVertices.at(1).x * triangleVertices.at(0).y;
		float fbc_pixel = (triangleVertices.at(1).y - triangleVertices.at(2).y) * pixel.x + (triangleVertices.at(2).x - triangleVertices.at(1).x) * pixel.y + triangleVertices.at(1).x * triangleVertices.at(2).y - triangleVertices.at(2).x * triangleVertices.at(1).y;
		float fca_pixel = (triangleVertices.at(2).y - triangleVertices.at(0).y) * pixel.x + (triangleVertices.at(0).x - triangleVertices.at(2).x) * pixel.y + triangleVertices.at(2).x * triangleVertices.at(0).y - triangleVertices.at(0).x * triangleVertices.at(2).y;

		float fbc_a = (triangleVertices.at(1).y - triangleVertices.at(2).y) * pixel.x + (triangleVertices.at(2).x - triangleVertices.at(1).x) * pixel.y + triangleVertices.at(1).x * triangleVertices.at(2).y - triangleVertices.at(2).x * triangleVertices.at(1).y;
		float fca_b = (triangleVertices.at(2).y - triangleVertices.at(0).y) * pixel.x + (triangleVertices.at(0).x - triangleVertices.at(2).x) * pixel.y + triangleVertices.at(2).x * triangleVertices.at(0).y - triangleVertices.at(0).x * triangleVertices.at(2).y;

		alpha = fbc_pixel/fbc_a;
		beta = fca_pixel/fca_b;
		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors) {
		//TO DO - Implement the triangle rasterization algorithm
		// Compute the bounding box of the three vertices
		float bbox_xmin, bbox_ymin, bbox_xmax, bbox_ymax;
		bbox_xmin = minimum(triangleVertices.at(0).x, triangleVertices.at(1).x, triangleVertices.at(2).x);
		bbox_ymin = minimum(triangleVertices.at(0).y, triangleVertices.at(1).y, triangleVertices.at(2).y);
		bbox_xmax = maximum(triangleVertices.at(0).x, triangleVertices.at(1).x, triangleVertices.at(2).x);
		bbox_ymax = maximum(triangleVertices.at(0).y, triangleVertices.at(1).y, triangleVertices.at(2).y);

		// Iterate over all pixels inside the bounding box
		for (int i = bbox_xmin; i <= bbox_xmax; ++i) {
			for (int j = bbox_ymin; j <= bbox_ymax; ++j) = {

			}
		}

	}

}