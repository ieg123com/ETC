#pragma once
#include "etc/etc.h"


// 用于调用 Location app 接口，简化协议发送过程
class LocationProxyComponent:
	public Component
{
public:
	static LocationProxyComponent* Instance;

	void Add(const int64_t key, const int64_t instance_id);
	
	void Lock(const int64_t key,const int64_t instance_id,const int32_t time);

	void UnLock(const int64_t key, const int64_t old_instance_id, const int64_t instance_id);

	void Remove(const int64_t key);

	int64_t Get(const int64_t key);


	// 取出地址进程id
	static InstanceID GetLocationAppId(const int64_t key);

};
