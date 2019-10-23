#include "StateFactory.h"

void StateFactory::update(sf::Time deltaTime)
{
	for (auto state = _states.rbegin(); state != _states.rend(); state++ )
		if (!(*state)->update(deltaTime))
			break;
	ApplyPendingChanges();
}

void StateFactory::render(sf::RenderWindow* window)
{
	for (auto state = _states.rbegin(); state != _states.rend(); state++)
		(*state)->render(window);
}

void StateFactory::PushState(States stateId)
{
	_pendingChanges.push_back(PendingChange(Action::Push, stateId));
}

void StateFactory::PopState()
{
	_pendingChanges.push_back(PendingChange(Action::Pop));
}

void StateFactory::ClearStates()
{
	_pendingChanges.push_back(PendingChange(Action::Clear));
}

bool StateFactory::IsEmpty()
{
	if (_states.empty())
		return true;
	return false;
}

State::StatePtr StateFactory::CreateState(States stateId)
{
	auto function = _functions.find(stateId);
	assert(function != _functions.end());

	return function->second();
}

void StateFactory::ApplyPendingChanges()
{
	for (PendingChange change : _pendingChanges)
	{
		switch (change._action)
		{
		case Action::Push:
			if (change._state != States::BLANK_STATE)
			{
				_states.push_back(CreateState(change._state));
				_states.back()->load();
			}
			break;
		case Action::Pop:
			_states.pop_back();
			break;
		case Action::Clear:
			_states.clear();
			break;
		}
	}
	_pendingChanges.clear();
}

StateFactory::PendingChange::PendingChange(Action action, States state)
	: _action(action),
	_state(state)
{
}