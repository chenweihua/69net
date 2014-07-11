#include "All.h"
#include "ftoa.c"

namespace Utils
{

    // 取 整数 转换后的 string 长度系列
    // todo: if ( n < ...... ) 这种代码理论上讲可以优化成树形, 类似折半查找从而减少 if 次数

    int getToStringSize( uint8 v )
    {
        if( v < 10 ) return 1;
        else if( v < 100 ) return 2;
        else return 3;
    }

    int getToStringSize( uint16 v )
    {
        if( v < 10 ) return 1;
        else if( v < 100 ) return 2;
        else if( v < 1000 ) return 3;
        else if( v < 10000 ) return 4;
        else return 5;
    }

    int getToStringSize( uint32 v )
    {
        if( v < 10 ) return 1;
        else if( v < 100 ) return 2;
        else if( v < 1000 ) return 3;
        else if( v < 10000 ) return 4;
        else if( v < 100000 ) return 5;
        else if( v < 1000000 ) return 6;
        else if( v < 10000000 ) return 7;
        else if( v < 100000000 ) return 8;
        else if( v < 1000000000 ) return 9;
        else return 10;
    }

    int getToStringSize( uint64 v )
    {
        if( v < 10000000000LL ) return getToStringSize( (uint32)v );
        else if( v < 100000000000LL ) return 11;
        else if( v < 1000000000000LL ) return 12;
        else if( v < 10000000000000LL ) return 13;
        else if( v < 100000000000000LL ) return 14;
        else if( v < 1000000000000000LL ) return 15;
        else if( v < 10000000000000000LL ) return 16;
        else if( v < 100000000000000000LL ) return 17;
        else if( v < 1000000000000000000LL ) return 18;
        else if( v < (uint64)( (uint64)1000000000000000000LL * (uint64)10 ) ) return 19;
        else return 20;
    }


    int toStringCore( uint8 in, char *out )
    {
        if( in == 0 )
        {
            out[ 0 ] = '0';
            return 1;
        }

        int idx, len;
        idx = len = getToStringSize( in );
        size_t v = in, tmp;
        do
        {
#if __X64
            tmp = ( v * 1717986919 ) >> 34;			// v / 10 的高效率版
#else
            tmp = v / 10;
#endif
            out[ --idx ] = (char)( 48 + v - tmp * 10 );
        } while( ( v = tmp ) );
        return len;
    }


    int toStringCore( uint16 in, char *out )
    {
        if( in == 0 )
        {
            out[ 0 ] = '0';
            return 1;
        }

        int idx, len;
        idx = len = getToStringSize( in );
        size_t v = in, tmp;
        do
        {
#if __X64
            tmp = ( v * 1717986919 ) >> 34;			// v / 10 的高效率版
#else
            tmp = v / 10;
#endif
            out[ --idx ] = (char)( 48 + v - tmp * 10 );
        } while( ( v = tmp ) );
        return len;
    }



    int toStringCore( uint32 in, char *out )
    {
        if( in == 0 )
        {
            out[ 0 ] = '0';
            return 1;
        }

        int idx, len;
        idx = len = getToStringSize( in );
        size_t v = in, tmp;
        do
        {
#if __X64
            tmp = ( v * 1717986919 ) >> 34;			// v / 10 的高效率版
#else
            tmp = v / 10;
#endif
            out[ --idx ] = (char)( 48 + v - tmp * 10 );
        } while( ( v = tmp ) );
        return len;
    }


    int toStringCore( uint64 in, char * out )
    {
        if( in == 0 )
        {
            out[ 0 ] = '0';
            return 1;
        }
        if( in <= 0xFFFFFFFFLL ) return toStringCore( (uint32)in, out );
        int len, idx;
        idx = len = getToStringSize( in );
        size_t v = (size_t)in, tmp;
        do
        {
            tmp = v / 10;
            out[ --idx ] = (char)( 48 + v - tmp * 10 );
        } while( ( v = tmp ) );
        return len;
    }


    int toStringCore( int in, char * out )
    {
        if( in < 0 )
        {
            *out = '-';
            return toStringCore( (uint32)-in, out + 1 ) + 1;
        }
        return toStringCore( (uint32)in, out );
    }


    int toStringCore( int64 in, char * out )
    {
        if( in < 0 )
        {
            *out = '-';
            return toStringCore( (uint64)-in, out + 1 ) + 1;
        }
        return toStringCore( (uint64)in, out );
    }


    int toStringCore( bool in, char * out )
    {
        if( in )
        {
            out[ 0 ] = 't';
            out[ 1 ] = 'r';
            out[ 2 ] = 'u';
            out[ 3 ] = 'e';
            return 4;
        }
        else
        {
            out[ 0 ] = 'f';
            out[ 1 ] = 'a';
            out[ 2 ] = 'l';
            out[ 3 ] = 's';
            out[ 4 ] = 'e';
            return 5;
        }
    }

