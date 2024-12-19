#include "guitask.hpp"
#include "datapool.hpp"
#include "shutdownmessage.hpp"
#include "taskspawner.hpp"

BOOL 
GUITask::Init()
{
   // !TODO: This should be hidden from the user :)
   std::weak_ptr<GUITask> pclTaskHandle = TaskSpawner<TaskTable::N>::GetSharedTaskHandle<GUITask>(TaskIDEnum::GUI_TASK);
   if(pclTaskHandle.lock())
   {
      GetDataPoolInstance<ShutDownMessage>()->RegisterCallBack(&GUITask::RespondToShutDown, pclTaskHandle);
      return TRUE;
   }
   return FALSE;
}


void 
GUITask::Main()
{
   return;
}

void 
GUITask::RespondToShutDown(
   const std::shared_ptr<ShutDownMessage>& pstShutDown_)
{
   return;
}


