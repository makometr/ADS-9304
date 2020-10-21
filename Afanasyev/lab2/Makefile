compiler = g++
flags = -c -g -std=c++17
appname = lab2
lib_dir = Sources/libs/
src_dir = Sources/srcs/

src_files := $(wildcard $(src_dir)*)
obj_files := $(addsuffix .o, $(basename $(notdir $(src_files))))

define compile
	$(compiler) $(flags) $<
endef 

programbuild: $(obj_files)
	$(compiler) $^ -o $(appname)

%.o: $(src_dir)/%.cpp $(lib_dir)/*.h
	$(call compile)

clean:
	rm -f *.o $(appname)