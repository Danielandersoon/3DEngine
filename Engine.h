#pragma once
#include <list>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "MathsStructure.h"
#include "MeshStructures.h"
#include "dev/Callbacks.h"

namespace Eng {

	class Engine
	{
	public:
		Engine(unsigned int x, unsigned int y, std::string title) :
			screenX(x),
			screenY(y)
		{
			app.create(sf::VideoMode(x, y), title, sf::Style::Default);
			window_open_callback();

			OnUserCreate();

			end = false;
		};

		Vector3 Matrix_MultiplyVector(Matrix4x4& m, Vector3& i)
		{
			Vector3 v;
			v.x = i.x * m.matrix[0][0] + i.y * m.matrix[1][0] + i.z * m.matrix[2][0] + i.w * m.matrix[3][0];
			v.y = i.x * m.matrix[0][1] + i.y * m.matrix[1][1] + i.z * m.matrix[2][1] + i.w * m.matrix[3][1];
			v.z = i.x * m.matrix[0][2] + i.y * m.matrix[1][2] + i.z * m.matrix[2][2] + i.w * m.matrix[3][2];
			v.w = i.x * m.matrix[0][3] + i.y * m.matrix[1][3] + i.z * m.matrix[2][3] + i.w * m.matrix[3][3];
			return v;
		}

		Matrix4x4 Matrix_MakeIdentity()
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = 1.0f;
			matrix.matrix[1][1] = 1.0f;
			matrix.matrix[2][2] = 1.0f;
			matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Matrix4x4 Matrix_MakeRotationX(float fAngleRad)
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = 1.0f;
			matrix.matrix[1][1] = cosf(fAngleRad);
			matrix.matrix[1][2] = sinf(fAngleRad);
			matrix.matrix[2][1] = -sinf(fAngleRad);
			matrix.matrix[2][2] = cosf(fAngleRad);
			matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Matrix4x4 Matrix_MakeRotationY(float fAngleRad)
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = cosf(fAngleRad);
			matrix.matrix[0][2] = sinf(fAngleRad);
			matrix.matrix[2][0] = -sinf(fAngleRad);
			matrix.matrix[1][1] = 1.0f;
			matrix.matrix[2][2] = cosf(fAngleRad);
			matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Matrix4x4 Matrix_MakeRotationZ(float fAngleRad)
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = cosf(fAngleRad);
			matrix.matrix[0][1] = sinf(fAngleRad);
			matrix.matrix[1][0] = -sinf(fAngleRad);
			matrix.matrix[1][1] = cosf(fAngleRad);
			matrix.matrix[2][2] = 1.0f;
			matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Matrix4x4 Matrix_MakeTranslation(float x, float y, float z)
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = 1.0f;
			matrix.matrix[1][1] = 1.0f;
			matrix.matrix[2][2] = 1.0f;
			matrix.matrix[3][3] = 1.0f;
			matrix.matrix[3][0] = x;
			matrix.matrix[3][1] = y;
			matrix.matrix[3][2] = z;
			return matrix;
		}

		Matrix4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
		{
			float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
			Matrix4x4 matrix;
			matrix.matrix[0][0] = fAspectRatio * fFovRad;
			matrix.matrix[1][1] = fFovRad;
			matrix.matrix[2][2] = fFar / (fFar - fNear);
			matrix.matrix[3][2] = (-fFar * fNear) / (fFar - fNear);
			matrix.matrix[2][3] = 1.0f;
			matrix.matrix[3][3] = 0.0f;
			return matrix;
		}

		Matrix4x4 Matrix_MultiplyMatrix(Matrix4x4& m1, Matrix4x4& m2)
		{
			Matrix4x4 matrix;
			for (int c = 0; c < 4; c++)
				for (int r = 0; r < 4; r++)
					matrix.matrix[r][c] = m1.matrix[r][0] * m2.matrix[0][c] + m1.matrix[r][1] * m2.matrix[1][c] + m1.matrix[r][2] * m2.matrix[2][c] + m1.matrix[r][3] * m2.matrix[3][c];
			return matrix;
		}

