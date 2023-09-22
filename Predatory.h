#pragma once

#include "Creaturs.h";


class Predatory : public Creaturs {
private:
	double hunger;
	int food_counter;
	bool birth;

public:
	Predatory(int x_pos, int y_pos) {
		x = x_pos;
		y = y_pos;
		image_index = rand() % 2 + 1;
		moving = true;

		hunger = 1;
		food_counter = 0;
		birth = true;
	};

	~Predatory() {

	}

	virtual void Move(Creaturs* grid[10][10]) {
		int counter = 0;
		int x_offset = 0;
		int y_offset = 0;

		while (moving == true) {

			if (counter >= 10) {
				moving = false;
			}


			if (hunger >= 0.5) {
				x_offset = rand() % 3 - 1;
				y_offset = rand() % 3 - 1;
			}
			else {
				x_offset = rand() % 5 - 2;
				y_offset = rand() % 5 - 2;
			}
			
			if (BordersCheak(x, x_offset) && BordersCheak(y, y_offset)) {				
				int scan_result = grid[x + x_offset][y + y_offset]->GetImageIndex();

				if (scan_result == 0 || (3 <= scan_result && scan_result <= 6)) {
					if (3 <= scan_result && scan_result <= 6) {
						hunger += 0.2;
						food_counter++;
					}

					grid[x + x_offset][y + y_offset] = grid[x][y];

					if (food_counter > 2 && birth) {
						grid[x][y] = new Predatory(x, y);
						hunger -= 0.4;
						
						if (hunger <= 0) {
							grid[x + x_offset][y + y_offset] = new Void();
						}
						birth = false;
					}
					else {
						grid[x][y] = new Void();
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
