.PHONY: all clean

CC = clang++
CFLAGS = -O3 -Wall -m64 -shared -std=c++11 -fPIC
SRC = _Voronoi.cpp
DRAW_SRC = Draw_color.h
POINT = Point.o
SEG = Seg.o
ARC_EVENT = Arc_Event.o
DRAW_COLOR = Draw_color.o
TARGET = $(patsubst %.cpp, %.so, $(SRC))

all: $(TARGET)

%.so: %.cpp $(POINT) $(SEG) $(ARC_EVENT) $(DRAW_COLOR)
	$(CC) $(CFLAGS) -I/usr/include/mkl `python3 -m pybind11 --includes` $< $(POINT) $(SEG) $(ARC_EVENT) $(DRAW_COLOR) -o $@ `python3-config --includes --ldflags`

$(POINT): Point.cpp Point.h
	g++ -c Point.cpp -o Point.o
	
$(SEG): Seg.cpp Seg.h
	g++ -c Seg.cpp -o Seg.o
	
$(ARC_EVENT): Arc_Event.cpp Arc_Event.h
	g++ -c Arc_Event.cpp -o Arc_Event.o

$(DRAW_COLOR): Draw_color.cpp Draw_color.h
	g++ -c Draw_color.cpp -o Draw_color.o

test: test_.py _Voronoi.so
	python3 -m pytest -v

demo: demo.py _Voronoi.so
	python3 demo.py

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
	rm -f test
