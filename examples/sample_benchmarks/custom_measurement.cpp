#include <gauge/gauge.hpp>
#include <cstdlib>

class benchmark_me
{
public:
    benchmark_me()
        : m_count(0),
          m_limit(1000)
    {}

    void run_this()
    {
        uint32_t k = 0;
        while(k < m_limit)
        {
            k += rand() % 100;
            ++m_count;
        }
    }

    uint32_t m_limit;
    uint32_t m_count;
};

/// A custom benchmark where we do not measure time
/// but implement our own start(), stop() and
/// measurement() functions.
///
/// In this case we want to see how many counts we need
/// in the benchmark_me class
class custom_measurement : public gauge::benchmark
{
public:

    void start()
    {
        m_old_count = m_benchmark_me.m_count;
    }

    void stop()
    {
        m_new_count = m_benchmark_me.m_count;
        m_limit = m_benchmark_me.m_limit;
    }

    double measurement()
    {
        assert(m_new_count >= m_old_count);
        uint32_t diff = m_new_count - m_old_count;

        return static_cast<double>(diff);
    }

    /// The unit we measure in
    std::string unit_text() const
    { return "counts"; }

    void store_results(gauge::temp_results &results)
    {
        // Add the first measurement
        auto& count = results["custom_counts"];

        if(count.m_unit.empty())
            count.m_unit = "counts";

        double diff = static_cast<double>(m_new_count - m_old_count);

        count.m_results.push_back(diff);
        count.m_iterations.push_back(iteration_count());

        // Add the second measurement
        auto& step = results["custom_count_step_size"];

        if(step.m_unit.empty())
            step.m_unit = "step size";

        step.m_results.push_back(m_limit / diff);
        step.m_iterations.push_back(iteration_count());
    }


    /// The class being bench-marked
    benchmark_me m_benchmark_me;

    uint32_t m_old_count;
    uint32_t m_new_count;
    uint32_t m_limit;
};


BENCHMARK_F(custom_measurement, BenchmarkMe, RunCount, 100)
{
    RUN{
        m_benchmark_me.run_this();
    }
}


