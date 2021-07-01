#pragma once
#include <stdint.h>

class TimeSystem
{
public:
	TimeSystem();

	// ��һ֡ˢ��ʱ������ ����
	int64_t DeltaTime;


	int64_t NowServerMilliseconds();

	int64_t NowServerSeconds();



private:
	// ˢ�¸���ʱ��
	void RefreshLastTime();
private:
	// �ϴθ���ʱ��
	int64_t	m_last_time;

	friend class GameSystem;
};