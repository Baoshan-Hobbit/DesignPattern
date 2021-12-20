#include "design_pattern/behavior.h"

#include <stdio.h>

void TestBehavior() {
  // ConcretePublisher concrete_publisher;
  // PublisherRegister* publisher_register = concrete_publisher.GetPublisherRegister();
  // PublisherContent* publisher_content = concrete_publisher.GetPublisherContent();
  // ConcreteSubscriber concrete_subscriber_a("sub_A", publisher_register, publisher_content);
  // ConcreteSubscriber concrete_subscriber_b("sub_B", publisher_register, publisher_content);
  // concrete_publisher.set_state(5);
  // concrete_publisher.Notify();
  // concrete_publisher.set_state(3);
  // concrete_publisher.Detatch(&concrete_subscriber_b);
  // printf("list size: %d\n", static_cast<int>(concrete_publisher.GetSize()));
  // concrete_publisher.Notify();

  // Receiver receiver;
  // OnCommand on_command(&receiver);
  // OffCommand off_command(&receiver);
  // AlterCommand alter_command(&receiver);
  // Invoker invoker_1;
  // invoker_1.Add(&on_command);
  // invoker_1.Add(&off_command);
  // Invoker invoker_2;
  // invoker_2.Add(&invoker_1);
  // invoker_2.Add(&alter_command);
  // invoker_2.Execute();
  // invoker_2.Remove(&invoker_1);
  // invoker_2.Execute();

  // PolicyA policy_a;
  // PolicyB policy_b;
  // Context context;
  // context.set_policy(&policy_b);
  // context.Run();

  Context context;
  printf("%s\n", context.get_state());
  context.PassiveOpen();
  printf("%s\n", context.get_state());
  context.ActiveOpen();
  printf("%s\n", context.get_state());
  context.SynRecv();
  printf("%s\n", context.get_state());
  context.Close();
  printf("%s\n", context.get_state());

  // ConcreteCollege college_a;
  // ConcreteCollege college_b;
  // ConcreteMediator msg_mediator;
  // msg_mediator.RegisterCollege(1, &college_a);
  // msg_mediator.RegisterCollege(2, &college_b);
  // college_a.SendMsg(2, "hello");

  // ConcreteAggregate<int> nums;
  // for (int i=0; i<5; ++i) { nums.Add(i); }
  // std::unique_ptr<Iterator<int> > it(nums.CreateIterator());
  // while (!it->IsLast()) {
  //  // printf易产生段错误,比如使用%d打印一个空指针的解引用
  //  printf("%d\n", *(it->GetCurrent()));
  //  it->Next();
  //}

  // Request request("zhaosi");
  // request.set_type("pay raise");
  // request.set_content(1900);
  // Leader leader("leader");
  // Inspector inspector("inspector");
  // Manager manager("manager");
  // leader.set_successor(&inspector);
  // inspector.set_successor(&manager);
  // leader.HandleRequest(&request);

  // ConcreteProcessA process_a;
  // ConcreteProcessB process_b;
  // process_a.StandardMethod();
  // process_b.StandardMethod();

  // CareTaker caretaker;
  // Chess chess(&caretaker);
  // chess.Play(1, 2, "ma");
  // chess.Play(2, 4, "che");
  // chess.Play(5, 3, "pao");
  // chess.Undo();
  // chess.Play(6, 8, "shi");
  // chess.Undo();
  // chess.Undo();
  // chess.Redo();
  // chess.Undo();
  // chess.Redo();
  // chess.Play(4, 4, "bing");
  // chess.Undo();

  // ConcreteElementA elem_a;
  // ConcreteElementB elem_b;
  // ObjectStructure elem_set;
  // elem_set.Add(&elem_a);
  // elem_set.Add(&elem_b);
  // ConcreteVisitorA visitor_a;
  // ConcreteVisitorB visitor_b;
  // elem_set.Accept(&visitor_a);
  // elem_set.Accept(&visitor_b);
  // elem_set.Remove(&elem_b);
  // elem_set.Accept(&visitor_a);
}

int main(int argc, char* argv[]) {
  TestBehavior();
  return 0;
}
