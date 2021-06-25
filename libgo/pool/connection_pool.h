#pragma once
#include "../common/config.h"
#include "../common/clock.h"
#include "../sync/channel.h"

namespace co {

// 杩炴帴姹?
// @typename Connection: 杩炴帴绫诲瀷
template <typename Connection>
class ConnectionPool
{
public:
    typedef std::shared_ptr<Connection> ConnectionPtr;
    typedef std::function<Connection*()> Factory;
    typedef std::function<void(Connection*)> Deleter;
    typedef std::function<bool(Connection*)> CheckAlive;

    // @Factory: 鍒涘缓杩炴帴镄勫伐铡?
    // @Deleter: 阌€姣佽繛鎺? 浼犻€扤ULL镞朵细浣跨敤delete鍒犻櫎杩炴帴.
    // @maxConnection: 链€澶ц繛鎺ユ暟, 0琛ㄧず涓嶉檺鏁伴噺
    // @maxIdleConnection: 链€澶х┖闂茶繛鎺ユ暟, 0琛ㄧず涓嶉檺鏁伴噺
    // 娉ㄦ剰锛欶actory鍜娈eleter镄勮皟鐢ㄥ彲鑳戒细骞惰.
    explicit ConnectionPool(Factory f, Deleter d = NULL, size_t maxConnection = 0, size_t maxIdleConnection = 0)
        : factory_(f), deleter_(d), count_(0),
        maxConnection_(maxConnection),
        maxIdleConnection_(maxIdleConnection == 0 ? maxConnection : maxIdleConnection),
        channel_(maxIdleConnection_)
    {
        if (maxIdleConnection_ == 0)
            maxIdleConnection_ = maxConnection_;

        if (!deleter_) {
            deleter_ = [](Connection * ptr){ delete ptr; };
        }
    }

    ~ConnectionPool()
    {
        Connection* ptr = nullptr;
        while (channel_.TryPop(ptr)) {
            Delete(ptr);
        }
    }

    // 棰勫垱寤轰竴浜涜繛鎺?
    // @nConnection: 杩炴帴鏁伴噺, 澶т簬maxIdleConnection_镄勯儴鍒嗘棤鏁?
    void Reserve(size_t nConnection)
    {
        for (size_t i = Count(); i < maxIdleConnection_; ++i)
        {
            Connection* connection = CreateOne();
            if (!connection) break;
            if (!channel_.TryPush(connection)) {
                Delete(connection);
                break;
            }
        }
    }

    // 銮峰彇涓€涓繛鎺?
    // 濡傛灉姹犵┖浜嗗苟涓旇繛鎺ユ暟杈惧埌涓婇檺, 鍒欎细绛夊緟
    // 杩斿洖镄勬櫤鑳芥寚阍堥攒姣佹椂, 浼氲嚜锷ㄥ皢杩炴帴褰掕缮缁欐睁
    ConnectionPtr Get(CheckAlive checkAliveOnGet = NULL,
            CheckAlive checkAliveOnPut = NULL)
    {
        Connection* connection = nullptr;
retry_get:
        if (channel_.TryPop(connection)) {
            if (checkAliveOnGet && !checkAliveOnGet(connection)) {
                Delete(connection);
                connection = nullptr;
                goto retry_get;
            }

            return Out(connection, checkAliveOnPut);
        }

        connection = CreateOne();
        if (connection)
            return Out(connection, checkAliveOnPut);

        channel_ >> connection;
        if (checkAliveOnGet && !checkAliveOnGet(connection)) {
            Delete(connection);
            connection = nullptr;
            goto retry_get;
        }

        return Out(connection, checkAliveOnPut);
    }

    // 銮峰彇涓€涓繛鎺?
    // 濡傛灉姹犵┖浜嗗苟涓旇繛鎺ユ暟杈惧埌涓婇檺, 鍒欎细绛夊緟
    // 杩斿洖镄勬櫤鑳芥寚阍堥攒姣佹椂, 浼氲嚜锷ㄥ皢杩炴帴褰掕缮缁欐睁
    //
    // @timeout: 绛夊緟瓒呮椂镞堕棿, 浠呭湪鍗忕▼涓湁鏁? 渚? std::chrono::seconds(1)
    // @checkAliveOnGet: 鐢宠镞舵镆ヨ繛鎺ユ槸鍚﹁缮链夋晥
    // @checkAliveOnPut: 褰掕缮镞舵镆ヨ繛鎺ユ槸鍚﹁缮链夋晥
    ConnectionPtr Get(FastSteadyClock::duration timeout,
            CheckAlive checkAliveOnGet = NULL,
            CheckAlive checkAliveOnPut = NULL)
    {
        FastSteadyClock::time_point deadline = FastSteadyClock::now() + timeout;
        Connection* connection = nullptr;
retry_get:
        if (channel_.TryPop(connection)) {
            if (checkAliveOnGet && !checkAliveOnGet(connection)) {
                Delete(connection);
                connection = nullptr;
                goto retry_get;
            }

            return Out(connection, checkAliveOnPut);
        }

        connection = CreateOne();
        if (connection)
            return Out(connection, checkAliveOnPut);

        if (channel_.TimedPop(connection, deadline)) {
            if (checkAliveOnGet && !checkAliveOnGet(connection)) {
                Delete(connection);
                connection = nullptr;
                goto retry_get;
            }

            return Out(connection, checkAliveOnPut);
        }

        return ConnectionPtr();
    }

    size_t Count()
    {
        return count_;
    }

private:
    Connection* CreateOne()
    {
        if (++count_ > maxConnection_) {
            --count_;
            return nullptr;
        }

        return factory_();
    }

    void Put(Connection* connection)
    {
        if (!channel_.TryPush(connection)) {
            Delete(connection);
        }
    }

    void Delete(Connection* connection)
    {
        --count_;
        deleter_(connection);
    }

    ConnectionPtr Out(Connection* connection, CheckAlive checkAliveOnPut)
    {
        return ConnectionPtr(connection, [this, checkAliveOnPut](Connection* ptr){
                    if (checkAliveOnPut && !checkAliveOnPut(ptr)) {
                        this->Delete(ptr);
                        return ;
                    }

                    this->Put(ptr);
                });
    }

private:
    Factory factory_;
    Deleter deleter_;
    std::atomic<size_t> count_;
    size_t maxConnection_;
    size_t maxIdleConnection_;
    Channel<Connection*> channel_;
};

} // namespace co
