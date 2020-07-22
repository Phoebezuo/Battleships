#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM (8)
#define BUF_LEN (100)

#define CARRIER_LEN (5)
#define BATTLESHIP_LEN (4)
#define DESTROYER_LEN (3)
#define SUBMARINE_LEN (2)
#define PATROL_LEN (2)

#define CARRIER (0)
#define BATTLESHIP (1)
#define DESTROYER (2)
#define SUBMARINE (3)
#define PATROL (4)

typedef struct {
    char x;
    int y;
    char z;
} ship;

int set_loc(ship lists[BUF_LEN],char loc[DIM][DIM], int obj_type, int obj_len, int player) {
    char buff[BUF_LEN];
    char *obj;
    char tag;

    if (obj_type == 0) {
        obj = "Carrier";
        tag = 'C';
    } else if (obj_type == 1) {
        obj = "Battleship";
        tag = 'B';
    } else if (obj_type == 2) {
        obj = "Destroyer";
        tag = 'D';
    } else if (obj_type == 3) {
        obj = "Submarine";
        tag = 'S';
    } else if (obj_type == 4) {
        obj = "Patrol Boat";
        tag = 'P';
    } else {
        obj = "";
    }
    printf("%s: ", obj);
    while (fgets(buff, BUF_LEN, stdin)) {
        // puts(buff);
        if (sscanf(buff, "%c %d %c", &lists[player].x, &lists[player].y, &lists[player].z) == 3 && lists[player].x >= 'A' && lists[player].x <= 'H' && lists[player].y > 0 && lists[player].y < DIM + 1 && (lists[player].z == 'H' || lists[player].z == 'V')) {
            if (lists[player].z == 'H') {
                for (int i = 0; i < obj_len; i++) {
                    if (loc[lists[player].x - 'A'][lists[player].y - 1 + i] == ' ') {
                        loc[lists[player].x - 'A'][lists[player].y - 1 + i] = tag;
                    } else {
                        puts("Invalid ship configuration");
                        return 0;
                    }
                }
            } else if (lists[player].z == 'V') {
                for (int i = 0; i < obj_len; i++) {
                    if (loc[lists[player].x - 'A' + i][lists[player].y - 1] == ' ') {
                        loc[lists[player].x - 'A' + i][lists[player].y - 1] = tag;
                    } else {
                        puts("Invalid ship configuration");
                        return 0;
                    }
                }
            }
            break;
        } else {
            puts("Invalid ship configuration");
            return 0;
        }
    }
    return 1;
}

void print_board(char board[DIM][DIM]) {
    puts("");
    printf(" ");
    for (int i = 1; i < DIM + 1; i++) {
        printf(" %d", i);
    }
    puts("");
    for (int i = 0; i < DIM; i++) {
        printf("%c|", 65+i);
        for (int j = 0; j < DIM; j++) {
            printf("%c|", board[i][j]);
        }
        puts("");
    }
    puts("");
}

int fire(char board[DIM][DIM], char loc[DIM][DIM], char X, int Y, int* c_can_hit, int* b_can_hit, int* d_can_hit, int* s_can_hit, int* p_can_hit) {
    int x = X - 'A';
    int y = Y - 1;
    if (loc[x][y] == ' ') {
        puts("\nYou have missed!");
        board[x][y] = '0';
        loc[x][y] = '*';
    } else if (loc[x][y] == '*') {
        puts("You have already fired at this location");
        return 1;
    } else if (loc[x][y] == 'C') {
        // printf("%d\n", *c_can_hit);
        if (*c_can_hit > 1) {
            puts("\nWe have hit the target!");
        } else {
            puts("\nWe have sunk your Carrier!");
        }
        board[x][y] = 'X';
        loc[x][y] = '*';
        *c_can_hit = *c_can_hit - 1;
    } else if (loc[x][y] == 'B') {
        if (*b_can_hit > 1) {
            puts("\nWe have hit the target!");
        } else {
            puts("\nWe have sunk your Battleship!");
        }
        board[x][y] = 'X';
        loc[x][y] = '*';
        *b_can_hit = *b_can_hit - 1;
    } else if (loc[x][y] == 'D') {
        if (*d_can_hit > 1) {
            puts("\nWe have hit the target!");
        } else {
            puts("\nWe have sunk your Destroyer!");
        }
        board[x][y] = 'X';
        loc[x][y] = '*';
        *d_can_hit = *d_can_hit - 1;
    } else if (loc[x][y] == 'S') {
        if (*s_can_hit > 1) {
            puts("\nWe have hit the target!");
        } else {
            puts("\nWe have sunk your Submarine!");
        }
        board[x][y] = 'X';
        loc[x][y] = '*';
        *s_can_hit = *s_can_hit - 1;
    } else if (loc[x][y] == 'P') {
        if (*p_can_hit > 1) {
            puts("\nWe have hit the target!");
        } else {
            puts("\nWe have sunk your Patrol Boat!");
        }
        board[x][y] = 'X';
        loc[x][y] = '*';
        *p_can_hit = *p_can_hit - 1;
    }
    return 0;
}

