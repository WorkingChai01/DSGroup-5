#include <iostream>
#include <windows.h>
#include <unistd.h>
#include "SequentialList.h"
#include "updateRank.h"
#include "purge_Sq.h"

using namespace std;

const string DB_FILE = "leaderboard.txt";

void manualAddPlayer(LeaderBoard* LB) {
    string name;
    int score, subs;
    cout << "\n--- Add Player ---" << endl;
    cout << "Name: (No Space)";
    cin >> name;
    cout << "Score: ";
    if (!(cin >> score)) { cin.clear(); cin.ignore(1000, '\n'); return; }
    cout << "Subs: ";
    if (!(cin >> subs)) { cin.clear(); cin.ignore(1000, '\n'); return; }
    cin.ignore(1000, '\n'); 
    updateRank(LB, name, score, subs);
    cout << "Copy" << endl;
}

int main() {
    LeaderBoard LB;
    InitBoard(&LB, 10);
    LoadFromTxt(&LB, DB_FILE);
    purge_Sq(&LB);
    //载入标准测试数据
    if (IsEmpty(&LB)) {
        updateRank(&LB, "Alice", 90, 2);
        updateRank(&LB, "Bob", 90, 1);
    }
    int choice;
    do {
        cout << "\n1. Show Rank\n2. Add Player\n3. Demo\n4. Save & Exit\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
            case 1: PrintBoard(&LB); break;
            case 2: manualAddPlayer(&LB); PrintBoard(&LB); break;
            case 3: 
                updateRank(&LB, "Bob", 95, 2);
                updateRank(&LB, "Catherine", 85, 10);
                PrintBoard(&LB); 
                break;
            case 4: SaveToTxt(&LB, DB_FILE); purge_Sq(&LB); break;
            default: cout << "Invalid." << endl;
        }
    } while (choice != 4);

    Destroy(&LB);
    system("pause");
    return 0;
}