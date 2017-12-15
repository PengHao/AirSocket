CC = g++

PRODUCT_INCLUDE = AirSocket

INCLUDE_FILES = ./AirConnectionPackageIO.h \
				./AirSessionManager.h \
				./AirPackage.h \
				./AirSession.h \
				./AirConnectionManager.h \
				./AirConnection.h \
				./AirCircleBuffer.h \
				./AirSocket.h \
				./AirFormatDataIO.h \
				./AirServer.h \
				./AirSocketDefine.h \
				./AirSocketConfig.h \
				./AirConnectionManagerDelegate.h \
				./Thread/AirThread.h \
				./Thread/AirThreadLock.h \
				./Thread/AirThreadPool.h \
				./Thread/AirOperation.h \
				./Thread/AirQueue.h

INCLUDE = 
LIB = -lstdc++

CFLAG = -std=c++11 

OBJECTS = AirCircleBuffer.o \
		  AirConnection.o \
		  AirConnectionManager.o \
		  AirConnectionPackageIO.o \
		  AirPackage.o \
		  AirServer.o \
		  AirSession.o \
		  AirSessionManager.o \
		  AirSocket.o \
		  AirOperation.o \
		  AirQueue.o \
		  AirThread.o \
		  AirThreadLock.o \
		  AirThreadPool.o

COMPLIE_FILES = AirConnection.cpp \
				AirCircleBuffer.cpp \
				AirConnectionManager.cpp \
				AirConnectionPackageIO.cpp \
				AirPackage.cpp \
				AirServer.cpp \
				AirSession.cpp \
				AirSessionManager.cpp \
				AirSocket.cpp \
				Thread/AirOperation.cpp \
				Thread/AirQueue.cpp \
				Thread/AirThread.cpp \
				Thread/AirThreadLock.cpp \
				Thread/AirThreadPool.cpp

complie : ${CONPLIE_FILES}
	${CC} -c ${INCLUDE} ${CFLAG} ${COMPLIE_FILES}

libairsocket.a : complie ${OBJECTS}
	ar cr $@ ${OBJECTS}

install : libairsocket.a
	test -d ${PRODUCT_INCLUDE} || mkdir -p ${PRODUCT_INCLUDE}
	rm -rf ${PRODUCT_INCLUDE}/*
	tar -cpf - ${INCLUDE_FILES} | ( cd ${PRODUCT_INCLUDE}; tar -xpf - )
	cp -r libairsocket.a /usr/local/lib/
	cp -r ${PRODUCT_INCLUDE} /usr/local/include/
clean :
	rm -rf ${OBJECTS} ${PRODUCT_INCLUDE} libairsocket.a
