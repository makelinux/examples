#include <bits/stdc++.h>

using namespace std;

/**
  @file
  @brief skeleton C++ examples of OOP and Design patterns

  © 2021 Constantine Shulyupin

  Patterns help to conform to [SOLID principles](https://en.wikipedia.org/wiki/SOLID):
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


  Coding style:
  Using struct because is it like class with default public members and methods.
  Less is more. Skeleton code with minimal optional code and duplications.
  Each word "Sample" in an inventer assumes multiple instances like Sample1, Sample2 ... SampleN

  Contents
  - @ref OOP
  - @ref DP

*/

/**
  @defgroup OOP C++ OOP patterns
  @brief some examples in C++

  Four Pillars of
  [Object-oriented_programming](https://en.wikipedia.org/wiki/Object-oriented_programming):
  - [Abstraction](https://en.wikipedia.org/wiki/Abstraction_(computer_science))
  - [Encapsulation](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming))
  - [Inheritance](https://en.wikipedia.org/wiki/Inheritance_(object-oriented_programming))
  - [Polymorphism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science))

  [object-oriented-programming-in-cpp](https://www.geeksforgeeks.org/object-oriented-programming-in-cpp)

  [class](https://en.cppreference.com/w/cpp/language/class)

  [derived_class](https://en.cppreference.com/w/cpp/language/derived_class)

  [abstract_class](https://en.cppreference.com/w/cpp/language/abstract_class)

  [shared_lock](https://en.cppreference.com/w/cpp/thread/shared_lock)

  Three independent interfaces
  Setter_interface, Getter_interface and Change_interface demonstrate
  [Interface segregation](https://en.wikipedia.org/wiki/Interface_segregation_principle)

  [Use multiple inheritance to represent multiple distinct interfaces](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces)

  @{
  */

struct Module { };

/// [Object composition](https://en.wikipedia.org/wiki/Object_composition)
struct Composition {
    Module m1, m2;
};

/** [Aggregation](https://en.wikipedia.org/wiki/Object_composition#Aggregation)
  by reference
*/
struct Reference {
    Module &m1, &m2;
    Reference() = default;
};

/** [Pointer](https://en.wikipedia.org/wiki/Pointer_(computer_programming)#C_and_C++)
  is also can be used for aggregation
  */
struct Pointer {
    Module* ptr;
    shared_ptr<Module> sm;
    unique_ptr<Module> um;
};

/// [Associations](https://en.wikipedia.org/wiki/Association_(object-oriented_programming))
void associations_demo()
{
    Module m1, m2;
    Reference r { m1, m2 };

    Pointer p { &m1 };
    // References can't be changed or zeroed like pointers during runtime.
    p.ptr = nullptr;
}

/// @brief is a sample of setter abstract interface for Synchronized_encapsulated_value
template <typename ValueType>
struct Setter_interface {
    virtual void set(ValueType i) = 0;
    virtual ~Setter_interface() = default;
};

template <typename ValueType>
struct Getter_interface
/// @brief is a sample of getter abstract interface for Synchronized_encapsulated_value
{
    virtual ValueType get() const = 0;
    virtual ~Getter_interface() = default;
};

template <typename ValueType>
struct Change_interface
/// @brief is a sample of changer abstract interface for Synchronized_encapsulated_value
{
    virtual void change(ValueType c) = 0;
    virtual ~Change_interface() = default;
};

template <typename ValueType>
class Synchronized_encapsulated_value
    /**
      @brief [encapsulating](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming))
             class with only public accessor and [mutator](https://en.wikipedia.org/wiki/Mutator_method) intrfaces

      Classes by default are private. This class doesn't contain public members.

      See also:
      - [Boost synchronized values](https://www.boost.org/doc/libs/release/doc/html/thread/sds.html#thread.sds.synchronized_valuesxxx)
      - [boost/thread/synchronized_value.hpp](https://github.com/boostorg/thread/blob/HEAD/include/boost/thread/synchronized_value.hpp)
      */
    : public Setter_interface<ValueType>,
      public Getter_interface<ValueType>,
      public Change_interface<ValueType> {
    void set(ValueType i) override
    {
        scoped_lock writer_lock(mtx);
        value = i;
    }

    ValueType get() const override
    {
        shared_lock reader_lock(mtx); /// [reader writer locks](https://www.modernescpp.com/index.php/reader-writer-locks)
        return value;
    }

    void change(ValueType c) override
    {
        scoped_lock writer_lock(mtx);
        value += c;
    }

    mutable shared_mutex mtx; ///< [shared_mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex)
    ValueType value;
};

