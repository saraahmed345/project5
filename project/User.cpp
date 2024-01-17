#include "User.h"
#include <iostream>

using namespace std;

User::User() {}
User::User(string username, string password, string id, queue<Message>& favoriteMessages) {
	this->username = username;
	this->password = password;
	this->ID = id;
	Message TempMessage;
	queue<Message> TempFavoriteMessages = favoriteMessages;
	while (!TempFavoriteMessages.empty()) {
		if (getID() == TempFavoriteMessages.front().reciever) {
			TempMessage.sender = TempFavoriteMessages.front().sender;
			TempMessage.reciever = TempFavoriteMessages.front().reciever;
			TempMessage.message = TempFavoriteMessages.front().message;
			currentUserFavoriteMessages.push(TempMessage);
		}
		TempFavoriteMessages.pop();
	}
}


string User::getID() {
	return this->ID;
}

void User::userOptions(list<SarahaUsers>& users, list<Contact>& contacts, stack<Message>& messages, queue<Message>& favoriteMessages)
{
	short int choice = 0;
	while (choice != 12) {
		cout << "Please choose one of the following options: " << endl
			<< "1. Add Contact to your contactlist." << endl														//Done
			<< "2. view all contacts in your contactlist." << endl													//Done
			<< "3. search for a specific contact." << endl										//Done
			<< "4. send a Message to another user." << endl														//Done
			<< "5. view all sent messages." << endl													//Done
			<< "6. undo the last sent message." << endl
			<< "7. View all Received Messages." << endl												//Done
			<< "8. View all the received messages from specfic contact." << endl
			<< "9. put a message in favorites." << endl
			<< "10. View all Favorite Messages." << endl
			<< "11. Remove the oldest message from favorite." << endl
			<< "12. delete contact" << endl
			<< "13. logout." << endl;
		cout << "enter your Choice: ";
		cin >> choice;
		switch (choice)
		case 1:
		{
			system("cls");
			addContact( contacts,messages);
			break;
		case 2:
			system("cls");
			cout << "\t\t___________________________________________" << endl << "\t\t\t\tView Contacts\n";
			cout << "\t\t___________________________________________" << endl << endl;

			viewContacts(contacts,messages);
			break;
		case 3:
			system("cls");
			searchContact(contacts);
			break;
		case 4:
			system("cls");
			sendMessage(contacts, messages,users);
			break;
		case 5:
			system("cls");
			// We will use stack for messages not vector
			viewSentMessages(messages, users);
			break;
		case 6:
			system("cls");
			undoLastSentMessage(messages, users);
			break;
		case 7:
			system("cls");
			viewReceivedMessages(messages);
			break;
		case 8:
			system("cls");
			//cout << "ID: " << getID() << endl << endl;
			viewReceivedMsgsfromContact(contacts, messages);
			break;
		case 9:
			system("cls");
			addToFavorite(favoriteMessages, messages);
			break;
		case 10:
			system("cls");
			viewFavoriteMessages(favoriteMessages);
			break;
		case 11:
			system("cls");
			RemoveOldestFavoriteMessage(favoriteMessages);
			break;
		case 12:
			system("cls");
			FileManager f;
			f.removeContact(contacts, getID());
		default:
			system("cls");
			choice = 12;
			break;
		}
	}
}

void User::addContact( list<Contact>& contacts, stack<Message>& messages)
{
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tAdd Contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	string id;
	
	bool contactFound = false;
	Contact TempContact;
	bool contactInUserContacts = false;
	list <Contact>::iterator contactIt;
	cout << "Enter the id you want to add: ";
	cin >> id;
	
	
	
	for (contactIt = contacts.begin(); contactIt != contacts.end(); contactIt++) {
		if (getID() == contactIt->myID && id == contactIt->contactID) {
			contactInUserContacts = true;
			break;
		}
	}

	
	while (!messages.empty()) {
		if (id == messages.top().sender) {
			contactFound = true;
			break;
		}
		messages.pop();
	}
	if (contactFound)
	{
		cout << "Contact added to your contact list." << endl;
		cout << "_____________________________________________\n";
		FileManager::setContact(contacts);
	}
	//This  else if part is also added with the Updated part to validate.
	else if (contactInUserContacts) {
		cout << "The entered user is already in your contacts." << endl;
	}
	else {
		cout << "this id never send you a message ." << endl;
	}
}


void User::viewContacts(list<Contact> contacts, stack<Message>& messages) {
	
	list <Contact> ::iterator it;
	for (it = contacts.begin(); it != contacts.end(); it++) {
		if (getID() == it->myID) {
			int number = 0;
			while (!messages.empty()) {
				if (it->contactID == messages.top().sender && getID() == messages.top().reciever || getID() == messages.top().sender && it->contactID == messages.top().reciever) {
					number++;

				}
				messages.pop();
			}

			cout << "Username: " << it->contactUsername << endl;
			cout << "number of messages between you : " << number<<endl;
			
		}
		
	}
	cout << "_______________________________________________\n";
}

void User::searchContact( list<Contact> contacts) {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tSearch a contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	bool contactFound = false;
	string user_name;
	cout << "Enter the Username you want to search for: ";
	cin >> user_name;
	list <Contact> ::iterator it;
	for (it = contacts.begin(); it != contacts.end(); it++) {
		if (user_name == it->contactUsername && getID()==it->myID) {
			contactFound = true;
			break;
		}
	}
	if (contactFound)
	{
		cout << "Contact is found in your contacts." << endl;

	}
	else {
		cout << "NOT FOUND." << endl;
	}
}

