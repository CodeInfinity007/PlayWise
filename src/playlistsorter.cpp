#include "playlistsorter.h"
# include "playlist.h"
#include <iostream>
using namespace std;

// helpers

// comparator
bool PlaylistSorter::compareSongs(const Song &a, const Song &b, string criteria, bool ascending) {
    if (criteria == "title") {
        return ascending ? (a.title < b.title) : (a.title > b.title);
    } else if (criteria == "duration") {
        return ascending ? (a.duration < b.duration) : (a.duration > b.duration);
    } else if (criteria == "recent") {
        return ascending ? (a.id < b.id) : (a.addedOrder > b.addedOrder);
    }
    return false;
}

// divide based on pivot
int PlaylistSorter::partition(vector<Song> &arr, int low, int high, string criteria, bool ascending) {
    Song pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compareSongs(arr[j], pivot, criteria, ascending)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void PlaylistSorter::quickSort(vector<Song> &arr, int low, int high, string criteria, bool ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, criteria, ascending);
        quickSort(arr, low, pi - 1, criteria, ascending);
        quickSort(arr, pi + 1, high, criteria, ascending);
    }
}


// main funcs
void PlaylistSorter::add_song(const Song& s) {
    songs.push_back(s);
}


void PlaylistSorter::clear() {
    songs.clear();
}

void PlaylistSorter::sort_playlist(playlist& pl, string criteria, bool ascending) {
    songs = pl.get_all_songs();

    quickSort(songs, 0, songs.size() - 1, criteria, ascending);

    // update dll after sorting
    pl.rebuild_from_vector(songs);
}


void PlaylistSorter::display_playlist() {
    for (auto &s : songs) {
        cout << s.title << " (" << s.duration << " sec, rating " << s.rating << ")\n";
    }
}



