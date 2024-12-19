#ifndef GUI_TASK_HPP
#define GUI_TASK_HPP

#include "taskbase.hpp"

// Forward declarations 
struct ShutDownMessage;

class GUITask 
   : public TaskBase
{
   public:

      GUITask() = default;
      ~GUITask() = default;
   
   public:
      // The GUI event loop is much more complicated, requires override
      void Main() override;

   private:

      BOOL Init() override;
      void RespondToShutDown(const std::shared_ptr<ShutDownMessage>& pstShutDown_) override;

};

#endif 
