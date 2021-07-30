#include <bits/stdc++.h>

/**
  @file
*/

/**
  The singleton will be automatically safely instantiated on the first call.
  define constructor body after the define */

#define SINGLETON(Singleton)	\
public:				\
	/* Meyers Singleton realization */ \
	static Singleton& get() {	   \
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


/// Components implementations have to predeclared
struct Sample_component;

struct Visitor {
	virtual string visit(const Sample_component&) const = 0;
};

struct Component {
	virtual string component_accept(Visitor&) const = 0;
};

/// @brief knows only abstract visitor and component
string client_visit(const list<unique_ptr<Component>>& components,
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
struct Sample_component: public Component {
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
	/// @brief one of many visitors
	struct Sample_visitor : public Visitor {
		string visit(const Sample_component& c) const override {
			return string(__func__) + " > " + c.component_method();
		}
	};

	list<unique_ptr<Component>> components;
	components.emplace_back(new Sample_component);
	Sample_visitor v;
	assert(client_visit(components, v) ==
	       "client_visit > component_accept > visit > component_method");
}

struct Abstract_product
{
	virtual int num() { return 0; }
};

struct Generic_client
{
	virtual shared_ptr<Abstract_product> factory_method() = 0;

	int client() {
		auto p(factory_method());
		return p->num();
	};
};

struct Sample_product :
	Abstract_product
{
	int num() override { return 1; }
};

struct Sample_client :
	Generic_client
{
	shared_ptr<Abstract_product> factory_method() override {
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
	virtual shared_ptr<Abstract_product> create() = 0;
};

struct Sample_factory
	: Abstract_factory
{
	virtual shared_ptr<Abstract_product> create() {
		return make_shared<Sample_product>();
	}
};

void abstract_factory_demo()
{
	unique_ptr<Abstract_factory> factory(new Sample_factory());
	auto product = factory->create();
}

int main()
{
	Singleton_demo& singe = Singleton_demo::get();
	visitor_demo();
	factory_method_demo();
	abstract_factory_demo();
}
