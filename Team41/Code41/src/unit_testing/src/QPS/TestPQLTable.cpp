#include "catch.hpp"
#include "QPS/Table/PQLTable.h"
#include "QPS/Table/Row.h"

using namespace std;

TEST_CASE("QPS: PQLTable") {
    Header header({"a", "b", "c", "d"});
    PQLTable table = PQLTable(header);

    SECTION("empty table") {
        Header header2({"a", "b", "c", "d"});

        REQUIRE(table.isEmpty());
        REQUIRE(table.size() == 0);
        REQUIRE_FALSE(table.hasColumn("e"));
        REQUIRE(table.hasColumn("a"));
        REQUIRE(table.getHeader() == header2);
    }

    SECTION("populated table") {
        Row *row = new Row();
        row->addEntry("a", "1");
        row->addEntry("b", "2");
        row->addEntry("c", "3");
        row->addEntry("d", "4");

        Row *row2 = new Row();
        row2->addEntry("a", "1");
        row2->addEntry("b", "2");
        row2->addEntry("c", "3");
        row2->addEntry("e", "4");
        Header header2({"a", "b", "c", "d"});

        REQUIRE_NOTHROW(table.addRow(row));
        REQUIRE_THROWS(table.addRow((row2)));
        REQUIRE_THROWS(table.addRow(nullptr));

        // this is to test if adding rows will affect the checks we have done
        REQUIRE(table.size() == 1);
        REQUIRE_FALSE(table.isEmpty());
        REQUIRE_FALSE(table.hasColumn("e"));
        REQUIRE(table.hasColumn("a"));
        REQUIRE(table.getHeader() == header2);

        delete row2;
    }

    SECTION("combine table") {
        Header header2({"a", "v"});
        Header header3({"a"});
        Header header4({"a", "d"});

        /*
         * a | v
         * 1 | a
         * 1 | b
         * 2 | c
         */
        PQLTable table2 = PQLTable(header2);
        Row *row1a = new Row();
        Row *row1b = new Row();
        Row *row2c = new Row();
        REQUIRE_NOTHROW(row1a->addEntry("a", "1"));
        REQUIRE_NOTHROW(row1a->addEntry("v", "a"));
        REQUIRE_NOTHROW(row1b->addEntry("a", "1"));
        REQUIRE_NOTHROW(row1b->addEntry("v", "b"));
        REQUIRE_NOTHROW(row2c->addEntry("a", "2"));
        REQUIRE_NOTHROW(row2c->addEntry("v", "c"));
        REQUIRE_NOTHROW(table2.addRow(row1a));
        REQUIRE_NOTHROW(table2.addRow(row1b));
        REQUIRE_NOTHROW(table2.addRow(row2c));
        REQUIRE_THROWS(table2.mergeJoin(nullptr));
        /*
         * a
         * 1
         * 4
         * 3
         */
        PQLTable table3 = PQLTable(header3);
        Row *a1 = new Row();
        Row *a4 = new Row();
        Row *a3 = new Row();
        REQUIRE_NOTHROW(a1->addEntry("a", "1"));
        REQUIRE_NOTHROW(a4->addEntry("a", "4"));
        REQUIRE_NOTHROW(a3->addEntry("a", "3"));
        REQUIRE_NOTHROW(table3.addRow(a1));
        REQUIRE_NOTHROW(table3.addRow(a4));
        REQUIRE_NOTHROW(table3.addRow(a3));

        /*
         * a | v
         * 1 | a
         * 1 | b
         */
        Table *newTable = table2.mergeJoin(&table3);
        REQUIRE(newTable->getHeader() == header2);
        REQUIRE(newTable->size() == 2);
        REQUIRE(newTable->hasRow(row1a));
        REQUIRE(newTable->hasRow(row1b));
        REQUIRE_FALSE(newTable->hasRow(row2c));

        /*
         * a | d
         * 1 | z
         * 4 | x
         * 3 | y
         */
        Table *table4 = new PQLTable(header4);
        Row *row1z = new Row();
        Row *row4x = new Row();
        Row *row3y = new Row();
        REQUIRE_NOTHROW(row1z->addEntry("a", "1"));
        REQUIRE_NOTHROW(row1z->addEntry("d", "z"));
        REQUIRE_NOTHROW(row4x->addEntry("a", "4"));
        REQUIRE_NOTHROW(row4x->addEntry("d", "x"));
        REQUIRE_NOTHROW(row3y->addEntry("a", "3"));
        REQUIRE_NOTHROW(row3y->addEntry("d", "y"));
        REQUIRE_NOTHROW(table4->addRow(row1z));
        REQUIRE_NOTHROW(table4->addRow(row4x));
        REQUIRE_NOTHROW(table4->addRow(row3y));

        /*
         * a | v | d
         * 1 | a | z
         * 1 | b | z
         */
        Table *newTable2 = table2.mergeJoin(table4);
        Header header5({"a", "d", "v"});
        REQUIRE(newTable2->getHeader() == header5);
        REQUIRE(newTable2->size() == 2);

        Row *row1az = new Row();
        REQUIRE_NOTHROW(row1az->addEntry("a", "1"));
        REQUIRE_NOTHROW(row1az->addEntry("v", "a"));
        REQUIRE_NOTHROW(row1az->addEntry("d", "z"));
        Row *row1bz = new Row();
        REQUIRE_NOTHROW(row1bz->addEntry("a", "1"));
        REQUIRE_NOTHROW(row1bz->addEntry("v", "b"));
        REQUIRE_NOTHROW(row1bz->addEntry("d", "z"));
        REQUIRE(newTable2->hasRow(row1az));
        REQUIRE(newTable2->hasRow(row1bz));

        delete row1az;
        delete row1bz;

        delete newTable;
        delete table4;
        delete newTable2;
    }

    SECTION("MERGE_JOIN_TEST2") {
        Header header1({"v"});
        Header header2({"v", "a"});

        PQLTable table1 = PQLTable(header1);
        Row *rowX = new Row("v", "x");
        Row *rowY = new Row("v", "y");
        Row *rowG = new Row("v", "g");
        Row *rowA = new Row("v", "a");
        table1.addRow(rowX);
        table1.addRow(rowY);
        table1.addRow(rowG);
        table1.addRow(rowA);

        PQLTable *table2 = new PQLTable(header2);
        Row *rowa2 = new Row();
        rowa2->addEntry("v", "a");
        rowa2->addEntry("a", "2");
        Row *rowy1 = new Row();
        rowy1->addEntry("v", "y");
        rowy1->addEntry("a", "1");
        table2->addRow(rowa2);
        table2->addRow(rowy1);

        Table *table3 = table1.mergeJoin(table2);
        REQUIRE(table3->size() == 2);
        REQUIRE(table3->getHeader() == header2);

        delete table2;
        delete table3;
    }
}