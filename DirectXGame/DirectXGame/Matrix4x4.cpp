#include "Matrix4x4.h"

void Matrix4x4::SetIdentity()
{
	::memset(mat, 0, sizeof(float) * 16);
	for (int i = 0; i < 4; i++)
	{
		mat[i][i] = 1;
	}
}

void Matrix4x4::SetMatrix(const Matrix4x4 matrix)
{
	::memcpy(this->mat, matrix.mat, sizeof(float) * 16);
}

void Matrix4x4::SetMatrix(float matrix[4][4])
{
	::memcpy(this->mat, matrix, sizeof(float) * 16);
}

void Matrix4x4::SetTranslate(Vector3D vector)
{
	mat[3][0] = vector.x;
	mat[3][1] = vector.y;
	mat[3][2] = vector.z;
}
	
void Matrix4x4::SetScale(Vector3D vector)
{
	mat[0][0] = vector.x;
	mat[1][1] = vector.y;
	mat[2][2] = vector.z;
}

void Matrix4x4::SetRotationX(float x)
{
	mat[1][1] = cos(x);
	mat[1][2] = sin(x);
	mat[2][1] = -sin(x);
	mat[2][2] = cos(x);
}

void Matrix4x4::SetRotationY(float y)
{
	mat[0][0] = cos(y);
	mat[0][2] = -sin(y);
	mat[2][0] = sin(y);
	mat[2][2] = cos(y);
}

void Matrix4x4::SetRotationZ(float z)
{
	mat[0][0] = cos(z);
	mat[0][1] = sin(z);
	mat[1][0] = -sin(z);
	mat[1][1] = cos(z);
}

Vector3D Matrix4x4::GetZDirection()
{
	return Vector3D(mat[2][0], mat[2][1], mat[2][2]);
}

Vector3D Matrix4x4::GetYDirection()
{
	return Vector3D(mat[1][0], mat[1][1], mat[1][2]);
}

Vector3D Matrix4x4::GetXDirection()
{
	return Vector3D(mat[0][0], mat[0][1], mat[0][2]);
}

Vector3D Matrix4x4::GetTranslation()
{
	return Vector3D(mat[3][0], mat[3][1], mat[3][2]);
}

void Matrix4x4::SetPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	mat[0][0] = xscale;
	mat[1][1] = yscale;
	mat[2][2] = zfar / (zfar - znear);
	mat[2][3] = 1.0f;
	mat[3][2] = (-znear*zfar) / (zfar - znear);
}

void Matrix4x4::SetOrthoLH	(float width, float height, float near_plane, float far_plane)
{
	SetIdentity();
	mat[0][0] = 2.0f / width;
	mat[1][1] = 2.0f / height;
	mat[2][2] = 1.0f / (far_plane - near_plane);
	mat[3][2] = -(near_plane / (far_plane - near_plane));
}

void Matrix4x4::Inverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4 v, vec[3];
	float det = 0.0f;

	det = this->GetDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->mat[j][0]);
				vec[a].y = (this->mat[j][1]);
				vec[a].z = (this->mat[j][2]);
				vec[a].w = (this->mat[j][3]);
			}
		}
		v.Cross(vec[0], vec[1], vec[2]);

		out.mat[0][i] = pow(-1.0f, i) * v.x / det;
		out.mat[1][i] = pow(-1.0f, i) * v.y / det;
		out.mat[2][i] = pow(-1.0f, i) * v.z / det;
		out.mat[3][i] = pow(-1.0f, i) * v.w / det;
	}

	this->SetMatrix(out);
}

float Matrix4x4::GetDeterminant()
{
	Vector4 minor, v1, v2, v3;
	float det;

	v1 = Vector4(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
	v2 = Vector4(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
	v3 = Vector4(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


	minor.Cross(v1, v2, v3);
	det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
		this->mat[3][3] * minor.w);
	return det;
}

Matrix4x4 Matrix4x4::MultiplyTo(Matrix4x4 matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.mat[i][j] =
				this->mat[i][0] * matrix.mat[0][j] + this->mat[i][1] * matrix.mat[1][j] +
				this->mat[i][2] * matrix.mat[2][j] + this->mat[i][3] * matrix.mat[3][j];
		}
	}

	return out;
}

float* Matrix4x4::GetMatrix()
{
	return *this->mat;
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.mat[i][j] =
				mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
				mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
		}
	}
	SetMatrix(out);
}
