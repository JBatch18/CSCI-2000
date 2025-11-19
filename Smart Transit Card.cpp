#include <iostream>

using namespace std;

void PrintMenu();
float Recharge(float currentBalance);
void TapIn(int* ptr_startZone, int* ptr_startHour,bool* ptr_inTrip);
void TapOut(int* ptr_startZone,int* ptr_startHour,int* ptr_endZone,int* ptr_endHour,float* ptr_balance,int* ptr_numTripPenalties,bool* ptr_inTrip);
void ShowBalance(float currentBalance);
void ShowLastTrip(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour);
void Debug(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour, float* ptr_balance, int* ptr_numTripPenalties, bool* ptr_inTrip);
float CalcFare(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour);

int main()
{
	
	int choice, startZone, startHour, endZone, endHour,numTripPenalties;
	int* ptr_startZone = nullptr;
	int* ptr_startHour = nullptr;
	int* ptr_endZone = nullptr;
	int* ptr_endHour = nullptr;
	int* ptr_numTripPenalties = nullptr;
	float balance = 0.00;
	float* ptr_balance = nullptr;
	bool exit = false;
	bool inTrip = false;
	bool* ptr_inTrip = nullptr;

	ptr_inTrip = &inTrip;
	ptr_balance = &balance;
	ptr_startZone = &startZone;
	ptr_startHour = &startHour;
	ptr_endZone = &endZone;
	ptr_endHour = &endHour;
	ptr_numTripPenalties = &numTripPenalties;
	

	do
	{
		PrintMenu();
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			balance = Recharge(balance);
			break;
		case 2:
			TapIn(ptr_startZone,ptr_startHour,ptr_inTrip);
			break;
		case 3:
			TapOut(ptr_startZone,ptr_startHour,ptr_endZone,ptr_endHour,ptr_balance,ptr_numTripPenalties,ptr_inTrip);
			break;
		case 4:
			ShowBalance(balance);
			break;
		case 5:
			ShowLastTrip(ptr_startZone,ptr_startHour,ptr_endZone,ptr_endHour);
			break;
		case 6:
			Debug(ptr_startZone,ptr_startHour,ptr_endZone,ptr_endHour,ptr_balance,ptr_numTripPenalties,ptr_inTrip);
			break;
		case 7:
			exit = true;
			break;
		default:
			cout << "Invalid choice! Please enter choice (1-7)!\n";
			break;
		}
	} while (!exit);

}

