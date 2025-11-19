#include <iostream>

using namespace std;

void printMenu();

int main()
{
    bool light_on = false;
    int choice;
    do
    {
   
        printMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (light_on == true)
            {
                cout << "\nLight is already on! 💡\n";
            }
            else
            {
                cout << "\nLight is now ON - your room is bright! 💡\n";
                light_on = true;
            }
            break;
        case 2:
            if (light_on == false)
            {
                cout << "\nLight is already off! 🌑\n";
            }
            else
            {
                cout << "\nLight is now OFF - your room is dark. 🌑\n";
                light_on = false;
            }
            break;
        case 3:
            if (light_on)
            {
                cout << "\nStatus: Light is on! 💡\n";
            }
            else
            {
                cout << "\nStatus: Light is off! 🌑\n";
            }
            break;
        default:
            break;
        }
    } while (choice != 4);

}

void printMenu()
{
    cout << "------------------------------\n";
    cout << "🏠 Smart Home Light by Justin\n";
    cout << "------------------------------\n";
    cout << "Room : Bedroom\n";
    cout << "[1] Turn ON 💡\n";
    cout << "[2] Turn OFF 🌑\n";
    cout << "[3] Status 📋\n";
    cout << "[4] Exit App 🚪\n";
    cout << "------------------------------\n";
    cout << "Enter your choice(1 - 4) : ";
}