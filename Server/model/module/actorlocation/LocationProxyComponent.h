#pragma once
#include "etc/etc.h"


// 用于调用 Location app 接口，简化协议发送过程
class LocationProxyComponent:
	public Component
{
public:
	static LocationProxyComponent* Instance;

	void Add(const ID key, const InstanceID instance_id);
	
	void Lock(const ID key,const InstanceID instance_id,const time_t time);

	void UnLock(const ID key, const InstanceID old_instance_id, const InstanceID instance_id);

	void Remove(const ID key);

	InstanceID Get(const ID key);


	// 取出地址进程id
	static InstanceID GetLocationAppId(const InstanceID key);

};
