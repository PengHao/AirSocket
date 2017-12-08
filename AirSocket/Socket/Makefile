CC = g++

PRODUCT_INCLUDE = include

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
				./AirConnectionObserver.h \
				./Thread/AirThread.h \
				./Thread/AirThreadLock.h \
				./Thread/AirThreadPool.h \
				./Thread/AirOperation.h \
				./Thread/AirQueue.h

INCLUDE = -IPCMPlayerServer \
	-IPCMPlayerServer/include \
	-IPCMPlayerServer/Protocol

LIB = -LPCMPlayerServer/lib \
	  -lProtocolBuffer \
	  -lAirSocket

CFLAG = -std=gnu++11 

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

libAirSocket.a : complie ${OBJECTS}
	ar cr $@ ${OBJECTS}

install : libAirSocket.a
	test -d ${PRODUCT_INCLUDE} || mkdir -p ${PRODUCT_INCLUDE}
	rm -rf ${PRODUCT_INCLUDE}/*
	tar -cpf - ${INCLUDE_FILES} | ( cd ${PRODUCT_INCLUDE}; tar -xpf - )

clean :
	rm -rf ${OBJECTS} ${PRODUCT_INCLUDE} libAirSocket.a
