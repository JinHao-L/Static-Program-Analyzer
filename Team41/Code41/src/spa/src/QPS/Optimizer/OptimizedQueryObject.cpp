#include "OptimizedQueryObject.h"

OptimizedQueryObject::OptimizedQueryObject(QueryObject *qo) : QueryObject(*qo), clauseGroups(nullptr) {
}

OptimizedQueryObject::OptimizedQueryObject(QueryObject *qo, ClauseGroups *cg) :
        QueryObject(*qo), clauseGroups(cg) {}

SuperClause *OptimizedQueryObject::popClause() {
    if (empty()) throw runtime_error("OptimizedQueryObject: no more clauses left to consume");
    return clauseGroups->pop();
}

bool OptimizedQueryObject::empty() {
    return clauseGroups->empty();
}

bool OptimizedQueryObject::isLastOfGroup() {
    return clauseGroups->isLastOfGroup();
}

size_t OptimizedQueryObject::currGroupSize() {
    return clauseGroups->currGroupSize();
}

bool OptimizedQueryObject::currGroupCanSimplify() {
    return clauseGroups->currGroupCanSimplify();
}

void OptimizedQueryObject::print() {
    clauseGroups->print();
}

OptimizedQueryObject::~OptimizedQueryObject() {
    cleanUp();
    delete clauseGroups;
}
