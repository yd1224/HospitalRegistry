/**
 * @class Registry
 * @brief Manages hospital appointments, doctors, patients, and visit cards.
 * @inherit IRegistry
 *
 * This class is responsible for scheduling and canceling appointments,
 * maintaining lists of doctors and patients, and handling hospital visit cards.
 * It provides methods to access and modify these entities and to generate
 * default appointments for demonstration purposes.
 */
class Registry : public IRegistry
{
private:
    vector<HospitalVisitCard> _visitCards;

    vector<Doctor> _doctors = {
        Doctor("John Smith"),
        Doctor("Emily Johnson"),
        Doctor("David Brown"),
        Doctor("Sarah Lee"),
        Doctor("Michael Wilson"),
        Doctor("Alexandra Garcia"),
        Doctor("Matthew Taylor"),
        Doctor("Olivia Martinez")};

    vector<Patient> _patients = {
        Patient("Alice Smith", "23.08.1997"),
        Patient("Bob Johnson", "22.06.2000"),
        Patient("Charlie Brown", "12.01.1998"),
        Patient("Diana Davis", "03.03.2003"),
        Patient("Eva Martinez", "02.08.2008"),
        Patient("Frank Lopez", "14.02.2012"),
        Patient("Grace Lee", "14.08.2012"),
        Patient("Henry Jackson", "22.08.2006")};

    vector<Appointment> _appointments;

    InputOutput interface;

