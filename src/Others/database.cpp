#include <fstream>
#include <sqlite3.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include "database.h"
#include "utilities.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>




const char *kDbFileName = "testDb.db";
std::string max_data;
// Country and population
const std::string kDbData = "China,1439323776\n"
                            "India,1380004385\n"
                            "United States,331002651\n"
                            "Indonesia,273523615\n"
                            "Pakistan,220892340\n"
                            "Brazil,212559417\n"
                            "Nigeria,206139589\n"
                            "Bangladesh,164689383\n"
                            "Russia,145934462\n"
                            "Mexico,128932753\n"
                            "Japan,126476461\n"
                            "Ethiopia,114963588\n"
                            "Philippines,109581078\n"
                            "Egypt,102334404\n"
                            "Vietnam,97338579\n"
                            "DR Congo,89561403\n"
                            "Turkey,84339067\n"
                            "Iran,83992949\n"
                            "Germany,83783942\n"
                            "Thailand,69799978\n"
                            "United Kingdom,67886011\n"
                            "France,65273511\n"
                            "Italy,60461826\n"
                            "Tanzania,59734218\n"
                            "South Africa,59308690\n"
                            "Myanmar,54409800\n"
                            "Kenya,53771296\n"
                            "South Korea,51269185\n"
                            "Colombia,50882891\n"
                            "Spain,46754778";

std::ostream &operator<<(std::ostream &os, const DbRow &row) {
    os << "'" << row.country << "', " << row.infected_number << ", '" << row.date << "'";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Date &dt) {
    os << dt.year << "-";
    if (dt.month < 10) {
        os << "0";
    }
    os << dt.month << "-";
    if (dt.day < 10) {
        os << "0";
    }
    return os << dt.day;
}


void execStatement(sqlite3 *openedDb, const char *statement) {
    char *zErrMsg = nullptr;
    int rc;
    rc = sqlite3_exec(openedDb, statement, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        exitWithError(sqlite3_errmsg(openedDb));
    }
}

/**
 * @return Opened database with the name provided in kDbFileName
 */
sqlite3 * openedDb() {
    sqlite3 *outDb;
    int rc = sqlite3_open(kDbFileName, &outDb);
    if (rc != SQLITE_OK) {
        exitWithError("Unable to open the database");
    }
    return outDb;
}



/**
 * Insert database rows with a random number of infected people
 * @param openedDb - Opened database
 */
void insertRandomData(sqlite3 *openedDb) {
    std::stringstream in_stream(kDbData);
    std::stringstream out_stream;
    std::string line;
    out_stream << "INSERT INTO \"COVID-statistic\" (Country, InfectedNumer, Date)\n"
                  "VALUES ";
    // First line
    std::getline(in_stream, line);
    unsigned long commaPos = line.find(',');
    std::string country = line.substr(0, commaPos);
    long default_infected_number = std::stol(line.substr(commaPos + 1)); // start after comma position
    out_stream << "(" << DbRow(country, default_infected_number, Date(2020, 6, 4)) << ")";
    // Other lines
    while (std::getline(in_stream, line)) {
        commaPos = line.find(',');
        country = line.substr(0, commaPos);
        default_infected_number = std::stol(line.substr(commaPos + 1)); // start after comma position
        out_stream << ",\n(" << DbRow(country, default_infected_number, Date(2020, 6, 4)) << ")";
    }
    out_stream << ";";
    execStatement(openedDb, out_stream.str().c_str());
}

void clearTable(sqlite3 *openedDb) {
    char *zErrMsg = nullptr;
    const char *statement = "DELETE FROM \"COVID-statistic\";";
    int rc = sqlite3_exec(openedDb, statement, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        exitWithError(sqlite3_errmsg(openedDb));
    }
}

void createTableIfNotExists(sqlite3 *openedDb) {
    char *zErrMsg = nullptr;
    int rc;

    const char *statement = "create table if not exists \"COVID-statistic\"\n"
                             "(\n"
                             "    Country VARCHAR(30),\n"
                             "    InfectedNumer INTEGER,\n"
                             "    Date DATE\n"
                             ");";

    rc = sqlite3_exec(openedDb, statement, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        exitWithError(sqlite3_errmsg(openedDb));
    }}

