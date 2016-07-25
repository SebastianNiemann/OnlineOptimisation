FROM ubuntu:16.04

MAINTAINER Sebastian Niemann <niemann@sra.uni-hannover.de>

RUN apt-get update

# Installs compilers and sets them as default
# - GCC
# - Clang
RUN apt-get install -y g++-5 && \
    update-alternatives --remove g++ /usr/bin/gcc && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 100 && \
    update-alternatives --set gcc /usr/bin/gcc-5 && \
    update-alternatives --remove g++ /usr/bin/g++ && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 100 && \
    update-alternatives --set g++ /usr/bin/g++-5 && \
    update-alternatives --remove gcov /usr/bin/gcov && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-5 100 && \
    update-alternatives --set gcov /usr/bin/gcov-5
RUN apt-get install -y clang-3.8 && \
    update-alternatives --remove clang /usr/bin/clang && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 100 && \
    update-alternatives --set clang /usr/bin/clang-3.8 && \
    update-alternatives --remove clang++ /usr/bin/clang++ && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.8 100 && \
    update-alternatives --set clang++ /usr/bin/clang++-3.8
    
# Installs dependencies
# - CMake
# - Armadillo C++ (and fixes issues with IWYU (suggesting for example <armadillo_bits/Base_bones.hpp> instead of <armadillo>)
RUN apt-get install -y cmake
RUN apt-get install -y wget xz-utils libblas-dev liblapack-dev libopenblas-dev && \
    wget -O armadillo.tar.xz http://downloads.sourceforge.net/arma/armadillo-7.300.0.tar.xz && \
    mkdir armadillo && \
    tar -xJf armadillo.tar.xz -C ./armadillo --strip-components=1 && \
    cd armadillo && \
    cmake . && \
    make -j 4 && \
    make install && \
    find /usr/include/armadillo_bits -name *.hpp -exec sed -i -e '1i\/\/ IWYU pragma\: private\, include \<armadillo\>' {} ';' && \
    cd .. && \
    rm -Rf armadillo.tar.xz armadillo/ && \
    apt-get remove -y --purge wget xz-utils

# Installs optional dependencies
# - MPI (including missing default include path)
RUN apt-get install -y libmpich-dev && \
    export CPATH=$CPATH:/usr/include/mpich/

# Installs testing libraries
# - Catch
RUN apt-get install -y catch

# Installs code analyser
# - Clang-format
# - Include-what-you-use (including missing default include path)
RUN apt-get install -y clang-format-3.8 && \
    update-alternatives --remove clang-format /usr/bin/clang-format && \
    update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-3.8 100 && \
    update-alternatives --set clang-format /usr/bin/clang-format-3.8
RUN apt-get install -y iwyu && \
    export CPATH=$CPATH:/usr/lib/gcc/x86_64-linux-gnu/6/include:/usr/lib/gcc/x86_64-linux-gnu/6/include-fixed:/usr/lib/llvm-3.8/lib/clang/3.8.1/include

# Installs benchmarker
# - Google microbenchmark library
RUN apt-get install -y wget && \
    wget -O benchmark.tar.gz https://github.com/google/benchmark/archive/master.tar.gz && \
    mkdir benchmark && \
    tar -xzf benchmark.tar.gz -C ./benchmark --strip-components=1 && \
    cd benchmark  && \
    cmake -DCMAKE_BUILD_TYPE=Release . && \
    make benchmark && \
    make install && \
    cd .. && \
    rm -Rf benchmark.tar.gz benchmark/ && \
    apt-get remove -y --purge wget