EXAMPLE_FILES := Demo1
override CXXFLAGS += -lpthread -Wconversion -std=c++17 -IuWebSocketsInclude -IuSockets/src -Iinclude 
override LDFLAGS += uSockets/*.o  ./examples/lib_json/libjsoncpp.a -lz

# WITH_OPENSSL=1 enables OpenSSL 1.1+ support
ifeq ($(WITH_OPENSSL),1)
	# With problems on macOS, make sure to pass needed LDFLAGS required to find these
	override LDFLAGS += -lssl -lcrypto
else
	# WITH_WOLFSSL=1 enables WolfSSL 4.2.0 support (mutually exclusive with OpenSSL)
	ifeq ($(WITH_WOLFSSL),1)
		override LDFLAGS += -L/usr/local/lib -lwolfssl
	endif
endif

# WITH_LIBUV=1 builds with libuv as event-loop
ifeq ($(WITH_LIBUV),1)
	override LDFLAGS += -luv
endif

# WITH_ASAN builds with sanitizers
ifeq ($(WITH_ASAN),1)
	override CXXFLAGS += -fsanitize=address
	override LDFLAGS += -lasan
endif

.PHONY: examples
examples:
	$(MAKE) -C uSockets
	$(foreach FILE,$(EXAMPLE_FILES),$(CXX) -flto -O3 $(CXXFLAGS) examples/$(FILE).cpp -o $(FILE) $(LDFLAGS);)
	
all:
	$(MAKE) examples
	
clean:
	rm -rf $(EXAMPLE_FILES)

	
	
