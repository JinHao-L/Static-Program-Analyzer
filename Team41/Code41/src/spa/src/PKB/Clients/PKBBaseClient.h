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

    bool isAssignStmt(const string &stmtNum) const;// Checks if statement is an assignment
    bool isWhileStmt(const string &stmtNum) const;// Checks if statement is a while statement
    bool isIfStmt(const string &stmtNum) const;// Checks if statement is an if statement
    bool isReadStmt(const string &stmtNum) const;// Checks if statement is a read statement
    bool isPrintStmt(const string &stmtNum) const;// Checks if statement is a print statement
    bool isCallStmt(const string &stmtNum) const;// Checks if statement is a call statement

    string getCallsProcNameAttr(const string &stmtNumber) const; // Gets calls.procName attr
    string getPrintVarNameAttr(const string &stmtNumber) const; // Gets print.varName attr
    string getReadVarNameAttr(const string &stmtNumber) const; // Gets read.varName attr

    /**
     * Gets the number of statements stored in table
     *
     * @return set of statement numbers
     */
    size_t getStatementCount() const;

    size_t getAssignCount() const; // Gets the number of assign statements stored in table
    size_t getWhileCount() const; // Gets the number of while statements stored in table
    size_t getIfCount() const; // Gets the number of if statements stored in table
    size_t getReadCount() const; // Gets the number of read statements stored in table
    size_t getPrintCount() const; // Gets the number of print statements stored in table
    size_t getCallCount() const; // Gets the number of call statements stored in table
    bool hasStmt(const string &stmtNumber) const; // Checks if statement exists in the PKB

    //======================================== Entities ==================================================

    unordered_set<string> getVariables() const;// Gets list of variables
    unordered_set<string> getConstants() const;// Gets list of constants
    unordered_set<string> getProcedures() const;// Gets list of procedure names
    unordered_set<string> getStatements() const; // Gets list of statement numbers

    bool isConstant(const string &constVal) const;// Checks if specified variable is registered
    bool isProcedure(const string &procName) const;// Checks if specified constant is registered
    bool isVariable(const string &varName) const;// Checks if specified procedure is registered

    size_t getConstantCount() const; // Gets the number of constants stored in table
    size_t getProcedureCount() const; // Gets the number of procedures stored in table
    size_t getVariableCount() const; // Gets the number of variables stored in table
};