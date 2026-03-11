#include <iostream>
#include "binaryoperation.h"
#include "number.h"
#include "tools.h"

int main() {
    Expression* firstNumber = new Number(10);
    Expression* secondNumber = new Number(20);
    Expression* operation = new BinaryOperation(firstNumber, '-', secondNumber);

    std::cout << "firstNumber vs secondNumberr: " << checkEquals(firstNumber, secondNumber) << std::endl;

    std::cout << "firstNumber vs operation: " << checkEquals(firstNumber, operation) << std::endl;

    delete firstNumber;
    delete secondNumber;

    return 0;
}
