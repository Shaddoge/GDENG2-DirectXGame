#include "Matrix.h"

void Matrix::SetIdentity()
{
	::memset(mat, 0, sizeof(float) * 16);
	for (int i = 0; i < 4; i++)
	{
		mat[i][i] = 1;
	}
}

void Matrix::SetTranslate(Vector3 vector)
{
	SetIdentity();
	mat[3][0] = vector.x;
	mat[3][1] = vector.y;
	mat[3][2] = vector.z;
}
	
void Matrix::SetScale(Vector3 vector)
{
	SetIdentity();
	mat[0][0] = vector.x;
	mat[1][1] = vector.y;
	mat[2][2] = vector.z;
}

void Matrix::SetOrthoLH	(float width, float height, float near_plane, float far_plane)
{
	SetIdentity();
	mat[0][0] = 2.0f / width;
	mat[1][1] = 2.0f / height;
	mat[2][2] = 1.0f / (far_plane - near_plane);
	mat[3][2] = -(near_plane / (far_plane - near_plane));
}

void Matrix::operator*=(const Matrix& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] =
				mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
				mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
		}
	}
}
