#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// cards that had been used
int red;
int pink;
int yellow;
int orange;
int blue;
int green;
int gray;
int rainbow;
int plus2;

int input_area_again;

int total_used_cards = 0;  // when used cards accumulate to 61, the next card will be END CARD

int area1_placed_card_amount = 0;
int area2_placed_card_amount = 0;
int area3_placed_card_amount = 0;
int area4_placed_card_amount = 0;

int area1[4] = {};
int area2[4] = {};
int area3[4] = {};
int area4[4] = {};

// players' hand cards
int user_cards[10] = {};
int AI1_cards[10] = {};
int AI2_cards[10] = {};
int AI3_cards[10] = {};

enum area_status { no_card,
                   can_put_card,
                   full,
                   been_taken };
enum player_status { play,
                     end_play };
enum round_status { last_round,
                    not_last_round };
enum last_one_or_not { last_one,
                       not_last_one };

round_status last_round_or_not;

last_one_or_not is_user_last_one;
last_one_or_not is_AI1_last_one;
last_one_or_not is_AI2_last_one;
last_one_or_not is_AI3_last_one;

area_status area1_status;
area_status area2_status;
area_status area3_status;
area_status area4_status;

player_status user_status;
player_status AI1_status;
player_status AI2_status;
player_status AI3_status;

void four_player_game_of_user();
void four_people_first_round_draw();
int draw_card();
void place_card(int);
void user_take_area();
void count_point();
int add_to_each_card_sum(int);
int draw_card_again();
void AI1();
void AI2();
void AI3();
void decide_first_player_next_round();
void user_decide_who_is_next_player();
void AI1_decide_who_is_next_player();
void AI2_decide_who_is_next_player();
void AI3_decide_who_is_next_player();

void show_each_player_cards();

void show_table_cards();
void count_area1_cards(int);
void count_area2_cards(int);
void count_area3_cards(int);
void count_area4_cards(int);

int array_for_counting_area1_cards[10];
int array_for_counting_area2_cards[10];
int array_for_counting_area3_cards[10];
int array_for_counting_area4_cards[10];

int main() {
    // cards that had been used
    red = 0;
    pink = 0;
    yellow = 0;
    orange = 0;
    blue = 0;
    green = 0;
    gray = 0;
    rainbow = 0;
    plus2 = 0;

    srand(time(0));

    area1[4] = {};
    area2[4] = {};
    area3[4] = {};
    area4[4] = {};

    last_round_or_not = not_last_round;

    total_used_cards = 0;

    is_user_last_one = not_last_one;
    is_AI1_last_one = not_last_one;
    is_AI2_last_one = not_last_one;
    is_AI3_last_one = not_last_one;

    area1_status = no_card;
    area2_status = no_card;
    area3_status = no_card;
    area4_status = no_card;

    user_status = play;
    AI1_status = play;
    AI2_status = play;
    AI3_status = play;

    four_people_first_round_draw();
    four_player_game_of_user();
}

void four_player_game_of_user() {
    srand(time(0));
    cout << "\nuser's turn\n"
         << "input 1 to draw card, input 2 to take area\n";
    int user_action;
    cin >> user_action;
    while (user_action != 1 && user_action != 2) {
        cout << "input error, please input 1 to draw card, input 2 to take area\n";
        cin >> user_action;
    }
    switch (user_action) {
        case 1:
            place_card(draw_card());
            break;
        case 2:
            user_take_area();
            break;
    }
}

void four_people_first_round_draw() {
    srand(time(0));
    total_used_cards = 4;
    int a = 1 + rand() % 7;
    int b = 1 + rand() % 7;
    int c = 1 + rand() % 7;
    int d = 1 + rand() % 7;
    while (a == b || a == c || a == d || b == c || b == d || c == d)  // if have same card, draw again
    {
        a = 1 + rand() % 7;
        b = 1 + rand() % 7;
        c = 1 + rand() % 7;
        d = 1 + rand() % 7;
    }
    add_to_each_card_sum(a);
    add_to_each_card_sum(b);
    add_to_each_card_sum(c);
    add_to_each_card_sum(d);
    // give cards to players' array
    user_cards[a]++;
    AI1_cards[b]++;
    AI2_cards[c]++;
    AI3_cards[d]++;
    show_each_player_cards();
    show_table_cards();
}

void show_each_player_cards() {
    cout << "\nuser:\n"
         << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << user_cards[1] << setw(10) << user_cards[2] << setw(10) << user_cards[3] << setw(10) << user_cards[4] << setw(10) << user_cards[5] << setw(10) << user_cards[6] << setw(10) << user_cards[7] << setw(10) << user_cards[8] << setw(10) << user_cards[9];

    cout << "\nAI1:\n"
         << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << AI1_cards[1] << setw(10) << AI1_cards[2] << setw(10) << AI1_cards[3] << setw(10) << AI1_cards[4] << setw(10) << AI1_cards[5] << setw(10) << AI1_cards[6] << setw(10) << AI1_cards[7] << setw(10) << AI1_cards[8] << setw(10) << AI1_cards[9];

    cout << "\nAI2:\n"
         << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << AI2_cards[1] << setw(10) << AI2_cards[2] << setw(10) << AI2_cards[3] << setw(10) << AI2_cards[4] << setw(10) << AI2_cards[5] << setw(10) << AI2_cards[6] << setw(10) << AI2_cards[7] << setw(10) << AI2_cards[8] << setw(10) << AI2_cards[9];

    cout << "\nAI3:\n"
         << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << AI3_cards[1] << setw(10) << AI3_cards[2] << setw(10) << AI3_cards[3] << setw(10) << AI3_cards[4] << setw(10) << AI3_cards[5] << setw(10) << AI3_cards[6] << setw(10) << AI3_cards[7] << setw(10) << AI3_cards[8] << setw(10) << AI3_cards[9];
}

