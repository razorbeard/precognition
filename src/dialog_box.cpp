#include "dialog_box.hpp"

#include "game_manager.hpp"
#include "utils.hpp"

DialogBox::DialogBox(GameManager* game, const Dialog& message)
	: mShowArrow(false)
	, mMessage(message)
	, mCurrentLine(0)
	, mSubstrIdx(0)
{
	mFont.loadFromFile("resources/fonts/PressStart2P.ttf");

	mBox.setSize(sf::Vector2f(game->mWindow.getSize().x - 100.0f, game->mWindow.getSize().y / 4u));
	mBox.setFillColor(sf::Color::Black);
	mBox.setOutlineColor(sf::Color::White);
	mBox.setOutlineThickness(4.0f);
	mBox.setPosition(sf::Vector2f(game->mWindow.getSize().x / 2u, game->mWindow.getSize().y * 0.8f));
	centerOrigin(mBox);

	sf::FloatRect const boxRect{ mBox.getGlobalBounds() };

	mArrow.setRadius(15.0f);
	mArrow.setPointCount(3);
	mArrow.rotate(180.0f);
	mArrow.setPosition(boxRect.left + boxRect.width - 30.0f, boxRect.top + boxRect.height - 30.0f);
	centerOrigin(mArrow);

	postTreatment(mMessage);
	mDialog.setString("");
	mDialog.setFont(mFont);
	mDialog.setCharacterSize(23);
	mDialog.setPosition(boxRect.left + 40.0f, boxRect.top + 40.0f);
}

void DialogBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBox, states);
	target.draw(mDialog, states);

	if (mShowArrow)
  {
		target.draw(mArrow, states);
  }
}

bool DialogBox::hasFinishedAllLines()
{
	// In addition of the size check, we confirm that the line has been totally displayed
	if ((mCurrentLine == mMessage.lines.size() - 1) && hasFinishedCurrentLine())
	{
    return true;
  }

	return false;
}

bool DialogBox::hasFinishedCurrentLine()
{
	if (mDialog.getString() == mMessage.lines[mCurrentLine])
	{
    return true;
  }

	return false;
}

void DialogBox::update(sf::Time dt)
{
	mElapsedTime += dt;
	static sf::Clock timer;

	if (hasFinishedCurrentLine() && mMessage.isSkippable)
  {
    mShowArrow = true;
  }
  else
  {
		mShowArrow = false;
  }

	// Give an "up-down" effect to the arrow
	mArrow.move(0.0f, 0.5f * std::sin(10.0f * mElapsedTime.asSeconds()));

	// Scrolling text
	if (timer.getElapsedTime() > sf::seconds(0.05f) && mSubstrIdx <= mMessage.lines[mCurrentLine].length())
	{
		mDialog.setString(mMessage.lines[mCurrentLine].substr(0, mSubstrIdx));

		mSubstrIdx++;
		timer.restart();
	}
}

void DialogBox::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		// Arrow is shown: pass to the next line of dialog
		if (event.mouseButton.button == sf::Mouse::Left && mShowArrow)
		{
			if (mCurrentLine < mMessage.lines.size() - 1)
			{
				++mCurrentLine;
				mSubstrIdx = 0; // Reset substr cursor
			}

			// Jump to the next dialog message
			if (hasFinishedAllLines() && !mNextMessage.lines.empty())
			{
				mMessage = mNextMessage;
				mNextMessage = {}; // Empty the next message

				mCurrentLine = 0;
				mSubstrIdx = 0;
				mShowArrow = false;
			}
		}
	}
}

void DialogBox::addNewMessage(const Dialog& message)
{
	mNextMessage = message;
	postTreatment(mNextMessage);
}

int DialogBox::getCurrentLine() const
{
	return mCurrentLine;
}

void DialogBox::postTreatment(Dialog& message)
{
	// Maximum 36 char per line
	std::size_t chunkSize = 37;

	for (auto& line : message.lines)
	{
		if (line.length() < chunkSize)
			continue;

		std::string output;
		std::size_t idx = 0;

		while (idx < line.length() - chunkSize) // Omit the last chunk
		{
			std::string substring = line.substr(idx, chunkSize);
			auto found = substring.rfind(' ');
			if (found != std::string::npos)
			{
				substring.erase(substring.begin() + found, substring.end());
				substring.append("\n\n");
			}
			output.append(substring);
			idx += found + 1;
		}

		output.append(line.substr(idx, line.length()));
		line = output;
	}
}
