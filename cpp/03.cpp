/**
 @file
 @brief C++03 / C++98

 @defgroup CPP03 C++03 examples
 @brief C++03 / C++98

 https://en.wikipedia.org/wiki/C++03

 @{
 */

#include <bits/stdc++.h>

using namespace std;

/**
 @defgroup lang03 Language
 @{

 */

void init_03()
{

    // https://en.cppreference.com/w/cpp/language/copy_initialization
    int x3 = { 3 };
    double x4 = { 3.0 };

    struct point {
        int x, y;
    };

    point p1 = { 1, 2 };
    (void)p1.x;
    (void)p1.y;

#if gcc_extension
    // designated initializers
    // https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html
    __extension__ point gpp_ext = { .x = 1 }; // C99-like gcc extension
    __extension__ point gcc_ext = { x : 1 }; // C-like gcc extension
#endif

    // Mutable
    struct struct_with_mutable {
        struct_with_mutable() {};
        mutable int m;
    } const const_struct_with_mutable;
    const_struct_with_mutable.m = 2;
    assert(const_struct_with_mutable.m == 2);
    int y = 0;
    int& reference = y;
}

/**
  [set](https://en.cppreference.com/w/cpp/container/set)

  [map](https://en.cppreference.com/w/cpp/container/map)

  [multimap](https://en.cppreference.com/w/cpp/container/multimap)
  */

void associative_containers_03()
{
    set<int> s;
    s.insert(1);
    s.insert(2);
    assert(*s.find(1) == 1);
    assert(s.find(3) == s.end());

    map<char, int> m;
    m['a'] = 1;
    m.insert(make_pair('b', 2));
    ++m['a'];
    assert(m['a'] == 2);

    multimap<char, int> mm;
    mm.insert(make_pair('c', 1));
    mm.insert(make_pair('b', 2));
    mm.insert(make_pair('a', 3));
    mm.insert(make_pair('a', 4));
    multimap<char, int>::iterator i = mm.find('a');
    assert(i->second == 3);
    i++;
    assert(i->second == 4);
    i++;
    assert(i->first == 'b');
    assert(i->second == 2);
}

template <class C>
void test_generic_container(C& c)
{
    assert(c.empty());
    assert(c.max_size() > 1000);
    c.push_back(0);
    assert(c.front() == 0);
    assert(c.back() == 0);
    assert(c.size() == 1);
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    assert(c.size() == 4);
    for (typename C::iterator i = c.begin(); i != c.end();) {
        if (*i == 1) {
            i = c.erase(i);
            continue;
        }
        if (*i == 2) {
            c.erase(i++);
            continue;
        }
        ++i;
    }
    assert(c.size() == 2);
    assert(c.front() == 0);
    assert(c.back() == 3);
    c.assign(4, 1);
    assert(c.size() == 4);
    c.clear();
}

template <class V>
void test_vector_container(V& v)
{
    string err;
    try {
        v.at(666) = 0;
    } catch (out_of_range const& exc) {
        err = exc.what();
    }
    assert(err.length());
    assert(v[0] == 1);
    v.resize(4);

    int arr[] = { 1, 2, 3 };
    v.insert(v.begin(), arr, arr + 3);
    assert(v[1] == 2);
}

/// [container](https://en.cppreference.com/w/cpp/container)

void container_03()
{
    list<int> l;
    test_generic_container(l);

    vector<int> v;
    test_generic_container(v);
    test_vector_container(v);

    v.reserve(10);
    assert(v.capacity() == 10);

    deque<int> d;
    test_generic_container(d);
    test_vector_container(d);

    stack<int> s;
    s.push(1);
    assert(s.top() == 1);
    s.push(2);
    assert(s.top() == 2);
    s.pop();
    assert(s.top() == 1);
    s.pop();
    assert(s.empty());

    queue<int> q;
    q.push(1);
    q.push(2);
    assert(q.front() == 1);
    assert(q.back() == 2);
    q.pop();
    assert(q.front() == 2);
    q.pop();
    assert(q.empty());

    priority_queue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    assert(pq.top() == 3);

    associative_containers_03();
}

/**
 @fn void sort_03()
 http://www.cplusplus.com/reference/algorithm/sort/?kw=sort

 Compare with @ref lambda::sort_11 and @ref sort_libc
 */

/// @private
bool func(int i, int j) { return i < j; }

/// @private
struct _ {
    bool operator()(int i, int j) { return i < j; }
} functor;

void sort_03()
{
    int a[] = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
    list<int> list(a, a + sizeof a / sizeof a[0]);
    list.sort();

    vector<int> v(a, a + sizeof a / sizeof a[0]);

    // using default comparison (operator <):
    sort(v.begin(), v.begin() + 4);

    // using function as comp
    sort(v.begin() + 4, v.end(), func);

    // sort using a standard library compare function object
    sort(v.begin(), v.end(), greater<int>());

    // using object as comp
    sort(v.begin(), v.end(), functor);

    int prev = -1;
    for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
        assert(*i >= prev);
        prev = *i;
    }
}

/// [algorithm](https://en.cppreference.com/w/cpp/algorithm)

void algo_03()
{
    int a[] = { 1, 2, 3 };
    vector<int> v(a, a + sizeof a / sizeof a[0]);
    vector<int> r(sizeof a / sizeof a[0]);
    reverse_copy(v.begin(), v.end(), r.begin());
    assert(r[0] > r[1]);

    sort_03();
}

/// [reference](https://en.cppreference.com/w/cpp/language/reference)
int& a_ref(int& a) { return a; }

struct Common {
    int n;
    Common(int x)
        : n(x)
    {
    }
};

/// [ref](https://en.cppreference.com/w/cpp/language/virtual)
struct Virtual_A : virtual Common {
    Virtual_A()
        : Common(1)
    {
    }
};
struct Virtual_B : virtual Common {
    Virtual_B()
        : Common(2)
    {
    }
};
struct Diamond : Virtual_A, Virtual_B {
    Diamond()
        : Common(3)
        , Virtual_A()
        , Virtual_B()
    {
    }
};

void types_03()
{
    int a = 0;
    assert(typeid(int) == typeid(a));
    assert(typeid(int).name() == string("i"));

    a_ref(a) = 2;
    assert(a == 2);

    Diamond d;
    assert(d.Virtual_A::n == 3);
    assert(d.Virtual_B::n == 3);
}

/// @}

int main(void)
{
    assert(__cplusplus == 199711);

    init_03();
    container_03();
    algo_03();
    types_03();
    assert(min(1, 2) == 1);
    assert(max(1, 2) == 2);
    pair<int, char> p(1, 'a');
    assert(p.first == 1);
    assert(p.second == 'a');
    p = make_pair('b', 2);
    assert(p.first == 'b');
}

/// @}
