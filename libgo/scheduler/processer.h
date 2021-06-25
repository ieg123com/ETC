#pragma once
#include "../common/config.h"
#include "../common/clock.h"
#include "../task/task.h"
#include "../common/ts_queue.h"

#if ENABLE_DEBUGGER
#include "../debug/listener.h"
#endif
#include <condition_variable>
#include <mutex>
#include <atomic>

namespace co {

class Scheduler;

// 鍗忕▼镓ц鍣?
// 瀵瑰簲涓€涓嚎绋? 璐熻矗链嚎绋嬬殑鍗忕▼璋冨害, 闱炵嚎绋嫔畨鍏?
class Processer
{
    friend class Scheduler;

private:
    Scheduler * scheduler_;

    // 绾跨▼ID
    int id_;

    // 婵€娲绘€?
    // 闱炴縺娲荤殑P浠呬粎鏄笉鑳芥帴鍙楁柊镄勫岗绋嫔姞鍏? 浠岖劧鍙互寮鸿AddTask骞舵甯稿鐞?
    volatile bool active_ = true;

    // 褰揿墠姝ｅ湪杩愯镄勫岗绋?
    Task* runningTask_{nullptr};
    Task* nextTask_{nullptr};

    // 姣忚疆璋冨害鍙姞链夐檺娆℃暟鏂板岗绋? 阒叉鏂板岗绋嫔垱寤烘柊鍗忕▼浜х敓姝诲惊鐜?
    int addNewQuota_ = 0;

    // 褰揿墠姝ｅ湪杩愯镄勫岗绋嬫湰娆¤皟搴﹀紑濮嬬殑镞堕棿鎴?Dispatch绾跨▼涓撶敤)
    volatile int64_t markTick_ = 0;
    volatile uint64_t markSwitch_ = 0;

    // 鍗忕▼璋冨害娆℃暟
    volatile uint64_t switchCount_ = 0;

    // 鍗忕▼阒熷垪
    typedef TSQueue<Task, true> TaskQueue;
    TaskQueue runnableQueue_;
    TaskQueue waitQueue_;
    TSQueue<Task, false> gcQueue_;

    TaskQueue newQueue_;

    // 绛夊緟镄勬浔浠跺彉閲?
    std::condition_variable_any cv_;
    std::atomic_bool waiting_{false};
    bool notified_ = false;

    static int s_check_;

public:
    ALWAYS_INLINE int Id() { return id_; }

    static Processer* & GetCurrentProcesser();

    static Scheduler* GetCurrentScheduler();

    inline Scheduler* GetScheduler() { return scheduler_; }

    // 銮峰彇褰揿墠姝ｅ湪镓ц镄勫岗绋?
    static Task* GetCurrentTask();

    // 鏄惁鍦ㄥ岗绋嬩腑
    static bool IsCoroutine();

    // 鍗忕▼鍒囧嚭
    ALWAYS_INLINE static void StaticCoYield();

    // 鎸傝捣镙囱瘑
    struct SuspendEntry {
        WeakPtr<Task> tk_;
        uint64_t id_;

        explicit operator bool() const { return !!tk_; }

        friend bool operator==(SuspendEntry const& lhs, SuspendEntry const& rhs) {
            return lhs.tk_ == rhs.tk_ && lhs.id_ == rhs.id_;
        }

        friend bool operator<(SuspendEntry const& lhs, SuspendEntry const& rhs) {
            if (lhs.id_ == rhs.id_)
                return lhs.tk_ < rhs.tk_;
            return lhs.id_ < rhs.id_;
        }

        bool IsExpire() const {
            return Processer::IsExpire(*this);
        }
    };

    // 鎸傝捣褰揿墠鍗忕▼
    static SuspendEntry Suspend();

    // 鎸傝捣褰揿墠鍗忕▼, 骞跺湪鎸囧畾镞堕棿鍚庤嚜锷ㄥ敜阅?
    static SuspendEntry Suspend(FastSteadyClock::duration dur);
    static SuspendEntry Suspend(FastSteadyClock::time_point timepoint);

    // 鍞ら啋鍗忕▼
    static bool Wakeup(SuspendEntry const& entry, std::function<void()> const& functor = NULL);

    // 娴嬭瘯涓€涓猄uspendEntry鏄惁杩桦彲鑳芥湁鏁?
    static bool IsExpire(SuspendEntry const& entry);

    /// --------------------------------------
    // for friend class Scheduler
private:
    explicit Processer(Scheduler * scheduler, int id);

    // 寰呮墽琛岀殑鍗忕▼鏁伴噺
    // 鏆傚寸鐢ㄤ簬璐熻浇鎸囨暟
    std::size_t RunnableSize();

    ALWAYS_INLINE void CoYield();

    // 鏂板垱寤恒€侀樆濉炲悗瑙﹀彂镄勫岗绋媋dd杩涙潵
    void AddTask(Task *tk);

    // 璋冨害
    void Process();

    // 锅锋潵镄勫岗绋媋dd杩涙潵
    void AddTask(SList<Task> && slist);

    void NotifyCondition();

    // 鏄惁澶勪簬绛夊緟钟舵€?镞爎unnable鍗忕▼)
    // 璋冨害绾跨▼浼氩敖閲忓垎閰嶅岗绋嬭绷鏉?
    ALWAYS_INLINE bool IsWaiting() { return waiting_; }

    // 鍗曚釜鍗忕▼镓ц镞堕昵瓒呰绷棰勮链? 鍒椤垽瀹氢负阒诲钟舵€?
    // 阒诲钟舵€佷笉鍐嶅姞鍏ユ柊镄勫岗绋? 骞剁敱璋冨害绾跨▼steal璧版墍链夊岗绋?姝ｅ湪镓ц镄勯櫎澶?
    bool IsBlocking();

    // 锅峰岗绋?
    SList<Task> Steal(std::size_t n);
    /// --------------------------------------

private:
    void WaitCondition();

    void GC();

    bool AddNewTasks();

    // 璋冨害绾跨▼镓撴爣璁? 鐢ㄤ簬妫€娴嬮樆濉?
    void Mark();

    int64_t NowMicrosecond();

    SuspendEntry SuspendBySelf(Task* tk);

    bool WakeupBySelf(IncursivePtr<Task> const& tkPtr, uint64_t id, std::function<void()> const& functor);
};

ALWAYS_INLINE void Processer::StaticCoYield()
{
    auto proc = GetCurrentProcesser();
    if (proc) proc->CoYield();
}

ALWAYS_INLINE void Processer::CoYield()
{
    Task *tk = GetCurrentTask();
    assert(tk);

    ++ tk->yieldCount_;

#if ENABLE_DEBUGGER
    DebugPrint(dbg_yield, "yield task(%s) state = %s", tk->DebugInfo(), GetTaskStateName(tk->state_));
    if (Listener::GetTaskListener())
        Listener::GetTaskListener()->onSwapOut(tk->id_);
#endif

    tk->SwapOut();
}


} //namespace co
