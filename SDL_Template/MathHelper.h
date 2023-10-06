#ifndef __MATHHELPER_H
#define __MATHHELPER_H

#include <string>
#include <math.h>
#include <ostream>

namespace SDLFramework {

#define PI 3.1415926535f
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

	struct Vector2 {
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f)
			: x{ _x }, y{ _y } {}

		float MagnitudeSqr() const {
			return x * x + y * y;
		}

		float Magnitude() const {
			return (float)sqrt(x * x + y * y);
		}

		Vector2 Normalized() const {
			float mag = Magnitude();
			if (mag == 0.0f) {
				return Vector2(0.0f, 0.0f);
			}
			else {
				return Vector2(x / mag, y / mag);
			}
		}

		Vector2 & operator+=(const Vector2 & rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vector2 & operator-=(const Vector2 & rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vector2 operator-() const {
			return Vector2(-x, -y);
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
			os << "(" << vec.x << ", " << vec.y << ")";
			return os;
		}

		bool operator>=(const Vector2& rhs) {
			return MagnitudeSqr() >= rhs.MagnitudeSqr();
		}
	};

	inline Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs) {
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs) {
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vector2 operator*(const Vector2 & lhs, float rhs) {
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}

	inline Vector2 operator*(float lhs, const Vector2 & rhs) {
		return Vector2(lhs * rhs.x, lhs * rhs.y);
	}

	inline Vector2 operator/(const Vector2& lhs, float rhs) {
		return Vector2(lhs.x / rhs, lhs.y / rhs);
	}

	inline Vector2 Lerp(const Vector2 & start, const Vector2 & end, float time) {
		if (time <= 0.0f) {
			return start;
		}

		if (time >= 1.0f) {
			return end;
		}

		Vector2 dir = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;
	}

	inline Vector2 RotateVector(const Vector2 & vec, float angle) {
		float radAngle = (float)(angle * DEG_TO_RAD);

		return Vector2(
			(float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)),
			(float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))
		);
	}

	inline float Dot(const Vector2& vec1, const Vector2& vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	inline float Clamp(const float& value, const float& min, const float& max) {
		if (value > max)
			return max;
		if (value < min)
			return min;
		return value;
	}


	const Vector2 Vec2_Zero = { 0.0f, 0.0f };
	const Vector2 Vec2_One = { 1.0f, 1.0f };
	const Vector2 Vec2_Up = { 0.0f, 1.0f };
	const Vector2 Vec2_Right = { 1.0f, 0.0f };

	// cubic bezier curve
	struct BezierCurve {
		Vector2 p0;
		Vector2 p1;
		Vector2 p2;
		Vector2 p3;

		Vector2 CalculatePointAlongCurve(float t) {
			float tt = t * t;
			float ttt = tt * t;
			float u = 1.0f - t;
			float uu = u * u;
			float uuu = uu * u;

			Vector2 point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
			point.x = (float)round(point.x);
			point.y = (float)round(point.y);
			return point;
		}
	};

	inline float PointToLineDistance(const Vector2 & lineStart, const Vector2 & lineEnd, const Vector2& point) {
		Vector2 slope = lineEnd - lineStart;
		float param = Clamp(Dot(point - lineStart, slope) / slope.MagnitudeSqr(), 0.0f,	1.0f);
		Vector2 nearestPoint = lineStart + slope * param;

		return (point - nearestPoint).Magnitude();
	}

	inline bool PointInPolygon(Vector2* verts, int vertCount, const Vector2& point) {
		bool retVal = false;

		for (int i = 0, j = vertCount - 1; i < vertCount; j = i++) {
			if ((verts[i].y >= point.y) != (verts[j].y >= point.y)) {
				Vector2 vec1 = (verts[i] - verts[j]).Normalized();
				Vector2 proj = verts[j] + vec1 * Dot(point - verts[j], vec1);
				if (proj.x > point.x) {
					retVal = !retVal;
				}
			}
		}
		return retVal;
	}

	inline float getInterpolant(Vector2 startPosition, Vector2 currentPosition, Vector2 targetPosition) {
		float totalDistance = (targetPosition - startPosition).Magnitude();
		float currentDistance = (currentPosition - targetPosition).Magnitude();
		return currentDistance / totalDistance;
	}

	inline float getInterpolant(Vector2 currentPosition, Vector2 targetPosition, float totalDistance) {
		float currentDistance = (currentPosition - targetPosition).Magnitude();
		return currentDistance / totalDistance;
	}

	inline float getRotation(Vector2 currentPosition, Vector2 targetPosition) {
		float angleRadians = std::atan2(currentPosition.y - targetPosition.y, currentPosition.x - targetPosition.x);
		float angleDegrees = (angleRadians * (180.0f / PI)) - 90;
		return angleDegrees;
	}

	inline float getConstantSpeed(Vector2 startPosition, Vector2 targetPosition, float speed, float frameRate) {
		float totalDistance = (targetPosition - startPosition).Magnitude();
		float constantSpeed = (totalDistance / speed) * frameRate;
		return constantSpeed;
	}

	inline float getConstantSpeed(float totalDistance, float speed, float frameRate) {
		float constantSpeed = (totalDistance / speed) * frameRate;
		return constantSpeed;
	}

	inline Vector2 getMoveVector(Vector2 targetPosition, Vector2 startPosition, float multiplier) {
		Vector2 mouseToScreenMiddle = targetPosition - startPosition;
		float distance = mouseToScreenMiddle.Magnitude();

		if (distance != 0) {
			Vector2 direction = mouseToScreenMiddle / distance;
			return direction * (distance * multiplier);
		}
		else {
			return Vector2(0.0f, 0.0f);
		}
	}

	inline float roundToDecimalPlaces(float number, int decimalPlaces) {
		float multiplier = (float)std::pow(10.0f, decimalPlaces);
		return std::round(number * multiplier) / multiplier;
	}

	inline std::string removeTrailingZeros(float number) {
		std::string strNumber = std::to_string(number);
		size_t decimalPos = strNumber.find('.');

		if (decimalPos != std::string::npos) {
			size_t lastNonZero = strNumber.find_last_not_of('0');

			if (lastNonZero != std::string::npos && lastNonZero > decimalPos) {
				strNumber.erase(lastNonZero + 1);
			}
			else if (lastNonZero != std::string::npos && lastNonZero == decimalPos) {
				strNumber.erase(lastNonZero);
			}
		}

		return strNumber;
	}

	inline std::string getCondensedNumber(unsigned long long number) {
		std::string str;

		if (number < 1000) {
			str = std::to_string(number);
		}
		else if (number < 1000000) {
			str = std::to_string(number / 1000) + "K";
		}
		else if (number < 1000000000) {
			str = std::to_string(number / 1000000) + "M";
		}
		else if (number < 1000000000000) {
			str = std::to_string(number / 1000000000) + "B";
		}
		else if (number < 1000000000000000) {
			str = std::to_string(number / 1000000000000) + "T";
		}
		else if (number < 1000000000000000000) {
			str = std::to_string(number / 1000000000000000) + "Qd";
		}
		else {
			str = std::to_string(number / 10000000000000000);
			str.insert(str.length() - 2, ".");
			str = str + "Qn";
		}

		return str;
	}

	struct Vertex {
		Vector2 position;

		struct UV {
			float u;
			float v;
		} uv;

		struct Color {
			float r;
			float g;
			float b;
			float a;
		} color;

		void SetPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void SetUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

		void SetColor(float r, float g, float b, float a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
	};


}

#endif