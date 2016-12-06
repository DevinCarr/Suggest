LIBS := -lcurl
CXXFLAGS := -std=c++11
INSTALL_DIR := /usr/local/bin/

EXE := s

all: $(EXE)

install:
	install $(EXE) $(INSTALL_DIR)

$(EXE): main.cpp auth.h
	$(CXX) $(CXXFLAGS) $(LIBS) $< -o $@

clean:
	rm -f $(EXE)
