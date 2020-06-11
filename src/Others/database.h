#ifndef SCZR_PROJECT_DATABASE_H
#define SCZR_PROJECT_DATABASE_H

#include <sstream>
#include <utility>

struct Date {
    int year;
    short month;
    short day;

    /**
     * ctor
     * @param year
     * @param month
     * @param day
     */
    Date(int year, short month, short day) : year(year), month(month), day(day) {}

    /**
    * @return - appended stream with date format is like in SQLite e.x. 2020-06-04
    */
    friend std::ostream &operator<<(std::ostream &os, const Date &dt);
};

struct DbRow {
    std::string country;
    long infected_number;
    Date date;

    DbRow(std::string country, long infected_number, Date date) : country(std::move(country)),
                                                                  infected_number(infected_number),
                                                                  date(date) {}

    /**
     * @return appended stream with a row like in SQLite. e.x. output: 'China', 1439323776, '2020-06-02'
     */
    friend std::ostream &operator<<(std::ostream &os, const DbRow &row);
};

/**
 * Generate a database in the catalog with the executable. The database is made by the convention and has a random
 * numer of infected people by countries.
 */
void generateRandomlyFilledTable();

std::string generatestring();

void getData();

#endif //SCZR_PROJECT_DATABASE_H
