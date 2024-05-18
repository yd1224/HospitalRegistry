/**
 * @class Patient
 * @brief Represents a patient in the appointment scheduling system.
 * @inherit AbstractPerson
 *
 * This class inherits from AbstractPerson and represents a patient with a name and date of birth.
 * It provides methods to print appointment details and cancel appointments.
 */
class Patient : public AbstractPerson
{
private:
    InputOutput interface; ///< The input-output interface for interacting with the user.

public:
    /**
     * @brief Constructs a Patient object with the given name and date of birth.
     * @param name The name of the patient.
     * @param dateOfBirth The date of birth of the patient.
     */
    Patient(const string &name, const string &dateOfBirth) : AbstractPerson(name, dateOfBirth) {}

    /**
     * @brief Prints the details of appointments for the patient.
     *
     * This method displays the details of appointments for the patient, including the date and time
     * of each appointment and the name of the doctor involved.
     */
    void printDetails() override
    {
        interface.headerMsg("Appointments");

        if (appointments.size() == 0)
        {
            interface.printMsg("\n No appointments to show \n");
            return;
        }

        int index = 1;
        for (auto &appointment : appointments)
        {
            interface.showAppointment(index, appointment);
            index++;
        }
    }
};
