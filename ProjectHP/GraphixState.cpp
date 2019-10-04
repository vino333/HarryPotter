#include "GraphixState.h"

//=============================================================================

//handleInput of walk state
shared_ptr<GraphixState> WalkState::handleInput(GameState input)
{
	shared_ptr<GraphixState> newState;

	switch (input)
	{
	case SHOOTATTAK:
	{
		newState = make_shared<ShootState>();
		break;
	}
	case WANDATTAK:
	{
		newState = make_shared<WandState>();
		break;
	}
	case SWORDATTAK:
	{
		newState = make_shared<SwordState>();
		break;
	}
	}

	return newState;
}

//=============================================================================

//enter function of walk state
void WalkState::enter(HumanObject& obj)
{
	obj.setGraphixState(WALK);
}

//=============================================================================

//handleInput of shoot state
shared_ptr<GraphixState> ShootState::handleInput(GameState input)
{
	shared_ptr<GraphixState> newState;

	switch (input)
	{
	case WALK:
	{
		return make_shared<WalkState>();
		break;
	}
	case WANDATTAK:
	{
		newState = make_shared<WandState>();
		break;
	}
	case SWORDATTAK:
	{
		newState = make_shared<SwordState>();
		break;
	}
	}

	return newState;
}

//=============================================================================

//enter function of shoot state
void ShootState::enter(HumanObject& obj)
{
	obj.setGraphixState(SHOOTATTAK);
}

//=============================================================================

//handleInput of wand state
shared_ptr<GraphixState> WandState::handleInput(GameState input)
{
	shared_ptr<GraphixState> newState;

	switch (input)
	{
	case WALK:
	{
		return make_shared<WalkState>();
		break;
	}
	case SHOOTATTAK:
	{
		newState = make_shared<ShootState>();
		break;
	}
	case SWORDATTAK:
	{
		newState = make_shared<SwordState>();
		break;
	}
}

	return newState;
}

//=============================================================================

//enter function of wand state
void WandState::enter(HumanObject& obj)
{
	obj.setGraphixState(WANDATTAK);
}

//=============================================================================

//handleInput of sword state
shared_ptr<GraphixState> SwordState::handleInput(GameState input)
{
	shared_ptr<GraphixState> newState;

	switch (input)
	{
	case WALK:
	{
		return make_shared<WalkState>();
		break;
	}
	case SHOOTATTAK:
	{
		newState = make_shared<ShootState>();
		break;
	}
	case WANDATTAK:
	{
		newState = make_shared<WandState>();
		break;
	}
	}
	
	return newState;
}

//=============================================================================

//enter function of sword state
void SwordState::enter(HumanObject& obj)
{
	obj.setGraphixState(SWORDATTAK);
}

