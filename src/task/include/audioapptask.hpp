#ifndef AUDIO_APP_TASK_HPP
#define AUDIO_APP_TASK_HPP

#include "taskbase.hpp"

// Forward declarations 
struct ShutDownMessage;

class AudioAppTask 
   : public TaskBase
{
   public:
      
      AudioAppTask() = default;
      ~AudioAppTask() = default;

   public:


   private:

      BOOL Init() override;
      void RespondToShutDown(const std::shared_ptr<ShutDownMessage>& pstShutDown_) override;
};
#endif 

