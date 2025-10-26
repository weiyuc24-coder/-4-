#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int playerAmount;
int cardsLeft = 76;
int eachCardsLeft[9] = {9, 9, 9, 9, 9, 9, 9, 3, 10};           // cards of each type left
int dealtCards[5][9] = {};                                     // 0: user, 1: AI1, 2: AI2, 3: AI3 4: AI4
vector<int> areaCards[5] = {};                                 // 5 areas, each area can hold up to 3 cards
bool playerFinished[5] = {false, false, false, false, false};  // whether player has finished their turn
bool areaTaken[5] = {false, false, false, false, false};       // whether area has been taken
string colors[9] = {"Red", "Pink", "Yellow", "Orange", "Blue", "Green", "Gray", "Rainbow", "Plus2"};
bool isLastRound = false, isGameEnd = false;
int finalScores[7] = {0, 1, 3, 6, 10, 15, 21};

void first_deal(int);
void show_each_hands();
void show_table_cards();
void game_loop(int, int);
int draw_card();
void place_card(int);
void user_take_area();
void AI(int);
int next_player(int);
void new_round();
void count_score();

int main() {
    bool doExit = false;
    while (!doExit) {
        cout << "\n=== Welcome to Join the Game ===\n";
        cout << "Enter number of players (3-5): ";
        while (scanf("%d", &playerAmount) != 1 || playerAmount < 3 || playerAmount > 5) {
            while (getchar() != '\n');  // clear invalid input
            cout << "Invalid input. Please enter a number between 3 and 5: ";
        }
        if (playerAmount == 3) {
            srand(time(0));
            int removedColor = rand() % 7;  // randomly remove one color
            eachCardsLeft[removedColor] = 0;
            cardsLeft -= 9;
        }
        first_deal(playerAmount);
        game_loop(playerAmount, 0);
        count_score();
        cout << "\nDo you want to play again? (1: Yes, 0: No): ";
        int playAgain;
        while (scanf("%d", &playAgain) != 1 || (playAgain != 0 && playAgain != 1)) {
            while (getchar() != '\n');  // clear invalid input
            cout << "Invalid input. Please enter 1 for Yes or 0 for No: ";
        }
        if (playAgain == 0) {
            doExit = true;
        } else {
            // reset game state
            cardsLeft = 76;
            memset(eachCardsLeft, 9, sizeof(eachCardsLeft));
            eachCardsLeft[7] = 3;
            eachCardsLeft[8] = 10;
            memset(dealtCards, 0, sizeof(dealtCards));
            for (int i = 0; i < 5; i++) {
                areaCards[i].clear();
            }
            memset(playerFinished, false, sizeof(playerFinished));
            memset(areaTaken, false, sizeof(areaTaken));
            isLastRound = false;
            isGameEnd = false;
        }
    }

    return 0;
}

void first_deal(int playerAmount) {
    cout << "\n--- First Deal ---\n";
    int card1[5] = {0};
    srand(time(0));
    do {
        card1[0] = rand() % 7;
    } while (eachCardsLeft[card1[0]] == 0);
    do {
        card1[1] = rand() % 7;
    } while (card1[1] == card1[0] || eachCardsLeft[card1[1]] == 0);
    do {
        card1[2] = rand() % 7;
    } while (card1[2] == card1[0] || card1[2] == card1[1] || eachCardsLeft[card1[2]] == 0);
    if (playerAmount >= 4) {
        do {
            card1[3] = rand() % 7;
        } while (card1[3] == card1[0] || card1[3] == card1[1] || card1[3] == card1[2] || eachCardsLeft[card1[3]] == 0);
    }
    if (playerAmount == 5) {
        do {
            card1[4] = rand() % 7;
        } while (card1[4] == card1[0] || card1[4] == card1[1] || card1[4] == card1[2] || card1[4] == card1[3] || eachCardsLeft[card1[3]] == 0);
    }

    for (int i = 0; i < playerAmount; i++) {
        dealtCards[i][card1[i]]++;
        eachCardsLeft[card1[i]]--;
        cardsLeft--;
    }
    show_each_hands();
    show_table_cards();
}

