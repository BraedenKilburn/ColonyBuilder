/********************************
 * Author: Braeden Kilburn
 * Section: 1005
 * Date Created: 6 May 2020
 * Description: Build a colony with
 * different sectors having their
 * own improvement. Aim to build
 * a colony with the greatest
 * amount of productivity based off
 * of your score.
 *******************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Constants
const int RESOURCE_TYPES = 4;
enum resourceTypes { POPULARITY, ECOLOGY, COMMERCE, INDUSTRY };

const int UPGRADE_COUNT = 6;

//Colony Array is Height x Width
const int COLONY_HEIGHT = 4;
const int COLONY_WIDTH = 5;

//insert improvement struct here
struct improvement {
    string name;
    int collects[RESOURCE_TYPES];
    int develops[RESOURCE_TYPES];
};

//insert sector struct here
struct sector {
    int resources[RESOURCE_TYPES];
    improvement zone;
};

//Prints the sectors of the colony in tabular format
void printColony(const sector colony[][COLONY_WIDTH])
{
    for (int i = 0; i < COLONY_HEIGHT; i++)
    {
        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "+----" << i + 1 << static_cast<char>('A' + j);
            cout << "----+ ";
        }
        cout << endl;

        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "|";
            unsigned int spaces = 10 - colony[i][j].zone.name.length();
            for (unsigned int k = 0; k < spaces / 2; k++)
            {
                cout << " ";
            }
            cout << colony[i][j].zone.name;
            for (unsigned int k = 0; k < spaces - spaces / 2; k++)
            {
                cout << " ";
            }
            cout << "| ";
        }
        cout << endl;

        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "|POP: " << colony[i][j].zone.collects[POPULARITY];
            cout << " x" << setw(2) << colony[i][j].resources[POPULARITY] << "| ";
        }
        cout << endl;

        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "|ECO: " << colony[i][j].zone.collects[ECOLOGY];
            cout << " x" << setw(2) << colony[i][j].resources[ECOLOGY] << "| ";
        }
        cout << endl;

        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "|COM: " << colony[i][j].zone.collects[COMMERCE];
            cout << " x" << setw(2) << colony[i][j].resources[COMMERCE] << "| ";
        }
        cout << endl;

        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            cout << "|IND: " << colony[i][j].zone.collects[INDUSTRY];
            cout << " x" << setw(2) << colony[i][j].resources[INDUSTRY] << "| ";
        }
        cout << endl;
    }

    for (int j = 0; j < COLONY_WIDTH; j++)
    {
        cout << "+----------+ ";
    }
    cout << endl;
}

//Function Prototypes
void getResourceTotals(sector[][COLONY_WIDTH], int[], int);
int getScore(int[], int);
void placeImprovement(sector[][COLONY_WIDTH], improvement, int, int);

//Handles I/O with user as well as the game loop
int main()
{
    sector colony[COLONY_HEIGHT][COLONY_WIDTH];
    int resourceTotals[RESOURCE_TYPES];
    //Sector Improvements
    improvement upgrades[UPGRADE_COUNT];
    upgrades[0] = { "Wilderness",{0,0,0,0}, { 0, 0, 0, 0} };
    upgrades[1] = { "Settlement",{1,1,1,1}, { 0, 0, 0, 0} };
    upgrades[2] = { "Farm",{0,2,0,0}, { 1, 1,-1,-1} };
    upgrades[3] = { "Mine",{0,0,0,2}, {-1,-1, 1, 1} };
    upgrades[4] = { "City",{0,0,2,0}, { 0,-1, 2,-1} };
    upgrades[5] = { "Resort",{2,0,0,0}, { 1, 1, 0,-2} };

    //Seed Random Number Generator
    srand(time(NULL));

    //Initialize sector resource values to random amounts from 0-3
    for (int i = 0; i < COLONY_HEIGHT; i++)
    {
        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            colony[i][j].zone = upgrades[0];
            for (int k = 0; k < RESOURCE_TYPES; k++)
            {
                int randomAmount = rand() % 100;
                if (randomAmount >= 95)
                {
                    colony[i][j].resources[k] = 3;
                }
                else if (randomAmount >= 80)
                {
                    colony[i][j].resources[k] = 2;
                }
                else if (randomAmount >= 50)
                {
                    colony[i][j].resources[k] = 1;
                }
                else
                {
                    colony[i][j].resources[k] = 0;
                }
            }
        }
    }

    //Allows user to select 12 improvements to the colony then provides a final score
    for (int i = 12; i > 0; i--)
    {
        //Colony Status
        printColony(colony);

        getResourceTotals(colony, resourceTotals, RESOURCE_TYPES);

        cout << "Colony Status: ";
        cout << "[" << resourceTotals[POPULARITY] << " Popularity] ";
        cout << "[" << resourceTotals[ECOLOGY] << " Ecology] ";
        cout << "[" << resourceTotals[COMMERCE] << " Commerce] ";
        cout << "[" << resourceTotals[INDUSTRY] << " Industry] ";
        cout << "\nCurrent Score: " << getScore(resourceTotals, RESOURCE_TYPES) << endl;

        //Improvement Selection Menu
        cout << "Place Improvement (" << i << "/12)\n";
        cout << "[1] Settlement (Px1 Ex1 Cx1 Ix1)(P 0 E 0 C 0 I 0)\n";
        cout << "[2] Farm       (Px0 Ex2 Cx0 Ix0)(P+1 E+1 C-1 I-1)\n";
        cout << "[3] Mine       (Px0 Ex0 Cx0 Ix2)(P-1 E-1 C+1 I+1)\n";
        cout << "[4] City       (Px0 Ex0 Cx2 Ix0)(P 0 E-1 C+2 I-1)\n";
        cout << "[5] Resort     (Px2 Ex0 Cx0 Ix0)(P+1 E+1 C 0 I-2)\n";

        //User Selects Improvement to Build
        int zoneType = 0;
        do
        {
            cout << "Select improvement to construct(1-" << UPGRADE_COUNT - 1 << "): ";
            cin >> zoneType;
            if (cin.fail())
            {
                cout << "Invalid improvement type, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            }
        } while (zoneType <= 0 || zoneType > UPGRADE_COUNT);
        cin.ignore(100000, '\n');

        //User Selects Location to Build Improvement
        string location;
        int x, y;
        do
        {
            cout << "Construct " << upgrades[zoneType].name << " location: ";
            cin >> location;
            if (location.length() == 2)
            {
                //Allows location to be selected with either lower or upper case coordinate value
                if (location[1] >= 'a' && location[1] <= 'z')
                {
                    location[1] -= 'a' - 'A';
                }
                //Converts user input to coordinates
                x = location[1] - 'A';
                y = location[0] - '1';

                //Ensures coordinates are within the colony bounds
                if (y >= 0 && y < COLONY_HEIGHT && x >= 0 && x < COLONY_WIDTH)
                {
                    break;
                }
                else
                {
                    cout << "Invalid location, please try again.\n";
                }
            }
            else
            {
                cout << "Invalid location, please try again.\n";
            }
        } while (true);
        cin.ignore(100000, '\n');

        placeImprovement(colony, upgrades[zoneType], x, y);
    }

    //Final Status of Colony
    printColony(colony);

    getResourceTotals(colony, resourceTotals, RESOURCE_TYPES);

    cout << "\nFinished Colony: ";
    cout << "[" << resourceTotals[POPULARITY] << " Popularity] ";
    cout << "[" << resourceTotals[ECOLOGY] << " Ecology] ";
    cout << "[" << resourceTotals[COMMERCE] << " Commerce] ";
    cout << "[" << resourceTotals[INDUSTRY] << " Industry] ";
    cout << "\nFinal Score: " << getScore(resourceTotals, RESOURCE_TYPES) << endl;
}

// Calculates how much of each resource is collected within each sector
void getResourceTotals(sector colony[][COLONY_WIDTH], int resourceTotals[RESOURCE_TYPES], int resourceCount)
{
    // Initialize resourceTotals[RESOURCE_TYPE] to zero
    for (int i = 0; i < resourceCount; i++)
    {
        resourceTotals[i] = 0;
    }

    // Goes through each colony and multiplies it's collect score with it's resources multiplier then adds
    // that number to the resourceTotals specific to it's resource type
    for (int i = 0; i < COLONY_HEIGHT; i++)
    {
        for (int j = 0; j < COLONY_WIDTH; j++)
        {
            for (int k = 0; k < resourceCount; k++)
            {
                resourceTotals[k] += colony[i][j].zone.collects[k] * colony[i][j].resources[k];
            }
        }
    }
}

// Calculates and returns the score for the current colony
int getScore(int resources[], int resourceCount)
{
    int lowestScore = INT32_MAX;
    int score = 0;

    for (int i = ECOLOGY; i < resourceCount; i++) //Search starting from ecology (skip Popularity)
    {
        if (resources[i] < lowestScore)
            lowestScore = resources[i];
    }

    score = resources[POPULARITY] * lowestScore;

    return score;
}

// Replace the improvement at the specified coordinates with a new one
void placeImprovement(sector colony[][COLONY_WIDTH], improvement newZone, int x, int y)
{
    // Remove resource "develops" values of current improvement sector and surrounding sectors
    // based on what type of development the chosen sector is
    if (colony[y][x].zone.name == "Farm") // Remove "Farm" develops values in the improvement sector and surrounding sectors
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (!(i >= 0 && i < COLONY_HEIGHT)) // Not within bounds, continue
                continue;

            for (int j = x - 1; j <= x + 1; j++)
            {
                if (!(j >= 0 && j < COLONY_WIDTH)) // Not within bounds, continue
                    continue;

                colony[i][j].resources[POPULARITY]--;
                colony[i][j].resources[ECOLOGY]--;
                colony[i][j].resources[COMMERCE]++;
                colony[i][j].resources[INDUSTRY]++;

                // Change the collection rates to zero to start fresh
                for (int k = 0; k < RESOURCE_TYPES; k++)
                {
                    colony[i][j].zone.collects[k] = 0;
                }
            }
        }
    }
    else if (colony[y][x].zone.name == "Mine") // Remove "Mine" develops values in the improvement sector and surrounding sectors
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (!(i >= 0 && i < COLONY_HEIGHT)) // Not within bounds, continue
                continue;

            for (int j = x - 1; j <= x + 1; j++)
            {
                if (!(j >= 0 && j < COLONY_WIDTH)) // Not within bounds, continue
                    continue;

                colony[i][j].resources[POPULARITY]++;
                colony[i][j].resources[ECOLOGY]++;
                colony[i][j].resources[COMMERCE]--;
                colony[i][j].resources[INDUSTRY]--;

                // Change the collection rates to zero to start fresh
                for (int k = 0; k < RESOURCE_TYPES; k++)
                {
                    colony[i][j].zone.collects[k] = 0;
                }
            }
        }
    }
    else if (colony[y][x].zone.name == "City") // Remove "City" develops values in the improvement sector and surrounding sectors
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (!(i >= 0 && i < COLONY_HEIGHT)) // Not within bounds, continue
                continue;

            for (int j = x - 1; j <= x + 1; j++)
            {
                if (!(j >= 0 && j < COLONY_WIDTH)) // Not within bounds, continue
                    continue;

                colony[i][j].resources[ECOLOGY]++;
                colony[i][j].resources[COMMERCE] -= 2;
                colony[i][j].resources[INDUSTRY]++;

                // Change the collection rates to zero to start fresh
                for (int k = 0; k < RESOURCE_TYPES; k++)
                {
                    colony[i][j].zone.collects[k] = 0;
                }
            }
        }
    }
    else if (colony[y][x].zone.name == "Resort") // Remove "Resort" develops values in the improvement sector and surrounding sectors
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (!(i >= 0 && i < COLONY_HEIGHT)) // Not within bounds, continue
                continue;

            for (int j = x - 1; j <= x + 1; j++)
            {
                if (!(j >= 0 && j < COLONY_WIDTH)) // Not within bounds, continue
                    continue;

                colony[i][j].resources[POPULARITY]--;
                colony[i][j].resources[ECOLOGY]--;
                colony[i][j].resources[INDUSTRY] += 2;

                // Change the collection rates to zero to start fresh
                for (int k = 0; k < RESOURCE_TYPES; k++)
                {
                    colony[i][j].zone.collects[k] = 0;
                }
            }
        }
    }

    // Add the resource "develops" value for the new improvement to all 9 adjacent sectors
    for (int i = y - 1; i <= y + 1; i++)
    {
        if (!(i >= 0 && i < COLONY_HEIGHT)) // Not within bounds, continue
            continue;

        for (int j = x - 1; j <= x + 1; j++)
        {
            if (!(j >= 0 && j < COLONY_WIDTH)) // Not within bounds, continue
                continue;

            for (int k = 0; k < RESOURCE_TYPES; k++)
            {
                colony[i][j].resources[k] += newZone.develops[k];
            }
        }
    }

    // Change the "zone" value of the sector y,x to the new improvement name
    colony[y][x].zone.name = newZone.name;

    // Change the collects value of the sector y,x to the new improvement collection value
    for (int i = 0; i < RESOURCE_TYPES; i++)
    {
        colony[y][x].zone.collects[i] += newZone.collects[i];
    }
}