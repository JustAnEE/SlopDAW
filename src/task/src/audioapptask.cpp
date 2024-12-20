#include "audioapptask.hpp"
#include "shutdownmessage.hpp"
#include "taskspawner.hpp"
#include "datapool.hpp"

BOOL 
AudioAppTask::Init()
{
   // !TODO: This should be hidden from the user :)
   std::weak_ptr<AudioAppTask> pclTaskHandle = TaskSpawner::GetSharedTaskHandle<AudioAppTask>(TaskIDEnum::APP_TASK);
   if(pclTaskHandle.lock())
   {
      GetDataPoolInstance<ShutDownMessage>()->RegisterCallBack(&AudioAppTask::RespondToShutDown, pclTaskHandle);
   }

   return FALSE;
}

void 
AudioAppTask::RespondToShutDown(
   const std::shared_ptr<ShutDownMessage>& pstShutDown_)
{
   bMyContinueRunning = !pstShutDown_->bShutDown;
   return;
}

