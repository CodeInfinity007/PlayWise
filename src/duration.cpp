#include "duration.h"
#include <iostream>
#include <climits>
#include <queue>
using namespace std;

void Duration::summarize(const vector<Song>& songs) const {
    if (songs.empty()) {
        cout << "Playlist is empty.\n";
        return;
    }

    int total = 0;
    priority_queue<Song, vector<Song>, SongDurationMax> maxHeap;
    priority_queue<Song, vector<Song>, SongDurationMin> minHeap;

    for(auto s: songs){
        maxHeap.push(s);
        minHeap.push(s);
        total+=s.duration;
    }

    cout << "Special Use Case Summarizer:";
    cout << "Playtime: " << total << " sec\n";
    cout << "Shortest Song: " << minHeap.top().title << ": " << minHeap.top().duration << " sec\n";
    cout << "Longest Song: "  << maxHeap.top().title << " : " << maxHeap.top().duration << " sec\n";

}
