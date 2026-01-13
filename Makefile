BUILD_DIR = build
CMAKE = cmake

all: build_project

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) ..

build_project: $(BUILD_DIR)
	$(CMAKE) --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

run: all
	./$(BUILD_DIR)/main

.PHONY: all build_project clean rebuild run