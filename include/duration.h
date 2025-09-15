#ifndef DURATION_H
#define DURATION_H

#include "song.h"
#include <vector>
#include <queue>
#include <string>

// custom comparators
// true → a lower priority
struct SongDurationMin {
    bool operator()(const Song& a, const Song& b) const {
        return a.duration > b.duration;
    }
};

// true → a lower priority
struct SongDurationMax {
    bool operator()(const Song& a, const Song& b) const {
        return a.duration < b.duration;
    }
};

class Duration {
public:
    void summarize(const std::vector<Song>& songs) const;
};

#endif
