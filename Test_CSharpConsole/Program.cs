﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test_CSharpConsole
{
    public static class Program
    {
        static void Main( string[] args )
        {
            //fb.writes( 123, 1.23f, 1.23, "asdfqwerzxcv1234", (byte)123, true );



            var s = "asdfqwerzxcv1234";
            var ms = new MemoryStream();

            var sw = new Stopwatch();
            sw.Start();
            for( int i = 0; i < 9999999; i++ )
            {
                //ms = new MemoryStream();
                var buf = BitConverter.GetBytes( 123 );
                ms.Write( buf, 0, buf.Length );
                buf = BitConverter.GetBytes( 1.23f );
                ms.Write( buf, 0, buf.Length );
                buf = BitConverter.GetBytes( 1.23 );
                ms.Write( buf, 0, buf.Length );
                buf = BitConverter.GetBytes( s.Length );
                ms.Write( buf, 0, buf.Length );
                buf = Encoding.UTF8.GetBytes( s );
                ms.Write( buf, 0, buf.Length );
                ms.WriteByte( 123 );
                ms.WriteByte( true ? (byte)1 : (byte)0 );
            }
            Console.WriteLine( sw.ElapsedMilliseconds );
            var buff = ms.ToArray();
            //foreach( var b in buff ) Console.Write( b.ToString( "x2" ) + " " );






            var llls = new List<List<List<string>>>();
            var lls = new List<List<String>>();
            var ls = new List<String>();
            ls.Add( "ooooo" );
            ls.Add( "xxxxx" );
            lls.Add( ls );
            lls.Add( ls );
            llls.Add( lls );
            llls.Add( lls );


        }
    }
}
