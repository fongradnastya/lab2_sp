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
* \brief Считывает из консоли строку
* \param[in] len Длина считываемых символов
* \return Считанная строка
*/
char* GetString(int *len);

/*!
* \brief Считывает из консоли одно целое число
* \param[out] val Считанное значение
* \return Код успешности выполнения функции
*/
int InputNumber(int* val);

/*!
* \brief Функция, которую будет выполнять процесс
* \param[in] group_number Номер текущего потока
* \return Пустой указатель
*/
void* group(void* group_number);

/*!
* \brief Считывает от пользователя место расположения клада
* \param[in] partsNumber Количество частей, на которое поделен остров
* \return Считанное число
*/
int getTreasureNumber(int partsNumber);


/*!
* \brief Прячет сокровище в одном из мест острова
* \param[in] partsNumber Количество частей, на которое поделен остров
* \param[in] minPartArea Площадь части острова
* \param[in] treasureNumber Номер части, в которой спрятано сокровище
* \param[in] groupIds[] Массив номеров групп
* \param[in] minGroup Минимальный размер группы
*/
void hideTreasure(int partsNumber, int minPartArea, int c, 
    int groupIds[], int minGroup);

/*!
* \brief Запускает основную логику программы
* \return Код завершения программы
*/
int main();

#endif
