# makefile 的一个 例子

执行make命令，可以看到下面的输出内容：

```
  g++ -g -Wall -std=c++11  ./src/*.cpp ./src2/*.cpp -o ./bin/Demo1 -I./include -I./include2  
```
 
关于库文件的链接，这类只举了静态库.a文件的链接；
对于动态库的链接方式，还不是太熟悉，没有做这方面说明。

