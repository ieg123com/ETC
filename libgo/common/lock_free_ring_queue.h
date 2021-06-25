#pragma once
#include <atomic>
#include <limits>

namespace co {

struct LockFreeResult {
    bool success = false;
    bool notify = false;
};

// 镞犻挛鐜舰阒熷垪
template <typename T, typename SizeType = size_t>
class LockFreeRingQueue
{
public:
    typedef SizeType uint_t;
    typedef std::atomic<uint_t> atomic_t;

    // 澶氱敌璇蜂竴涓猼ypename T镄勭┖闂? 渚夸簬鍒ゆ柇full鍜宔mpty.
    explicit LockFreeRingQueue(uint_t capacity)
        : capacity_(reCapacity(capacity))
        , readable_{0}
        , write_{0}
        , read_{0}
        , writable_{uint_t(capacity_ - 1)}
    {
        buffer_ = (T*)malloc(sizeof(T) * capacity_);
    }

    ~LockFreeRingQueue() {
        // destory elements.
        uint_t read = consume(read_);
        uint_t readable = consume(readable_);
        for (; read < readable; ++read) {
            buffer_[read].~T();
        }

        free(buffer_);
    }

    template <typename U>
    LockFreeResult Push(U && t) {
        LockFreeResult result;

        // 1.write_姝ヨ繘1.
        uint_t write, writable;
        do {
            write = relaxed(write_);
            writable = consume(writable_);
            if (write == writable)
                return result;

        } while (!write_.compare_exchange_weak(write, mod(write + 1),
                    std::memory_order_acq_rel, std::memory_order_relaxed));

        // 2.鏁版嵁鍐椤叆
        new (buffer_ + write) T(std::forward<U>(t));

        // 3.镟存柊readable
        uint_t readable;
        do {
            readable = relaxed(readable_);
        } while (!readable_.compare_exchange_weak(write, mod(readable + 1),
                    std::memory_order_acq_rel, std::memory_order_relaxed));

        // 4.妫€镆ュ啓鍏ユ椂鏄惁empty
        result.notify = (write == mod(writable + 1));
        result.success = true;
        return result;
    }

    LockFreeResult Pop(T & t) {
        LockFreeResult result;

        // 1.read_姝ヨ繘1.
        uint_t read, readable;
        do {
            read = relaxed(read_);
            readable = consume(readable_);
            if (read == readable)
                return result;

        } while (!read_.compare_exchange_weak(read, mod(read + 1),
                    std::memory_order_acq_rel, std::memory_order_relaxed));

        // 2.璇绘暟鎹?
        t = std::move(buffer_[read]);
        buffer_[read].~T();

        // 3.镟存柊writable
        // update condition: mod(writable_ + 1) == read_
        //               as: writable_ == mod(read_ + capacity_ - 1)
        uint_t check = mod(read + capacity_ - 1);
        while (!writable_.compare_exchange_weak(check, read,
                    std::memory_order_acq_rel, std::memory_order_relaxed));

        // 4.妫€镆ヨ鍙栨椂鏄惁full
        result.notify = (read == mod(readable_ + 1));
        result.success = true;
        return result;
    }

private:
    inline uint_t relaxed(atomic_t & val) {
        return val.load(std::memory_order_relaxed);
    }

    inline uint_t acquire(atomic_t & val) {
        return val.load(std::memory_order_acquire);
    }

    inline uint_t consume(atomic_t & val) {
        return val.load(std::memory_order_consume);
    }

    inline uint_t mod(uint_t val) {
        return val % capacity_;
    }

    inline size_t reCapacity(uint_t capacity) {
        return (size_t)capacity + 1;
    }

private:
    size_t capacity_;
    T* buffer_;

    // [write_, writable_] 鍙啓鍖洪棿, write_ == writable_ is full.
    // read鍚庢洿鏂皐ritable
    atomic_t write_;
    atomic_t writable_;

    // [read_, readable_) 鍙鍖洪棿, read_ == readable_ is empty.
    // write鍚庢洿鏂皉eadable
    atomic_t read_;
    atomic_t readable_;
};

} // namespace co
