#include "systemsnapshot.h"
#include "duration.h"
#include "playlistsorter.h"
#include <iostream>
#include <algorithm>
using namespace std;

void SystemSnapshot::export_snapshot(playlist& pl, PlaybackHistory& history, SongRatingTree& ratingTree) {

    vector<Song> longestSongs = get_top_5_longest(pl);
    cout << "\nTop 5 Longest Songs:\n";
    for (int i = 0; i < longestSongs.size(); i++) {
        cout << longestSongs[i].title << " (" << longestSongs[i].duration << " sec)\n";
    }

    vector<Song> recentSongs = get_recently_played(history, 5);
    cout << "\nRecently Played Songs:\n";
    for (int i = 0; i < recentSongs.size(); i++) {
        cout << recentSongs[i].title << "\n";
    }

    unordered_map<int, int> ratingMap = get_song_count_by_rating(ratingTree);
    cout << "\nSong Count by Rating:\n";
    for (auto it = ratingMap.begin(); it != ratingMap.end(); it++) {
        cout << it->first << " : " << it->second << " songs\n";
    }

    // Duration summary (total, shortest, longest)
    // special use case
    Duration dv;
    dv.summarize(pl.get_all_songs());
}

vector<Song> SystemSnapshot::get_top_5_longest(playlist& pl) {
    vector<Song> songs = pl.get_all_songs();

    // Comparator
    struct CompareSongs {
        bool operator()(const Song &a, const Song &b) {
            return a.duration > b.duration;
        }
    };

    sort(songs.begin(), songs.end(), CompareSongs());

    // first 5 songs
    if (songs.size() > 5) {
        songs.resize(5);
    }

    return songs;
}


vector<Song> SystemSnapshot::get_recently_played(PlaybackHistory& history, int count) {
    return history.get_recent_songs(count);
}

unordered_map<int, int> SystemSnapshot::get_song_count_by_rating(SongRatingTree& ratingTree) {
    return ratingTree.get_song_count_map();
}
