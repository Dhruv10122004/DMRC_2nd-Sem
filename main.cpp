#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <thread>
#include <iomanip>

using namespace std;
using namespace chrono;

int ind;
int point = 1;
//FUNCTION DECLARATION

// Generates a random UMI (Unique Member Identifier) for user registration
string setPassword2();

// Checks if the given UMI and password combination exists in the user details file
bool presentInFile(string umi, string pass, vector<vector<string>> &details);

// Allows the user to add an amount to their account balance
void addAmount(vector<vector<string>> &details);

// Simulates a travel journey for the user
void travel(vector<vector<string>> &details);

// Updates user details such as password
void updateDetails(vector<vector<string>> &details);

// Writes user details to a file
void writeToFile(vector<vector<string>> &details);

//FOR STORING AND GETTING LOCKER NUMBER
void locker(string station_name, vector<vector<string>> &details);

//GENERATES RANDOM LOCKER NUMBER
int getlockerNumber();
//CHARGING FOR LOCKER USES
void deductLockerAmount(vector<vector<string>> &details);

//HELPDESK PROVIDES ALL THE NECESSARY DETAILS THAT 
void helpdesk();
//CLASS DECLARATION
class FileHandling;
class UserDetails
{
protected:
    string name;
    string aadhar;
    string phone_number;
    string umi;
    string password;
    string age;
    string gender;
    double balance = 0;

public:
    vector<vector<string>> duplicate;
    vector<string> line;
    UserDetails()
    {
        umi = setUmi();
        password = setPassword();
        cout << "Name: ";
        fflush(stdin);
        getline(cin, name);
        cout << endl
             << "Phone Number: ";
        fflush(stdin);
        getline(cin, phone_number);
        cout << endl
             << "AADHAR Number: ";
        fflush(stdin);
        getline(cin, aadhar);
        cout << endl
             << "Age: ";
        cin >> age;
        cout << endl
             << "Gender (M for Male/ F for female/ O for others): ";
        cin >> gender;
        try
        {
            cout << "Enter the amount you want to add in your account (Minimum entry is 200)." << endl;
            cin >> balance;

            if (balance < 200)
            {
                throw "Minimum amount to be added is 200.";
            }
        }
        catch (const char *str)
        {
            cout << str << endl;
            cout << "Enter the amount again: ";
            cin >> balance;
        }
    }
    //It  provides an auto-generated 4 character unique umi
    string setUmi();

    //provided an auto-generated password
    string setPassword();
};
//tHIS FUNCTION GENERATES RANDOM CHARACTER
char randomch(string st, int len)
{
    int x = rand() % len;//It will generate Random number from 0 to len-1
    return st[x];
}

string UserDetails ::setUmi()
{
    srand(time(0));
    string st = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    int size = 4;
    string id = "";
    for (int i = 0; i < size; i++)
    {
        id = id + randomch(st, 62);
    }
    return id;
}
string UserDetails ::setPassword()
{
    srand(time(0));
    string st = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*";
    int size = 4;
    string pass = "";
    for (int i = 0; i < size; i++)
    {
        pass = pass + randomch(st, 70);
    }
    return pass;
}

class FileHandling : public UserDetails//class file handling inheriting class user details-->INHERITANCE
{
public:
    FileHandling()//constructor of class file handling
    {
        string new_pass, new_pass_check, pass;
        cout << "Your Password is " << password << endl;
        int choice;
        cout << "If you want to change the password then press 1 else press any other digit" << endl;
        cin >> choice;
        int flag = 2;
        if (choice == 1)
        {
            cout << "Enter the new password: " << endl;
            new_pass = setPassword2();
            cout << endl
                 << "Re-enter the new password: " << endl;
        repeat:
            new_pass_check = setPassword2();
            if (new_pass == new_pass_check)
            {
                password = new_pass;
                flag = 1;
            }
            if (flag == 2)
            {
                cout << endl
                     << "Password was not set" << endl;
                cout << endl
                     << "Re-Enter the new password" << endl;
                new_pass_check = setPassword();
                cout << endl;
                goto repeat;
            }
        }
        string word;
        string str = umi + " " + password + " " + to_string(balance) + " " + aadhar + " " + phone_number + " " + age + " " + gender + " " + name;
        stringstream obj(str);
        while (obj >> word)
        {
            line.push_back(word);
        }
        duplicate.push_back(line);
    }
    //This function provides the copy of the class 
    vector<vector<string>> getDVector();
};

