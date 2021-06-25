#pragma once
#include "../common/config.h"
#include "../common/spinlock.h"
#include "../sync/channel.h"
#include "../scheduler/scheduler.h"

namespace co {

// 鍗忕▼姹?
// 鍙互镞犵绅涓庡纾姝ヤ唬镰佺粨鍚? 澶勭悊寮傛妗嗘灦涓殑阒诲浜嬩欢
class AsyncCoroutinePool
{
public:
    static AsyncCoroutinePool* Create(size_t maxCallbackPoints = 128);

    typedef std::function<void()> Func;

    // 鍒濆鍖栧岗绋嬫暟閲?
    void InitCoroutinePool(size_t maxCoroutineCount);

    // 鍚姩鍗忕▼姹?
    void Start(int minThreadNumber, int maxThreadNumber = 0);

    void Post(Func const& func, Func const& callback);

    template <typename R>
    void Post(Channel<R> const& ret, std::function<R()> const& func) {
        Post([=]{ ret << func(); }, NULL);
    }

    void Post(Channel<void> const& ret, std::function<void()> const& func) {
        Post([=]{ func(); ret << nullptr; }, NULL);
    }

    template <typename R>
    void Post(std::function<R()> const& func, std::function<void(R&)> const& callback) {
        std::shared_ptr<R> ctx(new R);
        Post([=]{ *ctx = func(); }, [=]{ callback(*ctx); });
    }

    // 瑙﹀彂镣?
    struct CallbackPoint
    {
        size_t Run(size_t maxTrigger = 0);

        void SetNotifyFunc(Func const& notify);

    private:
        friend class AsyncCoroutinePool;

        void Post(Func && cb);

        void Notify();

    private:
        Channel<Func> channel_;
        Func notify_;
    };

    // 缁戝畾锲炶皟鍑芥暟瑙﹀彂镣? 鍙互缁戝畾澶氢釜瑙﹀彂镣? 杞祦浣跨敤.
    // 濡傛灉涓岖粦瀹氲Е鍙戠偣, 鍒椤洖璋冨嚱鏁扮洿鎺ュ湪鍗忕▼姹犵殑宸ヤ綔绾跨▼涓Е鍙?
    // 绾跨▼瀹夊叏鎺ュ彛
    bool AddCallbackPoint(CallbackPoint * point);

private:
    AsyncCoroutinePool(size_t maxCallbackPoints);
    ~AsyncCoroutinePool() {}

    void Go();

    struct PoolTask {
        Func func_;
        Func cb_;
    };

private:
    size_t maxCoroutineCount_;
    std::atomic<int> coroutineCount_{0};
    Scheduler* scheduler_;
    Channel<PoolTask> tasks_;
    std::atomic<size_t> pointsCount_{0};
    std::atomic<size_t> writePointsCount_{0};
    size_t maxCallbackPoints_;
    std::atomic<size_t> robin_{0};
    CallbackPoint ** points_;
    LFLock started_;
};

} // namespace co
