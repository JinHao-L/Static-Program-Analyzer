#include "catch.hpp"

#include "DesignExtractor/ParentExtractor.h"
#include "Common/AstBuilder.h"
#include "TestExtractorUtils.h"

using namespace std;

/**
 * Assign, Read, Print, While, If, Non-nested, Nested, n3iif, n3iwl, n3wim, n3wwl
 * multiproc1
 */

TEST_CASE("ParentExtractor: Assign") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("assign.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    REQUIRE(pe.getParentMap().empty());
    REQUIRE(pe.getParentTMap().empty());
    delete ast;
}

TEST_CASE("ParentExtractor: Read") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("read.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    REQUIRE(pe.getParentMap().empty());
    REQUIRE(pe.getParentTMap().empty());
    delete ast;
}

TEST_CASE("ParentExtractor: Print") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("print.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    REQUIRE(pe.getParentMap().empty());
    REQUIRE(pe.getParentTMap().empty());
    delete ast;
}

TEST_CASE("ParentExtractor: While") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("while.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"1",  {"2"}},
            {"3",  {"4"}},
            {"5",  {"6"}},
            {"7",  {"8"}},
            {"8",  {"9"}},
            {"10", {"11"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"1",  {"2"}},
            {"3",  {"4"}},
            {"5",  {"6"}},
            {"7",  {"8", "9"}},
            {"8",  {"9"}},
            {"10", {"11"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: If") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("if.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"1",  {"2",  "3"}},
            {"4",  {"5",  "6"}},
            {"7",  {"8",  "9"}},
            {"10", {"11", "14"}},
            {"11", {"12", "13"}},
            {"14", {"15", "16"}},
            {"17", {"18", "19"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"1",  {"2",  "3"}},
            {"4",  {"5",  "6"}},
            {"7",  {"8",  "9"}},
            {"10", {"11", "12", "13", "14", "15", "16"}},
            {"11", {"12", "13"}},
            {"14", {"15", "16"}},
            {"17", {"18", "19"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: Non-nested") {
    // non_nested-simple.txt
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("non_nested.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"3", {"4", "5"}},
            {"6", {"7", "8", "9"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"3", {"4", "5"}},
            {"6", {"7", "8", "9"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: Nested") {
    // nested-simple.txt
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("nested.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"1", {"2", "3"}},
            {"3", {"4", "5", "6", "7"}},
            {"7", {"8", "9", "10"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"1", {"2", "3", "4", "5", "6", "7", "8", "9", "10"}},
            {"3", {"4", "5", "6", "7", "8", "9", "10"}},
            {"7", {"8", "9", "10"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: n3iif") {
    TNode *ast = AstBuilder(TestExtractorUtils::readSimpleProgram("n3iif.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"1",  {"2",  "3",  "4"}},
            {"4",  {"5",  "11", "12", "13", "16"}},
            {"5",  {"6",  "9",  "10"}},
            {"6",  {"7",  "8"}},
            {"13", {"14", "15"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"1",  {"2",  "3", "4", "5", "6", "7",  "8",  "9",  "10", "11", "12", "13", "14", "15", "16"}},
            {"4",  {"5",  "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}},
            {"5",  {"6",  "7", "8", "9", "10"}},
            {"6",  {"7",  "8"}},
            {"13", {"14", "15"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: n3iwl") {
    TNode *ast = AstBuilder(TestExtractorUtils::readSimpleProgram("n3iwl.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"2",  {"3", "4", "13"}},
            {"4",  {"5", "6"}},
            {"6",  {"7", "8", "10", "11"}},
            {"8",  {"9"}},
            {"11", {"12"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"2",  {"3", "4", "5", "6",  "7",  "8",  "9",  "10", "11", "12", "13"}},
            {"4",  {"5", "6", "7", "8",  "9",  "10", "11", "12"}},
            {"6",  {"7", "8", "9", "10", "11", "12"}},
            {"8",  {"9"}},
            {"11", {"12"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: n3wim") {
    TNode *ast = AstBuilder(TestExtractorUtils::readSimpleProgram("n3wim.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"2",  {"3",  "4",  "21"}},
            {"4",  {"5",  "6",  "12", "13", "14", "20"}},
            {"6",  {"7",  "8",  "11"}},
            {"8",  {"9",  "10"}},
            {"14", {"15", "16", "19"}},
            {"16", {"17", "18"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"2",  {"3",  "4",  "5",  "6",  "7", "8",  "9",  "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"}},
            {"4",  {"5",  "6",  "7",  "8",  "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"}},
            {"6",  {"7",  "8",  "9",  "10", "11"}},
            {"8",  {"9",  "10"}},
            {"14", {"15", "16", "17", "18", "19"}},
            {"16", {"17", "18"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: n3wwl") {
    TNode *ast = AstBuilder(TestExtractorUtils::readSimpleProgram("n3wwl.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"2", {"3", "4"}},
            {"4", {"5", "6"}},
            {"6", {"7", "8"}},
            {"8", {"9"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"2", {"3", "4", "5", "6", "7", "8", "9"}},
            {"4", {"5", "6", "7", "8", "9"}},
            {"6", {"7", "8", "9"}},
            {"8", {"9"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}

TEST_CASE("ParentExtractor: multiproc1") {
    TNode *ast = AstBuilder(TestExtractorUtils::readDeInput("multiproc/multiproc1.x")).build();
    unordered_map<TNode *, string> nodeToStmtNumMap = TestExtractorUtils::makeNodeToStmtNumMap(ast);
    ParentExtractor pe = ParentExtractor(ast, nodeToStmtNumMap);
    pe.extract();

    unordered_map<string, list<string>> expectedParent = {
            {"1",  {"2",  "5", "6", "7"}},
            {"2",  {"3",  "4"}},
            {"10", {"11", "12"}},
            {"16", {"17", "18"}},
            {"22", {"23"}}
    };
    REQUIRE(pe.getParentMap() == expectedParent);
    unordered_map<string, list<string>> expectedParentT = {
            {"1",  {"2",  "3", "4", "5", "6", "7"}},
            {"2",  {"3",  "4"}},
            {"10", {"11", "12"}},
            {"16", {"17", "18"}},
            {"22", {"23"}}
    };
    REQUIRE(pe.getParentTMap() == expectedParentT);
    delete ast;
}
