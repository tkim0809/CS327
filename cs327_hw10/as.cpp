#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <ncurses.h>

const int HEALTH_POINTS = 10;
const std::string airplaneNames[] = {"Skybolt", "Thunderstrike", "Fireball"};
const std::string playerAirplane[] = {" >", "=>", "==>"};
const std::string enemyAirplane[] = {" <", "=<", "<=="};

const int PLAYER_COLOR_PAIR = 1;
const int ENEMY_COLOR_PAIR = 2;
const int BULLET_COLOR_PAIR = 3;

struct Bullet {

    int x;
    int y;
    int speed;
    bool homing;

};

void init_colors() {

    start_color();
    init_pair(PLAYER_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(ENEMY_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(BULLET_COLOR_PAIR, COLOR_YELLOW, COLOR_BLACK);

}

void draw(WINDOW* win, int playerHealth, int enemyHealth, int playerY, int enemyY, std::vector<Bullet>& playerBullets, std::vector<Bullet>& enemyBullets, int airplaneChoice) {

    wclear(win); // Clear the screen

    for (int y = 0; y < 20; ++y) {

        for (int x = 0; x < 40; ++x) {

            bool is_drawn = false;

            if (y == playerY && x >= 0 && x < 3) {

                wattron(win, COLOR_PAIR(PLAYER_COLOR_PAIR));
                mvwaddch(win, y, x, playerAirplane[airplaneChoice][x]); // Draw player
                wattroff(win, COLOR_PAIR(PLAYER_COLOR_PAIR));
                is_drawn = true;

            } else if (y == enemyY && x >= 37 && x < 40) {

                wattron(win, COLOR_PAIR(ENEMY_COLOR_PAIR));
                mvwaddch(win, y, x, enemyAirplane[airplaneChoice][x - 37]); // Draw enemy
                wattroff(win, COLOR_PAIR(ENEMY_COLOR_PAIR));
                is_drawn = true;

            }

            for (const auto& bullet : playerBullets) {

                if (y == bullet.y && x == bullet.x) {
                    
                    wattron(win, COLOR_PAIR(BULLET_COLOR_PAIR));
                    mvwaddch(win, y, x, '*'); // Draw player bullet
                    wattroff(win, COLOR_PAIR(BULLET_COLOR_PAIR));
                    is_drawn = true;
                    break;

                }

            }

            for (const auto& bullet : enemyBullets) {

                if (y == bullet.y && x == bullet.x) {

                    wattron(win, COLOR_PAIR(BULLET_COLOR_PAIR));
                    mvwaddch(win, y, x, '-'); // Draw enemy bullet
                    wattroff(win, COLOR_PAIR(BULLET_COLOR_PAIR));
                    is_drawn = true;
                    break;

                }

            }

            if (!is_drawn) {

                mvwaddch(win, y, x, ' '); // Draw empty space

            }

        }

    }

    mvwprintw(win, 20, 0, "Player health: %d | Enemy health: %d", playerHealth, enemyHealth);
    wrefresh(win);

}


void fight(WINDOW* win, int airplaneChoice, int difficulty) {

    int playerHealth = HEALTH_POINTS;
    int enemyHealth = HEALTH_POINTS;
    int playerY = 5;
    int enemyY = 0;
    int enemyDirection = 1;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    bool specialActive = false;
    auto specialActivatedAt = std::chrono::steady_clock::now();

    // Adjust enemy AI based on difficulty
    int enemyShotFrequency = 10;
    if (difficulty == 0) { // Easy
        enemyShotFrequency = 15;
    } else if (difficulty == 1) { // Medium
        enemyShotFrequency = 10;
    } else if (difficulty == 2) { // Hard
        enemyShotFrequency = 5;
    }

    nodelay(win, TRUE);
    keypad(win, TRUE);
    curs_set(0);

    while (playerHealth > 0 && enemyHealth > 0) {

        draw(win, playerHealth, enemyHealth, playerY, enemyY, playerBullets, enemyBullets, airplaneChoice);

        // Handle player input
        int ch = getch();

        switch (ch) {

            case KEY_UP:

                if (playerY > 0) {

                    --playerY;

                }

                break;

            case KEY_DOWN:

                if (playerY < 19) {

                    ++playerY;

                }

                break;

            case 'q':

                playerBullets.push_back({1, playerY, 2, false});
                break;

            case 'w':

                if (!specialActive) {

                    specialActive = true;
                    specialActivatedAt = std::chrono::steady_clock::now();

                    switch (airplaneChoice) {

                        case 0:
                            for (int i = -2; i <= 2; ++i) {

                                playerBullets.push_back({1, playerY + i, 2, false});

                            }
                            break;
                        case 1:
                            for (auto& bullet : playerBullets) {

                                bullet.speed = 4;

                            }
                            break;
                        case 2:

                            playerBullets.push_back({1, playerY, 2, true});
                            break;
                    }

                }

                break;

        }

        // Check if special skill duration has ended
        if (specialActive && airplaneChoice == 1) {

            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - specialActivatedAt).count() >= 5) {

                specialActive = false;

                for (auto& bullet : playerBullets) {

                    bullet.speed = 2;

                }
        
            }

        }


        // Move player bullets
        for (auto& bullet : playerBullets) {

            bullet.x += bullet.speed;

            if (airplaneChoice == 2 && bullet.homing) {

                if (bullet.y < enemyY) {

                    ++bullet.y;

                } else if (bullet.y > enemyY) {

                    --bullet.y;

                }

            }

        }

        playerBullets.erase(std::remove_if(playerBullets.begin(), playerBullets.end(), [&](const Bullet& bullet) {

            if (bullet.x >= 37 && bullet.y == enemyY) {

                int damage = (airplaneChoice == 2 && bullet.homing) ? 1 : 2;
                enemyHealth -= damage;

                return true;

            }

            return bullet.x > 40;
        }), playerBullets.end());

        // Move enemy bullets
        for (auto& bullet : enemyBullets) {

            bullet.x -= bullet.speed;

        }

        enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [&](const Bullet& bullet) {

            if (bullet.x >= 0 && bullet.x < 3 && bullet.y == playerY) {
                playerHealth -= 2;
                return true;
            }

            return bullet.x < 0;
        }), enemyBullets.end());

        // Enemy AI
        enemyY += enemyDirection;
        if (enemyY <= 0 || enemyY >= 19) {

            enemyDirection *= -1;

        }

          if (std::rand() % 10 == 0) {

            enemyDirection = std::rand() % 3 - 1; // Randomly choose a direction: -1, 0, or 1

        }

        enemyY += enemyDirection;

        if (enemyY < 0) {

            enemyY = 0;

        } else if (enemyY > 19) {

            enemyY = 19;

        }

        if (std::rand() % enemyShotFrequency == 0) {

            enemyBullets.push_back({38, enemyY, 2, false});

        }

        // Check for game over
        if (playerHealth <= 0 || enemyHealth <= 0) {

            break;

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (playerHealth <= 0) {

        printw("You have been defeated!\n");

    } else {

        printw("You have won the battle!\n");

    }

    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    endwin();

}

int main() {

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    srand(time(0));

    init_colors(); // Initialize colors

    printw("Welcome to Airplane Battle!\n");
    printw("Choose your airplane:\n");
    for (size_t i = 0; i < sizeof(airplaneNames) / sizeof(airplaneNames[0]); ++i) {
        printw("%zu. %s\n", i + 1, airplaneNames[i].c_str());
    }
    refresh();

    int airplaneChoice;
    airplaneChoice = getch() - '1';

    
    printw("Choose the difficulty:\n");
    printw("1. Easy\n");
    printw("2. Medium\n");
    printw("3. Hard\n");
    refresh();

    int difficulty;
    difficulty = getch() - '1';

    if (difficulty >= 0 && difficulty < 3) {

    fight(stdscr, airplaneChoice, difficulty);

} else {

    printw("Invalid choice! Exiting...\n");
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(3));

}

    endwin();

    return 0;
}

