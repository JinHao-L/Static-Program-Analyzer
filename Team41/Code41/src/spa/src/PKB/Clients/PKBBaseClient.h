#pragma once

#include <string>
#include <unordered_set>

using namespace std;

class StmtTable;
class EntityTable;

/**
 * Used for retrieving information on the entities/statements of the SIMPLE source code.
 *
 * This PKB facade class provides methods to
 * access information on the SIMPLE source code entities/statements.
 */
class PKBBaseClient {
protected:
    StmtTable *stmtTable;
    EntityTable *entityTable;

public:
    PKBBaseClient();

    ~PKBBaseClient();

    //======================================== Statement ==================================================

    unordered_set<string> getAssigns() const;// Gets list of assign statement
    unordered_set<string> getWhiles() const;// Gets list of while statement
    unordered_set<string> getIfs() const;// Gets list of if statement
    unordered_set<string> getReads() const;// Gets list of read statement
    unordered_set<string> getPrints() const;// Gets list of print statement
    unordered_set<string> getCalls() const;// Gets list of call statement

    bool isAssignStmt(string stmtNum) const;// Checks if statement is an assignment
    bool isWhileStmt(string stmtNum) const;// Checks if statement is a while statement
    bool isIfStmt(string stmtNum) const;// Checks if statement is an if statement
    bool isReadStmt(string stmtNum) const;// Checks if statement is a read statement
    bool isPrintStmt(string stmtNum) const;// Checks if statement is a print statement
    bool isCallStmt(string stmtNum) const;// Checks if statement is a call statement

    /**
     * Gets the number of statements stored in table
     *
     * @return set of statement numbers
     */
    int getStatementCount() const;

    //======================================== Entities ==================================================

    unordered_set<string> getVariables() const;// Gets list of variables
    unordered_set<string> getConstants() const;// Gets list of constants
    unordered_set<string> getProcedures() const;// Gets list of procedure names
    // Gets list of statement numbers

    bool isConstant(string constVal) const;// Checks if specified variable is registered
    bool isProcedure(string procName) const;// Checks if specified constant is registered
    bool isVariable(string varName) const;// Checks if specified procedure is registered
    unordered_set<string> getStatements() const;
};