#pragma once
#include "../common/config.h"
#include "../common/deque.h"
#include "../common/spinlock.h"
#include "../common/timer.h"
#include "../task/task.h"
#include "../debug/listener.h"
#include "processer.h"
#include <mutex>

namespace co {

struct TaskOpt
{
    bool affinity_ = false;
    int lineno_ = 0;
    std::size_t stack_size_ = 0;
    const char* file_ = nullptr;
};

// 鍗忕▼璋冨害鍣?
// 璐熻矗绠＄悊1鍒癗涓皟搴︾嚎绋? 璋冨害浠庡睘鍗忕▼.
// 鍙互璋幂敤Create鎺ュ彛鍒涘缓镟村棰濆镄勮皟搴﹀櫒
class Scheduler
{
    friend class Processer;

public:
    ALWAYS_INLINE static Scheduler& getInstance();

    static Scheduler* Create();

    // 鍒涘缓涓€涓岗绋?
    void CreateTask(TaskF const& fn, TaskOpt const& opt);

    // 褰揿墠鏄惁澶勪簬鍗忕▼涓?
    bool IsCoroutine();

    // 鏄惁娌℃湁鍗忕▼鍙墽琛?
    bool IsEmpty();

    // 鍚姩璋冨害鍣?
    // @minThreadNumber : 链€灏忚皟搴︾嚎绋嬫暟, 涓?镞? 璁剧疆涓篶pu镙稿绩鏁?
    // @maxThreadNumber : 链€澶ц皟搴︾嚎绋嬫暟, 涓?镞? 璁剧疆涓簃inThreadNumber.
    //          濡傛灉maxThreadNumber澶т簬minThreadNumber, 鍒椤綋鍗忕▼浜х敓闀挎椂闂撮樆濉炴椂,
    //          鍙互镊姩镓╁睍璋冨害绾跨▼鏁?
    void Start(int minThreadNumber = 1, int maxThreadNumber = 0);
    void goStart(int minThreadNumber = 1, int maxThreadNumber = 0);
    static const int s_ulimitedMaxThreadNumber = 40960;

    // 锅沧璋冨害 
    // 娉ㄦ剰: 锅沧鍚庢棤娉曟仮澶? 浠呯敤浜庡畨鍏ㄩ€€鍑簃ain鍑芥暟, 涓崭缭璇佺粓姝㈡墍链夌嚎绋?
    //       濡傛灉镆愪釜璋冨害绾跨▼琚岗绋嬮樆濉? 蹇呴』绛夊緟阒诲缁撴潫镓嶈兘阃€鍑?
    void Stop();

    // 浣跨敤镫珛镄勫畾镞跺櫒绾跨▼
    void UseAloneTimerThread();

    // 褰揿墠璋冨害鍣ㄤ腑镄勫岗绋嬫暟閲?
    uint32_t TaskCount();

    // 褰揿墠鍗忕▼ID, ID浠?寮€濮嬶纸涓嶅湪鍗忕▼涓垯杩斿洖0锛?
    uint64_t GetCurrentTaskID();

    // 褰揿墠鍗忕▼鍒囨崲镄勬鏁?
    uint64_t GetCurrentTaskYieldCount();

    // 璁剧疆褰揿墠鍗忕▼璋冭瘯淇℃伅, 镓揿嵃璋冭瘯淇℃伅镞跺皢锲炴樉
    void SetCurrentTaskDebugInfo(std::string const& info);

    typedef Timer<std::function<void()>> TimerType;

public:
    inline TimerType & GetTimer() { return timer_ ? *timer_ : StaticGetTimer(); }

    inline bool IsStop() { return stop_; }

    static bool& IsExiting();

private:
    Scheduler();
    ~Scheduler();

    Scheduler(Scheduler const&) = delete;
    Scheduler(Scheduler &&) = delete;
    Scheduler& operator=(Scheduler const&) = delete;
    Scheduler& operator=(Scheduler &&) = delete;

    static void DeleteTask(RefObject* tk, void* arg);

    // 灏嗕竴涓岗绋嫔姞鍏ュ彲镓ц阒熷垪涓?
    void AddTask(Task* tk);

    // dispatcher绾跨▼鍑芥暟
    // 1.镙规嵁寰呮墽琛屽岗绋嬭绠楄礋杞? 灏嗛佩璐熻浇镄凯涓殑鍗忕▼steal涓€浜涚粰绌鸿浇镄凯
    // 2.渚︽祴鍒伴樆濉炵殑P(鍗曚釜鍗忕▼杩愯镞堕棿瓒呰绷阒€链?, 灏哖涓殑鍏朵粬鍗忕▼steal缁椤叾浠朠
    void DispatcherThread();

    void NewProcessThread();

    TimerType & StaticGetTimer();

    // deque of Processer, write by start or dispatch thread
    Deque<Processer*> processers_;

    LFLock started_;

    atomic_t<uint32_t> taskCount_{0};

    volatile uint32_t lastActive_ = 0;

    TimerType *timer_ = nullptr;
    
    int minThreadNumber_ = 1;
    int maxThreadNumber_ = 1;

    std::thread dispatchThread_;

    std::thread timerThread_;

    std::mutex stopMtx_;

    bool stop_ = false;
};

} //namespace co

#define g_Scheduler ::co::Scheduler::getInstance()

namespace co
{
    ALWAYS_INLINE Scheduler& Scheduler::getInstance()
    {
        static Scheduler obj;
        return obj;
    }

} //namespace co