void show_each_hands() {
    cout << "\nUser:\n"
         << "Red\tPink\tYellow\tOrange\tBlue\tGreen\tGray\tRainbow\tPlus2\n"
         << dealtCards[0][0] << "\t" << dealtCards[0][1] << "\t" << dealtCards[0][2] << "\t" << dealtCards[0][3] << "\t" << dealtCards[0][4] << "\t" << dealtCards[0][5] << "\t" << dealtCards[0][6] << "\t" << dealtCards[0][7] << "\t" << dealtCards[0][8] << "\n";
    for (int i = 1; i < playerAmount; i++) {
        cout << "AI" << i << ":\n"
             << "Red\tPink\tYellow\tOrange\tBlue\tGreen\tGray\tRainbow\tPlus2\n"
             << dealtCards[i][0] << "\t" << dealtCards[i][1] << "\t" << dealtCards[i][2] << "\t" << dealtCards[i][3] << "\t" << dealtCards[i][4] << "\t" << dealtCards[i][5] << "\t" << dealtCards[i][6] << "\t" << dealtCards[i][7] << "\t" << dealtCards[i][8] << "\n";
    }
}

void show_table_cards() {
    cout << "\nTable Cards:\n";
    for (int i = 0; i < playerAmount; i++) {
        cout << "Area" << i + 1 << ": ";
        if (areaTaken[i]) {
            cout << "[Already been taken]\n";
            continue;
        } else if (areaCards[i].empty()) {
            cout << "[Empty]\n";
            continue;
        }
        for (int j = 0; j < areaCards[i].size(); j++) {
            cout << colors[areaCards[i][j]] << "\t";
        }
        cout << "\n";
    }
}

void game_loop(int playerAmount, int currentPlayer) {
    if (isGameEnd) return;
    if (currentPlayer == 0) {
        cout << "\nUser's turn\nInput 1 to draw card to place on the area, 2 to take card from area\n";
        int userAction;
        while (scanf("%d", &userAction) != 1 || (userAction != 1 && userAction != 2)) {
            while (getchar() != '\n');  // clear invalid input
            cout << "Invalid input. Please input 1 to draw card to place on the area, 2 to take card from area\n";
        }
        if (userAction == 1) {
            place_card(draw_card());
        } else {
            user_take_area();
        }
    } else {
        cout << "\nAI" << currentPlayer << "'s turn\n";
        AI(currentPlayer);
    }
    game_loop(playerAmount, next_player(currentPlayer));
}

int draw_card() {
    bool canPlace = false;  // check if there is space to place the card
    for (int i = 0; i < playerAmount; i++) {
        if (areaTaken[i]) continue;
        if (areaCards[i].size() < 3) {
            canPlace = true;
            break;
        }
    }
    if (!canPlace) {
        cout << "All areas are full, you can only take area back\n";
        return -1;
    } else {
        while (true) {
            int card = rand() % 9;  // draw a random card
            if (eachCardsLeft[card] > 0) {
                eachCardsLeft[card]--;
                cardsLeft--;
                if (cardsLeft == 14) {
                    isLastRound = true;
                    cout << "\n!!!Last round triggered!!!\n\n";
                }
                cout << "You drew a \"" << colors[card] << "\" card.\n";
                return card;
            }
        }
    }
}

void place_card(int card) {
    if (card == -1) {
        user_take_area();
        return;
    }
    cout << "Choose an area to place the card (1-" << playerAmount << "): ";
    int inputArea;
    while (scanf("%d", &inputArea) != 1 || inputArea < 1 || inputArea > playerAmount) {
        while (getchar() != '\n');  // clear invalid input
        cout << "Invalid input. Please choose an area to place the card (1-" << playerAmount << "): ";
    }
    if (areaTaken[inputArea - 1]) {
        cout << "This area has been taken. Choose another area.\n";
        place_card(card);
    } else if (areaCards[inputArea - 1].size() < 3) {
        areaCards[inputArea - 1].push_back(card);
        cout << "Placed \"" << colors[card] << "\" card in Area" << inputArea << ".\n";
        show_each_hands();
        show_table_cards();
    } else {
        cout << "This area is full. Choose another area.\n";
        place_card(card);
    }
}

