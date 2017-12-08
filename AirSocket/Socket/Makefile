CC = g++
PRODUCT_INCLUDE = include

INCLUDE_FILES = ./AirConnectionPackageIO.h ./AirSessionManager.h ./AirPackage.h ./AirSession.h \
	./AirConnectionManager.h ./AirConnection.h ./AirCircleBuffer.h ./AirSocket.h ./AirFormatDataIO.h \
	./AirServer.h ./AirSocketDefine.h ./AirSocketConfig.h ./AirConnectionObserver.h ./Thread/AirThread.h \
	./Thread/AirThreadLock.h ./Thread/AirThreadPool.h ./Thread/AirOperation.h ./Thread/AirQueue.h

INCLUDE = -I/Users/penghao/Project/github/c++/PCMPlayerServer \
	-I/Users/penghao/Project/github/c++/PCMPlayerServer/include \
	-I/Users/penghao/Project/github/c++/PCMPlayerServer/Protocol

LIB = -L/Users/penghao/Project/github/c++/PCMPlayerServer/lib -lProtocolBuffer -lAirSocket

CFLAG = -arch x86_64 -std=gnu++11 -stdlib=libc++

OBJECTS = AirCircleBuffer.o AirConnection.o AirConnectionManager.o AirConnectionPackageIO.o \
	AirPackage.o AirServer.o AirSession.o AirSessionManager.o AirSocket.o AirOperation.o \
	AirQueue.o AirThread.o AirThreadLock.o AirThreadPool.o

COMPLIE_FILES =  AirConnection.cpp AirCircleBuffer.cpp AirConnectionManager.cpp AirConnectionPackageIO.cpp \
	AirPackage.cpp AirServer.cpp AirSession.cpp  AirSessionManager.cpp AirSocket.cpp \
	Thread/AirOperation.cpp Thread/AirQueue.cpp Thread/AirThread.cpp Thread/AirThreadLock.cpp \
	Thread/AirThreadPool.cpp

com : ${CONPLIE_FILES}
	${CC} -c ${INCLUDE} ${CFLAG} ${COMPLIE_FILES}

libAirSocket.a : com ${OBJECTS}
	ar cr $@ ${OBJECTS}

install : libAirSocket.a
	test -d ${PRODUCT_INCLUDE} || mkdir -p ${PRODUCT_INCLUDE}
	rm -rf ${PRODUCT_INCLUDE}/*
	tar -cpf - ${INCLUDE_FILES} | ( cd ${PRODUCT_INCLUDE}; tar -xpf - )
	#install ${INCLUDE_FILES} ${PRODUCT_INCLUDE}


clean :
	rm ${OBJECTS} libAirSocket.a
