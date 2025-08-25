# Makefile for Virtual Stock Trading App

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
TARGET = trading_app
SOURCES = main.cpp Stock.cpp User.cpp Market.cpp TradingApp.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Stock.h User.h Market.h TradingApp.h

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Run the application
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the application (default)"
	@echo "  clean    - Remove build files"
	@echo "  run      - Build and run the application"
	@echo "  debug    - Build with debug information"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  help     - Show this help message"

.PHONY: all clean install uninstall run debug help
