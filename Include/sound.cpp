//
// Created by conne on 26/10/2025.
//

#include "sound.hpp"

#include <iostream>
#include <ostream>
#include <raylib.h>
#include <unordered_map>



namespace Sounds {
    std::unordered_map<SoundType, SoundCollection> loadedSounds;

    void LoadSound(char* filePath, SoundType type) {
        Sound sound = ::LoadSound(filePath);

        if (loadedSounds.contains(type)) {
            SoundCollection cur = loadedSounds[type];
            cur.AddSound(sound);
            loadedSounds[type] = cur;
        }else {
            SoundCollection cur = SoundCollection();
            cur.AddSound(sound);
            loadedSounds[type] = cur;
        }
    }

    void PlaySound(SoundType sound) {
        if (!loadedSounds.contains(sound)) std::cerr << "Sound not found" << std::endl;

        loadedSounds[sound].PlaySound();
    }


    void UnloadAllSounds() {
        for (auto &pair : loadedSounds) {
            pair.second.UnloadSounds();
        }
        loadedSounds.clear();
    }
}
