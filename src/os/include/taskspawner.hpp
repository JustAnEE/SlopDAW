#ifndef TASK_SPAWNER_HPP
#define TASK_SPAWNER_HPP

#include <thread>
#include <utility>

#include "taskbase.hpp"
#include "enums.hpp"
#include "tasktable.hpp"
#include "audioapptask.hpp"
#include "guitask.hpp"

template<TaskIDEnum>
struct TaskTypeAlias;

template<>
struct TaskTypeAlias<TaskIDEnum::APP_TASK>
{
   using TaskType = AudioAppTask;
};

template<>
struct TaskTypeAlias<TaskIDEnum::GUI_TASK>
{
   using TaskType = GUITask;
};


template<typename Task>
class TaskFactory
{
   public:
      static std::shared_ptr<Task> InstantiateTask();
};

template<typename Task>
std::shared_ptr<Task>
TaskFactory<Task>::InstantiateTask()
{
   static Task clTask = {};
   return std::shared_ptr<Task>(&clTask);
};

template<ULONG N, std::size_t... Idcs>
static constexpr const std::array<std::shared_ptr<TaskBase>, N>
SpawnTaskImplementation(std::index_sequence<Idcs...>)
{
   // Fill out the task array with a compile time for loop. If there's another way to do this,
   // this needs to be immediately replaced with something more readable.
   std::array<std::shared_ptr<TaskBase>, N> apclTasks = {};
   ((apclTasks[Idcs] = TaskFactory<typename TaskTypeAlias<TaskTable::GetTaskTable()[Idcs].eTask>::TaskType>::InstantiateTask()),...);
   return apclTasks;
}

template<ULONG N>
static constexpr const std::array<std::shared_ptr<TaskBase>, N>
SpawnTasks()
{
   return SpawnTaskImplementation<N>(std::make_index_sequence<N>{});
}


template<ULONG N = TaskTable::N>
class TaskSpawner 
{
   public:
      
      static void StartTasks()
      {
         std::vector<std::thread> vtTaskThreads;
         apclMyTasks = SpawnTasks<N>();
         for (std::shared_ptr<TaskBase>  pclTask_ : apclMyTasks)
         {
            pclTask_->InitTask();
            vtTaskThreads.emplace_back(
               &TaskBase::Main,
               pclTask_);
         }
         for (std::thread& tTaskThread_ : vtTaskThreads)
         {
            tTaskThread_.join();
         }
         return; 
      }

   public:
      
      // !TODO: std::optional
      template<typename T>
      static std::weak_ptr<T>
      GetSharedTaskHandle(TaskIDEnum eTask_)
      {
         std::weak_ptr<T> pclReturn;
         for(ULONG ulIdx = 0; ulIdx < TaskTable::N; ulIdx++)
         {
            if(TaskTable::GetTaskTable()[ulIdx].eTask == eTask_)
            {
               // yuck... maybe the task inheritance should be done 
               // through CRTP as well
               pclReturn = dynamic_pointer_cast<T>(apclMyTasks[ulIdx]); 
            }
         }
         return pclReturn; 
      }

   private:

      TaskSpawner() = default;
      ~TaskSpawner() = default;

   private:
      // Inline required 
      inline static std::array<std::shared_ptr<TaskBase>, N> apclMyTasks = {};
};

#endif 
