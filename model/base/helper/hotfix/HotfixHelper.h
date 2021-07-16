#pragma once
#include <memory>



namespace Model
{
	class Dll;


	// 全局变量
	struct stGlobalVar
	{
		class TypeFactory*			type_factory;
		class ISingletonFactory*	single_factory;
		class GlobalGame*			game;
		class GlobalData*			global_data;
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