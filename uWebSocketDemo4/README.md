# uWebSocketsDemo4
	基于uWebSockets框架，用C++写的一个服务器程序。可以实现客户端的注册和登陆功能。
	与客户端交互的消息，是通过JsonCpp库来序列化和反序列化的。
	客户端url参数，是sscanf来匹配正则表达式来获取参数
	还用了MongoCxx读写数据库
  
# 编译 
 
  在uWebSocketsDemo4目录下面，执行下面的命名：
  
 - > make 