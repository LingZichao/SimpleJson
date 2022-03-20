# SimpleJson——轻量级Json构建、字符串化练习

使用`C++11`实现~~但是性能甚至不`node.js~~的简陋Json库，大量使用STL参数所以常数开销不小，因此使用`std::move`进行了一丝丝补救，反正不敢跑benchmark（还不支持反向Json化（逃

## Feature OR Annoyance

* **单头文件库** —— 代码体积小、编译器友好 / 没啥强大功能
* **面向对象设计** —— 充分利用多态间的cast / 就是装X，乌龟壳+1
* **数组类型使用原生vector** —— 扩展性好、贴合日常使用，学习成本低 / 懒得造轮子，乌龟壳+1
* **使用转发和`std::move`构造对象** —— 避免拷贝构造，优化性能，~~一次性用品干净卫生~~ / 容易`Segment Fault`
* **构造器辅助内存管理** —— 用就完了，无需担心内存问题 / 嘛，将来会达成目标

## 快速上手

```c++
#include "SimpleJson.hpp"

using namespace SimpleJson;
int main() {
	SimpleJson::Json j;
	//基本类型
	j.push_back({"status" , true});
	j.push_back({"msg" , "success"});
	j.push_back({"obj" , 
		{ 
			{"name" , "ARX"} , 
			{"age" , 14 }
		} 
	});

	//加入Json对象数组
	std::vector< SimpleJson::Object > m;
	m.push_back( { {"key" , "test1"} , {"[pos]" , 1} }) ;
	j.push_back({"data" , m} );

	//加入Json数组，说明设计的‘一次性’
	std::vector<double> q {1.1 , 3.3 , 5.5, 20001128 ,-7 ,8.134};
	for(auto &it : q) {
		printf("%lf\n" , it); //std::move之前
	}
	j.push_back({"data" , q} );
	printf("数据push_back后就不能使用了, 都为一次性用品QAQ\n");
	for(auto &it : q) {
		printf("%lf\n" , it); //std::move之后——没有输出
	}

	//将以上项目字符串化并输出
    std::cout << j.stringize();
    printf("\nDone\n");

	return 0;
}
```
***Note:*** SimpleJson命名空间在全局`using`后可以省略`SimpleJson::`前缀

## 支持的数据类型

这里的**数据类型**指的是`K-V对`中`Value`的类型，使用时每个`K-V对`请使用`{}`包括起来，并使用`,`代替JSON格式中的`:`。

| ItemType | Description |
| --------- | ----------|
| `int`  | 原生C/C++类型|
| `double`| 原生C/C++类型|
| `bool`| 原生C/C++类型|
| `std::string`| C++ STL类型|
| `std::vector<int>`| 表示整形数组|
| `std::vector<double>`| 表示浮点数组|
| `std::vector<bool>`| 表示布尔值数组|
| `std::vector< std::string >` | 表示字符串数组|
| `std::vector< SimpleJson::Object >`| 表示对象数组|

## 支持的JSON对象方法


| Function | Description |
| --------- | ----------|
| `push_back()`  | 添加一个支持的数据类型 |
| `stringize()`| 将JSON文件字符串化 |
| `length()`| 返回Json文件字符串化后，该字符串的长度。如没有stringize()，则为0|



## 未来展望
> ~~多半咕咕，没有未来~~
+ 完成反JSON化
+ 优化内存模型，更加高效的存储
+ 找出未知的BUG
