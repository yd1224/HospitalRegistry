/// @library
/// @{
#include <chrono> //<! Used for std::chrono functionality.
#include <ctime>  //<! Provides std::time_t, std::tm, std::localtime, std::mktime.
#include <cstdio> //<! Provides std::sscanf.
/// @}

using namespace std;

/**
 * @brief Checks if the given date is valid.
 * @param date The date to be checked.
 * @return True if the date is valid, false otherwise.
 *
 * This function checks if the provided date is valid by comparing it to the current date.
 * If the date is in the past, an invalid date message is displayed.
 */
bool isValidDate(string &date)
{
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    time_t now = time(0);
    tm *currentTime = localtime(&now);

    if (year < (currentTime->tm_year + 1900) ||
        (year == (currentTime->tm_year + 1900) && month < (currentTime->tm_mon + 1)) ||
        (year == (currentTime->tm_year + 1900) && month == (currentTime->tm_mon + 1) && day < currentTime->tm_mday))
    {
        InputOutput interface;

        interface.printMsg("Invalid date. Date must be today or in the future.");

        return false;
    }

    return true;
}

/**
 * @brief Gets the current date in the format YYYY-MM-DD.
 * @return A string representing the current date.
 *
 * This function retrieves the current date and formats it as YYYY-MM-DD.
 */
string getTodayDate()
{
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm *local_time = localtime(&now_time_t);
    ostringstream oss;
    oss << put_time(local_time, "%Y-%m-%d");

    return oss.str();
}

/**
 * @brief Gets the date for tomorrow in the format YYYY-MM-DD.
 * @return A string representing the date for tomorrow.
 *
 * This function calculates and retrieves the date for tomorrow and formats it as YYYY-MM-DD.
 */
string getTomorrowDate()
{
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm *local_time = std::localtime(&now_time_t);
    tm tomorrow_time = *local_time;
    tomorrow_time.tm_mday += 1;
    mktime(&tomorrow_time);
    ostringstream oss;
    oss << put_time(&tomorrow_time, "%Y-%m-%d");

    return oss.str();
}