void synchronized_encapsulated_value()
/**
  Lambda expression 'client' demonstrates [Dependency inversion](https://en.wikipedia.org/wiki/Dependency_inversion_principle) -
  it doesn't depends from implementation Synchronized_encapsulated_value but depends only from interfaces.
  */

{
    auto client = [](Setter_interface<int>& s, Getter_interface<int>& g) {
        s.set(1);
        assert(g.get() == 1);
    };
    Synchronized_encapsulated_value<int> v;
    Setter_interface<int>& s = v;
    Getter_interface<int>& g = v;
    client(s, g);

    auto client2 = [](Setter_interface<string>& s, Getter_interface<string>& g) {
        s.set("abc");
        assert(g.get() == "abc");
    };
    Synchronized_encapsulated_value<string> v2;
    Setter_interface<string>& s2(v2);
    Getter_interface<string>& g2(v2);
    Change_interface<string>& c2(v2);
    client2(s2, g2);
    c2.change("de");
    assert(g2.get() == "abcde");
}

void oop_demo()
{
    associations_demo();
    synchronized_encapsulated_value();
}

/// @}

/**
  @defgroup DP Design patterns skeleton examples
  @brief [Software design patterns](https://en.wikipedia.org/wiki/Software_design_pattern)

  https://refactoring.guru/design-patterns

  [C++ Programming: Code patterns design](https://en.wikibooks.org/wiki/C++_Programming/Code/Design_Patterns)

  Disclaimer:

  Example code below for simplicity doesn't utilize synchronization,
  privatization and other administrative functions.

  Don't forget to add locking, synchronization, encapsulation, privatization,
  protection manually where it is required when using examples below.

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

#define SINGLETON(Singleton)                         \
public:                                              \
    /* Meyers Singleton realization */               \
    static Singleton& instance()                     \
    {                                                \
        static Singleton me;                         \
        return me;                                   \
    }                                                \
    Singleton(const Singleton&) = delete;            \
    Singleton& operator=(const Singleton&) = delete; \
    Singleton(Singleton&&) = delete;                 \
    Singleton& operator=(Singleton&&) = delete;      \
                                                     \
private:                                             \
    Singleton()

struct Singleton_demo {
    SINGLETON(Singleton_demo) {};
};

struct Factory_method_demo {
    virtual unique_ptr<Interface> factory_method() = 0;

    int client()
    {
        auto p(factory_method());
        return p->method();
    };
};

struct Sample_product
    : Interface {
    int data;
    int method() override { return data; }
    Sample_product(int d = 0)
        : data(d)
    {
    }
};

struct Sample_factory_method_demo
    : Factory_method_demo {
    unique_ptr<Interface> factory_method() override
    {
        return make_unique<Sample_product>(123);
    }
};

struct Abstract_factory {
    virtual unique_ptr<Interface> create() = 0;
};

struct Sample_factory
    : Abstract_factory {
    virtual unique_ptr<Interface> create()
    {
        return make_unique<Sample_product>();
    }
};

struct Prototype
    /// @brief is the factory of himself
    : Abstract_factory,
      Interface {

    int method() override { return 1; }
    unique_ptr<Interface> create() override
    {
        auto clone = new Prototype(*this);
        return unique_ptr<Interface>(clone);
    }
};

struct Builder {
    int data = 0;
    Builder& add(int i)
    {
        data += i;
        return *this;
    }

    Builder& operator<<(int i) { return add(i); }

    Interface& create()
    {
        return *new Sample_product(data);
    }
};

