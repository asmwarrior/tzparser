
NAME		=	tzparse

SRC		=	TzParseDefaultRules.cpp		\
			TzParseGroup.cpp		\
			TzParseRule.cpp			\
			TzParseValue.cpp		\
			TzParser.cpp			\
			TzParserIgnore.cpp		\

OBJ		=	$(SRC:.cpp=.o)

SONAME		=	lib$(NAME).so

CXX		=	g++

CXXFLAGS	=	-I. -Iheaders -Iheaders/tzParse -fPIC -DUNIX -W -Wall

RM		=	rm -f

JUNK		=	*~ \\\#*\\\#  headers/*~ headers/\\\#*\\\#

MV		=	mv

$(NAME)	: $(OBJ)
	$(CXX) -shared -W1,-soname,$(SONAME) -o $(SONAME) $(OBJ) $(LDFLAGS)
	$(MV) $(SONAME) ../Unix

clean	:
	$(RM) $(JUNK)
	$(RM) $(OBJ)

fclean	: clean
	$(RM) ../Unix/$(SONAME)

all	: $(NAME)

re	: clean all
