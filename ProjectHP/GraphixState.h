#pragma once
#include "General.h"
#include "HumanObject.h"

//=============================================================================

//abstract state class
class GraphixState
{
public:
	virtual void enter(HumanObject& obj) = 0;
	virtual shared_ptr<GraphixState>	handleInput(GameState input) = 0;
	virtual string name() = 0;
};

//=============================================================================

//the walk state class
class WalkState: public GraphixState
{
public:
	shared_ptr<GraphixState> handleInput(GameState input) override;

	void enter(HumanObject& obj);

	string name() { return "walk"; }
};

//=============================================================================

//the shoot state class
class ShootState : public GraphixState 
{
public:
	shared_ptr<GraphixState> handleInput(GameState input) override;

	void enter(HumanObject& obj);

	string name() { return "spell"; }
};

//=============================================================================

//the wand state class
class WandState : public GraphixState
{
public:
	shared_ptr<GraphixState> handleInput(GameState input) override;

	void enter(HumanObject& obj);

	string name() { return "Sspell"; }
};

//=============================================================================

//the sword state class
class SwordState : public GraphixState
{
public:
	shared_ptr<GraphixState> handleInput(GameState input) override;

	void enter(HumanObject& obj);

	string name() { return "sword"; }
};

//=============================================================================

