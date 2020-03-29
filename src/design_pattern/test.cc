/*************************************************************************
  > File Name: test.cpp
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月05日 星期四 13时03分54秒
 ************************************************************************/

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "src/macro.h"

// 父类一般禁用拷贝,避免对子类对象的切割
class Oops {
 public:
	Oops() {}
};

class Base {
 public:
	virtual void Print() const { printf("Base print.\n"); }
	//Base() : n(0), oops(nullptr) {}
	Base() : n(0) {}
	Base(const Base& other) = delete;
	Base& operator=(const Base& other) = delete;
	void NoVirtualMethod() { printf("base no virtual method.\n"); }
	void Show() { printf("ptr: %d\n", oops == nullptr); }

 protected:
	int n;
	Oops* oops;
};

class Derived : public Base {
 public:
	Derived() {}
	Derived(int state) : state_(state) {} 
	void Print() const override { printf("Derived print.\n"); }
	void NoVirtualMethod() { printf("derived no virtual method.\n"); }
	void Show() { printf("state: %d, n: %d\n", state_, n); }
	//void Show() { printf("ptr: %p\n", oops); }
 private:
	int state_;
};

void PrintWithCopy(Base base) {	base.Print(); }
void PrintWithRef(Base& base) {	base.Print(); }

void TestVectorErase() {
	std::vector<int> vec{2, 4, 4, 3, 3, 1, 4, 3, 8};
	for (int num : vec) { printf("%d ", num); }
	printf("\n");
	std::vector<int>::iterator it = std::remove(vec.begin(), vec.end(), 3);
	vec.erase(it, vec.end());
//	std::vector<int>::iterator it = std::remove(vec.begin(), vec.end(), 2);
//	printf("%d\n", *it);
	for (int num : vec) { printf("%d ", num); }
	printf("\n");
//	printf("%d\n", static_cast<int>(vec.size()));
//	printf("%d\n", *(vec.end()));
//	vec.erase(vec.begin()+3);
//	printf("%d\n", static_cast<int>(vec.size()));
//	for (int num : vec) { printf("%d ", num); }
//	printf("\n");
//	for (auto it=vec.begin(); it!=vec.end(); ++it) {
//		if (*it < 3) {
//			// erase(it)删除后会改变迭代器it的值,指向删除元素的
//			// 下一位置,如果删除元素是最后一个,则指向尾后迭代器;
//			// oops! 只要使用erase()一次,尾后迭代器的解引用值就由0变为
//			// 最后一个元素的值;
//			// it = vec.erase(it)与vec.erase(it)的效果完全相同
//			it = vec.erase(it);
//			printf("%d, %d\n", *it, *(vec.end()));
//			if (it == vec.end()) 
//					break;  //增加判断条件,避免越界访问 
//		}
//	}
//	printf("%d\n", *(vec.end()));
}

struct Data {
	Data(int x, int y) : x_(x), y_(y) {}
	int x_; 
	int y_;
};

class Foo {
 public:
	Foo() : n_(-5) { printf("construct Foo\n"); }
	explicit Foo(int n) : n_(n) { printf("construct Foo with param\n"); }
	~Foo() { printf("destruct Foo\n"); }

 public:
	int n_;
};

class Bar {
 public:
	Bar() { 
		// vector重新分配内存会导致隐式的拷贝构造,如果不加reserve,当创建2个Foo
		// 对象后,先后把他们push_back进foo_list_,则程序结束会发现析构了5次
		foo_list_.reserve(8);
		printf("construct Bar\n"); 
	}
	//Bar() : foo_(nullptr) { printf("construct Bar\n"); }
	//explicit Bar(Foo* foo) : foo_(foo) { printf("construct Bar with param\n"); }
	~Bar() { printf("destruct Bar\n"); }

	void Add(const Foo& foo) { foo_list_.push_back(foo); }
	//void Show() {
	//	printf("address: %p\n", foo_);
	//	printf("compare: %d\n", foo_ == nullptr);
	//	printf("num: %d\n", foo_->n_);
	//}

 private:
	// 指针数据成员初始化时不会自动调用其指向对象的构造函数(包括默认构造函数)
	// 同理析构时也不会自动调用其指向对象的析构函数
	//Foo* foo_; // 指针数据成员要用nullptr初始化,否则为野指针
	// 对任何聚合类型的数据成员,均不会执行内部元素的默认初始化
	std::vector<Foo> foo_list_;
};

std::shared_ptr<Data> GetData(std::vector<Data> vec, int i) {
	std::shared_ptr<Data> result(&(vec[i]));
	return result;
}

void TestSharedPtr() {
	std::vector<Data> vec;
	vec.push_back(Data(0, 0));
	vec.push_back(Data(1, 1));
	vec.push_back(Data(2, 2));
	//std::shared_ptr<Data> data(&vec[2]);
	// 报错 double free 或 invalid pointer 或 invalid size,
	// 原因是shared_ptr和其指向的对象均会释放
	// !!!永远不要把shared_ptr指向在栈上创建的对象(尤其包括类内的数据成员)
	// !!!永远使用普通指针指向栈对象
	// !!!避免滥用shared_ptr,只有使用堆对象or要把堆对象当做参数或返回值时才使用
	std::shared_ptr<Data> data = GetData(vec, 2);
	printf("%d\n", data->x_);
}

void TestFormat() {
	int x = 5;
	if (x > 3) printf("x > 3\n");
	if (x > 2)
		printf("x > 2\n");
	if (x > 1)
		printf("x > 1\n");
		return;
		//printf("x > 1 again\n");
	
	for (int i=0; i<3; ++i)
		printf("i=%d\n", i);
}

int main() {
	Base base;
	Derived derived;
	//Derived derived(5);
	//base.Show();
	derived.Show();
	//Base* ptr = &derived;
	//ptr->Print();
	//ptr->NoVirtualMethod();

	//PrintWithRef(derived);
	//PrintWithCopy(derived);
	
	//TestVectorErase();

	//Data data(2, 3);
	//printf("%d\n", data.x_);
	
	//Foo foo;
	//Foo foo_2(5);
	//printf("foo address: %p\n", &foo);
	//Bar bar(&foo);
	//Bar bar;
	//bar.Add(foo);
	//bar.Add(foo_2);
	//bar.Show();
	
	//TestSharedPtr();
	//TestFormat();

	return 0;
}