void show_table_cards() {
    // clear them to calculate again
    for (int i = 1; i < 11; i++)
        array_for_counting_area1_cards[i] = 0;

    for (int i = 1; i < 4; i++) {
        count_area1_cards(area1[i]);
    }
    cout << "\n\narea1:\n";
    cout << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << array_for_counting_area1_cards[1] << setw(10) << array_for_counting_area1_cards[2] << setw(10) << array_for_counting_area1_cards[3] << setw(10) << array_for_counting_area1_cards[4] << setw(10) << array_for_counting_area1_cards[5] << setw(10) << array_for_counting_area1_cards[6] << setw(10) << array_for_counting_area1_cards[7] << setw(10) << array_for_counting_area1_cards[8] << setw(10) << array_for_counting_area1_cards[9] << endl;

    // clear them to calculate again
    for (int i = 1; i < 11; i++)
        array_for_counting_area2_cards[i] = 0;

    for (int i = 1; i < 4; i++) {
        count_area2_cards(area2[i]);
    }
    cout << "area2:\n";
    cout << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << array_for_counting_area2_cards[1] << setw(10) << array_for_counting_area2_cards[2] << setw(10) << array_for_counting_area2_cards[3] << setw(10) << array_for_counting_area2_cards[4] << setw(10) << array_for_counting_area2_cards[5] << setw(10) << array_for_counting_area2_cards[6] << setw(10) << array_for_counting_area2_cards[7] << setw(10) << array_for_counting_area2_cards[8] << setw(10) << array_for_counting_area2_cards[9] << endl;

    // clear them to calculate again
    for (int i = 1; i < 11; i++)
        array_for_counting_area3_cards[i] = 0;

    for (int i = 1; i < 4; i++) {
        count_area3_cards(area3[i]);
    }
    cout << "area3:\n";
    cout << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << array_for_counting_area3_cards[1] << setw(10) << array_for_counting_area3_cards[2] << setw(10) << array_for_counting_area3_cards[3] << setw(10) << array_for_counting_area3_cards[4] << setw(10) << array_for_counting_area3_cards[5] << setw(10) << array_for_counting_area3_cards[6] << setw(10) << array_for_counting_area3_cards[7] << setw(10) << array_for_counting_area3_cards[8] << setw(10) << array_for_counting_area3_cards[9] << endl;

    // clear them to calculate again
    for (int i = 1; i < 11; i++)
        array_for_counting_area4_cards[i] = 0;

    for (int i = 1; i < 4; i++) {
        count_area4_cards(area4[i]);
    }
    cout << "area4:\n";
    cout << setw(10) << "red" << setw(10) << "pink" << setw(10) << "yellow" << setw(10) << "orange" << setw(10) << "blue" << setw(10) << "green" << setw(10) << "gray" << setw(10) << "rainbow" << setw(10) << "plus2\n";
    cout << setw(10) << array_for_counting_area4_cards[1] << setw(10) << array_for_counting_area4_cards[2] << setw(10) << array_for_counting_area4_cards[3] << setw(10) << array_for_counting_area4_cards[4] << setw(10) << array_for_counting_area4_cards[5] << setw(10) << array_for_counting_area4_cards[6] << setw(10) << array_for_counting_area4_cards[7] << setw(10) << array_for_counting_area4_cards[8] << setw(10) << array_for_counting_area4_cards[9] << endl;
}

void count_area1_cards(int x) {
    switch (x) {
        case 1:
            array_for_counting_area1_cards[1]++;
            break;

        case 2:
            array_for_counting_area1_cards[2]++;
            break;

        case 3:
            array_for_counting_area1_cards[3]++;
            break;

        case 4:
            array_for_counting_area1_cards[4]++;
            break;

        case 5:
            array_for_counting_area1_cards[5]++;
            break;

        case 6:
            array_for_counting_area1_cards[6]++;
            break;

        case 7:
            array_for_counting_area1_cards[7]++;
            break;

        case 8:
            array_for_counting_area1_cards[8]++;
            break;

        case 9:
            array_for_counting_area1_cards[9]++;
            break;
    }
}

void count_area2_cards(int x) {
    switch (x) {
        case 1:
            array_for_counting_area2_cards[1]++;
            break;

        case 2:
            array_for_counting_area2_cards[2]++;
            break;

        case 3:
            array_for_counting_area2_cards[3]++;
            break;

        case 4:
            array_for_counting_area2_cards[4]++;
            break;

        case 5:
            array_for_counting_area2_cards[5]++;
            break;

        case 6:
            array_for_counting_area2_cards[6]++;
            break;

        case 7:
            array_for_counting_area2_cards[7]++;
            break;

        case 8:
            array_for_counting_area2_cards[8]++;
            break;

        case 9:
            array_for_counting_area2_cards[9]++;
            break;
    }
}

void count_area3_cards(int x) {
    switch (x) {
        case 1:
            array_for_counting_area3_cards[1]++;
            break;

        case 2:
            array_for_counting_area3_cards[2]++;
            break;

        case 3:
            array_for_counting_area3_cards[3]++;
            break;

        case 4:
            array_for_counting_area3_cards[4]++;
            break;

        case 5:
            array_for_counting_area3_cards[5]++;
            break;

        case 6:
            array_for_counting_area3_cards[6]++;
            break;

        case 7:
            array_for_counting_area3_cards[7]++;
            break;

        case 8:
            array_for_counting_area3_cards[8]++;
            break;

        case 9:
            array_for_counting_area3_cards[9]++;
            break;
    }
}

