#include "blocklist.h"
#include <iostream>
using namespace std;

// Blocklist blocklist;

void Blocklist::block(const string& artist) {
    blocked.insert(artist);
    cout << "Blocked artist: " << artist << "\n";
}

void Blocklist::unblock(const string& artist) {
    if (blocked.erase(artist)) {
        cout << "Unblocked artist: " << artist << "\n";
    } else {
        cout << "Artist not blocked.\n";
    }
}

bool Blocklist::is_blocked(const string& artist) const {
    return blocked.count(artist) > 0;
}

void Blocklist::display_blocked() const {
    cout << "Blocked Artists:\n";
    for (const auto& artist : blocked) {
        cout << artist << "\n";
    }
}
