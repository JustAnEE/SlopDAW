#ifndef DATA_POOL_HPP
#define DATA_POOL_HPP

#include "messagepool.hpp"
#include <vector>

template<typename Data> 
struct CallBackTypeAlias 
{
   using TaskCallBackType = std::function<void(const std::shared_ptr<Data>&)>; 
};

template<typename Data> 
struct CallBackStruct 
{
    CallBackTypeAlias<Data>::TaskCallBackType fpCallBack;
};

template<typename Data> 
requires BasicConcepts::POD<Data>
std::vector<CallBackStruct<Data>>&
GetCallBackVectorInstance()
{
   //!TODO: Don't use a vector 
   static std::vector<CallBackStruct<Data>> vTheCallBacks;
   return vTheCallBacks;
}

template<typename ImplType>
class DataPool
{
   public: 
      template<typename Data, typename Task>
      static void RegisterCallBack(
         void (Task::* fpCallBack_)(const std::shared_ptr<Data>&),
         std::weak_ptr<Task>& pclTask_)
      {
         ImplType::RegisterCallBackImplementation(fpCallBack_, pclTask_);
         return;
      }

      template<typename Data>
      static void Publish(
         const std::shared_ptr<Data>& pstData_)
      {
         ImplType::PublishImplementation(pstData_);
         return;
      }
      
      template<typename Data>
      static BOOL Acquire(
         std::shared_ptr<Data>& pstData_)
      {
         return MessagePool<Data>::AcquireDataImplementation(pstData_);
      }
   
   protected:
      
      template<typename Data>
      static void IvokeCallBacks(
         const std::shared_ptr<Data>& pstData_)
      {
         ImplType::InvokeCallBacksImplementation(pstData_);
         return;
      }

}; 

template<typename Data>
requires BasicConcepts::POD<Data>
class DataPoolPOD : 
   public DataPool<DataPoolPOD<Data>>
{
   public:
      
      template<typename Task>
      static void RegisterCallBackImplementation(
         void (Task::* fpCallBack_)(const std::shared_ptr<Data>&),
         std::weak_ptr<Task>& pclTask_) 
      {
         // !TODO: std::function objects created from binding a method to an instance of an object
         // do not have a targetmethod :) Might need to store a vector of the raw function pointer 
         // addresses. 
         //using CallBackType = CallBackTypeAlias<Data>::TaskCallBackType;
         //for (auto fpCallBack : GetCallBackVectorInstance<Data>())
         //{
         //   CallBackType fpNewCallBack = std::bind(fpCallBack_, clTask_, std::placeholders::_1);
         //   if ( fpCallBack.target<CallBackType>() == fpNewCallBack.target<CallBackType>() )
         //   {
         //      // Do not register the same callback twice. It's fine to just loop over everything,
         //      // this code should never be called after the multitasking starts.
         //      return;
         //   }
         //}

         GetCallBackVectorInstance<Data>().emplace_back(
            std::bind(fpCallBack_, 
                      pclTask_.lock(), 
                      std::placeholders::_1) // Placeholder for std::shared_ptr<Data>& reference
         );
         return;
      }
      
      static void PublishImplementation(
         const std::shared_ptr<Data>& pstData_)
      {
         // For POD types, we can just fire off the callbacks without much 
         // worry
         InvokeCallBacksImplementation(pstData_);
         return;
      }
      
      static void InvokeCallBacksImplementation(
         const std::shared_ptr<Data>& pstData_)
      {
         std::lock_guard<std::mutex> lock(mtxMyCallBackMutex);
         for(auto& laCallBack : GetCallBackVectorInstance<Data>())
         {
            laCallBack.fpCallBack(pstData_);
         }
         return;
      }

   private:
      static std::mutex mtxMyCallBackMutex;
};
template<typename Data>
requires BasicConcepts::POD<Data>
std::mutex DataPoolPOD<Data>::mtxMyCallBackMutex;


// !TODO: Make this a member of the DataPool interface.
template<typename Data>
requires BasicConcepts::POD<Data>
const DataPoolPOD<Data>* GetDataPoolInstance()
{
   static DataPoolPOD<Data> clTheDataPoolPOD;
   return &clTheDataPoolPOD;
}


#endif 