    const int WORK_START_HOUR = 8;
    const int WORK_END_HOUR = 18;
    const int APPOINTMENT_DURATION = 30;

public:
    /**
     * Checks if a patient with the given name exists in the registry.
     * @param name The name of the patient to check for existence.
     * @return True if a patient with the given name exists; otherwise, false.
     */
    bool patientExists(string &name) override
    {
        for (auto &patient : _patients)
        {
            if (patient.getName() == name)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Finds a doctor by their name in the list of doctors.
     * @param name The name of the doctor to find.
     * @return Reference to the doctor object with the specified name.
     * @throws std::runtime_error If the doctor with the given name is not found.
     */
    Doctor &findDoctorByName(string &name) override
    {
        for (Doctor &doctor : _doctors)
        {
            if (doctor.getName() == name)
            {
                return doctor;
            }
        }
        throw runtime_error("Doctor not found.");
    }

    /**
     * Finds a patient by their name in the list of patients.
     * @param name The name of the patient to find.
     * @return Reference to the patient object with the specified name.
     * @throws std::runtime_error If the patient with the given name is not found.
     */
    Patient &findPatientByName(string &name) override
    {
        for (Patient &patient : _patients)
        {
            if (patient.getName() == name)
            {
                return patient;
            }
        }
        throw runtime_error("Patient not found.");
    }

    /**
     * @brief Retrieves the list of doctors.
     * @return A reference to the vector containing all doctors.
     */
    vector<Doctor> &getDoctors() override { return _doctors; }

    /**
     * @brief Retrieves the list of patients.
     * @return A reference to the vector containing all patients.
     */
    vector<Patient> &getPatients() override { return _patients; }

    /**
     * @brief Retrieves the list of appointments.
     * @return A reference to the vector containing all appointments.
     */
    vector<Appointment> &getAppointments() override { return _appointments; }

    /**
     * @brief Schedules default appointments for a given date.
     * @param date The date for which to schedule appointments.
     * @param defaultTimeIndex The starting index for default appointment times.
     * @param doctorCount The number of doctors to schedule appointments for.
     * @param patientCount The number of patients to schedule appointments for.
     * @param startIndex The starting index for doctors and patients.
     */
    void scheduleDefaulteAppointmentsForDate(string &date, int defaultTimeIndex, int doctorCount, int patientCount, int startIndex) override
    {
        vector<std::string> defaultTime = {" 17:00", " 12:30", " 08:30", " 14:00", " 13:30", " 09:00", " 15:00", " 10:00"};

        for (int i = startIndex; i < doctorCount; ++i)
        {
            for (int j = startIndex; j < patientCount; ++j)
            {
                std::string dateTime = date + defaultTime[defaultTimeIndex];
                _doctors[i].addAppointment(dateTime, _patients[j].getName(), _doctors[i].getName());

                _patients[j]
                    .addAppointment(dateTime, _patients[j].getName(), _doctors[i].getName());

                _appointments.push_back(Appointment(dateTime, _doctors[i], _patients[j]));

                defaultTimeIndex = (defaultTimeIndex - 1 + defaultTime.size()) % defaultTime.size();
            }
        }
    }

    /**
     * @brief Generates default appointments for today and tomorrow.
     *
     * This method uses predefined time slots to create appointments for the first half
     * of the doctors and patients for today and for the remaining doctors and patients
     * for tomorrow.
     */
    void generateDefaultAppointments() override
    {
        int defaultTimeIndex = 0;
        string today_date = getTodayDate();
        string tomorrow_date = getTomorrowDate();
        int startIndex = 0;

        scheduleDefaulteAppointmentsForDate(today_date, defaultTimeIndex, _doctors.size() / 2, _patients.size() / 2, startIndex);

        defaultTimeIndex = 7;
        startIndex = 4;

        scheduleDefaulteAppointmentsForDate(tomorrow_date, defaultTimeIndex, _doctors.size(), _patients.size(), startIndex);
    }

    /**
     * Cancels an appointment for a given date and time, patient name, and doctor name.
     * Removes the appointment from the registry and updates the doctor's and patient's records.
     * @param dateTime The date and time of the appointment to cancel.
     * @param patientName The name of the patient associated with the appointment.
     * @param doctorName The name of the doctor associated with the appointment.
     */
    void cancelAppointment(string &dateTime, string &patientName, string &doctorName) override
    {
        _appointments.erase(std::remove_if(_appointments.begin(), _appointments.end(),
                                           [&dateTime, &patientName, &doctorName](Appointment &app)
                                           {
                                               return (app.getDateTime() == dateTime && app.getPatient().getName() == patientName && app.getDoctor().getName() == doctorName);
                                           }),
                            _appointments.end());

        Doctor &doctor = findDoctorByName(doctorName);

        doctor.deleteAppointment(dateTime, patientName, doctorName);

        Patient &patient = findPatientByName(patientName);

        patient.deleteAppointment(dateTime, patientName, doctorName);

        interface.printMsg("Appointment on " + dateTime + " canceled for patient " + patientName);
    }

    /**
     * @brief Retrieves all visit cards for a given patient.
     * @param patient The patient whose visit cards are to be retrieved.
     * @return A vector of HospitalVisitCard objects associated with the patient.
     *
     * This method searches through all visit cards and returns those that belong
     * to the specified patient.
     */
    vector<HospitalVisitCard> getVisitCardsForPatient(Patient &patient) override
    {
        vector<HospitalVisitCard> patientVisitCards;

        for (auto &visitCard : _visitCards)
        {
            if (visitCard.getPatientName() == patient.getName())
            {
                patientVisitCards.push_back(visitCard);
            }
        }

        return patientVisitCards;
    }

    /**
     * @brief Adds a new hospital visit card for a patient.
     * @param doctor The doctor who attended the patient.
     * @param patient The patient who is receiving the visit card.
     * @param dateTime The date and time of the visit.
     * @param diagnosis The diagnosis given to the patient.
     * @return The newly created HospitalVisitCard object.
     *
     * This method creates a new visit card with the provided details and adds it
     * to the list of visit cards.
     */
    HospitalVisitCard addHospitalVisitCard(Doctor &doctor, Patient &patient, string &dateTime, string &diagnosis) override
    {
        HospitalVisitCard visitCard(doctor, patient, dateTime, diagnosis);
        _visitCards.push_back(visitCard);

        return visitCard;
    }

    /**
     * Adds a new patient to the registry with the specified name and age.
     * If a patient with the same name already exists, returns the existing patient.
     * @param name The name of the new patient.
     * @param age The age of the new patient.
     * @return The newly added patient or the existing patient if one with the same name already exists.
     */
    Patient addPatient(string &name, string &age) override
    {
        if (patientExists(name))
        {
            interface.printMsg("Patient " + name + " already exists.");

            return findPatientByName(name);
        }

        Patient patient = Patient(name, age);

        _patients.push_back(patient);

        interface.printMsg("Patient " + name + " added to the registry.");

        return patient;
    }

    /**
     * @brief Retrieves available appointment times for a specific doctor on a given date.
     * @param date The date for which to retrieve available appointment times.
     * @param doctorName The name of the doctor.
     * @return A vector of pairs representing available appointment times and the corresponding doctor's name.
     *
     * This method retrieves all available appointment times for the specified doctor
     * on the provided date and returns them as a vector of pairs, where each pair consists
     * of the appointment time and the doctor's name.
     */
    vector<pair<string, string>> getAvailableTimesForDoctor(string &date, string &doctorName) override
    {
        vector<pair<string, string>> availableTimes;

        vector<pair<string, string>> allAvailableTimes = getAvailableTimes(date);

        for (const auto &timeDoctorPair : allAvailableTimes)
        {
            if (timeDoctorPair.second == doctorName)
            {
                availableTimes.push_back(timeDoctorPair);
            }
        }

        return availableTimes;
    }

    /**
     * Schedules an appointment for the specified date and time with the given doctor and patient.
     * If the doctor is available at the specified date and time, adds the appointment to the registry
     * and updates the doctor's and patient's records.
     * @param dateTime The date and time of the appointment.
     * @param doctor Reference to the doctor who will conduct the appointment.
     * @param patient Reference to the patient who scheduled the appointment.
     */
    void scheduleAppointment(string &dateTime, Doctor &doctor, Patient &patient) override
    {
        if (doctor.isAvailable(dateTime))
        {

            doctor.addAppointment(dateTime, patient.getName(), doctor.getName());

            Patient &registeredPatient = findPatientByName(patient.getName());

            registeredPatient.addAppointment(dateTime, patient.getName(), doctor.getName());

            Appointment newAppointment(dateTime, doctor, registeredPatient);

            _appointments.push_back(newAppointment);

            interface.printMsg("Appointment scheduled for " + dateTime + " with Dr. " + doctor.getName() + " for patient " + registeredPatient.getName());
        }
        else
        {
            interface.printMsg("Sorry, Dr. " + doctor.getName() + " is not available at " + dateTime + ". Please choose another time.");
        }
    }

    /**
     * Retrieves the names of doctors available on the specified date.
     * @param date The date for which available doctors are to be retrieved.
     * @return A vector containing the names of doctors available on the specified date.
     */
    vector<string> getAvailableDoctors(string &date) override
    {
        vector<string> availableDoctors;

        vector<pair<string, string>> availableTimes = getAvailableTimes(date);

        set<string> uniqueDoctors;

        for (auto &timeDoctorPair : availableTimes)
        {
            uniqueDoctors.insert(timeDoctorPair.second);
        }

        for (auto &doctor : _doctors)
        {
            if (uniqueDoctors.find(doctor.getName()) != uniqueDoctors.end())
            {
                availableDoctors.push_back(doctor.getName());
            }
        }

        return availableDoctors;
    }

    /**
     * @brief Retrieves the names of doctors available for appointments on a given date.
     * @param date The date for which to retrieve available doctors.
     * @return A vector containing the names of doctors available for appointments.
     *
     * This method retrieves the names of doctors who have available appointment times
     * on the specified date. It first retrieves all available appointment times for the
     * given date and then extracts the names of doctors from these appointment times.
     */
    vector<pair<string, string>> getAvailableTimes(string &date) override
    {
        vector<pair<string, string>> availableTimes;

        for (Doctor &doctor : _doctors)
        {
            for (int hour = WORK_START_HOUR; hour < WORK_END_HOUR; ++hour)
            {
                for (int minute = 0; minute < 60; minute += APPOINTMENT_DURATION)
                {
                    char buffer[10];

                    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);

                    string time = buffer;

                    string dateTime = date + " " + time;

                    if (doctor.isAvailable(dateTime))
                    {
                        availableTimes.push_back(make_pair(dateTime, doctor.getName()));
                    }
                }
            }
        }

        return availableTimes;
    }

    /**
     * @brief Retrieves an item from a vector by index.
     * @tparam T The type of item in the vector.
     * @param index The index of the item to retrieve.
     * @param items The vector containing the items.
     * @return A reference to the item at the specified index.
     * @throws std::out_of_range If the index is out of bounds.
     *
     * This template method retrieves an item from the specified vector by its index.
     * It checks if the index is within the bounds of the vector and returns a reference
     * to the item at that index. If the index is out of bounds, it throws an std::out_of_range
     * exception with an appropriate error message.
     */
    template <typename T>
    T &getByIndex(int index, vector<T> &items)
    {
        if (index >= 0 && index < items.size())
        {
            return items[index];
        }
        throw std::out_of_range("Invalid index.");
    };

    /**
     * @brief Displays all scheduled appointments.
     *
     * This method displays all scheduled appointments by iterating through the list
     * of appointments and passing relevant information to the interface for display.
     */

    void showAppointments() override
    {
        interface.headerMsg("Appointments");

        int index = 1;
        for (auto &appointment : _appointments)
        {
            interface.showAppointment(index, appointment.getDateTime(), appointment.getDoctor().getName(), appointment.getPatient().getName());

            index++;
        }
    }
};