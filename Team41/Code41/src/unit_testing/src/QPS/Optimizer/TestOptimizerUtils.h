#pragma once

#include <string>
#include <vector>
#include "QPS/Optimizer/SimpleGraph.h"
#include "QPS/QO/SuperClause.h"
#include "QPS/Optimizer/OptimizedQueryObject.h"
#include "QPS/Optimizer/FifoGroup.h"

using namespace std;

class TestOptimizerUtils {
public:
    static void print(vector<vector<string>> &arr);
    static SimpleGraph<string> genStringGraph(int fromInclusive, int toInclusive, const vector<pair<int, int>> &edges);
    static vector<vector<SuperClause*>> prepareClauseGroups(string &query);
    static void testGroupandGroupsAbstractions(string &query);
    static void print(vector<vector<SuperClause*>> &clauses);
    static void print(vector<QueryDeclaration> arr);
    static void ensureOQOIsCorrect(string &query, PKBManager &pkbManager);
};

struct PointedSuperClauseHash {
    size_t operator()(const SuperClause *cl) const {
        return cl->hash();
    }
};

struct PointedSuperClauseEq {
    bool operator()(const SuperClause *lhs, const SuperClause *rhs) const {
        return lhs->equals(*rhs);
    }
};