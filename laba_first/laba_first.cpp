#include <iostream>
using namespace std;


void task1TypesInfo() {

    cout << "Вывести, сколько памяти (в байтах) на вашем компьютере отводится под различные типы данных:\n\n";

    int intVar;
    short shortVar;
    long longVar;
    float floatVar;
    double doubleVar;
    long double longDoubleVar;
    char charVar;
    bool boolVar;

    cout << "int весит " << sizeof(intVar) << " байт\n";
    cout << "short весит " << sizeof(shortVar) << " байт\n";
    cout << "long весит " << sizeof(longVar) << " байт\n";
    cout << "float весит " << sizeof(floatVar) << " байт\n";
    cout << "double весит " << sizeof(doubleVar) << " байт\n";
    cout << "long double весит " << sizeof(longDoubleVar) << " байт\n";
    cout << "char весит " << sizeof(charVar) << " байт\n";
    cout << "bool весит " << sizeof(boolVar) << " байт\n\n";
}

void task2BinaryIntFloatDouble() {


    cout << "Вывести двоичное представление int (знак + значащие разряды):\n\n";

    int intValue;
    cout << "Введите int: ";
    cin >> intValue;

    int bitCount = sizeof(int) * 8;
    unsigned int bitMask = 1u << (bitCount - 1);

    cout << "INT (bin): ";
    for (int i = 0; i < bitCount; i++) {
        cout << ((intValue & (bitMask >> i)) ? '1' : '0');
        if (i == 0) cout << " ";
    }
    cout << "\n\n";


    cout << "Вывести двоичное представление float (знак | порядок | мантисса):\n\n";

    float floatValue;
    cout << "Введите float: ";
    cin >> floatValue;

    union {
        float floatValue;
        unsigned int intValue;
    } floatUnion;

    floatUnion.floatValue = floatValue;

    bitCount = sizeof(float) * 8;
    bitMask = 1u << (bitCount - 1);

    cout << "FLOAT (bin): ";
    for (int i = 0; i < bitCount; i++) {
        cout << ((floatUnion.intValue & (bitMask >> i)) ? '1' : '0');
        if (i == 0 || i == 8) cout << " ";
    }
    cout << "\n\n";


    cout << "Вывести двоичное представление double (знак | порядок | мантисса):\n\n";

    double doubleValue;
    cout << "Введите double: ";
    cin >> doubleValue;

    union {
        double doubleValue;
        unsigned int parts[2];
    } doubleUnion;

    doubleUnion.doubleValue = doubleValue;

    unsigned int bitMask32 = 1u << 31;

    cout << "DOUBLE (bin): ";


    for (int i = 0; i < 32; i++) {
        cout << ((doubleUnion.parts[1] & (bitMask32 >> i)) ? '1' : '0');
        if (i == 0 || i == 11) cout << " ";
    }


    for (int i = 0; i < 32; i++) {
        cout << ((doubleUnion.parts[0] & (bitMask32 >> i)) ? '1' : '0');
    }

    cout << "\n\n";
}


void task5BitEditing() {

    cout << "Выбор типа:\n1. int\n2. float\n3. double\n";
    int typeChoice;
    cin >> typeChoice;

    if (typeChoice == 1) {
        int intValue;
        cin >> intValue;

        int bitArray[32]{};
        for (int i = 0; i < 32; i++)
            bitArray[i] = (intValue >> (31 - i)) & 1;

        cout << "BIN: ";
        for (int bit : bitArray) cout << bit;
        cout << "\n";

        int bitIndex, bitValue;
        cout << "Индекс и значение: ";
        cin >> bitIndex >> bitValue;
        bitArray[31 - bitIndex] = bitValue;

        cout << "РЕЗ: ";
        for (int bit : bitArray) cout << bit;
        cout << "\n";
    }

    else if (typeChoice == 2) {
        float floatValue;
        cin >> floatValue;

        union {
            float floatValue;
            unsigned int intValue;
        } floatUnion;

        floatUnion.floatValue = floatValue;

        int bitArray[32]{};
        for (int i = 0; i < 32; i++)
            bitArray[i] = (floatUnion.intValue >> (31 - i)) & 1;

        cout << "BIN: ";
        for (int bit : bitArray) cout << bit;
        cout << "\n";
    }

    else if (typeChoice == 3) {
        double doubleValue;
        cin >> doubleValue;

        union {
            double doubleValue;
            unsigned int parts[2];
        } doubleUnion;

        doubleUnion.doubleValue = doubleValue;

        int bitArray[64]{};
        for (int i = 0; i < 32; i++)
            bitArray[i] = (doubleUnion.parts[1] >> (31 - i)) & 1;
        for (int i = 0; i < 32; i++)
            bitArray[i + 32] = (doubleUnion.parts[0] >> (31 - i)) & 1;

        cout << "BIN: ";
        for (int bit : bitArray) cout << bit;
        cout << "\n";
    }
}


void idzDoubleTask() {

    cout << "\nУстановка режима округления (эмуляция):\n\n";

    double doubleValue;
    cin >> doubleValue;

    union {
        double doubleValue;
        unsigned int parts[2];
    } doubleUnion;

    doubleUnion.doubleValue = doubleValue;

    int bitArray[64]{};
    for (int i = 0; i < 32; i++)
        bitArray[i] = (doubleUnion.parts[1] >> (31 - i)) & 1;
    for (int i = 0; i < 32; i++)
        bitArray[i + 32] = (doubleUnion.parts[0] >> (31 - i)) & 1;

    cout << "ИЗНАЧ: ";
    for (int bit : bitArray) cout << bit;
    cout << "\n";

    int lastOneIndex = -1;
    for (int i = 0; i < 64; i++)
        if (bitArray[i]) lastOneIndex = i;

    int twoBitValue = bitArray[10] * 2 + bitArray[11];
    if (twoBitValue % 3 == 0)
        bitArray[lastOneIndex + 1] = 1;
    else if (twoBitValue % 3 == 1) {
        bitArray[lastOneIndex + 1] = 1;
        bitArray[lastOneIndex + 2] = 1;
    }
    else
        bitArray[lastOneIndex + 3] = 1;

    cout << "КОНЕЧ: ";
    for (int bit : bitArray) cout << bit;
    cout << "\n";
}


int main() {
    setlocale(LC_ALL, "Russian");

    task1TypesInfo();
    task2BinaryIntFloatDouble();
    task5BitEditing();
    idzDoubleTask();

    return 0;
}
