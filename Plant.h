#pragma once

#include "Creaturs.h";

class Plant : public Creaturs {
private:
	int live_cycle_count;

public:
	Plant(int x_pos, int y_pos) {
		x = x_pos;
		y = y_pos;
		image_index = rand() % 2 + 7;
		moving = false;

		live_cycle_count = 0;
	};

	void Move(Creaturs* grid[10][10]) {
		live_cycle_count++;
		if (live_cycle_count >= 5) {
			grid[x][y] = new Void();
		}
	}
};