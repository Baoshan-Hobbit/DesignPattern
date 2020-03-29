/*************************************************************************
  > File Name: behavior.h
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月19日 星期四 19时17分26秒
 ************************************************************************/

#ifndef CPLUS_PRACTICE_DESIGN_PATTERN_BEHAVIOR_H_
#define CPLUS_PRACTICE_DESIGN_PATTERN_BEHAVIOR_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "src/macro.h"

// 观察者模式
class Subscriber;
class PublisherRegister {
 public:
	virtual ~PublisherRegister() {}

	void Attatch(Subscriber* subscriber);
	void Detatch(Subscriber* subscriber);
	void Notify();
	size_t GetSize() const { return subscriber_list_.size(); }
	
 private:
	std::vector<Subscriber*> subscriber_list_;
};

class PublisherContent {
 public:
	virtual ~PublisherContent() {}

	virtual int get_state() const = 0;
	virtual void set_state(int state) = 0;
};

class ConcretePublisher : public PublisherRegister, public PublisherContent {
 public:
	ConcretePublisher() : state_(0) {}
	DISALLOW_COPY_AND_ASSIGN(ConcretePublisher);

	int get_state() const override;
	void set_state(int state) override;

	PublisherRegister* GetPublisherRegister() { 
		return static_cast<PublisherRegister*>(this); 
	}
	PublisherContent* GetPublisherContent() {
		return static_cast<PublisherContent*>(this);
	}

 private:
	int state_;
};

class Subscriber {
 public:
	virtual ~Subscriber();
	virtual void Update() = 0;

 protected:
	Subscriber(PublisherRegister* publisher_register);

 private:
	PublisherRegister* publisher_register_;
};

class ConcreteSubscriber : public Subscriber {
 public:
	ConcreteSubscriber(const std::string& name, 
										 PublisherRegister* publisher_register, 
										 PublisherContent* publisher_content); 
	DISALLOW_COPY_AND_ASSIGN(ConcreteSubscriber);

	void Update() override;

 private:
	std::string name_;
	PublisherContent* publisher_content_;
};

// 命令模式
class Receiver {
 public:
	Receiver() {}
	DISALLOW_COPY_AND_ASSIGN(Receiver);

	void On();
	void Off();
	void Alter();
};

class Command {
 public:
	virtual ~Command() {}
	virtual void Execute() = 0;

protected:
	Command() : receiver_(nullptr) {}
	explicit Command(Receiver* receiver) : receiver_(receiver) {}

 protected:
	Receiver* receiver_;
};

class OnCommand : public Command {
 public:
	explicit OnCommand(Receiver* receiver) : Command(receiver) {}
	DISALLOW_COPY_AND_ASSIGN(OnCommand);

	void Execute() override;
};

class OffCommand : public Command {
 public:
	explicit OffCommand(Receiver* receiver) : Command(receiver) {}
	DISALLOW_COPY_AND_ASSIGN(OffCommand);

	void Execute() override;
};

class AlterCommand : public Command {
 public:
	explicit AlterCommand(Receiver* receiver) : Command(receiver) {}
	DISALLOW_COPY_AND_ASSIGN(AlterCommand);

	void Execute() override;
};

// Invoker继承Command是实现递归执行命令的关键,继承Command是组合模式的体现
// 需注意的时Command此时需要增加无参构造函数
class Invoker : public Command {
 public:
	Invoker() {}
	DISALLOW_COPY_AND_ASSIGN(Invoker);

	void Add(Command* command);
	void Remove(Command* command);
	//void Call(); 
	void Execute();

 private:
	std::vector<Command*> command_list_;
};

