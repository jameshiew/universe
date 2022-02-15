FROM debian:buster-20200130

# libglu1-mesa-dev and xorg-dev are needed for glfw
RUN DEBIAN_FRONTEND=noninteractive \
	apt-get update && \
	apt-get install -y --no-install-recommends \
	cmake=3.13.4-1 \
	g++=4:8.3.0-1 \
	gcc=4:8.3.0-1 \
	libglu1-mesa-dev=9.0.0-2.1+b3 \
	make=4.2.1-1.2 \
	python3-dev=3.7.3-1 \
	python3-pip=18.1-5 \
	python3-setuptools=40.8.0-1 \
	python3-wheel=0.32.3-2 \
	xorg-dev=1:7.7+19

RUN apt-get install -y --no-install-recommends libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-render-util0-dev libxcb-util0-dev libxcb-xinerama0-dev libxcb-xkb-dev xkb-data && \
	rm -rf /var/lib/apt/lists/*
RUN pip3 install --no-cache-dir --verbose conan
