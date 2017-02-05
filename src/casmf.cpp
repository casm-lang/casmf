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

#include "libpass.h"
#include "libstdhl.h"

#include "libcasm-fe.h"
#include "libcasm-ir.h"
#include "libcasm-tc.h"

/**
    @brief TODO

    TODO
*/

int main( int argc, const char* argv[] )
{
    const char* file_name = 0;
    u1 flag_dump_updates = false;

    libstdhl::Log::DefaultSource = libstdhl::Log::Source(
        [&argv]( void* args ) -> const char* { return argv[ 0 ]; } );

    libstdhl::Args options( argc, argv, libstdhl::Args::DEFAULT,
        [&file_name, &options]( const char* arg ) {
            static int cnt = 0;
            cnt++;

            if( cnt > 1 )
            {
                options.m_error( 1, "to many file names passed" );
            }

            file_name = arg;
        } );

// options.add( 't', "test-case-profile", libstdhl::Args::NONE,
//     "Display the unique test profile identifier and exit.",
//     [&options]( const char* option ) {
//         printf( "%s\n",
//             libcasm_tc::Profile::get( libcasm_tc::Profile::INTERPRETER ) );
//         exit( 0 );
//     } );

#define DESCRIPTION                                                            \
    "Corinthian Abstract State Machine (CASM) Format and Beautifier\n"

    options.add( 'h', "help", libstdhl::Args::NONE,
        "Display the program usage and synopsis and exit.",
        [&options]( const char* option ) {
            fprintf( stderr, DESCRIPTION
                "\n"
                "usage: %s [options] <file>\n"
                "\n"
                "options:\n",
                options.programName() );

            options.m_usage();

            exit( 0 );
        } );

    options.add( 'v', "version", libstdhl::Args::NONE,
        "Display interpreter version information",
        [&options]( const char* option ) {
            fprintf( stderr, DESCRIPTION
                "\n"
                "%s: version: %s [ %s %s ]\n"
                "\n"
                "%s\n",
                options.programName(), VERSION, __DATE__, __TIME__,
                LICENSE );

            exit( 0 );
        } );

    // for( auto& p : libpass::PassRegistry::getRegisteredPasses() )
    // {
    //     // PassId    id = p.first;
    //     libpass::PassInfo& pi = *p.second;

    //     if( pi.passArgChar() == 0 && pi.passArgString() == 0 )
    //     {
    //         // internal pass, do not register a cmd line flag
    //         continue;
    //     }

    //     options.add( pi.passArgChar(), pi.passArgString(),
    //     libstdhl::Args::NONE,
    //         pi.passDescription(), pi.passArgAction() );
    // }

    options.parse();

    if( !file_name )
    {
        options.m_error( 1, "no input file provided" );
    }

    // TODO: FIXME: the following code should be implemented in the PassManager
    // structure
    // to allow dynamic and possible pass calls etc.

    libpass::PassResult x;

    x.results()[ (void*)2 ]
        = (void*)flag_dump_updates; // TODO: PPA: this will be removed and
                                    // changed to a pass setter option

    auto load_file_pass = std::dynamic_pointer_cast< libpass::LoadFilePass >(
        libpass::PassRegistry::passInfo< libpass::LoadFilePass >()
            .constructPass() );
    load_file_pass->setFileName( file_name );
    if( not load_file_pass->run( x ) )
    {
        return -1;
    }

    libpass::PassInfo ast_parse
        = libpass::PassRegistry::passInfo< libcasm_fe::SourceToAstPass >();
    if( ast_parse.constructPass()->run( x ) )
    {
        if( ast_parse.isArgSelected() )
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }

    libpass::PassInfo ast_check
        = libpass::PassRegistry::passInfo< libcasm_fe::TypeCheckPass >();
    if( ast_check.constructPass()->run( x ) )
    {
        if( ast_check.isArgSelected() )
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
