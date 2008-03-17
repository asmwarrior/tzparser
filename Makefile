
NAME	=	TzParser

SRC	=	BNFRules.cpp		\
		TzTiXMLPrinter.cpp	\
		main.cpp

TZPDIR	=	tzParse

TZPSRC	=	$(TZPDIR)/TzParseDefaultRules.cpp	\
		$(TZPDIR)/TzParseGroup.cpp		\
		$(TZPDIR)/TzParseRule.cpp		\
		$(TZPDIR)/TzParseValue.cpp		\
		$(TZPDIR)/TzParser.cpp			\
		$(TZPDIR)/TzParserIgnore.cpp

TIXDIR	=	tinyxml

TIXSRC	=	$(TIXDIR)/tinystr.cpp		\
		$(TIXDIR)/tinyxml.cpp		\
		$(TIXDIR)/tinyxmlerror.cpp	\
		$(TIXDIR)/tinyxmlparser.cpp

OBJ	=	$(SRC:.cpp=.o)
TZPOBJ	=	$(TZPSRC:.cpp=.o)
TIXOBJ	=	$(TIXSRC:.cpp=.o)
ALLOBJ	=	$(OBJ) $(TZPOBJ) $(TIXOBJ)

CPP	=	g++

RM	=	rm -rf

MKDIR	=	mkdir -p

TRASH	=	*~ *\#*\# */*~ */\#*\#

CFLAGS	+=	-I. -ItzParse

$(NAME)	: $(ALLOBJ)
	$(CPP) -o $(NAME) $(ALLOBJ)

.cpp.o	:
	$(CPP) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) $(ALLOBJ)
	$(RM) $(TRASH)

fclean	: clean
	$(RM) $(NAME)

all	: $(NAME)

re	: clean all

compil	: all clean

install	:
	cp TzParser /usr/bin
