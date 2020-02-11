#include "SolarSystem.h"

SolarSystem::SolarSystem() {}

void SolarSystem::updateStatus(float time)
{
	// Cập nhật lại trạng thái cả tất cả các Planets sau khoảng thời gian time
	for (int i = 0; i < planets.size(); i++) {
		planets[i].updateStatus(time);
	}
}

void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

void SolarSystem::addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets[planetIndex].addMoon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

void SolarSystem::render()
{
	// Vẽ tất cả các Planet trong Solar System
	for (int i = 0; i < planets.size(); i++) {
		planets[i].render();
	}
}


void SolarSystem::renderOrbits()
{
	// Vẽ quỹ đạo của tất cả các Planet trong Solar System
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].renderOrbit();
	}
}

void SolarSystem::getPlanetPosition(int index, float vec[3])
{
	planets[index].getPosition(vec);
}

float SolarSystem::getRadiusOfPlanet(int index)
{
	return planets[index].getRadius();
}

void SolarSystem::renderPlanet(int index)
{
	if (index != -1)
		planets[index].renderOnly();
}
