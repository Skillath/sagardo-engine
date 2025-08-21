#ifndef MATHF_H
#define MATHF_H

#include <type_traits>
#include <cmath>
#include <algorithm>
#include <glm/gtc/quaternion.hpp>

namespace SagardoEngine
{
    struct Mathf final
    {
        // ---------- helpers ----------
        template <typename T>
        static constexpr bool IsFloat = std::is_floating_point_v<T>;

        template <typename T>
        static constexpr bool IsArithmetic = std::is_arithmetic_v<T>;

        template <typename T>
        static constexpr T Epsilon()
        {
            if constexpr (IsFloat<T>) return static_cast<T>(1e-7);
            else return static_cast<T>(0);
        }

        template <typename T>
        static T Clamp(const T& x, const T& lo, const T& hi)
        {
            return std::clamp(x, lo, hi);
        }

        // ============================================================
        // LERP
        // ============================================================

        // Scalar lerp (arithmetic). For ints, does the math in double then casts back to T.
        template <typename T, typename U,
                  typename = std::enable_if_t<IsArithmetic<T> && IsArithmetic<U>>>
        static T Lerp(T a, T b, U t)
        {
            const double tt = static_cast<double>(t);
            const double aa = static_cast<double>(a);
            const double bb = static_cast<double>(b);
            return static_cast<T>(aa + (bb - aa) * tt);
        }

        // GLM vector lerp (floating component)
        template <glm::length_t L, typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static glm::vec<L, T, Q> Lerp(const glm::vec<L, T, Q>& a,
                                      const glm::vec<L, T, Q>& b,
                                      T t)
        {
            return a + (b - a) * t;
        }

        // Quaternion lerp -> use SLERP (correct for rotations)
        template <typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static glm::qua<T, Q> Lerp(const glm::qua<T, Q>& a,
                                   const glm::qua<T, Q>& b,
                                   T t)
        {
            // Ensure shortest path: glm::slerp already handles this when inputs are normalized.
            return glm::slerp(glm::normalize(a), glm::normalize(b), t);
        }

        // ============================================================
        // INVERSE LERP
        // ============================================================

        // Scalar inverse lerp: returns t such that v = lerp(a,b,t).
        template <typename T,
                  typename = std::enable_if_t<IsArithmetic<T>>>
        static double InverseLerp(T a, T b, T v)
        {
            const double denom = static_cast<double>(b) - static_cast<double>(a);
            if (std::abs(denom) <= 1e-12) return 0.0; // degenerate
            return (static_cast<double>(v) - static_cast<double>(a)) / denom;
        }

        // Vector inverse lerp (projection): scalar t along the line a->b.
        template <glm::length_t L, typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static T InverseLerp(const glm::vec<L, T, Q>& a,
                             const glm::vec<L, T, Q>& b,
                             const glm::vec<L, T, Q>& v)
        {
            const glm::vec<L, T, Q> ab = b - a;
            const glm::vec<L, T, Q> av = v - a;
            const T denom = glm::dot(ab, ab);
            if (std::abs(denom) <= static_cast<T>(1e-12)) return static_cast<T>(0);
            return glm::dot(av, ab) / denom;
        }

        // Quaternion inverse lerp: fraction of angle from a to v relative to a->b.
        // Assumes v lies on the shortest-arc slerp path between a and b; otherwise this is a projection.
        template <typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static T InverseLerp(const glm::qua<T, Q>& a,
                             const glm::qua<T, Q>& b,
                             const glm::qua<T, Q>& v)
        {
            const glm::qua<T, Q> an = glm::normalize(a);
            glm::qua<T, Q> bn = glm::normalize(b);
            glm::qua<T, Q> vn = glm::normalize(v);

            // Force into same hemisphere as 'a' for shortest path comparisons
            if (glm::dot(an, bn) < static_cast<T>(0)) bn = -bn;
            if (glm::dot(an, vn) < static_cast<T>(0)) vn = -vn;

            auto angle_between = [](const glm::qua<T, Q>& q0, const glm::qua<T, Q>& q1) -> T
            {
                const T d = Clamp(glm::dot(q0, q1), static_cast<T>(-1), static_cast<T>(1));
                // Angle between rotations represented by unit quaternions is 2*acos(dot)
                return static_cast<T>(2) * std::acos(static_cast<double>(std::abs(d)));
            };

            const T total = angle_between(an, bn);
            if (total <= static_cast<T>(1e-12)) return static_cast<T>(0);

            const T part = angle_between(an, vn);
            return part / total; // may be outside [0,1] if v is off-arc
        }

        // ============================================================
        // REMAP
        // ============================================================

        // Scalar remap: v in [inMin,inMax] -> out interval (unclamped).
        template <typename T,
                  typename = std::enable_if_t<IsArithmetic<T>>>
        static T Remap(T inMin, T inMax, T outMin, T outMax, T v)
        {
            const double t = InverseLerp(inMin, inMax, v);
            return Lerp(outMin, outMax, t);
        }

        // Vector remap: uses scalar t along a->b and applies it between outMin->outMax.
        template <glm::length_t L, typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static glm::vec<L, T, Q> Remap(const glm::vec<L, T, Q>& inMin,
                                       const glm::vec<L, T, Q>& inMax,
                                       const glm::vec<L, T, Q>& outMin,
                                       const glm::vec<L, T, Q>& outMax,
                                       const glm::vec<L, T, Q>& v)
        {
            const T t = InverseLerp(inMin, inMax, v);
            return Lerp(outMin, outMax, t);
        }

        // Quaternion remap: map q from [qa,qb] into [qc,qd] using quaternion t.
        template <typename T, glm::qualifier Q,
                  typename = std::enable_if_t<IsFloat<T>>>
        static glm::qua<T, Q> Remap(const glm::qua<T, Q>& qa,
                                    const glm::qua<T, Q>& qb,
                                    const glm::qua<T, Q>& qc,
                                    const glm::qua<T, Q>& qd,
                                    const glm::qua<T, Q>& q)
        {
            const T t = InverseLerp(qa, qb, q);
            return Lerp(qc, qd, t);
        }
        
        template<typename T, typename U>
        static T LerpClamped(T a, T b, U t)
        {
            return Lerp(a, b, Clamp<U>(t, 0, 1));
        }
    };
}

#endif //MATHF_H
