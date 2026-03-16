#include "tools.h"

bool checkEquals(Expression *first, Expression *second)
{
    if (!first || !second) {
        return first == second;
    }

    unsigned long long* vptrFirst = *(unsigned long long**)first;
    unsigned long long* vptrSecond = *(unsigned long long**)second;

    return vptrFirst == vptrSecond;
}
