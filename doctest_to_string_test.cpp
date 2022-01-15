#include "doctest/doctest.h"
#include "ApprovalTests.hpp"
#include <sstream>

#if __cplusplus >= 202002L
#   define CXX_STANDARD 20
#elif __cplusplus >= 201703L
#   define CXX_STANDARD 17
#elif __cplusplus >= 201402L
#   define CXX_STANDARD 14
#elif __cplusplus >= 201103L
#   define CXX_STANDARD 11
#endif

//#define USE_STL_STRINGIFIER
#ifdef USE_STL_STRINGIFIER
#   define DOCTEST_CPP CXX_STANDARD
#   define DOCTEST_STL_STRINGIFY_CHRONO
#   define DOCTEST_STL_STRINGIFY_FLIP
#   include "stl_stringifier.h"
#endif

#include <string>
#include <utility>
#include <tuple>
#include <array>
#include <valarray>
#include <initializer_list>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <set>
#include <map>

#if CXX_STANDARD >= 14
#   include <string_view>
#endif

#if CXX_STANDARD >= 17
#   include <optional>
#   include <variant>
#endif

#if CXX_STANDARD >= 20
#   include <span>
#endif

using namespace ApprovalTests;

namespace
{

enum Enum
{
    E_VALUE = 1
};

enum EnumWithOss
{
    E_VALUE_WITH_OSS = 2
};

std::ostream& operator<<( std::ostream& os, EnumWithOss value )
{
    switch (value) {
    default:
        os << "???";
        break;
    case EnumWithOss::E_VALUE_WITH_OSS:
        os << "E_VALUE_WITH_OSS";
        break;
    }
    return os;
}

enum class EnumClass : int
{
    VALUE = 3
};

enum class EnumClassWithOss : int
{
    A = 4
};

std::ostream& operator<<( std::ostream& os, EnumClassWithOss value )
{
    switch (value) {
    default:
        os << "???";
        break;
    case EnumClassWithOss::A:
        os << "A";
        break;
    }
    return os;
}

struct Struct
{
};

struct StructOss
{
    int value;
};

inline std::ostream& operator<<(std::ostream& os, StructOss s)
{
    return os << s.value;
}

}

