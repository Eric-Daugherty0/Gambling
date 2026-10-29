#ifndef DAUGHERTY_GAMBLINGGREG_H
#define DAUGHERTY_GAMBLINGGREG_H

// Structure to hold information about each dog
struct DOG
{
    char name[20];
    int payout;
    int odds;
};

// Structure to hold information about each race
struct RACE
{
    int dogPicked;
    int dogWon;
    double wager;
};
// Functions
void showRaces(struct DOG dogs[], struct RACE races[], int current, int totalRaces);

void menu(struct DOG dogs[], struct RACE races[], int totalRaces, double cash, double bank);

#endif