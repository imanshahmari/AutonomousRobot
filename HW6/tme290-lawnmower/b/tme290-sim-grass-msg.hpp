
/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef TME290_GRASS_CONTROL_HPP
#define TME290_GRASS_CONTROL_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace tme290 { namespace grass {
using namespace std::string_literals; // NOLINT
class LIB_API Control {
    private:
        static constexpr const char* TheShortName = "Control";
        static constexpr const char* TheLongName = "tme290.grass.Control";

    public:
        inline static int32_t ID() {
            return 7744;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        Control() = default;
        Control(const Control&) = default;
        Control& operator=(const Control&) = default;
        Control(Control&&) = default;
        Control& operator=(Control&&) = default;
        ~Control() = default;

    public:
        inline Control& command(const uint8_t &v) noexcept {
            m_command = v;
            return *this;
        }
        inline uint8_t command() const noexcept {
            return m_command;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("uint8_t"s), std::move("command"s), m_command, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("uint8_t"s), std::move("command"s), m_command, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("uint8_t"s), std::move("command"s), m_command, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        uint8_t m_command{ 0 }; // field identifier = 1.
};
}}

template<>
struct isVisitable<tme290::grass::Control> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<tme290::grass::Control> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef TME290_GRASS_SENSORS_HPP
#define TME290_GRASS_SENSORS_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace tme290 { namespace grass {
using namespace std::string_literals; // NOLINT
class LIB_API Sensors {
    private:
        static constexpr const char* TheShortName = "Sensors";
        static constexpr const char* TheLongName = "tme290.grass.Sensors";

