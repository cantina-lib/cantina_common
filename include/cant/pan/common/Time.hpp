//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_TIME_HPP
#define CANTINA_TIME_HPP

#pragma once

#include <chrono>

#include <cant/common/formatting.hpp>
#include <cant/common/macro.hpp>

#include <cant/pan/common/PantoufleException.hpp>
#include <cant/pan/common/types.hpp>

namespace cant::pan
{
   class Time
   {
   private:
       static std::chrono::time_point<std::chrono::steady_clock> tStart;
   public:
       static time_m getCurrentTime()
       {
           auto t = std::chrono::steady_clock::now();
           std::chrono::duration<time_m> dur = t - tStart;
           return dur.count() * 1000;
       }

       CANT_NODISCARD static time_m checkTime(time_m t)
       {
           if(t < 0)
           {
               throw PANTOUFLE_EXCEPTION(fmt::format("Starting time of {0} incorrect, expected positive value.", t));
           }
           return t;
       }
   };
}

#endif //CANTINA_TIME_HPP
