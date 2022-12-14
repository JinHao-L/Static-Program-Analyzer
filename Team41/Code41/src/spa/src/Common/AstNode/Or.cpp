#include "Or.h"

Or::Or(CondExpr *lhs, CondExpr *rhs) : CondExpr(TNodeType::orOp,
                                                {static_cast<TNode *>(lhs), static_cast<TNode *>(rhs)}) {
}

string Or::toString() {
    return "||";
}

bool Or::isOr() const {
    return true;
}