void user_take_area() {
    int cardsInAreas = 0;
    for (int i = 0; i < playerAmount; i++) {
        cardsInAreas += areaCards[i].size();
    }
    if (cardsInAreas > 0) {
        while (true) {
            cout << "Choose an area to take back (1-" << playerAmount << "): ";
            int takenArea;
            if (scanf("%d", &takenArea) == 1 && takenArea >= 1 && takenArea <= playerAmount) {
                if (!areaCards[takenArea - 1].empty()) {
                    for (int card : areaCards[takenArea - 1]) {
                        dealtCards[0][card]++;
                    }
                    areaCards[takenArea - 1].clear();
                    areaTaken[takenArea - 1] = true;
                    cout << "You took back Area" << takenArea << ".\n";
                    show_each_hands();
                    show_table_cards();
                    playerFinished[0] = true;
                    break;
                } else {
                    cout << "This area has been taken, please take another one\n";
                }
            } else {
                while (getchar() != '\n');  // clear invalid input
                cout << "Invalid input. Please choose an area to take back (1-" << playerAmount << "): ";
            }
        }
    } else {
        cout << "There are no area you can take back, you can only draw card\n";
        place_card(draw_card());
    }
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

void AI(int AIIndex) {
    int worthAction[6] = {8, 0, 0, 0, 0, 0};  // 0: draw, 1-5: take area 1-5
    pair<int, int> AICards[9];                // color, count
    for (int i = 0; i < 9; i++) {
        AICards[i] = make_pair(i, dealtCards[AIIndex][i]);
    }
    sort(AICards, AICards + 7, cmp);
    int areaLeft = 3 * playerAmount;
    for (int i = 0; i < playerAmount; i++) {
        if (areaTaken[i]) {
            worthAction[i + 1] = -100;  // cannot take taken area
            areaLeft -= 3;
        } else if (areaCards[i].size() > 1) {
            worthAction[0] -= 3;
            areaLeft -= areaCards[i].size();
            for (int card : areaCards[i]) {
                if (card == 7 && AICards[0].second + AICards[1].second + AICards[2].second < 18 - AICards[7].second) {
                    worthAction[i + 1] += 6;
                } else if (card == 8) {
                    worthAction[i + 1] += 3;
                } else {
                    for (int j = 0; j < 3; j++) {
                        if (card == AICards[j].first) {
                            worthAction[i + 1] += (4 - j) * AICards[j].second * 3;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (areaLeft == 0) {
        worthAction[0] = -100;  // cannot draw if no space to place
    }
    int bestAction = max_element(worthAction, worthAction + playerAmount + 1) - worthAction;
    if (bestAction == 0) {
        cout << "AI" << AIIndex << " decides to draw a card to place.\n";
        srand(time(0));
        int drawnCard;
        while (true) {
            drawnCard = rand() % 9;
            if (eachCardsLeft[drawnCard] > 0) {
                eachCardsLeft[drawnCard]--;
                cardsLeft--;
                if (cardsLeft == 14) {
                    isLastRound = true;
                    cout << "\n!!!Last round triggered!!!\n\n";
                }
                break;
            }
        }
        cout << "AI" << AIIndex << " drew a \"" << colors[drawnCard] << "\" card.\n";
        // place drawn card and place the area that maximizes its benefit
        if (drawnCard == 7 || drawnCard == 8) {
            int leastFilledArea = -1, minCards = 3;
            for (int i = 0; i < playerAmount; i++) {
                if (!areaTaken[i] && areaCards[i].size() < minCards) {
                    minCards = areaCards[i].size();
                    leastFilledArea = i;
                }
            }
            areaCards[leastFilledArea].push_back(drawnCard);
            cout << "AI" << AIIndex << " placed \"" << colors[drawnCard] << "\" card in Area" << leastFilledArea + 1 << ".\n";
        } else {
            int benefits[5] = {0};
            for (int i = 0; i < playerAmount; i++) {
                if (!areaTaken[i] && areaCards[i].size() < 3) {
                    int benefit = 0;
                    for (int j = 0; j < 3; j++) {
                        if (drawnCard == AICards[j].first) {
                            benefit += (4 - j) * AICards[j].second;
                            break;
                        }
                    }
                    benefits[i] = benefit;
                }
            }
            int bestArea = 0, bestBenefit = 0;
            if (drawnCard == AICards[4].first || drawnCard == AICards[5].first || drawnCard == AICards[6].first) {
                for (int i = 0; i < playerAmount; i++) {
                    if (areaTaken[i] || areaCards[i].size() >= 3) {
                        if (bestArea == i) {
                            bestArea++;
                        }
                    } else if (benefits[i] < bestBenefit) {
                        bestArea = i;
                        bestBenefit = benefits[i];
                    }
                }
            } else {
                for (int i = 0; i < playerAmount; i++) {
                    if (areaTaken[i] || areaCards[i].size() >= 3) {
                        if (bestArea == i) {
                            bestArea++;
                        }
                    } else if (benefits[i] > bestBenefit) {
                        bestArea = i;
                        bestBenefit = benefits[i];
                    }
                }
            }
            areaCards[bestArea].push_back(drawnCard);
            cout << "AI" << AIIndex << " placed \"" << colors[drawnCard] << "\" card in Area" << bestArea + 1 << ".\n";
        }
        show_each_hands();
        show_table_cards();
    } else {
        cout << "AI" << AIIndex << " decides to take back Area" << bestAction << ".\n";
        for (int card : areaCards[bestAction - 1]) {
            dealtCards[AIIndex][card]++;
        }
        areaCards[bestAction - 1].clear();
        areaTaken[bestAction - 1] = true;
        playerFinished[AIIndex] = true;
        show_each_hands();
        show_table_cards();
    }
}

int next_player(int currentPlayer) {
    int next = (currentPlayer + 1) % playerAmount;
    while (playerFinished[next]) {
        next = (next + 1) % playerAmount;
        if (next == currentPlayer && playerFinished[next]) {
            new_round();
            break;
        }
    }
    return next;
}

void new_round() {
    if (isLastRound) {
        isGameEnd = true;
        cout << "\n--- Game Over ---\n";
        return;
    }
    cout << "\n--- New Round ---\n";
    memset(playerFinished, false, sizeof(playerFinished));
    memset(areaTaken, false, sizeof(areaTaken));
    show_table_cards();
}

void count_score() {
    for (int i = 0; i < playerAmount; i++) {
        sort(dealtCards[i], dealtCards[i] + 7, greater<int>());
        for (int j = 0; j < 7; j++) {
            if (dealtCards[i][j] >= 7) {
                dealtCards[i][j] = 6;
            }
            if (i < 3) {
                if (dealtCards[i][j] < 6) {
                    if (dealtCards[i][7] > 6 - dealtCards[i][j]) {
                        dealtCards[i][7] -= (6 - dealtCards[i][j]);
                        dealtCards[i][j] = 6;
                    } else {
                        dealtCards[i][j] += dealtCards[i][7];
                        dealtCards[i][7] = 0;
                    }
                }
            }
            dealtCards[i][j] = finalScores[dealtCards[i][j]];
        }
    }
    pair<int, int> scores[5];
    for (int i = 0; i < playerAmount; i++) {
        scores[i] = make_pair(i, 0);  // first: player index, second: score
        sort(dealtCards[i], dealtCards[i] + 7, greater<int>());
        scores[i].second += dealtCards[i][0] + dealtCards[i][1] + dealtCards[i][2];
        scores[i].second += dealtCards[i][8] * 2;
        scores[i].second -= dealtCards[i][3] + dealtCards[i][4] + dealtCards[i][5] + dealtCards[i][6];
    }

    cout << "\n--- Final Scores ---\n";
    sort(scores, scores + playerAmount, cmp);
    int ranking = 1;
    for (int i = 0; i < playerAmount; i++) {
        if (i > 0 && scores[i].second < scores[i - 1].second) {
            ranking = i + 1;
        }
        cout << "Rank " << ranking << "\t";
        if (scores[i].first == 0) {
            cout << "User\t" << scores[i].second << " points\n";
        } else {
            cout << "AI" << scores[i].first << "\t" << scores[i].second << " points\n";
        }
    }
}
