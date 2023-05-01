.PHONY: all clean

CC = clang++
CFLAGS = -O3 -Wall -m64 -shared -std=c++11 -fPIC
MKL_LIB_DIR=/usr/lib/x86_64-linux-gnu
MKL_LIB_SO=libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS=$(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) \
			-lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

SRC = _Voronoi.cpp
TARGET = $(patsubst %.cpp, %.so, $(SRC))

all: $(TARGET)

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
	rm -f test

%.so: %.cpp
	$(CC) $(CFLAGS) -I/usr/include/mkl `python3 -m pybind11 --includes` $< -o $@ `python3-config --includes --ldflags` ${MKL_LIBS}
