#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>

int mod(int num1, int num2) {
    return num1 % num2 >= 0 ? num1 % num2 : num2 + num1 % num2;
}

int countNeigbours(bool *gamefield, int i, int j, int CELLWIDTH, int CELLHIGHT) {
    int count = 0;
    for (int ii = -1; ii <= 1; ++ii) {
        for (int jj = -1; jj <= 1; ++jj) {
            if (ii != 0 || jj != 0) {
                if ((gamefield + CELLHIGHT * mod((i + ii), CELLWIDTH))[mod((j + jj), CELLHIGHT)]) {
                    ++count;
                }
            }
        }
    }
    return count;
}

void randField(bool* gamefield, int CELLWIDTH, int CELLHIGHT){
    std::srand(std::time(nullptr));
    for (int i = 0; i < CELLWIDTH; ++i) {
        for (int j = 0; j < CELLHIGHT; ++j) {
            *(gamefield + CELLHIGHT * i + j) = std::rand()%2;
        }
    }
}

int main() {
    constexpr int WIDTH = 2560;
    constexpr int HEIGHT = 1600;

    constexpr int CELLSIZE = 3;
    constexpr int CELLWIDTH = WIDTH / CELLSIZE;
    constexpr int CELLHIGHT = HEIGHT / CELLSIZE;

    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "GAME LIFE", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    bool gamefield[CELLWIDTH][CELLHIGHT]{};
    bool pause = true;
    sf::RectangleShape rect(sf::Vector2f(CELLSIZE, CELLSIZE));
    rect.setFillColor(sf::Color::White);

    sf::Event event{};
    while (window.isOpen()) {


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.scancode == sf::Keyboard::Scancode::P) {
                    pause = !pause;
                }
                if (event.key.scancode == sf::Keyboard::Scancode::R) {
                    randField(&gamefield[0][0], CELLWIDTH, CELLHIGHT);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2 mouseCoords = sf::Mouse::getPosition(window);
                    gamefield[mouseCoords.x / CELLSIZE][mouseCoords.y / CELLSIZE] = true;
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2 mouseCoords = sf::Mouse::getPosition(window);
                    std::cout << countNeigbours(&gamefield[0][0], mouseCoords.x / CELLSIZE, mouseCoords.y / CELLSIZE,
                                                CELLWIDTH, CELLHIGHT) << std::endl;
                }
            }

        }

        if (!pause) {
            bool newGameField[CELLWIDTH][CELLHIGHT]{};
            for (int i = 0; i < CELLWIDTH; ++i) {
                for (int j = 0; j < CELLHIGHT; ++j) {
                    int count = countNeigbours(&gamefield[0][0], i, j, CELLWIDTH, CELLHIGHT);

                    if (gamefield[i][j] && (count < 2 || count > 3)) {
                        newGameField[i][j] = false;
                    } else if (gamefield[i][j]) {
                        newGameField[i][j] = true;
                    } else if ((!gamefield[i][j]) && count == 3) {
                        newGameField[i][j] = true;
                    } else {
                        newGameField[i][j] = false;
                    }
                }
            }
            for (int i = 0; i < CELLWIDTH; ++i) {
                for (int j = 0; j < CELLHIGHT; ++j) {
                    gamefield[i][j] = newGameField[i][j];
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < CELLWIDTH; ++i) {
            for (int j = 0; j < CELLHIGHT; ++j) {
                if (gamefield[i][j]) {
                    rect.setPosition(i * CELLSIZE, j * CELLSIZE);
                    window.draw(rect);
                }
            }
        }

        window.display();
    }

    return 0;
}