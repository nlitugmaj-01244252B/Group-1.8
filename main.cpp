#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

//=========================================================
//                MOTOR CLASS
//=========================================================

class Motor
{
private:
    string motorName;
    double ratedCurrent;
    double measuredCurrent;
    double currentDifference;
    string status;

public:

    // Enter Motor Details
    void setMotorDetails()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter Motor Name: ";
        getline(cin, motorName);

        cout << "Enter Rated Current (A): ";
        cin >> ratedCurrent;

        cout << "Enter Measured Current (A): ";
        cin >> measuredCurrent;
    }

    // Validate Inputs
    bool validateDetails()
    {
        if(ratedCurrent <= 0 || measuredCurrent < 0)
        {
            cout << "\nInvalid current values!" << endl;
            return false;
        }

        return true;
    }

    // Compare Current Values
    void checkCurrentStatus()
    {
        currentDifference = measuredCurrent - ratedCurrent;

        if(measuredCurrent <= ratedCurrent)
        {
            status = "Safe Operation";
        }
        else
        {
            status = "Overload Warning";
        }
    }

    // Display Report
    void displayMotorReport()
    {
        cout << "\n============== MOTOR REPORT ==============" << endl;

        cout << "Motor Name         : " << motorName << endl;
        cout << "Rated Current      : " << ratedCurrent << " A" << endl;
        cout << "Measured Current   : " << measuredCurrent << " A" << endl;
        cout << "Current Difference : " << currentDifference << " A" << endl;
        cout << "Status             : " << status << endl;

        cout << "==========================================" << endl;
    }

    // Save Report
    void saveMotorReport(ofstream &file)
    {
        file << "Motor Name         : " << motorName << endl;
        file << "Rated Current      : " << ratedCurrent << " A" << endl;
        file << "Measured Current   : " << measuredCurrent << " A" << endl;
        file << "Current Difference : " << currentDifference << " A" << endl;
        file << "Status             : " << status << endl;
        file << "------------------------------------------" << endl;
    }

    // Return Status
    string getStatus()
    {
        return status;
    }
};
//=========================================================
//                    MAIN FUNCTION
//=========================================================

int main()
{
    int choice;
    int numberOfMotors;
    int safeMotors;
    int overloadedMotors;

    bool exitProgram = false;

    Motor motor;

    do
    {
        cout << "\n==========================================" << endl;
        cout << " MOTOR CURRENT SAFETY MONITORING SYSTEM" << endl;
        cout << "==========================================" << endl;

        cout << "1. Monitor Motors" << endl;
        cout << "2. View Saved Report" << endl;
        cout << "3. Clear Report" << endl;
        cout << "4. About System" << endl;
        cout << "5. Exit" << endl;

        cout << "\nEnter your choice: ";

        if(!(cin >> choice))
        {
            cout << "\nInvalid input! Please enter a number between 1 and 5." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        switch(choice)
        {

        //=================================================
        // CASE 1 : MONITOR MOTORS
        //=================================================

        case 1:
        {
            ofstream reportFile("motor_current_report.txt", ios::app);

            cout << "\nEnter number of motors to check: ";
            cin >> numberOfMotors;

            if(numberOfMotors <= 0)
            {
                cout << "\nInvalid number of motors." << endl;
                break;
            }

            safeMotors = 0;
            overloadedMotors = 0;

            reportFile << "\n========== NEW REPORT ==========\n";

            for(int i = 1; i <= numberOfMotors; i++)
            {
                cout << "\nMotor " << i << endl;

                motor.setMotorDetails();

                if(!motor.validateDetails())
                {
                    i--;
                    continue;
                }

                motor.checkCurrentStatus();

                motor.displayMotorReport();

                motor.saveMotorReport(reportFile);

                if(motor.getStatus() == "Safe Operation")
                {
                    safeMotors++;
                }
                else
                {
                    overloadedMotors++;
                }
            }

            cout << "\n========== SUMMARY ==========" << endl;
            cout << "Total Motors       : " << numberOfMotors << endl;
            cout << "Safe Motors        : " << safeMotors << endl;
            cout << "Overloaded Motors  : " << overloadedMotors << endl;

            reportFile.close();

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        //=================================================
        // CASE 2 : VIEW REPORT
        //=================================================

        case 2:
        {
            ifstream report("motor_current_report.txt");

            if(!report)
            {
                cout << "\nNo saved report found." << endl;
            }
            else
            {
                string line;

                if(report.peek() == ifstream::traits_type::eof())
                {
                    cout << "\nNo saved report found." << endl;
                }
                else
                {
                    cout << "\n========== SAVED REPORT ==========\n";

                    while(getline(report, line))
                    {
                        cout << line << endl;
                    }
                }

                report.close();
            }

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }
 //=================================================
        // CASE 3 : CLEAR REPORT
        //=================================================

        case 3:
        {
            ofstream clearFile("motor_current_report.txt");

            clearFile.close();

            cout << "\nReport cleared successfully." << endl;

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        //=================================================
        // CASE 4 : ABOUT SYSTEM
        //=================================================

        case 4:
        {
            cout << "\n========== ABOUT THIS SYSTEM ==========\n";

            cout << "Motor Current Safety Monitoring System\n\n";

            cout << "This system compares the Rated Current\n";
            cout << "with the Measured Current of a motor.\n\n";

            cout << "If Measured Current <= Rated Current\n";
            cout << "Status = Safe Operation\n\n";

            cout << "If Measured Current > Rated Current\n";
            cout << "Status = Overload Warning\n\n";

            cout << "Features\n";
            cout << "- Monitor multiple motors\n";
            cout << "- Save reports\n";
            cout << "- View reports\n";
            cout << "- Clear reports\n";

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        //=================================================
        // CASE 5 : EXIT
        //=================================================

        case 5:

            cout << "\nThank you for using the system." << endl;

            exitProgram = true;

            break;

        //=================================================
        // DEFAULT
        //=================================================

        default:

            cout << "\nInvalid choice! Please try again." << endl;

            break;

        }

    } while(!exitProgram);

    return 0;
}


