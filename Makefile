#
#   Copyright (C) 2017-2018 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber
#                 Emmanuel Pescosta
#                 <https://github.com/casm-lang/casmf>
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

TARGET = casmf

FORMAT  = src
FORMAT += src/*
FORMAT += src/*/*
FORMAT += etc
FORMAT += etc/*
FORMAT += etc/*/*

UPDATE_ROOT = ../../lib/stdhl

include .cmake/config.mk

ENV_FLAGS = CASM=$(OBJ)/$(TARGET) CASM_ARG_PRE=--ast-exec-num


license: $(OBJ)/src/license.h
$(OBJ)/src/license.h: $(OBJ) LICENSE.txt
	@echo "const char LICENSE[] =" > $@
	@head -n `grep -ne "------" LICENSE.txt | grep -Eo "[0-9]*"` LICENSE.txt | \
		sed "/-----/d" | \
		sed "/This file is part of/d" | \
		sed "s/^/    /" | \
		sed "s/^/\"/g" | \
		sed "s/$$/\\\n\"/g" >> $@
	@echo ";" >> $@
