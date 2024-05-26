#include "BoardGeneration.h"
#include <cstdlib>  // ��� ������� rand() � srand()
#include <ctime>    // ��� ������� time()
#include <fstream>  // ��� ������ � �������
#include <iomanip>  // ��� ���������������� ������

using namespace std;

// ������������� ������� ���������� ��������
const int BattleshipGame::NUM_SHIPS[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

// ����������� ������ BattleshipGame
BattleshipGame::BattleshipGame() {
    srand(time(nullptr)); // ������������� ���������� ��������� �����
    initializeField();    // ������������� �������� ����
}

// ����� ��� ������������� ����
void BattleshipGame::initializeField() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            field[i][j] = '.'; // ���������� ���� ��������� '.'
        }
    }
}

// ����� ��� ������� ��������� �������
void BattleshipGame::markSurroundings(int row, int col) {
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && field[i][j] == '.') {
                field[i][j] = '-'; // ������� ������ ������ ������� ��������� '-'
            }
        }
    }
}

// ����� ��� �������� ����������� ���������� �������
bool BattleshipGame::canPlaceShip(int row, int col, int shipLength, int direction) {
    if (direction == 0) { // �������������� ����������
        if (col + shipLength > SIZE) {
            return false;
        }
        else {
            for (int j = col; j < col + shipLength; ++j) {
                if (field[row][j] != '.') {
                    return false;
                }
            }
        }
    }
    else { // ������������ ����������
        if (row + shipLength > SIZE) {
            return false;
        }
        else {
            for (int i = row; i < row + shipLength; ++i) {
                if (field[i][col] != '.') {
                    return false;
                }
            }
        }
    }
    return true;
}

// ����� ��� ���������� �������
void BattleshipGame::placeShip(int row, int col, int shipLength, int direction) {
    Ship newShip;
    newShip.length = shipLength;
    newShip.coordinates.reserve(shipLength);

    for (int k = 0; k < shipLength; ++k) {
        if (direction == 0) { // �������������� ����������
            field[row][col + k] = 'A' + shipLength; // ����������� �������
            newShip.coordinates.push_back({ row, col + k }); // ���������� ���������
            markSurroundings(row, col + k); // ������� ���������
        }
        else { // ������������ ����������
            field[row + k][col] = 'A' + shipLength; // ����������� �������
            newShip.coordinates.push_back({ row + k, col }); // ���������� ���������
            markSurroundings(row + k, col); // ������� ���������
        }
    }

    // ���� ������� ���������� ��� 
    newShip.name = "Ship" + to_string(ships.size() + 1);
    ships.push_back(newShip); // ��������� ������� � ������
}

// ����� ��� ������� ���������� �������
void BattleshipGame::playerPlaceShip(int row, int col, int shipLength, int direction) {
    Ship newShip;
    newShip.length = shipLength;
    newShip.coordinates.reserve(shipLength);

    for (int k = 0; k < shipLength; ++k) {
        if (direction == 0) { // �������������� ����������
            field[row][col + k] = 'A' + shipLength; // ����������� �������
            newShip.coordinates.push_back({ row, col + k }); // ���������� ���������
            markSurroundings(row, col + k); // ������� ���������
        }
        else { // ������������ ����������
            field[row + k][col] = 'A' + shipLength; // ����������� �������
            newShip.coordinates.push_back({ row + k, col }); // ���������� ���������
            markSurroundings(row + k, col); // ������� ���������
        }
    }

    // ���� ������� ���������� ��� 
    newShip.name = "Ship" + to_string(ships.size() + 1);
    playerShips.push_back(newShip); // ��������� ������� � ������
}

// ����� ��� ��������� ��������� ����
void BattleshipGame::generateRandomField() {
    for (int shipLength : NUM_SHIPS) {
        bool placed = false;
        while (!placed) {
            int direction = rand() % 2;
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            if (canPlaceShip(row, col, shipLength, direction)) {
                placeShip(row, col, shipLength, direction);
                placed = true;
            }
        }
    }
}

