#ifndef CHECKING_FIELDS_H
#define CHECKING_FIELDS_H

bool isLifeStagnated(char** field, char** newField, const int& rows, const int& columns, std::string& result);
bool isNumberOfLiving(char** field, const int& rows, const int& columns, int& countLiving, std::string& result);

#endif