    int toStringCore( double in, char * out, int maxlen, int precision, bool delEndZeros )
    {
        int ret = lftoa( in, out, maxlen, precision );
        if( !delEndZeros ) return ret;
        auto lastPos = out + ret;
        auto dotPos = std::find( out, lastPos, '.' );
        if( dotPos == lastPos ) return ret;
        auto p = lastPos - 1;
        for( ; p > dotPos; --p ) if( *p != '0' ) break;
        ret -= int( lastPos - 1 - p );
        if( out[ ret - 1 ] == '.' ) --ret;
        return ret;
    }

    int toStringCore( float in, char * out, int maxlen, int precision, bool delEndZeros )
    {
        int ret = ftoa( in, out, maxlen, precision );
        if( !delEndZeros ) return ret;
        auto lastPos = out + ret;
        auto dotPos = std::find( out, lastPos, '.' );
        if( dotPos == lastPos ) return ret;
        auto p = lastPos - 1;
        for( ; p > dotPos; --p ) if( *p != '0' ) break;
        ret -= int( lastPos - 1 - p );
        if( out[ ret - 1 ] == '.' ) --ret;
        return ret;
    }

    int toString( char * dstBuf, uint8   v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, uint16  v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, uint    v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, uint64  v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, int8    v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, int16   v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, int     v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, int64   v ) { return toStringCore( v, dstBuf ); }
    int toString( char * dstBuf, double  v, int maxlen, int precision, bool delEndZeros ) { return toStringCore( v, dstBuf, maxlen, precision, delEndZeros ); }
    int toString( char * dstBuf, float   v, int maxlen, int precision, bool delEndZeros ) { return toStringCore( v, dstBuf, maxlen, precision, delEndZeros ); }
    int toString( char * dstBuf, bool    v ) { return toStringCore( v, dstBuf ); }

    int toString( char * dstBuf, char const* v )
    {
        auto len = strlen( v );
        memcpy( dstBuf, v, len );
        return (int)len;
    }

    int toString( char * dstBuf, std::string const & v )
    {
        memcpy( dstBuf, v.c_str(), v.size() );
        return (int)v.size();
    }

    int toString( char * dstBuf, String const & v )
    {
        memcpy( dstBuf, v.c_str(), v.size() );
        return v.size();
    }

    int toString( char * dstBuf, char v )
    {
        *dstBuf = v;
        return 1;
    }










