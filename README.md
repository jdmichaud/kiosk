# kiosk

A simple kiosk web browser based on QT5 WebViews.

# Compile

Use the Dockerfile to prepare a development environment.
Then, in the docker container:

```
git clone https://github.com/jdmichaud/kiosk
mkdir kiosk_build && cd kiosk_build
cmake ../
make
./kiosk
```

# Usage

```
./kiosk
```

# For development, you can use `entr` to automate the build

```
echo ../kiosk/CMakeLists.txt | entr bash -c "clear && CC=/usr/bin/clang CXX=/usr/bin/clang cmake ../kiosk"
find ../kiosk ! -name "CMakeLists.txt" | entr bash -c "clear && make"
echo kiosk | entr bash -c "clear && ./kiosk"
```
