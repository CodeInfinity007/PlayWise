#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include "song.h"
#include <string>
#include <iostream>
#include "blocklist.h"

using namespace std;

// struct Song {
//     string id;
//     string title;
//     string artist;
//     int duration;
//     int rating;
//     int addedOrder;
// };

// custom operator overloading for custom Song object
ostream& operator<<(ostream& os, const Song& s);

class SongSearch;
class SongRatingTree;
class PlaylistSorter;

struct Node {
    Song song;
    Node* prev;
    Node* next;
    Node(const Song& s) : song(s), prev(nullptr), next(nullptr) {}
};

class playlist {
private:
    Node* head;
    Node* tail;
    int size;
    SongSearch* searcher = nullptr;
    SongRatingTree* ratingTree = nullptr;
    PlaylistSorter* sorter = nullptr;
    Blocklist blocklist;

public:
    playlist(SongSearch* s = nullptr, SongRatingTree* r = nullptr, PlaylistSorter* p = nullptr);
    void set_modules(SongSearch* s, SongRatingTree* r, PlaylistSorter* p);
    void add_song(const Song& s);
    void raw_add_song(const Song& s);
    void delete_song(int ind);
    void move_song(int ind1, int ind2);
    void reverse_playlist();
    void display_playlist();
    vector<Song> get_all_songs() const;
    void rebuild_from_vector(const std::vector<Song>& sortedSongs);
    
    void block_artist(const string& artist);
    void unblock_artist(const string& artist);
    bool is_artist_blocked(const string& artist) const;
    void display_blocked_artists() const;


};

#endif
