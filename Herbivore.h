#pragma once

#include "Creaturs.h";

class Herbivore : public Creaturs {
private:
	double hunger;

public:
	Herbivore(int x_pos, int y_pos) {
		x = x_pos;
		y = y_pos;
		image_index = rand() % 4 + 3;
		moving = true;

		hunger = 1;
	};

	~Herbivore() {

	};

	virtual void Move(Creaturs* grid[10][10]) {
		int birth_cheak = rand() % 4;
		int counter = 0;

		while (moving == true) {

			if (counter >= 10) {
				moving = false;
			}

			int x_offset = rand() % 3 - 1;
			int y_offset = rand() % 3 - 1;
			if (BordersCheak(x, x_offset) && BordersCheak(y, y_offset)) {
				
				int scan_result = grid[x + x_offset][y + y_offset]->GetImageIndex();
				
				if (scan_result == 0 || scan_result == 7 || scan_result == 8) {
					if (scan_result == 7 || scan_result == 8) {
						hunger += 0.2;
					}
					
					grid[x + x_offset][y + y_offset] = grid[x][y];
					
					if (birth_cheak == 0) {
						grid[x][y] = new Void();
					}
					else {
						grid[x][y] = new Herbivore(x, y);
						hunger -= 0.4;
						if (hunger <= 0) {
							grid[x + x_offset][y + y_offset] = new Void();
						}
					}

					x += x_offset;
					y += y_offset;
					
					hunger -= 0.2;

					if (hunger <= 0) {
						grid[x][y] = new Void();
					}

					moving = false;
				}
			}

			counter++;
		}
	};
	
};