SRCDIR=src
INCDIR=inc
OBJDIR=obj
BINDIR=bin
DEPDIR=dep

POSTFIX=cpp
OUTFILENAME=outfile.out
TESTPOSTFIX=.test

SOURCES=$(notdir $(wildcard src/*.$(POSTFIX)))
OBJS=$(patsubst %.$(POSTFIX),%.o,$(SOURCES))

BASEFLAGS= -Wall -I $(INCDIR) -std=c++0x -pthread 
POSTFIXFLAGS= -lstdc++
CFLAGS=$(BASEFLAGS) -O2

vpath %.h 			$(INCDIR)
vpath %.$(POSTFIX)	$(SRCDIR)
vpath %.o			$(OBJDIR)
vpath %.d			$(DEPDIR)

ifeq ($(MAKECMDGOALS), runtest)
CFLAGS=$(BASEFLAGS) -g -DDEBUG -O0
endif
ifeq ($(MAKECMDGOALS), debug)
CFLAGS=$(BASEFLAGS) -g -DDEBUG -O0
endif

release:$(BINDIR)/$(OUTFILENAME)

$(BINDIR)/$(OUTFILENAME):$(OBJS)
	@$(CC) $(CFLAGS) -o $(BINDIR)/$(OUTFILENAME) $(patsubst %,$(OBJDIR)/%,$(OBJS)) $(POSTFIXFLAGS)
%.o:%.$(POSTFIX)
	@$(CC) -c $(CFLAGS) $< -o $(OBJDIR)/$@
$(DEPDIR)/%.d:%.$(POSTFIX)
	@$(RM) $(DEPDIR)/$@;
	@$(CC) -MM $(CFLAGS) $< | sed 's/\($(patsubst %.$(POSTFIX),%,$(notdir $<))\)\.o *: */\1.o \1.d:/' > $@

$(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX):$(OBJS)
	@$(CC) $(CFLAGS) -o $(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX) $(patsubst %,$(OBJDIR)/%,$(OBJS)) $(POSTFIXFLAGS)
 
ifneq ($(MAKECMDGOALS),clean)
sinclude $(patsubst %.o,$(DEPDIR)/%.d,$(OBJS))
endif

.PHONY: run runtest release debug clean

run:$(BINDIR)/$(OUTFILENAME)
	@$(BINDIR)/$(OUTFILENAME)

runtest:$(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX)
	@$(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX)

debug:$(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX)

clean:
	@$(RM) $(OBJDIR)/*.o
	@$(RM) $(DEPDIR)/*.d
	@$(RM) $(BINDIR)/$(OUTFILENAME)
	@$(RM) $(BINDIR)/$(OUTFILENAME)$(TESTPOSTFIX)