void creational_patterns_demo()
{
    Singleton_demo& singe = Singleton_demo::instance();

    unique_ptr<Abstract_factory> factory(new Sample_factory());

    auto product = factory->create();

    Prototype p1;
    auto p2 = p1.create();

    Sample_factory_method_demo C;
    assert(C.client() == 123);

    Interface& p = (Builder().add(1).add(2) << 3 << 4).create();
    assert(p.method() == 10);
    // strstream looks like string builder
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
    float standalone_method() const
    {
        return 1.01;
    }
};

struct Bridge
    /// @brief is a wrapper using different from Standalone interface. AKA Adapter
    : public Interface {
    Bridge(Standalone& s)
        : standalone(s)
    {
    }
    int method() override
    {
        return this->standalone.standalone_method();
    }

private:
    Standalone& standalone;
};

struct Proxy
    /// @brief is a opaque wrapper with same as wrapped object Interface
    : public Interface {
    Proxy(Interface& o)
        : subject(o)
    {
    }
    int method() override
    {
        return this->subject.method();
    }

private:
    Interface& subject;
};

struct Decorator
    /// @brief is a partial wrapper of an object with same as wrapped object Interface
    : public Interface {
    Decorator(Interface& o)
        : subject(o)
    {
    }
    int method() override
    {
        return 100 + this->subject.method();
    }
    Interface& subject; // decorated object is public
};

struct Composite
    : public Interface {
    int method() override
    {
        for (Interface& i : children)
            i.method();
        return 0;
    }
    forward_list<reference_wrapper<Interface>> children;
};

