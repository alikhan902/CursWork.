#ifndef BOARDGENERATION_H
#define BOARDGENERATION_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

// ��������� ��� �������� ���������� � �������
class Ship {
public:
    std::string name;
    std::vector<std::pair<int, int>> coordinates;
    int length;
};

// ����� ��� ���� � ������� ���
class BattleshipGame {
private:
    std::set<std::pair<int, int>> shotsFired; // ��������� ��� �������� ��������� ���������
    static const int SIZE = 10; // ������ ����
    static const int NUM_SHIPS[10]; // ���������� ��������

    char field[SIZE][SIZE]; // ���� ��� ����
    std::vector<Ship> ships; // ������ ��� �������� �������� ����������
    std::vector<Ship> playerShips; // ������ ��� �������� �������� ������

    void markSurroundings(int row, int col); // ����� ��� ������� ��������� �������
    bool canPlaceShip(int row, int col, int shipLength, int direction); // ����� ��� �������� ����������� ���������� �������
    void placeShip(int row, int col, int shipLength, int direction); // ����� ��� ���������� �������
    void playerPlaceShip(int row, int col, int shipLength, int direction); // ����� ��� ���������� ������� �������

public:
    BattleshipGame(); // �����������
    void initializeField(); // ����� ��� ������������� ����
    void generateRandomField(); // ����� ��� ��������� ��������� ����
    void printField(); // ����� ��� ������ ����
    void printFieldsSideBySide(const BattleshipGame& left, const BattleshipGame& right) const; // ����� ��� ������ ����� �����

    void generateManualField(); // ����� ��� ������� ����� ����

    void computerShoot(); // ����� ��� �������� ����������

    bool fieldStatus(); // ����� ��� �������� ������� ����

    static int CharToInt(char i); // ����� ��� �������������� ������� � �����

    void shoot(int row, int col); // ����� ��� �������� ������
    void Randomshoot(); // ����� ��� ���������� ��������

    void saveFieldsToFile(const std::string& filename, const BattleshipGame& left, const BattleshipGame& right) const; // ����� ��� ���������� ����� � ����
};

#endif // BOARDGENERATION_H
