#include "AssignEntities.h"

bool AssignEntities::isAssign() {
    return true;
}

string AssignEntities::toString() {
    return "assign";
}

int AssignEntities::hashCode() {
    return 0;
}

AssignEntities::AssignEntities() : Entities(new AssignReader()) {}

AssignEntities::~AssignEntities() {
    delete reader;
}