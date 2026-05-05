#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>

const int arraysize = 25;
bool Life[arraysize][arraysize] = {};

void turn();
void reproduction();
void overpopulation();
void underpopulation();
void createarray();
void printarray();
 int neighborscount(int i,int j);

	//\
	@ живая
	//\
	- мертвая

int main()
{
	createarray();
	printarray();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	for (int i = 0; i < 100; i++) {
		turn();
	}
	return 1;
}
void createarray() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution rand1(0.5);
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			Life[i][j] = rand1(gen);
		}
	}
}
void printarray() {
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			std::cout << (Life[i][j] == 0 ? "-" : "@") << " ";
		}
		std::cout << "\n";
	}
}
void turn() {
	std::system("cls");
	reproduction();
	overpopulation();
	underpopulation();
	printarray();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
int neighborscount(int i, int j) { //живые соседи
	int c = 0;
	return c;
}
void reproduction() {
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if ((neighborscount(i,j) == 3) && (Life[i][j] == 0)) {
				Life[i][j] = 1;
			}
		}
	}
}
void overpopulation() {
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if ((neighborscount(i, j) > 3) && (Life[i][j] == 1)) {
				Life[i][j] = 0;
			}
		}
	}
}
void underpopulation() {
	for (int i = 0; i < arraysize; i++) {
		for (int j = 0; j < arraysize; j++) {
			if ((neighborscount(i, j) < 2) && (Life[i][j] == 1)) {
				Life[i][j] = 0;
			}
		}
	}
}
