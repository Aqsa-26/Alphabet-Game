#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game {
public:
    char alphabet;
    int x, y;
    int score;

    Game() {
        score = 0;
        spawn();
    }

    void spawn() {
        alphabet = 'A' + rand() % 26;
        x = rand() % 80 + 1;
        y = 1;
    }

    void move() {
        y++;
    }

    void draw() {
        cout << "\r";
        for (int i = 0; i < y; i++) {
            cout << "\n";
        }
        for (int i = 0; i < x; i++) {
            cout << " ";
        }
        cout << alphabet;
    }

    void clear() {
        cout << "\r";
        for (int i = 0; i < y; i++) {
            cout << "\n";
        }
        for (int i = 0; i < x; i++) {
            cout << " ";
        }
        cout << " ";
    }

    void checkInput(char input) {
        if (input == alphabet) {
            score++;
            spawn();
        }
    }

    void printGameName() {
        string name[3] = {
            "======================",
            "   Galactic Typing    ",
            "======================"
        };

        // Get console width
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        // Calculate padding to center text
        int padding = (columns - name[1].length()) / 2;

        for (int i = 0; i < 3; i++) {
            cout << string(padding, ' ') << name[i] << endl;
        }
    }

    void reset() {
        score = 0;
        spawn();
        system("cls");
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    Game game;
    char input;
    system("color 0A");

    while (true) {
        // Display the name of the game
        game.printGameName();
        cout << "\nPress any key to start the game..." << endl;
        _getch(); // Wait for user to press a key

        bool gameOver = false;

        while (!gameOver) {
            game.move();
            game.draw();

            if (_kbhit()) {
                input = _getch();
                game.checkInput(input);
            }

            if (game.y > 20) {
                cout << "\n\nGame Over! Final Score: " << game.score << endl;
                gameOver = true;
            }

            Sleep(200);
            game.clear();
        }

        cout << "\nPress 'r' to restart or any other key to exit..." << endl;
        input = _getch();
        if (input != 'r' && input != 'R') {
            break;
        }

        game.reset();
    }

    return 0;
}

