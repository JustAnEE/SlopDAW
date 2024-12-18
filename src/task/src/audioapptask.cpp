#include "audioapptask.hpp"
#include "shutdownmessage.hpp"
#include "taskspawner.hpp"
#include "datapool.hpp"
#include "tasktable.hpp"

BOOL 
AudioAppTask::Init()
{
   // !TODO: This should be hidden from the user :)
   std::weak_ptr<AudioAppTask> pclTaskHandle = TaskSpawner<TaskTable::N>::GetSharedTaskHandle<AudioAppTask>(TaskIDEnum::APP_TASK);

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

   return;
}
