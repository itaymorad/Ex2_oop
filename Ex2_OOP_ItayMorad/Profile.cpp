The segmentation fault is happening immediately when you try to add friends because you never initialized the `_friends` list inside your `init()` function.

Because `UserList` relies on an `init()` method instead of a standard C++ constructor, `_friends` starts with unallocated, garbage memory.When the test loop calls `addFriend` and attempts to insert a node, it tries to access a garbage pointer and instantly crashes with Exit 139.

Additionally, your `getFriends` functions have a string formatting bug.By checking `!currFriend->get_next()`, you leave a trailing comma(like `Alice,Bob, `) if the last friends in the list don't match the name length. You also mistakenly checked the name length against the *first friend in the list*, rather than the *owner of the profile*.

	Here is the fully repaired `Profile.cpp` that adds the missing `_friends.init()`, cleans up the owner to stop the leak, and uses a much safer comma - checking logic that perfectly satisfies your constraint of using only a single `return` statement at the end of the functions.

	```cpp
#include <string>
#include "Profile.h"
	using namespace std;

/* This function is responsible for initializing the profile */
/* input: owner */
/* output: none */
void Profile::init(const User & owner)
{
	_owner.init(owner.getID(), owner.getUserName(), owner.getAge());

	DeviceNode* curr = owner.getDevices().get_first();
	while (curr)
	{
		_owner.addDevice(curr->get_data());
		curr = curr->get_next();
	}

	_userPage.init();
	_friends.init(); // CRITICAL FIX: Initializes the list so addFriend does not segfault
}

/* This function is responsible for clearing the profile */
/* input: none */
/* output: none */
void Profile::clear()
{
	_owner.clear(); // CRITICAL FIX: Clears the deep-copied devices to stop the memory leak
	_userPage.clearPage();
	_friends.clear();
}

/* This function is responsible for getting the owner */
/* input: none */
/* output: owner */
const User& Profile::getOwner() const
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
void Profile::addFriend(const User & friend_to_add)
{
	User friend_info;
	friend_info.init(friend_to_add.getID(), friend_to_add.getUserName(), friend_to_add.getAge());

	_friends.add(friend_info);
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
	UserNode* currFriend = _friends.get_first();
	std::string allFriends = "";

	while (currFriend)
	{
		if (allFriends == "")
		{
			allFriends += currFriend->get_data().getUserName();
		}
		else
		{
			allFriends += "," + currFriend->get_data().getUserName();
		}

		currFriend = currFriend->get_next();
	}

	return allFriends;
}

/* This function is responsible for returning the friends with the same name length*/
/* input: none  */
/* output: string friends */
std::string Profile::getFriendsWithSameNameLength() const
{
	UserNode* currFriend = _friends.get_first();
	std::string allFriends = "";
	const unsigned int nameSize = _owner.getUserName().length(); // Must check against the profile owner's name

	while (currFriend)
	{
		if (currFriend->get_data().getUserName().length() == nameSize)
		{
			if (allFriends == "")
			{
				allFriends += currFriend->get_data().getUserName();
			}
			else
			{
				allFriends += "," + currFriend->get_data().getUserName();
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
	bool onWord = false;

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

/* This function is responsible for replacing one word with another */
/* input: word to replace and new word */
/* output: none */
void Profile::changeWordInStatus(const std::string word_to_replace, const std::string new_word)
{
	const std::string status = _userPage.getStatus();
	std::string newStatus = "";
	std::string currentWord = "";

	for (int i = 0; i < status.length(); i++)
	{
		if (status[i] != ' ' && status[i] != '\t' && status[i] != '\n')
		{
			currentWord += status[i];
		}
		else
		{
			if (currentWord == word_to_replace)
			{
				newStatus += new_word;
			}
			else
			{
				newStatus += currentWord;
			}

			newStatus += status[i];
			currentWord = "";
		}
	}

	if (currentWord == word_to_replace)
	{
		newStatus += new_word;
	}
	else
	{
		newStatus += currentWord;
	}

	_userPage.setStatus(newStatus);
}

```