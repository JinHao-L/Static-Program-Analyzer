#include "PrintEntities.h"

bool PrintEntities::isPrint() {
    return true;
}

string PrintEntities::toString() {
    return "print";
}

int PrintEntities::hashCode() {
    return 4;
}

PrintEntities::PrintEntities() : Entities(new PrintReader()) {}

PrintEntities::~PrintEntities() {
    delete reader;
}