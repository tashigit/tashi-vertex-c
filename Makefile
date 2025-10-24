.PHONY: tidy format

INCLUDE_PATH = $(shell pwd)/include

tidy:
	@find . -name "*.h" -or -name "*.c" -exec clang-tidy -header-filter=.* {} -- -I$(INCLUDE_PATH) \;

format:
	@find . -name "*.h" -or -name "*.c" -exec clang-format -i {} \;
