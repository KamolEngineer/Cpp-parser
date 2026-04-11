EXEC_SUFIX = Exec

COMPILE = g++

MAIN_EXEC = parserExec
LIST_OF_CPP_FILES = $(wildcard *.cpp)
LIST_OF_EXECUTABLES = $(addsuffix $(EXEC_SUFIX), $(patsubst %.cpp, %, $(LIST_OF_CPP_FILES)))

all:
	@echo $(LIST_OF_CPP_FILES)
	@echo $(LIST_OF_EXECUTABLES)
	@$(COMPILE) $(word 1, $(LIST_OF_CPP_FILES)) -o $(word 1, $(LIST_OF_EXECUTABLES))

clean:
	@echo "Cleaning up executables..."
	@rm -f $(LIST_OF_EXECUTABLES)
	@echo "All executables removed successfully."
