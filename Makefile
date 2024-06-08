##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

CMAKE_BUILD_TYPE=Release
CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CURDIR}
CMAKE_LIBRARY_OUTPUT_DIRECTORY=${CURDIR}/lib

BUILD_DIR=build

BINS=zappy_server zappy_ai zappy_gui

all: $(BINS)

$(BINS):
	@cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(CMAKE_RUNTIME_OUTPUT_DIRECTORY) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(CMAKE_LIBRARY_OUTPUT_DIRECTORY) \
		&& make -C $(BUILD_DIR) $@ -j --no-print-directory

clean:
	@make -C $(BUILD_DIR) clean --no-print-directory

fclean: clean
	@for bin in $(CMAKE_RUNTIME_OUTPUT_DIRECTORY)/$(BINS); do \
		rm -f $$bin; \
	done
	@rm -rf $(BUILD_DIR)

re: fclean all

debug: $(BINS:%=%-debug)

$(BINS:%=%-debug):
	@echo "Building $@..."
	@cmake -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(CMAKE_RUNTIME_OUTPUT_DIRECTORY) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(CMAKE_LIBRARY_OUTPUT_DIRECTORY) \
		&& make -C $(BUILD_DIR) $(@:-debug=) -j --no-print-directory

.PHONY: all clean fclean re $(BINS) debug $(BINS)-debug
