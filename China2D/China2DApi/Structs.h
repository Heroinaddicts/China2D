#ifndef __Structs_h__
#define __Structs_h__

#include <cmath>
#include <iostream>

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
			return *this;  // 返回自身
		}
	};

	using Vector2 = Vector2Template<float>;
	using Vector2Int = Vector2Template<int>;
	using Size = Vector2Template<float>;

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

	struct RectF {
		float x;
		float y;
		float w;
		float h;
	};

	struct Color4 {
		float R;
		float G;
		float B;
		float A;

		Color4()
			: R(1.0f), G(1.0f), B(1.0f), A(1.0f) {
		}

		Color4(float r, float g, float b, float a = 1.0f)
			: R(r), G(g), B(b), A(a) {
		}
	};

    class Vector4 {
    public:
        float X, Y, Z, W;

        Vector4() : X(0), Y(0), Z(0), W(1) {}
        Vector4(float x, float y, float z, float w)
            : X(x), Y(y), Z(z), W(w) {
        }
    };

    class Matrix4x4 {
    public:
        float M[16];

        Matrix4x4() {
            SetIdentity();
        }

        explicit Matrix4x4(float diagonal) {
            SetZero();
            M[0] = diagonal;
            M[5] = diagonal;
            M[10] = diagonal;
            M[15] = diagonal;
        }

        static Matrix4x4 Identity() {
            return Matrix4x4(1.0f);
        }

        void SetZero() {
            memset(M, 0, sizeof(M));
        }

        void SetIdentity() {
            SetZero();
            M[0] = 1.0f;
            M[5] = 1.0f;
            M[10] = 1.0f;
            M[15] = 1.0f;
        }

        static Matrix4x4 Translate(float x, float y, float z = 0.0f) {
            Matrix4x4 m = Identity();
            m.M[12] = x;
            m.M[13] = y;
            m.M[14] = z;
            return m;
        }

        static Matrix4x4 Scale(float x, float y, float z = 1.0f) {
            Matrix4x4 m;
            m.SetZero();
            m.M[0] = x;
            m.M[5] = y;
            m.M[10] = z;
            m.M[15] = 1.0f;
            return m;
        }

        static Matrix4x4 RotateZ(float rad) {
            float c = cosf(rad);
            float s = sinf(rad);

            Matrix4x4 m = Identity();
            m.M[0] = c;  m.M[4] = -s;
            m.M[1] = s;  m.M[5] = c;
            return m;
        }

        static Matrix4x4 Ortho(
            float left, float right,
            float bottom, float top,
            float zNear = -1.0f, float zFar = 1.0f
        ) {
            Matrix4x4 m;
            m.SetZero();

            m.M[0] = 2.0f / (right - left);
            m.M[5] = 2.0f / (top - bottom);
            m.M[10] = -2.0f / (zFar - zNear);

            m.M[12] = -(right + left) / (right - left);
            m.M[13] = -(top + bottom) / (top - bottom);
            m.M[14] = -(zFar + zNear) / (zFar - zNear);
            m.M[15] = 1.0f;

            return m;
        }

        Matrix4x4 operator*(const Matrix4x4& rhs) const {
            Matrix4x4 result;
            result.SetZero();

            for (int col = 0; col < 4; ++col) {
                for (int row = 0; row < 4; ++row) {
                    result.M[col * 4 + row] =
                        M[0 * 4 + row] * rhs.M[col * 4 + 0] +
                        M[1 * 4 + row] * rhs.M[col * 4 + 1] +
                        M[2 * 4 + row] * rhs.M[col * 4 + 2] +
                        M[3 * 4 + row] * rhs.M[col * 4 + 3];
                }
            }
            return result;
        }

        Matrix4x4& operator*=(const Matrix4x4& rhs) {
            *this = (*this) * rhs;
            return *this;
        }

        Vector4 MultiplyPoint(float x, float y, float z, float w) const {
            Vector4 r;
            r.X =
                M[0] * x + M[4] * y + M[8] * z + M[12] * w;
            r.Y =
                M[1] * x + M[5] * y + M[9] * z + M[13] * w;
            r.Z =
                M[2] * x + M[6] * y + M[10] * z + M[14] * w;
            r.W =
                M[3] * x + M[7] * y + M[11] * z + M[15] * w;
            return r;
        }

        const float* Data() const { return M; }
        float* Data() { return M; }
    };
}

#endif // __Structs_h__
