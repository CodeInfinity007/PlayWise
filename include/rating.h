#ifndef RATING_H
#define RATING_H

#include "song.h"
#include <vector>
#include<unordered_map>
using namespace std;

struct RatingNode {
    int rating;
    vector<Song> songs;
    RatingNode* left;
    RatingNode* right;
    RatingNode(int r);
};

class SongRatingTree {
private:
    RatingNode* root;
    RatingNode* insert(RatingNode* node, const Song& song);
    RatingNode* search(RatingNode* node, int rating);
    RatingNode* findMin(RatingNode* node);
    RatingNode* deleteSong(RatingNode* node, const Song& song);
    void collect_counts(RatingNode* node, unordered_map<int, int>& ratingCount) const;
    void clear_recursive(RatingNode* node);

public:
    SongRatingTree();
    void insert_song(const Song& song);
    void search_by_rating(int rating);
    void delete_song(const Song& song);
    unordered_map<int, int> get_song_count_map() const;
    void clear();

};

#endif