void generateRandomlyFilledTable() {
    sqlite3 *openedDatabase = openedDb();
    createTableIfNotExists(openedDatabase);
    clearTable(openedDatabase);
    insertRandomData(openedDatabase);
    sqlite3_close(openedDatabase);
}

int callback2(void *NotUsed, int argc, char **argv, char **azColName){

        max_data=argv[0];

    return 0;
}
std::string generatestring()
{
    std::stringstream in_stream(kDbData);
    std::stringstream out_stream;
    std::string line;
    std::string country;
    std::string out_string;
    long default_infected_number;
    srand( time( NULL ) );
    unsigned long commaPos;
    char *zErrMsg =0;
    sqlite3 *db;
    int rc = sqlite3_open("testDb.db", &db);
    const char *sql_select = "SELECT ifnull(date(max(Date) ,'+1 day'), date('now'))from 'COVID-statistic';";
    rc=sqlite3_exec(db, sql_select, callback2, 0, &zErrMsg);
    while (std::getline(in_stream, line)) {
        commaPos = line.find(',');
        country = line.substr(0, commaPos);
        default_infected_number = std::stol(line.substr(commaPos + 1)); // start after comma position
        //out_string=(out_string+country + ", "+ std::to_string(rand()%1000) + ", "+ "2020.01.01\n");
       out_string=(out_string+country + ", "+ std::to_string(rand()%1000) + ", "+ max_data+'\n');

    }
    sqlite3_close(db);
 return out_string;

}

void insertData(sqlite3 *openedDb) {
    std::string database_string;
    std::stringstream in_stream;
    in_stream.str(generatestring());
    std::stringstream out_stream;
    std::string line;
    out_stream << "INSERT INTO \"COVID-statistic\" (Country, InfectedNumer, Date)\n"
                  "VALUES ";
    // First line
    std::getline(in_stream, line);
    int year, month, day;
    year = std::stoi(max_data.substr(0, 4));
    month = std::stoi(max_data.substr(5, 2));
    day = std::stoi(max_data.substr(8, 2));
    unsigned long commaPos = line.find(',');
    std::string country = line.substr(0, commaPos);
    long default_infected_number = std::stol(line.substr(commaPos + 1)); // start after comma position
    //out_stream << "(" << DbRow(country, default_infected_number, Date(2021, 6, 4)) << ")";
    out_stream << "(" << DbRow(country, default_infected_number, Date(year, month, day)) << ")";
    // Other lines

    while (std::getline(in_stream, line)) {
        commaPos = line.find(',');
        country = line.substr(0, commaPos);
        default_infected_number = std::stol(line.substr(commaPos + 1)); // start after comma position
        out_stream << ",\n(" << DbRow(country, default_infected_number, Date(year, month, day))<< ")";
    }
    out_stream << ";";
    execStatement(openedDb, out_stream.str().c_str());
}


void getData() {
    sqlite3 *openedDatabase = openedDb();
    createTableIfNotExists(openedDatabase);
   // clearTable(openedDatabase);
    insertData(openedDatabase);
    sqlite3_close(openedDatabase);
}



int callback(void *NotUsed, int argc, char **argv, char **azColName){
    std::ofstream file;
    file.open("results.txt", std::ios::app);
  //  file << "REPORT"<<'\n'<<"Country"<<'\t'<<'\t'<<"Infected_Numer"<<'\t'<<'\t'<<"Date"<<'\n';
    for(int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
        file  << argv[i] <<'\t'<<'\t'<<'\t';
    }
    file <<std::endl;
    std::cout << std::endl;
    file.close();
    return 0;
}




void create_results()
{

    sqlite3 *db;
    int rc = sqlite3_open("testDb.db", &db);
    std::string sql_select = "SELECT country, InfectedNumer, Date from 'COVID-statistic' where rowid=1 order by Date desc, InfectedNumer desc;";
    char *zErrMsg =0;
    rc = sqlite3_exec(db, sql_select.c_str(),callback, 0, &zErrMsg );
    sqlite3_close(db);

}







