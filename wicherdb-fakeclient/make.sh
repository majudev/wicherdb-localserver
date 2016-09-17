g++ -O3 -Wall `pkg-config --cflags --libs jansson` \
	sha256.cpp \
	Toolkit.cpp \
	Database.cpp \
	DatabaseQuery.cpp \
	main.cpp \
	-o client
