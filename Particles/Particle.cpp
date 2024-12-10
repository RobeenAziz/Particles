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
