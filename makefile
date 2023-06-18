CLEANUP := rm -f
MKDIR := mkdir -p
TARGET_EXTENSION := out

# folders
PATHU = ../Unity/src/
PATHS = src/
PATHT = test/
PATHB = build/
PATHO = build/objs/
PATH_TO := build/test_objs/
PATH_TE = build/test_exec/
PATH_TR = build/test_results/

BUILD_PATHS = $(PATHB) $(PATHO)
BUILD_PATHS_T = $(PATHB) $(PATH_TO) $(PATH_TE) $(PATH_TR)

# target exec
TARGET_EXEC := $(PATHB)clox

# source files
SRC := $(wildcard $(PATHS)*.c)
SRC_T := $(wildcard $(PATHT)Test*.c)
SRC_T_LIB := $(filter-out $(SRC_T), $(wildcard $(PATHT)*.c))

COMPILE := gcc -c
LINK := gcc
DEPEND := gcc -MM -MG -MF
CFLAGS_T := -I. -I$(PATHU) -I$(PATHS) -DTEST
CFLAGS := -I. -I$(PATHS)

# create src objs in build/objs/
OBJS := $(patsubst $(PATHS)%.c,$(PATHO)%.o,$(SRC))
# create source objs in build/test_objs/
OBJS_T := $(patsubst $(PATHS)%.c,$(PATH_TO)%.o,$(SRC))
# create test lib objs in build/test_objs/
OBJS_T_LIB := $(patsubst $(PATHT)%.c,$(PATH_TO)%.o,$(SRC_T_LIB))

RESULTS := $(patsubst $(PATHT)Test%.c,$(PATH_TR)Test%.txt,$(SRC_T))

PASSED := `grep -s PASS $(PATH_TR)*.txt`
FAIL := `grep -s FAIL $(PATH_TR)*.txt`
IGNORE := `grep -s IGNORE $(PATH_TR)*.txt`

# exec
.PHONY: clox
clox: $(BUILD_PATHS) $(TARGET_EXEC)
	@echo "\nDONE"

$(TARGET_EXEC): $(OBJS) 
	$(LINK) -o $@ $^

$(PATHO)%.o: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@


# build/result/*.txt
.PHONY: test
test: $(BUILD_PATHS_T) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

# build/test_exec/Test*.out
$(PATH_TR)%.txt: $(PATH_TE)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# build/test_objs/Test*.o build/test_objs/{all_src}.o, build/test_objs/{test_lib}.o build/test_objs/unity.o
$(PATH_TE)Test%.$(TARGET_EXTENSION): $(PATH_TO)Test%.o $(OBJS_T) $(OBJS_T_LIB) $(PATH_TO)unity.o
	$(LINK) -o $@ $^

# test/*.c
$(PATH_TO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS_T) $< -o $@

# src/*.c
$(PATH_TO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS_T) $< -o $@

# ../Unity/src/*.c  ../Unity/src/*.h
$(PATH_TO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS_T) $< -o $@

# create folders
$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATH_TO):
	$(MKDIR) $(PATH_TO)

$(PATH_TE):
	$(MKDIR) $(PATH_TE)

$(PATH_TR):
	$(MKDIR) $(PATH_TR)

.PHONY: clean
clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATH_TO)*.o
	$(CLEANUP) $(PATH_TE)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(TARGET_EXEC)
	$(CLEANUP) $(PATH_TR)*.txt

.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATH_TO)%.o
.PRECIOUS: $(PATH_TE)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATH_TR)%.txt

