#ifndef SEARCH_H
#define SEARCH_H

#include "song.h"
#include <unordered_map>
#include <string>

class SongSearch {
private:
    std::unordered_map<std::string, Song> songMap;
public:
    void add_song(const Song& s);
    Song* search_song(const std::string& id);
    void delete_song(const std::string& id);
    void clear();

};

#endif