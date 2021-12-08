#pragma once
#include <memory>
#include <functional>
#include "base/GlobalData.h"
#include "coroutine.h"

namespace Model
{
	namespace async
	{



		inline void fake_void_to_void(const std::shared_ptr<void>&){}

		template<typename T>
		inline T fake_void_to_void(const std::shared_ptr<T>& t_ptr) {
			return *t_ptr;
		}

		inline void run_fake_void_to_void(const std::function<void()>& func, std::shared_ptr<void>& result) {
			func();
		}

		template<typename T>
		inline void run_fake_void_to_void(const std::function<T()>& func, std::shared_ptr<T>& result) {
			result = std::make_shared<T>(std::move(func()));
		}

		enum class TaskState : uint8_t
		{
			None,		// 空的任务
			Pending,	// 等待执行中
			UnWrapped,	// 正在执行中
			Completed,	// 任务执行完毕，有结果
			Canceled,	// 任务取消，有异常
		};

		class BaseTask
		{
			friend class Scheduler;
		public:
			BaseTask():__Channel(1) {
				__Id = Model::GlobalData::GetAsyncTaskId();
				__State = TaskState::None;
			}

			// 查询是否处理完成
			bool ready() const {
				return (__State == TaskState::Completed || __State == TaskState::Canceled) ? true : false;
			}

			// 查询任务是否被取消，可是中途发生异常
			bool canceled() const {
				return (__State == TaskState::Canceled) ? true : false;
			}

			// 等待这个任务执行完毕
			template <typename Rep, typename Period>
			bool wait(std::chrono::duration<Rep, Period> dur) {
				if (__State == TaskState::None)return false;
				if (ready())return true;
				TaskState task_state = TaskState::None;
				return __Channel.TimedPop(task_state, dur);
			}

			TaskState task_state() const {
				return __State;
			}

			void cancel() {
				__State = TaskState::Canceled;
				__Exception = "Task is cancelled";
			}

			std::string exception()const {
				return __Exception;
			}
			// 执行这个任务
			virtual void run() = 0;

		protected:
			// 任务id
			int64_t	__Id;
			// 任务状态
			TaskState	__State;

			std::string	__Exception;

			co::Channel<TaskState> __Channel;
		};



		template<typename Result>
		class Task :
			public BaseTask
		{
		public:


			virtual void run()override {
				if (__State != TaskState::Pending)return;

				// 设置这个任务正在执行中
				__State = TaskState::UnWrapped;

				try {
					run_fake_void_to_void(__InternalTask, __Result);
					__State = TaskState::Completed;
				}
				catch (std::exception& e) {
					__Exception = e.what();
					__State = TaskState::Canceled;
				}
				catch (...) {
					__Exception = "Unknown error";
					__State = TaskState::Canceled;
				}

				__Channel.TryPush(__State);
			}

			Result get() {
				return fake_void_to_void(__Result);
			}

			template<typename T>
			void __SetTask(T&& task) {
				__InternalTask = std::move(task);
			}

		private:
			// 回复的结果
			std::shared_ptr<Result>	__Result;
			// 需要做的任务
			std::function<Result()>	__InternalTask;
		};


	}
}