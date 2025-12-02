// cpp
// File: `memory.cpp`
//
// Created by https://github.com/GingerNinjaProgramming on 16/11/2025.
//

#include "memory.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "constants.hpp"
using json = nlohmann::json;

namespace JSON {
    void saveData(const json& data) {
        std::ofstream file(SAVE_FILE);
        if (!file.is_open()) {
            std::cerr << "Error: cannot write to file!\n";
            return;
        }
        file << data.dump(4);
        file.close();
    }

    json AmendScoreJson(int score) {
        json data = { {"Score", score} };
        saveData(data);
        return data;
    }

    json loadData() {
        std::ifstream file(SAVE_FILE);
        if (!file.is_open()) {
            std::cout << "No save file found, creating a new one.\n";
            json data = { {"Score", 0} };
            std::ofstream out(SAVE_FILE);
            out << data.dump(4);
            out.close();
            return data;
        }

        json data;
        try {
            file >> data;
        } catch (const nlohmann::json::exception &e) {
            std::cerr << "Failed to parse save file: " << e.what() << "\n";
            file.close();
            json fallback = { {"Score", 0} };
            saveData(fallback);
            return fallback;
        }
        file.close();

        // Normalize array-shaped saves into an object with "Score"
        if (data.is_array()) {
            if (data.empty()) {
                data = json{ {"Score", 0} };
            } else if (data[0].is_object() && data[0].contains("Score")) {
                data = data[0];
            } else {
                bool found = false;
                for (const auto &el : data) {
                    if (el.is_object() && el.contains("Score")) {
                        data = el;
                        found = true;
                        break;
                    }
                }
                if (!found) data = json{ {"Score", 0} };
            }
            // Persist normalized form
            saveData(data);
        }

        return data;
    }
}