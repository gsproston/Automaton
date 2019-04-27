#include "Resource.h"

Resource::Resource(const sf::Vector2f vfMapPos,
	const sf::Color colour,
	const typeEnum type) :
	PointBased(vfMapPos),
	m_type(type)
{
	// construct vertex array
	static const uint8_t iSize = 4;

	// init the vertices
	// top left
	m_aVertices[0] = sf::Vertex(
		vfMapPos,
		colour);
	// top right
	m_aVertices[1] = sf::Vertex(
		vfMapPos + sf::Vector2f(iSize, 0),
		colour);
	// bottom right
	m_aVertices[2] = sf::Vertex(
		vfMapPos + sf::Vector2f(iSize, iSize),
		colour);
	m_aVertices[3] = sf::Vertex(
		vfMapPos + sf::Vector2f(iSize, iSize),
		colour);
	// bottom left
	m_aVertices[4] = sf::Vertex(
		vfMapPos + sf::Vector2f(0, iSize),
		colour);
	m_aVertices[5] = sf::Vertex(
		vfMapPos,
		colour);
}

Resource::~Resource() {}


void Resource::addVertices(std::vector<sf::Vertex>& rvVertices) const
{
	for (uint8_t i = 0; i < 6; ++i)
	{
		rvVertices.push_back(m_aVertices[i]);
	}
}