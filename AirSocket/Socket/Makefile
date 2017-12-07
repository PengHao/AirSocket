CC = g++

INCLUDE = -I/Users/penghao/Project/github/c++/PCMPlayerServer \
	-I/Users/penghao/Project/github/c++/PCMPlayerServer/include \
	-I/Users/penghao/Project/github/c++/PCMPlayerServer/Protocol

LIB = -L/Users/penghao/Project/github/c++/PCMPlayerServer/lib -lProtocolBuffer -lAirSocket

CFLAG = -arch x86_64 -std=gnu++11 -stdlib=libc++

OBJECTS = AirCircleBuffer.o AirConnection.o AirConnectionManager.o AirConnectionPackageIO.o \
	AirPackage.o AirServer.o AirSession.o AirSessionManager.o AirSocket.o AirOperation.o \
	AirQueue.o AirThread.o AirThreadLock.o AirThreadPool.o


AirCircleBuffer.o : AirCircleBuffer.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirCircleBuffer.cpp

AirConnection.o : AirConnection.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirConnection.cpp

AirConnectionManager.o : AirConnectionManager.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirConnectionManager.cpp

AirConnectionPackageIO.o : AirConnectionPackageIO.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirConnectionPackageIO.cpp

AirPackage.o : AirPackage.cpp
	${CC} -c ${INCLUDE} ${CFLAG} AirPackage.cpp

AirServer.o : AirServer.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirServer.cpp

AirSession.o : AirSession.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirSession.cpp

AirSessionManager.o : AirSessionManager.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirSessionManager.cpp

AirSocket.o : AirSocket.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  AirSocket.cpp

AirOperation.o : Thread/AirOperation.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  Thread/AirOperation.cpp

AirQueue.o : Thread/AirQueue.cpp
	${CC} -c ${INCLUDE} ${CFLAG} Thread/AirQueue.cpp

AirThread.o : Thread/AirThread.cpp
	${CC} -c ${INCLUDE} ${CFLAG} Thread/AirThread.cpp

AirThreadLock.o : Thread/AirThreadLock.cpp
	${CC} -c ${INCLUDE} ${CFLAG}  Thread/AirThreadLock.cpp

AirThreadPool.o : Thread/AirThreadPool.cpp
	${CC} -c ${INCLUDE} ${CFLAG} Thread/AirThreadPool.cpp


libAirSocket.a : ${OBJECTS}
	ar cr $@ ${OBJECTS}


clean :
	rm ${OBJECTS} libAirSocket.a
