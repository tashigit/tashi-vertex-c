.PHONY: tidy format

tidy:
	@find . -name "*.h" -or -name "*.c" -exec clang-tidy -header-filter=.* {} -- -I$(shell pwd)/include -I$(shell pwd)/examples/include \;

format:
	@find . -name "*.h" -or -name "*.c" -exec clang-format -i {} \;
