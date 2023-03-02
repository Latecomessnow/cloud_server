thread:thread.cc
	# 使用原生线程库需要带上 -lpthread 选项
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f thread