#include "Playlist.h"
#include <iostream>

using namespace std;

PlaylistNode::PlaylistNode()
{
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}
PlaylistNode::PlaylistNode(string ID, string songName, string artistName, int songLength) 
: uniqueID(ID), songName(songName), artistName(artistName), songLength(songLength) {}
string PlaylistNode::GetID()
{
    return uniqueID;
}
string PlaylistNode::GetSongName()
{
    return songName;
}
string PlaylistNode::GetArtistName()
{
    return artistName;
}
int PlaylistNode::GetSongLength()
{
    return songLength;
}
PlaylistNode* PlaylistNode::GetNext()
{
    return nextNodePtr;
}
void PlaylistNode::PrintPlaylistNode()
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
void PlaylistNode::InsertAfter(PlaylistNode*& newNode)
{
    this->nextNodePtr = newNode;
}
void PlaylistNode::SetNext(PlaylistNode*& newNode)
{
    this->nextNodePtr = newNode;
}