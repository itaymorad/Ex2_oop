#include <iostream>
#include <string>
#include "Page.h"
using namespace std;


/* This function is responsible for initializing the page */
/* input: none */
/* output: none */
void Page::init()
{
	_posts = "";
	_status = "";
}


/* This function is responsible for getting the posts */
/* input: none */
/* output: posts */
std::string Page::getPosts() const
{
	return _posts;
}


/* This function is responsible for getting the status */
/* input: none */
/* output: status */
std::string Page::getStatus() const
{
	return _status;
}	


/* This function is responsible for clearing the page */
/* input: none */
/* output: none */
void Page::clearPage()
{
	_posts = "";
	_status = "";
}


/* This function is responsible for setting the status */
/* input: status */
/* output: none */
void Page::setStatus(const std::string status)
{
	_status = status;
}


/* This function is responsible for adding line to posts */
/* input: status */
/* output: none */
void Page::addLineToPosts(const std::string new_line)
{
	_posts = new_line + '\n';
}

