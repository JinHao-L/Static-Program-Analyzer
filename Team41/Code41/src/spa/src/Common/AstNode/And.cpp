#include "And.h"

And::And(CondExpr *lhsCondExpr, CondExpr *rhsCondExpr) : CondExpr(TNodeType::andOp, {static_cast<TNode *>(lhsCondExpr),
                                                                                     static_cast<TNode *>(rhsCondExpr)}) {}


string And::toString() {
    return "&&";
}

bool And::isAnd() const {
    return true;
}
