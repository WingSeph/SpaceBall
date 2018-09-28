#pragma once
#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__

#include "Utilities.h"

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);

private:

};

#endif // !__CONTACTLISTENER_H__
