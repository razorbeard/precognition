#include "game_manager.hpp"

#include "menu_state.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Cursor.hpp>

const sf::Time GameManager::sTimePerFrame = sf::seconds(1.0f / 60.0f);

GameManager::GameManager()
	: mWindow({ 1024, 768 }, "Precognition", sf::Style::Close)
{
	mWindow.setVerticalSyncEnabled(true);

	pushState<MenuState>(this);
}

void GameManager::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Main loop
	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > sTimePerFrame)
		{
			timeSinceLastUpdate -= sTimePerFrame;

			processInput();

			if (!mStack.empty())
      {
        mStack.top()->update(sTimePerFrame);
      }
      else
      {
				mWindow.close();
      }
		}

		render();
	}
}

void GameManager::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (!mStack.empty())
    {
			mStack.top()->handleEvent(event);
    }

		if (event.type == sf::Event::Closed)
    {
			mWindow.close();
    }
	}
}

void GameManager::render()
{
	mWindow.clear();

	if (!mStack.empty())
  {
		mStack.top()->draw();
  }

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

std::unique_ptr<State> GameManager::popState()
{
	if (!mStack.empty())
	{
		std::unique_ptr<State> ref = std::move(mStack.top());
		mStack.pop();
		return ref;
	}

	return nullptr;
}