float Recharge(float currentBalance)
{
	float recharge = 0.00;
	
	do
	{
		cout << "Enter Recharge Amount: ";
		cin >> recharge;
		cout << endl;
		if (recharge <= 0.00)
		{
			cout << "Invalid amount! Please try again!\n";
		}
		else if (recharge > 0.00)
		{
			currentBalance += recharge;
			cout << "Recharge successful. New balance: $" << currentBalance << endl;
			return currentBalance;
		}
	} while (recharge <= 0.00);
	
	
}
void TapIn(int* ptr_startZone, int* ptr_startHour,bool* ptr_inTrip)
{
	if (*ptr_inTrip)
	{
		cout << "Warning! You are already in a trip! Please tap out first!\n";
		*ptr_inTrip = true;
		return;
	}
	else
	{
		do
		{
			cout << "Please enter the starting zone (1-3): ";
			cin >> *ptr_startZone;
			cout << endl;

			if (*ptr_startZone < 1 || *ptr_startZone > 3)
			{
				cout << "Invalid Start Zone! Please try again!\n";
			}

		} while (*ptr_startZone < 1 || *ptr_startZone > 3);

		do
		{
			cout << "Please enter the starting hour (0-23): ";
			cin >> *ptr_startHour;
			cout << endl;

			if (*ptr_startHour < 0 || *ptr_startHour > 23)
			{
				cout << "Invalid Start Hour! Please try again!\n";
			}
		} while (*ptr_startHour < 0 || *ptr_startHour > 23);
	}

	cout << "Tap-In recorded sucessfully!\n";
	*ptr_inTrip = true;
	return;
}
void TapOut(int* ptr_startZone,int* ptr_startHour,int* ptr_endZone,int* ptr_endHour,float* ptr_balance,int* ptr_numTripPenalties,bool* ptr_inTrip)
{
	float fare;

	if (((!*ptr_inTrip) && *ptr_balance >= 6.00))
	{
		cout << "Penalty charged: $6.00\n";

		*ptr_balance -= 6.00;
		*ptr_numTripPenalties += 1;
		cout << "New balance is: $" << *ptr_balance << endl;
		return;

	}
	else if (((!*ptr_inTrip) && *ptr_balance < 6.00))
	{
		cout << "Insufficient balance to pay penalty. Please recharge!\n";
		*ptr_numTripPenalties += 1;
		return;
	}
	else
	{
	
		do
		{
			cout << "Please enter ending zone (1-3): ";
			cin >> *ptr_endZone;
			cout << endl;
			if (*ptr_endZone < 1 || *ptr_endZone > 3)
			{
				cout << "Invalid input! Please try again!\n";
			}
		} while (*ptr_endZone < 1 || *ptr_endZone > 3);
		do
		{
			
			cout << "Please enter ending hour (0-23): ";
			cin >> *ptr_endHour;
			cout << endl;
		} while (*ptr_endHour < 0 || *ptr_endHour > 23);
		
		fare = CalcFare(ptr_startZone, ptr_startHour, ptr_endZone, ptr_endHour);
		cout << "Fare is: $" << fare << endl;
		*ptr_balance -= fare;
		cout << "New balance is: $" << *ptr_balance << endl;
		*ptr_inTrip = false;
		return;
	}
}
float CalcFare(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour)
{
	float baseFare = 2.50;
	float peakHourFare = 1.25;
	float crossZoneFare = 1.75;
	bool peakHours = false;
	bool crossZone = false;
	float totalFare;

	
	if (((*ptr_startHour >= 7) && (*ptr_startHour <= 9)) || ((*ptr_endHour >= 17) && (*ptr_endHour <= 19)))
	{
		peakHours = true;
	}
	
	if (*ptr_endZone != *ptr_startZone)
	{
		crossZone = true;
	}

	if (peakHours && crossZone)
	{
		totalFare = baseFare + peakHourFare + crossZoneFare;
		return totalFare;
	}
	else if (peakHours && (!crossZone))
	{
		totalFare = baseFare + peakHourFare;
		return totalFare;
	}
	else if (crossZone && (!peakHours))
	{
		totalFare = baseFare + crossZoneFare;
		return totalFare;
	}
	else
	{
		return baseFare;
	}

}
void ShowLastTrip(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour)
{
	float lastFare;

	if (*ptr_endZone < 1)
	{
		cout << "No previous trip found!\n";
	}
	else
	{
		lastFare = CalcFare(ptr_startZone, ptr_startHour, ptr_endZone, ptr_endHour);

		cout << "Last Trip Summary\n";
		cout << "-----------------\n";
		cout << "Start Zone: " << *ptr_startZone << endl;
		cout << "End Zone  : " << *ptr_endZone << endl;
		cout << "Start Hour: " << *ptr_startHour << endl;
		cout << "End Hour  : " << *ptr_endHour << endl;
		cout << "Fare Paid : " << lastFare << endl;
	}
}
void ShowBalance(float currentBalance)
{
	cout << "You current balance is: $" << currentBalance << endl;
	return;
}
void Debug(int* ptr_startZone, int* ptr_startHour, int* ptr_endZone, int* ptr_endHour, float* ptr_balance, int* ptr_numTripPenalties, bool* ptr_inTrip)
{
	cout << "[ADMIN DEBUG]\n";
	cout << "balance     @ " << ptr_balance << endl;
	cout << "inTrip      @ " << ptr_inTrip << endl;
	cout << "startZone   @ " << ptr_startZone << endl;
	cout << "startHour   @ " << ptr_startHour << endl;
	cout << "endZone     @ " << ptr_endZone << endl;
	cout << "endHour     @ " << ptr_endHour << endl;
	cout << "numTripPens @ " << ptr_numTripPenalties << endl;
}
void PrintMenu()
{
	cout << "========== SMART TRANSIT CARD ===========\n";
	cout << "1) Recharge\n";
	cout << "2) Tap-In\n";
	cout << "3) Tap-Out\n";
	cout << "4) Show Balance\n";
	cout << "5) Show Last Trip\n";
	cout << "6) Admin/Debug\n";
	cout << "7) Exit\n";
	cout << "Choose: ";
}

