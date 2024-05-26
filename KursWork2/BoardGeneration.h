#ifndef BOARDGENERATION_H
#define BOARDGENERATION_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

// Структура для хранения информации о корабле
class Ship {
public:
    std::string name;
    std::vector<std::pair<int, int>> coordinates;
    int length;
};

// Класс для игры в Морской бой
class BattleshipGame {
private:
    std::set<std::pair<int, int>> shotsFired; // Множество для хранения координат выстрелов
    static const int SIZE = 10; // Размер поля
    static const int NUM_SHIPS[10]; // Количество кораблей

    char field[SIZE][SIZE]; // Поле для игры
    std::vector<Ship> ships; // Вектор для хранения кораблей компбютера
    std::vector<Ship> playerShips; // Вектор для хранения кораблей игрока

    void markSurroundings(int row, int col); // Метод для отметки окружения корабля
    bool canPlaceShip(int row, int col, int shipLength, int direction); // Метод для проверки возможности размещения корабля
    void placeShip(int row, int col, int shipLength, int direction); // Метод для размещения корабля
    void playerPlaceShip(int row, int col, int shipLength, int direction); // Метод для размещения корабля игроком

public:
    BattleshipGame(); // Конструктор
    void initializeField(); // Метод для инициализации поля
    void generateRandomField(); // Метод для случайной генерации поля
    void printField(); // Метод для вывода поля
    void printFieldsSideBySide(const BattleshipGame& left, const BattleshipGame& right) const; // Метод для вывода полей рядом

    void generateManualField(); // Метод для ручного ввода поля

    void computerShoot(); // Метод для выстрела компьютера

    bool fieldStatus(); // Метод для проверки статуса поля

    static int CharToInt(char i); // Метод для преобразования символа в число

    void shoot(int row, int col); // Метод для выстрела игрока
    void Randomshoot(); // Метод для случайного выстрела

    void saveFieldsToFile(const std::string& filename, const BattleshipGame& left, const BattleshipGame& right) const; // Метод для сохранения полей в файл
};

#endif // BOARDGENERATION_H
