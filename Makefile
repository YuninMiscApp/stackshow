
.PHONY: all source clean

ifdef language
  ifeq ("$(origin language)", "command line")
    KBUILD_LANGUAGE = $(language)
  endif
endif

#****************************************************************************
# output files
#****************************************************************************
OUTPUT_DYNAMIC_LIB ?= libstackshow.so
OUTPUT_STATIC_LIB ?= libstackshow.a

ifeq ($(KBUILD_LANGUAGE),c++)
OUTPUT_BIN ?= ${CURDIR}/tests/stack_show_test_cpp
else
OUTPUT_BIN ?= ${CURDIR}/tests/stack_show_test_c
endif


#****************************************************************************
# environment variable
#****************************************************************************
#CURDIR := $(shell pwd)

#****************************************************************************
# standard CFLAGS
#****************************************************************************
CFLAGS = -fPIC -Wall -rdynamic

ifdef CONFIG_CPP
CFLAGS := $(CFLAGS) -x c++
endif

#
ifeq (YES, ${NV_DEBUG})
LDFLAGS := -shared -g
else
LDFLAGS := -shared
endif





#

NV_CROSS_COMPILE ?=arm-hisiv400-linux-

ifeq ($(KBUILD_LANGUAGE),c++)
	export CC:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)g++,g++)
else
	export CC:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)gcc,gcc)
endif

export CXX:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)g++,g++)
export LD:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)ld,ld)
export AR:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)ar,ar)
export TP:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)strip,strip)
export RANLIB:=$(if $(strip $(NV_CROSS_COMPILE)),$(NV_CROSS_COMPILE)ranlib,ranlib)


#


#****************************************************************************
# Source files
#****************************************************************************
BIN_SRCDIRS := $(shell find ./backtrace -maxdepth 1 -type d ! -name '.git' -a ! -name 'build' -a ! -name 'deps' -a ! -name 'patches')
BIN_SRCS :=  $(foreach dir,$(BIN_SRCDIRS),$(wildcard $(dir)/*.cpp))\
			$(foreach dir,$(BIN_SRCDIRS),$(wildcard $(dir)/*.c))
BIN_OBJS := $(patsubst %.c, %.o, $(BIN_SRCS)) 


#output
ifeq ($(KBUILD_LANGUAGE),c++)
OUTPUT_OBJS := ${CURDIR}/tests/main.cpp
else
OUTPUT_OBJS := ${CURDIR}/tests/main.c
endif



#libs
LIBS ?=


#****************************************************************************
# target
#****************************************************************************
all: $(LIBS) $(BIN_OBJS)
	${CC} ${LDFLAGS}  -o ${OUTPUT_DYNAMIC_LIB} $(LIBS) $(BIN_OBJS) -ldl
	$(AR) rs ${OUTPUT_STATIC_LIB} $(BIN_OBJS) 
	

#****************************************************************************
# misc command
#****************************************************************************
source:
	@echo "Source files: "
	@echo $(BIN_SRCDIRS)
	@echo $(BIN_SRCS)
	@echo $(BIN_OBJS)

test:
	${CC} -Wall -rdynamic -o $(OUTPUT_BIN) $(OUTPUT_OBJS) -L$(CURDIR) -lstackshow


environment:
	@echo "[current directory]: " ${CURDIR}
	@echo "[output bin]:" ${OUTPUT_BIN}

#****************************************************************************
# Compile rules
#****************************************************************************
./%.o : ./%c
	$(CC) ${CFLAGS} -c $< -o $@	



#****************************************************************************
# clean rules
#****************************************************************************
clean:
	rm -f $(BIN_OBJS) 
	rm -f ${OUTPUT_BIN}*
	rm -f $(OUTPUT_DYNAMIC_LIB)
	rm -f ${OUTPUT_STATIC_LIB}
	rm -f *.bak