    static char const Int2HexTable[] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'
    };

    int toHexString( char * dstBuf, uint8 v )
    {
        dstBuf[ 0 ] = Int2HexTable[ v >> 4 ];
        dstBuf[ 1 ] = Int2HexTable[ v & 15 ];
        return 2;
    }

    int toHexString( char * dstBuf, uint16 v )
    {
        toHexString( dstBuf, uint8( v >> 8 ) );
        toHexString( dstBuf + 2, (uint8)v );
        return 4;
    }

    int toHexString( char * dstBuf, uint v )
    {
        toHexString( dstBuf, uint16( v >> 16 ) );
        toHexString( dstBuf + 4, (uint16)v );
        return 8;
    }

    int toHexString( char * dstBuf, uint64 v )
    {
        toHexString( dstBuf, uint32( v >> 32 ) );
        toHexString( dstBuf + 8, (uint32)v );
        return 16;
    }


    int toHexString( char * dstBuf, int8 v )
    {
        return toHexString( dstBuf, (uint8)v );
    }

    int toHexString( char * dstBuf, int16 v )
    {
        return toHexString( dstBuf, (uint16)v );
    }

    int toHexString( char * dstBuf, int v )
    {
        return toHexString( dstBuf, (uint32)v );
    }

    int toHexString( char * dstBuf, int64 v )
    {
        return toHexString( dstBuf, (uint64)v );
    }





















    // string 转为各种长度的 有符号整数. Out 取值范围： int8~64
    template <typename OutType>
    void toInt( char const * in, OutType & out )
    {
        auto in_ = in;
        if( *in_ == '0' )
        {
            out = 0;
            return;
        }
        bool b;
        if( *in_ == '-' )
        {
            b = true;
            ++in_;
        }
        else b = false;
        OutType r = *in_ - '0';
        char c;
        while( ( c = *( ++in_ ) ) ) r = r * 10 + ( c - '0' );
        out = b ? -r : r;
    }

    // string (不能有减号打头) 转为各种长度的 无符号整数. Out 取值范围： uint8, uint16, uint32, uint64
    template <typename OutType>
    void toUInt( char const * in, OutType & out )
    {
        assert( in );
        auto in_ = in;
        if( *in_ == '0' )
        {
            out = 0;
            return;
        }
        OutType r = *(in_)-'0';
        char c;
        while( ( c = *( ++in_ ) ) ) r = r * 10 + ( c - '0' );
        out = r;
    }


    void fromStringCore( char const * in, uint8 & out )
    {
        toUInt( in, out );
    }


    void fromStringCore( char const * in, uint16 & out )
    {
        toUInt( in, out );
    }


    void fromStringCore( char const * in, uint32 & out )
    {
        toUInt( in, out );
    }


    void fromStringCore( char const * in, uint64 & out )
    {
        toUInt( in, out );
    }


    void fromStringCore( char const * in, int8 & out )
    {
        toInt( in, out );
    }


    void fromStringCore( char const * in, int16 & out )
    {
        toInt( in, out );
    }


    void fromStringCore( char const * in, int & out )
    {
        toInt( in, out );
    }


    void fromStringCore( char const * in, int64 & out )
    {
        toInt( in, out );
    }

    void fromStringCore( char const * in, double & out )
    {
        out = strtod( in, nullptr );
    }

    void fromStringCore( char const * in, float & out )
    {
        out = (float)strtod( in, nullptr );
    }


    void fromStringCore( char const * in, bool & out )
    {
        out = ( in[ 0 ] == '1' || in[ 0 ] == 'T' || in[ 0 ] == 't' );
    }

    void fromString( uint8   & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( uint16  & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( uint32  & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( uint64  & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( int8    & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( int16   & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( int     & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( int64   & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( double  & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( float   & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }
    void fromString( bool    & dstVar, char const * s ) { return fromStringCore( s, dstVar ); }












    int getHash_CS( byte const* buf, int len )
    {
        assert( (size_t)buf % 4 == 0 );
        if( !len ) return 0;
        int n1 = 0x15051505, n2 = n1, mod = len % 8, i = 0;
        int64 n = 0;
        auto np = (int*)&n;
        for( ; i < len - mod; i += 8 )
        {
            n = *(uint64*)( buf + i );
            n1 = ( ( ( n1 << 5 ) + n1 ) + ( n1 >> 0x1b ) ) ^ np[ 1 ];
            n2 = ( ( ( n2 << 5 ) + n2 ) + ( n2 >> 0x1b ) ) ^ np[ 0 ];
        }
        if( mod )
        {
            auto n = *(uint64*)( buf + i );
            auto np = (int*)&n;
            n &= size_t( 0xFFFFFFFFFFFFFFFF ) >> ( ( 8 - mod ) * 8 );
            n1 = ( ( ( n1 << 5 ) + n1 ) + ( n1 >> 0x1b ) ) ^ np[ 1 ];
            if( np[ 0 ] ) n2 = ( ( ( n2 << 5 ) + n2 ) + ( n2 >> 0x1b ) ) ^ np[ 0 ];
        }
        return n1 + n2 * 0x5d588b65;
    }

    int getHash_Lua( byte const* buf, int len )
    {
        if( !len ) return 0;
        uint seed = 131, hash = 0;
        for( int i = 0; i < len; ++i )
            hash = hash * seed + (uint8)buf[ i ];
        return (int)hash;
    }



    static const int _primes[] =
    {
        1, 2, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287,
        1048573, 2097143, 4194301, 8388593, 16777213, 33554393, 67108859, 134217689, 268435399, 536870909, 1073741789
    };
    int getPrime( int n )
    {
        return _primes[ calc2n( n ) ];
    }










    void binaryDumpCore( String & s, char const * buf, int len )
    {
        for( int i = 0; i < len; ++i )
        {
            uint8 c = buf[ i ];
            if( c < 32 || c > 126 ) s.append( '.' );
            else s.append( (char)c );
        }
    }

    void binaryDump( String & s, char const * buf, int len )
    {
        if( len == 0 ) return;
        s.append( "\n--------  0  1  2  3 | 4  5  6  7 | 8  9  A  B | C  D  E  F" );
        int i = 0;
        for( ; i < len; ++i )
        {
            if( ( i % 16 ) == 0 )
            {
                if( i )
                {           // output ascii to the end of the line
                    s.append( "  " );
                    binaryDumpCore( s, buf + i - 16, 16 );
                }
                s.append( '\n' );
                s.appendHex( i );
                s.append( "  " );
            }
            else if( i && ( i % 4 == 0 ) )
            {
                s.append( "  " );
            }
            else s.append( ' ' );
            s.appendHex( (uint8)buf[ i ] );
        }
        int left = i % 16;
        if( left )
        {
            len = len + 16 - left;
            for( ; i < len; ++i )
            {
                if( i && ( i % 4 == 0 ) )
                    s.append( "  " );
                else s.append( ' ' );
                s.append( "  " );
            }
            s.append( "  " );
            binaryDumpCore( s, buf + i - 16, left );
        }
    }



    void binaryWrite( char* dest, String const& src )
    {
        binaryWrite( dest, src.size() );
        memcpy( dest + sizeof( int ), src.data(), src.size() );
    }

    void binaryWrite( char* dest, FlatBuffer const& src )
    {
        binaryWrite( dest, src.size() );
        memcpy( dest + sizeof( int ), src.data(), src.size() );
    }



    int binaryRead( String& dest, char const* src, int len )
    {
        int destLen;
        if( auto rtv = binaryRead( destLen, src, len ) ) return rtv;
        dest.resize( destLen, false );
        memcpy( dest.data(), src + sizeof( int ), destLen );
        return 0;
    }

    int binaryRead( FlatBuffer& dest, char const* src, int len )
    {
        int destLen;
        if( auto rtv = binaryRead( destLen, src, len ) ) return rtv;
        dest.reserve( destLen );
        memcpy( dest.data(), src + sizeof( int ), destLen );
        dest.widx() = destLen;
        dest.ridx() = 0;
    }

}
