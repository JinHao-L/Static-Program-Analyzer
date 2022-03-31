#include "ReadEntities.h"

bool ReadEntities::isRead() {
    return true;
}

string ReadEntities::toString() {
    return "read";
}

int ReadEntities::hashCode() {
    return 6;
}

ReadEntities::ReadEntities() : Entities(new ReadReader()) {}

ReadEntities::~ReadEntities() {
    delete reader;
}