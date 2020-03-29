/*************************************************************************
  > File Name: structure_unittest.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月20日 星期五 09时07分29秒
 ************************************************************************/

#include <stdio.h>
#include <memory>
#include "src/design_pattern/structure.h"

void TestStructure() {
	//Facade facade("facade");
	//facade.WrapOperation();

	//SafeFolder music("music");
	//SafeFolder pop("pop");
	//SafeFile huanlesong("huanlesong");
	//SafeFile songbie("songbie");
	//SafeFile qifengle("qifengle");
	//music.Add(&pop);
	//music.Add(&huanlesong);
	//pop.Add(&songbie);
	//pop.Add(&qifengle);
	//music.Display();
	//pop.Display();
	//pop.Remove();
	//pop.Display();
	//huanlesong.Display();

	//Adaptee adaptee("adaptee");
	//std::unique_ptr<Target> target(new Adapter(&adaptee));
	//Adapter2 adapter2("adaptee");
	//Target* target(&adapter2);
	//target->Request();
		
	//Proxy proxy;
	//proxy.Request();
	
	//ConcreteImplementor concrete_implementor;
	//RefinedAbstraction refined_abstraction(&concrete_implementor);
	//refined_abstraction.Operate();
	
	//ConcreteComponent concrete_component;
	//ConcreteDecorator concrete_decorator(&concrete_component);
	//concrete_decorator.Operate();

	CachedFactory& factory = CachedFactory::GetInstance();
	FlyWeight* butterfly = factory.CreateFlyWeight("butterfly");
	FlyWeight* butterfly_2 = factory.CreateFlyWeight("butterfly");
	FlyWeight* butterfly_3 = factory.CreateFlyWeight("butterfly");
	FlyWeight* bee = factory.CreateFlyWeight("bee");
	FlyWeight* bee_2 = factory.CreateFlyWeight("bee");
	bee_2->Operate("dance");
	size_t n_objects = factory.get_count();
	printf("total object num: %d\n", static_cast<int>(n_objects));
	// 新new出的对象地址时nil和插入进pool的对象地址是不一致的
	printf("butterfly: %p, butterfly_2: %p, butterfly_3: %p\n", 
				butterfly, butterfly_2, butterfly_3);
}

int main(int argc, char* argv[]) {
	TestStructure();
	return 0;
}
