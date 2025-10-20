FROM ubuntu:20.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get upgrade -y
    
RUN DEBIAN_FRONTEND='noninteractive' apt-get install -y git \
                    wget \
                    dpkg-dev \
                    cmake \
                    g++ \
                    gcc \
                    binutils \
                    libx11-dev \
                    libxmu-dev \
                    libglu1-mesa-dev \
                    freeglut3-dev \
                    mesa-common-dev \
                    libxi-dev \
                    libxpm-dev \
                    libxft-dev \
                    libxext-dev \
                    libtool \
                    gfortran \
                    libssl-dev \
                    libpcre3-dev \
                    xlibmesa-glu-dev \
                    libglew1.5-dev \
                    libftgl-dev \
                    libmysqlclient-dev \
                    libfftw3-dev \
                    libcfitsio-dev \
                    graphviz-dev \
                    libavahi-compat-libdnssd-dev \
                    libldap2-dev \
                    python-dev \
                    libxml2-dev \
                    libkrb5-dev \
                    libgsl0-dev \
                    libtinfo5 \
                    qt5-default \
                    vim \
                    autoconf \
                    bumpversion \
                    rsync grsync

ADD create-env conda_settings.yml requirements.txt /tmp/

RUN cd /tmp && \
    bash create-env /opt/GeMSE && \
    rm -f create-env conda_xnt.yml

# build info
RUN echo "Timestamp:" `date --utc` | tee /image-build-info.txt

