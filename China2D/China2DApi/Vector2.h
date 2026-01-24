#ifndef __Vector2Template_h__
#define __Vector2Template_h__

namespace China2D {
	template <typename T>
	class Vector2Template {
	public:
		T _X;
		T _Y;

		Vector2Template() : _X(0), _Y(0) {}
		Vector2Template(T x, T y) : _X(x), _Y(y) {}

		Vector2Template<T> operator+(const Vector2Template<T>& v) const {
			return Vector2Template<T>(_X + v._X, _Y + v._Y);
		}

		Vector2Template<T> operator-(const Vector2Template<T>& v) const {
			return Vector2Template<T>(_X - v._X, _Y - v._Y);
		}

		Vector2Template<T> operator*(T scalar) const {
			return Vector2Template<T>(_X * scalar, _Y * scalar);
		}

		float Length() const {
			return static_cast<float>(std::sqrt(_X * _X + _Y * _Y));
		}

		Vector2Template<T> Normalize() const {
			float len = Length();
			if (len > 0) {
				return Vector2Template<T>(_X / len, _Y / len);
			}
			return *this;  // ·µ»Ø×ÔÉí
		}
	};

	using Vector2 = Vector2Template<float>;
	using Vector2Int = Vector2Template<int>;
	using Size = Vector2Template<float>;
}

#endif // __Vector2Template_h__
