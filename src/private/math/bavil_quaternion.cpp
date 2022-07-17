#include "math/bavil_quaternion.h"
#include "math/bavil_matrix33.h"
#include "math/bavil_matrix44.h"

namespace bavil::math
{

	namespace
	{

		static constexpr f32 quaternion_identity[] =
		{
			0.f,
			0.f,
			0.f,
			1.f
		};


		static constexpr f32 quaternion_empty[] =
		{
			0.f,
			0.f,
			0.f,
			0.f
		};

	} //! namespace 


	/// <summary>
	/// 単位クォータニオン.
	/// </summary>
	const Quaternion& Quaternion::IDENTITY = *reinterpret_cast<const Quaternion*>(quaternion_identity);

	/// <summary>
	/// 全てがゼロで初期化されたクォータニオン.
	/// </summary>
	const Quaternion& Quaternion::EMPTY = *reinterpret_cast<const Quaternion*>(quaternion_empty);

	Quaternion& Quaternion::setMatrix(Matrix44 const& m)
	{
		value_type tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];

		if (tr >= 1.0f)
		{
			value_type const fourD = 2.0f * std::sqrt(tr);
			this->w = fourD / 4.0f;
			this->x = (m.m[1][2] - m.m[2][1]) / fourD;
			this->y = (m.m[2][0] - m.m[0][2]) / fourD;
			this->z = (m.m[0][1] - m.m[1][0]) / fourD;

			return *this;
		}

		value_type qa[4];
		int i, j, k;

		if (m.m[0][0] > m.m[1][1])
		{
			i = 0;
		}
		else
		{
			i = 1;
		}
		if (m.m[2][2] > m.m[i][i])
		{
			i = 2;
		}

		j = (i + 1) % 3;
		k = (j + 1) % 3;

		tr = m.m[i][i] - m.m[j][j] - m.m[k][k] + 1.0f;

		value_type const fourD = 2.0f * std::sqrt(tr);

		qa[i] = fourD / 4.0f;
		qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
		qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
		qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

		this->x = qa[0];
		this->y = qa[1];
		this->z = qa[2];
		this->w = qa[3];

		return	*this;

	}

	Matrix44 Quaternion::rotate() const noexcept
	{
		value_type xx = this->x * this->x * 2.0f;
		value_type yy = this->y * this->y * 2.0f;
		value_type zz = this->z * this->z * 2.0f;
		value_type xy = this->x * this->y * 2.0f;
		value_type xz = this->x * this->z * 2.0f;
		value_type yz = this->y * this->z * 2.0f;
		value_type wx = this->w * this->x * 2.0f;
		value_type wy = this->w * this->y * 2.0f;
		value_type wz = this->w * this->z * 2.0f;

		return Matrix44
		(
			1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
			xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
			xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Quaternion Quaternion::Rotation(Matrix33 const& m)
	{

		value_type tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + 1.0f;

		if (tr >= 1.0f)
		{
			const value_type fourD = 2.0f * std::sqrt(tr);

			return
			{
				(m.m[1][2] - m.m[2][1]) / fourD,
				(m.m[2][0] - m.m[0][2]) / fourD,
				(m.m[0][1] - m.m[1][0]) / fourD,
				fourD / 4.0f
			};
		}

		value_type		qa[4];
		int			i, j, k;

		i = (m.m[0][0] > m.m[1][1]) ? (0) : (1);


		if (m.m[2][2] > m.m[i][i])
		{
			i = 2;
		}

		j = (i + 1) % 3;
		k = (j + 1) % 3;

		tr = m.m[i][i] - m.m[j][j] - m.m[k][k] + 1.0f;

		const value_type fourD = 2.0f * std::sqrt(tr);

		qa[i] = fourD / 4.0f;
		qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
		qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
		qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

		return
		{
			qa[0],
			qa[1],
			qa[2],
			qa[3]
		};
	}

	Quaternion Quaternion::Rotation(Matrix44 const& m)
	{
		value_type tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];
		if (tr >= 1.0f)
		{
			const value_type fourD = 2.0f * std::sqrt(tr);
			return
			{
				(m.m[1][2] - m.m[2][1]) / fourD,
				(m.m[2][0] - m.m[0][2]) / fourD,
				(m.m[0][1] - m.m[1][0]) / fourD,
				fourD / 4.0f
			};
		}

		int i = 0;

		if (m.m[0][0] <= m.m[1][1])
		{
			i = 1;
		}
		if (m.m[2][2] > m.m[i][i])
		{
			i = 2;
		}

		int j = (i + 1) % 3;
		int k = (j + 1) % 3;

		tr = m.m[i][i] - m.m[j][j] - m.m[k][k] + 1.0f;

		value_type fourD = 2.0f * std::sqrt(tr);
		value_type qa[4];

		qa[i] = fourD / 4.0f;
		qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
		qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
		qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

		return
		{
			qa[0],
			qa[1],
			qa[2],
			qa[3]
		};
	}

	Matrix44 Quaternion::Rotate(const Vector3& axis, Radian angle)
	{
		return Quaternion(axis, angle).rotate();
	}

}
