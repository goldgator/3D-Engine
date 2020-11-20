#include "pch.h"
#include "InputSystem.h"

bool nc::InputSystem::Startup()
{
	// get current keystate and retrieve numKeys
			// get current keystate and retrieve numKeys
	const Uint8* keystate = SDL_GetKeyboardState(&m_numKeys);

	// allocate memory for current and previous keystate
	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];
	// copy current keystate (source) to m_keystate (destination)
	memcpy(m_keystate, keystate, m_numKeys);
	// copy current keystate to m_prevKeystate
	memcpy(m_prevKeystate,m_keystate, m_numKeys);

	return true;

}

void nc::InputSystem::Shutdown()
{
	delete[] m_keystate;
	delete[] m_prevKeystate;
}

void nc::InputSystem::Update()
{
	// copy m_keystate (source) to m_prevKeystate (destination)
	memcpy(m_prevKeystate, m_keystate , m_numKeys);
	// get current keystate
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	// copy current keystate to m_keystate
	memcpy(m_keystate, keystate, m_numKeys);

}

nc::InputSystem::eButtonState nc::InputSystem::GetButtonState(int id)
{
	eButtonState state = eButtonState::IDLE;

	bool buttonDown = GetButtonDown(id);
	bool prevButtonDown = GetPreviousButtonDown(id);

	if (buttonDown)
	{
		//current state = 1				true			false
		state = (prevButtonDown) ? eButtonState::HELD : eButtonState::PRESSED ;
	}
	else
	{
		//current state = 0			true						false
		state = (prevButtonDown) ? eButtonState::RELEASED : eButtonState::IDLE ;
	}

	return state;

}

bool nc::InputSystem::GetButtonDown(int id)
{
	return m_keystate[id];
}

bool nc::InputSystem::GetPreviousButtonDown(int id)
{

	return m_prevKeystate[id];
}
