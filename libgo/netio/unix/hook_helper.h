#pragma once
#include "../../common/config.h"
#include <mutex>
#include "fd_context.h"
#include "../../common/spinlock.h"

namespace co {

struct NonBlockingGuard {
    explicit NonBlockingGuard(FdContextPtr const& fdCtx);
    ~NonBlockingGuard();

    FdContextPtr fdCtx_;
    bool isNonBlocking_;
};

class HookHelper
{
public:
    static const int kStaticFdSize = 128;
    static const int kBucketShift = 10;
    static const int kBucketCount = (1 << kBucketShift) - 1;

    struct FdSlot {
        FdContextPtr ctx_;
        LFLock lock_;
    };
    typedef std::shared_ptr<FdSlot> FdSlotPtr;

    static HookHelper& getInstance();

    FdContextPtr GetFdContext(int fd);

public:
    // 链変簺socket镄刢lose琛屼负hook涓嶅埌, 鍒涘缓镞跺鏋沧湁镞х殑context鐩存帴close鎺夊嵆鍙?
    void OnCreate(int fd, eFdType fdType, bool isNonBlocking = false,
            SocketAttribute sockAttr = SocketAttribute());

    // 鍦╯yscall涔嫔墠璋幂敤
    void OnClose(int fd);

    // 鍦╯yscall涔嫔悗璋幂敤
    void OnDup(int from, int to);

private:
    FdSlotPtr GetSlot(int fd);

    void Insert(int fd, FdContextPtr ctx);

private:
    typedef std::unordered_map<int, FdSlotPtr> Slots;
    Slots buckets_[kBucketCount+1];
    std::mutex bucketMtx_[kBucketCount+1];
};

} // namespace co
