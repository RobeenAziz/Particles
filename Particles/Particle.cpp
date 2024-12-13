#include "Particle.h"
#include <iostream>
using namespace sf;
using namespace Matrices;
using namespace std;

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2,numPoints) {
  m_ttl = TTL;
  m_numPoints = numPoints;
  m_radiansPerSec = static_cast<float>(rand()) / RAND_MAX * M_PI;
  m_cartesianPlane.setCenter(0,0);
  
  m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
  m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);
  
  m_vx = rand() % 400 + 100;
  if(rand() % 2 == 1){
    m_vx = -m_vx;
  }

  m_vy = rand() %400 + 100;
  if(rand() % 2 == 1){
    m_vy = -m_vy;
  }

  m_color1 = Color::White;
  m_color2 = Color(rand() % 256, rand() % 256, rand() % 256);

  float theta = static_cast<float>(rand()) / RAND_MAX * (M_PI / 2);
  float dTheta = 2 * M_PI / (numPoints - 1);

  for(int j = 0; j < numPoints; j++){
    float r = rand() % 61 + 20;
    float dx = r * cos(theta);
    float dy = r * sin(theta);

    m_A(0, j) = m_centerCoordinate.x + dx;
    m_A(1, j) = m_centerCoordinate.y + dy;

    theta += dTheta;
  }
}
  
  void Particle::draw(RenderTarget & target, RenderStates states) const
{
	VertexArray lines(TriangleFan, m_numPoints + 1);
	Vector2f center;
	center = static_cast<Vector2f>(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane));
	lines[0].position = center;
	lines[0].color = m_color1;
	for (int j = 1; j <= m_numPoints; ++j)
	{
		lines[j].position = target.mapCoordsToPixel(Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane); 
		lines[j].color = m_color2;
	}
	target.draw(lines);
}

void update(float dt)
{
	m_ttl = m_ttl - dt;
	rotate(dt * m_radiansPerSec);
	scale(SCALE);
	float dx, dy;
	dx = m_vx * dt;
	m_vy = m_vy - (G * dt);
	dy = m_vy * dt;
	translate(dx, dy);
}

translate(double xShift, double yShift)
{
	TranslationMatrix T(xShift, yShift, m_numPoints);
	m_A = T + m_A
	m_centerCoordinate.x += xShift;
	m_centerCoordinate.y += yShift;
}

rotate(double theta)
{
	Vector2f temp = m_centerCoordinate;
	translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
	RotationMatrix R(theta);
	m_A = R * m_A;
	translate(temp.x, temp.y);
}

scale(double c)
{
	Vector2f temp = m_centerCoordinate;
	translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
	ScalingMatrix S(c);
	m_A = S * m_A;
	translate(temp.x, temp.y);
}
  
}


bool Particle::almostEqual(double a, double b, double eps)
{
return fabs(a - b) < eps;
}
