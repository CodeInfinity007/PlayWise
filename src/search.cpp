#include "search.h"
#include <iostream>

void SongSearch::add_song(const Song& s) {
    songMap[s.id] = s;
}

Song* SongSearch::search_song(const std::string& id) {
    auto it = songMap.find(id);
    if (it != songMap.end()) {
        return &(it->second);
    } else {
        std::cout << "Song not found.\n";
        return nullptr;
    }
}

void SongSearch::delete_song(const std::string& id) {
    songMap.erase(id);
}

void SongSearch::clear() {
    songMap.clear();
}
