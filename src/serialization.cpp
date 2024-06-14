#include "include/serialization.h"

#include <iostream>

namespace serialize {
    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map) {
        size_t msize = map.size();
        var(outfile, msize);

        for (const auto& [key, value] : map) {
            size_t ksize = key.size();
            outfile.write(reinterpret_cast<const char*>(&ksize), sizeof(size_t));
            outfile.write(key.data(), ksize);
            outfile.write(reinterpret_cast<const char*>(&value), sizeof(V));
        }
    }

    template<typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair) {
        size_t fsize = pair.first.size();
        var(outfile, fsize);
        outfile.write(pair.first.data(), fsize);

        size_t ssize = pair.second.size();
        var(outfile, ssize);
        outfile.write(pair.second.data(), ssize);
    }

    template <typename T>
    void var(std::ofstream& outfile, const T& var) {
        outfile.write(reinterpret_cast<const char*>(&var), sizeof(T));
    }

    void config(const Struct::Config& config) {
        std::ofstream outfile("config", std::ios::binary);

        var(outfile, config.autosave);

        var(outfile, config.window_mode);

        const size_t mcsize = config.controls.size();
        outfile.write(reinterpret_cast<const char*>(&mcsize), sizeof(size_t));

        for (const auto& [key, value] : config.controls) {
            outfile.write(reinterpret_cast<const char*>(&key), sizeof(SDL_KeyCode));
            outfile.write(reinterpret_cast<const char*>(&value), sizeof(Event::ID));
        }

        outfile.close();
    }

}; // namespace serialize

namespace deserialize {
    template <typename K, typename V>
    void map(std::ifstream& infile, std::map<K, V>& map) {
        size_t msize;
        var(infile, msize);
        for (size_t i = 0; i < msize; ++i) {
            size_t ksize;
            var(infile, ksize);
            std::string key(ksize, '\0');
            infile.read(&key[0], ksize);
            V value;
            var(infile, value);
            map[key] = value;
        }
    }

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair) {
        size_t fsize;
        var(infile, fsize);
        std::string firstData(fsize, '\0');
        infile.read(&firstData[0], fsize);
        pair.first = std::move(firstData);

        size_t ssize;
        var(infile, ssize);
        std::string secondData(ssize, '\0');
        infile.read(&secondData[0], ssize);
        pair.second = std::move(secondData);
    }

    template <typename T>
    void var(std::ifstream& infile, T& var) {
        infile.read(reinterpret_cast<char*>(&var), sizeof(T));
    }

    Struct::Config config() {
        Struct::Config cstruct;

        std::ifstream infile("config", std::ios::binary);

        var(infile, cstruct.autosave);

        var(infile, cstruct.window_mode);

        size_t mcsize;
        infile.read(reinterpret_cast<char*>(&mcsize), sizeof(size_t));

        for (size_t i = 0; i < mcsize; ++i) {
            SDL_KeyCode key;
            infile.read(reinterpret_cast<char*>(&key), sizeof(SDL_KeyCode));
            Event::ID value;
            infile.read(reinterpret_cast<char*>(&value), sizeof(Event::ID));

            cstruct.controls[key] = value;
        }

        infile.close();

        return cstruct;
    }

}; // namepsace deserialize
