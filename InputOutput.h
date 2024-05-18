using std::cin;
using std::cout;
using std::endl;

/**
 * @class InputOutput
 * @brief Handles input and output operations for the Appointment Scheduling System.
 *
 * This class provides methods for displaying menus, headers, messages, and collecting user input.
 */
class InputOutput
{
public:
    /**
     * @brief Displays the role selection menu.
     */
    void optionMenu()
    {
        cout << "=========================================" << endl;
        cout << "Please, select your role" << endl;
        cout << "(1) Role: Patient" << endl;
        cout << "(2) Role: Registrator" << endl;
        cout << "(3) Exit" << endl;
        cout << "=========================================" << endl;
        cout << endl;
    }

    /**
     * @brief Displays the menu for a registrator.
     */
    void optionMenuForRegistrator()
    {
        cout << endl;
        cout << "=========================================" << endl;
        cout << "(1) Schedule appointment" << endl;
        cout << "(2) Cancel appointment" << endl;
        cout << "(3) Add visit card for appointment" << endl;
        cout << "(4) Get visit cards for a patient" << endl;
        cout << "(5) Check doctor's schedule" << endl;
        cout << "(6) Exit" << endl;
        cout << "=========================================" << endl;
        cout << endl;
    }

    /**
     * @brief Displays the menu for a patient.
     */
    void optionMenuForPatient()
    {
        cout << endl;
        cout << "=========================================" << endl;
        cout << "(1) Schedule appointment" << endl;
        cout << "(2) Cancel appointment" << endl;
        cout << "(3) Check existing appointments" << endl;
        cout << "(4) Exit" << endl;
        cout << "=========================================" << endl;
        cout << endl;
    }

    /**
     * @brief Prints a hospital visit card.
     * @param patientName The name of the patient.
     * @param doctorName The name of the doctor.
     * @param dateTime The date and time of the visit.
     * @param diagnosis The diagnosis given to the patient.
     */
    void printVisitCard(string patientName, string doctorName, string dateTime, string diagnosis)
    {
        cout << "Patient Name: " << patientName << endl;
        cout << "Doctor Name: " << doctorName << endl;
        cout << "Date & Time: " << dateTime << endl;
        cout << "Diagnosis: " << diagnosis << endl;
        cout << "--------------------------------------" << endl;
        cout << endl;
    }

    /**
     * @brief Prints a message to the console.
     * @param msg The message to be printed.
     */
    void headerMsg(string msg)
    {
        cout << endl;
        cout << "=========================================" << endl;
        cout << msg << endl;
        cout << "=========================================" << endl;
        cout << endl;
    }

    /**
     * @brief Shows a single appointment.
     * @param index The index of the appointment.
     * @param appointment A pair containing the date and time of the appointment and the doctor's name.
     */
    void showAppointment(int index, pair<string, pair<string, string>> appointment)
    {
        cout << "(" << index << ") "
             << "-----------------------------" << endl;
        cout << "    Date & Time: " << appointment.first << endl;
        cout << "    Doctor: " << appointment.second.second << endl;
    }

    /**
     * @brief Retrieves user's choice from the menu.
     * @return The user's choice.
     */
    int getUserChoice()
    {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    /**
     * @brief Retrieves user's input information.
     * @param text The message to be printed.
     * @return The user's input.
     */
    string getInfo(string text)
    {
        string data;
        cout << text;
        cin >> data;
        return data;
    }

    /**
     * @brief Displays the schedule of a doctor.
     * @param appointments A vector of pairs containing appointment information.
     *
     * This method prints the schedule of a doctor by iterating through the vector of appointments
     * and displaying each appointment's date and time along with the patient's name.
     */
    void printDoctorSchedule(vector<pair<string, pair<string, string>>> &appointments)
    {
        cout << "=========================================" << endl;
        for (auto &appointment : appointments)
        {
            cout << "Date & Time: " << appointment.first << ", Patient: " << appointment.second.first << endl;
        }
        cout << "=========================================" << endl;
    }

    /**
     * @brief Retrieves a valid choice from the user.
     * @tparam T The type of elements in the vector.
     * @param vec The vector of choices.
     * @return The user's valid choice index.
     *
     * This method prompts the user for a choice and validates it against the size of the vector.
     * If the choice is invalid, it displays a message and returns -1; otherwise, it returns the
     * index of the valid choice.
     */
    template <typename T>
    int getValidChoice(vector<T> &vec)
    {
        int choice = getUserChoice();
        if (choice < 1 || choice > vec.size())
        {
            cout << endl;
            printMsg("\n Invalid choice. Please try again.");

            return -1;
        }
        return choice;
    }

    /**
     * @brief Displays appointment information.
     * @param index The index of the appointment.
     * @param date The date and time of the appointment.
     * @param doctorName The name of the doctor.
     * @param patientName The name of the patient.
     *
     * This method displays the information of an appointment, including its index, date and time,
     * the name of the doctor, and the name of the patient.
     */
    void showAppointment(int index, string date, string doctorName, string patientName)
    {
        cout << "(" << index << ") "
             << "-----------------------------" << endl;
        cout << "     Date & Time: " << date << endl;
        cout << "     Doctor: " << doctorName << endl;
        cout << "     Patient: " << patientName << endl;
        cout << endl;
    }

    /**
     * @brief Displays available appointment times.
     * @param availableTimes A vector of pairs containing available appointment times and corresponding doctors.
     *
     * This method displays the available appointment times along with their indices for selection.
     */
    void showAvailableTimes(vector<pair<string, string>> &availableTimes)
    {
        int index = 1;
        for (auto &timeDoctorPair : availableTimes)
        {
            cout << "Time: " << timeDoctorPair.first << "  (" << index << ")" << endl;
            index++;
        }
        cout << endl;
    }

    /**
     * @brief Displays information about people.
     * @tparam T The type of elements in the vector.
     * @param items The vector containing information about people.
     *
     * This method displays information about people stored in the vector, including their names.
     */
    template <typename T>
    void showPeople(vector<T> &items)
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            cout << "(" << i + 1 << ") " << items[i].getName() << endl;
        }
    };

    /**
     * @brief Prints a message to the console.
     * @param prompt The message to be printed.
     */
    void printMsg(string prompt)
    {
        cout << prompt << endl;
    }
};
