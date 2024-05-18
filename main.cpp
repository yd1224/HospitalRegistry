/// @library
/// @{
#include <iostream>  //<! Used for std::cout, std::endl, std::cin.
#include <string>    //<! Provides std::string class and related functions.
#include <vector>    //<! Provides std::vector container for dynamic arrays.
#include <utility>   //<! Provides utility std::pair.
#include <iomanip>   //<! Provides std::put_time.
#include <sstream>   //<! Provides std::ostringstream for string stream operations.
#include <set>       //<! Provides std::set container for storing unique elements in a specific order.
#include <algorithm> //<! Provides std::remove_if.
/// @}

using std::pair;
using std::string;
using std::vector;

#include "InputOutput.h"
#include "AbstractPerson.h"
#include "helpers.h"
#include "Doctor.h"
#include "Patient.h"
#include "HospitalVisitCard.h"
#include "Appointment.h"
#include "IRegistry.h"
#include "Registry.h"
#include "Menu.h"

/**
 * @fn int main()
 * @brief The main entry point for the application.
 *
 * Initializes the registry, user interface, and main menu.
 * Starts the application by invoking the start method on the menu.
 * @return int Returns 0 upon successful execution.
 */
int main()
{
    Registry registry;

    InputOutput interface;

    Menu menu(registry, interface);

    menu.start();

    return 0;
}