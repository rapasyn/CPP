#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>

const int arraysize = 25;
bool Life[arraysize][arraysize] = {};
bool nextLife[arraysize][arraysize] = {};

void turn(int generation);
void createarray();
void printarray();
int neighborscount(int i, int j);
void updateGeneration();
bool checkStagnation();
bool checkExtinction();
void saveGenerationForStagnation();
bool compareWithPrevious();

bool previousLife[arraysize][arraysize] = {};
int stagnationCounter = 0;
const int maxStagnationGenerations = 5; // Если 5 поколений без изменений - останавливаем

// @ - живая
// - - мертвая

int main()
{
    setlocale(LC_ALL, "ru");
    createarray();
    printarray();
    std::cout << "Игра начинается через 5 секунд..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    int generation = 1;
    const int maxGenerations = 200; // Максимальное количество поколений

    while (generation <= maxGenerations) {
        turn(generation);

        // Проверяем условия окончания игры
        if (checkExtinction()) {
            std::cout << "\n=== ИГРА ОКОНЧЕНА ===" << std::endl;
            std::cout << "Все клетки мертвы. Жизнь исчезла!" << std::endl;
            std::cout << "Поколений прожито: " << generation << std::endl;
            break;
        }

        if (checkStagnation()) {
            std::cout << "\n=== ИГРА ОКОНЧЕНА ===" << std::endl;
            std::cout << "Достигнута стагнация - состояние не меняется "
                << maxStagnationGenerations << " поколений подряд." << std::endl;
            std::cout << "Поколений прожито: " << generation << std::endl;
            break;
        }

        generation++;
    }

    if (generation > maxGenerations) {
        std::cout << "\n=== ИГРА ОКОНЧЕНА ===" << std::endl;
        std::cout << "Достигнуто максимальное количество поколений: " << maxGenerations << std::endl;
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.get();
    return 0;
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
    int C = 0;
    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            std::cout << (Life[i][j] == 0 ? "- " : "@ ");
            if (Life[i][j] == 1) C++;
        }
        std::cout << "\n";
    }
    std::cout << "\nЖивых клеток: " << C << std::endl;
}

int neighborscount(int i, int j) {
    int c = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;

            int ni = i + di;
            int nj = j + dj;

            if (ni >= 0 && ni < arraysize && nj >= 0 && nj < arraysize) {
                if (Life[ni][nj] == 1) {
                    c++;
                }
            }
        }
    }
    return c;
}

void updateGeneration() {
    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            int neighbors = neighborscount(i, j);

            if (Life[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    nextLife[i][j] = 0;
                }
                else {
                    nextLife[i][j] = 1;
                }
            }
            else {
                if (neighbors == 3) {
                    nextLife[i][j] = 1;
                }
                else {
                    nextLife[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            Life[i][j] = nextLife[i][j];
        }
    }
}

void saveGenerationForStagnation() {
    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            previousLife[i][j] = Life[i][j];
        }
    }
}

bool compareWithPrevious() {
    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            if (Life[i][j] != previousLife[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool checkStagnation() {
    if (compareWithPrevious()) {
        stagnationCounter++;
        if (stagnationCounter >= maxStagnationGenerations) {
            return true;
        }
    }
    else {
        stagnationCounter = 0;
    }
    return false;
}

bool checkExtinction() {
    for (int i = 0; i < arraysize; i++) {
        for (int j = 0; j < arraysize; j++) {
            if (Life[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

void turn(int generation) {
    if (generation == 1) {
        saveGenerationForStagnation();
    }

    updateGeneration();

    std::system("cls");
    std::cout << "Поколение: " << generation <<"\n";

    printarray();

    std::cout << "\nСтатус: ";
    if (checkExtinction()) {
        std::cout << "ВСЕ МЕРТВЫ";
    }
    else if (stagnationCounter > 0) {
        std::cout << "Стагнация: " << stagnationCounter << "/" << maxStagnationGenerations;
    }
    else {
        std::cout << "Эволюция продолжается";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}
