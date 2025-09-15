#ifndef SONG_H
#define SONG_H

#include <string>

struct Song {
    std::string id;
    std::string title;
    std::string artist;
    int duration;
    int rating;
    int addedOrder;
};

#endif