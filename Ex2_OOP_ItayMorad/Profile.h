#pragma once


#include <string>
#include "User.h"
#include "Page.h"
#include "UserList.h"


class Profile
{

public:
	void init(const User owner);
	void clear();
	User getOwner() const;	
	void setStatus(const std::string new_status);
	void addPostToProfilePage(const std::string post);
	void addFriend(User friend_to_add);
	std::string getPage() const;
	std::string getFriends() const;
	std::string getFriendsWithSameNameLength() const;
	void changeAllWordsInStatus(const std::string word);
	void changeWordInStatus(const std::string word_to_replace, const std::string new_word);

private:
	UserList _friends;
	Page _userPage;
	User _owner;

};