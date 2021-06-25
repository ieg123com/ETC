#pragma once
#include "../common/config.h"
#include "../common/spinlock.h"
#include "../common/util.h"
#include <deque>
#include <mutex>
#include <map>
#include <vector>
#include <unordered_set>

#if defined(__GNUC__)
#include <cxxabi.h>
#include <stdlib.h>
#endif 

namespace co
{

// libgo璋冭瘯宸ュ叿
class CoDebugger
{
public:
    template <typename T>
    class DebuggerBase
#if ENABLE_DEBUGGER
        : public ObjectCounter<T>
    {
    public:
        typedef DebuggerBase<T> this_type;
        typedef std::unordered_set<this_type*> DbgMap;

    protected:
        DebuggerBase() {
            std::unique_lock<std::mutex> lock(GetLock());
            GetDbgMap().insert(this);
        }

        virtual ~DebuggerBase() {
            std::unique_lock<std::mutex> lock(GetLock());
            GetDbgMap().erase(this);
        }

        static DbgMap& GetDbgMap() {
            static DbgMap obj;
            return obj;
        }

        static std::mutex& GetLock() {
            static std::mutex obj;
            return obj;
        }

    public:
        static std::shared_ptr<DbgMap> SafeGetDbgMap() {
            GetLock().lock();
            return std::shared_ptr<DbgMap>(&GetDbgMap(), [](DbgMap*){
                        GetLock().unlock();
                    });
        }
    };
#else
    {
        ALWAYS_INLINE void Initialize() {}
    };
#endif

public:
    static CoDebugger& getInstance();

    // 銮峰彇褰揿墠镓€链変俊鎭?
    std::string GetAllInfo();

    // 褰揿墠鍗忕▼镐绘暟閲?
    int TaskCount();

    // 褰揿墠鍗忕▼ID, ID浠?寮€濮嬶纸涓嶅湪鍗忕▼涓垯杩斿洖0锛?
    unsigned long GetCurrentTaskID();

    // 褰揿墠鍗忕▼鍒囨崲镄勬鏁?
    unsigned long GetCurrentTaskYieldCount();

    // 璁剧疆褰揿墠鍗忕▼璋冭瘯淇℃伅, 镓揿嵃璋冭瘯淇℃伅镞跺皢锲炴樉
    void SetCurrentTaskDebugInfo(std::string const& info);

    // 銮峰彇褰揿墠鍗忕▼镄勮皟璇曚俊鎭? 杩斿洖镄勫唴瀹瑰寘鎷敤鎴疯嚜瀹氢箟镄勪俊鎭拰鍗忕▼ID
    const char* GetCurrentTaskDebugInfo();

private:
    CoDebugger() = default;
    ~CoDebugger() = default;
    CoDebugger(CoDebugger const&) = delete;
    CoDebugger& operator=(CoDebugger const&) = delete;
};

template <typename T>
struct real_typename_helper {};

template <typename T>
std::string real_typename()
{
#if defined(__GNUC__)
    /// gcc.
    int s;
    char * realname = abi::__cxa_demangle(typeid(real_typename_helper<T>).name(), 0, 0, &s);
    std::string result(realname);
    free(realname);
#else
    std::string result(typeid(real_typename_helper<T>).name());
#endif 
    std::size_t start = result.find_first_of('<') + 1;
    std::size_t end = result.find_last_of('>');
    return result.substr(start, end - start);
}

} //namespace co