void count_area4_cards(int x) {
    switch (x) {
        case 1:
            array_for_counting_area4_cards[1]++;
            break;

        case 2:
            array_for_counting_area4_cards[2]++;
            break;

        case 3:
            array_for_counting_area4_cards[3]++;
            break;

        case 4:
            array_for_counting_area4_cards[4]++;
            break;

        case 5:
            array_for_counting_area4_cards[5]++;
            break;

        case 6:
            array_for_counting_area4_cards[6]++;
            break;

        case 7:
            array_for_counting_area4_cards[7]++;
            break;

        case 8:
            array_for_counting_area4_cards[8]++;
            break;

        case 9:
            array_for_counting_area4_cards[9]++;
            break;
    }
}

int draw_card() {
    // only when there are space to put can user draw the card
    if (area1_placed_card_amount == 3 && area2_status == been_taken && area3_status == been_taken && area4_status == been_taken) {
        cout << "areas are all full or be taken, you can only take area back\n";
        user_take_area();
    } else {
        if (area1_status == been_taken && area2_placed_card_amount == 3 && area3_status == been_taken && area4_status == been_taken) {
            cout << "areas are all full or be taken, you can only take area back\n";
            user_take_area();
        } else {
            if (area1_status == been_taken && area2_status == been_taken && area3_placed_card_amount == 3 && area4_status == been_taken) {
                cout << "areas are all full or be taken, you can only take area back\n";
                user_take_area();
            } else {
                if (area1_status == been_taken && area2_status == been_taken && area3_status == been_taken && area4_placed_card_amount == 3) {
                    cout << "areas are all full or be taken, you can only take area back\n";
                    user_take_area();
                }

                // if there are space to place the card
                else {
                    if (total_used_cards != 61) {
                        int final_card;

                        total_used_cards++;
                        int card = 1 + rand() % 9;
                        card = add_to_each_card_sum(card);

                        if (card == 1)
                            cout << "get RED card" << endl;
                        else if (card == 2)
                            cout << "get PINK card" << endl;
                        else if (card == 3)
                            cout << "get YELLOW card" << endl;
                        else if (card == 4)
                            cout << "get ORANGE card" << endl;
                        else if (card == 5)
                            cout << "get BLUE card" << endl;
                        else if (card == 6)
                            cout << "get GREEN card" << endl;
                        else if (card == 7)
                            cout << "get GRAY card" << endl;
                        else if (card == 8)
                            cout << "get RAINBOW card" << endl;
                        else if (card == 9)
                            cout << "get PLUS2 card" << endl;
                        return card;
                    } else  // if next card is 62th, get LAST ROUND card
                    {
                        total_used_cards++;
                        cout << "\n\nget LAST ROUND CARD\n\n\n";
                        last_round_or_not = last_round;
                        int card = 1 + rand() % 9;
                        card = add_to_each_card_sum(card);

                        if (card == 1)
                            cout << "get RED card" << endl;
                        else if (card == 2)
                            cout << "get PINK card" << endl;
                        else if (card == 3)
                            cout << "get YELLOW card" << endl;
                        else if (card == 4)
                            cout << "get ORANGE card" << endl;
                        else if (card == 5)
                            cout << "get BLUE card" << endl;
                        else if (card == 6)
                            cout << "get GREEN card" << endl;
                        else if (card == 7)
                            cout << "get GRAY card" << endl;
                        else if (card == 8)
                            cout << "get RAINBOW card" << endl;
                        else if (card == 9)
                            cout << "get PLUS2 card" << endl;
                        return card;
                    }
                }
            }
        }
    }
}

void place_card(int input_card) {
    is_user_last_one = not_last_one;
    is_AI1_last_one = not_last_one;
    is_AI2_last_one = not_last_one;
    is_AI3_last_one = not_last_one;

    int input_area;
    cout << "please choose area number(1~4) to place\n";
    cin >> input_area;
    if (input_area == 1) {
        if (area1_placed_card_amount != 3)  // if the area had already put 3 cards, choose another area
        {
            if (area1_status != been_taken) {
                for (int i = 1; i < 4; i++) {
                    if (area1[i] == 0)  // put card in the first empty place
                    {
                        area1[i] = input_card;
                        area1_placed_card_amount++;
                        area1_status = can_put_card;
                        show_table_cards();
                        break;
                    }
                }
                user_decide_who_is_next_player();
                decide_first_player_next_round();
            } else {
                cout << "this area had been taken ";
                place_card(input_card);
            }
        } else {
            cout << "this area was full\n";
            place_card(input_card);
        }
    } else if (input_area == 2) {
        if (area2_placed_card_amount != 3)  // if the area had already put 3 cards, choose another area
        {
            if (area2_status != been_taken) {
                for (int i = 1; i < 4; i++) {
                    if (area2[i] == 0)  // put card in the first empty place
                    {
                        area2[i] = input_card;
                        area2_placed_card_amount++;
                        area2_status = can_put_card;
                        show_table_cards();
                        break;
                    }
                }
                user_decide_who_is_next_player();
                decide_first_player_next_round();
            } else {
                cout << "this area had been taken\n";
                place_card(input_card);
            }
        } else {
            cout << "this area is full\n";
            place_card(input_card);
        }
    } else if (input_area == 3) {
        if (area3_placed_card_amount != 3)  // if the area had already put 3 cards, choose another area
        {
            if (area3_status != been_taken) {
                for (int i = 1; i < 4; i++) {
                    if (area3[i] == 0)  // put card in the first empty place
                    {
                        area3[i] = input_card;
                        area3_placed_card_amount++;
                        area3_status = can_put_card;
                        show_table_cards();
                        break;
                    }
                }
                user_decide_who_is_next_player();
                decide_first_player_next_round();
            } else {
                cout << "this area had been taken\n";
                place_card(input_card);
            }
        } else {
            cout << "this area is full\n ";
            place_card(input_card);
        }
    } else if (input_area == 4) {
        if (area4_placed_card_amount != 3)  // if the area had already put 3 cards, choose another area
        {
            if (area4_status != been_taken) {
                for (int i = 1; i < 4; i++) {
                    if (area4[i] == 0)  // put card in the first empty place
                    {
                        area4[i] = input_card;
                        area4_placed_card_amount++;
                        area4_status = can_put_card;
                        show_table_cards();
                        break;
                    }
                }
                user_decide_who_is_next_player();
                decide_first_player_next_round();
            } else {
                cout << "this area had been taken\n";
                place_card(input_card);
            }
        } else {
            cout << "this area is full\n";
            place_card(input_card);
        }
    } else {
        cout << "input error\n ";
        place_card(input_card);
    }
}