void structural_patterns_demo()
{
    Standalone sa;
    Bridge br(sa);
    br.method();
    Proxy p(br);
    Decorator dec(br);
    dec.method();
    dec.subject.method();
    p.method();
    Composite comp;
    comp.children.push_front(p);
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

struct Subject;

struct Observer
/// @brief is virtual observer of a Subject
{
    /// @brief without arguments
    virtual void notify() {};
    /// @brief with the only Subject argument
    virtual void update(Subject& subject) {};
    virtual ~Observer() = default;
};

struct Subject
/// @brief of Observer
{
    void notify_observers()
    {
        for (Observer& o : observers) {
            o.notify();
            o.update(*this);
        }
    }
    forward_list<reference_wrapper<Observer>> observers;
};

void observer_demo()
{
    Observer o;
    Subject s;
    s.observers.push_front(o);
    s.notify_observers();
}

/**
  @defgroup PS Publish–subscribe pattern
  @brief [Publish–subscribe pattern](https://en.wikipedia.org/wiki/Publish–subscribe_pattern)

  @{
  */

struct Message { };

struct Subscriber {
    void message(Message& m) {};
};

struct Publisher {
    map<string, forward_list<reference_wrapper<Subscriber>>> topic_subscribers;

    void publish(const string& topic, Message& m)
    {
        for (Subscriber& s : topic_subscribers[topic])
            s.message(m);
    }
};

void publisher_subscriber_demo()
{
    Subscriber sub;
    Publisher pub;
    pub.topic_subscribers["sample_topic"].push_front(sub);
    Message m;
    pub.publish("sample_topic", m);
}

/// @} PS

/**
  [Mediator_pattern](https://en.wikipedia.org/wiki/Mediator_pattern)

  https://refactoring.guru/design-patterns/mediator
  */

struct Mediator;

struct Member {
    Mediator* mediator;
    void send(Message&);
    void receive(Message&) { }
};

struct Mediator {
    void register_member(Member& m)
    {
        m.mediator = this;
        members.push_front(m);
    }
    void dispatch(Message& msg)
    {
        for (Member& m : members)
            m.receive(msg);
    }
    forward_list<reference_wrapper<Member>> members;
};

void Member::send(Message& m)
{
    mediator->dispatch(m);
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

struct Command
/** @brief encapsulates arguments. AKA Intent, operation.

  [Command pattern](https://en.wikipedia.org/wiki/Command_pattern)

  https://refactoring.guru/design-patterns/command/cpp/example
 */
{
    virtual int execute() { return -1; };
};

/**
  @defgroup visitor Visitor
  @brief [Visitor pattern](https://en.wikipedia.org/wiki/Visitor_pattern)

  https://refactoring.guru/design-patterns/visitor/cpp/example
  @{
  */

struct Abstract_visitor;

struct Component
/// @brief accepts a pure virtual Abstract_visitor
{
    virtual string component_accept(Abstract_visitor&) const = 0;
    virtual ~Component() = default;
};

string client_visit(const forward_list<unique_ptr<Component>>& components,
    const forward_list<unique_ptr<Abstract_visitor>>& visitors)
/// @brief knows only virtual visitor and component
{
    string res;
    for (auto&& v : visitors)
        for (auto&& c : components) {
            assert(typeid(c) != typeid(Component));
            res += string(__func__) + " > " + c->component_accept(*v.get());
        }
    return res;
}

struct Sample_component;
struct Abstract_visitor
/// @brief is a pure virtual visitor of Sample_component and other specific components
{
    /// overloaded function for each component subtype
    virtual string visit(const Sample_component&) const = 0;
    virtual ~Abstract_visitor() = default;
};

struct Sample_component
    : public Component
/** @brief one of many components
  is independent from Sample_visitor and implementations of function visit.
  */
{
    string component_accept(Abstract_visitor& visitor) const override
    {
        assert(typeid(*this) == typeid(Sample_component));
        assert(typeid(visitor) != typeid(Abstract_visitor));
        return string(__func__) + " > " + visitor.visit(*this);
    }
    /// @brief is not virtual
    string sample_component_method() const
    {
        return __func__;
    }
};

/**
  Call hierarchy:

        visitor_demo
                client_visit
                        component_accept
                                visit
                                        sample_component_method
*/

void visitor_demo()
{
    /// @brief is one of many specific visitors with custom method visit
    /// Per each of the possible pairs of Sample_visitor and Sample_component
    struct Sample_visitor
        : public Abstract_visitor {
        /// overloaded function for each component
        string visit(const Sample_component& sc) const override
        {
            assert(typeid(*this) == typeid(Sample_visitor));
            assert(typeid(sc) == typeid(Sample_component));
            return string(__func__) + " > " + sc.sample_component_method();
        }
    };

    forward_list<unique_ptr<Component>> components;
    components.emplace_front(new Sample_component);

    forward_list<unique_ptr<Abstract_visitor>> visitors;
    visitors.emplace_front(new Sample_visitor);

    assert(client_visit(components, visitors) == "client_visit > component_accept > visit > sample_component_method");

    // flat code of expanded client_visit:
    for (auto&& v : visitors) {
        if (auto sv = dynamic_cast<Sample_visitor*>(v.get()))
            for (auto&& c : components) {
                if (auto sc = dynamic_cast<Sample_component*>(c.get()))
                    // inside component_accept:
                    sv->visit(*sc);
                else {
                };
            }
        else {
            /* And so on for each pair of visitor and component.
               Total number of pairs is multiplication of
               number components and number of visitors.
             */
        };
    }
}

/// @} visitor

struct Handler
/// @brief is a virtual command handler of Chain_of_responsibility
{
    /// Specific handler can process a command and return non-negative
    virtual int handle(Command& cmnd) { return cmnd.execute(); };
    virtual ~Handler() = default;
};

struct Chain_of_responsibility
    : Handler
/** @brief list based implementation without recursion

  [Chain-of-responsibility pattern](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern)

  https://refactoring.guru/design-patterns/chain-of-responsibility

 */
{
    void register_handler(Handler&& h, bool front = false)
    {
        if (front)
            handlers.push_front(h);
        else
            handlers.push_back(h);
    }
    int handle(Command& cmnd) override
    {
        int rc = -1;
        for (Handler& h : handlers)
            if ((rc = h.handle(cmnd)) >= 0)
                return rc;
        return rc;
    }

private:
    list<reference_wrapper<Handler>> handlers;
};

void behavioral_patterns_demo()
{
    observer_demo();

    publisher_subscriber_demo();

    mediator_demo();

    Chain_of_responsibility chain;
    chain.register_handler(Handler());

    Command cmnd;
    chain.handle(cmnd);

    visitor_demo();
}

/// @} BP

/**
  @defgroup AP Architectural
  @brief [Architectural patterns](https://en.wikipedia.org/wiki/Architectural_pattern)

  https://refactoring.guru/design-patterns/behavioral-patterns

  @{
  */

struct Model
    : Subject
/// @brief is part of MVC with View and Controller
{
    void register_observer(Observer& o)
    {
        observers.push_front(o);
    }

    int command(Command& cmnd)
    {
        int rc = cmnd.execute();
        notify_observers();
        return rc;
    }

    int command(Command&& cmnd)
    {
        int rc = cmnd.execute();
        notify_observers();
        return rc;
    }
};

struct View
    /// @brief is concrete Observer
    : public Observer {
    View(Model& m)
        : model(m) {};

    void notify() override
    {
        // check model
        (void)model;
    }

    Model& model;
};

struct Controller
/** @brief is part of MVC with Model and View

  */
{
    Model& mod; // can be many models
    Controller(Model& s)
        : mod(s) {};

    int command(Command& cmnd)
    {
        return mod.command(cmnd);
    }

    int command(Command&& cmnd)
    {
        return mod.command(cmnd);
    }
};

void architectural_patterns_demo()
{
    Model mod;
    View view(mod);
    mod.register_observer(view);
    mod.notify_observers();
    Controller ctrl(mod);
    ctrl.command(Command());
    Command cmnd;
    ctrl.command(cmnd);
}

/// @} AP

/**
  @defgroup CC Concurrency
  @brief [Concurrency patterns](https://en.wikipedia.org/wiki/Concurrency_pattern)

  @{
  */

template <typename T, class Container = queue<T>>
class Synchronized_queue
    /**
      See also
      - [Boost synchronized queues](https://www.boost.org/doc/libs/release/doc/html/thread/sds.html#thread.sds.synchronized_queues)
      - [boost/thread/concurrent_queues/sync_queue.hpp](https://github.com/boostorg/thread/blob/HEAD/include/boost/thread/concurrent_queues/sync_queue.hpp)
      - [boost/thread/concurrent_queues/detail/sync_queue_base.hpp](https://github.com/boostorg/thread/blob/HEAD/include/boost/thread/concurrent_queues/detail/sync_queue_base.hpp)

      Warning: unbounded synchronized queues can cause [OOM](https://en.wikipedia.org/wiki/Out_of_memory)
      */
    : Container {
    mutex mtx;
    bool stoped = false;

public:
    condition_variable cv;
    void push(T&& v)
    {
        scoped_lock<mutex> { mtx }, Container::push(v);
        cv.notify_one();
    };

    T& pull()
    {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [&] { return !this->empty() || stoped; });
        if (stoped)
            throw "stopped";
        auto ret = ref(Container::front());
        this->pop();
        return ret;
    };

    void stop()
    {
        stoped = true;
        cv.notify_one();
    }
};

struct Active_object
    /** @brief [Active object](https://en.wikipedia.org/wiki/Active_object)

      [Revisiting the Active Object Pattern - with C++11 Closures](https://www.codeproject.com/Articles/991641/Revisiting-the-Active-Object-Pattern-with-Cplusplu)

      */
    : Interface {
    typedef function<void()> Command;
    Interface& subject;
    Active_object(Interface& s)
        : subject(s)
    {
        th = thread([this] {
            try {
                while (true)
                    cmd_q.pull()(); // call Command
            } catch (...) {
            }
        });
    }
    ~Active_object()
    {
        cmd_q.stop();
        th.join();
    }

    int method() override
    {
        promise<int> p;
        future f = p.get_future();
        cmd_q.push([&p, this] { p.set_value(subject.method()); });
        auto status = f.wait_for(1s);
        if (status != future_status::ready)
            throw status;
        return f.get();
    }

protected:
    Synchronized_queue<Command> cmd_q; // BTW, Circular buffer is more durable because it doesn't cause OOM
    thread th;
};

void concurrency_patterns_demo()
{
    Sample_product sp(3);
    Active_object ao(sp);
    assert(ao.method() == 3);
}

/// @} CC

int main()
{
    oop_demo();
    creational_patterns_demo();
    structural_patterns_demo();
    behavioral_patterns_demo();
    architectural_patterns_demo();
    concurrency_patterns_demo();
}

/// @}

/**
 @mainpage

 @ref OOP

 @ref DP

 @ref CPP

 [Sources](https://github.com/makelinux/examples/tree/main/cpp)
*/
