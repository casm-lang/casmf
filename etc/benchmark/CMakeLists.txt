#
#   Copyright (C) 2017-2024 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#   <https://github.com/casm-lang/casmf/graphs/contributors>
#
#   This file is part of casmf.
#
#   casmf is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   casmf is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with casmf. If not, see <http://www.gnu.org/licenses/>.
#

include_directories(
  ${PROJECT_BINARY_DIR}/src
  ${LIBHAYAI_INCLUDE_DIR}
  ${LIBSTDHL_INCLUDE_DIR}
  ${LIBPASS_INCLUDE_DIR}
  )

add_library( ${PROJECT}-benchmark OBJECT
  main.cpp
  )
