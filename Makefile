# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld

all:
	@echo "Try 'make format'!"

.PHONY: format
format:
	clang-format -i $$(find -name *.c -o -name *.cpp)

README.html: README.md
	pandoc -i $< -o $@ -f markdown -t html -s
