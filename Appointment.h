/**
 * @class Appointment
 * @brief Represents an appointment between a doctor and a patient.
 *
 * This class encapsulates information about an appointment, including the date and time,
 * the doctor involved, and the patient attending the appointment.
 */
class Appointment
{
private:
    string _dateTime; ///< The date and time of the appointment.
    Doctor _doctor;   ///< The doctor involved in the appointment.
    Patient _patient; ///< The patient attending the appointment.

public:
    /**
     * @brief Constructs an Appointment object with the given date and time, doctor, and patient.
     * @param dateTime The date and time of the appointment.
     * @param doctor The doctor involved in the appointment.
     * @param patient The patient attending the appointment.
     */
    Appointment(string &dateTime, Doctor &doctor, Patient &patient)
        : _dateTime(dateTime), _doctor(doctor), _patient(patient) {}

    /**
     * @brief Gets the date and time of the appointment.
     * @return A constant reference to the date and time of the appointment.
     */
    string &getDateTime()
    {
        return _dateTime;
    }

    /**
     * @brief Gets the doctor involved in the appointment.
     * @return A constant reference to the doctor involved in the appointment.
     */
    Doctor &getDoctor()
    {
        return _doctor;
    }

    /**
     * @brief Gets the patient attending the appointment.
     * @return A constant reference to the patient attending the appointment.
     */
    Patient &getPatient()
    {
        return _patient;
    }
};
