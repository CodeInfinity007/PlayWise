#include "playbackhistory.h"
# include "blocklist.h"
# include<iostream>
using namespace std;


void PlaybackHistory::play_song(const Song& s) {
    // if (blocklist.is_blocked(s.artist)) {
    //     cout << "Can't add song, Artist " << s.artist << " blocked.\n";
    //     return;
    // }

    cout << "Playing " << s.title << endl;
    history.push(s);
}

void PlaybackHistory::undo_last_play(playlist& pl) {
    if (isempty()) return;
    Song lastsong = history.top();
    history.pop();
    pl.add_song(lastsong);
    cout << "Song" << lastsong.title<< "re-added to history!!" <<endl;
}

bool PlaybackHistory::isempty() {
    return history.empty();
}

vector<Song> PlaybackHistory::get_recent_songs(int count) const {
    vector<Song> result;
    stack<Song> tempStack = history;

    while (!tempStack.empty() && result.size() < (size_t)count) {
        result.push_back(tempStack.top());
        tempStack.pop();
    }
    return result;
}

