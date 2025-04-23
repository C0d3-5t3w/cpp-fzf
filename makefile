.PHONY: init
init:
	@mkdir -p build

.PHONY: clean
clean:
	@rm -rf .DS_Store
	@rm -rf src/.DS_Store
	@rm -rf build

.PHONY: build
build: clean init
	@cd build && cmake .. && make all

.PHONY: run
run:
	@cd build && ./FzF

.PHONY: deps-mac
deps-mac:
	@brew install cmake
	@brew install ripgrep
	@brew install wxwidgets

.PHONY: deps-linux
deps-linux:
	@sudo apt-get install cmake
	@sudo apt-get install ripgrep
	@sudo apt-get install libwxgtk3.0-dev

.PHONY: help
help:
	@echo "Makefile commands:"
	@echo "  init       - Create build directory"
	@echo "  clean      - Remove build directory"
	@echo "  build      - Build the project"
	@echo "  run        - Run the project"
	@echo "  deps-mac   - Install dependencies for macOS"
	@echo "  deps-linux - Install dependencies for Linux"
	@echo "  help       - Show this help message"
