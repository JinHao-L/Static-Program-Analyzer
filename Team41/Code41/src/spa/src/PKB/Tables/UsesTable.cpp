#include "UsesTable.h"

#include <utility>

UsesTable::UsesTable() : usesStmtRelation("UsesS"), usesProcRelation("UsesP") {}

void UsesTable::setVarUsedInStmt(const string& stmtNum, const string& varName) {
    usesStmtRelation.addMapping(stmtNum, varName);
}

unordered_set<string> UsesTable::getVarsUsedInStmt(string stmtNum) {
    return usesStmtRelation.getValuesFromKey(std::move(stmtNum));
}

unordered_set<string> UsesTable::getStmtsUsingVar(string varName) {
    return usesStmtRelation.getKeysFromValue(std::move(varName));
}

vector<pair<string, string>> UsesTable::getStmtsVarEntries() {
    return usesStmtRelation.getEntries();
}

unordered_set<string> UsesTable::getVarsUsedInSomeStmt() {
    return usesStmtRelation.getValues();
}

unordered_set<string> UsesTable::getStmtsUsingSomeVar() {
    return usesStmtRelation.getKeys();
}

bool UsesTable::isUsesS(string stmtNum, string varName) {
    return usesStmtRelation.hasMapping(std::move(stmtNum), std::move(varName));
}

void UsesTable::setVarUsedInProc(const string& procName, const string& varName) {
    usesProcRelation.addMapping(procName, varName);
}

unordered_set<string> UsesTable::getVarsUsedInProc(string procName) {
    return usesProcRelation.getValuesFromKey(std::move(procName));
}

unordered_set<string> UsesTable::getProcsUsingVar(string varName) {
    return usesProcRelation.getKeysFromValue(std::move(varName));
}

vector<pair<string, string>> UsesTable::getProcVarEntries() {
    return usesProcRelation.getEntries();
}

unordered_set<string> UsesTable::getVarsUsedInSomeProc() {
    return usesProcRelation.getValues();
}

unordered_set<string> UsesTable::getProcsUsingSomeVar() {
    return usesProcRelation.getKeys();
}

bool UsesTable::isUsesP(string procName, string varName) {
    return usesProcRelation.hasMapping(std::move(procName), std::move(varName));
}