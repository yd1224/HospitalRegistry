/**
 * @class Doctor
 * @brief Represents a doctor in the hospital system.
 *
 * This class inherits from the AbstractPerson class and represents a doctor
 * with functionalities such as checking availability, printing schedule details,
 * and canceling appointments.
 */
class Doctor : public AbstractPerson
{
private:
    InputOutput interface; ///< InputOutput object for displaying information.

public:
    /**
     * @brief Constructs a Doctor object with the given name.
     * @param name The name of the doctor.
     */
    Doctor(const string &name) : AbstractPerson(name) {}

    /**
     * @brief Checks if the doctor is available at the given date and time.
     * @param dateTime The date and time to check for availability.
     * @return True if the doctor is available, false otherwise.
     */
    bool isAvailable(string &dateTime)
    {
        for (auto &app : appointments)
        {
            if (app.first == dateTime)
                return false;
        }
        return true;
    }

    /**
     * @brief Prints the schedule details of the doctor.
     *
     * This method prints the schedule details of the doctor, including the
     * appointments booked.
     */
    void printDetails() override
    {
        interface.printDoctorSchedule(appointments);
    }
};
