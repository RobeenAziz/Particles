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
	    Time curtime;
            curtime = clock.restart();
            float seconds;
            seconds = curtime.asSeconds();
            input();
            update(seconds);
            draw();
	}
}

void Engine::update(float dtAsSeconds)
{
	for (vector<Particle>::iterator i = m_particles.begin(); i != m_particles.end();)
	{
		if (i->getTTL() > 0)
		{
			i->update(dtAsSeconds);
			++i;
		}
		else
		{
			i = m_particles.erase(i);
		}
	}

}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); ++i)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}

void Engine::input() {
	Event event;

	while (m_Window.pollEvent(event)) {
		if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			Vector2i mouseClickPosition = Mouse::getPosition(m_Window);

			for (int i = 0; i < 5; i++) {
				int numPoints = rand() % 26 + 25;
				m_particles.push_back(Particle(m_Window, numPoints, mouseClickPosition));

			}
		}
	}
}
