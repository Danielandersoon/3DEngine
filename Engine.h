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
		Engine(unsigned int x, unsigned int y, std::string title);

		Vector3 Matrix_MultiplyVector(Matrix4x4& m, Vector3& i);
		
		Matrix4x4 Matrix_MakeIdentity();

		Matrix4x4 Matrix_MakeRotationX(float fAngleRad);

		Matrix4x4 Matrix_MakeRotationY(float fAngleRad);

		Matrix4x4 Matrix_MakeRotationZ(float fAngleRad);

		Matrix4x4 Matrix_MakeTranslation(float x, float y, float z);

		Matrix4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);

		Matrix4x4 Matrix_MultiplyMatrix(Matrix4x4& m1, Matrix4x4& m2);

		Matrix4x4 Matrix_PointAt(Vector3& pos, Vector3& target, Vector3& up);

		Matrix4x4 Matrix_QuickInverse(Matrix4x4& m); // Only for Rotation/Translation Matrices

		Vector3 Vector_Add(Vector3& v1, Vector3& v2);

		Vector3 Vector_Sub(Vector3& v1, Vector3& v2);

		Vector3 Vector_Mul(Vector3& v1, float k);

		Vector3 Vector_Div(Vector3& v1, float k);

		float Vector_DotProduct(Vector3& v1, Vector3& v2);

		float Vector_Length(Vector3& v);

		Vector3 Vector_Normalise(Vector3& v);

		Vector3 Vector_CrossProduct(Vector3& v1, Vector3& v2);

		Vector3 Vector_IntersectPlane(Vector3& plane_p, Vector3& plane_n, Vector3& lineStart, Vector3& lineEnd);

		int Triangle_ClipAgainstPlane(Vector3 plane_p, Vector3 plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2);

		void returnFrameTime();


		bool OnUserCreate();

		bool OnUserUpdate(sf::Event event);


		void playeGame();

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

