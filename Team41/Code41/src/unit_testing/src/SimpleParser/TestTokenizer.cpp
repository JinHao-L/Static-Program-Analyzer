#include <iostream>
#include <string>

#include "Common/AstNode/TNode.h"
#include "SimpleParser/Tokenizer.h"
#include "TestTokenizerUtils.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Tokenizer: all") {
    string s = "procedure main {\n"
               "    one = 0;\n"
               "    two = 0;\n"
               "    read x;\n"
               "    print x;\n"
               "    while (!(1 > 2) && (3 >= 4)) {\n"
               "        one = 1;\n"
               "    }\n"
               "    if ((one != two) || (1 <= 2)) then {\n"
               "        two = 2;\n"
               "    } else {\n"
               "        two = 3;\n"
               "    }\n"
               "}";
    Tokenizer tokenizer(s);
    Tokens tokens = tokenizer.tokenize();
    vector<pair<TokenType, string>> expected = {
            {TokenType::name,           "procedure"},
            {TokenType::name,           "main"},
            {TokenType::openingBrace,   "{"},
            {TokenType::name,           "one"},
            {TokenType::assign,         "="},
            {TokenType::integer,        "0"},
            {TokenType::semicolon,      ";"},
            {TokenType::name,           "two"},
            {TokenType::assign,         "="},
            {TokenType::integer,        "0"},
            {TokenType::semicolon,      ";"},
            {TokenType::name,           "read"},
            {TokenType::name,           "x"},
            {TokenType::semicolon,      ";"},
            {TokenType::name,           "print"},
            {TokenType::name,           "x"},
            {TokenType::semicolon,      ";"},
            {TokenType::name,           "while"},
            {TokenType::openingBracket, "("},
            {TokenType::notOp,          "!"},
            {TokenType::openingBracket, "("},
            {TokenType::integer,        "1"},
            {TokenType::gt,             ">"},
            {TokenType::integer,        "2"},
            {TokenType::closingBracket, ")"},
            {TokenType::andOp,          "&&"},
            {TokenType::openingBracket, "("},
            {TokenType::integer,        "3"},
            {TokenType::ge,             ">="},
            {TokenType::integer,        "4"},
            {TokenType::closingBracket, ")"},
            {TokenType::closingBracket, ")"},
            {TokenType::openingBrace,   "{"},
            {TokenType::name,           "one"},
            {TokenType::assign,         "="},
            {TokenType::integer,        "1"},
            {TokenType::semicolon,      ";"},
            {TokenType::closingBrace,   "}"},
            {TokenType::name,           "if"},
            {TokenType::openingBracket, "("},
            {TokenType::openingBracket, "("},
            {TokenType::name,           "one"},
            {TokenType::ne,             "!="},
            {TokenType::name,           "two"},
            {TokenType::closingBracket, ")"},
            {TokenType::orOp,           "||"},
            {TokenType::openingBracket, "("},
            {TokenType::integer,        "1"},
            {TokenType::le,             "<="},
            {TokenType::integer,        "2"},
            {TokenType::closingBracket, ")"},
            {TokenType::closingBracket, ")"},
            {TokenType::name,           "then"},
            {TokenType::openingBrace,   "{"},
            {TokenType::name,           "two"},
            {TokenType::assign,         "="},
            {TokenType::integer,        "2"},
            {TokenType::semicolon,      ";"},
            {TokenType::closingBrace,   "}"},
            {TokenType::name,           "else"},
            {TokenType::openingBrace,   "{"},
            {TokenType::name,           "two"},
            {TokenType::assign,         "="},
            {TokenType::integer,        "3"},
            {TokenType::semicolon,      ";"},
            {TokenType::closingBrace,   "}"},
            {TokenType::closingBrace,   "}"},
            {TokenType::eof,            ""},
    };
    TestTokenizerUtils::tokenizeAndCompare(s, expected);
}

