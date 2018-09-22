# stackshow
提供嵌入式平台栈回溯信息输出。
依赖于glibc/uClibc等开源库,跟gcc编译器亦有关联.


1.编译命令	
	# make all
	# make clean

2.设置环境变量
	export LD_LIBRARY_PATH=$(PATH)/stackshow			# $(PATH) 表示路径

3.测试例子
	⑴ 编译 show_stack.c 文件
	# make test 

