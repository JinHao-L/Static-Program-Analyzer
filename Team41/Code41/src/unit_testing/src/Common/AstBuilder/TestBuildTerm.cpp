#include "catch.hpp"
#include "TestAstBuilderUtils.h"
#include "Common/TreeUtils.h"
#include "../AstNode/AstUtils.h"

using namespace std;

TEST_CASE("AST Builder: term") {
    SECTION("1") {
        // 2 * b
        string simple = TestAstBuilderUtils::readFile("term", "1-simple.txt");
        string xml = TestAstBuilderUtils::readFile("term", "1-xml.txt");
        // manually build actual AST
        TNode *mult = AstUtils::makeTimes(
                AstUtils::makeConstVal(Token::makeConst("2")),
                AstUtils::makeVarName(Token::makeName("b"))
        );
        // parse and test
        TNode *ast = TestAstBuilderUtils::parseXml(xml);
        REQUIRE(ast != nullptr);
        REQUIRE(TreeUtils::isEqual(ast, mult));
        delete ast;
        delete mult;
    }

    SECTION("2") {
        // c / 3
        string simple = TestAstBuilderUtils::readFile("term", "2-simple.txt");
        string xml = TestAstBuilderUtils::readFile("term", "2-xml.txt");
        // manually build actual AST
        TNode *div = AstUtils::makeDiv(
                AstUtils::makeVarName(Token::makeName("c")),
                AstUtils::makeConstVal(Token::makeConst("3"))
        );
        // parse and test
        TNode *ast = TestAstBuilderUtils::parseXml(xml);
        REQUIRE(ast != nullptr);
        REQUIRE(TreeUtils::isEqual(ast, div));
        delete ast;
        delete div;
    }

    SECTION("3") {
        // 10 % 10
        string simple = TestAstBuilderUtils::readFile("term", "3-simple.txt");
        string xml = TestAstBuilderUtils::readFile("term", "3-xml.txt");
        // manually build actual AST
        TNode *mod = AstUtils::makeMod(
                AstUtils::makeConstVal(Token::makeConst("10")),
                AstUtils::makeConstVal(Token::makeConst("10"))
        );
        // parse and test
        TNode *ast = TestAstBuilderUtils::parseXml(xml);
        REQUIRE(ast != nullptr);
        REQUIRE(TreeUtils::isEqual(ast, mod));
        delete ast;
        delete mod;
    }
}