TEST_CASE("doctest::toString")
{
    std::ostringstream ss;
    
    auto formLabel = []( const char* str )
    {
        constexpr size_t LABEL_WIDTH = 30;
        const size_t len = strlen( str );
        const size_t spacesToAdd = (len < LABEL_WIDTH) ? LABEL_WIDTH - len : 0u;
        return std::string(4, ' ') + str + ':' + std::string(spacesToAdd, ' ') + ' ';
    };
    
#define DUMP_TYPE_VALUE(TYPE, VALUE) ss << formLabel( #TYPE ) << doctest::toString( static_cast<TYPE>(VALUE) ) << '\n'
    
    // https://en.cppreference.com/w/cpp/language/types
    ss << "Fundamental types:\n";
    
    // std::nullptr_t
    DUMP_TYPE_VALUE(std::nullptr_t, nullptr);
    
    // Signed and unsigned integer types
    DUMP_TYPE_VALUE(short int, -1);
    DUMP_TYPE_VALUE(unsigned short int, 1);
    DUMP_TYPE_VALUE(int, -2);
    DUMP_TYPE_VALUE(unsigned int, 2);
    DUMP_TYPE_VALUE(long int, -3);
    DUMP_TYPE_VALUE(unsigned long int, 3);
    DUMP_TYPE_VALUE(long long int, -4);
    DUMP_TYPE_VALUE(unsigned long long int, 4);
    
    // Boolean type
    DUMP_TYPE_VALUE(bool, true);
    
    // Character types
    DUMP_TYPE_VALUE(signed char, 'A');
    DUMP_TYPE_VALUE(unsigned char, 'B');
    DUMP_TYPE_VALUE(char, 'C');
    DUMP_TYPE_VALUE(wchar_t, L'D');
    DUMP_TYPE_VALUE(char16_t, L'E');
    DUMP_TYPE_VALUE(char32_t, L'F');
    
    // Floating-point types
    DUMP_TYPE_VALUE(float, 1.1f);
    DUMP_TYPE_VALUE(double, 2.2);
    DUMP_TYPE_VALUE(long double, 3.3);
    
    #define DUMP_POINTER_TYPE_VALUE(TYPE, VALUE) ss << formLabel( #TYPE "*" ) << doctest::toString( reinterpret_cast<TYPE*>(VALUE) ) << '\n' // NOLINT
    
    // Signed and unsigned integer types
    DUMP_POINTER_TYPE_VALUE(short int, 0);
    DUMP_POINTER_TYPE_VALUE(unsigned short int, 2);
    DUMP_POINTER_TYPE_VALUE(int, 3);
    DUMP_POINTER_TYPE_VALUE(unsigned int, 4);
    DUMP_POINTER_TYPE_VALUE(long int, 5);
    DUMP_POINTER_TYPE_VALUE(unsigned long int, 6);
    DUMP_POINTER_TYPE_VALUE(long long int, 7);
    DUMP_POINTER_TYPE_VALUE(unsigned long long int, 8);
    
    // Boolean type
    DUMP_POINTER_TYPE_VALUE(bool, 9);
    
    // Character types
    DUMP_POINTER_TYPE_VALUE(signed char, 10);
    DUMP_POINTER_TYPE_VALUE(unsigned char, 11);
    DUMP_POINTER_TYPE_VALUE(char, 12);
    DUMP_POINTER_TYPE_VALUE(wchar_t, 13);
    DUMP_POINTER_TYPE_VALUE(char16_t, 14);
    DUMP_POINTER_TYPE_VALUE(char32_t, 15);
    
    // Floating-point types
    DUMP_POINTER_TYPE_VALUE(float, 16);
    DUMP_POINTER_TYPE_VALUE(double, 17);
    DUMP_POINTER_TYPE_VALUE(long double, 18);
    
    #define DUMP_CONST_POINTER_TYPE_VALUE(TYPE, VALUE) ss << formLabel( "const " #TYPE "*" ) << doctest::toString( reinterpret_cast<const TYPE*>(VALUE) ) << '\n' // NOLINT
    
    // Signed and unsigned integer types
    DUMP_CONST_POINTER_TYPE_VALUE(short int, 0);
    DUMP_CONST_POINTER_TYPE_VALUE(unsigned short int, 2);
    DUMP_CONST_POINTER_TYPE_VALUE(int, 3);
    DUMP_CONST_POINTER_TYPE_VALUE(unsigned int, 4);
    DUMP_CONST_POINTER_TYPE_VALUE(long int, 5);
    DUMP_CONST_POINTER_TYPE_VALUE(unsigned long int, 6);
    DUMP_CONST_POINTER_TYPE_VALUE(long long int, 7);
    DUMP_CONST_POINTER_TYPE_VALUE(unsigned long long int, 8);
    
    // Boolean type
    DUMP_CONST_POINTER_TYPE_VALUE(bool, 9);
    
    // Character types
    DUMP_CONST_POINTER_TYPE_VALUE(signed char, 10);
    DUMP_CONST_POINTER_TYPE_VALUE(unsigned char, 11);
    DUMP_CONST_POINTER_TYPE_VALUE(char, 12);
    DUMP_CONST_POINTER_TYPE_VALUE(wchar_t, 13);
    DUMP_CONST_POINTER_TYPE_VALUE(char16_t, 14);
    DUMP_CONST_POINTER_TYPE_VALUE(char32_t, 15);
    
    // Floating-point types
    DUMP_CONST_POINTER_TYPE_VALUE(float, 16);
    DUMP_CONST_POINTER_TYPE_VALUE(double, 17);
    DUMP_CONST_POINTER_TYPE_VALUE(long double, 18);
    
    ss << "С arrays:\n";
    
    {
        const char cArray[] = {'f', 'o', 'o'};
        ss << formLabel( "const char[]" ) << doctest::toString( cArray ) << '\n';
    }
    
    {
        char cArray[] = {'b', 'a', 'r'};
        ss << formLabel( "char[]" ) << doctest::toString( cArray ) << '\n';
    }
    
    {
        const int cArray[] = {1, 2, 3};
        ss << formLabel( "const int[]" ) << doctest::toString( cArray ) << '\n';
    }
    
    {
        int cArray[] = {4, 5, 6};
        ss << formLabel( "int[]" ) << doctest::toString( cArray ) << '\n';
    }
    
    ss << "enumerations:\n";
    DUMP_TYPE_VALUE(Enum, Enum::E_VALUE);
    DUMP_TYPE_VALUE(EnumWithOss, EnumWithOss::E_VALUE_WITH_OSS);
    DUMP_TYPE_VALUE(EnumClass, EnumClass::VALUE);
    DUMP_TYPE_VALUE(EnumClassWithOss, EnumClassWithOss::A);
    
    ss << "structs:\n";
    
    {
        Struct s;
        ss << formLabel( "struct" ) << doctest::toString( s ) << '\n';
    }
    
    {
        StructOss s {};
        s.value = 777;
        ss << formLabel( "struct with oss" ) << doctest::toString( s ) << '\n';
    }

    ss << "std container and classes (c++11):\n";

    {
        const std::string value = "Hello world!";
        ss << formLabel( "std::string" ) << doctest::toString( value ) << '\n';
    }

    {
        std::pair<int, float> value { 1, 2.3f };
        ss << formLabel( "std::pair" ) << doctest::toString( value ) << '\n';
    }

    {
        std::tuple<bool, int, double> value { false, 7, 6.6 };
        ss << formLabel( "std::tuple" ) << doctest::toString( value ) << '\n';
    }

    {
        std::array<int, 3> value { 1, 5, 8 };
        ss << formLabel( "std::array" ) << doctest::toString( value ) << '\n';
    }

    {
        std::valarray<int> value { 7, 3, 2 };
        ss << formLabel( "std::valarray" ) << doctest::toString( value ) << '\n';
    }

    {
        std::initializer_list<int> value { 1, 7, 0 };
        ss << formLabel( "std::initializer_list" ) << doctest::toString( value ) << '\n';
    }

    {
        std::vector<int> value { 4, 2, 7 };
        ss << formLabel( "std::vector" ) << doctest::toString( value ) << '\n';
    }

    {
        std::deque<int> value { 1, 1, 6, 2 };
        ss << formLabel( "std::deque" ) << doctest::toString( value ) << '\n';
    }

    {
        std::list<int> value { 7, 5, 2, 1 };
        ss << formLabel( "std::list" ) << doctest::toString( value ) << '\n';
    }

    {
        std::forward_list<int> value { 7, 0, 3, 7, 4 };
        ss << formLabel( "std::forward_list" ) << doctest::toString( value ) << '\n';
    }

    {
        std::stack<int> value {{ 1, 2, 3, 4, 5 }};
        ss << formLabel( "std::stack" ) << doctest::toString( value ) << '\n';
    }

    {
        std::queue<int> value {{ 1, 2, 3, 4, 5 }};
        ss << formLabel( "std::queue" ) << doctest::toString( value ) << '\n';
    }

    {
        const auto data = { 1, 8, 5, 6, 3 };

        std::priority_queue<int> value { data.begin(), data.end() };
        ss << formLabel( "std::priority_queue" ) << doctest::toString( value ) << '\n';
    }
    
    {
        std::set<int> value {{ 1, 2, 2, 6, 1, 4 }};
        ss << formLabel( "std::set" ) << doctest::toString( value ) << '\n';
    }
    
    {
        std::multiset<int> value {{ 1, 2, 2, 6, 1, 4 }};
        ss << formLabel( "std::multiset" ) << doctest::toString( value ) << '\n';
    }
    
    {
        std::map<int, std::string> value {{ { 1, "foo" }, { 2, "bar" }, { 1, "baz" } }};
        ss << formLabel( "std::map" ) << doctest::toString( value ) << '\n';
    }
    
    {
        std::multimap<int, std::string> value {{ { 1, "foo" }, { 2, "bar" }, { 1, "baz" } }};
        ss << formLabel( "std::multimap" ) << doctest::toString( value ) << '\n';
    }

#if CXX_STANDARD >= 14
    ss << "std container and classes (c++14):\n";

    {
        std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6> value {};
        ss << formLabel( "std::integer_sequence" ) << doctest::toString( value ) << '\n';
    }
#endif

#if CXX_STANDARD >= 17
    ss << "std container and classes (c++17):\n";
    
    {
        const std::string s = "Hello world!";
        std::string_view value{ s };
        value = value.substr( 0, 5 );
        ss << formLabel( "std::string_view" ) << doctest::toString( value ) << '\n';
    }
    
    {
        ss << formLabel( "std::nullopt" ) << doctest::toString( std::nullopt ) << '\n';
        std::optional<int> value {};
        ss << formLabel( "std::optional(nullopt)" ) << doctest::toString( value ) << '\n';
        value = 9;
        ss << formLabel( "std::optional" ) << doctest::toString( value ) << '\n';
    }

    {
        std::variant<std::monostate, int, float> value {};
        ss << formLabel( "std::variant(monostate)" ) << doctest::toString( value ) << '\n';
        value = 5;
        ss << formLabel( "std::variant(int)" ) << doctest::toString( value ) << '\n';
        value = 9.2f;
        ss << formLabel( "std::variant(float)" ) << doctest::toString( value ) << '\n';
    }
#endif

#if CXX_STANDARD >= 20
    ss << "std container and classes (c++20):\n";
    
    {
        std::array<int, 3> ar { 9, 1, 5 };
        std::span<int> value { ar };
        ss << formLabel( "std::span" ) << doctest::toString( value ) << '\n';
    }
#endif
    
    
    Approvals::verify(ss.str());
}
