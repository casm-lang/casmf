//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/casm-lang/casmf
//
//  This file is part of casmf.
//
//  casmf is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  casmf is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with casmf. If not, see <http://www.gnu.org/licenses/>.
//

#include "license.h"
#include "version.h"

#include "cpp/Args.h"
#include "cpp/Default.h"

#include "libcasm-fe.all.h"
#include "libcasm-ir.all.h"
#include "libcasm-tc.h"
#include "libpass.h"

/**
    @brief TODO

    TODO
*/

int main( int argc, const char* argv[] )
{
    const char* file_name = 0;
    u1 flag_dump_updates = false;

    Args options(
        argc, argv, Args::DEFAULT, [&file_name, &options]( const char* arg ) {
            static int cnt = 0;
            cnt++;

            if( cnt > 1 )
            {
                options.error( 1, "to many file names passed" );
            }

            file_name = arg;
        } );

// options.add( 't', "test-case-profile", Args::NONE,
//     "Display the unique test profile identifier and exit.",
//     [&options]( const char* option ) {
//         printf( "%s\n",
//             libcasm_tc::Profile::get( libcasm_tc::Profile::INTERPRETER ) );
//         exit( 0 );
//     } );

#define DESCRIPTION                                                            \
    "Corinthian Abstract State Machine (CASM) Format and Beautifier\n"

    options.add( 'h', "help", Args::NONE,
        "Display the program usage and synopsis and exit.",
        [&options]( const char* option ) {
            fprintf( stderr, DESCRIPTION
                "\n"
                "usage: %s [options] <file>\n"
                "\n"
                "options:\n",
                options.getProgramName() );

            options.usage();

            exit( 0 );
        } );

    options.add( 'v', "version", Args::NONE,
        "Display interpreter version information",
        [&options]( const char* option ) {
            fprintf( stderr, DESCRIPTION
                "\n"
                "%s: version: %s [ %s %s ]\n"
                "\n"
                "%s\n",
                options.getProgramName(), VERSION, __DATE__, __TIME__,
                LICENSE );

            exit( 0 );
        } );

    // for( auto& p : libpass::PassRegistry::getRegisteredPasses() )
    // {
    //     // PassId    id = p.first;
    //     libpass::PassInfo& pi = *p.second;

    //     if( pi.getPassArgChar() == 0 && pi.getPassArgString() == 0 )
    //     {
    //         // internal pass, do not register a cmd line flag
    //         continue;
    //     }

    //     options.add( pi.getPassArgChar(), pi.getPassArgString(), Args::NONE,
    //         pi.getPassDescription(), pi.getPassArgAction() );
    // }

    options.parse();

    if( !file_name )
    {
        options.error( 1, "no input file provided" );
    }

    // TODO: FIXME: the following code should be implemented in the PassManager
    // structure
    // to allow dynamic and possible pass calls etc.

    libpass::PassResult x;
    x.getResults()[ 0 ] = (void*)file_name;
    x.getResults()[ (void*)2 ]
        = (void*)flag_dump_updates; // TODO: PPA: this will be removed and
                                    // changed to a pass setter option

    libpass::PassInfo ast_parse
        = libpass::PassRegistry::getPassInfo< libcasm_fe::SourceToAstPass >();
    if( ast_parse.constructPass()->run( x ) )
    {
        if( ast_parse.isPassArgSelected() )
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }

    libpass::PassInfo ast_check
        = libpass::PassRegistry::getPassInfo< libcasm_fe::TypeCheckPass >();
    if( ast_check.constructPass()->run( x ) )
    {
        if( ast_check.isPassArgSelected() )
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
