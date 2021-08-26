//Author : Meir Elkabets

#pragma once
#include <math.h>

#define PI (3.141592653589793)
template<typename T>
constexpr auto DEG2RAD(T deg) { return (deg*PI*0.00555555555555555555555555555556); }

//It is recommended to use double or float as the type of the class(T)
template <class T> class C3DVector
{
	typedef struct ST_D3Vector
	{
		T vx;
		T vy;
		T vz;
	}ST_D3Vector;

public:
	C3DVector(const T& vx, const T& vy, const T& vz)
	{
		m_stVector = { vx, vy, vz };
	}

	C3DVector()
	{
		m_stVector = { 0, 0, 0 };
	}

	T SelfDotProduct()
	{
		T rv = m_stVector.vx*m_stVector.vx + m_stVector.vy*m_stVector.vy + m_stVector.vz*m_stVector.vz;
		return rv;
	}

	T GetSize()
	{
		T rv = SelfDotProduct();
		return sqrt(rv);
	}

	T DotProduct(const C3DVector& other)
	{
		T rv = m_stVector.vx*other.m_stVector.vx + m_stVector.vy*other.m_stVector.vy + m_stVector.vz*other.m_stVector.vz;
		return rv;
	}

	// return by value (copy)
	C3DVector operator-(const C3DVector& other)
	{
		C3DVector<T> rv(this->m_stVector.vx - other.m_stVector.vx,
			            this->m_stVector.vy - other.m_stVector.vy,
			            this->m_stVector.vz - other.m_stVector.vz);

		return rv;
	}

	// return by value (copy)
	C3DVector operator+(const C3DVector& other)
	{
		C3DVector<T> rv(this->m_stVector.vx + other.m_stVector.vx,
			            this->m_stVector.vy + other.m_stVector.vy,
			            this->m_stVector.vz + other.m_stVector.vz);

		return rv;
	}

	// return by value (copy) same as CrossProduct.
	C3DVector operator*(const C3DVector& other)
	{
		C3DVector<T> rv = CrossProduct(other);

		return rv;
	}

	T operator[] (int index)
	{
		T v[] = { m_stVector.vx , m_stVector.vy, m_stVector.vz };

		if (index >= 0 && index < 3)
		{
			return v[index];
		}

		return NAN;
	}


	inline const T& vx() const { return m_stVector.vx; }
	inline const T& vy() const { return m_stVector.vy; }
	inline const T& vz() const { return m_stVector.vz; }

	T Distance(const C3DVector& other)
	{
		C3DVector<T> rv(this->m_stVector.vx - other.m_stVector.vx,
			            this->m_stVector.vy - other.m_stVector.vy,
			            this->m_stVector.vz - other.m_stVector.vz);

		return rv.GetSize();
	}

	// return by value (copy)
	C3DVector CrossProduct(const C3DVector& other)
	{
		T vx =  (this->m_stVector.vy*other.m_stVector.vz - this->m_stVector.vz*other.m_stVector.vy);
		T vy = -(this->m_stVector.vx*other.m_stVector.vz - this->m_stVector.vz*other.m_stVector.vx);
		T vz =  (this->m_stVector.vx*other.m_stVector.vy - this->m_stVector.vy*other.m_stVector.vx);

		C3DVector<T> rv(vx, vy, vz);

		return rv;
	}

	// return by value (copy) input in radians (roll, pitch, yaw  rotation)
	C3DVector RPYRotation(const T& roll, const T& pitch, const T& yaw)
	{
		//construct the matrix rotation rows vectors
		T cosYaw   = cos(yaw);
		T sinYaw   = sin(yaw);
		T cosPitch = cos(pitch);
		T sinPitch = sin(pitch);
		T sinRoll  = sin(roll);
		T cosRoll  = cos(roll);

		C3DVector<T> matrixRow0(cosYaw*cosPitch,
			                    cosYaw*sinPitch*sinRoll - sinYaw *cosRoll,
			                    cosYaw*sinPitch*cosRoll + sinYaw *sinRoll);

		C3DVector<T> matrixRow1(sinYaw*cosPitch,
			                    sinYaw*sinPitch*sinRoll + cosYaw*cosRoll,
			                    sinYaw*sinPitch*cosRoll - cosYaw*sinRoll);

		C3DVector<T> matrixRow2(-sinPitch, cosPitch*sinRoll, cosPitch*cosRoll);

		//[3x3] matrix X current vector = [1x3] vector (rotated)
		C3DVector<T> rv(matrixRow0.m_stVector.vx*m_stVector.vx + matrixRow0.m_stVector.vy*m_stVector.vy + matrixRow0.m_stVector.vz*m_stVector.vz,
			            matrixRow1.m_stVector.vx*m_stVector.vx + matrixRow1.m_stVector.vy*m_stVector.vy + matrixRow1.m_stVector.vz*m_stVector.vz,
			            matrixRow2.m_stVector.vx*m_stVector.vx + matrixRow2.m_stVector.vy*m_stVector.vy + matrixRow2.m_stVector.vz*m_stVector.vz);

		return rv;
	}
	
private:

	ST_D3Vector m_stVector;
};

