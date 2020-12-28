/*
 * Юревич В.Ю. М8О-207Б-19
 * Создать шаблон динамической коллекцию, согласно варианту
 * задания:
 * 1. Коллекция должна быть реализована с помощью умных указателей
 * (std::shared_ptr, std::weak_ptr). Опционально использование
 * std::unique_ptr;
 * 2. В качестве параметра шаблона коллекция должна принимать тип
 * данных – фигуры;
 * 3. Коллекция должна содержать метод доступа: pop, push, top;
 * 4. Реализовать аллокатор, который выделяет фиксированный размер
 * памяти (количество блоков памяти – является параметром шаблона
 * аллокатора). Внутри аллокатор должен хранить указатель на
 * используемый блок памяти и динамическую коллекцию указателей на
 * свободные блоки. Динамическая коллекция должна соответствовать
 * варианту задания (Динамический массив, Список, Стек, Очередь).
 * 5. Коллекция должна использовать аллокатор для выделения и
 * освобождения памяти для своих элементов.
 * 6. Аллокатор должен быть совместим с контейнерами std::map и
 * std::list (опционально – vector).
 * 7. Реализовать программу, которая:
 * - позволяет вводить с клавиатуры фигуры (с типом int в качестве
 *   параметра шаблона фигуры) и добавлять в коллекцию;
 * - позволяет удалять элемент из коллекции по номеру элемента;
 * - выводит на экран введенные фигуры c помощью std::for_each;
 * 
 * Вариант 13: 
 * Фигура - ромб. Контейнер - Список, Аллокатор - динамический массив
 */

#include "List.h"
#include "Rhombus.h"
#include "Allocator.h"
#include <iostream>
#include <algorithm>


const std::size_t BLOCK_SIZE  = 40;

TRhombus<int, Allocator<int, BLOCK_SIZE>> EnterRhombus() {
    TRhombus<int, Allocator<int, BLOCK_SIZE>> rhomb;
    bool key = false;
    do {
        std::cout << "Укажите координату Х центра ромба: ";
        std::cin >> rhomb.center.first;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else { 
            key = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (key != true);
    do {
        std::cout << "Укажите координату Y центра ромба: ";
        std::cin >> rhomb.center.second;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else { 
            key = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (key != false);
    do {
        std::cout << "Укажите длину вертикальной диагонали: ";
        std::cin >> rhomb.vertDiag;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else if (rhomb.vertDiag < 0) {
                    std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                }
        else {
            key = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while(key != true);
    do {
        std::cout << "Укажите длину горизонтальной диагонали: ";
        std::cin >> rhomb.horDiag;
        if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else if (rhomb.horDiag < 0) {
                    std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                }
        else {
            key = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while(key != false);
    return(rhomb);
}

void EnterPosition (size_t& pos) {
    bool key = false;
    size_t i;
    do {
        std::cout << "Укажите номер позиции: ";
        std::cin >> i;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else if (i < 0) {
            std::cout << "Ошибка ввода. Номер позиции в списке может быть только положительным. Повторите ввод.\n";
        }
        else {
            key = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while(key != true);
    pos = i;
}


int main() {
    TRhombus<int, Allocator<int, BLOCK_SIZE>> rhomb;
    TList<TRhombus<int, Allocator<int, BLOCK_SIZE>>> list;
    bool key = false;
    int menu = 1;
    int square;
    size_t i;

    auto Print = [](const TRhombus<int, Allocator<int, BLOCK_SIZE>>& r) {
		std::cout << r << "\n" << std::endl;
	};
    auto TestSquare = [&square](const TRhombus<int, Allocator<int, BLOCK_SIZE>>& r) {
        return (RhombusSquare<int, Allocator<int, BLOCK_SIZE>>(r) < square);
    };

    while(menu != 0) {
        switch(menu) {
            case 1:
                std::cout << "1 - Вывести меню\n2 - Добавить ромб в список\n3 - Печать списка" << std::endl;
                std::cout << "4 - Вставить по номеру в списке\n5 - Удалить по номеру в списке\n6 - Вывести количество элементов в списке" << std::endl;
                std::cout << "7 - Вставить элемент на место головы списка\n0 - Выход" << std::endl;
                break;
            case 2:
                rhomb = EnterRhombus();
                list.PushBack(rhomb);
                break;
            case 3:
                if (list.Size() <= 0) {
                    std::cout << "Ошибка. Сначала необходимо добавить что-нибудь в список" << std::endl;
                }
                else {
                    std::cout << std::endl;
                    std::for_each(list.Begin(), list.End(), Print);
                }
                break;
            case 4: {
                if (list.Size() <= 0) {
                    std::cout << "Ошибка. Сначала необходимо добавить что-нибудь в список" << std::endl;
                }
                else {   
                    EnterPosition(i);
                    rhomb = EnterRhombus();
                    TList<TRhombus<int, Allocator<int, BLOCK_SIZE>>>::TLIterator iter(list, i);
                    try {
                        list.Insert(iter, rhomb);
                    }
                    catch(std::logic_error& error){
                        std::cout << error.what();
                    }
                }
            }
            break;
            case 5: {
                if (list.Size() <= 0) {
                    std::cout << "Ошибка. Сначала необходимо добавить что-нибудь в список" << std::endl;
                }
                else {
                EnterPosition(i);
                TList<TRhombus<int, Allocator<int, BLOCK_SIZE>>>::TLIterator iter(list, i);
                try {
                        list.Erase(iter);
                    }
                    catch(std::logic_error& error){
                        std::cout << error.what();
                    }
                }
                break;
            }
            case 6:
                std::cout << list.Size() << std::endl;
                break;
            case 7:
            rhomb = EnterRhombus();
            list.InsertToHead(rhomb);
            break;
            case 0:
            break;
        }
        do {
            std::cout << "Выберете пункт меню: ";
            std::cin >> menu;
            if (std::cin.fail()) { //контроль вводимых данных
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
            }
            else if ((menu < 0) || (menu > 7)) {
                std::cout << "Указанный пункт отсутсвует в меню. Попробуйте ещё раз." << std::endl;
            }
            else {
                key = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while(key != true);
        key = false;
    }
    return(0);
}