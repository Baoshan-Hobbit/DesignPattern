/*************************************************************************
  > TransparentFile Name: structure.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月12日 星期四 16时54分32秒
 ************************************************************************/

#include "src/design_pattern/structure.h"
#include <stdio.h>
#include <string>
#include <typeinfo>
#include "src/design_pattern/create.h"
#include "src/design_pattern/product.h"

Facade::Facade(const std::string& name) : name_(name) {
	product1_.reset(new Product1("product1"));
	product2_.reset(new Product2("product2"));
}

void Facade::WrapOperation() const {
	printf("test %s\n", name_.c_str());
	product1_->use();
	product2_->use();
}

void TransparentFile::Add(TransparentComponent* component) {
	printf("Ilegal Add() for TransparentFile!");
	return;
}
void TransparentFile::Remove() {
	printf("Ilegal Remove() for TransparentFile!");
	return;
}
void TransparentFile::Display() {
	printf("%s\n", name_.c_str());	
}

void TransparentFolder::Add(TransparentComponent* component) {
	composite_list_.push_back(component);
}
void TransparentFolder::Remove() {
	composite_list_.pop_back();
}

// 修改level_,不能定义为const
void TransparentFolder::Display() {
	printf("%s\n", name_.c_str());
	std::string prefix;
	for (int i=0; i<level_; ++i)
		prefix += "\t-";
	for (TransparentComponent* component : composite_list_) {
		// RTTI, bad coding
		if (typeid(*component) == typeid(TransparentFolder)) 
			(dynamic_cast<TransparentFolder*>(component))->level_ = level_ + 1;
		printf("%s", prefix.c_str());
		component->Display();
	}
		// 修改下层目录级别(higher TransparentFolder) or 打印下层
		// 文件(bottom TransparentFolder)完成,重置为默认级别
		level_ = 1; 
}

void SafeFile::Display() {
	printf("%s\n", name_.c_str());	
}

void SafeFolder::Add(SafeComponent* component) {
	composite_list_.push_back(component);
}
void SafeFolder::Remove() {
	composite_list_.pop_back();
}

// 修改level_,不能定义为const
void SafeFolder::Display() {
	printf("%s\n", name_.c_str());
	std::string prefix;
	for (int i=0; i<level_; ++i)
		prefix += "\t-";
	for (SafeComponent* component : composite_list_) {
		// RTTI, bad coding
		if (typeid(*component) == typeid(SafeFolder)) 
			(dynamic_cast<SafeFolder*>(component))->level_ = level_ + 1;
		printf("%s", prefix.c_str());
		component->Display();
	}
		// 修改下层目录级别pi(higher TransparentFolder) or 打印下层
		// 文件(bottom TransparentFolder)完成,重置为默认级别
		level_ = 1; 
}

Adaptee::Adaptee(const std::string& str) : adaptee_member_(str) {}
void Adaptee::OldRequest() { printf("%s\n", adaptee_member_.c_str()); }

Adapter::Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
void Adapter::Request() { adaptee_->OldRequest(); }

Adapter2::Adapter2(const std::string& str) : Adaptee(str) {}
void Adapter2::Request() { OldRequest(); }

void RealSubject::Request() { printf("Real subject request.\n"); }
void Proxy::Request() { 
	PreRequest();
	real_subject_->Request();
	AfterRequest();
}

void Abstraction::OperateImplementor() { impl_->Implement(); }
void RefinedAbstraction::Operate() {
	printf("RefinedAbstraction.Operate()\n");
	OperateImplementor();
}
void ConcreteImplementor::Implement() { 
	printf("ConcreteImplementor.Implement()\n"); 
}

void ConcreteComponent::Operate() { printf("ConcreteComponent.Operate()\n"); }
void ConcreteDecorator::Operate() {
	AddProperty();
	OperateComponent();
}
void ConcreteDecorator::AddProperty() { printf("Add property.\n"); }

void ConcreteFlyWeight::Operate(const std::string& external) {
	printf("%s.\n", external.c_str());
}
FlyWeight* CachedFactory::CreateFlyWeight(const std::string& arg) {
	std::map<std::string, FlyWeight*>::const_iterator it = fly_weight_pool_.find(
			arg);
	FlyWeight* fly_weight = nullptr;
	if (it == fly_weight_pool_.end()) {
		//printf("create %s\n", arg.c_str());
		FlyWeight* fly_weight = new ConcreteFlyWeight(arg);
		fly_weight_pool_.insert(std::make_pair(arg, fly_weight));
	} else {
		printf("get from pool.\n");
		fly_weight = it->second;
	}
	return fly_weight;
}
