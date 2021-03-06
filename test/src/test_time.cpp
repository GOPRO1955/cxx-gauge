// Copyright (c) 2012 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <gtest/gtest.h>

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include <gauge/gauge.hpp>

namespace bc = boost::chrono;

struct sleep_benchmark : public gauge::time_benchmark
{
    bool accept_measurement()
    {
        // We always accept the first measurement here
        return true;
    }

    double measurement()
    {
        // Get the time spent sleeping
        double time = gauge::time_benchmark::measurement();
        // This should be higher than the requested time
        EXPECT_GT(time, m_last_delay);
        return time;
    }

    void run_benchmark(uint32_t delay)
    {
        m_last_delay = delay;
        RUN
        {
            boost::this_thread::sleep_for(bc::microseconds(delay));
        }
    }

protected:

    uint32_t m_last_delay;
};

BENCHMARK_F(sleep_benchmark, Gauge, sleep_10usecs, 1)
{
     run_benchmark(10);
}

BENCHMARK_F(sleep_benchmark, Gauge, sleep_100usecs, 1)
{
    run_benchmark(100);
}

BENCHMARK_F(sleep_benchmark, Gauge, sleep_1000usecs, 1)
{
    run_benchmark(1000);
}

BENCHMARK_F(sleep_benchmark, Gauge, sleep_10000usecs, 1)
{
    run_benchmark(10000);
}

BENCHMARK_F(sleep_benchmark, Gauge, sleep_100000usecs, 1)
{
    run_benchmark(100000);
}

TEST(Gauge, sleep_intervals)
{
    // Dummy arguments for gauge::runner
    int argc = 1;
    const char* argv[] = { "program" };

    gauge::runner::add_default_printers();
    gauge::runner::run_benchmarks(argc, argv);
}
