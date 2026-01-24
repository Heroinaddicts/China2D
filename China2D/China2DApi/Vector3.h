#ifndef __Vector3Template_h__
#define __Vector3Template_h__

#include <cmath>
#include <iostream>

namespace China2D {
	template <typename T>
	class Vector3Template {
	public:
		T _X;  // X 分量
		T _Y;  // Y 分量
		T _Z;  // Z 分量

		// 默认构造函数
		Vector3Template() : _X(0), _Y(0), _Z(0) {}

		// 带参数的构造函数
		Vector3Template(T x, T y, T z) : _X(x), _Y(y), _Z(z) {}

		// 重载加法运算符
		Vector3Template<T> operator+(const Vector3Template<T>& v) const {
			return Vector3Template<T>(_X + v._X, _Y + v._Y, _Z + v._Z);
		}

		// 重载减法运算符
		Vector3Template<T> operator-(const Vector3Template<T>& v) const {
			return Vector3Template<T>(_X - v._X, _Y - v._Y, _Z - v._Z);
		}

		// 重载乘法运算符（标量乘法）
		Vector3Template<T> operator*(T scalar) const {
			return Vector3Template<T>(_X * scalar, _Y * scalar, _Z * scalar);
		}

		// 计算向量的长度（模）
		float Length() const {
			return static_cast<float>(std::sqrt(_X * _X + _Y * _Y + _Z * _Z));
		}

		// 向量归一化
		Vector3Template<T> Normalize() const {
			float len = Length();
			if (len > 0) {
				return Vector3Template<T>(_X / len, _Y / len, _Z / len);
			}
			return *this;  // 返回自身
		}

		// 计算点积
		float Dot(const Vector3Template<T>& v) const {
			return static_cast<float>(_X * v._X + _Y * v._Y + _Z * v._Z);
		}

		// 打印向量（方便调试）
		void Print() const {
			std::cout << "Vector3Template(" << _X << ", " << _Y << ", " << _Z << ")" << std::endl;
		}
	};

	// 为 float 和 int 类型定义别名
	using Vector3 = Vector3Template<float>;
	using Vector3Int = Vector3Template<int>;
}

#endif // __Vector3Template_h__
