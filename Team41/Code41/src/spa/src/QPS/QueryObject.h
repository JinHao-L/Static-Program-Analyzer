#pragma once

#include <string>
#include <vector>
#include "QueryDeclaration.h"
#include "QueryClause.h"

using namespace std;

class QueryObject {
public:
    vector<QueryDeclaration> &declarations;
    vector<QueryClause> &clauses; // Actual clauses parser affects
    bool isQueryValid;
    QueryObject(vector<QueryDeclaration> &declarations, vector<QueryClause> &clauses, bool isQueryValid);
};