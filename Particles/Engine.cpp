#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particle System");
}

void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	while (m_Window.isOpen())
	{
		clock.restart();
		Time curtime;
		float seconds;
		curtime = clock.getElapsedTime();
		seconds = curtime.asSeconds();
		input();
		update(seconds);
		draw();
	}
}
