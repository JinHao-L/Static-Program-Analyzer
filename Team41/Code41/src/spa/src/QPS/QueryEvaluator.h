#pragma once

#include <unordered_set>
#include <string>
#include <vector>

#include "PKB/PKBClient.h"

#include "QPS/Evaluator/Evaluator.h"
#include "QPS/Evaluator/UsesSEvaluator.h"
#include "QPS/Evaluator/UsesPEvaluator.h"
#include "QPS/Evaluator/ModifiesSEvaluator.h"
#include "QPS/Evaluator/ModifiesPEvaluator.h"
#include "QPS/Evaluator/SelectSynonymEvaluator.h"
#include "QPS/Evaluator/FollowsEvaluator.h"
#include "QPS/Evaluator/FollowsTEvaluator.h"
#include "QPS/Evaluator/ParentEvaluator.h"
#include "QPS/Evaluator/ParentTEvaluator.h"
#include "QPS/Evaluator/CallsEvaluator.h"
#include "QPS/Evaluator/CallsTEvaluator.h"
#include "QPS/Evaluator/NextEvaluator.h"
#include "QPS/Evaluator/NextTEvaluator.h"
#include "QPS/Evaluator/WithEvaluator.h"
#include "QPS/Evaluator/AffectsEvaluator.h"
#include "QPS/Evaluator/AffectsTEvaluator.h"
#include "QPS/Evaluator/AssignPatternEvaluator.h"
#include "QPS/Evaluator/IfPatternEvaluator.h"
#include "QPS/Evaluator/WhilePatternEvaluator.h"

#include "QueryProjector.h"
#include "QueryResult.h"
#include "QPS/QO/QueryObject.h"
#include "Optimizer/OptimizedQueryObject.h"
#include "QPS/QO/QueryClause.h"
#include "QPS/QO/Selectable.h"

#include "QPS/Proxy/NextKBProxy.h"
#include "QPS/Proxy/AffectsKBProxy.h"

using namespace std;

class QueryEvaluator {
private:
    PKBClient *pkb;
    NextKBProxy *nextKBProxy;
    AffectsKBProxy *affectsKBProxy;

    /**
     * Deletes a table after it is not being used.
     *
     * @param tableToDelete Table to be deleted.
     */
    void safeDeleteTable(Table *tableToDelete);

    /**
     * Deletes a table after it is not being used and it is not the same reference as result table.
     *
     * @param tableToDelete Table to be deleted.
     * @param resultTable Table that contains the current result.
     */
    void safeDeleteTable(Table *tableToDelete, Table *resultTable);

    Table *mergeTable(Table *resultTable, Table *intermediateTable);

    Table *evaluateClauses(Table *resultTable, QueryObject *queryObject);

    Table *evaluateSelectables(Table *resultTable, QueryObject *queryObject);

public:
    explicit QueryEvaluator(PKBClient *pkb);

    ~QueryEvaluator();

    /**
     * Based on the QueryObject, evaluates the query provided return a set of results.
     *
     * @param queryObject QueryObject.
     * @return A set of results based on the query provided.
     */
    QueryResult evaluateQuery(QueryObject *queryObject);

    /**
     * Constructs a table based on the QueryClause provided.
     *
     * @param clause QueryClause.
     * @return A table that contains information based on the QueryClause provided.
     */
    Table *evaluate(SuperClause *clause, bool canMorphClause);

    Table *evaluate(const QueryClause &clause);

    Table *evaluate(const PatternClause &clause);

    Table *evaluate(const WithClause &clause);

    /**
     * Extract the vector of synonyms from the query's return type from query object.
     *
     * @param queryObject QueryObject.
     * @return A vector of synonyms from the query's return type.
     */
    vector<string> getSynonyms(QueryObject *queryObject);
};
