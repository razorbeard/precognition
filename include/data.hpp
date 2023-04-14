#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
#include <string>

// 1 line = max 36*3 = 108 characters
using Lines = std::vector<std::string>;

struct Dialog
{
	Lines lines;
	bool isSkippable = true;
	// std::string speaker;
};

namespace Intro
{
	enum class ID
	{
		Colonel,
		Captain
	};

	const Dialog colonel = { { "Ha... It's you. My guys said you can slightly see the future.",
							   "Well, I don't know if that's true, but I must go to the toilets.",
							   "Take command and lead us to victory !" }
	};

	const Dialog captain{ { "...",
							"...",
							"Hey small fry, the colonel wants me to tell you the current situation.",
							"Right now, we've been surrounded by many of these hideous aliens.",
							"Their strength and intelligence are far superior to us, they came well prepared.",
							"If we don't act quickly, Earth will be doomed. We need your ability to turn the tide.",
							"The green point is one of our bases, and the red one is an ennemy base.",
							"We don't know about the white points, but we must retake them before the aliens do.",
							"These are your action points for every day, use them wisely.",
							"You can train our troops, improve our defenses or attack a base when needed.",
							"Good luck small fry, our future is in your hands..."}
	};
}

namespace Game
{
	enum class ID
	{
		Victory,
		Gameover,
		PlayerTurn,
	};

	const Dialog victory = { {"Victory ! You successfully push back all enemy onslaughts !"} };
	const Dialog gameover = { {"Game Over... Aliens take over Humanity..."} };

	const Dialog playerTurn = { {"Select your next actions."}, false };
}

#endif
