# Dockerfile
FROM mongodb/mongo-cxx-driver:3.10.1-redhat-ubi-9.4

WORKDIR /build

RUN microdnf upgrade -y && microdnf install -y dnf
RUN dnf install -y \
  llvm-toolset\
  gcc-gfortran\
  gcc \
  gcc-c++ \
  cmake \
  git \
  make \
  openssl-devel \
  automake \
  autoconf \
  libtool \
  && dnf clean all

COPY . /app
WORKDIR /app

# Build the application
RUN mkdir build && cd build && cmake .. && make

# Expose the port your application will run on
EXPOSE 18080

# Command to run your application
CMD ["./build/Server"]