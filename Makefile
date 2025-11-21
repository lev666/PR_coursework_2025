CC = gcc
CFLAGS = -Wall -Wextra -Werror -Isrc -MMD -MP -Iinclude
CFLAGS_RELEASE = -O1
CFLAGS_DEBUG = -fno-common -std=c11 -g -fsanitize=address
LDFLAGS_DEBUG = -g -fsanitize=address

SOURCES = $(wildcard src/*.c)

EXEC_REL = cw
EXEC_DBG = $(EXEC_REL).debug

BUILD_DIR = build
REL_DIR = $(BUILD_DIR)/release
DBG_DIR = $(BUILD_DIR)/debug

OBJ_REL = $(patsubst src/%.c, $(REL_DIR)/%.o, $(SOURCES))
DEPS_REL = $(OBJ_REL:.o=.d)
OBJ_DBG = $(patsubst src/%.c, $(DBG_DIR)/%.o, $(SOURCES))
DEPS_DBG = $(OBJ_DBG:.o=.d)

.PHONY: all clean tests debug doxy doxy_pdf clang_format

all: $(EXEC_REL)

doxy:
	@doxygen Doxyfile

doxy_pdf: doxy
	@make -C docs/latex

debug: $(EXEC_DBG)

$(EXEC_REL): $(OBJ_REL)
	$(CC) $(OBJ_REL) -o $(EXEC_REL)
$(EXEC_DBG): $(OBJ_DBG)
	$(CC) $(OBJ_DBG) $(LDFLAGS_DEBUG) -o $(EXEC_DBG)

tests: $(EXEC_DBG)
	@./tests/run_tests.sh

$(REL_DIR)/%.o: src/%.c
	mkdir -p $(REL_DIR)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -c $< -o $@

$(DBG_DIR)/%.o: src/%.c
	mkdir -p $(DBG_DIR)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -c $< -o $@

clang_format: $(SOURCE_FILES_DIST)
	clang-format -style=file -i $(SOURCE_FILES_DIST)


clean:
	rm -rf $(BUILD_DIR) $(EXEC_REL) $(EXEC_DBG) docs/latex docs/html

help:
	@echo "Доступные команды:"
	@echo "  make all       - Собрать release-версию (по умолчанию)"
	@echo "  make debug     - Собрать debug-версию"
	@echo "  make test      - Запустить тесты"
	@echo "  make doxy      - Собрать документацию"
	@echo "  make doxy_pdf  - Собрать PDF-документацию"
	@echo "  make clean     - Очистить папку сборки"

-include $(DEPS_REL)
-include $(DEPS_DBG)
