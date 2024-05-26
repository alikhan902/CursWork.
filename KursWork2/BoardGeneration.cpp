#include "BoardGeneration.h"
#include <cstdlib>  // Для функций rand() и srand()
#include <ctime>    // Для функции time()
#include <fstream>  // Для работы с файлами
#include <iomanip>  // Для форматированного вывода

using namespace std;

// Инициализация массива количества кораблей
const int BattleshipGame::NUM_SHIPS[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

// Конструктор класса BattleshipGame
BattleshipGame::BattleshipGame() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    initializeField();    // Инициализация игрового поля
}

// Метод для инициализации поля
void BattleshipGame::initializeField() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            field[i][j] = '.'; // Заполнение поля символами '.'
        }
    }
}

// Метод для отметки окружения корабля
void BattleshipGame::markSurroundings(int row, int col) {
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && field[i][j] == '.') {
                field[i][j] = '-'; // Пометка клеток вокруг корабля символами '-'
            }
        }
    }
}

// Метод для проверки возможности размещения корабля
bool BattleshipGame::canPlaceShip(int row, int col, int shipLength, int direction) {
    if (direction == 0) { // Горизонтальное размещение
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
    else { // Вертикальное размещение
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

// Метод для размещения корабля
void BattleshipGame::placeShip(int row, int col, int shipLength, int direction) {
    Ship newShip;
    newShip.length = shipLength;
    newShip.coordinates.reserve(shipLength);

    for (int k = 0; k < shipLength; ++k) {
        if (direction == 0) { // Горизонтальное размещение
            field[row][col + k] = 'A' + shipLength; // Обозначение корабля
            newShip.coordinates.push_back({ row, col + k }); // Сохранение координат
            markSurroundings(row, col + k); // Отметка окружения
        }
        else { // Вертикальное размещение
            field[row + k][col] = 'A' + shipLength; // Обозначение корабля
            newShip.coordinates.push_back({ row + k, col }); // Сохранение координат
            markSurroundings(row + k, col); // Отметка окружения
        }
    }

    // Даем кораблю уникальное имя 
    newShip.name = "Ship" + to_string(ships.size() + 1);
    ships.push_back(newShip); // Добавляем корабль в вектор
}

// Метод для ручного размещения корабля
void BattleshipGame::playerPlaceShip(int row, int col, int shipLength, int direction) {
    Ship newShip;
    newShip.length = shipLength;
    newShip.coordinates.reserve(shipLength);

    for (int k = 0; k < shipLength; ++k) {
        if (direction == 0) { // Горизонтальное размещение
            field[row][col + k] = 'A' + shipLength; // Обозначение корабля
            newShip.coordinates.push_back({ row, col + k }); // Сохранение координат
            markSurroundings(row, col + k); // Отметка окружения
        }
        else { // Вертикальное размещение
            field[row + k][col] = 'A' + shipLength; // Обозначение корабля
            newShip.coordinates.push_back({ row + k, col }); // Сохранение координат
            markSurroundings(row + k, col); // Отметка окружения
        }
    }

    // Даем кораблю уникальное имя 
    newShip.name = "Ship" + to_string(ships.size() + 1);
    playerShips.push_back(newShip); // Добавляем корабль в вектор
}

// Метод для случайной генерации поля
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

// Метод для ручного ввода поля
void BattleshipGame::generateManualField() {
    int x, z, i = 0;
    char y;

    for (int shipLength : NUM_SHIPS) {
        system("cls");
        printField();
        if (i == 0) {
            cout << "Корабли будут располагаться от большего к меньшему\n";
            cout << "Вам нужно будет указать ориентацию, где 0 - горизонталь, а 1 - вертикаль, и начальные координаты:\n";
            i++;
        }
        bool placed = false;
        while (!placed) {
            cout << "Ориентация: ";
            cin >> z;
            cout << "Ряд: ";
            cin >> x;
            cout << "Столбец: ";
            cin >> y;
            int direction = z % 2;
            int row = x % SIZE;
            int col = BattleshipGame::CharToInt(y);
            if (canPlaceShip(row, col, shipLength, direction)) {
                playerPlaceShip(row, col, shipLength, direction); // Используем метод для размещения корабля игроком
                placed = true;
                printField();
            }
        }
    }
}

// Метод для вывода поля
void BattleshipGame::printField() {
    // Печатаем метки для столбцов
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // Преобразуем индекс в букву
        cout << colLabel << " ";
    }
    cout << endl;

    // Печатаем поля
    for (int i = 0; i < SIZE; ++i) {
        // Печатаем метки для строк
        cout << i << " "; // Нумерация строк начинается с 0
        for (int j = 0; j < SIZE; ++j) {
            char cell = field[i][j];
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Метод для выстрела игрока
void BattleshipGame::shoot(int row, int col) {
    if (field[row][col] == 'E' || field[row][col] == 'D' || field[row][col] == 'C' || field[row][col] == 'B') {
        field[row][col] = 'Y'; // Попадание
    }
    else if (field[row][col] == '.' || field[row][col] == '-') {
        field[row][col] = 'M'; // Мимо
    }

    // Проверяем каждый корабль в векторе на потопленность
    for (Ship& ship : ships) {
        bool allHit = true;
        for (const auto& coord : ship.coordinates) {
            if (field[coord.first][coord.second] != 'Y') {
                allHit = false; // Если хотя бы одна клетка корабля не помечена как попадание, он не потоплен
                break;
            }
        }
        if (allHit) {
            // Все клетки корабля помечены как попадания, он потоплен, помечаем его как 'X'
            for (const auto& coord : ship.coordinates) {
                field[coord.first][coord.second] = 'X';
            }
        }
    }
}

// Метод для случайного выстрела
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

// Метод для выстрела компьютера с использованием базовой стратегии
void BattleshipGame::computerShoot() {
    static int lastRow = -1;
    static int lastCol = -1;
    static int direction = -1;
    static bool hitLastTurn = false;

    if (lastRow == -1 && lastCol == -1) {
        // Рандомный выстрел, если это первый выстрел компьютера
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        shoot(row, col);
        lastRow = row;
        lastCol = col;
        return;
    }

    // Если последний выстрел попал в корабль
    if (field[lastRow][lastCol] == 'Y') {
        // Если корабль не потонул, продолжаем атаку вокруг последнего попадания
        if (direction == -1 || !hitLastTurn) {
            // Рандомно выбираем начальное направление для атаки
            direction = rand() % 4;
        }

        int row = lastRow;
        int col = lastCol;

        // Продолжаем стрельбу в текущем направлении
        while (true) {
            // Выбираем следующую клетку для атаки в зависимости от направления
            switch (direction) {
            case 0: // Вверх
                row--;
                break;
            case 1: // Вправо
                col++;
                break;
            case 2: // Вниз
                row++;
                break;
            case 3: // Влево
                col--;
                break;
            }

            // Проверяем, не вышли ли за границы поля
            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || field[row][col] == 'M') {
                // Если вышли за границы поля или уже стреляли в данную клетку, меняем направление
                direction = (direction + 1) % 4;
                row = lastRow;
                col = lastCol;
                hitLastTurn = false;
                return; // Выходим из метода, чтобы следующий выстрел был рандомным
            }

            // Выстрел по следующей клетке
            shoot(row, col);

            // Если попали, обновляем последние координаты и завершаем метод
            if (field[row][col] == 'Y') {
                lastRow = row;
                lastCol = col;
                hitLastTurn = true;
                return; // Выходим из метода, чтобы следующий выстрел был в этом же направлении
            }
            else {
                hitLastTurn = false;
                return; // Выходим из метода, чтобы следующий выстрел был в другом направлении
            }
        }
    }

    // Если корабль потонул или стратегия не применима, делаем рандомный выстрел
    int row = rand() % SIZE;
    int col = rand() % SIZE;
    while (field[row][col] == 'M') { // Проверяем, не стреляли ли уже в данную клетку
        row = rand() % SIZE;
        col = rand() % SIZE;
    }
    shoot(row, col);
    lastRow = row;
    lastCol = col;
}

// Метод для вывода двух полей бок о бок
void BattleshipGame::printFieldsSideBySide(const BattleshipGame& left, const BattleshipGame& right) const {
    // Печатаем метки для столбцов первого поля
    cout << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // Преобразуем индекс в букву
        cout << colLabel << " ";
    }

    // Разделитель между полями
    cout << "        ";

    // Печатаем метки для столбцов второго поля
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // Преобразуем индекс в букву
        cout << colLabel << " ";
    }
    cout << endl;

    // Печатаем поля
    for (int i = 0; i < SIZE; ++i) {
        // Печатаем метку для строки первого поля
        cout << i << " ";

        // Печатаем элементы первого поля
        for (int j = 0; j < SIZE; ++j) {
            char cell = left.field[i][j];
            cout << cell << " ";
        }

        // Разделитель между полями
        cout << "      ";

        // Печатаем метку для строки второго поля
        cout << i << " ";

        // Печатаем элементы второго поля
        for (int j = 0; j < SIZE; ++j) {
            char cell = right.field[i][j];
            // Если это вражеское поле и символ не "Y", "X", или "M", выводим "."
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

// Метод для проверки статуса поля (есть ли непотопленные корабли)
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

// Метод для преобразования символа столбца в индекс
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
    std::ofstream outFile(filename); // Открытие файла для записи

    // Печатаем метки для столбцов первого поля
    outFile << "  ";
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // Преобразуем индекс в букву
        outFile << colLabel << " ";
    }

    // Разделитель между полями
    outFile << "        ";

    // Печатаем метки для столбцов второго поля
    for (int i = 0; i < SIZE; ++i) {
        char colLabel = 'A' + i; // Преобразуем индекс в букву
        outFile << colLabel << " ";
    }
    outFile << std::endl;

    // Печатаем поля
    for (int i = 0; i < SIZE; ++i) {
        // Печатаем метку для строки первого поля
        outFile << i << " ";

        // Печатаем элементы первого поля
        for (int j = 0; j < SIZE; ++j) {
            char cell = left.field[i][j];
            outFile << cell << " ";
        }

        // Разделитель между полями
        outFile << "      ";

        // Печатаем метку для строки второго поля
        outFile << i << " ";

        // Печатаем элементы второго поля
        for (int j = 0; j < SIZE; ++j) {
            char cell = right.field[i][j];
            // Если это вражеское поле и символ не "Y", "X", или "M", выводим "."
            if (cell != 'Y' && cell != 'X' && cell != 'M') {
                outFile << "." << " ";
            }
            else {
                outFile << cell << " ";
            }
        }
        outFile << std::endl;
    }

    outFile.close(); // Закрытие файла
}
