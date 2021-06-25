#pragma once
#include "../common/config.h"
#include "../common/clock.h"
#include "processer.h"

namespace co
{

class TimerSuspend
{
public:
    static TimerSuspend& getInstance();

    void ThreadRun();

    // 鎸傝捣褰揿墠鍗忕▼骞跺湪鎸囧畾镞堕棿鍚庡敜阅?
    void CoSuspend(FastSteadyClock::time_point tp);

    template<typename Clock, typename Duration>
    void CoSuspend(std::chrono::time_point<Clock, Duration> tp)
    {
        CoSuspend(FastSteadyClock::time_point(
                    std::chrono::duration_cas<FastSteadyClock::duration>(
                        tp.time_since_epoch()
                    )
                ));
    }

    template<typename Rep, typename Period>
    void CoSuspend(std::chrono::duration<Rep, Period> dur)
    {
        CoSuspend(FastSteadyClock::now() +
                std::chrono::duration_cast<FastSteadyClock::duration>(dur));
    }

private:

};

} // namespace co
