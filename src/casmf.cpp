//
//  Copyright (C) 2017-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                <https://github.com/casm-lang/casmf>
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

#include <casmf/Version>

#include <libcasm-fe/libcasm-fe>
#include <libcasm-ir/libcasm-ir>
#include <libpass/libpass>
#include <libstdhl/libstdhl>

/**
    @brief TODO

    TODO
*/

int main( int argc, const char* argv[] )
{
    assert( argc > 0 );
    const std::string app_name = argv[ 0 ];

    libpass::PassManager pm;
    libstdhl::Logger log( pm.stream() );
    log.setSource(
        libstdhl::Memory::make< libstdhl::Log::Source >( app_name, casmf::DESCRIPTION ) );

    auto flush = [&pm, &app_name]() {
        libstdhl::Log::ApplicationFormatter f( app_name );
        libstdhl::Log::OutputStreamSink c( std::cerr, f );
        pm.stream().flush( c );
    };

    std::vector< std::string > files;

    libstdhl::Args options( argc, argv, libstdhl::Args::DEFAULT, [&files, &log]( const char* arg ) {
        if( files.size() > 0 )
        {
            log.error(
                "too many files, input file '" + files.front() +
                "' cannot be combined with file '" + arg + "'" );
            return 1;
        }

        files.emplace_back( arg );
        return 0;
    } );

    options.add(
        't',
        "test-case-profile",
        libstdhl::Args::NONE,
        "display the unique test profile identifier",
        []( const char* ) {
            std::cout << casmf::PROFILE << "\n";
            return -1;
        } );

    options.add(
        'h',
        "help",
        libstdhl::Args::NONE,
        "display usage and synopsis",
        [&log, &options]( const char* ) {
            log.output(
                "\n" + casmf::DESCRIPTION + "\n" + log.source()->name() +
                ": usage: [options] <file>\n" + "\n" + "options: \n" + options.usage() + "\n" );

            return -1;
        } );

    options.add(
        'v', "version", libstdhl::Args::NONE, "display version information", [&log]( const char* ) {
            log.output(
                "\n" + casmf::DESCRIPTION + "\n" + log.source()->name() + ": version: " +
                casmf::REVTAG + " [ " + __DATE__ + " " + __TIME__ + " ]\n" + "\n" + casmf::NOTICE );

            return -1;
        } );

    // add passes to the pass manager to setup command-line options

    pm.add< libcasm_fe::AstDumpSourcePass >();

    for( auto id : pm.passes() )
    {
        libpass::PassInfo& pi = libpass::PassRegistry::passInfo( id );

        if( pi.argChar() or pi.argString() )
        {
            options.add(
                pi.argChar(),
                pi.argString(),
                libstdhl::Args::NONE,
                pi.description(),
                pi.argAction() );
        }
    }

    // parse the command-line

    if( auto ret = options.parse( log ) )
    {
        flush();

        if( ret >= 0 )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if( files.size() == 0 )
    {
        log.error( "no input file provided" );
        flush();
        return 2;
    }

    // set default settings

    libpass::PassResult pr;
    pr.setInput< libpass::LoadFilePass >( files.front() );

    pm.setDefaultResult( pr );
    pm.setDefaultPass< libcasm_fe::AstDumpSourcePass >();

    // set pass-specific configurations

    // pm.set< libcasm_fe::TODO >( [&]( libcasm_fe::TODO& pass ) {
    //     pass.setTODO( TODO );

    // } );

    // run pass pipeline

    if( not pm.run( flush ) )
    {
        return -1;
    }

    flush();
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
