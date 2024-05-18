/**
 * @class AbstractPerson
 * @brief Represents an abstract person in the hospital system.
 *
 * This class provides common functionalities and data members for both patients
 * and doctors, such as name, date of birth, and appointments.
 */
class AbstractPerson
{
protected:
    string name;                                             ///< The name of the person.
    string dateOfBirth;                                      ///< The date of birth of the person.
    vector<pair<string, pair<string, string>>> appointments; ///< Appointments associated with the person.

public:
    /**
     * @brief Constructs an AbstractPerson object with the given name and date of birth.
     * @param name The name of the person.
     * @param dateOfBirth The date of birth of the person.
     */
    AbstractPerson(const string &name, const string &dateOfBirth) : name(name), dateOfBirth(dateOfBirth) {}

    /**
     * @brief Constructs an AbstractPerson object with the given name.
     * @param name The name of the person.
     */
    AbstractPerson(const string &name) : name(name) {}

    /**
     * @brief Pure virtual function to print details of the person.
     *
     * This function must be implemented by derived classes to print details specific to the person type.
     */
    virtual void printDetails() = 0;

    /**
     * @brief Gets the name of the person.
     * @return The name of the person.
     */
    string &getName()
    {
        return name;
    }

    /**
     * @brief Gets the appointments associated with the person.
     * @return A reference to the vector of appointments.
     */
    vector<pair<string, pair<string, string>>> &getAppointments()
    {
        return appointments;
    }

    /**
     * @brief Adds an appointment for the person.
     * @param dateTime The date and time of the appointment.
     * @param patientName The name of the patient associated with the appointment.
     * @param doctorName The name of the doctor associated with the appointment.
     */
    void addAppointment(string &dateTime, string &patientName, string &doctorName)
    {
        appointments.push_back(make_pair(dateTime, make_pair(patientName, doctorName)));
    }

    /**
     * Deletes an appointment from the appointments list based on the specified date and time, patient name, and doctor name.
     * @param dateTime The date and time of the appointment to delete.
     * @param patientName The name of the patient associated with the appointment.
     * @param doctorName The name of the doctor associated with the appointment.
     */
    void deleteAppointment(string &dateTime, string &patientName, string &doctorName)
    {
        auto it = std::remove_if(appointments.begin(), appointments.end(),
                                 [&](pair<string, pair<string, string>> &appointment)
                                 {
                                     return (appointment.first == dateTime &&
                                             appointment.second.first == patientName &&
                                             appointment.second.second == doctorName);
                                 });

        appointments.erase(it, appointments.end());
    }
};
