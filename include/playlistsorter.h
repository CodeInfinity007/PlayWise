#ifndef PLAYLISTSORTER_H
#define PLAYLISTSORTER_H

#include "song.h"
#include "playlist.h"
#include <vector>
using namespace std;

class PlaylistSorter {
private:
    vector<Song> songs;
    bool compareSongs(const Song &a, const Song &b, string criteria, bool ascending);
    int partition(vector<Song> &arr, int low, int high, string criteria, bool ascending);
    void quickSort(vector<Song> &arr, int low, int high, string criteria, bool ascending);

public:
    // playlist pl;
    // vector<Song> songs;
    void add_song(const Song& s);
    void sort_playlist(playlist& pl, string criteria, bool ascending);
    void display_playlist();
    void clear();

};


#endif