TEST_CASE("Tokenizer: procedures") {
    SECTION("keyword as procedure") {
        string s = "procedure procedure {"
                   "print x;"
                   "}";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,         "procedure"},
                {TokenType::name,         "procedure"},
                {TokenType::openingBrace, "{"},
                {TokenType::name,         "print"},
                {TokenType::name,         "x"},
                {TokenType::semicolon,    ";"},
                {TokenType::closingBrace, "}"},
                {TokenType::eof,          ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: read statement") {
    SECTION("correct") {
        string s = "read thisisavariable;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "read"},
                {TokenType::name,      "thisisavariable"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("no spacing") {
        string s = "readthisisavariable;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "readthisisavariable"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing capital letters") {
        string s = "rEAD x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "rEAD"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("leading capital letter") {
        string s = "Read x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "Read"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing numbers") {
        string s = "read123 x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "read123"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("keyword as argument") {
        string s = "read read;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "read"},
                {TokenType::name,      "read"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}


TEST_CASE("Tokenizer: print statement") {
    SECTION("correct") {
        string s = "print thisisavariable;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "print"},
                {TokenType::name,      "thisisavariable"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("no spacing") {
        string s = "printthisisavariable;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "printthisisavariable"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing capital letters") {
        string s = "pRINT x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "pRINT"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("leading capital letter") {
        string s = "Print x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "Print"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing numbers") {
        string s = "print123 x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "print123"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("keyword as argument") {
        string s = "print print;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "print"},
                {TokenType::name,      "print"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: call statement") {
    SECTION("correct") {
        string s = "call main;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "call"},
                {TokenType::name,      "main"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("no spacing") {
        string s = "callthisisavariable;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "callthisisavariable"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing capital letters") {
        string s = "cALL x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "cALL"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("leading capital letter") {
        string s = "Call x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "Call"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("trailing numbers") {
        string s = "call123 x;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "call123"},
                {TokenType::name,      "x"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("keyword as argument") {
        string s = "call call;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "call"},
                {TokenType::name,      "call"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: while statement") {
    SECTION("correct") {
        string s = "while(1==1){print x;}";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,           "while"},
                {TokenType::openingBracket, "("},
                {TokenType::integer,        "1"},
                {TokenType::eq,             "=="},
                {TokenType::integer,        "1"},
                {TokenType::closingBracket, ")"},
                {TokenType::openingBrace,   "{"},
                {TokenType::name,           "print"},
                {TokenType::name,           "x"},
                {TokenType::semicolon,      ";"},
                {TokenType::closingBrace,   "}"},
                {TokenType::eof,            ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: if statement") {
    SECTION("correct") {
        string s = "if (1==1) then { print x; } else { print y; }";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,           "if"},
                {TokenType::openingBracket, "("},
                {TokenType::integer,        "1"},
                {TokenType::eq,             "=="},
                {TokenType::integer,        "1"},
                {TokenType::closingBracket, ")"},
                {TokenType::name,           "then"},
                {TokenType::openingBrace,   "{"},
                {TokenType::name,           "print"},
                {TokenType::name,           "x"},
                {TokenType::semicolon,      ";"},
                {TokenType::closingBrace,   "}"},
                {TokenType::name,           "else"},
                {TokenType::openingBrace,   "{"},
                {TokenType::name,           "print"},
                {TokenType::name,           "y"},
                {TokenType::semicolon,      ";"},
                {TokenType::closingBrace,   "}"},
                {TokenType::eof,            ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: assign statement") {
    SECTION("correct") {
        string s = "variable = 1234;";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,      "variable"},
                {TokenType::assign,    "="},
                {TokenType::integer,   "1234"},
                {TokenType::semicolon, ";"},
                {TokenType::eof,       ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: conditional expression") {
    SECTION("correct") {
        string s = "!(a==b) (cc==dd) && (1==1) || (1==1)";
        vector<pair<TokenType, string>> expected = {
                {TokenType::notOp,          "!"},
                {TokenType::openingBracket, "("},
                {TokenType::name,           "a"},
                {TokenType::eq,             "=="},
                {TokenType::name,           "b"},
                {TokenType::closingBracket, ")"},
                {TokenType::openingBracket, "("},
                {TokenType::name,           "cc"},
                {TokenType::eq,             "=="},
                {TokenType::name,           "dd"},
                {TokenType::closingBracket, ")"},
                {TokenType::andOp,          "&&"},
                {TokenType::openingBracket, "("},
                {TokenType::integer,        "1"},
                {TokenType::eq,             "=="},
                {TokenType::integer,        "1"},
                {TokenType::closingBracket, ")"},
                {TokenType::orOp,           "||"},
                {TokenType::openingBracket, "("},
                {TokenType::integer,        "1"},
                {TokenType::eq,             "=="},
                {TokenType::integer,        "1"},
                {TokenType::closingBracket, ")"},
                {TokenType::eof,            ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: relational expression") {
    SECTION("correct") {
        string s = "a<b<=c>d>=1==2!=3";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,    "a"},
                {TokenType::lt,      "<"},
                {TokenType::name,    "b"},
                {TokenType::le,      "<="},
                {TokenType::name,    "c"},
                {TokenType::gt,      ">"},
                {TokenType::name,    "d"},
                {TokenType::ge,      ">="},
                {TokenType::integer, "1"},
                {TokenType::eq,      "=="},
                {TokenType::integer, "2"},
                {TokenType::ne,      "!="},
                {TokenType::integer, "3"},
                {TokenType::eof,     ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: arithmetic expression") {
    SECTION("correct") {
        string s = "flwekfjw * 139458 + fiweu / fiowqefj % 2019381 - 23049823";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,    "flwekfjw"},
                {TokenType::times,   "*"},
                {TokenType::integer, "139458"},
                {TokenType::plus,    "+"},
                {TokenType::name,    "fiweu"},
                {TokenType::div,     "/"},
                {TokenType::name,    "fiowqefj"},
                {TokenType::mod,     "%"},
                {TokenType::integer, "2019381"},
                {TokenType::minus,   "-"},
                {TokenType::integer, "23049823"},
                {TokenType::eof,     ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("concatenated") {
        string s = "+++---***///%%%";
        vector<pair<TokenType, string>> expected = {
                {TokenType::plus,  "+"},
                {TokenType::plus,  "+"},
                {TokenType::plus,  "+"},
                {TokenType::minus, "-"},
                {TokenType::minus, "-"},
                {TokenType::minus, "-"},
                {TokenType::times, "*"},
                {TokenType::times, "*"},
                {TokenType::times, "*"},
                {TokenType::div,   "/"},
                {TokenType::div,   "/"},
                {TokenType::div,   "/"},
                {TokenType::mod,   "%"},
                {TokenType::mod,   "%"},
                {TokenType::mod,   "%"},
                {TokenType::eof,   ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: name") {
    SECTION("correct") {
        string s = "nevergonnagiveyouupnevergonnaletyoudown1111nevergonnarunaroundanddesertyou2222"
                   "nevergonnamakeyoucrynevergonnasaygoodbyenevergonnatellalieandhurtyou3333";
        vector<pair<TokenType, string>> expected = {
                {TokenType::name,
                                 "nevergonnagiveyouupnevergonnaletyoudown1111nevergonnarunaroundanddesertyou2222nevergonnamakeyoucrynevergonnasaygoodbyenevergonnatellalieandhurtyou3333"},
                {TokenType::eof, ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: integer") {
    SECTION("correct") {
        string s = "341098257902358610295781340912835610947319085361094832751902783412039561029587312409";
        vector<pair<TokenType, string>> expected = {
                {TokenType::integer, "341098257902358610295781340912835610947319085361094832751902783412039561029587312409"},
                {TokenType::eof,     ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }

    SECTION("all zeroes should throw") {
        string s = "0000000000000000000";
        REQUIRE_THROWS(TestTokenizerUtils::tokenize(s));
    }

    SECTION("leading zeroes should throw") {
        string s = "0000000000000000000999";
        REQUIRE_THROWS(TestTokenizerUtils::tokenize(s));
    }

    SECTION("single zero should not throw") {
        string s = "0";
        vector<pair<TokenType, string>> expected = {
                {TokenType::integer, "0"},
                {TokenType::eof,     ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: whitespace") {
    SECTION("correct") {
        string s = "    \t   \n   \r   \f   \v   ";
        vector<pair<TokenType, string>> expected = {
                {TokenType::eof, ""},
        };
        TestTokenizerUtils::tokenizeAndCompare(s, expected);
    }
}

TEST_CASE("Tokenizer: unknown input") {
    SECTION("first") {
        string s = "[ ] : ' \\ / < > @ # $ % ^ & ~";
        REQUIRE_THROWS(TestTokenizerUtils::tokenize(s));
    }
}
