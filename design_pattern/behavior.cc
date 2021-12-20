#include "design_pattern/behavior.h"
#include <stdio.h>
#include <map>
#include <string>

void PublisherRegister::Attatch(Subscriber* subscriber) {
  subscriber_list_.push_back(subscriber);
}
void PublisherRegister::Detatch(Subscriber* subscriber) {
  for (auto it = subscriber_list_.begin(); it != subscriber_list_.end(); ++it) {
    if (*it == subscriber) {
      subscriber_list_.erase(it);
      return;
    }
  }
}
void PublisherRegister::Notify() {
  for (auto it = subscriber_list_.begin(); it != subscriber_list_.end(); ++it)
    (*it)->Update();
}
Subscriber::Subscriber(PublisherRegister* publisher_register)
    : publisher_register_(publisher_register) {
  publisher_register_->Attatch(this);
}
Subscriber::~Subscriber() {
  publisher_register_->Detatch(this);
}
void ConcretePublisher::set_state(int state) {
  state_ = state;
}
int ConcretePublisher::get_state() const {
  return state_;
}
ConcreteSubscriber::ConcreteSubscriber(const std::string& name,
                                       PublisherRegister* publisher_register,
                                       PublisherContent* publisher_content)
    : name_(name), Subscriber(publisher_register), publisher_content_(publisher_content) {
}
void ConcreteSubscriber::Update() {
  int state = publisher_content_->get_state();
  printf("subscriber name: %s, publisher state: %d\n", name_.c_str(), state);
}

void Receiver::On() {
  printf("Receiver on.\n");
}
void Receiver::Off() {
  printf("Receiver off.\n");
}
void Receiver::Alter() {
  printf("Receiver alter.\n");
}
void OnCommand::Execute() {
  receiver_->On();
}
void OffCommand::Execute() {
  receiver_->Off();
}
void AlterCommand::Execute() {
  receiver_->Alter();
}
void Invoker::Add(Command* command) {
  command_list_.push_back(command);
}
void Invoker::Remove(Command* command) {
  for (auto it = command_list_.begin(); it != command_list_.end(); ++it) {
    if (*it == command) {
      command_list_.erase(it);
      return;
    }
  }
}
void Invoker::Execute() {
  for (auto it = command_list_.begin(); it != command_list_.end(); ++it)
    (*it)->Execute();
}

// void Context::set_policy(Policy* policy) { policy_ = policy; }
// void Context::Run() { policy_->Execute(); }
// void PolicyA::Execute() { printf("policy A execute.\n"); }
// void PolicyB::Execute() { printf("policy B execute.\n"); }

Context::Context() : state_(&ClosedState::GetInstance()) {
  // state_ = &ClosedState::GetInstance();
}
void Context::PassiveOpen() {
  if (state_->get_name() == "closed") {
    state_->OnPassiveOpen(this);
  } else {
    printf("wrong state, should be CLOSED.\n");
  }
}
void Context::ActiveOpen() {
  if (state_->get_name() == "closed") {
    state_->OnActiveOpen(this);
  } else {
    printf("wrong state, should be CLOSED.\n");
  }
}
void Context::SynRecv() {
  if (state_->get_name() == "listen") {
    state_->OnSynRecv(this);
  } else {
    printf("wrong state, should be LISTEN.\n");
  }
}
void Context::Close() {
  state_->OnClose(this);
}
void ClosedState::OnPassiveOpen(Context* context) {
  State* state_listen = &ListenState::GetInstance();
  context->set_state(state_listen);
}
void ClosedState::OnActiveOpen(Context* context) {
  State* state_syn_sent = &SynSentState::GetInstance();
  context->set_state(state_syn_sent);
}
void ListenState::OnSynRecv(Context* context) {
  State* state_syn_recv = &SynRecvState::GetInstance();
  context->set_state(state_syn_recv);
}
void SynRecvState::OnClose(Context* context) {
  State* state_close = &ClosedState::GetInstance();
  context->set_state(state_close);
}
void SynSentState::OnClose(Context* context) {
  State* state_close = &ClosedState::GetInstance();
  context->set_state(state_close);
}

