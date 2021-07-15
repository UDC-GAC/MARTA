BINARY_NAME=micro_codelet
MAIN_SRC=main
MAIN_SUFFIX=.c
TARGET=micro_codelet
INLINE=_inline

include ../MakeFlags.mk

.PHONY: inline_codelet 

inline_codelet:
	python3 inline_codelets.py '$(COMMON_FLAGS)'