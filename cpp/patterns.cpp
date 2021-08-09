#include <bits/stdc++.h>

/**
  @file
*/

/**
  @defgroup DP Design patterns examples
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
/// @brief encapsulates arguments. Aka Intent, operation.
{};

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

/// Components implementations have to predeclared
struct Sample_component;

struct Visitor
/// @brief is pure virtual a visitor of Sample_component
{
	virtual string visit(const Sample_component&) const = 0;
	virtual ~Visitor() = default;
};

struct Component
/// @brief is pure virtual a Visitor acceptor
{
	virtual string component_accept(Visitor&) const = 0;
	virtual ~Component() = default;
};

/// @brief knows only abstract visitor and component
string client_visit(const forward_list<unique_ptr<Component>>& components,
		    Visitor& visitor)
{
	string res;
	for (auto&& comp : components) {
		res += string(__func__) + " > " + comp->component_accept(visitor);
		//assert(rc);
	}
	//assert(rc);
	return res;
}

/// @brief one of many components
struct Sample_component
	: public Component
{
	string component_accept(Visitor& visitor) const override {
		return string(__func__) + " > " + visitor.visit(*this);
	}
	/// @brief is not virtual
	string component_method() const {
		return __func__;
	}
};

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
		children.push_front(&o);
	}
	int method() override {
		for (Interface* i : children) i->method();
		return 0;
	}
private:
	forward_list<Interface*> children;
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
	/// @brief one of many visitors
	struct Sample_visitor
		: public Visitor {
		string visit(const Sample_component& c) const override {
			return string(__func__) + " > " + c.component_method();
		}
	};

	forward_list<unique_ptr<Component>> components;
	components.emplace_front(new Sample_component);
	Sample_visitor v;
	assert(client_visit(components, v) ==
	       "client_visit > component_accept > visit > component_method");
}

/**
  @defgroup factories Factories

  @{
  */

struct Generic_client
{
	virtual shared_ptr<Interface> factory_method() = 0;

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
	shared_ptr<Interface> factory_method() override {
		return make_shared<Sample_product>();
	}
};

void factory_method_demo()
{
	Sample_client C;
	assert(C.client() == 1);
}

struct Abstract_factory
{
	virtual shared_ptr<Interface> create() = 0;
};

struct Sample_factory
	: Abstract_factory
{
	virtual shared_ptr<Interface> create() {
		return make_shared<Sample_product>();
	}
};

void abstract_factory_demo()
{
	unique_ptr<Abstract_factory> factory(new Sample_factory());
	auto product = factory->create();
}

/// @}
/// @}

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
