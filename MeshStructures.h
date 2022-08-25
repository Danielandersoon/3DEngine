#pragma once
#include <string>
#include <algorithm>
#include <fstream>
#include <strstream>
#include <vector>

#include "polygon.h"

namespace Eng{

	struct Vector3
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 1;
	};

	struct Triangle
	{
		Vector3 vect[3];
		wchar_t sym;
		short col;
	};

	struct Mesh
	{
		std::vector<Triangle> mesh;

		bool LoadFromObjectFile(std::string sFilename)
		{
			std::ifstream f(sFilename);
			if (!f.is_open())
				return false;

			// Local cache of verts
			std::vector<Vector3> verts;

			while (!f.eof())
			{
				char line[128];
				f.getline(line, 128);

				std::strstream s;
				s << line;

				char junk;

				if (line[0] == 'v')
				{
					Vector3 v;
					s >> junk >> v.x >> v.y >> v.z;
					verts.push_back(v);
				}

				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					mesh.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
				}
			}
			return true;
		}
	};
};