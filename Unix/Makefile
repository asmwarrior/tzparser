
NAME	=	tzparser


## Directories

DIR_SRC	=	../src

DIR_TZP	=	../tzParse

DIR_TIX	=	../src/tinyxml

DIR_PRJ	=	..


## Sources

SRC_SRC	=	$(DIR_SRC)/BNFRules.cpp			\
		$(DIR_SRC)/main.cpp			\
		$(DIR_SRC)/TzTiXMLPrinter.cpp

SRC_TZP	=	$(DIR_TZP)/TzParseDefaultRules.cpp	\
		$(DIR_TZP)/TzParseGroup.cpp		\
		$(DIR_TZP)/TzParser.cpp			\
		$(DIR_TZP)/TzParserIgnore.cpp		\
		$(DIR_TZP)/TzParseRule.cpp		\
		$(DIR_TZP)/TzParseValue.cpp

SRC_TIX	=	$(DIR_TIX)/tinystr.cpp			\
		$(DIR_TIX)/tinyxml.cpp			\
		$(DIR_TIX)/tinyxmlerror.cpp		\
		$(DIR_TIX)/tinyxmlparser.cpp

ALL_SRC	=	$(SRC_SRC) $(SRC_TZP) $(SRC_TIX)


## Objects

OBJ_SRC	=	$(SRC_SRC:.cpp=.o)

OBJ_TZP	=	$(SRC_TZP:.cpp=.o)

OBJ_TIX	=	$(SRC_TIX:.cpp=.o)

ALL_OBJ	=	$(OBJ_SRC) $(OBJ_TZP) $(OBJ_TIX)


## Commands and vars

CC	=	g++

RM	=	rm -f

JUNK	=	*~ \#*\#


## Flags

CFLAGS	+=	-I$(DIR_PRJ) -I$(DIR_SRC)


## Compilation rules

$(NAME)	: $(ALL_OBJ)
	$(CC) -o $(NAME) *.o

.cpp.o	:
	$(CC) $(CFLAGS) -c $< -o `basename $@`

clean	:
	$(RM) $(JUNK)
	$(RM) $(DIR_SRC)/$(JUNK)
	$(RM) $(DIR_TZP)/$(JUNK)
	$(RM) $(DIR_TIX)/$(JUNK)
	$(RM) *.o

fclean	: clean
	$(RM) $(NAME)

all	: $(NAME)

re	: clean all

compil	: all clean


## Installation rules /!\ : Need to be root !

install		:
	cp tzparser /usr/bin/

uninstall	:
	rm -f /usr/bin/tzparser

autoinstall	: all install fclean
