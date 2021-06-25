#pragma once
#include "../common/config.h"
#include "../scheduler/processer.h"
#include <queue>
#include "co_condition_variable.h"

namespace co
{

/// 璇诲啓阌?
class CoRWMutex
{
    LFLock lock_;
    long lockState_;  // 0:镞犻挛, >=1:璇婚挛, -1:鍐欓挛

    // 鍏煎铡熺敓绾跨▼
    ConditionVariableAny rCv_;
    ConditionVariableAny wCv_;

    // 鏄惁鍐欎紭鍏?
    bool writePriority_;

public:
    explicit CoRWMutex(bool writePriority = true);
    ~CoRWMutex();

    void RLock();
    bool RTryLock();
    void RUnlock();

    void WLock();
    bool WTryLock();
    void WUnlock();

    bool IsLock();

private:
    void TryWakeUp();

public:
    class ReadView
    {
        friend class CoRWMutex;
        CoRWMutex * self_;

    public:
        void lock();
        bool try_lock();
        bool is_lock();
        void unlock();

        ReadView() = default;
        ReadView(ReadView const&) = delete;
        ReadView& operator=(ReadView const&) = delete;
    };

    class WriteView
    {
        friend class CoRWMutex;
        CoRWMutex * self_;

    public:
        void lock();
        bool try_lock();
        bool is_lock();
        void unlock();

        WriteView() = default;
        WriteView(WriteView const&) = delete;
        WriteView& operator=(WriteView const&) = delete;
    };

    ReadView& Reader();
    WriteView& Writer();

    // 鍏煎镞х増鎺ュ彛
    ReadView& reader();
    WriteView& writer();

private:
    ReadView readView_;
    WriteView writeView_;
};

typedef CoRWMutex co_rwmutex;
typedef CoRWMutex::ReadView co_rmutex;
typedef CoRWMutex::WriteView co_wmutex;

} //namespace co
