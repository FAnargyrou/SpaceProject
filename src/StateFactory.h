#ifndef STATEFACTORY_H
#define STATEFACTORY_H

#include <functional>
#include <assert.h>

#include "State.h"

enum States
{
	PLAY_STATE,
	PAUSE_STATE,
	MENU_STATE,
	BLANK_STATE
};

class StateFactory : sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear
	};

	template <class T> 
	void RegisterId(States stateId);

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* window);

	void PushState(States stateId);
	void PopState();
	void ClearStates();

	bool IsEmpty();

private:
	struct PendingChange
	{
		PendingChange(Action action, States state = States::BLANK_STATE);

		Action _action;
		States _state;
	};

	State::StatePtr CreateState(States stateId);

	void ApplyPendingChanges();

	std::vector<State::StatePtr> _states;
	std::vector<PendingChange> _pendingChanges;

	std::map<States, std::function<State::StatePtr()>> _functions;
};

template <class T>
void StateFactory::RegisterId(States stateId)
{
	_functions[stateId] = [this]()
	{
		return State::StatePtr(new T());
	};
}

#endif