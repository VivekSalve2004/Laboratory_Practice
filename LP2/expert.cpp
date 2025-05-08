#include <iostream>
#include <string>
using namespace std;

bool isManager() {
    string position;
    cout << "Enter your position: ";
    getline(cin, position);
    if (position != "Manager") {
        cout << "Access denied. Only Managers can perform this operation." << endl;
        return false;
    }
    return true;
}

void evaluateEmployee() {
    string name, position;
    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter employee's position: ";
    getline(cin, position);

    if (position == "Manager") {
        cout << "Managers cannot evaluate themselves." << endl;
        return;
    }

    int p, q, t, l;
    cout << "Rate punctuality (1-10): ";
    cin >> p;
    cout << "Rate work quality (1-10): ";
    cin >> q;
    cout << "Rate teamwork (1-10): ";
    cin >> t;
    cout << "Rate leadership (1-10): ";
    cin >> l;
    cin.ignore();

    float avg = (p + q + t + l) / 4.0;
    cout << "Employee " << name << " (" << position << ") has a score of " << avg << "/10." << endl;

    if (avg >= 8)
        cout << "Outstanding performance!" << endl;
    else if (avg >= 6)
        cout << "Good, but can improve." << endl;
    else
        cout << "Needs improvement. Training recommended." << endl;
}

void suggestTraining() {
    string skill;
    cout << "Enter area to improve (Leadership, Technical, Communication): ";
    getline(cin, skill);

    for (char& c : skill)
        c = tolower(c);

    if (skill == "leadership")
        cout << "Suggested: Leadership & Management Training" << endl;
    else if (skill == "technical")
        cout << "Suggested: Advanced Technical Skills Workshop" << endl;
    else if (skill == "communication")
        cout << "Suggested: Effective Communication Skills" << endl;
    else
        cout << "Suggested: General Professional Development" << endl;
}

void calculateBonus() {
    string name, position;
    float salary, score;
    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter position: ";
    getline(cin, position);
    cout << "Enter base salary: ";
    cin >> salary;
    cout << "Enter performance score (1-10): ";
    cin >> score;
    cin.ignore();

    float multiplier = 0.1;
    if (position == "Intern") multiplier = 0.05;
    else if (position == "Junior Developer") multiplier = 0.10;
    else if (position == "Senior Developer") multiplier = 0.15;
    else if (position == "Manager") multiplier = 0.20;
    else if (position == "Director") multiplier = 0.25;

    float bonus = (score / 10.0) * salary * multiplier;
    cout << "Bonus for " << name << ": INR " << bonus << endl;
}

void checkPromotionEligibility() {
    string name, position;
    int experience, lastPromo;
    float score;

    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter position: ";
    getline(cin, position);
    cout << "Years of experience: ";
    cin >> experience;
    cout << "Years since last promotion: ";
    cin >> lastPromo;
    cout << "Performance score (1-10): ";
    cin >> score;
    cin.ignore();

    if (score >= 8 && experience > 3 && lastPromo > 2)
        cout << name << " is eligible for promotion." << endl;
    else
        cout << name << " is not eligible for promotion yet." << endl;
}

void checkWorkLifeBalance() {
    string name;
    int hours;
    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter average weekly work hours: ";
    cin >> hours;
    cin.ignore();

    if (hours > 50)
        cout << name << ", you might be overworking. Try balancing better." << endl;
    else
        cout << name << ", your work-life balance is good." << endl;
}

int main() {
    cout << "Welcome to the Employee Evaluation Expert System!" << endl;

    while (true) {
        cout << endl;
        cout << "Options:" << endl;
        cout << "1. Evaluate Performance" << endl;
        cout << "2. Suggest Training" << endl;
        cout << "3. Calculate Bonus" << endl;
        cout << "4. Check Promotion Eligibility" << endl;
        cout << "5. Check Work-Life Balance" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (isManager()) evaluateEmployee();
                break;
            case 2:
                if (isManager()) suggestTraining();
                break;
            case 3:
                if (isManager()) calculateBonus();
                break;
            case 4:
                if (isManager()) checkPromotionEligibility();
                break;
            case 5:
                checkWorkLifeBalance();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}