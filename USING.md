# Инструкции по установке

Для запуска программы через терминал линукс последовательно введите следующие команды:

```bash
gcc main.c -o main
gcc child.c -o child
./main
```

## Тестирование

Для установки библиотеки CUnit введите:

```bash
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```

Для запуска тестов введите следующие команды:

```bash
gcc -o unit_tests unit_tests.c -lcunit
./unit_tests
```