void Mediator::RegisterCollege(int id, College* college) {
  std::map<int, College*>::const_iterator it = college_list_.find(id);
  if (it == college_list_.end()) {
    college_list_.insert(std::make_pair(id, college));
    college->set_mediator(this);
  } else {
    printf("%d already registered.\n", id);
  }
}
void ConcreteMediator::Operate(int id, const std::string& msg) {
  std::map<int, College*>::const_iterator it = college_list_.find(id);
  if (it != college_list_.end()) {
    College* college_recv = it->second;
    college_recv->RecvMsg(msg);
  } else {
    printf("college(receiver) %d not registered\n", id);
  }
}
void ConcreteCollege::SendMsg(int id, const std::string& msg) {
  mediator_->Operate(id, msg);
}
void ConcreteCollege::RecvMsg(const std::string& msg) {
  printf("[recv] %s\n", msg.c_str());
}

void Leader::HandleRequest(Request* request) {
  if (request->get_type() == "vocation" && request->get_content() < 3) {
    printf("%s approved: %s request %d vocation\n",
           name_.c_str(),
           request->get_name().c_str(),
           request->get_content());
  } else {
    if (successor_ != nullptr)
      successor_->HandleRequest(request);
  }
}
void Inspector::HandleRequest(Request* request) {
  if (request->get_type() == "vocation" && request->get_content() > 3 &&
      request->get_content() < 7) {
    printf("%s approved: %s request %d vocation\n",
           name_.c_str(),
           request->get_name().c_str(),
           request->get_content());
  } else {
    if (successor_ != nullptr)
      successor_->HandleRequest(request);
  }
}
void Manager::HandleRequest(Request* request) {
  if (request->get_type() == "vocation") {
    // printf容易忘记\n和string转char*
    printf("%s approved: %s request %d vocation\n",
           name_.c_str(),
           request->get_name().c_str(),
           request->get_content());
  } else if (request->get_type() == "pay raise") {
    if (request->get_content() < 1000) {
      printf("%s approved: %s request %d pay raise\n",
             name_.c_str(),
             request->get_name().c_str(),
             request->get_content());
    } else {
      printf("%s denied: %s request %d pay raise\n",
             name_.c_str(),
             request->get_name().c_str(),
             request->get_content());
    }
  } else {
    if (successor_ != nullptr)
      successor_->HandleRequest(request);
  }
}

void Chess::Play(int x, int y, const std::string& label) {
  Originator originator(x, y, label);
  std::shared_ptr<Memorandum> memory(originator.Save());
  printf("Play\n");
  originator.Show();
  int index = caretaker_->get_index();
  if (index == caretaker_->GetSize() - 1) {
    caretaker_->AddMemory(memory);
  } else {
    caretaker_->SetMemory(memory, index + 1);
  }
  caretaker_->set_index(index + 1);
  state_ = "play";
}

void Chess::Undo() {
  int current = caretaker_->get_index();
  Originator originator;
  Memorandum* memory = caretaker_->GetMemory(current - 1);
  originator.Restore(memory);
  printf("Undo\n");
  originator.Show();
  caretaker_->set_index(current - 1);
  state_ = "undo";
}

void Chess::Redo() {
  if (state_ == "undo") {
    int current = caretaker_->get_index();
    Originator originator;
    originator.Restore(caretaker_->GetMemory(current + 1));
    printf("Redo\n");
    originator.Show();
    caretaker_->set_index(current + 1);
    state_ = "redo";
  } else {
    printf("must follow undo\n");
  }
}

void ConcreteVisitorA::Visit(ConcreteElementA* element) {
  std::string content = element->Get();
  printf("A visit %s.\n", content.c_str());
}
void ConcreteVisitorA::Visit(ConcreteElementB* element) {
  std::string content = element->Get();
  printf("A visit %s.\n", content.c_str());
}
void ConcreteVisitorB::Visit(ConcreteElementA* element) {
  std::string content = element->Get();
  printf("B visit %s.\n", content.c_str());
}
void ConcreteVisitorB::Visit(ConcreteElementB* element) {
  std::string content = element->Get();
  printf("B visit %s.\n", content.c_str());
}
void ConcreteElementA::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
void ConcreteElementB::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
void ObjectStructure::Accept(Visitor* visitor) {
  for (std::vector<Element*>::const_iterator it = element_list_.begin(); it != element_list_.end();
       ++it)
    (*it)->Accept(visitor);
}
void ObjectStructure::Add(Element* element) {
  element_list_.push_back(element);
}
void ObjectStructure::Remove(Element* element) {
  for (std::vector<Element*>::const_iterator it = element_list_.begin(); it != element_list_.end();
       ++it) {
    if (*it == element) {
      element_list_.erase(it);
      return;
    }
  }
}
