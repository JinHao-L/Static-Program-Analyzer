#include "catch.hpp"
#include "TestAstBuilderUtils.h"
#include "Common/TreeUtils.h"
#include <iostream>

using namespace std;

TEST_CASE("AST Builder: statement list") {
    SECTION("1") {
        /*
            read x;
            print x;
            call main;
            x = 0;
            while (1==1) { print x; }
            if (1==1) then { print x; } else { print y; }
         */
        string simple = TestAstBuilderUtils::readFile("stmtlist", "1-simple.txt");
        string xml = TestAstBuilderUtils::readFile("stmtlist", "1-xml.txt");
        // manually build actual AST
        TNode* stmts = TNode::makeStmtLst({
            TNode::makeReadStmt(TNode::makeVarName(Token::makeVar("x"))),
            TNode::makePrintStmt(TNode::makeVarName(Token::makeVar("x"))),
            TNode::makeCallStmt(TNode::makeVarName(Token::makeVar("main"))),
            TNode::makeAssignStmt(TNode::makeVarName(Token::makeVar("x")), TNode::makeConstVal(Token::makeConst("0"))),
            TNode::makeWhileStmt(
                    TNode::makeEq(TNode::makeConstVal(Token::makeConst("1")), TNode::makeConstVal(Token::makeConst("1"))),
                    TNode::makeStmtLst({ TNode::makePrintStmt(TNode::makeVarName(Token::makeVar("x"))) })
                ),
            TNode::makeIfStmt(
                    TNode::makeEq(TNode::makeConstVal(Token::makeConst("1")), TNode::makeConstVal(Token::makeConst("1"))),
                    TNode::makeStmtLst({ TNode::makePrintStmt(TNode::makeVarName(Token::makeVar("x"))) }),
                    TNode::makeStmtLst({ TNode::makePrintStmt(TNode::makeVarName(Token::makeVar("y"))) })
                )
        });
        // parse and test
        TNode *ast = TestAstBuilderUtils::parseXml(xml);
        REQUIRE(ast != nullptr);
        REQUIRE(TreeUtils::isEqual(ast, stmts));
    }
}