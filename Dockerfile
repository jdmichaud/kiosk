# Build with
# docker build -t simplekiosk .

FROM ubuntu:xenial

ENV IMAGE_NAME simplekiosk

# Create user
RUN useradd jedi --create-home --password jedi && echo "jedi:jedi" | chpasswd && adduser jedi sudo

RUN apt-get update
# Some utilities
RUN apt-get install -y build-essential \
  nano \
  vim \
  unzip \
  curl \
  git \
  sudo \
  tig \
  tmux \
  dos2unix \
  lsb-release \
  silversearcher-ag \
  clang \
  cmake \
  google-mock \
# Python
  python \
  python-dev \
  python-setuptools \
# For X11 application (i.e. Clion)
  libxrender1 \
  libxtst6 \
  libxi6 \
  libfreetype6 \
  libfontconfig1 \
# libraries
  libncurses5-dev \
  libc++-dev \
  libc++abi-dev

# Google Test/Mock to compile with x86 as target
RUN cd /usr/src/gmock && cmake CMakeLists.txt && make

# pip
RUN easy_install pip

USER jedi
# dotfile configuration
RUN cd /home/jedi && \
  git clone https://github.com/jdmichaud/dotfiles && \
  rm -fr /home/jedi/.mybashrc && \
  ln -s /home/jedi/dotfiles/.mybashrc /home/jedi/.mybashrc && \
  ln -s /home/jedi/dotfiles/.vimrc /home/jedi/.vimrc && \
  ln -s /home/jedi/dotfiles/.vimrc.local /home/jedi/.vimrc.local && \
  ln -s /home/jedi/dotfiles/.vimrc.local.bundles /home/jedi/.vimrc.local.bundles && \
  ln -s /home/jedi/dotfiles/.tmux.conf /home/jedi/.tmux.conf && \
  ln -s /home/jedi/dotfiles/.git /home/jedi/.git && \
  git clone https://github.com/jdmichaud/sh

# Force color prompt
RUN sed -i 's/#force_color_prompt=yes/force_color_prompt=yes/g' /home/jedi/.bashrc

# Git configuration
RUN git config --global user.email "jean.daniel.michaud@gmail.com" && \
  git config --global user.name "JD"

# Set prompt with image name
RUN echo 'export PS1="`echo $PS1 | sed s/@.h/@${IMAGE_NAME}/g` "' >> /home/jedi/.profile

# Specific part of the docker file

USER root

# Install dependencies for openGL
RUN apt-get install -y libcogl-gles2-dev

# Install dependencies for Qt WebEngine
RUN apt-get install -y \
  libssl-dev \
  libxcursor-dev \
  libxcomposite-dev \
  libxdamage-dev \
  libxrandr-dev \
  libdbus-1-dev \
  libfontconfig1-dev \
  libcap-dev \
  libxtst-dev \
  libpulse-dev \
  libudev-dev \
  libpci-dev \
  libnss3-dev \
  libasound2-dev \
  libxss-dev \
  libegl1-mesa-dev \
  gperf \
  bison

USER jedi

# Clone qt and build it
# http://wiki.qt.io/Building_Qt_5_from_Git#Getting_the_submodule_source_code
RUN cd ~/ && \
  git clone https://code.qt.io/qt/qt5.git && \
  cd qt5 && \
  git checkout v5.8.0 && \
  git submodule update --init --recursive && \
  ./configure \
    -developer-build \
    -debug \
    -opensource \
    -nomake examples \
    -nomake tests \
    -nomake tests \
    -confirm-license
RUN cd ~/qt5 && \
  make module-qtbase && \
  make module-qtwebengine


