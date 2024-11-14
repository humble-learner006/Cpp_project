#pragma once
// �ļ�·��: AudioManager.h

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>
#include <memory>

class AudioManager {
public:
    // ��ʼ����Ƶ��������ָ����������Ƶ�ʡ���ʽ��ͨ�����ͻ����С
    bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048) {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
            SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            return false;
        }
        return true;
    }

    // ������Ƶ�ļ�
    bool loadSound(const std::string& id, const std::string& filepath) {
        Mix_Chunk* sound = Mix_LoadWAV(filepath.c_str());
        if (sound == nullptr) {
            SDL_Log("Failed to load sound: %s, Mix_Error: %s\n", filepath.c_str(), Mix_GetError());
            return false;
        }
        sounds[id] = sound;
        return true;
    }

    bool loadMusic(const std::string& id, const std::string& filepath) {
        Mix_Music* music = Mix_LoadMUS(filepath.c_str());
        if (music == nullptr) {
            SDL_Log("Failed to load music: %s, Mix_Error: %s\n", filepath.c_str(), Mix_GetError());
            return false;
        }
        musicTracks[id] = music;
        return true;
    }

    // ������Ч
    void playSound(const std::string& id, int loops = 0) {
        auto it = sounds.find(id);
        if (it != sounds.end()) {
            Mix_PlayChannel(-1, it->second, loops);
        }
    }

    // ��������
    void playMusic(const std::string& id, int loops = -1) {
        auto it = musicTracks.find(id);
        if (it != musicTracks.end()) {
            Mix_PlayMusic(it->second, loops);
        }
    }

    // ֹͣ������Ч������
    void stopAll() {
        Mix_HaltChannel(-1); // ֹͣ����ͨ����Ч
        Mix_HaltMusic();      // ֹͣ��������
    }

    // �ͷ���Դ���ر�SDL_mixer
    void cleanup() {
        for (auto& sound : sounds) {
            Mix_FreeChunk(sound.second);
        }
        for (auto& music : musicTracks) {
            Mix_FreeMusic(music.second);
        }
        Mix_CloseAudio();
        SDL_Quit();
    }

private:
    std::map<std::string, Mix_Chunk*> sounds;     // �洢��Ч
    std::map<std::string, Mix_Music*> musicTracks; // �洢����
};
