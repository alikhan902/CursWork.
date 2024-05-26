#include "BoardGeneration.h"
#include <iostream> // для ввода/вывода
#include <cstdlib>  // для system()

using namespace std;

int main() {
    BattleshipGame Computer;
    BattleshipGame Player;
    Computer.generateRandomField();
    setlocale(LC_ALL, "Russian");

    int z;
    cout << "Выберите метод генерации поля:\n1 - случайная генерация\n2 - ручной ввод" << endl;
    cin >> z;
    if (z == 1) {
        Player.generateRandomField();
    }
    else {
        Player.generateManualField();
    }

    while (Computer.fieldStatus() && Player.fieldStatus()) {
        system("cls"); // Очистка экрана

        cout << "Ваше поле:\t\t    Поле оппонента:" << endl;
        Player.printFieldsSideBySide(Player, Computer);

        cout << "Выберите как хотите атаковать:\n 1 - вручную\n 2 - случайно\n";
        cin >> z;
        if (z %2== 1) {
            int row;
            char col;
            cout << "Ряд: ";
            cin >> row;
            cout << "Столбец: ";
            cin >> col;
            Computer.shoot(row, BattleshipGame::CharToInt(col));
        }
        else if (z%2==0) {
            Computer.Randomshoot();
        }
        Player.computerShoot();
    }

    system("cls");
    Player.printFieldsSideBySide(Player, Computer);

    if (!Computer.fieldStatus()) {
        cout << "\nПобеда!";
    }
    else {
        cout << "\nПоражение.";
    }

    Player.saveFieldsToFile("fields.txt", Player, Computer);
    return 0;
}
