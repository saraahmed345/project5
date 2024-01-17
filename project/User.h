#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "FileManager.h"
using namespace std;
#pragma once
class User
{
private:
	string username;
	string password;
	string ID;
public:
	queue<Message> currentUserFavoriteMessages;
	User();
	User(string username, string password, string id, queue<Message>&);
	void addContact( list<Contact>&, stack<Message>& messages);
	string getID();
	void userOptions(list<SarahaUsers>& users, list<Contact>& contacts, stack<Message>& messages, queue <Message>& favoriteMessages);
	void viewContacts(list<Contact> contacts, stack<Message>& messages);
	void searchContact( list<Contact> contacts);
	void sendMessage(list<Contact> contacts, stack<Message>& messages, list<SarahaUsers>users);
	void viewSentMessages(stack<Message> messages, list<SarahaUsers>users);
	void undoLastSentMessage(stack<Message>& messages, list<SarahaUsers>users);
	string getUsername(string id, list<SarahaUsers>users);
	void viewReceivedMessages(stack<Message> messages);
	void viewReceivedMsgsfromContact(list<Contact>contacts, stack<Message> messages);
	void viewFavoriteMessages(queue<Message> favoriteMessages);
	void addToFavorite(queue<Message>& favoriteMessages, stack<Message> messages);
	void RemoveOldestFavoriteMessage(queue<Message>& favoriteMessages);
	
};

