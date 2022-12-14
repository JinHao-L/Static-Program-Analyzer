#include "EntityTable.h"
#include <stdexcept>

EntityTable::EntityTable() : mapping({{},
                                      {},
                                      {},
                                      {}}) {}

unordered_set<string> EntityTable::getConstants() {
    return mapping.at(CONST);
}

unordered_set<string> EntityTable::getProcedures() {
    return mapping.at(PROC);
}

unordered_set<string> EntityTable::getVariables() {
    return mapping.at(VAR);
}

void EntityTable::addConstant(const string &numStr) {
    mapping.at(CONST).insert(numStr);
}

void EntityTable::addProcedure(const string &procName) {
    if (isProcedure(procName)) {
        throw runtime_error("[PKB][EntityTable] Procedure name already declared");
    }
    mapping.at(PROC).insert(procName);
}

void EntityTable::addVariable(const string &varName) {
    mapping.at(VAR).insert(varName);
}

bool EntityTable::isConstant(const string &constVal) {
    unordered_set<string> consts = getConstants();
    return consts.find(constVal) != consts.end();
}

bool EntityTable::isProcedure(const string &procName) {
    unordered_set<string> procs = getProcedures();
    return procs.find(procName) != procs.end();
}

bool EntityTable::isVariable(const string &varName) {
    unordered_set<string> vars = getVariables();
    return vars.find(varName) != vars.end();
}

size_t EntityTable::getEntityCount(EntityType type) {
    return mapping.at(type).size();
}