int main() {
    char board1[DIM][DIM];
    memset(board1, ' ', DIM * DIM);
    char board2[DIM][DIM];
    memset(board2, ' ', DIM * DIM);

    char loc1[DIM][DIM];
    memset(loc1, ' ', DIM * DIM);
    char loc2[DIM][DIM];
    memset(loc2, ' ', DIM * DIM);

    ship carriers[BUF_LEN];
    ship battleships[BUF_LEN];
    ship destroyers[BUF_LEN];
    ship submarines[BUF_LEN];
    ship patrols[BUF_LEN];

    char buff[BUF_LEN];
    char ipt[BUF_LEN];
    char x;
    int y;

    int c1_can_hit = 5;
    int b1_can_hit = 4;
    int d1_can_hit = 3;
    int s1_can_hit = 2;
    int p1_can_hit = 2;

    int c2_can_hit = 5;
    int b2_can_hit = 4;
    int d2_can_hit = 3;
    int s2_can_hit = 2;
    int p2_can_hit = 2;


    int player = 0;
    printf("Player 1, please set up your ships (y, x, orientation)\n");
    int flag = 0;
    while (flag == 0) {
        flag = set_loc(carriers, loc1, CARRIER, CARRIER_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(battleships, loc1, BATTLESHIP, BATTLESHIP_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(destroyers, loc1, DESTROYER, DESTROYER_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(submarines, loc1, SUBMARINE, SUBMARINE_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(patrols, loc1, PATROL, PATROL_LEN, player);
    }

    puts("");
    player = (player + 1) % 2;
    printf("\nPlayer 2, please set up your ships (y, x, orientation)\n");
    flag = 0;
    while (flag == 0) {
        flag = set_loc(carriers, loc2, CARRIER, CARRIER_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(battleships, loc2, BATTLESHIP, BATTLESHIP_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(destroyers, loc2, DESTROYER, DESTROYER_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(submarines, loc2, SUBMARINE, SUBMARINE_LEN, player);
    }
    flag = 0;
    while (flag == 0) {
        flag = set_loc(patrols, loc2, PATROL, PATROL_LEN, player);
    }
    printf("\nAll boats set up, Player 1 can now strike.\n");
    puts("");
    player = (player + 1) % 2;

    int turns;
    while (fgets(buff, BUF_LEN, stdin)) {
        // puts(buff);
        if (sscanf(buff, "%s %c %d", ipt, &x, &y) == 3) {
            if (x < 'A' || x > 'H' || y < 1 || y > DIM) {
                puts("Invalid coordinates");
            } else {
                if (strcmp(ipt, "fire") == 0) {
                    if (player == 0) {
                        turns = fire(board1, loc2, x, y, &c2_can_hit, &b2_can_hit, &d2_can_hit, &s2_can_hit, &p2_can_hit);
                        // puts("player 1 after fire");
                        if (c2_can_hit == 0 && b2_can_hit == 0 && d2_can_hit == 0 && s2_can_hit == 0 && p2_can_hit == 0) {
                            puts("\nPlayer 1 wins!");
                            break;
                        }
                    } else {
                        turns = fire(board2, loc1, x, y, &c1_can_hit, &b1_can_hit, &d1_can_hit, &s1_can_hit, &p1_can_hit);
                        if (c1_can_hit == 0 && b1_can_hit == 0 && d1_can_hit == 0 && s1_can_hit == 0 && p1_can_hit == 0) {
                            puts("\nPlayer 2 wins!");
                            break;
                        }
                    }
                    if (turns == 0) {
                        puts("");
                        player = (player + 1) % 2;
                        printf("Player %d's turn\n", player + 1);
                        puts("");
                    }
                } else {
                    puts("Unrecognised command");
                }
            }
        } else if (sscanf(buff, "%s", ipt) == 1) {
            if (strcmp(ipt, "exit") == 0) {
                return 1;
            } else if (strcmp(ipt, "shots") == 0) {
                if (player == 0) {
                    print_board(board1);
                } else {
                    print_board(board2);
                }
            } else {
                puts("Unrecognised command");
            }
        }
    }
    return 0;
}