//// 策略模式
//class Policy;
//class Context {
// public:
//	Context() : policy_(nullptr) {}
//	DISALLOW_COPY_AND_ASSIGN(Context);
//
//	void set_policy(Policy* policy);
//	void Run();
//
// private:
//	Policy* policy_;
//};
//
//class Policy {
// public:
//	virtual ~Policy() {}
//	virtual void Execute() = 0;
//};
//
//class PolicyA : public Policy {
// public:
//	PolicyA() {}
//	DISALLOW_COPY_AND_ASSIGN(PolicyA);
//
//	void Execute() override;
//};
//
//class PolicyB : public Policy {
// public:
//	PolicyB() {}
//	DISALLOW_COPY_AND_ASSIGN(PolicyB);
//
//	void Execute() override;
//};

// 状态模式
class Context;
class State {
 public:
	virtual ~State() {}

	// state_->Method(),Method() must be defined in State class.
	virtual void OnPassiveOpen(Context* context) {}
	virtual void OnActiveOpen(Context* context) {}
	virtual void OnSynRecv(Context* context) {}
	virtual void OnClose(Context* context) {}
	virtual const char* get_name() const {}

 protected:
	State() {}
};

class Context {
 public:
	Context();
	DISALLOW_COPY_AND_ASSIGN(Context);

	void PassiveOpen();
	void ActiveOpen();
	void SynRecv();
	void Close();

	void set_state(State* state) { state_ = state; }
	const char* get_state() const { return state_->get_name(); }

 private:
	State* state_;
};

class ClosedState : public State{
 public:
	static const constexpr char* name = "closed";
	static ClosedState& GetInstance() {
		static ClosedState state;
		return state;
	}
	DISALLOW_COPY_AND_ASSIGN(ClosedState);
	
	void OnPassiveOpen(Context* context) override;
	void OnActiveOpen(Context* context) override;
	const char* get_name() const override { return name; }

 private:
	ClosedState() {}
};

class ListenState : public State {
 public:
	static const constexpr char* name = "listen";
	static ListenState& GetInstance() {
		static ListenState state;
		return state;
	}
	DISALLOW_COPY_AND_ASSIGN(ListenState);
	
	void OnSynRecv(Context* context) override;
	const char* get_name() const override { return name; }

 private:
	ListenState() {}
};

class SynRecvState : public State {
 public:
	static const constexpr char* name = "syn_recv";
	static SynRecvState& GetInstance() {
		static SynRecvState state;
		return state;
	}
	DISALLOW_COPY_AND_ASSIGN(SynRecvState);
	
	void OnClose(Context* context) override;
	const char* get_name() const override { return name; }

 private:
	SynRecvState() {}
};

class SynSentState : public State {
 public:
	static const constexpr char* name = "syn_sent";
	static SynSentState& GetInstance() {
		static SynSentState state;
		return state;
	}
	DISALLOW_COPY_AND_ASSIGN(SynSentState);
	
	void OnClose(Context* context) override;
	const char* get_name() const override { return name; }

 private:
	SynSentState() {}
};

// 中介者模式
class College;
class Mediator {
 public:
	virtual ~Mediator() {}

	void RegisterCollege(int id, College* college);
	virtual void Operate(int id, const std::string& msg) = 0;

 protected:
	Mediator() {}

 protected:
	std::map<int, College*> college_list_;
};

class College {
 public:
	 virtual ~College() {}

	 void set_mediator(Mediator* mediator) { mediator_ = mediator; }
	 // 非纯虚函数记得定义,否则报错对‘vtable for College’未定义的引用
	 virtual void SendMsg(int id, const std::string& msg) = 0;
	 virtual void RecvMsg(const std::string& msg) = 0;

 protected:
	 College() {}

 protected:
	Mediator* mediator_;
};

class ConcreteMediator : public Mediator {
 public:
	ConcreteMediator() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteMediator);

	void Operate(int id, const std::string& msg) override;
};

class ConcreteCollege : public College {
 public:
	ConcreteCollege() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteCollege);

	void SendMsg(int id, const std::string& msg) override;
	void RecvMsg(const std::string& msg) override;
};

// 迭代器模式
template <class Object>
class Iterator {
 public:
	virtual ~Iterator() {}

