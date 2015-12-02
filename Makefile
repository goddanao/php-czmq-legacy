NAME				=	php-czmq
INI_DIR				=	/etc/php5/mods-available
EXTENSION_DIR		=	$(shell php-config --extension-dir)
CLIB_PATH           =   $(shell cat /etc/ld.so.conf.d/libc.conf | grep /usr)
EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini
COMPILER			=	g++
LINKER				=	g++
COMPILER_FLAGS		=	`php-config --includes` -w -c -O2 -g -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared

RM					=	rm -f
CP					=	cp -f
MKDIR				=	mkdir -p

SOURCES				=	$(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -L${CLIB_PATH} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}


install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
				
clean:
						${RM} ${EXTENSION} ${OBJECTS}
