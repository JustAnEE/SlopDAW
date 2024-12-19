#ifndef TASK_TABLE_HPP
#define TASK_TABLE_HPP
#include "enums.hpp"
#include "types.hpp"
#include <array>

namespace TaskTable
{
   // Number of tasks 
   static constexpr const ULONG N = 2;

   struct TaskEntry
   {
      TaskIDEnum eTask;
      TaskPriorityEnum ePriority;
   };

   static constexpr const std::array<TaskEntry, N>
   astTheTaskTable = 
   {
      {
         {TaskIDEnum::GUI_TASK, TaskPriorityEnum::MEDIUM_PRIORITY},
         {TaskIDEnum::APP_TASK, TaskPriorityEnum::MEDIUM_PRIORITY}
      }
   };

   static constexpr const std::array<TaskEntry, N>
   GetTaskTable()
   {
      return astTheTaskTable;
   }
};
#endif 
