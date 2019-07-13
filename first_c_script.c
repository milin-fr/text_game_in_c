#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define White 15
#define Lightblue 9
#define Lightgreen 10
#define Lightred 12
#define Yellow 14

int game_over = 0;
int game_table[4][4];
int table_of_colors[17] = {White, Lightblue, Lightgreen, Lightred, Yellow, Lightblue, Lightgreen, Lightred, Yellow, Lightblue, Lightgreen, Lightred, Yellow, Lightblue, Lightgreen, Lightred, Yellow};

char table_of_symbols[17] = {".####****++++$$$$"};

int deck_with_cards_in_random_order[16];
int turn_index = 0;
int card_to_play;
int last_played_row;
int last_played_column;

char player1[20];
char player2[20];

void fil_game_table_with_zeroes();
void print_game_rules();
void print_game_plate();
void ask_players_names();
void increase_turn_index();
int card_already_in_deck(int card, int *deck_with_cards_in_random_order, int size_of_the_deck);
void fill_in_the_deck_with_cards_in_random_order();
void get_card_to_play();
void ask_for_card_placement();
void print_current_player_name();
void color (int couleurDuTexte);
void announce_the_winner();
void announce_draw();
void ckeck_winning_conditions();
void cycle_turns();


int main()
{
    print_game_rules();
    fil_game_table_with_zeroes();
    fill_in_the_deck_with_cards_in_random_order();
    ask_players_names();
    cycle_turns();
    return 0;
}

void fil_game_table_with_zeroes() {
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            game_table[i][j]=0;
        }
    }
}

void print_game_rules() {
    printf("Allign 4 cards by symbol or by color to win the game!\n");
}

void print_game_plate() {
    int current_card;
    int current_color;
    char current_symbol;
    int i,j;
    for(i=0;i<4;i++)
    {
        printf("\n");
        for(j=0;j<4;j++)
        {
            current_card = game_table[i][j];
            current_color = table_of_colors[current_card];
            current_symbol = table_of_symbols[current_card];
            color(current_color);
            printf(" %c ", current_symbol);
            color(White);
        }
    }
    printf("\n\n");
}

void ask_players_names() {
    printf("Player 1 name?");
    scanf("%s", player1);
    printf("Player 2 name?");
    scanf("%s", player2);
}

void increase_turn_index() {
    turn_index++;
}


int card_already_in_deck(int card, int *deck_with_cards_in_random_order, int size_of_the_deck){
    int index;
    for (index=0; index < size_of_the_deck; index++) {
        if (deck_with_cards_in_random_order[index] == card)
            return 1;
    }
    return 0;
}

void fill_in_the_deck_with_cards_in_random_order(){
    int index = 0;
    int random_number;
    srand(time(NULL));
    do{
        do{
            random_number = rand()%16 + 1;
            deck_with_cards_in_random_order[index] = random_number;
        }while(card_already_in_deck(random_number, deck_with_cards_in_random_order, index) == 1);
        index++;
    }while (index < 16);
}

void get_card_to_play(){
    int current_color;
    char current_symbol;
    card_to_play = deck_with_cards_in_random_order[turn_index];
    current_color = table_of_colors[card_to_play];
    current_symbol = table_of_symbols[card_to_play];
    if(turn_index % 2 == 0)
    {
        printf("%s, your card is ", player1);
        color(current_color);
        printf(" %c ", current_symbol);
        color(White);
    }
    else
    {
        printf("%s, your card is ", player2);
        color(current_color);
        printf(" %c ", current_symbol);
        color(White);
    }
    printf("\n\n");
}

void ask_for_card_placement() {
    do{
        printf("Choose the row for the gard (1 - 4): ");
        scanf("%d", &last_played_row);
    }while(!(0 < last_played_row && last_played_row < 5));
    do{
        printf("Choose the column for the gard (1 - 4): ");
        scanf("%d", &last_played_column);
    }while(!(0 < last_played_column && last_played_column < 5));
    if (game_table[last_played_row-1][last_played_column-1] == 0)
    {
        game_table[last_played_row-1][last_played_column-1] = card_to_play;
        printf("%d\n", game_table[last_played_row-1][last_played_column-1]);
    }
    else
    {
        ask_for_card_placement();
    }
}



void print_current_player_name() {
    if(turn_index % 2 == 0)
    {
        printf("Current player is %s.\n", player1);
    }
    else
    {
        printf("Current player is %s.", player2);
    }
}

void color (int couleurDuTexte)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, 0*16+couleurDuTexte);
}

void announce_the_winner() {
    game_over = 1;
    print_game_plate();
    if(turn_index % 2 == 0)
    {
        printf("Player %s wins in %d turns.\n", player1, turn_index + 1);
    }
    else
    {
        printf("Player %s wins in %d turns.\n", player2, turn_index + 1);
    }
}

void announce_draw() {
    game_over = 1;
    print_game_plate();
    printf("Draw!");
}

void ckeck_winning_conditions() {
    int alligned_card_by_row1;
    int alligned_card_by_row2;
    int alligned_card_by_row3;
    int alligned_card_by_row4;
    
    int alligned_card_by_column1;
    int alligned_card_by_column2;
    int alligned_card_by_column3;
    int alligned_card_by_column4;

    alligned_card_by_row1 = game_table[last_played_row-1][0];
    alligned_card_by_row2 = game_table[last_played_row-1][1];
    alligned_card_by_row3 = game_table[last_played_row-1][2];
    alligned_card_by_row4 = game_table[last_played_row-1][3];

    alligned_card_by_column1 = game_table[0][last_played_column-1];
    alligned_card_by_column2 = game_table[1][last_played_column-1];
    alligned_card_by_column3 = game_table[2][last_played_column-1];
    alligned_card_by_column4 = game_table[3][last_played_column-1];

    if (table_of_colors[alligned_card_by_row1] == table_of_colors[alligned_card_by_row2] && table_of_colors[alligned_card_by_row1] == table_of_colors[alligned_card_by_row3] && table_of_colors[alligned_card_by_row1] == table_of_colors[alligned_card_by_row4])
    {
        announce_the_winner();
    }
    else if (table_of_symbols[alligned_card_by_row1] == table_of_symbols[alligned_card_by_row2] && table_of_symbols[alligned_card_by_row1] == table_of_symbols[alligned_card_by_row3] && table_of_symbols[alligned_card_by_row1] == table_of_symbols[alligned_card_by_row4])
    {
        announce_the_winner();
    }
    else if (table_of_colors[alligned_card_by_column1] == table_of_colors[alligned_card_by_column2] && table_of_colors[alligned_card_by_column1] == table_of_colors[alligned_card_by_column3] && table_of_colors[alligned_card_by_column1] == table_of_colors[alligned_card_by_column4])
    {
        announce_the_winner();
    }
    else if (table_of_symbols[alligned_card_by_column1] == table_of_symbols[alligned_card_by_column2] && table_of_symbols[alligned_card_by_column1] == table_of_symbols[alligned_card_by_column3] && table_of_symbols[alligned_card_by_column1] == table_of_symbols[alligned_card_by_column4])
    {
        announce_the_winner();
    }
    else if (turn_index == 15)
    {
        announce_draw();
    }
}

void cycle_turns() {
    do{
        print_game_plate();
        printf("Turn number %d.\n", turn_index+1);
        get_card_to_play();
        ask_for_card_placement();
        ckeck_winning_conditions();
        increase_turn_index();
    }while(game_over == 0);
}


