#pragma once

#include "Common/AstNode/RelExpr.h"
#include "Common/AstNode/RelFactor.h"

class Gt : public RelExpr {
public:
    Gt(RelFactor *lhs, RelFactor *rhs);
};