void user_take_area() {
    // only when there are cards exist on table can user take the area back
    if (area1_placed_card_amount + area2_placed_card_amount + area3_placed_card_amount + area4_placed_card_amount > 0) {
        int taken_area_number;
        cout << "Which row do you want to take back:\n";
        cin >> taken_area_number;
        // if no cards were placed, can't take area back
        if (area1_status == no_card && area2_status == no_card && area3_status == no_card && area4_status == no_card) {
            cout << "there don't have area that is available to take back" << endl
                 << "you can only draw card, and computer will help you draw\n";
            place_card(draw_card());
        } else {
            if (taken_area_number == 1 || taken_area_number == 2 || taken_area_number == 3 || taken_area_number == 4) {
                if (taken_area_number == 1) {
                    if (area1_status == can_put_card || area1_status == full) {
                        for (int i = 1; i < 4; i++) {
                            user_cards[area1[i]]++;
                            area1[i] = 0;
                        }
                        area1_placed_card_amount = 0;
                        area1_status = been_taken;
                        user_status = end_play;
                        show_table_cards();
                        show_each_player_cards();
                        if (AI1_status == end_play && AI2_status == end_play && AI3_status == end_play) {
                            is_user_last_one = last_one;
                        }
                        user_decide_who_is_next_player();
                        decide_first_player_next_round();
                    } else {
                        cout << "area1 cannot be taken, please take another one\n";
                        user_take_area();
                    }
                } else if (taken_area_number == 2) {
                    if (area2_status == can_put_card || area2_status == full) {
                        for (int i = 1; i < 4; i++) {
                            user_cards[area2[i]]++;
                            area2[i] = 0;
                        }
                        area2_placed_card_amount = 0;
                        area2_status = been_taken;
                        user_status = end_play;
                        show_table_cards();
                        show_each_player_cards();
                        if (AI1_status == end_play && AI2_status == end_play && AI3_status == end_play) {
                            is_user_last_one = last_one;
                        }
                        user_decide_who_is_next_player();
                        decide_first_player_next_round();
                    } else {
                        cout << "area2 cannot be taken, please take another one\n";
                        user_take_area();
                    }
                } else if (taken_area_number == 3) {
                    if (area3_status == can_put_card || area3_status == full) {
                        for (int i = 1; i < 4; i++) {
                            user_cards[area3[i]]++;
                            area3[i] = 0;
                        }
                        area3_placed_card_amount = 0;
                        area3_status = been_taken;
                        user_status = end_play;
                        show_table_cards();
                        show_each_player_cards();
                        if (AI1_status == end_play && AI2_status == end_play && AI3_status == end_play) {
                            is_user_last_one = last_one;
                        }
                        user_decide_who_is_next_player();
                        decide_first_player_next_round();
                    } else {
                        cout << "area3 cannot be taken, please take another one\n";
                        user_take_area();
                    }
                } else if (taken_area_number == 4) {
                    if (area4_status == can_put_card || area4_status == full) {
                        for (int i = 1; i < 4; i++) {
                            user_cards[area4[i]]++;
                            area4[i] = 0;
                        }
                        area4_placed_card_amount = 0;
                        area4_status = been_taken;
                        user_status = end_play;
                        show_table_cards();
                        show_each_player_cards();
                        if (AI1_status == end_play && AI2_status == end_play && AI3_status == end_play) {
                            is_user_last_one = last_one;
                        }
                        user_decide_who_is_next_player();
                        decide_first_player_next_round();
                    } else {
                        cout << "area4 cannot be taken, please take another one\n";
                        user_take_area();
                    }
                }
            } else {
                cout << "Input error please try again!" << endl;
                user_take_area();
            }
        }
    } else {
        cout << "\nThere are no area you can take back, you can only draw card\n";
        place_card(draw_card());
    }
}

