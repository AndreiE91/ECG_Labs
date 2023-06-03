#include "clip.h"

int xMin = INT_MAX, yMin = INT_MAX, xMax = INT_MIN, yMax = INT_MIN;

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		//TO DO - compute the code for the point given as argument
		for (int i = 0; i < clipWindow.size(); ++i) { // Initialize bounds depending on clipWindow
			if (clipWindow[i].x > xMax) {
				xMax = clipWindow[i].x;
			}
			if (clipWindow[i].y > yMax) {
				yMax = clipWindow[i].y;
			}
			if (clipWindow[i].x < xMin) {
				xMin = clipWindow[i].x;
			}
			if (clipWindow[i].y < yMin) {
				yMin = clipWindow[i].y;
			}
		}
		if (p.y < yMin)
			code.push_back(1); // Upper region
		else code.push_back(0);
		if (p.y > yMax)
			code.push_back(1); // Lower region
		else code.push_back(0);
		if (p.x > xMax)
			code.push_back(1); // Right region
		else code.push_back(0);
		if (p.x < xMin)
			code.push_back(1); // Left region
		else code.push_back(0);
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[i] == 1 && cod2[i] == 1) { // same region, reject
				return true;
			}
		}
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[i] == 0 && cod2[i] == 0) { 
				continue;
			}
			else {
				return false;
			}
		}

		return true;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
		bool finished = false;
		while(finished == false) {
			std::vector<int> code1 = computeCSCode(clipWindow, p1); //compute the 4 digits code for P(x1, y1)
			std::vector<int> code2 = computeCSCode(clipWindow, p2); // compute the 4 digits code for P(x2, y2)
			bool reject = simpleRejection(code1, code2); //test for simple rejection case
			if (reject == true) {
				finished = true;
				return -1; // This will not show any line whatsoever. Might be another way but this is what I noticed in the main function so I will use it
			} else {
				bool display = simpleAcceptance(code1, code2); //test for simple acceptance case
				if (display == true) {
					finished = true;
				} else {
					if (p1.x >= xMin && p1.x <= xMax && p1.y >= yMin && p1.y <= yMax) { //Inside view area
						//if P(x1, y1) is inside the display area, invert P(x1, y1) and P(x2, y2)
						//together with their 4 digits CS codes
						vec3 tempPoint;
						tempPoint.x = p1.x;
						tempPoint.y = p1.y;
						p1.x = p2.x;
						p1.y = p2.y;
						p2.x = tempPoint.x;
						p2.y = tempPoint.y;
						int aux;
						for (int i = 0; i < code1.size(); ++i) {
							aux = code1[i];
							code1[i] = code2[i];
							code2[i] = aux;
						}
					}
					if (code1[0] == 1 && p2.y != p1.y) { //eliminate the segment above the display area
						p1.x = p1.x + (p2.x - p1.x) * (yMin - p1.y) / (p2.y - p1.y);
						p1.y = yMin;
					}
					else if (code1[1] == 1 && p2.y != p1.y) { //eliminate the segment under the display area
						p1.x = p1.x + (p2.x - p1.x) * (yMax - p1.y) / (p2.y - p1.y);
						p1.y = yMax;
					}
					else if (code1[2] == 1 && p2.x != p1.x) { //eliminate the segment on the right of the display area
						p1.y = p1.y + (p2.y - p1.y) * (xMax - p1.x) / (p2.x - p1.x);
						p1.x = xMax;
					}
					else if (code1[3] == 1 && p2.x != p1.x) { //eliminate the segment on the left of the display area
						p1.y = p1.y + (p2.y - p1.y) * (xMin - p1.x) / (p2.x - p1.x);
						p1.x = xMin;
					}
				}
			} 
		}
		return 0;
	}
}

