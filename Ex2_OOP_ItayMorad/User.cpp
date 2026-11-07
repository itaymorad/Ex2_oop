#include <iostream>
#include <string>
#include "User.h"
#include "DeviceList.h"
using namespace std;


/* This function is responsible for getting the user name */
/* input: none */
/* output: the user name */
std::string User::getUserName() const
{
	return _username;
}


/* This function is responsible for getting the id */
/* input: none */
/* output: the id */
unsigned int User::getID() const
{
	return _id;
}


/* This function is responsible for getting the age */
/* input: none */
/* output: the age */
unsigned int User::getAge() const
{
	return _age;
}


/* This function is responsible for checking if all devices are on */
/* input: none */
/* output: true/false */
bool User::checkIfDevicesAreOn() const
{
	bool isDeviceAct = true;
	DeviceNode* currDev = new DeviceNode;
	currDev = _allDevs.get_first();

	while (currDev->get_next())
	{
		if (!currDev->get_data().isActive())
		{
			isDeviceAct = false;
			break;
		}

		currDev = currDev->get_next();
	}

	delete currDev;

	return isDeviceAct;
}


/* This function is responsible for adding another device */
/* input: the new device */
/* output: none */
void User::addDevice(const Device newDevice)
{
	_allDevs.add(newDevice);
}


/* This function is responsible for clearing all devices */
/* input: none */
/* output: none */
void User::clear()
{
	DeviceNode* currDev = new DeviceNode;
	DeviceNode* temp = NULL;

	currDev = _allDevs.get_first();
	temp = currDev;

	while (!currDev)
	{
		currDev = currDev->get_next();
		delete temp;
		temp = currDev;
	}

	currDev = NULL;
	temp = NULL;
}


/* This function is responsible for getting all the devices */
/* input: none */
/* output: all devices */
const DevicesList& User::getDevices() const
{
	return _allDevs;
}

