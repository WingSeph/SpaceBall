#include "Pawn.h"

#include "ContactListener.h"

MyContactListener::MyContactListener()
{}

MyContactListener::~MyContactListener()
{}

void MyContactListener::BeginContact(b2Contact* _contact)
{
	Pawn* pawn1 = static_cast<Pawn*>(_contact->GetFixtureA()->GetBody()->GetUserData());
	Pawn* pawn2 = static_cast<Pawn*>(_contact->GetFixtureA()->GetBody()->GetUserData());

	if (pawn1)
	{
		static_cast<Pawn*>(pawn1)->startContact();
	}
	 
	if (pawn2)
	{
		static_cast<Pawn*>(pawn2)->endContact();
	}

	if (pawn1 != nullptr && pawn2 != nullptr)
	{
		pawn1->OnCollisionEnter(pawn2);
		pawn2->OnCollisionEnter(pawn1);
	}
}

void MyContactListener::EndContact(b2Contact* _contact)
{
	void* bodyUserData = _contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<Pawn*>(bodyUserData)->endContact();
	}

	bodyUserData = _contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<Pawn*>(bodyUserData)->endContact();
	}
}