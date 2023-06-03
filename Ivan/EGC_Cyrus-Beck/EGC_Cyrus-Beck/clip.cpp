#include "clip.h"

namespace egc {

	//Cyrus-Beck clipping algorithm
	//clipWindow specifies the vertices that define the clipping area in conterclockwise order
	//and can represent any convex polygon
	//function returns -1 if the line segment cannot be clipped


	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cyrus-Beck line clipping algorithm - consult the laboratory work

		float tE = 0; //max entry
		float tL = 1; //min exit

		vec3 p2p1 = p2 - p1;
		int numpoints = clipWindow.size();

		//parcurgem toti vectorii poligonului de decupare
		for (unsigned int i = 0; i < numpoints; i++) {

			//printf("%f,%f ", clipWindow.at(i).x, clipWindow.at(i).y);

			//initialize normal to edge vector (backward direction)
			vec3 normal = clipWindow.at(i) - clipWindow.at((i + 1) % numpoints);

			float tmp = normal.x;
			//rotate counterclockwise 90 degrees
			normal.x = -normal.y;
			normal.y = tmp;

			float product = dotProduct(normal, p2p1);

			float t = dotProduct(normal, p1 - clipWindow.at(i)) / (-product);

			//include cazul 0 t = inf, intersectia e la infinit
			//tE va fi inf -> mai mare decat tL -> nu se deseneaza
			if (product >= 0) {
				//find max entry t
				if (t > tE)
					tE = t;
			}
			else {
				//find min exit t
				if (t < tL)
					tL = t;
			}
		}

		printf("%f - %f\n", tE, tL);
		//outside
		if (tE > tL)
			return -1;

		p2.x = p1.x + p2p1.x * tL;
		p2.y = p1.y + p2p1.y * tL;

		p1.x = p1.x + p2p1.x * tE;
		p1.y = p1.y + p2p1.y * tE;

		return 0;
	}

	
}

