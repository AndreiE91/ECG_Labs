#include "clip.h"
#include <iostream>

using namespace std;

int xMin = INT_MAX, yMin = INT_MAX, xMax = INT_MIN, yMax = INT_MIN;

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		//TO DO - compute the code for the point given as argument
		for (int i = 0; i < clipWindow.size(); i++) {
			if (clipWindow[i].x > xMax)
				xMax = clipWindow[i].x;
			if (clipWindow[i].y > yMax)
				yMax = clipWindow[i].y;
			if (clipWindow[i].x < xMin)
				xMin = clipWindow[i].x;
			if (clipWindow[i].y < yMin)
				yMin = clipWindow[i].y;
		}
		if (p.y < yMin)
			code.push_back(1);
		else code.push_back(0);
		if (p.y > yMax)
			code.push_back(1);
		else code.push_back(0);
		if (p.x > xMax)
			code.push_back(1);
		else code.push_back(0);
		if (p.x < xMin)
			code.push_back(1);
		else code.push_back(0);
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE REJECTION case
		for (int i = 0; i < cod1.size(); i++)
			if (cod1[i] == cod2[i] && cod1[i] == 1)
				return true;
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		for (int i = 0; i < cod1.size(); i++)
			if (cod1[i] != 0)
				return false;
		for (int i = 0; i < cod1.size(); i++)
			if (cod2[i] != 0)
				return false;
		return true;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
		bool finished = false;
		while (finished != true) {
			std::vector<int> code1, code2;
			code1 = computeCSCode(clipWindow, p1);
			code2 = computeCSCode(clipWindow, p2);
			bool respins = simpleRejection(code1, code2);
			if (respins == true)
			{
				finished = true;
				return -1;
			}
			else {
				bool display = simpleAcceptance(code1, code2);
				if (display == true)
					finished = true;
				else {
					if (p1.x >= xMin && p1.x <= xMax && p1.y >= yMin && p1.y <= yMax) {
						vec3 p3;
						p3.x = p1.x;
						p3.y = p1.y;
						p1.x = p2.x;
						p1.y = p2.y;
						p2.x = p3.x;
						p2.y = p3.y;
						int aux;
						for (int i = 0; i < code1.size(); i++) {
							aux = code1[i];
							code1[i] = code2[i];
							code2[i] = aux;
						}
					}
					if (code1[0] == 1 && p1.y != p2.y) {
						p1.x = p1.x + (p2.x - p1.x) * (yMin - p1.y) / (p2.y - p1.y);
						p1.y = yMin;
					}
					else if (code1[1] == 1 && p1.y != p2.y) {
						p1.x = p1.x + (p2.x - p1.x) * (yMax - p1.y) / (p2.y - p1.y);
						p1.y = yMax;
					}
					else if (code1[2] == 1 && p1.x != p2.x) {
						p1.y = p1.y + (p2.y - p1.y) * (xMax - p1.x) / (p2.x - p1.x);
						p1.x = xMax;
					}
					else if (code1[3] == 1 && p1.x != p2.x) {
						p1.y = p1.y + (p2.y - p1.y) * (xMin - p1.x) / (p2.x - p1.x);
						p1.x = xMin;
					}
				}
			}
		}
		return 0;
	}
}

