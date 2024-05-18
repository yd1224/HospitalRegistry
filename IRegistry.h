/**
 * @interface IRegistry
 * @brief Interface for managing hospital appointments, doctors, patients, and visit cards.
 *
 * This interface defines the necessary operations for scheduling and canceling appointments,
 * maintaining lists of doctors and patients, handling hospital visit cards, and other related
 * functionalities in a hospital registry system.
 */
class IRegistry
{
public:
    virtual ~IRegistry() {}

    /**
     * @brief Checks if a patient with the given name exists.
     * @param name Reference to the name of the patient to check.
     * @return True if the patient exists, false otherwise.
     */
    virtual bool patientExists(string &name) = 0;

    /**
     * @brief Retrieves a doctor by name.
     * @param name Reference to the name of the doctor to find.
     * @return A reference to the found Doctor object.
     * @throws std::runtime_error If no doctor with the given name is found.
     */
    virtual Doctor &findDoctorByName(string &name) = 0;

    /**
     * @brief Retrieves a patient by name.
     * @param name Reference to the name of the patient to find.
     * @return A reference to the found Patient object.
     * @throws std::runtime_error If no patient with the given name is found.
     */
    virtual Patient &findPatientByName(string &name) = 0;

    /**
     * @brief Retrieves the list of all doctors.
     * @return A reference to a vector containing all doctors.
     */
    virtual vector<Doctor> &getDoctors() = 0;

    /**
     * @brief Retrieves the list of all patients.
     * @return A reference to a vector containing all patients.
     */
    virtual vector<Patient> &getPatients() = 0;

    /**
     * @brief Retrieves the list of all appointments.
     * @return A reference to a vector containing all appointments.
     */
    virtual vector<Appointment> &getAppointments() = 0;

    /**
     * @brief Schedules default appointments for a given date.
     * @param date Reference to the date string for scheduling appointments.
     * @param defaultTimeIndex Index to start from predefined default times.
     * @param doctorCount Number of doctors to schedule.
     * @param patientCount Number of patients to schedule.
     * @param startIndex Starting index for selecting doctors and patients.
     */

    /**
     * @brief Schedules default appointments for a given date.
     * @param date Reference to the date string for scheduling appointments.
     * @param defaultTimeIndex Index to start from predefined default times.
     * @param doctorCount Number of doctors to schedule.
     * @param patientCount Number of patients to schedule.
     * @param startIndex Starting index for selecting doctors and patients.
     */
    virtual void scheduleDefaulteAppointmentsForDate(string &date, int defaultTimeIndex, int doctorCount, int patientCount, int startIndex) = 0;

    /**
     * @brief Generates default appointments for demonstration purposes.
     */
    virtual void generateDefaultAppointments() = 0;

    /**
     * @brief Cancels a specific appointment.
     * @param dateTime Reference to the date and time of the appointment to cancel.
     * @param patientName Reference to the name of the patient associated with the appointment.
     * @param doctorName Reference to the name of the doctor associated with the appointment.
     */
    virtual void cancelAppointment(string &dateTime, string &patientName, string &doctorName) = 0;

    /**
     * @brief Retrieves visit cards for a specific patient.
     * @param patient Reference to the patient whose visit cards are to be retrieved.
     * @return A vector of HospitalVisitCard objects for the specified patient.
     */
    virtual vector<HospitalVisitCard> getVisitCardsForPatient(Patient &patient) = 0;

    /**
     * @brief Adds a new hospital visit card for a patient.
     * @param doctor Reference to the attending doctor.
     * @param patient Reference to the patient receiving the visit card.
     * @param dateTime Reference to the date and time of the visit.
     * @param diagnosis Reference to the diagnosis given to the patient.
     * @return The newly created HospitalVisitCard object.
     */
    virtual HospitalVisitCard addHospitalVisitCard(Doctor &doctor, Patient &patient, string &dateTime, string &diagnosis) = 0;

    /**
     * @brief Adds a new patient to the registry.
     * @param name Reference to the name of the new patient.
     * @param age Reference to the age of the new patient.
     * @return The newly added Patient object.
     */
    virtual Patient addPatient(string &name, string &age) = 0;

    /**
     * @brief Retrieves available appointment times for a specific doctor on a given date.
     * @param date Reference to the date for which to retrieve available times.
     * @param doctorName Reference to the name of the doctor.
     * @return A vector of pairs representing available times and the corresponding doctor's name.
     */
    virtual vector<pair<string, string>> getAvailableTimesForDoctor(string &date, string &doctorName) = 0;

    /**
     * @brief Schedules an appointment for a specific date and time.
     * @param dateTime Reference to the date and time of the appointment.
     * @param doctor Reference to the doctor who will conduct the appointment.
     * @param patient Reference to the patient who will attend the appointment.
     */
    virtual void scheduleAppointment(string &dateTime, Doctor &doctor, Patient &patient) = 0;

    /**
     * @brief Retrieves the names of doctors available on a specific date.
     * @param date Reference to the date for which to retrieve available doctors.
     * @return A vector containing the names of available doctors.
     */
    virtual vector<string> getAvailableDoctors(string &date) = 0;

    /**
     * @brief Retrieves available appointment times on a given date.
     * @param date Reference to the date for which to retrieve available times.
     * @return A vector of pairs representing available times and the corresponding doctor's name.
     */
    virtual vector<pair<string, string>> getAvailableTimes(string &date) = 0;

    /**
     * @brief Displays all scheduled appointments.
     */
    virtual void showAppointments() = 0;
};