void User::sendMessage(list<Contact> contacts, stack<Message>& messages, list<SarahaUsers>users) {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tSend Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	string contactUsername;
	Message TempMessage;
	bool inuserss = false;
	cout << "Enter the id of the user to send to: ";
	cin >> contactUsername;
	list <SarahaUsers> ::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (contactUsername == it->ID) {
			TempMessage.sender = getID();
			TempMessage.reciever = it->ID;
			inuserss = true;
			break;
		}
	}
	if (inuserss) {
		cout << "Enter the message: ";
		cin.ignore();
		getline(cin, TempMessage.message);
		messages.push(TempMessage);
		FileManager::setMessage(messages);
	}
	else {
		cout << "the id you send to is not a sarahaa user" << endl;
	}
}

void User::viewSentMessages(stack<Message> messages, list<SarahaUsers>users) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Sent Messages\n";
	cout << "\t\t___________________________________________" << endl << endl;

	while (!messages.empty()) {
		if (getID() == messages.top().sender) {
			cout << "The message is sent to: " << getUsername(messages.top().reciever, users) << endl
				<< "The message: " << messages.top().message << endl;
		}
		messages.pop();
	}
}

void User::undoLastSentMessage(stack<Message>& messages, list<SarahaUsers>users)
{
	cout << "\t\t___________________________________________" << endl << "\t\t\tUndo Last Sent Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	messages.pop();
	cout << "Last sent message undoed\n";
	cout << "last sent messages after deleting last sent one:\n";
	viewSentMessages(messages, users);
	FileManager::setMessage(messages);
}

string User::getUsername(string id, list<SarahaUsers>users) {

	list <SarahaUsers> ::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (id == it->ID) {
			return it->username;
		}
	}
}

void User::viewReceivedMessages(stack<Message> messages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Received Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	while (!messages.empty()) {
		if (messages.top().reciever == getID()) {
			cout << "The message sent From: " << messages.top().sender << endl
				<< "The message: " << messages.top().message << endl;
			cout << "__________________\n";
		}
		messages.pop();
	}
	cout << "____________________________________________________________\n";
}
void User::viewReceivedMsgsfromContact( list<Contact>contacts, stack<Message> messages ) {
	cout << "\t\t___________________________________________" << endl << "\t\tMy Received Messages from a specific contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	cout << "Contacts: " << endl;
	viewContacts(contacts,messages);
	cout << endl;
	bool found = false;
		list<Contact>::iterator it;

		while (!found) 
		{
			cout << "_____________________________________" << endl;
			cout << "Enter the contact name: ";
			Contact cnt;
			cin >> cnt.contactUsername;
			for (it = contacts.begin(); it != contacts.end(); it++) {
				if (cnt.contactUsername == it->contactUsername && getID() == it->myID) {
					cnt.contactID = it->contactID;
					found = true;
					break;
				}
			}
			if (found) {
				while (!messages.empty()) {
					if (cnt.contactID == messages.top().sender && getID() == messages.top().reciever) {
						cout << "The message: " << messages.top().message << endl;
					}
					messages.pop();
				}
			}
			else {
				cout << "User is not in your contacts please choose one from the above" << endl;
			}
	    }
		
}


void User::viewFavoriteMessages(queue<Message> favoriteMessages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Favorite Messages\n";
	cout << "\t\t___________________________________________" << endl << endl;

	queue<Message> secondaryQueue = currentUserFavoriteMessages;
	while (!secondaryQueue.empty()) {
		cout << "The message was sent from: " << secondaryQueue.front().sender << endl
			<< "The message: " << secondaryQueue.front().message << endl;
		secondaryQueue.pop();
	}
}

void User::addToFavorite(queue<Message>& favoriteMessages, stack<Message> messages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tAdd to Favorite\n";
	cout << "\t\t___________________________________________" << endl << endl;

	queue<Message> secondaryMessages1;

	while(!messages.empty()){
		if (getID() == messages.top().reciever) {
			secondaryMessages1.push(messages.top());
		}
		messages.pop();
	}
	queue<Message> secondaryMessages2 = secondaryMessages1;
	int i = 0;
	while(!secondaryMessages1.empty()) {
		cout << i + 1 << "- " << secondaryMessages1.front().message << endl;
		secondaryMessages1.pop();
		i++;
	}
	short int messageNum;
	cout << "Please enter the number of the message you want to add to the Favorite: ";
	cin >> messageNum;
	i = 0;
	if (messageNum > 0 && messageNum <= secondaryMessages2.size()) {
		while (!secondaryMessages2.empty()) {
			i++;
			if (i == messageNum) {
				favoriteMessages.push(secondaryMessages2.front());
				currentUserFavoriteMessages.push(secondaryMessages2.front());
			}
			secondaryMessages2.pop();
		}
		FileManager::setFavoriteMessage(favoriteMessages);
	}
	else {
		cout << "You entered a wrong number." << endl;
	}

}

void User::RemoveOldestFavoriteMessage(queue<Message>& favoriteMessages) {
	cout << "\t\t___________________________________________" << endl << "\t\tRemove Oldest Favorite Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	Message TempRemovedMessage = currentUserFavoriteMessages.front();
	currentUserFavoriteMessages.pop();
	queue<Message> secondaryQueue1 = favoriteMessages;
	queue<Message> secondaryQueue2;
	while (!secondaryQueue1.empty()) {
		if (secondaryQueue1.front().sender == TempRemovedMessage.sender && secondaryQueue1.front().reciever == TempRemovedMessage.reciever && secondaryQueue1.front().message == TempRemovedMessage.message) {
			secondaryQueue1.pop();
			continue;
		}
		secondaryQueue2.push(secondaryQueue1.front());
		secondaryQueue1.pop();
	}
	favoriteMessages = secondaryQueue2;
	FileManager::setFavoriteMessage(favoriteMessages);
	cout << "The oldest message successfully deleted." << endl;
}