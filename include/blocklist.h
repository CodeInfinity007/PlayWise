#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <string>
#include <unordered_set>
using namespace std;


class Blocklist {
private:
    unordered_set<string> blocked;

public:
    void block(const string& artist);
    void unblock(const string& artist);
    bool is_blocked(const string& artist) const;
    void display_blocked() const;
};

// extern Blocklist blocklist;

#endif
