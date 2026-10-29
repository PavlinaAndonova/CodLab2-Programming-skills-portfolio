
#include <iostream>
#include <string>
using namespace std;

// Function to get the distance travelled
double getDistance() {
    double distance;
    cout << "Enter distance travelled in miles: ";
    cin >> distance;
    return distance;
}

// Function to get the fuel type
string getFuelType() {
    string fuel;
    cout << "Enter fuel type (petrol or diesel): ";
    cin >> fuel;
    return fuel;
}

// Function to calculate CO2 emissions
double calculateCO2(double distance, string fuel) { // distance in miles, fuel type as string
    double fuelConsumption = 9.66; // average fuel consumption in litres per 100 km
    double emissionsPerLitre; // CO2 emissions per litre of fuel in kg

    if (fuel == "diesel" || fuel == "Diesel") { // Check for diesel fuel type
        emissionsPerLitre = 2.68; // CO2 emissions per litre of diesel in kg
    }
    else if (fuel == "petrol" || fuel == "Petrol") { // Check for petrol fuel type
        emissionsPerLitre = 2.31; // CO2 emissions per litre of petrol in kg
    }
    else { 
        return -1;
    }

    double litresUsed = (distance / 100) * fuelConsumption; // Convert distance from miles to litres used based on fuel consumption
    double emissions = litresUsed * emissionsPerLitre; // Calculate total CO2 emissions in kg

    return emissions;
}

int main() {
    double distance = getDistance(); // Get distance travelled from user
    string fuel = getFuelType(); // Get fuel type from user

    double result = calculateCO2(distance, fuel); // Calculate CO2 emissions based on distance and fuel type

    if (result == -1) { // Check for invalid fuel type
        cout << "Invalid fuel type entered." << endl; // Display error message for invalid fuel type
    }
    else { // If valid fuel type, display the estimated CO2 emissions
        cout << "Estimated CO2 emissions: "
             << result << " kg CO2" << endl;
    }

    return 0;
}