	virtual void Next() = 0;
	virtual void Previous() = 0;
	virtual bool IsLast() = 0;
	virtual bool IsFirst() = 0;
	virtual Object* GetCurrent() = 0;
};

template <class Object>
class Aggregate {
 public:
	virtual ~Aggregate() {}

	virtual void Add(const Object& object) = 0;
	// size_t无符号类型,不能用于倒序遍历,需static_case至int
	virtual size_t GetSize() const= 0; 
	virtual Object* GetItem(size_t i) = 0;
	virtual Iterator<Object>* CreateIterator() = 0;
};

template <class Object>
class ConcreteIterator : public Iterator<Object> {
 public:
	ConcreteIterator(Aggregate<Object>* aggregate) 
		: current_(0), aggregate_(aggregate) {}

	void Next() override { ++current_; }
	void Previous() override { --current_; }
	bool IsLast() override { return current_ == aggregate_->GetSize(); }
	bool IsFirst() override { return current_ == 0; }
	Object* GetCurrent() override { 
		Object* current_obj = nullptr;
		if (current_ < aggregate_->GetSize() && current_ >= 0) {
			current_obj = aggregate_->GetItem(current_);
		}
		return current_obj;
	}

 private:
	Aggregate<Object>* aggregate_;
	size_t current_;
};

// 对具体列表(如vector, set)编程
// 模板类不能使用宏DISALLOW_COPY_AND_ASSIGN()
template <class Object>
class ConcreteAggregate : public Aggregate<Object> {
 public:
	ConcreteAggregate() {}

	void Add(const Object& object) override {
		list_.push_back(object); // 类对象定义了转移构造函数时可以使用emplace_back
	}

	size_t GetSize() const override { return list_.size(); }
	Object* GetItem(size_t i) override { return &(list_[i]); }
	Iterator<Object>* CreateIterator() override { 
		return new ConcreteIterator<Object>(this);
	}

 private:
	std::vector<Object> list_; // 除非类对象特别大,才在vector中存储对象的指针
};

// 职责链模式
class Request;
class Handler {
 public:
	virtual ~Handler() {}
	void set_successor(Handler* successor) { successor_ = successor; }
	virtual void HandleRequest(Request* request) = 0;

 protected:
	Handler* successor_;
};

class Leader : public Handler {
 public:
	explicit Leader(const std::string& name) : name_(name) {}
	DISALLOW_COPY_AND_ASSIGN(Leader);

	void HandleRequest(Request* request) override;

 private:
	std::string name_;
};

class Inspector : public Handler {
 public:
	explicit Inspector(const std::string& name) : name_(name) {}
	DISALLOW_COPY_AND_ASSIGN(Inspector);

	void HandleRequest(Request* request) override;

 private:
	std::string name_;
};

class Manager : public Handler {
 public:
	explicit Manager(const std::string& name) : name_(name) {}
	DISALLOW_COPY_AND_ASSIGN(Manager);

	void HandleRequest(Request* request) override;

 private:
	std::string name_;
};

class Request {
 public:
	explicit Request(const std::string& name) : name_(name) {}
	DISALLOW_COPY_AND_ASSIGN(Request);

	void set_type(const std::string& type) { type_ = type; }
	void set_content(int content) { content_ = content; }
	std::string get_type() const { return type_; }
	int get_content() const { return content_; }
	std::string get_name() const { return name_; }

 private:
	std::string name_;
	std::string type_;
	int content_;
};

// 模板方法模式
class TemplateProcess {
 public:
	virtual ~TemplateProcess() {}

	void StandardMethod() {
		FixedStep();
		Step1();
		Step2();
	}
	void FixedStep() { printf("fixed step in template.\n"); }

 protected:
	virtual void Step1() = 0; 
	virtual void Step2() = 0; 
}; 

class ConcreteProcessA : public TemplateProcess {
 public:
	ConcreteProcessA() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteProcessA);

 private:
	void Step1() override { printf("ConcreteProcessA.Step1()\n"); }
	void Step2() override { printf("ConcreteProcessA.Step2()\n"); }
};