    public:
        inline static int32_t ID() {
            return 7745;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        Sensors() = default;
        Sensors(const Sensors&) = default;
        Sensors& operator=(const Sensors&) = default;
        Sensors(Sensors&&) = default;
        Sensors& operator=(Sensors&&) = default;
        ~Sensors() = default;

    public:
        inline Sensors& i(const uint32_t &v) noexcept {
            m_i = v;
            return *this;
        }
        inline uint32_t i() const noexcept {
            return m_i;
        }
        inline Sensors& j(const uint32_t &v) noexcept {
            m_j = v;
            return *this;
        }
        inline uint32_t j() const noexcept {
            return m_j;
        }
        inline Sensors& time(const uint64_t &v) noexcept {
            m_time = v;
            return *this;
        }
        inline uint64_t time() const noexcept {
            return m_time;
        }
        inline Sensors& grassTopLeft(const float &v) noexcept {
            m_grassTopLeft = v;
            return *this;
        }
        inline float grassTopLeft() const noexcept {
            return m_grassTopLeft;
        }
        inline Sensors& grassTopCentre(const float &v) noexcept {
            m_grassTopCentre = v;
            return *this;
        }
        inline float grassTopCentre() const noexcept {
            return m_grassTopCentre;
        }
        inline Sensors& grassTopRight(const float &v) noexcept {
            m_grassTopRight = v;
            return *this;
        }
        inline float grassTopRight() const noexcept {
            return m_grassTopRight;
        }
        inline Sensors& grassLeft(const float &v) noexcept {
            m_grassLeft = v;
            return *this;
        }
        inline float grassLeft() const noexcept {
            return m_grassLeft;
        }
        inline Sensors& grassCentre(const float &v) noexcept {
            m_grassCentre = v;
            return *this;
        }
        inline float grassCentre() const noexcept {
            return m_grassCentre;
        }
        inline Sensors& grassRight(const float &v) noexcept {
            m_grassRight = v;
            return *this;
        }
        inline float grassRight() const noexcept {
            return m_grassRight;
        }
        inline Sensors& grassBottomLeft(const float &v) noexcept {
            m_grassBottomLeft = v;
            return *this;
        }
        inline float grassBottomLeft() const noexcept {
            return m_grassBottomLeft;
        }
        inline Sensors& grassBottomCentre(const float &v) noexcept {
            m_grassBottomCentre = v;
            return *this;
        }
        inline float grassBottomCentre() const noexcept {
            return m_grassBottomCentre;
        }
        inline Sensors& grassBottomRight(const float &v) noexcept {
            m_grassBottomRight = v;
            return *this;
        }
        inline float grassBottomRight() const noexcept {
            return m_grassBottomRight;
        }
        inline Sensors& rain(const float &v) noexcept {
            m_rain = v;
            return *this;
        }
        inline float rain() const noexcept {
            return m_rain;
        }
        inline Sensors& battery(const float &v) noexcept {
            m_battery = v;
            return *this;
        }
        inline float battery() const noexcept {
            return m_battery;
        }
        inline Sensors& rainCloudDirX(const float &v) noexcept {
            m_rainCloudDirX = v;
            return *this;
        }
        inline float rainCloudDirX() const noexcept {
            return m_rainCloudDirX;
        }
        inline Sensors& rainCloudDirY(const float &v) noexcept {
            m_rainCloudDirY = v;
            return *this;
        }
        inline float rainCloudDirY() const noexcept {
            return m_rainCloudDirY;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("uint32_t"s), std::move("i"s), m_i, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint32_t"s), std::move("j"s), m_j, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("uint64_t"s), std::move("time"s), m_time, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("float"s), std::move("grassTopLeft"s), m_grassTopLeft, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("float"s), std::move("grassTopCentre"s), m_grassTopCentre, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("float"s), std::move("grassTopRight"s), m_grassTopRight, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("float"s), std::move("grassLeft"s), m_grassLeft, visitor);
                return;
            }
            if (8 == fieldId) {
                doVisit(8, std::move("float"s), std::move("grassCentre"s), m_grassCentre, visitor);
                return;
            }
            if (9 == fieldId) {
                doVisit(9, std::move("float"s), std::move("grassRight"s), m_grassRight, visitor);
                return;
            }
            if (10 == fieldId) {
                doVisit(10, std::move("float"s), std::move("grassBottomLeft"s), m_grassBottomLeft, visitor);
                return;
            }
            if (11 == fieldId) {
                doVisit(11, std::move("float"s), std::move("grassBottomCentre"s), m_grassBottomCentre, visitor);
                return;
            }
            if (12 == fieldId) {
                doVisit(12, std::move("float"s), std::move("grassBottomRight"s), m_grassBottomRight, visitor);
                return;
            }
            if (13 == fieldId) {
                doVisit(13, std::move("float"s), std::move("rain"s), m_rain, visitor);
                return;
            }
            if (14 == fieldId) {
                doVisit(14, std::move("float"s), std::move("battery"s), m_battery, visitor);
                return;
            }
            if (15 == fieldId) {
                doVisit(15, std::move("float"s), std::move("rainCloudDirX"s), m_rainCloudDirX, visitor);
                return;
            }
            if (16 == fieldId) {
                doVisit(16, std::move("float"s), std::move("rainCloudDirY"s), m_rainCloudDirY, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("uint32_t"s), std::move("i"s), m_i, visitor);
            doVisit(2, std::move("uint32_t"s), std::move("j"s), m_j, visitor);
            doVisit(3, std::move("uint64_t"s), std::move("time"s), m_time, visitor);
            doVisit(4, std::move("float"s), std::move("grassTopLeft"s), m_grassTopLeft, visitor);
            doVisit(5, std::move("float"s), std::move("grassTopCentre"s), m_grassTopCentre, visitor);
            doVisit(6, std::move("float"s), std::move("grassTopRight"s), m_grassTopRight, visitor);
            doVisit(7, std::move("float"s), std::move("grassLeft"s), m_grassLeft, visitor);
            doVisit(8, std::move("float"s), std::move("grassCentre"s), m_grassCentre, visitor);
            doVisit(9, std::move("float"s), std::move("grassRight"s), m_grassRight, visitor);
            doVisit(10, std::move("float"s), std::move("grassBottomLeft"s), m_grassBottomLeft, visitor);
            doVisit(11, std::move("float"s), std::move("grassBottomCentre"s), m_grassBottomCentre, visitor);
            doVisit(12, std::move("float"s), std::move("grassBottomRight"s), m_grassBottomRight, visitor);
            doVisit(13, std::move("float"s), std::move("rain"s), m_rain, visitor);
            doVisit(14, std::move("float"s), std::move("battery"s), m_battery, visitor);
            doVisit(15, std::move("float"s), std::move("rainCloudDirX"s), m_rainCloudDirX, visitor);
            doVisit(16, std::move("float"s), std::move("rainCloudDirY"s), m_rainCloudDirY, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("uint32_t"s), std::move("i"s), m_i, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint32_t"s), std::move("j"s), m_j, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("uint64_t"s), std::move("time"s), m_time, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("float"s), std::move("grassTopLeft"s), m_grassTopLeft, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("float"s), std::move("grassTopCentre"s), m_grassTopCentre, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("float"s), std::move("grassTopRight"s), m_grassTopRight, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("float"s), std::move("grassLeft"s), m_grassLeft, preVisit, visit, postVisit);
            doTripletForwardVisit(8, std::move("float"s), std::move("grassCentre"s), m_grassCentre, preVisit, visit, postVisit);
            doTripletForwardVisit(9, std::move("float"s), std::move("grassRight"s), m_grassRight, preVisit, visit, postVisit);
            doTripletForwardVisit(10, std::move("float"s), std::move("grassBottomLeft"s), m_grassBottomLeft, preVisit, visit, postVisit);
            doTripletForwardVisit(11, std::move("float"s), std::move("grassBottomCentre"s), m_grassBottomCentre, preVisit, visit, postVisit);
            doTripletForwardVisit(12, std::move("float"s), std::move("grassBottomRight"s), m_grassBottomRight, preVisit, visit, postVisit);
            doTripletForwardVisit(13, std::move("float"s), std::move("rain"s), m_rain, preVisit, visit, postVisit);
            doTripletForwardVisit(14, std::move("float"s), std::move("battery"s), m_battery, preVisit, visit, postVisit);
            doTripletForwardVisit(15, std::move("float"s), std::move("rainCloudDirX"s), m_rainCloudDirX, preVisit, visit, postVisit);
            doTripletForwardVisit(16, std::move("float"s), std::move("rainCloudDirY"s), m_rainCloudDirY, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        uint32_t m_i{ 0 }; // field identifier = 1.
        uint32_t m_j{ 0 }; // field identifier = 2.
        uint64_t m_time{ 0 }; // field identifier = 3.
        float m_grassTopLeft{ 0.0f }; // field identifier = 4.
        float m_grassTopCentre{ 0.0f }; // field identifier = 5.
        float m_grassTopRight{ 0.0f }; // field identifier = 6.
        float m_grassLeft{ 0.0f }; // field identifier = 7.
        float m_grassCentre{ 0.0f }; // field identifier = 8.
        float m_grassRight{ 0.0f }; // field identifier = 9.
        float m_grassBottomLeft{ 0.0f }; // field identifier = 10.
        float m_grassBottomCentre{ 0.0f }; // field identifier = 11.
        float m_grassBottomRight{ 0.0f }; // field identifier = 12.
        float m_rain{ 0.0f }; // field identifier = 13.
        float m_battery{ 0.0f }; // field identifier = 14.
        float m_rainCloudDirX{ 0.0f }; // field identifier = 15.
        float m_rainCloudDirY{ 0.0f }; // field identifier = 16.
};
}}

template<>
struct isVisitable<tme290::grass::Sensors> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<tme290::grass::Sensors> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef TME290_GRASS_STATUS_HPP
#define TME290_GRASS_STATUS_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace tme290 { namespace grass {
using namespace std::string_literals; // NOLINT
class LIB_API Status {
    private:
        static constexpr const char* TheShortName = "Status";
        static constexpr const char* TheLongName = "tme290.grass.Status";

    public:
        inline static int32_t ID() {
            return 7746;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        Status() = default;
        Status(const Status&) = default;
        Status& operator=(const Status&) = default;
        Status(Status&&) = default;
        Status& operator=(Status&&) = default;
        ~Status() = default;

    public:
        inline Status& time(const uint64_t &v) noexcept {
            m_time = v;
            return *this;
        }
        inline uint64_t time() const noexcept {
            return m_time;
        }
        inline Status& grassMax(const float &v) noexcept {
            m_grassMax = v;
            return *this;
        }
        inline float grassMax() const noexcept {
            return m_grassMax;
        }
        inline Status& grassMean(const float &v) noexcept {
            m_grassMean = v;
            return *this;
        }
        inline float grassMean() const noexcept {
            return m_grassMean;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("uint64_t"s), std::move("time"s), m_time, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("float"s), std::move("grassMax"s), m_grassMax, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("float"s), std::move("grassMean"s), m_grassMean, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("uint64_t"s), std::move("time"s), m_time, visitor);
            doVisit(2, std::move("float"s), std::move("grassMax"s), m_grassMax, visitor);
            doVisit(3, std::move("float"s), std::move("grassMean"s), m_grassMean, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("uint64_t"s), std::move("time"s), m_time, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("float"s), std::move("grassMax"s), m_grassMax, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("float"s), std::move("grassMean"s), m_grassMean, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        uint64_t m_time{ 0 }; // field identifier = 1.
        float m_grassMax{ 0.0f }; // field identifier = 2.
        float m_grassMean{ 0.0f }; // field identifier = 3.
};
}}

template<>
struct isVisitable<tme290::grass::Status> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<tme290::grass::Status> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef TME290_GRASS_RESTART_HPP
#define TME290_GRASS_RESTART_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>
namespace tme290 { namespace grass {
using namespace std::string_literals; // NOLINT
class LIB_API Restart {
    private:
        static constexpr const char* TheShortName = "Restart";
        static constexpr const char* TheLongName = "tme290.grass.Restart";

    public:
        inline static int32_t ID() {
            return 7747;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        Restart() = default;
        Restart(const Restart&) = default;
        Restart& operator=(const Restart&) = default;
        Restart(Restart&&) = default;
        Restart& operator=(Restart&&) = default;
        ~Restart() = default;

    public:
        inline Restart& seed(const uint32_t &v) noexcept {
            m_seed = v;
            return *this;
        }
        inline uint32_t seed() const noexcept {
            return m_seed;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("uint32_t"s), std::move("seed"s), m_seed, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("uint32_t"s), std::move("seed"s), m_seed, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("uint32_t"s), std::move("seed"s), m_seed, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        uint32_t m_seed{ 0 }; // field identifier = 1.
};
}}

template<>
struct isVisitable<tme290::grass::Restart> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<tme290::grass::Restart> {
    static const bool value = true;
};
#endif

