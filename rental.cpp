// Monica Bellare
// Code for Project 2

#include <iostream>
#include <iomanip>
using namespace std;

double rentalCharge1(double charge, int mi) { // method for adding to the rental charge for the first 100 miles
    return (charge + 0.27*mi);
}

double rentalCharge2(int charge, int mi, int mo) { // method for adding to the rental charge for the next 300 miles
    if(mo == 12 || (mo > 0 && mo < 4)) {
        return (charge + 0.27*mi);
    }
    else {
        return (charge + 0.21*mi);
    }
}

double rentalCharge3(int charge, int mi) { // method for adding to the rental charge for the remaining miles
    return (charge + 0.19*mi);
}

int main()
{
    int odometerStart;
    int odometerEnd;
    int miles;
    int rentalDays;
    string custName;
    string luxCar;
    int month;
    double rentalCharge;
    int valid = 0; // error counter
    
    cout << "Odometer at start: ";
    cin >> odometerStart;
    cout << "Odometer at end: ";
    cin >> odometerEnd;
    cout << "Rental days: ";
    cin >> rentalDays;
    cout << "Customer name: ";
    cin.ignore();
    getline(cin, custName);
    cout << "Luxury car? (y/n): ";
    getline(cin, luxCar);
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    cout << "---" << endl;
    
    if(odometerStart<0) {
        cout << "The starting odometer reading must be nonnegative." << endl;
        valid++; // accounts for the fact that the first input error has been found
    }
    
    if(odometerEnd<odometerStart && valid==0) {
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        valid++;
    }
    
    if(rentalDays < 0 && valid==0) {
        cout << "The number of rental days must be positive." << endl;
        valid++;
    }
    
    if(custName == "" && valid==0) {
        cout << "You must enter a customer name." << endl;
        valid++;
    }
    
    if(luxCar == "y") {
        rentalCharge = 61.0*rentalDays;
    }
    else if(luxCar == "n")
        rentalCharge = 33.0*rentalDays;
    else if(valid==0){ // for the case in which the user doesn't input y or n, and there have been no previous input error found
        rentalCharge = 0;
        cout << "You must enter y or n." << endl;
        valid++;
    }
    else { // for the case in which the user doesn't input y or n, but there have been/has been previous error(s)
        rentalCharge=0;
    }
    
    if((month < 1 || month > 12) && valid==0) {
        cout << "The month number must be in the range 1 through 12." << endl;
        valid++;
    }
    
    if(valid == 0) { // if no input errors have been found, and therefore the final line will not be an input error message
        miles = odometerEnd - odometerStart; // number of miles traveled
        
        if (miles<=100) { // only needs to call method for getting rental charge for first 100 miles or less
            rentalCharge = rentalCharge1(rentalCharge, miles);
        }
        else if (miles<=400) { // calls 2 methods for getting rental charge or first 100 miles and then remaining miles
            rentalCharge = rentalCharge1(rentalCharge, 100);
            rentalCharge = rentalCharge2(rentalCharge, (miles-100), month);
        }
        else { // calls 3 methods for getting rental charge for first 100 miles, next 300 miles, and then remaining miles
            rentalCharge = rentalCharge1(rentalCharge, 100);
            rentalCharge = rentalCharge2(rentalCharge, 300, month);
            rentalCharge = rentalCharge3(rentalCharge, (miles-400));
        }
        
        cout << "The rental charge for " << custName << " is $";
        cout << setprecision(2) << fixed << rentalCharge << endl;
    }
}