class ConcreteProcessB : public TemplateProcess {
 public:
	ConcreteProcessB() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteProcessB);

 private:
	void Step1() override { printf("ConcreteProcessB.Step1()\n"); }
	void Step2() override { printf("ConcreteProcessB.Step2()\n"); }
};

// 备忘录模式
struct Memorandum {
	Memorandum(int x, int y, const std::string& label) 
		: x_(x), y_(y), label_(label) {}

	int x_;
	int y_;
	std::string label_;
};

class Originator {
 public:
	Originator() : x_(0), y_(0) {}
	Originator(int x, int y, const std::string& label) 
		: x_(x), y_(y), label_(label) {}
	DISALLOW_COPY_AND_ASSIGN(Originator);

	Memorandum* Save() { return new Memorandum(x_, y_, label_); }
	// 和GetMemory()配合使用,栈对象,用普通指针
	void Restore(Memorandum* memory) {
		x_ = memory->x_;
		y_ = memory->y_;
		label_ = memory->label_;
	} 
	void Show() { printf("%s in pos: (%d, %d)\n", label_.c_str(), x_, y_); }

 private:
	int x_;
	int y_;
	std::string label_;
};

class CareTaker {
 public:
	CareTaker() : index_(-1) {}
	DISALLOW_COPY_AND_ASSIGN(CareTaker);

	Memorandum* GetMemory(int index) { 
		return &(memory_list_[index]);
	}
	// 和Save()配合使用,堆对象,用智能指针管理
	void AddMemory(std::shared_ptr<Memorandum> memory) { 
		memory_list_.push_back(*memory);
	}
	void SetMemory(std::shared_ptr<Memorandum> memory, int index) { 
		memory_list_[index] = *memory; 
	}

	void set_index(int i) { index_ = i; }
	int get_index() const { return index_; }
	int GetSize() const { return memory_list_.size(); }

 private:
	std::vector<Memorandum> memory_list_;
	int index_;
};

class Chess {
 public:
	explicit Chess(CareTaker* caretaker) 
		: caretaker_(caretaker), state_("play") {}
	DISALLOW_COPY_AND_ASSIGN(Chess);

	void Play(int x, int y, const std::string& label);	
	void Undo();
	void Redo();

 private:
	CareTaker* caretaker_;
	std::string state_;
};

// 访问者模式
class Visitor;
class Element {
 public:
	virtual ~Element() {}
	virtual void Accept(Visitor* visitor) = 0;
};

class ConcreteElementA : public Element {
 public:
	ConcreteElementA() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteElementA);

	void Accept(Visitor* visitor) override;
	std::string Get() const { return std::string("element A"); }
};

class ConcreteElementB : public Element {
 public:
	ConcreteElementB() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteElementB);

	void Accept(Visitor* visitor) override;
	std::string Get() const { return std::string("element B"); }
};

class Visitor {
 public:
	virtual ~Visitor() {}
	virtual void Visit(ConcreteElementA* element) = 0;
	virtual void Visit(ConcreteElementB* element) = 0;
};

class ConcreteVisitorA : public Visitor {
 public:
	ConcreteVisitorA() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteVisitorA);

	void Visit(ConcreteElementA* element) override;
	void Visit(ConcreteElementB* element) override;
};

class ConcreteVisitorB : public Visitor {
 public:
	ConcreteVisitorB() {}
	DISALLOW_COPY_AND_ASSIGN(ConcreteVisitorB);

	void Visit(ConcreteElementA* element) override;
	void Visit(ConcreteElementB* element) override;
};

class ObjectStructure {
 public:
	ObjectStructure() {}
	DISALLOW_COPY_AND_ASSIGN(ObjectStructure);

	void Accept(Visitor* visitor);
	void Add(Element* element);
	void Remove(Element* element);

 private:
	std::vector<Element*> element_list_;
};
#endif // CPLUS_PRACTICE_DESIGN_PATTERN_BEHAVIOR_H_