void count_point() {
    // cards that more then 7 count points as 6 cards
    for (int i = 1; i <= 7; i++) {
        if (user_cards[i] >= 7) {
            user_cards[i] = 6;
        }
        if (AI1_cards[i] >= 7) {
            AI1_cards[i] = 6;
        }
        if (AI2_cards[i] >= 7) {
            AI2_cards[i] = 6;
        }
        if (AI3_cards[i] >= 7) {
            AI3_cards[i] = 6;
        }
    }

    // sort cards amount(i = 7 has the most, i = 6 has second most ..., until i = 1 has least)
    sort(user_cards, user_cards + 8);
    sort(AI1_cards, AI1_cards + 8);
    sort(AI2_cards, AI2_cards + 8);
    sort(AI3_cards, AI3_cards + 8);

    // rainbow card's most beneficial placement
    while (user_cards[8] > 0)  // if have rainbow card
    {
        if (user_cards[7] < 6) {
            user_cards[7]++;
            user_cards[8]--;
        } else  // user_cards[7] = 6
        {
            if (user_cards[6] < 6) {
                user_cards[6]++;
                user_cards[8]--;
            } else  // user_cards[6] = 6
            {
                user_cards[5]++;
                user_cards[8]--;
                if (user_cards[5] > 6)  // if the three most amount cards all more than 6, don't need rainbow card
                {
                    user_cards[5] = 6;
                }
            }
        }
    }
    while (AI1_cards[8] > 0)  // if have rainbow card
    {
        if (AI1_cards[7] < 6) {
            AI1_cards[7]++;
            AI1_cards[8]--;
        } else  // AI1_cards[7] = 6
        {
            if (AI1_cards[6] < 6) {
                AI1_cards[6]++;
                AI1_cards[8]--;
            } else  // AI1_cards[6] = 6
            {
                AI1_cards[5]++;
                AI1_cards[8]--;
                if (AI1_cards[5] > 6)  // if the three most amount cards all more than 6, don't need rainbow card
                {
                    AI1_cards[5] = 6;
                }
            }
        }
    }
    while (AI2_cards[8] > 0)  // if have rainbow card
    {
        if (AI2_cards[7] < 6) {
            AI2_cards[7]++;
            AI2_cards[8]--;
        } else  // AI2_cards[7] = 6
        {
            if (AI2_cards[6] < 6) {
                AI2_cards[6]++;
                AI2_cards[8]--;
            } else  // AI2_cards[6] = 6
            {
                AI2_cards[5]++;
                AI2_cards[8]--;
                if (AI2_cards[5] > 6)  // if the three most amount cards all more than 6, don't need rainbow card
                {
                    AI2_cards[5] = 6;
                }
            }
        }
    }
    while (AI3_cards[8] > 0)  // if have rainbow card
    {
        if (AI3_cards[7] < 6) {
            AI3_cards[7]++;
            AI3_cards[8]--;
        } else  // AI3_cards[7] = 6
        {
            if (AI3_cards[6] < 6) {
                AI3_cards[6]++;
                AI3_cards[8]--;
            } else  // AI3_cards[6] = 6
            {
                AI3_cards[5]++;
                AI3_cards[8]--;
                if (AI3_cards[5] > 6)  // if the three most amount cards all more than 6, don't need rainbow card
                {
                    AI3_cards[5] = 6;
                }
            }
        }
    }

    // count point
    int user_point = 0;
    int AI1_point = 0;
    int AI2_point = 0;
    int AI3_point = 0;

    // the 3 most cards points is positive
    for (int i = 7; i >= 5; i--) {
        if (user_cards[i] == 6)
            user_point += 21;
        else if (user_cards[i] == 5)
            user_point += 15;
        else if (user_cards[i] == 4)
            user_point += 10;
        else if (user_cards[i] == 3)
            user_point += 6;
        else if (user_cards[i] == 2)
            user_point += 3;
        else if (user_cards[i] == 1)
            user_point += 1;

        if (AI1_cards[i] == 6)
            AI1_point += 21;
        else if (AI1_cards[i] == 5)
            AI1_point += 15;
        else if (AI1_cards[i] == 4)
            AI1_point += 10;
        else if (AI1_cards[i] == 3)
            AI1_point += 6;
        else if (AI1_cards[i] == 2)
            AI1_point += 3;
        else if (AI1_cards[i] == 1)
            AI1_point += 1;

        if (AI2_cards[i] == 6)
            AI2_point += 21;
        else if (AI2_cards[i] == 5)
            AI2_point += 15;
        else if (AI2_cards[i] == 4)
            AI2_point += 10;
        else if (AI2_cards[i] == 3)
            AI2_point += 6;
        else if (AI2_cards[i] == 2)
            AI2_point += 3;
        else if (AI2_cards[i] == 1)
            AI2_point += 1;

        if (AI3_cards[i] == 6)
            AI3_point += 21;
        else if (AI3_cards[i] == 5)
            AI3_point += 15;
        else if (AI3_cards[i] == 4)
            AI3_point += 10;
        else if (AI3_cards[i] == 3)
            AI3_point += 6;
        else if (AI3_cards[i] == 2)
            AI3_point += 3;
        else if (AI3_cards[i] == 1)
            AI3_point += 1;
    }
    // left cards points is negative
    for (int i = 4; i >= 1; i--) {
        if (user_cards[i] == 6)
            user_point -= 21;
        else if (user_cards[i] == 5)
            user_point -= 15;
        else if (user_cards[i] == 4)
            user_point -= 10;
        else if (user_cards[i] == 3)
            user_point -= 6;
        else if (user_cards[i] == 2)
            user_point -= 3;
        else if (user_cards[i] == 1)
            user_point -= 1;

        if (AI1_cards[i] == 6)
            AI1_point -= 21;
        else if (AI1_cards[i] == 5)
            AI1_point -= 15;
        else if (AI1_cards[i] == 4)
            AI1_point -= 10;
        else if (AI1_cards[i] == 3)
            AI1_point -= 6;
        else if (AI1_cards[i] == 2)
            AI1_point -= 3;
        else if (AI1_cards[i] == 1)
            AI1_point -= 1;

        if (AI2_cards[i] == 6)
            AI2_point -= 21;
        else if (AI2_cards[i] == 5)
            AI2_point -= 15;
        else if (AI2_cards[i] == 4)
            AI2_point -= 10;
        else if (AI2_cards[i] == 3)
            AI2_point -= 6;
        else if (AI2_cards[i] == 2)
            AI2_point -= 3;
        else if (AI2_cards[i] == 1)
            AI2_point -= 1;

        if (AI3_cards[i] == 6)
            AI3_point -= 21;
        else if (AI3_cards[i] == 5)
            AI3_point -= 15;
        else if (AI3_cards[i] == 4)
            AI3_point -= 10;
        else if (AI3_cards[i] == 3)
            AI3_point -= 6;
        else if (AI3_cards[i] == 2)
            AI3_point -= 3;
        else if (AI3_cards[i] == 1)
            AI3_point -= 1;
    }

    cout << "\nThe points you get:" << user_point << endl;
    cout << "The points AI1 gets:" << AI1_point << endl;
    cout << "The points AI2 gets:" << AI2_point << endl;
    cout << "The points AI3 gets:" << AI3_point << endl;

    int points_array[4] = {user_point, AI1_point, AI2_point, AI3_point};
    sort(points_array, points_array + 4);
    cout << "1st: " << points_array[3] << endl
         << "2nd: " << points_array[2] << endl
         << "3rd: " << points_array[1] << endl
         << "4th: " << points_array[0] << endl
         << endl;
    cout << "play again?(if yes, input 1, if no, input 2)\n";
    int s;
    cin >> s;
    if (s == 1) {
        red = 0;
        pink = 0;
        yellow = 0;
        orange = 0;
        blue = 0;
        green = 0;
        gray = 0;
        rainbow = 0;
        plus2 = 0;

        area1[4] = {};
        area2[4] = {};
        area3[4] = {};
        area4[4] = {};

        last_round_or_not = not_last_round;

        total_used_cards = 0;

        is_user_last_one = not_last_one;
        is_AI1_last_one = not_last_one;
        is_AI2_last_one = not_last_one;
        is_AI3_last_one = not_last_one;

        area1_status = no_card;
        area2_status = no_card;
        area3_status = no_card;
        area4_status = no_card;

        user_status = play;
        AI1_status = play;
        AI2_status = play;
        AI3_status = play;

        four_people_first_round_draw();
        four_player_game_of_user();
    } else
        exit(0);
}

