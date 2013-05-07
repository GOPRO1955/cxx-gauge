#include <cstdint>

#include <gtest/gtest.h>

#include <gauge/table.hpp>

TEST(TestTable, test_table)
{
    std::string unit("seconds");

    gauge::table t;
    t.set_unit(unit);

    EXPECT_EQ(t.unit(), unit);

    t.add_row("ok");
    t.add_run(10);
    t.add_run(10);
    t.add_run(10);

    t["ok"] = 4.0;

    t.add_run(100);
    t["ok"] = 6.5;

    t.add_row("blabla");
    t["blabla"] = 342.23;

    t.add_run(1000);

    uint32_t runs = 5;
    EXPECT_EQ(t.runs(), runs);

    // The table should now contain the following results
    // name: test
    // unit: seconds
    // iterations: 10 10 10 100    1000
    //         ok: 0  0  4  6.5    0
    //     blabla: 0  0  0  342.23 0

    auto &ok = t.row("ok");
    EXPECT_EQ(ok.size(), runs);
    EXPECT_EQ(ok[0], 0);
    EXPECT_EQ(ok[1], 0);
    EXPECT_EQ(ok[2], 4);
    EXPECT_EQ(ok[3], 6.5);
    EXPECT_EQ(ok[4], 0);

    auto &blabla = t.row("blabla");
    EXPECT_EQ(blabla.size(), runs);
    EXPECT_EQ(blabla[0], 0);
    EXPECT_EQ(blabla[1], 0);
    EXPECT_EQ(blabla[2], 0);
    EXPECT_EQ(blabla[3], 342.23);
    EXPECT_EQ(blabla[4], 0);

    auto &iterations = t.iterations();
    EXPECT_EQ(iterations.size(), runs);
    EXPECT_EQ(iterations[0], 10);
    EXPECT_EQ(iterations[1], 10);
    EXPECT_EQ(iterations[2], 10);
    EXPECT_EQ(iterations[3], 100);
    EXPECT_EQ(iterations[4], 1000);


    // Sum all results just to check that the iterators work
    double sum = 0;
    for(auto &e : t)
    {
        for(auto& r : e.second)
        {
            sum += r;
        }
    }

    EXPECT_EQ(sum, 352.73);
}


