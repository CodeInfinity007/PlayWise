#ifndef PLAYBACKHISTORY_H
#define PLAYBACKHISTORY_H

#include "playlist.h"
#include "song.h"
#include <stack>
using namespace std;

class PlaybackHistory {
private:
    stack<Song> history;
public:
    void play_song(const Song& s);
    void undo_last_play(playlist& pl);
    bool isempty();
    vector<Song> get_recent_songs(int count) const;

};

#endif
