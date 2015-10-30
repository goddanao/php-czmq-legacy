NAME				=	php-czmq
INI_DIR				=	/etc/php5/mods-available
EXTENSION_DIR		=	$(shell php-config --extension-dir)
LIBS_DIR			=   /usr/local/lib
EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini
COMPILER			=	g++
LINKER				=	g++
COMPILER_FLAGS		=	-w -c -O2 -g -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared
LINKER_DEPENDENCIES	=	-lphpcpp -lzmq -lczmq -lzyre -lmlm

RM					=	rm -f
CP					=	cp -f
MKDIR				=	mkdir -p

SOURCES				=	$(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -L${LIBS_DIR} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}


install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
				
clean:
						${RM} ${EXTENSION} ${OBJECTS}