void AI1() {
    cout << "\nAI1's turn\n";
    if (area1_status != no_card && area1_status != been_taken) {
        cout << "AI1 take back area1\n";
        for (int i = 1; i < 5; i++) {
            AI1_cards[area1[i]]++;
            area1[i] = 0;
        }
        area1_placed_card_amount = 0;
        area1_status = been_taken;
        AI1_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI2_status == end_play && AI3_status == end_play) {
            is_AI1_last_one = last_one;
        }
        AI1_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area2_status != no_card && area2_status != been_taken) {
        cout << "AI1 take back area2\n";
        for (int i = 1; i < 5; i++) {
            AI1_cards[area2[i]]++;
            area2[i] = 0;
        }
        area2_placed_card_amount = 0;
        area2_status = been_taken;
        AI1_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI2_status == end_play && AI3_status == end_play) {
            is_AI1_last_one = last_one;
        }
        AI1_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area3_status != no_card && area3_status != been_taken) {
        cout << "AI1 take back area3\n";
        for (int i = 1; i < 5; i++) {
            AI1_cards[area3[i]]++;
            area3[i] = 0;
        }
        area3_placed_card_amount = 0;
        area3_status = been_taken;
        AI1_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI2_status == end_play && AI3_status == end_play) {
            is_AI1_last_one = last_one;
        }
        AI1_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area4_status != no_card && area4_status != been_taken) {
        cout << "AI1 take back area4\n";
        for (int i = 1; i < 5; i++) {
            AI1_cards[area4[i]]++;
            area4[i] = 0;
        }
        area4_placed_card_amount = 0;
        area4_status = been_taken;
        AI1_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI2_status == end_play && AI3_status == end_play) {
            is_AI1_last_one = last_one;
        }
        AI1_decide_who_is_next_player();
        decide_first_player_next_round();
    }
    // if can't take back area, mean the area left all don't have card, so place the card
    else {
        cout << "AI1 draw a card\n";
        int drawn_card_by_AI1 = draw_card();
        if (area1_status != been_taken) {
            cout << "AI1 place card at area1\n";
            area1[1] = drawn_card_by_AI1;
            area1_status = can_put_card;
            area1_placed_card_amount++;
            show_table_cards();
        } else if (area2_status != been_taken) {
            cout << "AI1 place card at area2\n";
            area2[1] = drawn_card_by_AI1;
            area2_status = can_put_card;
            area2_placed_card_amount++;
            show_table_cards();
        } else if (area3_status != been_taken) {
            cout << "AI1 place card at area3\n";
            area3[1] = drawn_card_by_AI1;
            area3_status = can_put_card;
            area3_placed_card_amount++;
            show_table_cards();
        } else if (area4_status != been_taken) {
            cout << "AI1 place card at area4\n";
            area4[1] = drawn_card_by_AI1;
            area4_status = can_put_card;
            area4_placed_card_amount++;
            show_table_cards();
        }
    }
    AI1_decide_who_is_next_player();
    decide_first_player_next_round();
}

