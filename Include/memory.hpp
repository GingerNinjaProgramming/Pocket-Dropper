// cpp
// File: `memory.cpp`
//
// Created by https://github.com/GingerNinjaProgramming on 16/11/2025.
//


#ifndef POCKET_DROPPER_MEMORY_HPP
#define POCKET_DROPPER_MEMORY_HPP
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace JSON {
    json loadData();
    json AmendScoreJson(int score);
}


#endif //POCKET_DROPPER_MEMORY_HPP