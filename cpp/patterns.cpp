#include <bits/stdc++.h>

/**
  @file
  @brief skeleton examples of Design patterns

  See module @ref DP

  Code style:
  Using struct because is it like class with default public members and methods.
*/

/**
  @defgroup DP Design patterns skeleton examples
  @brief [Software design patterns](https://en.wikipedia.org/wiki/Software_design_pattern)

  https://refactoring.guru/design-patterns

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
/** @brief encapsulates arguments. Aka Intent, operation.

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
	Model mod;
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

struct Standalone
/** @brief is wrapped by Bridge. Aka adaptee of Adapter

  It could be a legacy interface playing adaptee role in Adapter pattern
  */
{
	float standalone_method() const {
		return 0.0;
	}
};

struct Interface
/// @brief is a common pure virtual interface
{
	virtual int method() = 0;
	virtual ~Interface() = default;
};

struct Bridge
/// @brief is a wrapper using different from Standalone interface. Aka Adapter
	: public Interface
{
	Bridge(Standalone& s): standalone(s) {}
	int method() override {
		return this->standalone.standalone_method();
	}
private:
	Standalone& standalone;
};

struct Proxy
/// @brief is a wrapper using same as wrapped object Interface
	: public Interface
{
	Proxy(Interface& o): orig(o) {}
	int method() override {
		return this->orig.method();
	}
private:
	Interface& orig;
};

struct Composite
	: public Interface
{
	void add(Interface& o) {
		children.push_front(o);
	}
	int method() override {
		for (Interface& i : children) i.method();
		return 0;
	}
private:
	forward_list<reference_wrapper<Interface>> children;
};

/**
  @defgroup factories Factories

  @{
  */

struct Generic_client
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
	int method() override { return 1; }
};

struct Sample_client
	: Generic_client
{
	unique_ptr<Interface> factory_method() override {
		return make_unique<Sample_product>();
	}
};

void factory_method_demo()
{
	Sample_client C;
	assert(C.client() == 1);
}

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

void abstract_factory_demo()
{
	unique_ptr<Abstract_factory> factory(new Sample_factory());
	auto product = factory->create();
}

/// @}

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

int main()
{
	Singleton_demo& singe = Singleton_demo::get();
	View ob;
	Model mod;
	mod.register_observer(ob);
	mod.notify_observers();
	Controller ctrl(mod);
	ctrl.command(Command());
	Command cmnd;
	ctrl.command(cmnd);

	Chain_of_responsibility chain;
	chain.register_handler(Handler());
	chain.handle(cmnd);

	Standalone sa;
	Bridge br(sa);
	br.method();
	Proxy p(br);
	p.method();
	Composite comp;
	comp.add(p);
	comp.method();

	visitor_demo();
	factory_method_demo();
	abstract_factory_demo();
}

/// @}
