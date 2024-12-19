#ifndef TASK_BASE_HPP
#define TASK_BASE_HPP
#include <memory>
#include "types.hpp" 
#include <atomic>

struct ShutDownMessage;
class TaskBase
{
   public:

      TaskBase()
      {
         bMyContinueRunning = TRUE;
         return;
      }

      virtual ~TaskBase() = default;

   public:

      // Default Main() behaviour is an empty while loop until bMyContinueRunning
      // is false. Child tasks are free to override this if they want.
      virtual void Main()
      {
         while(bMyContinueRunning){
         }
         return;
      }
      
      // Calls Init() from the child task, and handles any error.
      void InitTask()
      {
         Init();
         return;
      }

   protected:

      virtual void RespondToShutDown(const std::shared_ptr<ShutDownMessage>& pstShutDown_) = 0;
      virtual BOOL Init() = 0;
      
   protected:

      std::atomic<BOOL> bMyContinueRunning;

};


#endif 
