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


/* This function is responsible for adding a profile */
/* input: new profile */
/* output: success/not */
bool SocialNetwork::addProfile(const Profile& profile_to_add)
{
	bool worked = false;

	Profile profile_info;
	profile_info.init(profile_to_add.getOwner());

	if (_profiles.add(profile_info))
	{
		worked = true;
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

	while (currProfile)
	{
		User user = currProfile->get_data().getOwner();
		DeviceNode* currDevice = user.getDevices().get_first();

		while (currDevice)
		{
			Device device = currDevice->get_data();
			std::string os = device.getOS();

			if (os == WINDOWS11 || os == WINDOWS10 || os == WINDOWS7)
			{
				if (winDevices != "")
				{
					winDevices += ", ";
				}
				winDevices += "[" + std::to_string(device.getID()) + ", " + os + "]";
			}

			currDevice = currDevice->get_next();
		}

		currProfile = currProfile->get_next();
	}

	return winDevices;
}