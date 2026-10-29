#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Daugherty-GamblingGreg.h"

// Function to display the results of each race
void showRaces(struct DOG dogs[], struct RACE races[], int current, int totalRaces)
{
    if (current < totalRaces)
    {
        printf("Race %d: Picked %s, Winner %s, Wager $%.2f\n",
               current + 1,
               dogs[races[current].dogPicked].name,
               dogs[races[current].dogWon].name,
               races[current].wager);
        showRaces(dogs, races, current + 1, totalRaces);
    }
}

// Function to display the main menu and handle user input
void menu(struct DOG dogs[], struct RACE races[], int totalRaces, double cash, double bank)
{
    char choice;
    char bankChoice;
    int pick;
    int roll;
    int winner;
    double wager;
    double amount;
    double winnings;

    // Display the main menu
    printf("\n--- DOG TRACK ---\n");
    printf("Cash: $%.2f   Bank: $%.2f\n", cash, bank);
    printf("[G]amble\n");
    printf("[B]anking\n");
    printf("[R]esults of each race\n");
    printf("[L]eave the dog track\n");
    printf("Pick one: ");
    if (scanf(" %c", &choice) != 1)
    {
        return;
    }

    // Handle user input based on their choice
    switch (choice)
    {
        case 'G':
        case 'g':
            if (cash <= 0)
            {
                printf("You have no cash.\n");
            }
            else if (totalRaces >= 100)
            {
                printf("No more room to save races.\n");
            }
            else
            {
                printf("How much would you like to bet? $");
                scanf("%lf", &wager);

                if (wager <= 0 || wager > cash)
                {
                    printf("You cant bet that amount.\n");
                }
                else
                {
                    // Display the list of dogs and their odds
                    printf("\n1. %s  %d to 1  %d%%\n", dogs[0].name, dogs[0].payout, dogs[0].odds);
                    printf("2. %s  %d to 1  %d%%\n", dogs[1].name, dogs[1].payout, dogs[1].odds);
                    printf("3. %s  %d to 1  %d%%\n", dogs[2].name, dogs[2].payout, dogs[2].odds);
                    printf("4. %s  %d to 1  %d%%\n", dogs[3].name, dogs[3].payout, dogs[3].odds);
                    printf("5. %s  %d to 1  %d%%\n", dogs[4].name, dogs[4].payout, dogs[4].odds);
                    printf("6. %s  %d to 1  %d%%\n", dogs[5].name, dogs[5].payout, dogs[5].odds);
                    printf("7. %s  %d to 1  %d%%\n", dogs[6].name, dogs[6].payout, dogs[6].odds);
                    printf("8. %s  %d to 1  %d%%\n", dogs[7].name, dogs[7].payout, dogs[7].odds);
                    printf("9. %s  %d to 1  %d%%\n", dogs[8].name, dogs[8].payout, dogs[8].odds);
                    
                    // Prompt the user to pick a dog
                    printf("Which dog do you pick? ");
                    scanf("%d", &pick);

                    if (pick < 1 || pick > 9)
                    {
                        printf("invalid choice.\n");
                    }
                    else
                    {
                        
                        pick = pick - 1;

                        // Generate a random number between 1 and 100 to determine the winner
                        roll = rand() % 100 + 1;

                        // Determine the winner based on the random roll and the odds of each dog
                        if (roll <= 40)
                        {
                            winner = 0;
                        }
                        else if (roll <= 50)
                        {
                            winner = 1;
                        }
                        else if (roll <= 58)
                        {
                            winner = 2;
                        }
                        else if (roll <= 64)
                        {
                            winner = 3;
                        }
                        else if (roll <= 65)
                        {
                            winner = 4;
                        }
                        else if (roll <= 69)
                        {
                            winner = 5;
                        }
                        else if (roll <= 77)
                        {
                            winner = 6;
                        }
                        else if (roll <= 87)
                        {
                            winner = 7;
                        }
                        else
                        {
                            winner = 8;
                        }

                        printf("\nThe dogs start running!\n");
                        printf("The winner is %s!\n", dogs[winner].name);

                        // Store the results of the race in the races array
                        races[totalRaces].dogPicked = pick;
                        races[totalRaces].dogWon = winner;
                        races[totalRaces].wager = wager;

                        if (pick == winner)
                        {
                            winnings = wager * dogs[pick].payout;
                            cash = cash + winnings;
                            printf("You won $%.2f!\n", winnings);
                        }
                        else
                        {
                            cash = cash - wager;
                            printf("You lost $%.2f\n", wager);
                        }

                        totalRaces = totalRaces + 1;
                    }
                }
            }
            break;

        case 'B':
        case 'b':
            printf("[W]ithdraw or [D]eposit? ");
            scanf(" %c", &bankChoice);
            printf("How much? $");
            scanf("%lf", &amount);
            
            // Handle banking operations based on user input
            switch (bankChoice)
            {
            case 'W':
            case 'w':
                if (amount > 0 && amount <= bank)
                {
                    bank = bank - amount;
                    cash = cash + amount;
                }
                else
                {
                    printf("You cant do that.\n");
                }
                break;
            case 'D':
            case 'd':
                if (amount > 0 && amount <= cash)
                {
                    cash = cash - amount;
                    bank = bank + amount;
                }
                else
                {
                    printf("You cant do that.\n");
                }
                break;
            default:
                printf("Thats not a choice.\n");
                break;
            }
            break;

        case 'R':
        case 'r':
            if (totalRaces == 0)
            {
                printf("No races yet.\n");
            }
            else
            {
                showRaces(dogs, races, 0, totalRaces);
            }
            break;

        case 'L':
        case 'l':
            printf("Program Ended\n");
            break;

        default:
            printf("Thats not a choice.\n");
            break;
    }

    // If the user did not choose to quit display the menu again
    if (choice != 'L' && choice != 'l')
    {
        menu(dogs, races, totalRaces, cash, bank);
    }
}
// Main function to initialize the game and start the menu
int main()
{
    // Initialize the array of dogs with their names, payouts, and odds
    struct DOG dogs[9] = {
        {"Mango", 2, 40},
        {"Rambo", 5, 10},
        {"Luck", 10, 8},
        {"Speed", 15, 6},
        {"Lightning", 50, 1},
        {"Delta", 20, 4},
        {"Luna", 10, 8},
        {"Charlie", 5, 10},
        {"Speedy", 3, 13}
    };

    struct RACE races[100];

    //The random number generator with the current time to ensure different results each run
    srand(time(0));

    // Start the menu with initial cash and bank values
    menu(dogs, races, 0, 100, 500);

    return 0;
}