// ����� ��� ������� ����� ����
void BattleshipGame::generateManualField() {
    int x, z, i = 0;
    char y;

    for (int shipLength : NUM_SHIPS) {
        system("cls");
        printField();
        if (i == 0) {
            cout << "������� ����� ������������� �� �������� � ��������\n";
            cout << "��� ����� ����� ������� ����������, ��� 0 - �����������, � 1 - ���������, � ��������� ����������:\n";
            i++;
        }
        bool placed = false;
        while (!placed) {
            cout << "����������: ";
            cin >> z;
            cout << "���: ";
            cin >> x;
            cout << "�������: ";
            cin >> y;
            int direction = z % 2;
            int row = x % SIZE;
            int col = BattleshipGame::CharToInt(y);
            if (canPlaceShip(row, col, shipLength, direction)) {
                playerPlaceShip(row, col, shipLength, direction); // ���������� ����� ��� ���������� ������� �������
                placed = true;
                printField();
            }
        }
    }
}

// ����� ��� ������ ����
void BattleshipGame::printField() {
    // �������� ����� ��� ��������
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // ����������� ������ � �����
        cout << colLabel << " ";
    }
    cout << endl;

    // �������� ����
    for (int i = 0; i < SIZE; ++i) {
        // �������� ����� ��� �����
        cout << i << " "; // ��������� ����� ���������� � 0
        for (int j = 0; j < SIZE; ++j) {
            char cell = field[i][j];
            cout << cell << " ";
        }
        cout << endl;
    }
}

// ����� ��� �������� ������
void BattleshipGame::shoot(int row, int col) {
    if (field[row][col] == 'E' || field[row][col] == 'D' || field[row][col] == 'C' || field[row][col] == 'B') {
        field[row][col] = 'Y'; // ���������
    }
    else if (field[row][col] == '.' || field[row][col] == '-') {
        field[row][col] = 'M'; // ����
    }

    // ��������� ������ ������� � ������� �� �������������
    for (Ship& ship : ships) {
        bool allHit = true;
        for (const auto& coord : ship.coordinates) {
            if (field[coord.first][coord.second] != 'Y') {
                allHit = false; // ���� ���� �� ���� ������ ������� �� �������� ��� ���������, �� �� ��������
                break;
            }
        }
        if (allHit) {
            // ��� ������ ������� �������� ��� ���������, �� ��������, �������� ��� ��� 'X'
            for (const auto& coord : ship.coordinates) {
                field[coord.first][coord.second] = 'X';
            }
        }
    }
}

// ����� ��� ���������� ��������
void BattleshipGame::Randomshoot() {
    int n, m;
    while (true) {
        n = rand() % SIZE;
        m = rand() % SIZE;
        if (field[n][m] != 'Y' && field[n][m] != 'M' && field[n][m] != 'X') {
            shoot(n, m);
            break;
        }
    }
}

// ����� ��� �������� ���������� � �������������� ������� ���������
void BattleshipGame::computerShoot() {
    static int lastRow = -1;
    static int lastCol = -1;
    static int direction = -1;
    static bool hitLastTurn = false;

    if (lastRow == -1 && lastCol == -1) {
        // ��������� �������, ���� ��� ������ ������� ����������
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        shoot(row, col);
        lastRow = row;
        lastCol = col;
        return;
    }

    // ���� ��������� ������� ����� � �������
    if (field[lastRow][lastCol] == 'Y') {
        // ���� ������� �� �������, ���������� ����� ������ ���������� ���������
        if (direction == -1 || !hitLastTurn) {
            // �������� �������� ��������� ����������� ��� �����
            direction = rand() % 4;
        }

        int row = lastRow;
        int col = lastCol;

        // ���������� �������� � ������� �����������
        while (true) {
            // �������� ��������� ������ ��� ����� � ����������� �� �����������
            switch (direction) {
            case 0: // �����
                row--;
                break;
            case 1: // ������
                col++;
                break;
            case 2: // ����
                row++;
                break;
            case 3: // �����
                col--;
                break;
            }

            // ���������, �� ����� �� �� ������� ����
            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || field[row][col] == 'M') {
                // ���� ����� �� ������� ���� ��� ��� �������� � ������ ������, ������ �����������
                direction = (direction + 1) % 4;
                row = lastRow;
                col = lastCol;
                hitLastTurn = false;
                return; // ������� �� ������, ����� ��������� ������� ��� ���������
            }

            // ������� �� ��������� ������
            shoot(row, col);

            // ���� ������, ��������� ��������� ���������� � ��������� �����
            if (field[row][col] == 'Y') {
                lastRow = row;
                lastCol = col;
                hitLastTurn = true;
                return; // ������� �� ������, ����� ��������� ������� ��� � ���� �� �����������
            }
            else {
                hitLastTurn = false;
                return; // ������� �� ������, ����� ��������� ������� ��� � ������ �����������
            }
        }
    }

    // ���� ������� ������� ��� ��������� �� ���������, ������ ��������� �������
    int row = rand() % SIZE;
    int col = rand() % SIZE;
    while (field[row][col] == 'M') { // ���������, �� �������� �� ��� � ������ ������
        row = rand() % SIZE;
        col = rand() % SIZE;
    }
    shoot(row, col);
    lastRow = row;
    lastCol = col;
}