//It is recommended to use double or float as the type of the class(T)
template <class T> class C3X3Matrix
{
	typedef struct ST_D3X3Matrix
	{
		C3DVector<T> row0;
		C3DVector<T> row1;
		C3DVector<T> row2;
	}ST_D3X3Matrix;

public:
	C3X3Matrix(const C3DVector<T>& row0, const C3DVector<T>& row1, const C3DVector<T>& row2)
	{
		m_stMatrix.row0 = row0;
		m_stMatrix.row1 = row1;
		m_stMatrix.row2 = row2;		
	}

	C3X3Matrix()
	{
		m_stMatrix.row0 = C3DVector<T>(0,0,0);
		m_stMatrix.row1 = C3DVector<T>(0,0,0);
		m_stMatrix.row2 = C3DVector<T>(0,0,0);
	}

	T At (int row, int col)
	{
		C3DVector<T> mat[] = { m_stMatrix.row0, m_stMatrix.row1, m_stMatrix.row2 };

		if ( (row >= 0 && row < 3) && (col >= 0 && col < 3))
		{
			return mat[row][col];
		}

		return NAN;
	}

	// return by value (copy). 
	C3X3Matrix operator+(const C3X3Matrix& other)
	{
		C3DVector<T> row0(At(0,0) + other.At(0,0), At(0,1) + other.At(0,1), At(0,2) + other.At(0,2));
		C3DVector<T> row1(At(1,0) + other.At(1,0), At(1,1) + other.At(1,1), At(1,2) + other.At(1,2));
		C3DVector<T> row2(At(2,0) + other.At(2,0), At(2,1) + other.At(2,1), At(2,2) + other.At(2,2));

		C3X3Matrix rv(row0, row1, row2);

		return rv;
	}

	// return by value (copy). 
	C3X3Matrix operator-(const C3X3Matrix& other)
	{
		C3DVector<T> row0(At(0,0) - other.At(0,0), At(0,1) - other.At(0,1), At(0,2) - other.At(0,2));
		C3DVector<T> row1(At(1,0) - other.At(1,0), At(1,1) - other.At(1,1), At(1,2) - other.At(1,2));
		C3DVector<T> row2(At(2,0) - other.At(2,0), At(2,1) - other.At(2,1), At(2,2) - other.At(2,2));

		C3X3Matrix rv(row0, row1, row2);
		return rv;
	}

	// return by value (copy). 
	C3DVector<T> operator*(const C3DVector<T>& otherVector)
	{
		C3DVector rv(At(0,0)*otherVector.vx() + At(0,1)*otherVector.vy(), At(0,2)*otherVector.vz(),
			         At(1,0)*otherVector.vx() + At(1,1)*otherVector.vy(), At(1,2)*otherVector.vz(),
			         At(2,0)*otherVector.vx() + At(2,1)*otherVector.vy(), At(2,2)*otherVector.vz());
		return rv;
	}

	// return by value (copy). 
	C3X3Matrix operator*(const C3X3Matrix& other)
	{	

		C3DVector<T> row0(m_stMatrix.row0.vx()*other.m_stMatrix.row0.vx() + m_stMatrix.row0.vy()*other.m_stMatrix.row1.vx() + m_stMatrix.row0.vz()*other.m_stMatrix.row2.vx(),
			              m_stMatrix.row0.vx()*other.m_stMatrix.row0.vy() + m_stMatrix.row0.vy()*other.m_stMatrix.row1.vy() + m_stMatrix.row0.vz()*other.m_stMatrix.row2.vy(),
			              m_stMatrix.row0.vx()*other.m_stMatrix.row0.vz() + m_stMatrix.row0.vy()*other.m_stMatrix.row1.vz() + m_stMatrix.row0.vz()*other.m_stMatrix.row2.vz());
		
		C3DVector<T> row1(m_stMatrix.row1.vx()*other.m_stMatrix.row0.vx() + m_stMatrix.row1.vy()*other.m_stMatrix.row1.vx() + m_stMatrix.row1.vz()*other.m_stMatrix.row2.vx(),
			              m_stMatrix.row1.vx()*other.m_stMatrix.row0.vy() + m_stMatrix.row1.vy()*other.m_stMatrix.row1.vy() + m_stMatrix.row1.vz()*other.m_stMatrix.row2.vy(),
			              m_stMatrix.row1.vx()*other.m_stMatrix.row0.vz() + m_stMatrix.row1.vy()*other.m_stMatrix.row1.vz() + m_stMatrix.row1.vz()*other.m_stMatrix.row2.vz());

		C3DVector<T> row2(m_stMatrix.row2.vx()*other.m_stMatrix.row0.vx() + m_stMatrix.row2.vy()*other.m_stMatrix.row1.vx() + m_stMatrix.row2.vz()*other.m_stMatrix.row2.vx(),
			              m_stMatrix.row2.vx()*other.m_stMatrix.row0.vy() + m_stMatrix.row2.vy()*other.m_stMatrix.row1.vy() + m_stMatrix.row2.vz()*other.m_stMatrix.row2.vy(),
			              m_stMatrix.row2.vx()*other.m_stMatrix.row0.vz() + m_stMatrix.row2.vy()*other.m_stMatrix.row1.vz() + m_stMatrix.row2.vz()*other.m_stMatrix.row2.vz());

		C3X3Matrix<T> rv(row0, row1, row2);

		return rv;
	}

	T Det()
	{
		T rv = 0;

		rv =  m_stMatrix.row0.vx()*(m_stMatrix.row1.vy()*m_stMatrix.row2.vz() - m_stMatrix.row1.vz()*m_stMatrix.row2.vy()) -
			  m_stMatrix.row0.vy()*(m_stMatrix.row1.vx()*m_stMatrix.row2.vz() - m_stMatrix.row2.vx()*m_stMatrix.row1.vz()) +
			  m_stMatrix.row0.vz()*(m_stMatrix.row1.vx()*m_stMatrix.row2.vy() - m_stMatrix.row2.vx()*m_stMatrix.row1.vy());

		return rv;
	}

	// return by value (copy). 
	C3X3Matrix Transpose()
	{
		C3DVector<T> row0(m_stMatrix.row0.vx(), m_stMatrix.row1.vx(), m_stMatrix.row2.vx());
		C3DVector<T> row1(m_stMatrix.row0.vy(), m_stMatrix.row1.vy(), m_stMatrix.row2.vy());
		C3DVector<T> row2(m_stMatrix.row0.vz(), m_stMatrix.row1.vz(), m_stMatrix.row2.vz());

		C3X3Matrix<T> rv(row0, row1, row2);

		return rv;
	}

	//return by value (copy). 
	C3X3Matrix Adjoint()
	{
		T at00 = At(0, 0);
		T at01 = At(0, 1);
		T at02 = At(0, 2);

		T at10 = At(1, 0);
		T at11 = At(1, 1);
		T at12 = At(1, 2);

		T at20 = At(2, 0);
		T at21 = At(2, 1);
		T at22 = At(2, 2);

		C3DVector<T> row0( (at11*at22 - at21*at12), -(at01*at22 - at21*at02),  (at01*at12 - at11*at02));
		C3DVector<T> row1(-(at10*at22 - at20*at12),  (at00*at22 - at20*at02), -(at00*at12 - at10*at02));
		C3DVector<T> row2( (at10*at21 - at20*at11), -(at00*at21 - at20*at01),  (at00*at11 - at10*at01));

		C3X3Matrix<T> rv(row0, row1, row2);

		return rv;
	}

	// return by value (copy). 
	C3X3Matrix Inverse()
	{
		C3DVector<T> rowNan(NAN, NAN, NAN);

		C3X3Matrix<T> rv = C3X3Matrix<T>(rowNan, rowNan, rowNan);

		T det = Det();
		if (det != 0)
		{		
			T elm = 1 / det;

			C3DVector<T> row0(elm, 0  , 0);
			C3DVector<T> row1(0  , elm, 0);
			C3DVector<T> row2(0  , 0  , elm);

			C3X3Matrix<T> matDivider(row0, row1, row2);

			rv = (Adjoint())*matDivider;
		}
		
		return rv;
	}


private:

	const C3X3Matrix& Identity()
	{
		C3DVector<T> row0(1, 0, 0);
		C3DVector<T> row1(0, 1, 0);
		C3DVector<T> row2(0, 0, 1);

		C3X3Matrix<T> rv(row0, row1, row2);

		return rv;
	}

private:

	ST_D3X3Matrix m_stMatrix;

};

