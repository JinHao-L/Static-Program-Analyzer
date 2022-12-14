#pragma once

#include <vector>
#include "Common/CFGNode.h"
#include "PKB/Tables/NextTable.h"

using namespace std;

/**
 * Used for retrieving control flow information for SIMPLE source code.
 *
 * This PKB facade class provides methods to access the control flow graph and basic next relation
 */
class PKBCFGClient {
protected:
    NextTable *nextTable;
    CFGNode *rootCFG;
    StmtToNodeMap stmtToNodeMap;

public:
    PKBCFGClient();

    ~PKBCFGClient();

    //=========================================== CFG =======================================================

    /**
     * Gets the CFG for a specific stmt number
     *
     * @return pointer to CFG, nullptr for invalid stmtNumber
     */
    [[nodiscard]] CFGNode *getCFGForStmt(const string &stmtNum) const;

    /**
     * Gets the root CFG of the program
     */
    [[nodiscard]] CFGNode *getRootCFG() const;

    //=========================================== Next ===================================================

    /**
     * Checks if stmt2 can be executed immediately after stmt1
     */
    bool isNext(const string &stmt1, const string &stmt2) const;

    /**
     * Get the nodes that are executed directly after stmt
     */
    [[nodiscard]] vector<CFGNode *> getNextNodes(const string &stmt) const;

    /**
     * Gets the nodes that are executed directly before stmt
     */
    [[nodiscard]] vector<CFGNode *> getPrevNodes(const string &stmt) const;

    /**
     * Gets stmts pair where stmt1 are executed directly after stmt2
     */
    [[nodiscard]] vector<pair<string, string>> getAllNext() const;

    /**
     * get list of stmts that are executed before some stmt
     */
    [[nodiscard]] vector<string> getAllStmtsExecBeforeSomeStmt() const;

    /**
     * get list of stmts that are executed after some stmt
     */
    [[nodiscard]] vector<string> getAllStmtsExecAfterSomeStmt() const;

    /**
     * Get the number of stmts that are executed before some stmt
     */
    size_t getNumOfStartNodes() const;

    /**
     * Get the number of stmts that are executed after some stmt
     */
    size_t getNumOfEndNodes() const;
};