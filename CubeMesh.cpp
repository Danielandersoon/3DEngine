#include "CubeMesh.h"

namespace engine
{
	template<typename T>
	CubeMesh<T>::CubeMesh() :
	xPos(0),
	yPos(0),
	zPos(0),
	xSize(0),
	ySize(0),
	zSize(0),

	{
	}

	template<typename T>
	CubeMesh<T>::CubeMesh(T inxPos, T inyPos, T inzPos, T inxSize, T inySize, T inzSize) :
	xPos(inxPos),
	yPos(inyPos),
	zPos(inzPos),
	xSize(inxSize),
	ySize(inySize),
	zSize(inzSize),

	{
	}


	template<typename T>
	CubeMesh<T>::CubeMesh(const sf::Vector3<T> position, const sf::Vector3<T> size) :
	xPos(position.x),
	yPos(position.y),
	zPos(position.z),
	xSize(size.x),
	ySize(size.y),
	zSize(size.z),

	{
	}
}