		Matrix4x4 Matrix_PointAt(Vector3& pos, Vector3& target, Vector3& up)
		{
			Vector3 newForward = Vector_Sub(target, pos);
			newForward = Vector_Normalise(newForward);

			Vector3 a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
			Vector3 newUp = Vector_Sub(up, a);
			newUp = Vector_Normalise(newUp);

			Vector3 newRight = Vector_CrossProduct(newUp, newForward);

			Matrix4x4 matrix;
			matrix.matrix[0][0] = newRight.x;	matrix.matrix[0][1] = newRight.y;	matrix.matrix[0][2] = newRight.z;	matrix.matrix[0][3] = 0.0f;
			matrix.matrix[1][0] = newUp.x;		matrix.matrix[1][1] = newUp.y;		matrix.matrix[1][2] = newUp.z;		matrix.matrix[1][3] = 0.0f;
			matrix.matrix[2][0] = newForward.x;	matrix.matrix[2][1] = newForward.y;	matrix.matrix[2][2] = newForward.z;	matrix.matrix[2][3] = 0.0f;
			matrix.matrix[3][0] = pos.x;		matrix.matrix[3][1] = pos.y;		matrix.matrix[3][2] = pos.z;		matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Matrix4x4 Matrix_QuickInverse(Matrix4x4& m) // Only for Rotation/Translation Matrices
		{
			Matrix4x4 matrix;
			matrix.matrix[0][0] = m.matrix[0][0]; matrix.matrix[0][1] = m.matrix[1][0]; matrix.matrix[0][2] = m.matrix[2][0]; matrix.matrix[0][3] = 0.0f;
			matrix.matrix[1][0] = m.matrix[0][1]; matrix.matrix[1][1] = m.matrix[1][1]; matrix.matrix[1][2] = m.matrix[2][1]; matrix.matrix[1][3] = 0.0f;
			matrix.matrix[2][0] = m.matrix[0][2]; matrix.matrix[2][1] = m.matrix[1][2]; matrix.matrix[2][2] = m.matrix[2][2]; matrix.matrix[2][3] = 0.0f;
			matrix.matrix[3][0] = -(m.matrix[3][0] * matrix.matrix[0][0] + m.matrix[3][1] * matrix.matrix[1][0] + m.matrix[3][2] * matrix.matrix[2][0]);
			matrix.matrix[3][1] = -(m.matrix[3][0] * matrix.matrix[0][1] + m.matrix[3][1] * matrix.matrix[1][1] + m.matrix[3][2] * matrix.matrix[2][1]);
			matrix.matrix[3][2] = -(m.matrix[3][0] * matrix.matrix[0][2] + m.matrix[3][1] * matrix.matrix[1][2] + m.matrix[3][2] * matrix.matrix[2][2]);
			matrix.matrix[3][3] = 1.0f;
			return matrix;
		}

		Vector3 Vector_Add(Vector3& v1, Vector3& v2)
		{
			return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
		}

		Vector3 Vector_Sub(Vector3& v1, Vector3& v2)
		{
			return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
		}

		Vector3 Vector_Mul(Vector3& v1, float k)
		{
			return { v1.x * k, v1.y * k, v1.z * k };
		}

		Vector3 Vector_Div(Vector3& v1, float k)
		{
			return { v1.x / k, v1.y / k, v1.z / k };
		}

		float Vector_DotProduct(Vector3& v1, Vector3& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		float Vector_Length(Vector3& v)
		{
			return sqrtf(Vector_DotProduct(v, v));
		}

		Vector3 Vector_Normalise(Vector3& v)
		{
			float l = Vector_Length(v);
			return { v.x / l, v.y / l, v.z / l };
		}

		Vector3 Vector_CrossProduct(Vector3& v1, Vector3& v2)
		{
			Vector3 v;
			v.x = v1.y * v2.z - v1.z * v2.y;
			v.y = v1.z * v2.x - v1.x * v2.z;
			v.z = v1.x * v2.y - v1.y * v2.x;
			return v;
		}

		Vector3 Vector_IntersectPlane(Vector3& plane_p, Vector3& plane_n, Vector3& lineStart, Vector3& lineEnd)
		{
			plane_n = Vector_Normalise(plane_n);
			float plane_d = -Vector_DotProduct(plane_n, plane_p);
			float ad = Vector_DotProduct(lineStart, plane_n);
			float bd = Vector_DotProduct(lineEnd, plane_n);
			float t = (-plane_d - ad) / (bd - ad);
			Vector3 lineStartToEnd = Vector_Sub(lineEnd, lineStart);
			Vector3 lineToIntersect = Vector_Mul(lineStartToEnd, t);
			return Vector_Add(lineStart, lineToIntersect);
		}

		int Triangle_ClipAgainstPlane(Vector3 plane_p, Vector3 plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2)
		{
			plane_n = Vector_Normalise(plane_n);

			auto dist = [&](Vector3& p)
			{
				Vector3 n = Vector_Normalise(p);
				return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
			};

			Vector3* inside_points[3];  int nInsidePointCount = 0;
			Vector3* outside_points[3]; int nOutsidePointCount = 0;

			float d0 = dist(in_tri.vect[0]);
			float d1 = dist(in_tri.vect[1]);
			float d2 = dist(in_tri.vect[2]);

			if (d0 >= 0)
				inside_points[nInsidePointCount++] = &in_tri.vect[0];
			else
				outside_points[nOutsidePointCount++] = &in_tri.vect[0];
			if (d1 >= 0)
				inside_points[nInsidePointCount++] = &in_tri.vect[1];
			else
				outside_points[nOutsidePointCount++] = &in_tri.vect[1];
			if (d2 >= 0)
				inside_points[nInsidePointCount++] = &in_tri.vect[2];
			else
				outside_points[nOutsidePointCount++] = &in_tri.vect[2];

			if (nInsidePointCount == 0)
			{
				return 0;
			}

			if (nInsidePointCount == 3)
			{
				out_tri1 = in_tri;

				return 1;
			}

			if (nInsidePointCount == 1 && nOutsidePointCount == 2)
			{
				out_tri1.col = in_tri.col;
				out_tri1.sym = in_tri.sym;

				out_tri1.vect[0] = *inside_points[0];

				out_tri1.vect[1] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
				out_tri1.vect[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

				return 1;
			}

			if (nInsidePointCount == 2 && nOutsidePointCount == 1)
			{
				out_tri1.col = in_tri.col;
				out_tri1.sym = in_tri.sym;

				out_tri2.col = in_tri.col;
				out_tri2.sym = in_tri.sym;

				out_tri1.vect[0] = *inside_points[0];
				out_tri1.vect[1] = *inside_points[1];
				out_tri1.vect[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

				out_tri2.vect[0] = *inside_points[1];
				out_tri2.vect[1] = out_tri1.vect[2];
				out_tri2.vect[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

				return 2;
			}
		}

		void returnFrameTime()
		{
			dt = clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}


		bool OnUserCreate()
		{
			// Load object file
			mesh.LoadFromObjectFile("teapot.obj");

			// Projection Matrix
			matProj = Matrix_MakeProjection(90.0f, screenY / screenX, 0.1f, 1000.0f);
			return true;
		}

		bool OnUserUpdate()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				vCamera.x -= 0.01f * dt;	// Travel Along X-Axis

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				vCamera.x += 0.01f * dt;	// Travel Along X-Axis


			Vector3 vForward = Vector_Mul(vCameraDirection, 0.01f * dt);

			// Standard FPS Control scheme, but turn instead of strafe
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				vCamera = Vector_Add(vCamera, vForward);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				vCamera = Vector_Sub(vCamera, vForward);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				Yaw -= 0.0025f * dt;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				Yaw += 0.0025f * dt;

			Matrix4x4 matRotZ, matRotX;
			//Theta += 1.0f * dt; // Uncomment to spin me right round baby right round
			matRotZ = Matrix_MakeRotationZ(Theta * 0.5f);
			matRotX = Matrix_MakeRotationX(Theta);

			Matrix4x4 matTrans;
			matTrans = Matrix_MakeTranslation(0.0f, 0.0f, 5.0f);

			Matrix4x4 matWorld;
			matWorld = Matrix_MakeIdentity();	// Form World Matrix
			matWorld = Matrix_MultiplyMatrix(matRotZ, matRotX); // Transform by rotation
			matWorld = Matrix_MultiplyMatrix(matWorld, matTrans); // Transform by translation

			// Create "Point At" Matrix for camera
			Vector3 vUp = { 0,1,0 };
			Vector3 vTarget = { 0,0,1 };
			Matrix4x4 matCameraRot = Matrix_MakeRotationY(Yaw);
			vCameraDirection = Matrix_MultiplyVector(matCameraRot, vTarget);
			vTarget = Vector_Add(vCamera, vCameraDirection);
			Matrix4x4 matCamera = Matrix_PointAt(vCamera, vTarget, vUp);

			// Make view matrix from camera
			Matrix4x4 matView = Matrix_QuickInverse(matCamera);

			// Store triagles for rastering later
			std::vector<Triangle> vecTrianglesToRaster;

			// Draw Triangles
			for (auto tri : mesh.mesh)
			{
				Triangle triProjected, triTransformed, triViewed;

				// World Matrix Transform
				triTransformed.vect[0] = Matrix_MultiplyVector(matWorld, tri.vect[0]);
				triTransformed.vect[1] = Matrix_MultiplyVector(matWorld, tri.vect[1]);
				triTransformed.vect[2] = Matrix_MultiplyVector(matWorld, tri.vect[2]);

				// Calculate triangle Normal
				Vector3 normal, line1, line2;

				// Get lines either side of triangle
				line1 = Vector_Sub(triTransformed.vect[1], triTransformed.vect[0]);
				line2 = Vector_Sub(triTransformed.vect[2], triTransformed.vect[0]);

				// Take cross product of lines to get normal to triangle surface
				normal = Vector_CrossProduct(line1, line2);

				// You normally need to normalise a normal!
				normal = Vector_Normalise(normal);

				// Get Ray from triangle to camera
				Vector3 vCameraRay = Vector_Sub(triTransformed.vect[0], vCamera);

				// If ray is aligned with normal, then triangle is visible
				if (Vector_DotProduct(normal, vCameraRay) < 0.0f)
				{
					// Illumination
					Vector3 light_direction = { 0.0f, 1.0f, -1.0f };
					light_direction = Vector_Normalise(light_direction);

					// How "aligned" are light direction and triangle surface normal?
					float dp = std::max(0.1f, Vector_DotProduct(light_direction, normal));

					// Choose console colours as required (much easier with RGB)
					//triTransformed.col = c.Attributes;
					//triTransformed.sym = c.Char.UnicodeChar;

					// Convert World Space --> View Space
					triViewed.vect[0] = Matrix_MultiplyVector(matView, triTransformed.vect[0]);
					triViewed.vect[1] = Matrix_MultiplyVector(matView, triTransformed.vect[1]);
					triViewed.vect[2] = Matrix_MultiplyVector(matView, triTransformed.vect[2]);
					triViewed.sym = triTransformed.sym;
					triViewed.col = triTransformed.col;

					// Clip Viewed Triangle against near plane, this could form two additional
					// additional triangles. 
					int nClippedTriangles = 0;
					Triangle clipped[2];
					nClippedTriangles = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, triViewed, clipped[0], clipped[1]);

					// We may end up with multiple triangles form the clip, so project as
					// required
					for (int n = 0; n < nClippedTriangles; n++)
					{
						// Project triangles from 3D --> 2D
						triProjected.vect[0] = Matrix_MultiplyVector(matProj, clipped[n].vect[0]);
						triProjected.vect[1] = Matrix_MultiplyVector(matProj, clipped[n].vect[1]);
						triProjected.vect[2] = Matrix_MultiplyVector(matProj, clipped[n].vect[2]);
						triProjected.col = clipped[n].col;
						triProjected.sym = clipped[n].sym;

						// Scale into view, we moved the normalising into cartesian space
						// out of the matrix.vector function from the previous videos, so
						// do this manually
						triProjected.vect[0] = Vector_Div(triProjected.vect[0], triProjected.vect[0].w);
						triProjected.vect[1] = Vector_Div(triProjected.vect[1], triProjected.vect[1].w);
						triProjected.vect[2] = Vector_Div(triProjected.vect[2], triProjected.vect[2].w);

						// X/Y are inverted so put them back
						triProjected.vect[0].x *= -1.0f;
						triProjected.vect[1].x *= -1.0f;
						triProjected.vect[2].x *= -1.0f;
						triProjected.vect[0].y *= -1.0f;
						triProjected.vect[1].y *= -1.0f;
						triProjected.vect[2].y *= -1.0f;

						// Offset verts into visible normalised space
						Vector3 vOffsetView = { 1,1,0 };
						triProjected.vect[0] = Vector_Add(triProjected.vect[0], vOffsetView);
						triProjected.vect[1] = Vector_Add(triProjected.vect[1], vOffsetView);
						triProjected.vect[2] = Vector_Add(triProjected.vect[2], vOffsetView);
						triProjected.vect[0].x *= 0.5f * screenY;
						triProjected.vect[0].y *= 0.5f * screenY;
						triProjected.vect[1].x *= 0.5f * screenX;
						triProjected.vect[1].y *= 0.5f * screenY;
						triProjected.vect[2].x *= 0.5f * screenX;
						triProjected.vect[2].y *= 0.5f * screenY;

						// Store triangle for sorting
						vecTrianglesToRaster.push_back(triProjected);
					}
				}
			}

			// Sort triangles from back to front
			std::sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](Triangle& t1, Triangle& t2)
			{
				float z1 = (t1.vect[0].z + t1.vect[1].z + t1.vect[2].z) / 3.0f;
				float z2 = (t2.vect[0].z + t2.vect[1].z + t2.vect[2].z) / 3.0f;
				return z1 > z2;
			});

			// Clear Screen
			app.clear();

			// Loop through all transformed, viewed, projected, and sorted triangles
			for (auto& triToRaster : vecTrianglesToRaster)
			{
				// Clip triangles against all four screen edges, this could yield
				// a bunch of triangles, so create a queue that we traverse to 
				// ensure we only test new triangles generated against planes
				Triangle clipped[2];
				std::list<Triangle> listTriangles;

				// Add initial triangle
				listTriangles.push_back(triToRaster);
				int nNewTriangles = 1;

				for (int p = 0; p < 4; p++)
				{
					int nTrisToAdd = 0;
					while (nNewTriangles > 0)
					{
						// Take triangle from front of queue
						Triangle test = listTriangles.front();
						listTriangles.pop_front();
						nNewTriangles--;

						switch (p)
						{
						case 0:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 1:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, screenY - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 2:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 3:	nTrisToAdd = Triangle_ClipAgainstPlane({ screenX - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						}

						// clipping against next planes
						for (int w = 0; w < nTrisToAdd; w++)
							listTriangles.push_back(clipped[w]);
					}
					nNewTriangles = listTriangles.size();
				}


				// Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
				for (auto& t : listTriangles)
				{
					FillTriangle(t.vect[0].x, t.vect[0].y, t.vect[1].x, t.vect[1].y, t.vect[2].x, t.vect[2].y, t.sym, sf::Color::Blue, &app);
					//DrawTriangle(t.vect[0].x, t.vect[0].y, t.vect[1].x, t.vect[1].y, t.vect[2].x, t.vect[2].y, 3, sf::Color::White, &app);
				}
			}

			return true;
		}


		void playGame()
		{
			while (app.isOpen())
			{
				sf::Event event;
				while (app.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						app.close();
				}

				OnUserUpdate();

				app.display();

			}
		}


	private:
		float screenX, screenY;
		sf::RenderWindow app;

		Mesh mesh;
		Matrix4x4 matProj;
		Vector3 vCamera;
		Vector3 vCameraDirection;

		float Yaw;
		float Theta;

		bool end;

		sf::Clock clock;
		float dt;
	};
};

