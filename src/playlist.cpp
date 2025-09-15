#include "playlist.h"
#include <iostream>
#include <vector>
#include "search.h"
#include "rating.h"
#include "playlistsorter.h"
#include "blocklist.h"

using namespace std;

playlist::playlist(SongSearch* s, SongRatingTree* r, PlaylistSorter* p) {
    head = tail = nullptr;
    size = 0;
    searcher = s;
    ratingTree = r;
    sorter = p;
}

void playlist::set_modules(SongSearch* s, SongRatingTree* r, PlaylistSorter* p) {
    searcher = s;
    ratingTree = r;
    sorter = p;
}

void playlist::add_song(const Song& s) {

    if (blocklist.is_blocked(s.artist)) {
        cout << "Can't add song, Artist " << s.artist << " blocked.\n";
        return;
    }

    Node* newNode = new Node(s);
    
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;

    // Auto-sync with other modules
    if (searcher) searcher->add_song(s);
    if (ratingTree) ratingTree->insert_song(s);
    if (sorter) sorter->add_song(s);
}

void playlist::raw_add_song(const Song& s) {
    Node* newNode = new Node(s);

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

void playlist::delete_song(int ind) {
    // bounds check
    if (ind < 0 || ind >= size) return;

    Node* temp = head;
    // delete head (if)
    if (ind == 0) {
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
        size--;
        return;
    }
    // reach to where del
    for (int i = 0; i < ind; i++) temp = temp->next;

    // delete tail (if)
    if (!temp->next) {
        tail = temp->prev;
        tail->next = nullptr;
        delete temp;
        size--;
        return;
    }

    // neither head nor tail
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    size--;
}

void playlist::move_song(int ind1, int ind2) {
    if (size <= 1 || ind1 == ind2) return;

    /*
    cases:
    1. ind1 head, ind2 tail
    2. ind1 tail, ind2 head
    3. somewhere in between
    */

    // 1
    if ((ind1 == 0) && (ind2 == size - 1)) {
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        tail->next = temp;
        temp->prev = tail;
        temp->next = nullptr;
        tail = temp;
    }
    // 2
    else if ((ind1 == size - 1) && (ind2 == 0)) {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        head->prev = temp;
        temp->next = head;
        temp->prev = nullptr;
        head = temp;
    }
    // 3
    else {
        Node* tomove = head;
        for (int i = 0; i < ind1; i++) tomove = tomove->next;

        Node* target = head;
        for (int i = 0; i < ind2; i++) target = target->next;

        // special adjacent case
        if (ind2 == ind1 + 1) {
            tomove->prev->next = target;
            target->prev = tomove->prev;
            tomove->next = target->next;
            target->next->prev = tomove;
            target->next = tomove;
            tomove->prev = target;
            return;
        }

        // unlink tomove
        tomove->prev->next = tomove->next;
        tomove->next->prev = tomove->prev;

        // fix index
        if (ind1 < ind2) ind2--;

        target = head;
        for (int i = 0; i < ind2; i++) target = target->next;

        // add tomove to target pos
        tomove->next = target;
        tomove->prev = target->prev;
        target->prev->next = tomove;
        target->prev = tomove;
    }
}

void playlist::reverse_playlist() {
    if (!head || !head->next) return;
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;
        curr = curr->prev;
    }
    head = prev->prev;
}

void playlist::display_playlist(){
    Node* tmp = head;

    while (tmp){
        cout<< tmp->song << endl;
        tmp = tmp->next;
    }
    
}

vector<Song> playlist::get_all_songs() const {
    vector<Song> result;
    Node* temp = head;
    while (temp) {
        result.push_back(temp->song);
        temp = temp->next;
    }
    return result;
}


void playlist::rebuild_from_vector(const vector<Song>& sortedSongs) {
    // Delete all existing nodes
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = tail = nullptr;
    size = 0;

    // add updated dll
    for (const Song& s : sortedSongs) {
        raw_add_song(s);
    }

}

// wrapper funcs
void playlist::block_artist(const string& artist) {
    blocklist.block(artist);
}

void playlist::unblock_artist(const string& artist) {
    blocklist.unblock(artist);
}

bool playlist::is_artist_blocked(const string& artist) const {
    return blocklist.is_blocked(artist);
}

void playlist::display_blocked_artists() const {
    blocklist.display_blocked();
}



// custom op for print Song
ostream& operator<<(ostream& os, const Song& s) {
    os << "ID: " << s.id << "\n"
       << "Title: " << s.title << "\n"
       << "Artist: " << s.artist << "\n"
       << "Duration: " << s.duration << " sec\n"
       << "Rating: " << s.rating << "\n"
       << "Added Order: " << s.addedOrder << "\n";
    return os;
}