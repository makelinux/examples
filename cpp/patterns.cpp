#include <bits/stdc++.h>
using namespace std;

/**
  @file
  @brief skeleton examples of Design patterns

  © 2021 Constantine Shulyupin

  See module @ref DP

  Code style:
  Using struct because is it like class with default public members and methods.
  Less is more. Skeleton code with minimal optional code and duplications.
  Each word "Sample" in an inventers assumes multiple examples like Sample1, Sample2 ... SampleN

*/

/**
  @defgroup DP Design patterns skeleton examples
  @brief [Software design patterns](https://en.wikipedia.org/wiki/Software_design_pattern)

  https://refactoring.guru/design-patterns

  DP help to conform to [SOLID principles](https://en.wikipedia.org/wiki/SOLID):
  - [<b>S</b>ingle-responsibility](https://en.wikipedia.org/wiki/Single-responsibility_principle)
   - high [cohesion](https://en.wikipedia.org/wiki/Cohesion_(computer_science))
  - [<b>O</b>pen-closed](https://en.wikipedia.org/wiki/Open%E2%80%93closed_principle)
   - open for extension
   - but closed for modification
  - [<b>L</b>iskov substitution](https://en.wikipedia.org/wiki/Liskov_substitution_principle)
   - [composition over inheritance](https://en.wikipedia.org/wiki/Composition_over_inheritance)
  - [<b>I</b>nterface segregation](https://en.wikipedia.org/wiki/Interface_segregation_principle)
   - use many specific interfaces
  - [<b>D</b>ependency inversion](https://en.wikipedia.org/wiki/Dependency_inversion_principle)
   - don't depend on implementations
   - depend on interfaces
   - [Loose coupling](https://en.wikipedia.org/wiki/Loose_coupling)
  @{
  */

struct Interface
/// @brief is a common pure virtual interface
{
	virtual int method() = 0;
	virtual ~Interface() = default;
};

/**
  @defgroup CP Creational
  @brief [Creational patterns](https://en.wikipedia.org/wiki/Creational_pattern)

  https://refactoring.guru/design-patterns/creational-patterns

  @{
  */

/**
  The singleton will be automatically safely instantiated on the first call.

  Define constructor body after the define */

#define SINGLETON(Singleton)	\
public:				\
	/* Meyers Singleton realization */ \
	static Singleton& get() {	\
		static Singleton me; 	\
		return me; 		\
	}				\
	Singleton(const Singleton&) = delete; 			\
	Singleton& operator=(const Singleton&) = delete; 	\
	Singleton(Singleton&&) = delete;			\
	Singleton& operator=(Singleton&&) = delete;		\
private: \
	Singleton_demo()

struct Singleton_demo
{
	SINGLETON(Singleton_demo) { };
};

struct Factory_method_demo
{
	virtual unique_ptr<Interface> factory_method() = 0;

	int client() {
		auto p(factory_method());
		return p->method();
	};
};

struct Sample_product
	: Interface
{
	int data;
	int method() override { return data; }
	Sample_product(int d = 0) : data(d) {}
};

struct Sample_factory_method_demo
	: Factory_method_demo
{
	unique_ptr<Interface> factory_method() override {
		return make_unique<Sample_product>(123);
	}
};

struct Abstract_factory
{
	virtual unique_ptr<Interface> create() = 0;
};

struct Sample_factory
	: Abstract_factory
{
	virtual unique_ptr<Interface> create() {
		return make_unique<Sample_product>();
	}
};

struct Prototype
/// @brief is the factory of himself
	: Abstract_factory, Interface
{

	int method() override { return 1; }
	unique_ptr<Interface> create() override {
		auto clone = new Prototype(*this);
		return unique_ptr<Interface>(clone);
	}
};

struct Builder
{
	int data = 0;
	Builder& add(int i) {
		data += i;
		return *this;
	}

	Interface& create()
	{
		return *new Sample_product(data);
	}
};

void creational_patterns_demo()
{
	Singleton_demo& singe = Singleton_demo::get();
	unique_ptr<Abstract_factory> factory(new Sample_factory());
	auto product = factory->create();
	Prototype p1;
	auto p2 = p1.create();
	Sample_factory_method_demo C;
	assert(C.client() == 123);
	Interface& p = Builder().add(1).add(20).create();
	assert(p.method() == 21);
	delete &p;
}

/// @} CP

/**
  @defgroup SP Structural
  @brief [Structural patterns](https://en.wikipedia.org/wiki/Structural_pattern)

  https://refactoring.guru/design-patterns/structural-patterns

  @{
  */

struct Standalone
/** @brief is wrapped by Bridge. AKA adaptee of Adapter

  It could be a legacy interface playing adaptee role in Adapter pattern
  */
{
	float standalone_method() const {
		return 1.01;
	}
};

struct Bridge
/// @brief is a wrapper using different from Standalone interface. AKA Adapter
	: public Interface
{
	Bridge(Standalone& s): standalone(s) {
//		trace(typeid(*this).name());
	}
	int method() override {
		return this->standalone.standalone_method();
	}
private:
	Standalone& standalone;
};

struct Proxy
/// @brief is a opaque wrapper with same as wrapped object Interface
	: public Interface
{
	Proxy(Interface& o): subject(o) {}
	int method() override {
		return this->subject.method();
	}
private:
	Interface& subject;
};
};

struct Composite
	: public Interface
{
	void add(Interface& o) {
		children.push_front(o);
	}
	int method() override {
		//trace();
		for (Interface& i : children) i.method();
		return 0;
	}
private:
	forward_list<reference_wrapper<Interface>> children;
};

