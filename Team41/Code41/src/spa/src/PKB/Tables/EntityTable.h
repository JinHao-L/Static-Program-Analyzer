#pragma once

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

enum EntityType {
    UNKNOWN_ENTITY,
    CONST,
    VAR,
    PROC
};

/**
 * Store list of entities used in the SIMPLE program
 */
class EntityTable {
private:
    vector<unordered_set<string>> mapping;
public:
    EntityTable();

    /**
     * Add a constant to the entity table
     * @param numStr the constant number
     */
    void addConstant(const string &numStr);

    /**
     * Add a variable to the entity table
     * @param varName the variable name
     */
    void addVariable(const string &varName);

    /**
     * Add a procedure to the entity table
     * @param procName the procedure name
     */
    void addProcedure(const string &procName);

    /**
     * Get the list of constants from the entity table
     */
    unordered_set<string> getConstants();

    /**
     * Get the list of variables from the entity table
     */
    unordered_set<string> getVariables();

    /**
     * Get the list of procedures from the entity table
     */
    unordered_set<string> getProcedures();

    /**
     * Checks if the constant value is in the entity table
     */
    bool isConstant(const string &constVal);

    /**
     * Checks if the procedure name is in the entity table
     */
    bool isProcedure(const string &procName);

    /**
     * Checks if the variable name is in the entity table
     */
    bool isVariable(const string &varName);

    /**
     * Gets the count of entity based on type
     *
     * @return count of entity of the specific type
     */
    size_t getEntityCount(EntityType type);
};

