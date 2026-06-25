#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int WIDTH_HARD = 61;
const int HEIGHT_HARD = 25;
const int WIDTH_EASY = 21;
const int HEIGHT_EASY = 10;

char maze[HEIGHT_HARD][WIDTH_HARD + 1];
int playerX, playerY;
int exitX, exitY;
int currentWidth, currentHeight;

enum Difficulty { EASY, HARD };

const char* easyMaze[HEIGHT_EASY] = {
    "#####################",
    "#             #     #",
    "# ##### ##### # ### #",
    "# #         # #   # #",
    "# # ##### # # ### # #",
    "# # #   # # #     # #",
    "# ### # # # ##### # #",
    "#     # # #     #   #",
    "# ### # # ##### ### #",
    "#####################"
};

const char* hardMaze[HEIGHT_HARD] = {
    "#############################################################",
    "#     #         #         #     #       #       #     #     #",
    "# ### # ##### ### ### ### # ### ### ### ### ### ### ### ### #",
    "# #   #     #     # #   #   #     #   #     # #   #       # #",
    "# # ####### ##### # # ##### ### ### ##### ### ### ##### # # #",
    "# #       #     #   #     #     #     #   #     #     # #   #",
    "# ####### ### ####### ### ### ####### # ### ### ##### # ### #",
    "#       #   #       #   #   #       # #   # # #     # #     #",
    "####### ### ### ### ### # ##### ### ##### # # ##### ### ### #",
    "#     #     # # #   #   #     # # #     # # # #   #   #   # #",
    "# ### ### ### # # ### ##### ### # ### # # # # ### ### ### ###",
    "#   # #     # #   #     #     #   # # #   #   #     #     # #",
    "### # # ### # ##### ### ### ### ### # ######### ### ### # # #",
    "#   #   # # #     # #     #     #   #         #   #   # # # #",
    "# ### ### # ##### ### ### ### ### ########### ### ### # # # #",
    "# #   #   #     #     #   # #   #         #   #     #   #   #",
    "# # ### ######### ### ### # # ### ##### ### ####### ### ### #",
    "# # #   #       #   #   # #   #     #     #       # #   #   #",
    "# # # ### ### ### ### # ##### ##### # ### ### ### # # ### # #",
    "#   #     #   #     # #     #     # #   #     # #   #     # #",
    "### ####### ### ### ### ### ##### # ### ### # # ####### # ###",
    "#         #     #       #         #     #   #         #     #",
    "####### ### ### ### ### ### ### ### ### ### ### ### ### ### #",
    "#     #     #     #     #     #     #     #     #     #     #",
    "#############################################################"
};


void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void loadMaze(Difficulty level) {
    if (level == EASY) {
        currentWidth = WIDTH_EASY;
        currentHeight = HEIGHT_EASY;
        for (int y = 0; y < HEIGHT_EASY; y++) {
            strncpy_s(maze[y], currentWidth + 1, easyMaze[y], currentWidth);
        }
    } else {
        currentWidth = WIDTH_HARD;
        currentHeight = HEIGHT_HARD;
        for (int y = 0; y < HEIGHT_HARD; y++) {
            strncpy_s(maze[y], currentWidth + 1, hardMaze[y], currentWidth);
        }
    }

    vector<pair<int, int>> empty;
    for (int y = 0; y < currentHeight; y++) {
        for (int x = 0; x < currentWidth; x++) {
            if (maze[y][x] == ' ') empty.push_back({ x, y });
        }
    }

    srand(static_cast<unsigned int>(time(0)));

    auto pos = empty[rand() % empty.size()];
    playerX = pos.first;
    playerY = pos.second;

    empty.erase(remove(empty.begin(), empty.end(), pos), empty.end());
auto exitPos = empty[rand() % empty.size()];
    exitX = exitPos.first;
    exitY = exitPos.second;
    maze[exitY][exitX] = 'X';
}
void drawMaze() {
    system("cls");
    for (int y = 0; y < currentHeight; y++) {
        for (int x = 0; x < currentWidth; x++) {
            if (x == playerX && y == playerY) {
                SetColor(10); cout << '@'; SetColor(7);
            }
            else if (x == exitX && y == exitY) {
                SetColor(12); cout << 'X'; SetColor(7);
            }
            else {
                cout << maze[y][x];
            }
        }
        cout << endl;
    }
}

void movePlayer(char key) {
    int dx = 0, dy = 0;
    if (key == 'w') dy = -1;
    else if (key == 's') dy = 1;
    else if (key == 'a') dx = -1;
    else if (key == 'd') dx = 1;

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX >= 0 && newX < currentWidth && newY >= 0 && newY < currentHeight &&
        (maze[newY][newX] == ' ' || maze[newY][newX] == 'X')) {
        playerX = newX;
        playerY = newY;
    }
}

bool playGame(Difficulty level) {
    loadMaze(level);

    while (true) {
        drawMaze();

        if (playerX == exitX && playerY == exitY) {
            cout << "\nВи дійшли до виходу! Перемога!" << endl;
            cout << "Натисніть будь-яку клавішу, щоб повернутися в меню..." << endl;
            _getch();
            return true;
        }

        char key = _getch();
        if (key == 27) return false;
        movePlayer(tolower(key));
    }
}

void showMenu() {
    while (true) {
        system("cls");
        cout << "\n===== ЛАБІРИНТ =====\n"<< endl;
        cout << "1. Легкий рівень" << endl;
        cout << "2. Складний рівень" << endl;
        cout << "3. Вихід \n" << endl;
        cout << "Оберіть опцію: ";

        char choice = _getch();

        if (choice == '1') playGame(EASY);
        else if (choice == '2') playGame(HARD);
        else if (choice == '3') break;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");
    showMenu();
    return 0;
}