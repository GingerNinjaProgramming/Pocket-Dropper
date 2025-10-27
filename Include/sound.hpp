//
// Created by conne on 26/10/2025.
//

#ifndef POCKET_DROPPER_SOUND_HPP
#define POCKET_DROPPER_SOUND_HPP
#include <vector>
#include <raylib.h>
#include <unordered_map>
#include "enum.hpp"


//Warning this system assumes sounds exist at the given file path and are not being copyied
namespace Sounds {
    class SoundCollection;

    extern std::unordered_map<SoundType, SoundCollection> loadedSounds;

    class SoundCollection {
        std::vector<Sound> sounds;

        public:
            void AddSound(Sound sound) {
                sounds.push_back(sound);
            }

            void PlaySound() {
                Sound sound = sounds[GetRandomValue(0, sounds.size() - 1)];
                ::PlaySound(sound);
            }

            void UnloadSounds() {
                for (auto &sound : sounds) {
                    UnloadSound(sound);
                }
                sounds.clear();
            }
    };


    void LoadSound(char* filePath, SoundType type, float volume = 1);

    void PlaySound(SoundType sound);

    void UnloadAllSounds();

#endif //POCKET_DROPPER_SOUND_HPP
}