/**
 * @class Menu
 * @brief Manages the user interface for the hospital management system.
 *
 * This class provides various menus for scheduling and canceling appointments,
 * adding visit cards, and retrieving visit cards for patients. It also handles
 * different user roles such as patients and registrators.
 */
class Menu
{
private:
    Registry &registry;
    InputOutput &interface;

    /**
     * @enum UserChoice
     * @brief Enumerates the possible choices a user can make in the registrator menu.
     */
    enum UserChoice
    {
        SCHEDULE_APPOINTMENT = 1, ///< Option to schedule a new appointment.
        CANCEL_APPOINTMENT,       ///< Option to cancel an existing appointment.
        ADD_VISIT_CARD,           ///< Option to add a new visit card.
        GET_VISIT_CARD,           ///< Option to retrieve a visit card.
        DOCTOR_SCHEDULE,          ///< Option to check a doctor's schedule.
        RETURN_TO_MAIN_MENU       ///< Option to return to the main menu.
    };

public:
    /**
     * @brief Constructs a new Menu object.
     * @param reg Reference to the Registry object.
     * @param interface Reference to the InputOutput object.
     */
    Menu(Registry &reg, InputOutput &interface) : registry(reg), interface(interface) {}

    /**
     * Retrieves an appointment selected by the user from the registry.
     * Displays the list of appointments to the user and prompts for a selection.
     * @return The appointment chosen by the user.
     */
    Appointment getAppointmentFromUser()
    {
        registry.showAppointments();

        vector<Appointment> appointments = registry.getAppointments();

        int choice = interface.getValidChoice(appointments);

        return registry.getByIndex(choice - 1, appointments);
    }

    /**
     * @brief Displays the menu for canceling an appointment.
     */
    void cancelAppointmentMenu()
    {
        auto appointment = getAppointmentFromUser();

        string patientName = appointment.getPatient().getName();
        string doctorName = appointment.getDoctor().getName();
        string dateTime = appointment.getDateTime();

        Doctor doctor = registry.findDoctorByName(doctorName);

        registry.cancelAppointment(dateTime, patientName, doctorName);
    }

    /**
     * @brief Displays the menu for canceling an appointment for a specific patient.
     * @param patient Pointer to the Patient object.
     */
    void cancelAppointmentMenu(Patient *patient)
    {
        int choice;

        Patient registratedPatient = registry.findPatientByName(patient->getName());

        registratedPatient.printDetails();

        if (registratedPatient.getAppointments().size() == 0)
            return;

        cout << endl;
        choice = interface.getUserChoice();

        vector<pair<string, pair<string, string>>> appoinments = registratedPatient.getAppointments();

        string doctorName = appoinments[choice - 1].second.second;

        string dateTime = appoinments[choice - 1].first;

        registry.cancelAppointment(dateTime, patient->getName(), doctorName);
    }

    /**
     * @brief Prompts the user for a valid date input.
     * @return string A valid date string in the format YYYY-MM-DD.
     */
    string getValidDateFromUser()
    {
        string date;
        do
        {
            date = interface.getInfo("Enter date (YYYY-MM-DD): ");
        } while (!isValidDate(date));
        return date;
    }

    /**
     * @brief Prompts the user to select a doctor from a list.
     * @return Doctor* Pointer to the selected doctor object.
     * @return nullptr If the user cancels the selection.
     */
    Doctor *selectDoctorFromList()
    {
        Doctor *doctor = nullptr;
        int choice;

        do
        {
            interface.headerMsg("List of Doctors");
            interface.showPeople(registry.getDoctors());

            choice = interface.getUserChoice();
            if (choice < 1 || choice > registry.getDoctors().size())
            {
                cout << endl;
                interface.printMsg("\n Invalid choice. Please try again.");
                continue;
            }

            doctor = &registry.getByIndex(choice - 1, registry.getDoctors());
            break;
        } while (true);

        return doctor;
    }

    /**
     * @brief Displays the menu for scheduling an appointment for a specific patient.
     * @param patient Pointer to the Patient object.
     */
    void scheduleAppointmentMenu(Patient *patient)
    {
        Doctor *doctor = selectDoctorFromList();
        if (doctor == nullptr)
        {
            return;
        }

        string date = getValidDateFromUser();

        vector<pair<string, string>> availableTimes = registry.getAvailableTimesForDoctor(date, doctor->getName());

        displayAvailableTimes(availableTimes, doctor->getName(), date);

        int choice = interface.getValidChoice(availableTimes);

        if (choice == -1)
            return;

        string selectedTime = availableTimes[choice - 1].first;

        registry.scheduleAppointment(selectedTime, *doctor, *patient);
    }

    /**
     * @brief Displays the appointments for a specific patient.
     * @param patient Pointer to the Patient object.
     */
    void showAppointmentsForPatient(Patient *patient)
    {
        Patient registeredPatient = registry.findPatientByName(patient->getName());

        registeredPatient.printDetails();
    }

