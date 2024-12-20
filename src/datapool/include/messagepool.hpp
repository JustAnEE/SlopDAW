#ifndef MESSAGE_POOL_HPP
#define MESSAGE_POOL_HPP

#include "types.hpp"
#include "templates.hpp"
#include <vector>
#include <mutex>

template<typename Data>
requires BasicConcepts::POD<Data>
class MessagePool
{
   private:

      struct RawMessage
      {
         RawMessage()
         {
            bAvailable = TRUE;
         }

         Data stData;
         BOOL bAvailable; // !TODO: Atomic ?? 
      };

      struct ReleaseRawMessage
      {
         ReleaseRawMessage()
         {
            pvMessagePoolRef = &vMessagePool;
            ulMessageIdx = 0;
            return;
         }
      
         void operator()(Data*) const noexcept
         {

            (*pvMessagePoolRef)[ulMessageIdx].bAvailable = TRUE;
            return;
         }
      
         std::vector<RawMessage>* pvMessagePoolRef;
         ULONG ulMessageIdx;
      };

   public:

      static BOOL
      AcquireDataImplementation(
         std::shared_ptr<Data>& pstAcquireData_)
      {
         // Critical Section
         {
            std::lock_guard<std::mutex> lock(mtxMyAcquireMutex);
            for (ULONG ulIdx = 0; ulIdx < vMessagePool.size(); ulIdx++)
            {
               if (vMessagePool[ulIdx].bAvailable)
               {
                  ReleaseRawMessage stRelease;
                  stRelease.ulMessageIdx = ulIdx;
                  vMessagePool[ulIdx].bAvailable = FALSE;

                  pstAcquireData_ = std::shared_ptr<Data>(&vMessagePool[ulIdx].stData, stRelease);
                  return TRUE; 
               }
            }
            return FALSE;
         }
      }

   private:

      // !TODO: Don't use a vector.
      static std::vector<RawMessage> vMessagePool;
      static std::mutex mtxMyAcquireMutex;

};

template<typename Data>
requires BasicConcepts::POD<Data>
std::vector<typename MessagePool<Data>::RawMessage> MessagePool<Data>::vMessagePool(25);

template<typename Data>
requires BasicConcepts::POD<Data>
std::mutex MessagePool<Data>::mtxMyAcquireMutex;




#endif 

