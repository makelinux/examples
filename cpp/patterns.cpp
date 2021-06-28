#include <memory>
#include <list>

#define trace(end) cerr << __func__ << end;

/**
  @file

  Call hierarchy:

  visitor_demo
  	client_visit
		component_accept
			visit
				component_method
*/

struct A_component;

struct Visitor {
	virtual int visit(const A_component&) const = 0;
};

struct Component {
	virtual int component_accept(Visitor&) const = 0;
};

/// @brief knows only abstract visitor and component
void client_visit(const list<unique_ptr<Component>>& components,
		  Visitor& visitor)
{
	int rc = 0;
	trace(" > ");
	for (auto&& comp : components) {
		rc = comp->component_accept(visitor);
		assert(rc);
	}
	assert(rc);
}

/// @brief one of many components
struct A_component : public Component {
	int component_accept(Visitor& visitor) const override {
		trace(" > ");
		return visitor.visit(*this);
	}
	/// @brief is not virtual
	int component_method() const {
		trace("\n");
		return 1;
	}
};

void visitor_demo()
{
	trace(" > ");
	/// @brief one of many visitors
	struct A_visitor : public Visitor {
		int visit(const A_component& c) const override {
			trace(" > ");
			return c.component_method();
		}
	};

	list<unique_ptr<Component>> components;
	components.emplace_back(new A_component);
	A_visitor v;
	client_visit(components, v);
}

int main()
{
	trace(" > ");
	visitor_demo();
}
