#ifndef FILLING_FIELD_H
#define FILLING_FIELD_H

void createField(char** arr, const int& rows, const int& columns);
void fillFieldWithLivingElements(const std::string& file, char** field);
int calcNumOfLivingAroundCell(char** field, const int& rows, const int& columns, int& row, int& col);
void deathAndNewLifeCell(char** field, char** after_generation_field, const int& rows, const int& columns);
void copyField(char** field, char** after_generation_field, const int& rows, const int& columns);

#endif