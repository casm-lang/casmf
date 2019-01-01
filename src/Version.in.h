//
//  Copyright (C) 2017-2019 CASM Organization <https://casm-lang.org>
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

#ifndef _CASMF_VERSION_H_
#define _CASMF_VERSION_H_

#include <string>

/**
   @brief    TODO

   TODO

   variables are automatically set by CMake
*/

namespace casmf
{
    const std::string DESCRIPTION =
        "Corinthian Abstract State Machine (CASM) Code Format and Beautifier\n";
    const std::string PROFILE = "format";
    constexpr const char* REVTAG = "@GIT_REVTAG@";
    constexpr const char* COMMIT = "@GIT_COMMIT@";
    constexpr const char* BRANCH = "@GIT_BRANCH@";
    constexpr const char* LICENSE = "@GIT_LICENSE@";
    constexpr const char* NOTICE = "@GIT_NOTICE@";
}

#endif  // _CASMF_VERSION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
