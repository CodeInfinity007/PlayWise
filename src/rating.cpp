#include "rating.h"
#include <iostream>
#include <functional>
using namespace std;

RatingNode::RatingNode(int r) : rating(r), left(NULL), right(NULL) {}

SongRatingTree::SongRatingTree() {
    root = NULL;
}

// helper funcs

RatingNode* SongRatingTree::insert(RatingNode* node, const Song& song) {
    // empty tree add new
    if (!node) {
        RatingNode* newNode = new RatingNode(song.rating);
        newNode->songs.push_back(song);
        return newNode;
    }
    // find smaller or bigger traverse
    if (song.rating < node->rating) node->left = insert(node->left, song);
    else if (song.rating > node->rating) node->right = insert(node->right, song);
    else node->songs.push_back(song);
    return node;
}

RatingNode* SongRatingTree::search(RatingNode* node, int rating) {
    if (!node || node->rating == rating) return node;
    if (rating < node->rating) return search(node->left, rating);
    else return search(node->right, rating);
}

// find min by going leftest deep
RatingNode* SongRatingTree::findMin(RatingNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

RatingNode* SongRatingTree::deleteSong(RatingNode* node, const Song& song) {
    // nothing to delete
    if (!node) return NULL;
    // find left
    if (song.rating < node->rating) node->left = deleteSong(node->left, song);
    // find right
    else if (song.rating > node->rating) node->right = deleteSong(node->right, song);
    // found now find song
    else {
        // iterator
        for (auto it = node->songs.begin(); it != node->songs.end(); ++it) {
            if (it->id == song.id) { // match by Song ID
                node->songs.erase(it);
                break;
            }
        }
        // cases for if we have to delete full node
        if (node->songs.empty()) {
            // no children
            if (!node->left && !node->right) {
                delete node;
                return NULL;
            // no left 
            } else if (!node->left) {
                RatingNode* temp = node->right;
                delete node;
                return temp;
            // no right
            } else if (!node->right) {
                RatingNode* temp = node->left;
                delete node;
                return temp;
            // both left and right present so find min then copy
            } else {
                RatingNode* temp = findMin(node->right);
                node->rating = temp->rating;
                node->songs = temp->songs;
                node->right = deleteSong(node->right, temp->songs[0]);
            }
        }
    }
    return node;
}

// main funcs

void SongRatingTree::insert_song(const Song& song) {
    root = insert(root, song);
}

void SongRatingTree::search_by_rating(int rating) {
    RatingNode* res = search(root, rating);
    if (!res) {
        cout << "No songs for rating " << rating << "\n";
        return;
    }
    for (const Song& s : res->songs) cout << s.title << " ";
    cout << "\n";
}

void SongRatingTree::delete_song(const Song& song) {
    root = deleteSong(root, song);
}

// unordered_map passed as reference
void SongRatingTree::collect_counts(RatingNode* node, unordered_map<int, int>& ratingCount) const {
    if (!node) return;
    ratingCount[node->rating] += node->songs.size();
    collect_counts(node->left, ratingCount);
    collect_counts(node->right, ratingCount);
}

// map is updated with ratings of songs with specific ratings
unordered_map<int, int> SongRatingTree::get_song_count_map() const {
    unordered_map<int, int> ratingCount;
    collect_counts(root, ratingCount);
    return ratingCount;
}

void SongRatingTree::clear() {
    clear_recursive(root);
    root = nullptr;
}

void SongRatingTree::clear_recursive(RatingNode* node) {
    if (!node) return;
    clear_recursive(node->left);
    clear_recursive(node->right);
    delete node;
}



