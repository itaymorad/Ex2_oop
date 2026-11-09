#include <string>
#include "Profile.h"
using namespace std;

/* This function is responsible for initializing the profile */
/* input: owner */
/* output: none */
void Profile::init(const User& owner)
{
	_owner.init(owner.getID(), owner.getUserName(), owner.getAge());

	DeviceNode* curr = owner.getDevices().get_first();
	while (curr)
	{
		_owner.addDevice(curr->get_data());
		curr = curr->get_next();
	}

	_userPage.init();
}


/* This function is responsible for clearing the profile */
/* input: owner */
/* output: none */
void Profile::clear()
{
	_userPage.clearPage();
	_friends.clear();
}


/* This function is responsible for getting the owner */
/* input: none */
/* output: owner */
User Profile::getOwner() const
{
	return _owner;
}


/* This function is responsible for setting new status */
/* input: new status */
/* output: none */
void Profile::setStatus(const std::string new_status)
{
	_userPage.setStatus(new_status);
}


/* This function is responsible for uploading new post */
/* input: new post */
/* output: none */
void Profile::addPostToProfilePage(const std::string post)
{
	_userPage.addLineToPosts(post);
}


/* This function is responsible for adding new friend */
/* input: new friend */
/* output: none */
void Profile::addFriend(const User& friend_to_add)
{
	_friends.add(friend_to_add);
}


/* This function is responsible for returning the page */
/* input: none */
/* output: string page */
std::string Profile::getPage() const
{

	return "Status: " + _userPage.getStatus() + "\n*******************\n*******************\n" + _userPage.getPosts();
}


/* This function is responsible for returning the friends */
/* input: none */
/* output: string friends */
std::string Profile::getFriends() const
{
	UserNode* currFriend = NULL;
	std::string allFriends = "";

	if (_friends.get_first())
	{
		currFriend = _friends.get_first();
	}
	
	while (currFriend)
	{
		if (!currFriend->get_next())
		{
			allFriends += currFriend->get_data().getUserName();
		}
		else
		{
			allFriends += currFriend->get_data().getUserName() + ',';
		}

		currFriend = currFriend->get_next();
	}

	return allFriends;
}



/* This function is responsible for returning the friends with the same name length*/
/* input: string friends with same name length  */
/* output: none */
std::string Profile::getFriendsWithSameNameLength() const
{
	UserNode* currFriend = NULL;
	std::string allFriends = "";
	unsigned int nameSize = 0;

	if (_friends.get_first())
	{
		currFriend = _friends.get_first();
		nameSize = currFriend->get_data().getUserName().length();
	}

	while (currFriend)
	{
		if (currFriend->get_data().getUserName().length() == nameSize)
		{
			if (!currFriend->get_next())
			{
				allFriends += currFriend->get_data().getUserName();
			}
			else
			{
				allFriends += currFriend->get_data().getUserName() + ',';
			}
		}

		currFriend = currFriend->get_next();
	}

	return allFriends;
}


/* This function is responsible for changing all the words to a specific word in the status */
/* input: word */
/* output:none */

void Profile::changeAllWordsInStatus(const std::string word) 
{
	const std::string status = _userPage.getStatus();
	std::string newStatus = "";
	bool onWord = (status[0] != ' ' && status[0] != '\t' && status[0] != '\n');

	for (int i = 0; status[i]; i++)
	{
		if ((status[i] != ' ' && status[i] != '\t' && status[i] != '\n') && onWord)
		{
			onWord = false;
			newStatus += word;
		}
		else
		{
			newStatus += status[i];
			onWord = true;
		}
	}

	_userPage.setStatus(newStatus);
}


/* This function is responsible for replacing one word with another */
/* input: word to replace and new word */
/* output: none */
void Profile::changeWordInStatus(const std::string word_to_replace, const std::string new_word)
{
	const std::string status = _userPage.getStatus();

	std::string newStatus = "";
	std::string checkForWord = "";

	for (int i = 0; i < status.length(); i++)
	{
		if (status[i] == ' ' || status[i] == '\t' || status[i] == '\n')
		{
			newStatus += status[i]; 
			onWord = false;
		}
		else
		{
			if (!onWord) 
			{
				newStatus += word; 
				onWord = true;
			}
			
		}
	}
	_userPage.setStatus(newStatus);
}
}
