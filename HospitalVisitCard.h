/**
 * @class HospitalVisitCard
 * @brief Represents a hospital visit card containing details of a patient's visit.
 *
 * This class encapsulates information about a patient's visit to the hospital, including
 * the attending doctor, patient, date and time of the visit, and diagnosis given.
 */
class HospitalVisitCard
{
private:
    Doctor _doctor;        ///< The doctor attending the patient.
    Patient _patient;      ///< The patient receiving the visit.
    InputOutput interface; ///< InputOutput object for displaying information.
    string _dateTime;      ///< The date and time of the visit.
    string _diagnosis;     ///< The diagnosis given to the patient.

public:
    /**
     * @brief Constructs a HospitalVisitCard object.
     * @param doc The doctor attending the patient.
     * @param pat The patient receiving the visit.
     * @param date The date and time of the visit.
     * @param diag The diagnosis given to the patient.
     */
    HospitalVisitCard(Doctor &doc, Patient &pat, string &date, string &diag)
        : _doctor(doc), _patient(pat), _dateTime(date), _diagnosis(diag) {}

    /**
     * @brief Displays the visit card information.
     *
     * This method prints the details of the hospital visit card, including
     * the patient's name, attending doctor's name, visit date and time,
     * and the diagnosis given.
     */
    void showVisitCard()
    {
        interface.printVisitCard(_patient.getName(), _doctor.getName(), _dateTime, _diagnosis);
    }

    /**
     * @brief Gets the name of the patient associated with the visit card.
     * @return The name of the patient.
     */
    string &getPatientName()
    {
        return _patient.getName();
    }
};