vector<vector<string>> FileHandling ::getDVector()
{
    return duplicate;
}
//This function HIDES THE password -->ENCAPSULATION
string setPassword2()
{
    string pass;
    fflush(stdin);
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && !pass.empty())
        {
            cout << "\b \b";
            pass.pop_back();
        }
        else
        {
            cout << "*";
            pass += ch;
        }
    }
    return pass;
}

bool presentInFile(string umi, string pass, vector<vector<string>> &details)
{
    int flag = 0;
    for (int i = 0; i < details.size(); i++)
    {
        if (details[i][0] == umi && pass == details[i][1])
        {
            flag = 1;
            ind = i;
            break;
        }
    }
    if (flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getLockerNumber()
{
    srand(time(nullptr));
    int locker_number = (rand() % 5) + 1;
    return locker_number;
}

void helpdesk()
{
    cout << endl;
    cout << endl;
    cout << left << setw(35) << "DMRC 24x7 Helpline" << right << setw(126) << "DMRC Missing, Separated, Women, Child and Specially Abled Commuters Helpline" << endl;
    cout << left << setw(35) << "PH : 155370 (This call is chargeable)" << right << setw(65) << "PH : 011-23415480" << endl;
    cout << left << setw(35) << "Mail : helpline@dmrc.org" << right << setw(65) << "PH : 8800550490" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << left << setw(35) << "Delhi Police Control Room" << right << setw(73) << "Senior Citizen Helpline" << endl;
    cout << left << setw(35) << "PH  : 112" << right << setw(64) << "PH : 1091, 129" << endl;
    cout << left << setw(35) << "Mail : delpol.service@delhipolice.gov.in" << right << setw(85) << "Mail : delpol.service@delhipolice.gov.in" << endl;
}

void locker(string station_name, vector<vector<string>> &details)
{
    int locker_no = getLockerNumber();
    cout << "Your Locker Number is " << locker_no << endl;
    details[ind].push_back(to_string(locker_no));
}
void emptyLocker(vector<vector<string>> &details)
{
    cout << "Your locker has been successfully emptied" << endl;
    details[ind][9] = "false";
}

void deductLockerAmount(vector<vector<string>> &details)
{
    int amount = stoi(details[ind][2]);
    if (amount - 50 < 0)
    {
        cout << "Balance Low" << endl;
        cout << "Please add money to your account to take an exit" << endl;
        addAmount(details);
    }
    cout << "Deducting Money..." << endl;
    Sleep(2000);
    amount -= 50;
    details[ind][2] = to_string(amount);
}

void addAmount(vector<vector<string>> &details)
{
    int amt;
    cout << "Enter the amount you want to add to your Account" << endl;
    cin >> amt;
    int fin_amt = stoi(details[ind][2]);
    cout << fin_amt << endl;
    fin_amt += amt;
    cout << fin_amt << endl;
    details[ind][2] = to_string(fin_amt);
}

void travel(vector<vector<string>> &details)
{
    vector<string> stations = {"Noida Electronic City", "Noida Sector 62", "Noida Sector 59", "Noida Sector 61", "Noida Sector 52", "Noida Sector 34", "Noida City Centre", "Golf Course",
                               "Botanical Garden", "Noida Sector 18", "Noida Sector 16",
                               "Noida Sector 16", "New Ashok Nagar", "New Ashok Nagar", "Mayur Vihar I", "Akshardham", "Yamuna Bank", "Indraprastha", "Pragati Maidan", "Mandi House", "Barakhamb", "Rajiv Chowk",
                               "R K Ashram Marg", "Jhandewalan", "Karol Bagh", "Rajendra Place", "Patel Nagar", "Shadipur",
                               "Kirti Nagar", "Moti Nagar", "Ramesh Nagar", "Rajouri Garden", "Tagore Garden",
                               "Subhash Nagar", "Tilak Nagar", "Janak Puri East", "Uttam Nagar East", "Uttam Nagar West", "Nawada", "Dwarka Mor", "Dwarka"};

    int ch;
    cout << "Welcome to the DMRC Platform" << endl;
    cout << "Enter 1 for Time based travel and 2 for Destination based travel" << endl;

    cin >> ch;

    auto now = system_clock::to_time_t(system_clock::now());
    /*to_time_t is a function that reads time from the system clock and converts it into an object of data
    type time_t*/

    // Convert the current time to local time
    struct tm *local_time = localtime(&now); // the struct type tm holds the date and time in the form of a C structure
    /*Local time function from the <ctime> header to convert time from second - since - epoch format(time_t)
    to a calendar time representation based on your system's locale.*/

    // Extract the hour component from the local time
    int hour = local_time->tm_hour;

    // Determine whether it's AM or PM
    string period = (hour < 12) ? "GOOD MORNING" : (hour > 16) ? "Good EVENING"
                                                               : "GOOD AFTERNOON";
    cout << period << endl;

    switch (ch)
    {
    case 1://Time based travel
    {
        string station_name;
        cout << "Please enter the station name from where you are starting your journey" << endl;
        fflush(stdin);
        getline(cin, station_name);
        int cnt;

        for (cnt = 0; cnt < stations.size(); cnt++)
        {
            if (station_name == stations[cnt])
            {
                break;
            }
        }
        details[ind].push_back(to_string(cnt));
        cout << "Do you want to store your belongings in the locker ?" << endl;
        cout << "Rs 50 will be charged for the locker" << endl;
        cout << "Enter 1 for Yes and 0 for No" << endl;

        int c;
        cin >> c;

        if (c)
        {
            locker(station_name, details);
            details[ind].push_back("true");
            deductLockerAmount(details);
        }
        else
        {
            cout << "You have opted for No" << endl;
            cout << "Enjoy your journey further" << endl;
            details[ind].push_back("false");
        }

        if (details[ind][9] == "true")
        {
            if (details[ind][8] == to_string(cnt))
            {
                cout << "Your belongings are stored here" << endl;
                cout << "Do you want them out ?" << endl;
                int want;
                cout << "Enter 1 for Yes and 0  for No" << endl;
                cin >> want;
                if (want)
                {
                    emptyLocker(details);
                }
            }
        }

        cout << "PLATFORM 1: TOWARDS NOIDA ELECTRONIC CITY"
             << "        ";
        cout << "       PLATFORM 2: TOWARDS DWARKA" << endl;

        int choice;
        cout << " Enter the platform from where you want to board the train" << endl;
        cin >> choice;

        if (choice == 1)
        {
            reverse(stations.begin(), stations.end());
            cnt = 40 - cnt;
        }

        cout << "Press any key to start the journey, and press Enter to stop." << endl;
        _getch(); // Wait for any key press to start the timer

        auto start_time = high_resolution_clock::now(); // Record the start time from the epoch ( 1st January, 1970 ).

        cout << "Journey started. Press Enter to stop." << endl;
        int check = 0;
        int flag = 0;

        while (!_kbhit() || _getch() != '\r')
        {
            cout << "STATION ARRIVED: " << stations[cnt] << endl;
            Sleep(3000);
            cnt++;
            Sleep(2000);
        }
        cout << "Destination Reached: " << stations[cnt - 1] << endl;

        // Loop until Enter key is pressed
        /*REASON FOR COMPARISION WITH '\r'
        In C and C++, the Enter key typically generates a carriage return (\r) character followed by a newline (\n) character when pressed.

    When you call _getch() after _kbhit() to capture the Enter key press, you're actually capturing the carriage return character (\r). This is because _getch() reads a single character from the keyboard buffer, and when you press Enter, the Enter key press is immediately stored in the buffer as a single character, which is the carriage return character.

    So, when checking for the Enter key press using _getch(), you should compare the returned character with \r to detect the carriage return character generated by the Enter key press.

    Here's the relevant part of the code:

    cpp
    while (!_kbhit() || _getch() != '\r') {
    // Loop until Enter key (carriage return) is pressed
    }


    This loop continues until _kbhit() detects a key press and _getch() returns the carriage return character (\r), indicating that the Enter key has been pressed.

        */

        auto end_time = high_resolution_clock::now(); // Record the end time again from the epoch (1st January, 1970).
        duration<double> dd = end_time - start_time;  // Calculate the duration
        int dur = (int)dd.count();
        cout << "Timer stopped. Elapsed time: " << dur << " seconds." << endl;
        int amt;
        if (dur <= 9)
        {
            amt = 10;
        }
        else if (dur > 9 && dur <= 21)
        {
            amt = 20;
        }
        else if (dur > 21 && dur <= 45)
        {
            amt = 30;
        }
        else if (dur > 45 && dur <= 60)
        {
            amt = 40;
        }
        else if (dur > 60 && dur <= 75)
        {
            amt = 50;
        }
        else if (dur > 75 && dur <= 90)
        {
            amt = 60;
        }
        else
        {
            amt = 70;
        }

        cout << "Amount charged: " << amt << endl;
        int amount = stoi(details[ind][2]);
        if (amount - amt < 0)
        {
            cout << "Balance Low" << endl;
            cout << "Please add money to your account to take an exit" << endl;
            addAmount(details);
        }

        cout << amt << endl;
        int a = stoi(details[ind][2]);
        a -= amt;
        details[ind][2] = to_string(a);
        cout << details[ind][2] << endl;

        if (details[ind][9] == "true")
        {
            if (details[ind][8] == to_string(cnt))
            {
                cout << "Your belongings are stored here" << endl;
                cout << "Do you want them out ?" << endl;
                int want;
                cout << "Enter 1 for Yes and 0  for No" << endl;
                cin >> want;
                if (want)
                {
                    emptyLocker(details);
                }
            }
        }
    }
    break;

    case 2://DESTINATION BASED TRAVEL
    {
        string start, end;
        int s1, s2;
        cout << "Enter the name of the starting station" << endl;
        fflush(stdin);
        getline(cin, start);
        cout << "Enter the name of the ending station" << endl;
        fflush(stdin);
        getline(cin, end);

        cout << "Do you want to store your belongings in the locker ?" << endl;
        cout << "Rs 50 will be charged for the locker" << endl;
        cout << "Enter 1 for Yes and 0 for No" << endl;
        int cnt;
        for (cnt = 0; cnt < stations.size(); cnt++)
        {
            if (start == stations[cnt])
            {
                break;
            }
        }

        int c;
        cin >> c;//TAKING CHOICE

        if (c)
        {
            locker(start, details);
            details[ind].push_back("true");
            deductLockerAmount(details);
        }
        else
        {
            cout << "You have opted for No" << endl;
            cout << "Enjoy your journey further" << endl;
            details[ind].push_back("false");
        }

        if (details[ind][9] == "true")
        {
            if (details[ind][8] == to_string(cnt))
            {
                cout << "Your belongings are stored here" << endl;
                cout << "Do you want them out ?" << endl;
                int want;
                cout << "Enter 1 for Yes and 0  for No" << endl;
                cin >> want;
                if (want)
                {
                    emptyLocker(details);
                }
            }
        }

        cout << "PLATFORM 1: TOWARDS NOIDA ELECTRONIC CITY"
             << "        ";
        cout << "       PLATFORM 2: TOWARDS DWARKA" << endl;

        int choice;
        cout << " Enter the platform from where you want to board the train" << endl;
        cin >> choice;

        if (choice == 1)
        {
            reverse(stations.begin(), stations.end());
        }

        int ticket_amt;

        for (int i = 0; i < stations.size(); i++)
        {
            if (stations[i] == start)
            {
                s1 = i;
            }
            if (stations[i] == end)
            {
                s2 = i;
            }
        }

        ticket_amt = (s2 - s1) * 5;

        cout << "Journey Started" << endl;

        while (s1 != s2)
        {
            cout << "STATION ARRIVED: " << stations[s1] << endl;
            Sleep(3000);
            s1++;
            Sleep(2000);
        }
        cout << "Destination Reached: " << stations[s2] << endl;

        cout << "Press Enter to continue..." << endl;
        _getch();
        if (_getch() == '\r')
        {
            system("cls");
        }

        cout << "Fetching Fare..." << endl;
        Sleep(2000);

        cout << "Amount charged: " << ticket_amt << endl;
        int amount = stoi(details[ind][2]);
        if (amount - ticket_amt < 0)
        {
            cout << "Balance Low" << endl;
            cout << "Please add money to your account to take an exit" << endl;
            addAmount(details);
        }

        cout << ticket_amt << endl;
        int a = stoi(details[ind][2]);
        a -= ticket_amt;
        details[ind][2] = to_string(a);
        cout << details[ind][2] << endl;
        if (details[ind][9] == "true")
        {
            if (details[ind][8] == to_string(cnt))
            {
                cout << "Your belongings are stored here" << endl;
                cout << "Do you want them out ?" << endl;
                int want;
                cout << "Enter 1 for Yes and 0  for No" << endl;
                cin >> want;
                if (want)
                {
                    emptyLocker(details);
                }
            }
        }
    }
    }
}

void writeToFile(vector<vector<string>> &details)
{
    if (point)
    {
        ofstream out;
        string s = "";
        int cnt = 0; // Works for preventing extra blank line addition at the end of every run.
        out.open("user_details.txt");
        for (auto detail : details)
        {
            cnt++;
            for (int j = 0; j < detail.size(); j++)
            {
                s += detail[j] + " ";
            }
            if (cnt == details.size())
            {
                out << s;
            }
            else
            {
                out << s << endl;
            }
            s = "";
        }
    }
    else
    {
        ofstream out;
        string s = "";
        int cnt = 0;
        out.open("user_details.txt", ios::app);
        for (auto detail : details)
        {
            cnt++;
            for (int j = 0; j < detail.size(); j++)
            {
                s += detail[j] + " ";
            }
            out << endl
                << s;
            s = "";
        }
    }
}
void updateDetails(vector<vector<string>> &details)//Helps the user to change their respective password 
{
    cout << "ENTER AADHAR FOR VERIFICATION\n"
         << endl;
    char ch;
    string aadhar;
    string new_pass, verify_pass;
    cin >> aadhar;
    int flag = 0;
    for (int i = 0; i < details.size(); i++)
    {
        if (details[i][3] == aadhar)
        {
            cout << "Acces Granted" << endl;
            cout << "Enter the new password" << endl;
            new_pass = setPassword2();
            fflush(stdin);
            cout << endl
                 << "Re-Enter the new password" << endl;
            verify_pass = setPassword2();
        repeat:
            if (new_pass == verify_pass)
            {
                details[i][1] = new_pass;
                flag = 1;
                break;
            }
            else
            {
                cout << endl
                     << "Password was not set" << endl;
                flag = 2;
            }
            if (flag == 2)
            {
                cout << endl
                     << "Re-Enter the new password" << endl;//2-step confirmation
                verify_pass = setPassword2();
                cout << endl;
                goto repeat;
            }
        }
    }

    if (flag == 0)
    {
        cout << "Aadhar Not found" << endl;
        cout << "ENTER 1 FOR TRY AGAIN\nENTER 2 FOR EXIT THE CODE\n"
             << endl;
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            updateDetails(details);
        }
        else if (ch == 2)
        {
            exit(0);
        }
    }
}

int main()// OPERATES ALL THE FLOW OF THE CODE
{
    vector<vector<string>> details;
    vector<string> line;
    int choice, ch;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "                                        -----Hello! Welcome to the DMRC platform-----          " << endl;
    cout << "                                                           Made by :-" << endl;
    cout << "                                            **************************************" << endl;
    cout << "                                            *            Dhruv Khanna            *" << endl;
    cout << "                                            *            Dhruv Rawat             *" << endl;
    cout << "                                            *            Supratik Mukherjee      *" << endl;
    cout << "                                            **************************************"; 
    cout << endl
         << endl;

    helpdesk();

    cout << "Press Enter to continue..." << endl;
    _getch();
    if (_getch() == '\r')
    {
        system("cls");
    }

    cout << "Enter 1 for SIGN UP" << endl;
    cout << "Enter 2 for SIGN IN" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        FileHandling fh1;//CALLING File handling constructor
        vector<vector<string>> duplicate = fh1.getDVector();
        cout << endl
             << "Congratulations!! You have successfully been registered." << endl;

        cout << "Press Enter to continue..." << endl;
        _getch();
        if (_getch() == '\r')
        {
            system("cls");
        }

        cout << "Enter 1 if you want to travel right now." << endl;
        cout << endl;
        cout << "Enter 2 if you want to exit the platform." << endl;
        cin >> ch;
        if (ch == 1)
        {
            travel(duplicate);
            point = 0;
            writeToFile(duplicate);
        }
        else
        {
            point = 0;
            writeToFile(duplicate);
            return 0;
        }
    }
    break;
    case 2:
    {
        ifstream in;
        string str;
        string word;
        in.open("user_details.txt");
        while (in.eof() == 0)
        {
            getline(in, str);
            stringstream obj(str);
            while (obj >> word)
            {
                line.push_back(word);
            }
            details.push_back(line);
            line.clear();
        }
        in.close();
        string umi, pass;
        cout << "WELCOME TO LOGIN PAGE" << endl;
        cout << "Enter the umi and password respectively" << endl;
        fflush(stdin);
        getline(cin, umi);
        fflush(stdin);
        getline(cin, pass);
        if (presentInFile(umi, pass, details))
        {
            cout << "PROFILE VERIFIED" << endl;
            travel(details);
        }
        else
        {
            cout << "Wrong umi and password\nEnter 1 if you forgot password\nEnter 2 if you want to sign up\nEnter 3 if you want to exit\n"
                 << endl;
            int ch;
            cin >> ch;
            if (ch == 3)
            {
                cout << "Thank you for your visit\n";
                exit(0);
            }
            else if (ch == 1)
            {
                updateDetails(details);
            }
            else if (ch == 2)
            {
                FileHandling fh2;
            }
        }
        for (auto i : details)
        {
            for (auto j : i)
            {
                cout << j << " ";
            }
            cout << endl;
        }
        point = 1;
        writeToFile(details);
    }
    break;
    }
}
