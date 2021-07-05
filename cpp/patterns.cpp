#include <memory>
#include <list>

/**
  @file
*/

struct A_component;

struct Visitor {
	virtual string visit(const A_component&) const = 0;
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
struct A_component : public Component {
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
	struct A_visitor : public Visitor {
		string visit(const A_component& c) const override {
			return string(__func__) + " > " + c.component_method();
		}
	};

	list<unique_ptr<Component>> components;
	components.emplace_back(new A_component);
	A_visitor v;
	assert(client_visit(components, v) ==
		"client_visit > component_accept > visit > component_method");
}

struct Abstract {
	virtual shared_ptr<int> factory_method() = 0;
	int client() { return *factory_method(); };
};

struct Implementation : Abstract {
	virtual shared_ptr<int> factory_method() {return make_shared<int>(1); }
};

void factory_method_demo()
{
	Implementation I;
	assert(I.client() == 1);
}

int main()
{
	visitor_demo();
	factory_method_demo();
}