// ����� ��� ������ ���� ����� ��� � ���
void BattleshipGame::printFieldsSideBySide(const BattleshipGame& left, const BattleshipGame& right) const {
    // �������� ����� ��� �������� ������� ����
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // ����������� ������ � �����
        cout << colLabel << " ";
    }

    // ����������� ����� ������
    cout << "        ";

    // �������� ����� ��� �������� ������� ����
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // ����������� ������ � �����
        cout << colLabel << " ";
    }
    cout << endl;

    // �������� ����
    for (int i = 0; i < SIZE; ++i) {
        // �������� ����� ��� ������ ������� ����
        cout << i << " ";

        // �������� �������� ������� ����
        for (int j = 0; j < SIZE; ++j) {
            char cell = left.field[i][j];
            cout << cell << " ";
        }

        // ����������� ����� ������
        cout << "      ";

        // �������� ����� ��� ������ ������� ����
        cout << i << " ";

        // �������� �������� ������� ����
        for (int j = 0; j < SIZE; ++j) {
            char cell = right.field[i][j];
            // ���� ��� ��������� ���� � ������ �� "Y", "X", ��� "M", ������� "."
            if (cell != 'Y' && cell != 'X' && cell != 'M') {
                cout << "." << " ";
            }
            else {
                cout << cell << " ";
            }
        }
        cout << endl;
    }
}

// ����� ��� �������� ������� ���� (���� �� ������������� �������)
bool BattleshipGame::fieldStatus() {
    int k = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] == 'X') {
                k++;
            }
        }
    }
    return k != 20;
}

// ����� ��� �������������� ������� ������� � ������
int BattleshipGame::CharToInt(char i) {
    switch (i) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;
    case 'I': return 8;
    case 'J': return 9;
    default: return -1;
    }
}

void BattleshipGame::saveFieldsToFile(const std::string& filename, const BattleshipGame& left, const BattleshipGame& right) const {
    std::ofstream outFile(filename); // �������� ����� ��� ������

    // �������� ����� ��� �������� ������� ����
    outFile << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // ����������� ������ � �����
        outFile << colLabel << " ";
    }

    // ����������� ����� ������
    outFile << "        ";

    // �������� ����� ��� �������� ������� ����
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // ����������� ������ � �����
        outFile << colLabel << " ";
    }
    outFile << std::endl;

    // �������� ����
    for (int i = 0; i < SIZE; ++i) {
        // �������� ����� ��� ������ ������� ����
        outFile << i << " ";

        // �������� �������� ������� ����
        for (int j = 0; j < SIZE; ++j) {
            char cell = left.field[i][j];
            outFile << cell << " ";
        }

        // ����������� ����� ������
        outFile << "      ";

        // �������� ����� ��� ������ ������� ����
        outFile << i << " ";

        // �������� �������� ������� ����
        for (int j = 0; j < SIZE; ++j) {
            char cell = right.field[i][j];
            // ���� ��� ��������� ���� � ������ �� "Y", "X", ��� "M", ������� "."
            if (cell != 'Y' && cell != 'X' && cell != 'M') {
                outFile << "." << " ";
            }
            else {
                outFile << cell << " ";
            }
        }
        outFile << std::endl;
    }

    outFile.close(); // �������� �����
}
