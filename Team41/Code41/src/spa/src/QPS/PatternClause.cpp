#include "PatternClause.h"

PatternClause::PatternClause(QueryDeclaration synonym, ClauseVariable lhs, PatternVariable rhs) :
    synonym(synonym), lhs(lhs), rhs(rhs) {}

QueryDeclaration PatternClause::getSynonym() const { return synonym; }
ClauseVariable PatternClause::getLHS() const { return lhs; }
PatternVariable PatternClause::getRHS() const { return rhs; }