void AI2() {
    cout << "\nAI2's turn\n";
    if (area1_status != no_card && area1_status != been_taken) {
        cout << "AI2 take back area1\n";
        for (int i = 1; i < 5; i++) {
            AI2_cards[area1[i]]++;
            area1[i] = 0;
        }
        area1_placed_card_amount = 0;
        area1_status = been_taken;
        AI2_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI3_status == end_play) {
            is_AI2_last_one = last_one;
        }
        AI2_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area2_status != no_card && area2_status != been_taken) {
        cout << "AI2 take back area2\n";
        for (int i = 1; i < 5; i++) {
            AI2_cards[area2[i]]++;
            area2[i] = 0;
        }
        area2_placed_card_amount = 0;
        area2_status = been_taken;
        AI2_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI3_status == end_play) {
            is_AI2_last_one = last_one;
        }
        AI2_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area3_status != no_card && area3_status != been_taken) {
        cout << "AI2 take back area3\n";
        for (int i = 1; i < 5; i++) {
            AI2_cards[area3[i]]++;
            area3[i] = 0;
        }
        area3_placed_card_amount = 0;
        area3_status = been_taken;
        AI2_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI3_status == end_play) {
            is_AI2_last_one = last_one;
        }
        AI2_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area4_status != no_card && area4_status != been_taken) {
        cout << "AI2 take back area4\n";
        for (int i = 1; i < 5; i++) {
            AI2_cards[area4[i]]++;
            area4[i] = 0;
        }
        area4_placed_card_amount = 0;
        area4_status = been_taken;
        AI2_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI3_status == end_play) {
            is_AI2_last_one = last_one;
        }
        AI2_decide_who_is_next_player();
        decide_first_player_next_round();
    }
    // if can't take back area, mean the area left all don't have card, so place the card
    else {
        cout << "AI2 draw a card\n";
        int drawn_card_by_AI2 = draw_card();
        if (area1_status != been_taken) {
            cout << "AI2 place card at area1\n";
            area1[1] = drawn_card_by_AI2;
            area1_status = can_put_card;
            area1_placed_card_amount++;
            show_table_cards();
        } else if (area2_status != been_taken) {
            cout << "AI2 place card at area2\n";
            area2[1] = drawn_card_by_AI2;
            area2_status = can_put_card;
            area2_placed_card_amount++;
            show_table_cards();
        } else if (area3_status != been_taken) {
            cout << "AI2 place card at area3\n";
            area3[1] = drawn_card_by_AI2;
            area3_status = can_put_card;
            area3_placed_card_amount++;
            show_table_cards();
        } else if (area4_status != been_taken) {
            cout << "AI2 place card at area4\n";
            area4[1] = drawn_card_by_AI2;
            area4_status = can_put_card;
            area4_placed_card_amount++;
            show_table_cards();
        }
    }
    AI2_decide_who_is_next_player();
    decide_first_player_next_round();
}

void AI3() {
    cout << "\nAI3's turn\n";
    if (area1_status != no_card && area1_status != been_taken) {
        cout << "AI3 take back area1\n";
        for (int i = 1; i < 5; i++) {
            AI3_cards[area1[i]]++;
            area1[i] = 0;
        }
        area1_placed_card_amount = 0;
        area1_status = been_taken;
        AI3_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI2_status == end_play) {
            is_AI3_last_one = last_one;
        }
        AI3_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area2_status != no_card && area2_status != been_taken) {
        cout << "AI3 take back area2\n";
        for (int i = 1; i < 5; i++) {
            AI3_cards[area2[i]]++;
            area2[i] = 0;
        }
        area2_placed_card_amount = 0;
        area2_status = been_taken;
        AI3_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI2_status == end_play) {
            is_AI3_last_one = last_one;
        }
        AI3_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area3_status != no_card && area3_status != been_taken) {
        cout << "AI3 take back area3\n";
        for (int i = 1; i < 5; i++) {
            AI3_cards[area3[i]]++;
            area3[i] = 0;
        }
        area3_placed_card_amount = 0;
        area3_status = been_taken;
        AI3_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI2_status == end_play) {
            is_AI3_last_one = last_one;
        }
        AI3_decide_who_is_next_player();
        decide_first_player_next_round();
    } else if (area4_status != no_card && area4_status != been_taken) {
        cout << "AI3 take back area4\n";
        for (int i = 1; i < 5; i++) {
            AI3_cards[area4[i]]++;
            area4[i] = 0;
        }
        area4_placed_card_amount = 0;
        area4_status = been_taken;
        AI3_status = end_play;
        show_each_player_cards();
        show_table_cards();
        if (user_status == end_play && AI1_status == end_play && AI2_status == end_play) {
            is_AI3_last_one = last_one;
        }
        AI3_decide_who_is_next_player();
        decide_first_player_next_round();
    }
    // if can't take back area, mean the area left all don't have card, so place the card
    else {
        cout << "AI3 draw a card\n";
        int drawn_card_by_AI3 = draw_card();
        if (area1_status != been_taken) {
            cout << "AI3 place card at area1\n";
            area1[1] = drawn_card_by_AI3;
            area1_status = can_put_card;
            area1_placed_card_amount++;
            show_table_cards();
        } else if (area2_status != been_taken) {
            cout << "AI3 place card at area2\n";
            area2[1] = drawn_card_by_AI3;
            area2_status = can_put_card;
            area2_placed_card_amount++;
            show_table_cards();
        } else if (area3_status != been_taken) {
            cout << "AI3 place card at area3\n";
            area3[1] = drawn_card_by_AI3;
            area3_status = can_put_card;
            area3_placed_card_amount++;
            show_table_cards();
        } else if (area4_status != been_taken) {
            cout << "AI3 place card at area4\n";
            area4[1] = drawn_card_by_AI3;
            area4_status = can_put_card;
            area4_placed_card_amount++;
            show_table_cards();
        }
    }
    AI3_decide_who_is_next_player();
    decide_first_player_next_round();
}

