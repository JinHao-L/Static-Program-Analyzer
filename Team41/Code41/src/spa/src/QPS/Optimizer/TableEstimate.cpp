#include "TableEstimate.h"
#include "QPS/Optimizer/PKBAdapter.h"

#include <algorithm>
#include <iterator>
#include <unordered_set>

using namespace std;

TableEstimate::TableEstimate() = default;

TableEstimate::TableEstimate(const PKBAdapter &pkbAdapter) : pkbAdapter(pkbAdapter) {}

void TableEstimate::merge(const vector<QueryDeclaration> &sch) {
    // update row estimate
    estRows = estimateMergeCost(sch);

    // merge with new schema
    unordered_set<QueryDeclaration, queryDeclarationHasher, queryDeclarationEquals> a(schema.begin(), schema.end());
    for (const QueryDeclaration &cv: sch) {
        if (a.find(cv) == a.end()) schema.push_back(cv);
    }
}

bool TableEstimate::hasCommonCol(const vector<QueryDeclaration> &sch) {
    unordered_set<QueryDeclaration, queryDeclarationHasher, queryDeclarationEquals> a(schema.begin(), schema.end());
    for (const QueryDeclaration &cv: sch) {
        if (a.find(cv) != a.end()) return true;
    }
    return false;
}

long long TableEstimate::getEstimatedRows() const {
    return estRows;
}

vector<QueryDeclaration> TableEstimate::getSchema() const {
    return schema;
}

long long TableEstimate::estimateMergeCost(const vector<QueryDeclaration> &newSch) {
    if (schema.empty()) return pkbAdapter.getRowCount(newSch);

    if (hasCommonCol(newSch)) {
        // merge is constrained by the smaller table
        return min(estRows, pkbAdapter.getRowCount(newSch));
    } else {
        return estRows * pkbAdapter.getRowCount(newSch);
    }
}
