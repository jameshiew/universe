FROM alpine:3.7
RUN ["apk", "update"]
RUN ["apk", "add", "gcc", "cmake", "python3"]
RUN ["pip3", "install", "conan"]