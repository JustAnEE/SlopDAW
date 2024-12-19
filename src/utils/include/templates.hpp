#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <functional>
#include <type_traits>
#include "types.hpp"

namespace BasicConcepts
{
   template<typename T> 
   concept POD = std::is_trivial_v<T>;
   
};

#endif 
