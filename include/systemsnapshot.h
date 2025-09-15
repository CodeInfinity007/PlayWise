#ifndef SYSTEMSNAPSHOT_H
#define SYSTEMSNAPSHOT_H

#include "playlist.h"
#include "song.h"
#include "playbackhistory.h"
#include "rating.h"
#include <vector>
#include <unordered_map>
using namespace std;

class SystemSnapshot {
private:
    vector<Song> get_top_5_longest(playlist& pl);
    vector<Song> get_recently_played(PlaybackHistory& history, int count);
    unordered_map<int, int> get_song_count_by_rating(SongRatingTree& ratingTree);
public:
    void export_snapshot(playlist& pl, PlaybackHistory& history, SongRatingTree& ratingTree);
};

#endif
