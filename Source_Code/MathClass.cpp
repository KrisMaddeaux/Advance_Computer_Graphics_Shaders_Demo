#include "MathClass.h"

Vec3f::Vec3f()
{
	x = v[0] = 0.0f;
	y = v[1] = 0.0f;
	z = v[2] = 0.0f;
}

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = v[0] = x;
	this->y = v[1] = y;
	this->z = v[2] = z;
}

Vec3f Vec3f::negate() //mathclass.cpp
{
	return Vec3f(-x, -y, -z);
}

Vec3f Vec3f::operator+ (const Vec3f &other)
{
	return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f Vec3f::operator- (const Vec3f &other)
{
	return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::operator* (const Vec3f &other)
{
	return Vec3f(x * other.x, y * other.y, z * other.z);
}

Vec3f Vec3f::operator* (float scale)
{
	return Vec3f(x * scale, y * scale, z * scale);
}

Vec3f Vec3f::operator+= (const Vec3f &other)
{
	return Vec3f(x += other.x, y += other.y, z += other.z); 
}

Vec3f Vec3f::operator*= (const Vec3f &other)
{
	return Vec3f(x *= other.x, y *= other.y, z *= other.z);
}

Vec3f Vec3f::operator*= (float scale)
{
	return Vec3f(x *= scale, y *= scale, z *= scale);
}

bool Vec3f::operator== (const Vec3f &other)
{
	if(x == other.x && y == other.y && z == other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vec3f::operator!= (const Vec3f &other)
{
	if(x == other.x && y == other.y && z == other.z)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Vec3f::operator<= (const Vec3f &other)
{
	if(x <= other.x && y <= other.y && z <= other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vec3f::magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

Vec3f Vec3f::normalize()
{
	float mag = sqrtf((x * x) + (y * y) + (z * z));
	return Vec3f(x * (1.0f/mag), y * (1.0f/mag), z * (1.0f/mag));
}

Vec3f Vec3f::square()
{
	return Vec3f((x * x), (y * y), (z * z));
}

float Vec3f::dot(const Vec3f &other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

Vec3f Vec3f::cross(const Vec3f &other)
{
	return Vec3f((y * other.z) - (other.y * z), (z * other.x) - (other.z * x), (x * other.y) - (other.x * y));
}

Vec3f Vec3f::dirVec(const Vec3f &other)
{
	Vec3f combined = Vec3f(x - other.x, y - other.y, z - other.z);
	return combined.normalize();
}

ostream& operator<<(ostream& os, const Vec3f &v)
{
	cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vec4f::Vec4f()
{
	x = v[0] = 0.0f;
	y = v[1] = 0.0f;
	z = v[2] = 0.0f;
	a = v[3] = 1.0f;
}

Vec4f::Vec4f(float x, float y, float z, float a)
{
	this->x = v[0] = x;
	this->y = v[1] = y;
	this->z = v[2] = z;
	this->a = v[3] = a;
}

Vec4f::Vec4f(Vec3f vec, float a)
{
	this->x = v[0] = vec.x;
	this->y = v[1] = vec.y;
	this->z = v[2] = vec.z;
	this->a = v[3] = a;
}

Vec4f Vec4f::negate() //mathclass.cpp
{
	return Vec4f(-x, -y, -z, -a);
}

Vec4f Vec4f::operator+ (const Vec4f &other)
{
	return Vec4f(x + other.x, y + other.y, z + other.z, a + other.a);
}

Vec4f Vec4f::operator- (const Vec4f &other)
{
	return Vec4f(x - other.x, y - other.y, z - other.z, a - other.a);
}

Vec4f Vec4f::operator* (const Vec4f &other)
{
	return Vec4f(x * other.x, y * other.y, z * other.z, a * other.a);
}

Vec4f Vec4f::operator* (float scale)
{
	return Vec4f(x * scale, y * scale, z * scale, a * scale);
}

Vec4f Vec4f::operator+= (const Vec4f &other)
{
	return Vec4f(x += other.x, y += other.y, z += other.z, a += other.a); 
}

Vec4f Vec4f::operator*= (const Vec4f &other)
{
	return Vec4f(x *= other.x, y *= other.y, z *= other.z, a *= other.a);
}

Vec4f Vec4f::operator*= (float scale)
{
	return Vec4f(x *= scale, y *= scale, z *= scale, a *= scale);
}

bool Vec4f::operator== (const Vec4f &other)
{
	if(x == other.x && y == other.y && z == other.z && a == other.a)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vec4f::operator!= (const Vec4f &other)
{
	if(x == other.x && y == other.y && z == other.z && a == other.a)
	{
		return false;
	}
	else
	{
		return true;
	}
}

float Vec4f::magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z) + (a * a));
}

Vec4f Vec4f::normalize()
{
	float mag = sqrtf((x * x) + (y * y) + (z * z) + (a * a));
	return Vec4f(x * (1.0f/mag), y * (1.0f/mag), z * (1.0f/mag), a * (1.0f/mag));
}

Vec4f Vec4f::square()
{
	return Vec4f((x * x), (y * y), (z * z), (a * a));
}

float Vec4f::dot(const Vec4f &other)
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (a * other.a);
}

Vec4f Vec4f::cross(const Vec4f &other)
{
	return Vec4f((y * other.z) - (other.y * z), (z * other.x) - (other.z * x), (x * other.y) - (other.x * y), 1.0f);
}

Vec4f Vec4f::dirVec(const Vec4f &other)
{
	Vec4f combined = Vec4f(x - other.x, y - other.y, z - other.z, a - other.a);
	return combined.normalize();
}

Vec3f Vec4f::returnAsVec3f()
{
	return Vec3f(x, y, z);
}

ostream& operator<<(ostream& os, const Vec4f &v)
{
	cout << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.a << ")" << endl;
	return os;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//identity matrix
Mat3f::Mat3f()
{
	row1.x = 1.0f;
	row1.y = 0.0f;
	row1.z = 0.0f;
	row2.x = 0.0f;
	row2.y = 1.0f;
	row2.z = 0.0f;
	row3.x = 0.0f;
	row3.y = 0.0f;
	row3.z = 1.0f;

}

Mat3f::Mat3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	row1.x = m00;
	row1.y = m01;
	row1.z = m02;
	row2.x = m10;
	row2.y = m11;
	row2.z = m12;
	row3.x = m20;
	row3.y = m21;
	row3.z = m22;

	m[0] = m00;
	m[1] = m01;
	m[2] = m02;
	m[3] = m10;
	m[4] = m11;
	m[5] = m12;
	m[6] = m20;
	m[7] = m21;
	m[8] = m22;
}

Mat3f::Mat3f(Vec3f Vrow1, Vec3f Vrow2, Vec3f Vrow3)
{
	row1.x = Vrow1.x;
	row1.y = Vrow1.y;
	row1.z = Vrow1.z;
	row2.x = Vrow2.x;
	row2.y = Vrow2.y;
	row2.z = Vrow2.z;
	row3.x = Vrow3.x;
	row3.y = Vrow3.y;
	row3.z = Vrow3.z;
}

Mat3f Mat3f::operator+ (const Mat3f &other)
{
	return Mat3f(row1.x + other.row1.x, row1.y + other.row1.y, row1.z + other.row1.z, 
				 row2.x + other.row2.x, row2.y + other.row2.y, row2.z + other.row2.z, 
				 row3.x + other.row3.x, row3.y + other.row3.y, row3.z + other.row3.z);
}

Mat3f Mat3f::operator* (const Mat3f &other)
{
	return Mat3f((row1.x * other.row1.x) + (row1.y * other.row2.x) + (row1.z * other.row3.x), (row1.x * other.row1.y) + (row1.y * other.row2.y) + (row1.z * other.row3.y), (row1.x * other.row1.z) + (row1.y * other.row2.z) + (row1.z * other.row3.z),	//first row
				 (row2.x * other.row1.x) + (row2.y * other.row2.x) + (row2.z * other.row3.x), (row2.x * other.row1.y) + (row2.y * other.row2.y) + (row2.z * other.row3.y), (row2.x * other.row1.z) + (row2.y * other.row2.z) + (row2.z * other.row3.z),		//second row
				 (row3.x * other.row1.x) + (row3.y * other.row2.x) + (row3.z * other.row3.x), (row3.x * other.row1.y) + (row3.y * other.row2.y) + (row3.z * other.row3.y), (row3.x * other.row1.z) + (row3.y * other.row2.z) + (row3.z * other.row3.z));	//third row
}

Mat3f Mat3f::operator* (float scale)
{
	return Mat3f(row1 * scale, row2 * scale, row3 * scale);
}

Vec3f Mat3f::operator*(const Vec3f &other)
{
	return Vec3f ((row1.x * other.x) + (row1.y * other.y) + (row1.z * other.z),	//x-axis
				  (row2.x * other.x) + (row2.y * other.y) + (row2.z * other.z),  //y-axis
				  (row3.x * other.x) + (row3.y * other.y) + (row3.z * other.z));	//z-axis

}

Mat3f Mat3f::transpose()
{
	return Mat3f(row1.x, row2.x, row3.x,
				 row1.y, row2.y, row3.y,
				 row1.z, row2.z, row3.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4f::Mat4f()
{
	row1.x = 0.0f;
	row1.y = 0.0f;
	row1.z = 0.0f;
	row1.a = 0.0f;
	row2.x = 0.0f;
	row2.y = 0.0f;
	row2.z = 0.0f;
	row2.a = 0.0f;
	row3.x = 0.0f;
	row3.y = 0.0f;
	row3.z = 0.0f;
	row3.a = 0.0f;
	row4.x = 0.0f;
	row4.y = 0.0f;
	row4.z = 0.0f;
	row4.a = 0.0f;

	m[0] = 0.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
	m[4] = 0.0f; m[5] = 0.0f; m[6] = 0.0f; m[7] = 0.0f;
	m[8] = 0.0f; m[9] = 0.0f; m[10] = 0.0f; m[11] = 0.0f;
	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 0.0f;

	a[0][0] = 0.0f; a[0][1] = 0.0f; a[0][2] = 0.0f; a[0][3]= 0.0f;
	a[1][0] = 0.0f; a[1][1] = 0.0f; a[1][2] = 0.0f; a[1][3]= 0.0f;
	a[2][0] = 0.0f; a[2][1] = 0.0f; a[2][2] = 0.0f; a[2][3]= 0.0f;
	a[3][0] = 0.0f; a[3][1] = 0.0f; a[3][2] = 0.0f; a[3][3]= 0.0f;
}

Mat4f::Mat4f(float matrix[16])
{
	row1.x = matrix[0];  row1.y = matrix[1];  row1.z = matrix[2];  row1.a = matrix[3];
	row2.x = matrix[4];  row2.y = matrix[5];  row2.z = matrix[6];  row2.a = matrix[7];
	row3.x = matrix[8];  row3.y = matrix[9];  row3.z = matrix[10]; row3.a = matrix[11];
	row4.x = matrix[12]; row4.y = matrix[13]; row4.z = matrix[14]; row4.a = matrix[15];

	m[0] = matrix[0]; m[1] = matrix[1]; m[2] = matrix[2]; m[3] = matrix[3];
	m[4] = matrix[4]; m[5] = matrix[5]; m[6] = matrix[6]; m[7] = matrix[7];
	m[8] = matrix[8]; m[9] = matrix[9]; m[10] = matrix[10]; m[11] = matrix[11];
	m[12] = matrix[12]; m[13] = matrix[13]; m[14] = matrix[14]; m[15] = matrix[15];

	a[0][0] = matrix[0]; a[0][1] = matrix[1]; a[0][2] =  matrix[2]; a[0][3]= matrix[3];
	a[1][0] = matrix[4]; a[1][1] = matrix[5]; a[1][2] =  matrix[6]; a[1][3]= matrix[7];
	a[2][0] = matrix[8]; a[2][1] = matrix[9]; a[2][2] = matrix[10]; a[2][3]= matrix[11];
	a[3][0] = matrix[12]; a[3][1] = matrix[13]; a[3][2] = matrix[14]; a[3][3]= matrix[15];
}


Mat4f::Mat4f(float m00, float m01, float m02, float m03, 
			 float m10, float m11, float m12, float m13, 
			 float m20, float m21, float m22, float m23, 
			 float m30, float m31, float m32, float m33)
{
	row1.x = m00; row1.y = m01; row1.z = m02; row1.a = m03;
	row2.x = m10; row2.y = m11; row2.z = m12; row2.a = m13;
	row3.x = m20; row3.y = m21; row3.z = m22; row3.a = m23;
	row4.x = m30; row4.y = m31; row4.z = m32; row4.a = m33;

	m[0] = m00; m[1] = m01; m[2] = m02;m[3] = m03;
	m[4] = m10; m[5] = m11; m[6] = m12;m[7] = m13;
	m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
	m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;

	a[0][0] = m00; a[0][1] = m01; a[0][2] = m02; a[0][3]= m03;
	a[1][0] = m10; a[1][1] = m11; a[1][2] = m12; a[1][3]= m13;
	a[2][0] = m20; a[2][1] = m21; a[2][2] = m22; a[2][3]= m23;
	a[3][0] = m30; a[3][1] = m31; a[3][2] = m32; a[3][3]= m33;
}


Mat4f::Mat4f(Vec4f Vrow1, Vec4f Vrow2, Vec4f Vrow3, Vec4f Vrow4)
{
	row1.x = Vrow1.x;
	row1.y = Vrow1.y;
	row1.z = Vrow1.z;
	row1.a = Vrow1.a;

	row2.x = Vrow2.x;
	row2.y = Vrow2.y;
	row2.z = Vrow2.z;
	row2.a = Vrow2.a;

	row3.x = Vrow3.x;
	row3.y = Vrow3.y;
	row3.z = Vrow3.z;
	row3.a = Vrow3.a;

	row4.x = Vrow4.x;
	row4.y = Vrow4.y;
	row4.z = Vrow4.z;
	row4.a = Vrow4.a;

	m[0] = row1.x; m[1]  = row1.y; m[2]  = row1.z; m[3]  = row1.a;
	m[4] = row2.x; m[5]  = row2.y; m[6]  = row2.z; m[7]  = row2.a;
	m[8] = row3.x; m[9]  = row3.y; m[10] = row3.z; m[11] = row3.a;
	m[12]= row4.x; m[13] = row4.y; m[14] = row4.z; m[15] = row4.a;

	a[0][0] = row1.x; a[0][1] = row1.y; a[0][2] = row1.z; a[0][3]= row1.a;
	a[1][0] = row2.x; a[1][1] = row2.y; a[1][2] = row2.z; a[1][3]= row2.a;
	a[2][0] = row3.x; a[2][1] = row3.y; a[2][2] = row3.z; a[2][3]= row3.a;
	a[3][0] = row4.x; a[3][1] = row4.y; a[3][2] = row4.z; a[3][3]= row4.a;
}

Mat4f Mat4f::operator+ (const Mat4f &other)
{
	return Mat4f(row1.x + other.row1.x, row1.y + other.row1.y, row1.z + other.row1.z, row1.a + other.row1.a, 
				 row2.x + other.row2.x, row2.y + other.row2.y, row2.z + other.row2.z, row2.a + other.row2.a, 
				 row3.x + other.row3.x, row3.y + other.row3.y, row3.z + other.row3.z, row3.a + other.row3.a,
				 row4.x + other.row4.x, row4.y + other.row4.y, row4.z + other.row4.z, row4.a + other.row4.a);
}

Mat4f Mat4f::operator* (const Mat4f &other) const  
{
	Mat4f temp = Mat4f();
	for(int row = 0; row < 4; row++)
	{
		for(int col1 = 0; col1 < 4; col1++)
		{
			for(int col2 = 0; col2 < 4; col2++)
			{
				temp.a[row][col1] += a[row][col2] * other.a[col2][col1]; 
			}
		}
	}

	return Mat4f(temp.a[0][0], temp.a[0][1], temp.a[0][2], temp.a[0][3],
				 temp.a[1][0], temp.a[1][1], temp.a[1][2], temp.a[1][3],
				 temp.a[2][0], temp.a[2][1], temp.a[2][2], temp.a[2][3],
				 temp.a[3][0], temp.a[3][1], temp.a[3][2], temp.a[3][3]); 

}

Mat4f Mat4f::operator* (const Mat4f &other)
{
	Mat4f temp = Mat4f();
	for(int row = 0; row < 4; row++)
	{
		for(int col1 = 0; col1 < 4; col1++)
		{
			for(int col2 = 0; col2 < 4; col2++)
			{
				temp.a[row][col1] += a[row][col2] * other.a[col2][col1]; 
			}
		}
	}

	return Mat4f(temp.a[0][0], temp.a[0][1], temp.a[0][2], temp.a[0][3],
				 temp.a[1][0], temp.a[1][1], temp.a[1][2], temp.a[1][3],
				 temp.a[2][0], temp.a[2][1], temp.a[2][2], temp.a[2][3],
				 temp.a[3][0], temp.a[3][1], temp.a[3][2], temp.a[3][3]); 
}

Mat4f Mat4f::operator* (const float scale)
{
	return Mat4f(row1 * scale, row2 * scale, row3 * scale, row4 * scale);
}

Vec4f Mat4f::operator*(const Vec4f &other)
{
	return Vec4f ((row1.x * other.x) + (row1.y * other.y) + (row1.z * other.z) + (row1.a * other.a),	//x-axis
				  (row2.x * other.x) + (row2.y * other.y) + (row2.z * other.z) + (row2.a * other.a), //y-axis
				  (row3.x * other.x) + (row3.y * other.y) + (row3.z * other.z) + (row3.a * other.a),	//z-axis
				  (row4.x * other.x) + (row4.y * other.y) + (row4.z * other.z) + (row4.a * other.a));	//w-axis

}

Mat4f Mat4f::transpose()
{
	return Mat4f(row1.x, row2.x, row3.x, row4.x,
				 row1.y, row2.y, row3.y, row4.y,
				 row1.z, row2.z, row3.z, row4.z,
				 row1.a, row2.a, row3.a, row4.a); 
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Quaternions

Quat::Quat()
{
	w = 0.0f;
	XYZ = Vec3f(0.0f, 0.0f, 0.0f);
}

Quat::Quat(float _w, Vec3f &other)
{
	w = _w;
	XYZ = other;
}

Quat::Quat(float _w, float x, float y, float z)
{
	w = _w;
	XYZ = Vec3f(x, y, z);
}

/*Quat rotationQuat(float degrees, Vec3f &axis)
{
	float radians = degrees * (3.141592654 / 180.0f);
	return Quat(cosf(radians / 2), axis.normalize() * (sinf(radians / 2)));
}
*/
Quat Quat::conjugate()
{
	return Quat(w, XYZ * -1);
}

Quat Quat::operator*(Quat &other)
{
	return Quat((w * other.w) - XYZ.dot(other.XYZ), (other.XYZ * w) + (XYZ * other.w) + (XYZ.cross(other.XYZ)));
}

Quat Quat::operator*(float scale)
{
	return Quat(w * scale, XYZ.x * scale, XYZ.y * scale, XYZ.z * scale);
}

Quat Quat::operator+(Quat &other)
{
	return Quat(w + other.w, XYZ.x + other.XYZ.x, XYZ.y + other.XYZ.y, XYZ.z + other.XYZ.z);
}

Vec3f Quat::toVector()
{
	return Vec3f(XYZ);
}

float Quat::dot(Quat &other)
{
	return (w * other.w) + (XYZ.x * other.XYZ.x) + (XYZ.y * other.XYZ.y) + (XYZ.z * other.XYZ.z);
}

Quat Quat::normalize()
{
	float mag = sqrtf((w * w) + (XYZ.x * XYZ.x) + (XYZ.y * XYZ.y) + (XYZ.z * XYZ.z));
	return Quat(w * (1.0f/mag), XYZ.x * (1.0f/mag), XYZ.y * (1.0f/mag), XYZ.z * (1.0f/mag));

}

ostream &operator<<(ostream &os, const Quat &q)
{
	cout << "< " << q.w << ", " << q.XYZ.x << ", " << q.XYZ.y << ", " << q.XYZ.z << ">" << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

physics::physics()
{
}

physics::~physics()
{
}

//hooke's law
Vec3f physics::spring(float k, float length, Vec3f direction)
{
	return  direction * ((-1 * k) * (direction.magnitude()) - (length));
}

Vec3f physics::acceleration(Vec3f force, float mass)
{
	return force * (1.0f/mass);
}

