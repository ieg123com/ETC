#pragma once
#include <exception>

namespace co
{

class Listener
{
public:
    /**
     * 鍗忕▼浜嬩欢鐩戝惉鍣?
     * 娉ㄦ剰锛氩叾涓墍链夌殑锲炶皟鏂规硶閮戒笉鍏佽鎶涘嚭寮傚父
     */
    class TaskListener {
    public:
        /**
         * 鍗忕▼琚垱寤烘椂琚皟鐢?
         * 锛堟敞镒忔镞跺苟链繍琛屽湪鍗忕▼涓级
         *
         * @prarm task_id 鍗忕▼ID
         * @prarm eptr
         */
        virtual void onCreated(uint64_t task_id) noexcept {
        }
        
        /**
         * 姣忔鍗忕▼鍒囧叆鍓嶈皟鐢?
         * 锛堟敞镒忔镞跺苟链繍琛屽湪鍗忕▼涓级
         *
         * @prarm task_id 鍗忕▼ID
         * @prarm eptr
         */
        virtual void onSwapIn(uint64_t task_id) noexcept {
        }

        /**
         * 鍗忕▼寮€濮嬭繍琛?
         * 锛堟湰鏂规硶杩愯鍦ㄥ岗绋嬩腑锛?
         *
         * @prarm task_id 鍗忕▼ID
         * @prarm eptr
         */
        virtual void onStart(uint64_t task_id) noexcept {
        }

        /**
         * 姣忔鍗忕▼鍒囧嚭鍓嶈皟鐢?
         * 锛堟湰鏂规硶杩愯鍦ㄥ岗绋嬩腑锛?
         *
         * @prarm task_id 鍗忕▼ID
         * @prarm eptr
         */
        virtual void onSwapOut(uint64_t task_id) noexcept {
        }
        
        /**
         * 鍗忕▼姝ｅ父杩愯缁撴潫锛堟棤寮傚父鎶涘嚭锛?
         * 锛堟湰鏂规硶杩愯鍦ㄥ岗绋嬩腑锛?
         *
         * @prarm task_id 鍗忕▼ID
         */
        virtual void onCompleted(uint64_t task_id) noexcept {
        }

        /**
         * 鍗忕▼鎶涘嚭链鎹曡幏镄勫纾甯革纸链柟娉曡繍琛屽湪鍗忕▼涓级
         * @prarm task_id 鍗忕▼ID
         * @prarm eptr 鎶涘嚭镄勫纾甯稿璞℃寚阍堬紝鍙链寚阍堣祴链间互淇敼寮傚父瀵硅薄锛?
         *             寮傚父灏嗕娇鐢?CoroutineOptions.exception_handle 涓?
         *             閰岖疆镄勬柟寮忓鐞嗭绂璧嫔€间负nullptr鍒栾〃绀哄拷鐣ユ寮傚父
         *             锛侊紒娉ㄦ剰锛氩綋 exception_handle 閰岖疆涓?immedaitely_throw 镞舵湰浜嬩欢
         *             锛侊紒涓?onFinished() 鍧囧け鏁堬紝寮傚父鍙戠敓镞跺皢鐩存帴鎶涘嚭骞朵腑鏂▼搴忕殑杩愯锛屽悓镞剁敓鎴恈oredump
         */
        virtual void onException(uint64_t task_id, std::exception_ptr& eptr) noexcept {
        }

        /**
         * 鍗忕▼杩愯瀹屾垚锛宨f(eptr) 涓篺alse璇存槑鍗忕▼姝ｅ父缁撴潫锛屼负true璇存槑鍗忕▼鎶涘嚭浜嗕简寮傚父
         *锛堟湰鏂规硶杩愯鍦ㄥ岗绋嬩腑锛?
         *
         * @prarm task_id 鍗忕▼ID
         */
        virtual void onFinished(uint64_t task_id) noexcept {
        }

        virtual ~TaskListener() noexcept = default;

        // s: Scheduler锛岃〃绀鸿鏂规硶杩愯鍦ㄨ皟搴﹀櫒涓娄笅鏂囦腑
        // c: Coroutine锛岃〃绀鸿鏂规硶杩愯鍦ㄥ岗绋嬩笂涓嬫枃涓?
        //
        //                                           -->[c]onCompleted->
        //                                          |                   |
        // [s]onCreated-->[s]onSwapIn-->[c]onStart->*--->[c]onSwapOut-- -->[c]onFinished-->[c]onSwapOut
        //                                          |\                | |
        //                                          | \<-[s]onSwapIn--V |
        //                                          |                   |
        //                                           -->[c]onException->
    };

public:
#if ENABLE_DEBUGGER
    ALWAYS_INLINE static TaskListener*& GetTaskListener() {
        static TaskListener* task_listener = nullptr;
        return task_listener;
    }

    static void SetTaskListener(TaskListener* listener) {
        GetTaskListener() = listener;
    }
#endif
};

} // namespace co
