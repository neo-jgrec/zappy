##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

PROJECT_NAME=zappy

CMAKE_BUILD_TYPE=Release
CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CURDIR}
CMAKE_LIBRARY_OUTPUT_DIRECTORY=${CURDIR}/lib

BUILD_DIR=build

PROJECTS_SUFFIXES=server ai gui
BINS=$(addprefix $(PROJECT_NAME)_, $(PROJECTS_SUFFIXES))

all: $(BINS)

$(BINS):
	@cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(CMAKE_RUNTIME_OUTPUT_DIRECTORY) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(CMAKE_LIBRARY_OUTPUT_DIRECTORY) \
		&& make -C $(BUILD_DIR) $@ -j --no-print-directory

clean:
	@echo "Cleaning $(PROJECT_NAME)"; \
	make -C $(BUILD_DIR) clean --no-print-directory;

$(addprefix clean/, $(PROJECTS_SUFFIXES)):
	@echo "Cleaning $(PROJECT_NAME)_$(@:clean/%=%)"; \
	make -C $(BUILD_DIR)/src/$(@:clean/%=%) clean --no-print-directory;

fclean: clean
	rm -rf $(BUILD_DIR) $(BINS)

$(addprefix fclean/, $(PROJECTS_SUFFIXES)):
	@echo "Cleaning $(PROJECT_NAME)_$(@:fclean/%=%)"; \
	make -C $(BUILD_DIR)/src/$(@:fclean/%=%) clean --no-print-directory; \
	rm -rf $(BUILD_DIR)/src/$(@:fclean/%=%) $(PROJECT_NAME)_$(@:fclean/%=%);

re: fclean all

$(addprefix re/, $(PROJECTS_SUFFIXES)):
	@echo "Rebuilding $(PROJECT_NAME)_$(@:re/%=%)"; \
	make -C $(BUILD_DIR)/src/$(@:re/%=%) re --no-print-directory;

debug: CMAKE_BUILD_TYPE=Debug
debug: all

$(addprefix debug/, $(PROJECTS_SUFFIXES)):
	@cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(CMAKE_RUNTIME_OUTPUT_DIRECTORY) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(CMAKE_LIBRARY_OUTPUT_DIRECTORY) \
		&& make -C $(BUILD_DIR) $(PROJECT_NAME)_$(@:debug/%=%) -j --no-print-directory

$(addprefix test/, $(PROJECTS_SUFFIXES)):
	@cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(CMAKE_RUNTIME_OUTPUT_DIRECTORY) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(CMAKE_LIBRARY_OUTPUT_DIRECTORY) \
		&& make -C $(BUILD_DIR) $(@:test/%=%)_unit_tests -j --no-print-directory

tests_run: $(addprefix test/, $(PROJECTS_SUFFIXES))

.PHONY: all clean fclean re debug help $(BINS) $(addprefix clean/, $(PROJECTS_SUFFIXES)) $(addprefix fclean/, $(PROJECTS_SUFFIXES)) $(addprefix re/, $(PROJECTS_SUFFIXES)) $(addprefix debug/, $(BINS)) $(addprefix test/, $(PROJECTS_SUFFIXES))

.DEFAULT_GOAL := all

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all:    Build the project"
	@echo "  clean:  Clean the project"
	@echo "  fclean: Clean the project and remove the binary"
	@echo "  re:     Clean the project and rebuild it"
	@echo "  debug:  Build the project in debug mode"
	@echo "  help:   Display this help message"
	@echo ""
	@echo "Subtargets:"
	@echo "  clean/<project>:  Clean the specified project"
	@echo "  fclean/<project>: Clean the specified project and remove the binary"
	@echo "  re/<project>:     Clean the specified project and rebuild it"
	@echo "  debug/<project>:  Build the specified project in debug mode"
	@echo "  test/<project>:   Build the specified project unit tests"
	@echo ""
	@echo "Projects:"
	@echo "  $(PROJECTS_SUFFIXES)"
	@echo ""
	@echo "Examples:"
	@echo "  make"
	@echo "  make all"
	@echo "  make clean"
	@echo "  make fclean"
	@echo "  make re"
	@echo "  make debug"
	@echo "  make clean/server"
	@echo "  make fclean/server"
	@echo "  make re/server"
	@echo "  make debug/server"
	@echo "  make test/server"
	@echo ""
	@echo "For more information, ask me"
