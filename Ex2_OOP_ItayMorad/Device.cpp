#include <iostream>
#include <string>
#include "Device.h"
using namespace std;


/* This function is responsible for getting the os of the device */
/* input: none */
/* output: the os */
std::string Device::getOS() const
{
	return _devOs;
}


/* This function is responsible for getting if the device is active or not */
/* input: none */
/* output: true/false */
bool Device::isActive() const
{
	return _isDevActive;
}


/* This function is responsible for activating the device */
/* input: none */
/* output: none */
void Device::activate()
{
	_isDevActive = true;
}


/* This function is responsible for deactivating the device */
/* input: none */
/* output: none */
void Device::deactivate()
{
	_isDevActive = false;
}


/* This function is responsible for getting the id of the device */
/* input: none */
/* output: the device id */
unsigned int Device::getID() const
{
	return _devId;
}


/* This function is responsible for getting the os type of the device */
/* input: none */
/* output: the device id */
DeviceType Device::getType() const
{
	return _devType;
}


/* This function is responsible for initializing the device */
/* input: id, type and os */
/* output: none */
void Device::init(const unsigned int id, const DeviceType type, const std::string os)
{
	_devId = id;
	_devType = type;
	_devOs = os;
}