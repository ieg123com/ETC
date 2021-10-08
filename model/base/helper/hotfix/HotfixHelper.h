#pragma once
#include <memory>



namespace Model
{
	namespace async {
		class Scheduler;
	}
	class Dll;
	class IdGenerator;



	// 全局变量
	struct stGlobalVar
	{
		class TypeFactory*			type_factory;
		class ISingletonFactory*	single_factory;
		class GlobalGame*			game;
		class GlobalData*			global_data;
		IdGenerator*				id_generator;
		async::Scheduler*			async_scheduler;
		class ThreadSynchronizationContext*	thread_synchronization_context;
	};


	class Hotfix
	{
	public:
		Hotfix();
		~Hotfix();

		void Load(const char* path);

		void Clear();


	public:

		void Awake();

		void Init(const stGlobalVar& global);

		void Destroy();

	private:

		std::shared_ptr<Dll> m_dll;

		void* m_awake;
		void* m_init;
		void* m_destroy;


	};





}