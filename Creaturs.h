#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <stdlib.h>

class Creaturs{
protected:
	int x;
	int y;
	int image_index;
	bool moving;

public:
	void SetImageIndex(int new_image_index) { image_index = new_image_index; };
	
	int GetImageIndex() { return image_index; };


	int GetX() {
		return x;
	};

	int GetY() {
		return y;
	};

	void SetMoving(bool new_moving) { moving = new_moving; };
	
	bool GetMoving() { return moving; }


	

	bool BordersCheak(int coord, int offset) {
		if ((coord + offset) < 0) {
			return false;
		}
		else if ((coord + offset) > 9) {
			return false;
		}
		return true;
	};

	virtual void Move(Creaturs* grid[10][10]) = 0 {};
};