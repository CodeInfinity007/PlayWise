#include "playlist.h"
#include "playbackhistory.h"
#include "playlistsorter.h"
#include "search.h"
#include "rating.h"
#include "systemsnapshot.h"
# include "blocklist.h"
#include <iostream>
using namespace std;

int main() {
    SongSearch searcher;
    SongRatingTree ratingTree;
    PlaylistSorter sorter;

    playlist playlist(&searcher, &ratingTree, &sorter);
    PlaybackHistory history;
    SystemSnapshot snapshot;
    

    // Sample
    Song s1 = {"S101", "Song A", "Artist W", 200, 5, 0};
    Song s2 = {"S102", "Song B", "Artist X", 150, 4, 1};
    Song s3 = {"S103", "Song C", "Artist Y", 220, 5, 2};
    Song s4 = {"S104", "Song D", "Artist Z", 90, 1, 2};
    playlist.add_song(s1);
    playlist.add_song(s2);
    playlist.add_song(s3);
    // blocklist.block("Artist A");
    playlist.add_song(s4);


    int choice, choice2;
    do {
        cout << "1. Playlist Operations\n";
        cout << "2. Search Song by ID\n";
        cout << "3. Show Songs by Rating\n";
        cout << "4. Play a Song\n";
        cout << "5. Undo Last Play\n";
        cout << "6. Sort Playlist\n";
        cout << "7. Export System Snapshot\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                do {
                    cout << "1. Display Playlist\n";
                    cout << "2. Add Song\n";
                    cout << "3. Delete Song\n";
                    cout << "4. Move Song\n";
                    cout << "5. Reverse Playlist\n";
                    cout << "0. Main Menu\n";
                    cout << "Choice: ";
                    cin >> choice2;

                    switch (choice2) {
                        case 1:
                            playlist.display_playlist();
                            break;

                        case 2: {
                            string id, title, artist;
                            int duration, rating;

                            cout << "Enter Song ID: ";
                            cin.ignore();
                            getline(cin, id);

                            cout << "Enter Song Title: ";
                            getline(cin, title);

                            cout << "Enter Artist Name: ";
                            getline(cin, artist);

                            cout << "Enter Duration (seconds): ";
                            cin >> duration;

                            cout << "Enter Rating (1-5): ";
                            cin >> rating;

                            int addedOrder = playlist.get_all_songs().size() + 1;

                            Song s = {id, title, artist, duration, rating, addedOrder};
                            playlist.add_song(s);

                            cout << "Song added successfully!\n";
                            break;
                        }


                        case 3: {
                            int ind;
                            cout << "Enter Song at index to Delete: ";
                            cin>> ind;
                            playlist.delete_song(ind);
                            break;
                        }

                        case 4: {
                            int fromPos, toPos;
                            cout << "Enter Current Position: ";
                            cin >> fromPos;
                            cout << "Enter New Position: ";
                            cin >> toPos;
                            playlist.move_song(fromPos, toPos);
                            break;
                        }

                        case 5:
                            playlist.reverse_playlist();
                            cout << "Playlist reversed successfully!\n";
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice! Try again.\n";
                    }
                } while (choice2 != 0);
                break;


            case 2: {
                string id;
                cout << "Enter Song ID: ";
                cin >> id;
                Song* song = searcher.search_song(id);
                if (song){
                    cout<<*song;
                }
                break;
            }

            case 3: {
                int rating;
                cout << "Enter Rating (1-5): ";
                cin >> rating;
                ratingTree.search_by_rating(rating);
                break;
            }

            case 4: {
                string id;
                cout << "Enter Song ID to Play: ";
                cin >> id;
                Song* song = searcher.search_song(id);
                if (song) {
                    history.play_song(*song);
                } else {
                    cout << "Song not found!\n";
                }
                break;
            }

            case 5:
                history.undo_last_play(playlist);
                break;

            case 6: {
                string criteria;
                bool asc;
                cout << "Sort by (title/duration/recent): ";
                cin >> criteria;
                cout << "Ascending? (1=Yes, 0=No): ";
                cin >> asc;
                sorter.sort_playlist(playlist, criteria, asc);
                // sorter.display_playlist();
                playlist.display_playlist();
                break;
            }

            case 7:
                snapshot.export_snapshot(playlist, history, ratingTree);
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
