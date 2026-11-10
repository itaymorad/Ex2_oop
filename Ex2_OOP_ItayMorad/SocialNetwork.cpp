#include <string>
#include "SocialNetwork.h"
#include "ProfileList.h"
#include "DeviceList.h"
using namespace std;


/* This function is responsible for initializing the social network */
/* input: networkname and minimal age */
/* output: none */
void SocialNetwork::init(const std::string networkName, const int minAge)
{
	_networkName = networkName;
	_minAge = minAge;
	_profiles.init();
}


/* This function is responsible for clearing the social network */
/* input: none */
/* output: none */
void SocialNetwork::clear()
{
	_profiles.clear();
}


/* This function is responsible for getting the network name */
/* input: none */
/* output: network name */
std::string SocialNetwork::getNetworkName() const
{
	return _networkName;
}


/* This function is responsible for getting the minimal age */
/* input: none */
/* output: minimal age */
int SocialNetwork::getMinAge() const
{
	return _minAge;
}




/* This function is responsible for returning a list of connected windows devices */
/* input: none */
/* output: a list of connected windows devices */
bool SocialNetwork::addProfile(const Profile& profile_to_add)
{
	bool worked = false;

	if (profile_to_add.getOwner().getAge() >= _minAge)
	{
		if (_profiles.add(profile_to_add))
		{
			worked = true;
		}
	}

	return worked;
}

/* This function is responsible for returning a list of connected windows devices */
/* input: none */
/* output: a list of connected windows devices */
std::string SocialNetwork::getWindowsDevices() const
{
	ProfileNode* currProfile = _profiles.get_first();
	std::string winDevices = "";
	std::string oneDevice = "";

	while (currProfile)
	{
		DeviceNode* currDevice = currProfile->get_data().getOwner().getDevices().get_first();

		while (currDevice)
		{
			std::string os = currDevice->get_data().getOS();

			if (os == "Windows11" || os == "Windows10" || os == "Windows7")
			{
				oneDevice = "[" + std::to_string(currDevice->get_data().getID()) + ", " + os + "]";

				if (winDevices == "")
				{
					winDevices += oneDevice;
				}
				else
				{
					winDevices += ", " + oneDevice;
				}
			}

			currDevice = currDevice->get_next();
		}

		currProfile = currProfile->get_next();
	}

	return winDevices;
}