int add_to_each_card_sum(int x)  // calculate how many cards of each colors had been drawn
{
    int redrawn_card;
    if (x == 1) {
        red++;
        if (red >= 10)  // if red had been draw 10 times, draw again
        {
            cout << "屌";
            red--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 2) {
        pink++;
        if (pink >= 10)  // if pink had been draw 10 times, draw again
        {
            cout << "屌";
            pink--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 3) {
        yellow++;
        if (yellow >= 10)  // if yellow had been draw 10 times, draw again
        {
            cout << "屌";
            yellow--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 4) {
        orange++;
        if (orange >= 10)  // if orange had been draw 10 times, draw again
        {
            cout << "屌";
            orange--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 5) {
        blue++;
        if (blue >= 10)  // if blue had been draw 10 times, draw again
        {
            cout << "屌";
            blue--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 6) {
        green++;
        if (green >= 10)  // if green had been draw 10 times, draw again
        {
            cout << "屌";
            green--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 7) {
        gray++;
        if (gray >= 10)  // if gray had been draw 10 times, draw again
        {
            cout << "屌";
            gray--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 8) {
        rainbow++;
        if (rainbow >= 4)  // if rainbow had been draw 4 times, draw again
        {
            cout << "屌";
            rainbow--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
    if (x == 9) {
        plus2++;
        if (plus2 >= 11)  // if plus2 had been draw 11 times, draw again
        {
            cout << "屌";
            plus2--;
            redrawn_card = draw_card_again();
            redrawn_card = add_to_each_card_sum(redrawn_card);
            return redrawn_card;
        } else
            return x;
    }
}

int draw_card_again()  // without adding total card amount
{
    int card;
    card = 1 + rand() % 9;
    return card;
}

void decide_first_player_next_round() {
    // if user is the last person and isn't last round, then be the first to take action next round
    if (is_user_last_one == last_one && last_round_or_not == not_last_round) {
        area1[4] = {};
        area2[4] = {};
        area3[4] = {};
        area4[4] = {};

        area1_placed_card_amount = 0;
        area2_placed_card_amount = 0;
        area3_placed_card_amount = 0;
        area4_placed_card_amount = 0;

        is_user_last_one = not_last_one;
        is_AI1_last_one = not_last_one;
        is_AI2_last_one = not_last_one;
        is_AI3_last_one = not_last_one;

        area1_status = no_card;
        area2_status = no_card;
        area3_status = no_card;
        area4_status = no_card;

        user_status = play;
        AI1_status = play;
        AI2_status = play;
        AI3_status = play;

        four_player_game_of_user();
    }
    // if AI1 is the last person and isn't last round, then be the first to take action next round
    else if (is_AI1_last_one == last_one && last_round_or_not == not_last_round) {
        area1[4] = {};
        area2[4] = {};
        area3[4] = {};
        area4[4] = {};

        area1_placed_card_amount = 0;
        area2_placed_card_amount = 0;
        area3_placed_card_amount = 0;
        area4_placed_card_amount = 0;

        is_user_last_one = not_last_one;
        is_AI1_last_one = not_last_one;
        is_AI2_last_one = not_last_one;
        is_AI3_last_one = not_last_one;

        area1_status = no_card;
        area2_status = no_card;
        area3_status = no_card;
        area4_status = no_card;

        user_status == play;
        AI1_status == play;
        AI2_status == play;
        AI3_status == play;

        AI1();
    }
    // if AI2 is the last person and isn't last round, then be the first to take action next round
    else if (is_AI2_last_one == last_one && last_round_or_not == not_last_round) {
        area1[4] = {};
        area2[4] = {};
        area3[4] = {};
        area4[4] = {};

        area1_placed_card_amount = 0;
        area2_placed_card_amount = 0;
        area3_placed_card_amount = 0;
        area4_placed_card_amount = 0;

        is_user_last_one = not_last_one;
        is_AI1_last_one = not_last_one;
        is_AI2_last_one = not_last_one;
        is_AI3_last_one = not_last_one;

        area1_status = no_card;
        area2_status = no_card;
        area3_status = no_card;
        area4_status = no_card;

        user_status == play;
        AI1_status == play;
        AI2_status == play;
        AI3_status == play;

        AI2();
    }
    // if AI3 is the last person and isn't last round, then be the first to take action next round
    else if (is_AI3_last_one == last_one && last_round_or_not == not_last_round) {
        area1[4] = {};
        area2[4] = {};
        area3[4] = {};
        area4[4] = {};

        area1_placed_card_amount = 0;
        area2_placed_card_amount = 0;
        area3_placed_card_amount = 0;
        area4_placed_card_amount = 0;

        is_user_last_one = not_last_one;
        is_AI1_last_one = not_last_one;
        is_AI2_last_one = not_last_one;
        is_AI3_last_one = not_last_one;

        area1_status = no_card;
        area2_status = no_card;
        area3_status = no_card;
        area4_status = no_card;

        user_status = play;
        AI1_status = play;
        AI2_status = play;
        AI3_status = play;

        AI3();
    }
    // when last round
    else if (user_status == end_play && AI1_status == end_play && AI2_status == end_play && AI3_status == end_play && last_round_or_not == last_round) {
        count_point();
    }
}

void user_decide_who_is_next_player() {
    // check if user is not last person and who will be next
    if (user_status == play && AI1_status == end_play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == end_play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    }
}

void AI1_decide_who_is_next_player() {
    // check if AI1 is the not last person and who will be next
    if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == end_play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    }
}

void AI2_decide_who_is_next_player() {
    // check if AI2 is the not last person and who will be next
    if (user_status == end_play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == end_play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == end_play && AI1_status == end_play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == end_play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    }
}

void AI3_decide_who_is_next_player() {
    // check if AI3 is the not last person and who will be next
    if (user_status == end_play && AI1_status == end_play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI3();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == end_play && AI2_status == end_play && AI3_status == end_play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == play && AI1_status == end_play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        four_player_game_of_user();
    } else if (user_status == end_play && AI1_status == play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == play && AI2_status == end_play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI1();
    } else if (user_status == end_play && AI1_status == end_play && AI2_status == play && AI3_status == play && is_user_last_one == not_last_one && is_AI1_last_one == not_last_one && is_AI2_last_one == not_last_one && is_AI3_last_one == not_last_one) {
        AI2();
    }
}
