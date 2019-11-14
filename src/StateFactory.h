#ifndef STATEFACTORY_H
#define STATEFACTORY_H

#include <functional>
#include <assert.h>

#include "State.h"

class StateFactory : sf::NonCopyable
{
public:

	StateFactory(State::Settings settings);

	enum Action
	{
		Push,
		Pop,
		Clear
	};

	template <class T> 
	void RegisterId(States stateId);

	void update(sf::Time deltaTime);
	void render();
	void HandleEvent(const sf::Event& event);

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

	State::Settings _settings;
};

template <class T>
void StateFactory::RegisterId(States stateId)
{
	_functions[stateId] = [this]()
	{
		return State::StatePtr(new T(*this, _settings));
	};
}

#endif