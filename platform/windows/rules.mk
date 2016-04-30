sfml_LOCAL_PATH := $(call whereami)

SRCS_C += $(wildcard $(sfml_LOCAL_PATH)/platform/*.c)
SRCS_CPP += $(wildcard $(sfml_LOCAL_PATH)/*.cpp)
INCLUDE += $(sfml_LOCAL_PATH)/public /usr/include

LIBS += -lstdc++ -lsfml-window -lsfml-graphics -lsfml-system
#LDFLAGS += -fuse-ld=gold

CFLAGS_COMMON += -DTARGET_SFML=1 -DWRPG_EXCEPTIONS=1
CC = gcc
CPP = g++

EXE = $(OUT)/$(NAME).exe

$(EXE): $(ELF)
	@cp $(ELF) $(EXE)

run: all
	./$(EXE)