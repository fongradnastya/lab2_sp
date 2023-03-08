/*!
 * \file main.h
 * \brief Заголовочный файл с описанием функций
 *
 * Данный файл содержит в себе определения основных
 * функций, используемых в программе.
*/

#ifndef MAIN_2_LAB
#define MAIN_2_LAB

/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
char* GetString(int *len);

/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
int InputNumber(int* val);

/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
void* group(void* group_number);

/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
int getTreasureNumber(int partsNumber);


/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
void hideTreasure(int partsNumber, int minPartArea, int treasureNumber, 
    int groupIds[], int minGroup);

/*!
* \brief Считывает из консоли одно целое число
* \param[in] len Выводимое сообщение
* \return Считанное число
*/
int main();

#endif