    /**
     * @brief Displays available appointment times for a specific doctor and date.
     * @param availableTimes A vector of available times and corresponding doctor names.
     * @param doctorName The name of the doctor.
     * @param date The date for which to display available times.
     */
    void
    displayAvailableTimes(vector<pair<string, string>> &availableTimes, string &doctorName, string &date)
    {
        interface.headerMsg("Available Times for Dr. " + doctorName + " on " + date + ": ");

        interface.showAvailableTimes(availableTimes);
    }

    /**
     * @brief Registers a new patient and adds them to the registry.
     * @return Patient The newly registered patient object.
     */
    Patient registerPatient()
    {
        interface.headerMsg("Registration form");

        string name = interface.getInfo("Enter your name: ");

        string surname = interface.getInfo("Enter your surname: ");

        string patientName = name + " " + surname;

        string dateOfBirth = interface.getInfo("Enter your date of birth (DD.MM.YYYY): ");

        Patient patient = registry.addPatient(patientName, dateOfBirth);

        return patient;
    }

    /**
     * @brief Displays the menu for adding a visit card for an appointment.
     */
    void addVisitCardMenu()
    {
        Appointment *appointment = nullptr;

        registry.showAppointments();

        vector<Appointment> appointments = registry.getAppointments();

        int choice = interface.getValidChoice(appointments);

        appointment = &registry.getByIndex(choice - 1, appointments);

        Patient patient = appointment->getPatient();
        Doctor doctor = appointment->getDoctor();
        string dateTime = appointment->getDateTime();

        string diagnosis = interface.getInfo("Enter diagnosis: ");

        cout << endl;

        registry.addHospitalVisitCard(doctor, patient, dateTime, diagnosis);

        interface.printMsg("Hospital visit card is added for patient " + patient.getName());
    }

    /**
     * @brief Prompts the user to select a patient from a list.
     * @return Patient* Pointer to the selected patient object.
     */
    Patient *choosePatient()
    {
        Patient *patient = nullptr;

        interface.headerMsg("List of registered patients");

        interface.showPeople(registry.getPatients());

        int choice = interface.getValidChoice(registry.getPatients());

        patient = &registry.getByIndex(choice - 1, registry.getPatients());

        return patient;
    }

    /**
     * @brief Displays the menu for retrieving visit cards for a specific patient.
     */
    void getVisitCardMenu()
    {
        Patient *patient = choosePatient();

        vector<HospitalVisitCard> patientVisitCards = registry.getVisitCardsForPatient(*patient);

        interface.headerMsg("Hospital Visit Cards for " + patient->getName() + ":");

        if (patientVisitCards.size() == 0)
        {
            interface.printMsg("No visit cards found for this patient.");

            return;
        }

        for (auto &visitCard : patientVisitCards)
        {
            visitCard.showVisitCard();
        }
    }

    /**
     * @brief Displays the schedule for a specific doctor.
     */
    void getDoctorSchedule()
    {
        Doctor *doctor = selectDoctorFromList();

        doctor->printDetails();
    }

    /**
     * @brief Handles the menu and actions for a registrator user.
     */
    void registratorRoute()
    {
        UserChoice choice;

        do
        {
            interface.optionMenuForRegistrator();
            choice = static_cast<UserChoice>(interface.getUserChoice());

            switch (choice)
            {
            case SCHEDULE_APPOINTMENT:
                scheduleAppointmentMenu(choosePatient());
                break;
            case CANCEL_APPOINTMENT:
                cancelAppointmentMenu();
                break;
            case ADD_VISIT_CARD:
                addVisitCardMenu();
                break;
            case GET_VISIT_CARD:
                getVisitCardMenu();
                break;
            case DOCTOR_SCHEDULE:
                getDoctorSchedule();
                break;
            case RETURN_TO_MAIN_MENU:
                interface.printMsg("Returning to main menu...");
                return;
            default:
                interface.printMsg("\n Invalid choice. Please try again.");
            }
        } while (choice != RETURN_TO_MAIN_MENU);
    }

    /**
     * @brief Handles the menu and actions for a patient user.
     */
    void patientRoute()
    {
        Patient patient = registerPatient();

        int choice;

        do
        {
            interface.optionMenuForPatient();
            choice = interface.getUserChoice();

            switch (choice)
            {
            case 1:
                scheduleAppointmentMenu(&patient);
                break;
            case 2:
                cancelAppointmentMenu(&patient);
                break;
            case 3:
                showAppointmentsForPatient(&patient);
                break;
            case 4:
                interface.printMsg("Returning to main menu...");
                return;
            default:
                interface.printMsg("\n Invalid choice. Please try again.");
            }
        } while (choice != 4);
        }

    /**
     * @brief Starts the main menu and handles user interaction.
     */
    void start()
    {
        registry.generateDefaultAppointments();
        int choice;

        do
        {
            interface.headerMsg("===== Appointment Scheduling System =====");
            interface.optionMenu();

            choice = interface.getUserChoice();

            switch (choice)
            {
            case 1:
                patientRoute();
                break;
            case 2:
                registratorRoute();
                break;
            case 3:
                return;
            default:
                cout << endl;
                interface.printMsg("\n Invalid choice. Please try again.");
            }
        } while (choice != 3);
    }
};