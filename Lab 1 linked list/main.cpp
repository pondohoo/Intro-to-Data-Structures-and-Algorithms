#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

void PrintMenu(string title);

int main(){

    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr;
    int numSongs = 0; //need this for the change position option; make sure it's edited everywhere accordingly

    string playlistName;
    string ID;
    string songName;
    string artistName;
    int songLength;

    char option;

    int currpos, newpos;

//prompts user for title of playlist

    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistName);
    cout << endl;
    PrintMenu(playlistName);

//user picks an option

cin >> option;

while (option != 'q') {









//ADDING A SONG
if (option == 'a'){


    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> ID;
    cin.ignore();
    cout << "Enter song's name:" << endl;
    getline(cin, songName);
    cout << "Enter artist's name:";
    getline(cin, artistName);
    cout << endl;
    cout << "Enter song's length (in seconds):" << endl;
    cin >> songLength;



    
    if (head == nullptr) //playlist is empty
    {
        head = new PlaylistNode(ID, songName, artistName, songLength);
        tail = head;
        ++numSongs;
    }
    else if (head->GetNext() == nullptr) //playlist has 1 song
    {
        PlaylistNode* newSong = new PlaylistNode(ID, songName, artistName, songLength);
        head->SetNext(newSong);
        tail = head->GetNext();
        ++numSongs;
    }
    else //playlist has more than 1 song
    {
        PlaylistNode* newSong = new PlaylistNode(ID, songName, artistName, songLength);
        tail->SetNext(newSong);
        tail = tail->GetNext();
        ++numSongs;
    }
}












//REMOVE SONG GIVEN SONG ID

else if (option == 'd'){

    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> ID;
   



// if removing first song
    if(head->GetID() == ID){

        cout << "\"" << head->GetSongName() << "\" removed." << endl; 

        if(head->GetNext() == nullptr){    // if playlist after song removal is empty

            PlaylistNode* temp = head;
            head = nullptr;
            tail = nullptr;
            delete temp;

        }
        else{

        PlaylistNode* temp = head;
		head = head->GetNext();
		delete temp;

        }

        numSongs--;

    }
    
// if removing other songs
    else{
        
        PlaylistNode* currSong = nullptr;
        currSong = head;
        
        while(currSong->GetNext() != nullptr){
            
            if(currSong->GetNext()->GetID() == ID){

                cout << "\"" << currSong->GetNext()->GetSongName() << "\" removed." << endl;
                PlaylistNode* temp = currSong->GetNext();
                PlaylistNode* temp2 = currSong->GetNext()->GetNext();
                currSong->SetNext(temp2); // FIX:::: "initial value of reference to non-const must be an lvalue" 
                delete temp;
                
                if(currSong->GetNext()->GetNext() == nullptr){      // updates tail if removing the last song of the playlist
                    tail = currSong->GetNext();
                }



            }
            currSong = currSong->GetNext();
            
        }

            numSongs--;

    }

}












//CHANGING POSITION OF SONG
else if (option == 'c'){
    //WIP

    //one node is head
    // one node is tail
    // one node is inside

    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:";
    cin >> currpos;
    if (currpos < 1)
    {
        currpos = 1;
    }
    else if (currpos > numSongs)
    {
        currpos = numSongs;
    }
    cout << endl;
    cout << "Enter new position for song:" << endl;
    cin >> newpos;
    if (newpos < 1)
    {
        newpos = 1;
    }
    else if (newpos > numSongs)
    {
        newpos = numSongs;
    }

    //no need to swap if list only has 1 song or 0 songs or selfswap
    if (numSongs > 1 && currpos != newpos)
    {
        PlaylistNode* prev = nullptr;
        int counter = 1;
        PlaylistNode* curr = head;

        
        //going through list and finding the node at currpos 
        while (counter != currpos && curr != nullptr)
            {
                prev = curr; // going through nodes until reaches position
                curr = curr->GetNext();
                ++counter;
            }
        PlaylistNode* oldCurr = curr;
        PlaylistNode* oldPrev = prev;

        
        curr = head;
        prev = nullptr;
        counter = 1;
        while (counter != newpos && curr != nullptr)
            {
                prev = curr; // going through nodes until reaches position
                curr = curr->GetNext();
                ++counter;
            }


        cout << "\"" << oldCurr->GetSongName() << "\" moved to position " << newpos << endl;
        PlaylistNode* newCurr = curr;
        PlaylistNode* newPrev = prev;

        PlaylistNode* newCurrNext = newCurr->GetNext();
        PlaylistNode* oldCurrNext = oldCurr->GetNext();

        //old gets taken out of its original position
        if (oldPrev != nullptr)
         {
            oldPrev->SetNext(oldCurrNext);
        }
        else
        {
            head = oldCurr->GetNext();
        }
        if (currpos > newpos)
        {
            if (newPrev != nullptr)
            {
                newPrev->SetNext(oldCurr);
            }
            else
            {
                head = oldCurr;
            }

            oldCurr->SetNext(newCurr);
        }
        else
        {
            newCurr->SetNext(oldCurr);
            oldCurr->SetNext(newCurrNext);
            if (tail == newCurr)
            {
                tail = oldCurr;
            }
        }
    }
}











//OUTPUTTING SONGS BY ARTIST

else if (option == 's'){

    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cin.ignore();
    getline(cin, artistName);
    cout << endl;
   



   int counter = 1;

    PlaylistNode* currSong = head;


   while(currSong->GetNext() != nullptr){
       
       if(currSong->GetArtistName() == artistName){

           cout << counter << "." << endl;
           currSong->PrintPlaylistNode();
           currSong = currSong->GetNext();
           counter++;
           break;                              // breaks out of while loop
       }

       currSong = currSong->GetNext();
       counter++;
   }

     while(currSong != nullptr){
       
       if(currSong->GetArtistName() == artistName){

           cout << endl;           //to prevent new line at the end of the playlist
           cout << counter << "." << endl;
           currSong->PrintPlaylistNode();                          
       }

       currSong = currSong->GetNext();
       counter++;
   }

}


// TOTAL PLAYLIST TIME

else if (option == 't'){

   int sum = 0;

   PlaylistNode* currSong = head;
   
   while(currSong != nullptr){

       sum += currSong->GetSongLength();
       currSong = currSong->GetNext(); 

   }

   cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
   cout << "Total time: " << sum << " seconds" << endl;

}





//printing full playlist

else if (option == 'o'){

     cout << playlistName << " - OUTPUT FULL PLAYLIST" << endl;
    
        if(numSongs == 0){
            cout << "Playlist is empty" << endl; // if playlist is empty
        }

        else{                        // if playlist is not empty
        
        int counter = 1;
        PlaylistNode* currSong = head;

        cout << counter << "." << endl;
        currSong->PrintPlaylistNode();
        currSong = currSong->GetNext();
        counter++;

            while(currSong != nullptr){
                cout << endl;                          // does not print an extra endl at the end of the playlist
                cout << counter << "." << endl;
                currSong->PrintPlaylistNode();
                currSong = currSong->GetNext();
                counter++;
            }
            
        }


}

//display menu again, asks for user to enter option. if option == 'q', exits while loop

cout << endl;
PrintMenu(playlistName);
cin >> option;


} // bracket for while loop

return 0;
} // end of main 

void PrintMenu(string title){

    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;

}
