#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//declare global variable for balance
double smart_pass_balance = 0.0;

//declare helper funcitons;
void PrintMenu();
void RechargeBalance(double* ptr_balance);
void PlanJourney(double* balance_pointer);
void SimTraffic();
void CityMap();
double ComputeJourneyFare(int start_zone, int end_zone, int travel_mode, int travel_hour);

int main()
{
    bool exit = false;
    int choice;
    double* ptr_balance = nullptr;
    ptr_balance = &smart_pass_balance;
    
    // generate seed for random number generation later on.
    srand(time(0));

    do
    {
        PrintMenu();
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 0:
            cout << "Now exiting SMART CITY TRANSPORT SYSTEM\n";
            exit = true;
            break;
        case 1:
            RechargeBalance(ptr_balance);
            break;
        case 2:
            PlanJourney(ptr_balance);
            break;
        case 3:
            SimTraffic();
            break;
        case 4:
            CityMap();
            break;
        default:
            break;
        }
    } while (!exit);
    
}
void CityMap()
{
    for (int row = 1; row <= 10; row++)
    {
        for (int column = 1;column <= 10;column++)
        {
            int generate_map_char = 0 + (rand() % 99);
            
            if (generate_map_char >= 0 && generate_map_char <= 9)
            {
                cout << 'B';
            }
            else if (generate_map_char >= 10 && generate_map_char <= 19)
            {
                cout << 'M';
            }
            else if (generate_map_char >= 20 && generate_map_char <= 29)
            {
                cout << 'T';
            }
            else if (generate_map_char >= 30 && generate_map_char <= 99)
            {
                cout << '.';
            }
        }
        cout << endl;
    }
}
void SimTraffic()
{
    int traffic_density, accident_risk, weather_code;
    
    traffic_density = 0 + (rand() % 100);
    accident_risk = 0 + (rand() % 10);
    weather_code = 1 + (rand() % 5);

    switch (weather_code)
    {
    case 1:
        cout << "Weather is Clear\n";
        break;
    case 2: 
        cout << "Weather is Cloudy\n";
        break;
    case 3:
        cout << "Weather is Light Rain\n";
        break;
    case 4:
        cout << "Weather is Heavy Rain\n";
        break;
    case 5:
        cout << "Weather is Storm\n";
        break;
    default:
        break;

    }
    if (traffic_density > 70 && weather_code > 3)
    {
        cout << "Expect heave delays!\n";
        if (accident_risk >= 8)
        {
            cout << "High accident risk please use caution!\n";
        }
    }
    else if (traffic_density < 30 && weather_code == 1)
    {
        cout << "Now is the ideal time to travel!\n";
        if (accident_risk >= 8)
        {
            cout << "High accident risk please use caution!\n";
        }
    }
    else
    {
        cout << "Traffic is moderate.\n";
        if (accident_risk >= 8)
        {
            cout << "High accident risk please use caution!\n";
        }
    }
}
void PlanJourney(double* balance_pointer)
{
    int start_zone, end_zone, travel_hour, travel_mode = 0;
    do
    {
        bool exit = false;

        cout << "Please enter the start zone (1-5): ";
        cin >> start_zone;
        cout << endl;
        if (start_zone < 1 || start_zone >5)
        {
            cout << "Please enter a start zone within range (1-5)!\n";
        }
        else if (start_zone >= 1 && start_zone <= 5)
        {
            exit = true;
        }

    } while (!exit);
    do
    {
        bool exit = false;

        cout << "Please enter the end zone (1-5): ";
        cin >> end_zone;
        cout << endl;
        if (end_zone < 1 || end_zone >5)
        {
            cout << "Please enter an end zone within range (1-5)!\n";
        }
        else if (end_zone >= 1 && end_zone <= 5)
        {
            exit = true;
        }

    } while (!exit);
    do
    {
        bool exit = false;
        cout << "Please enter the travel hour (0-23): ";
        cin >> travel_hour;
        cout << endl;
        if (travel_hour < 0 || travel_hour > 23)
        {
            cout << "Please enter a travel hour within the range (0-23)!\n";
        }
        else if (travel_hour >= 0 && travel_hour <= 23)
        {
            exit = true;
        }
    } while (!exit);
    do
    {
        bool exit = false;
        cout << "Please enter the travel mode (1=Bus, 2=Taxi, 3=Metro): ";
        cin >> travel_mode;
        cout << endl;
        if (travel_mode < 0 || travel_mode > 3)
        {
            cout << "Please enter a travel hour within the range (1=Bus, 2=Taxi, 3=Metro)!\n";
        }
        else if (travel_hour >= 0 && travel_hour <= 23)
        {
            exit = true;
        }
    } while (!exit);

   double fare = ComputeJourneyFare(start_zone, end_zone, travel_mode, travel_hour); 
   int pay_with_pass;
   do
   {
       bool exit = false;

       cout << "Are you paying with pass? (1 = Yes, 0 = No): ";
       cin >> pay_with_pass;
       cout << endl;
       if (pay_with_pass == 1 || pay_with_pass == 0)
       {
           exit = true;
       }
       else
       {
           "Invalid input please try again!\n";
       }
       
   } while (!exit);
   
   if (pay_with_pass == 1)
   {
       if (*balance_pointer >= fare)
       {
           *balance_pointer -= fare;
           cout << "Remaining balance is: $" << *balance_pointer << endl;
       }
       else
       {
           cout << "Insufficient balance!\n";
       }
   }
   else
   {
       cout << "Pleas pay $" << fare << "in cash.\n";
   }
}
double ComputeJourneyFare(int start_zone, int end_zone, int travel_mode, int travel_hour)
{
    double fare = 0.00;
    int zone_distance = abs(end_zone - start_zone);
    if (zone_distance > 2 && travel_hour >= 22)
    {
        cout << "Long-distance night travel. Please be cautious!\n";
    }

    switch (travel_mode)
    {
    case 1:
        fare = 2.0 + zone_distance * 1.0;
        break;
    case 2:
        fare = 3.0 + zone_distance * 2.0;
        break;
    case 3:
        fare = 2.5 + zone_distance * 1.5;
        break;
    default:
        break;
    }
    switch (travel_hour)
    {
    case 7:
    case 8:
    case 9:
    case 10:
        fare = fare * 1.25;
        break;
    case 17:
    case 18:
    case 19:
    case 20:
        fare = fare * 1.25;
        break;
    default:
        break;
    }
    return fare;
}
void RechargeBalance(double* ptr_balance)
{
    double amount = 0.00;
   
    do
    {
        cout << "Please enter the recharge amount: ";
        cin >> amount;
        cout << endl;
        if (amount < 5)
        {
            cout << "Please enter an amount greater than $5!\n";
        }

    } while (amount <= 5);
    cout << "Old balance is: $" << *ptr_balance << endl;
    if (amount >= 50)
    {
        *ptr_balance += amount + (amount * .1);
    }
    else
    {
        *ptr_balance += amount;
    }
    cout << "New balance is: $" << *ptr_balance << endl;
}
void PrintMenu()
{
    cout << "==============================\n";
    cout << " SMART CITY TRANSPORT SYSTEM\n";
    cout << "==============================\n";
    cout << "1. Recharge Smart-Pass\n";
    cout << "2. Plan a Journey\n";
    cout << "3. Simulate Traffic\n";
    cout << "4. View City Map\n";
    cout << "Enter you choice: ";
}