void structural_patterns_demo()
{
	Standalone sa;
	Bridge br(sa);
	br.method();
	Proxy p(br);
	p.method();
	Composite comp;
	comp.add(p);
	comp.method();
}

/// @} SP

/**
  @defgroup BP Behavioral
  @brief [Behavioral patterns](https://en.wikipedia.org/wiki/Behavioral_pattern)

  https://refactoring.guru/design-patterns/behavioral-patterns

  @{
  */

/**
  Credit: [observer](https://cpppatterns.com/patterns/observer.html)
*/

struct Observer
/// @brief is pure virtual notification observer of a Model
{
	virtual void notify() = 0;
	virtual ~Observer() = default;
};

struct View
/// @brief is concrete Observer
	: public Observer
{
	void notify() override { }
};

struct Command
/** @brief encapsulates arguments. AKA Intent, operation.

  [Command pattern](https://en.wikipedia.org/wiki/Command_pattern)

  https://refactoring.guru/design-patterns/command
 */
{ };

struct Model
/// @brief is part of MVC with View and Controller
{
	void register_observer(Observer& o) {
		observers.push_front(o);
	}
	void notify_observers() {
		for (Observer& o : observers) o.notify();
	}
	int command(const Command& cmnd) { return 0; }
	int command(Command&& cmnd) { return 0; }
private:
	forward_list<reference_wrapper<Observer>> observers;
};

struct Controller
/// @brief is part of MVC with Model and View
{
	Model& mod; // can be many models
	Controller(Model& s) : mod(s) { };
	int command(const Command& cmnd) {
		return mod.command(cmnd);
	}
	int command(Command&& cmnd) {
		return mod.command(cmnd);
	}
};

/**
  @defgroup visitor Visitor
  @{
  */

struct Visitor
/// @brief is a pure virtual visitor of Sample_component and other specific components
{
	struct Sample_component;
	virtual string visit(const Sample_component&) const = 0;
	virtual ~Visitor() = default;
};

struct Component
/// @brief accepts a pure virtual Visitor
{
	virtual string component_accept(Visitor&) const = 0;
	virtual ~Component() = default;
};

string client_visit(const forward_list<unique_ptr<Component>>& components,
		    Visitor& visitor)
/// @brief knows only virtual visitor and component
{
	string res;
	for (auto&& comp : components) {
		res += string(__func__) + " > " + comp->component_accept(visitor);
		//assert(rc);
	}
	//assert(rc);
	return res;
}

struct Visitor::Sample_component
	: public Component
/// @brief one of many components
{
	string component_accept(Visitor& visitor) const override {
		return string(__func__) + " > " + visitor.visit(*this);
	}
	/// @brief is not virtual
	string component_method() const {
		return __func__;
	}
};

/**
  Call hierarchy:

	visitor_demo
		client_visit
			component_accept
				visit
					component_method
*/

void visitor_demo()
{
	/// @brief is one of many specific visitors with custom method visit
	struct Sample_visitor
		: public Visitor {
		string visit(const Visitor::Sample_component& c) const override {
			return string(__func__) + " > " + c.component_method();
		}
	};

	forward_list<unique_ptr<Component>> components;
	components.emplace_front(new Visitor::Sample_component);
	Sample_visitor v;
	assert(client_visit(components, v) ==
	       "client_visit > component_accept > visit > component_method");
}

/// @} visitor

struct Handler
/// @brief is a virtual command handler of Chain_of_responsibility
{
	/// Specific handler can process a command and return non-negative
	virtual int handle(Command) { return -1; };
	virtual ~Handler() = default;
};

struct Chain_of_responsibility
	: Handler
/** @brief list based implementation without recursion

  [Chain-of-responsibility pattern](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern)

  https://refactoring.guru/design-patterns/chain-of-responsibility

 */
{
	void register_handler(Handler&& h, bool front = false) {
		if (front)
			handlers.push_front(h);
		else
			handlers.push_back(h);
	}
	int handle(Command arg) override {
		int rc = -1;
		for (Handler& h : handlers)
			if ((rc = h.handle(arg)) >= 0)
				return rc;
		return rc;
	}
private:
	list<reference_wrapper<Handler>> handlers;
};

struct Message { };

/**
  [Mediator_pattern](https://en.wikipedia.org/wiki/Mediator_pattern)

  https://refactoring.guru/design-patterns/mediator
  */

struct Mediator;

struct Member
{
	Mediator* mediator;
	void send(Message& );
	void receive(Message& ) { }
};

struct Mediator
{
	void register_member(Member& m) {
		m.mediator = this;
		members.push_front(m);
	}
	void receive(Message& msg) {
		for (Member& m : members) m.receive(msg);
	}
	forward_list<reference_wrapper<Member>> members;
};

void Member::send(Message& m)
{
	mediator->receive(m);
}

void mediator_demo()
{
	Member m1, m2;
	Mediator md;
	md.register_member(m1);
	md.register_member(m2);
	Message msg;
	m1.send(msg);
}

void behavioral_patterns_demo()
{
	View view;
	Model mod;
	mod.register_observer(view);
	mod.notify_observers();
	Controller ctrl(mod);
	ctrl.command(Command());
	Command cmnd;
	ctrl.command(cmnd);

	Chain_of_responsibility chain;
	chain.register_handler(Handler());
	chain.handle(cmnd);

	visitor_demo();
	mediator_demo();
}

/// @} BP

int main()
{
	creational_patterns_demo();
	structural_patterns_demo();
	behavioral_patterns_demo();
}

/// @}
