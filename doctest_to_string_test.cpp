#include "doctest/doctest.h"
#include "ApprovalTests.hpp"
#include <sstream>

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
    
    Approvals::verify(ss.str());
}
