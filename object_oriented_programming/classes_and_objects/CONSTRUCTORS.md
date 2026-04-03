# C++ Constructors — Complete Concept Guide

A practical reference for remembering **WHY and HOW constructors work in C++**.

---

# 1. What is a Constructor?

A **constructor** is a special member function that is **automatically called when an object is created**.

Purpose:

* Initialize the object
* Ensure object starts in a **valid state**
* Enforce class invariants

Example:

```cpp
class Car
{
public:
    int speed;

    Car()
    {
        speed = 0;
    }
};
```

Usage

```cpp
Car c1;
```

Execution Flow

```
Memory allocated for object
↓
Constructor executes
↓
Members initialized
↓
Object ready
```

Conceptually a constructor is like:

```
Birth of an object
```

---

# 2. Types of Constructors

## Default Constructor

Constructor with **no parameters**.

```cpp
class Car
{
public:
    int speed;

    Car()
    {
        speed = 0;
    }
};
```

Usage:

```cpp
Car c;
```

Compiler generates a default constructor automatically **only if none exist**.

Example:

```cpp
class Test
{
    int x;
};
```

Compiler generates:

```cpp
Test::Test(){}
```

But `x` will remain **uninitialized**.

---

## Parameterized Constructor

Constructor that takes parameters.

```cpp
class Car
{
public:
    int speed;

    Car(int s)
    {
        speed = s;
    }
};
```

Usage:

```cpp
Car c1(100);
```

Why it exists:

To force users to create objects with **valid required data**.

Example:

```cpp
class BankAccount
{
    int balance;

public:
    BankAccount(int b)
    {
        balance = b;
    }
};
```

Now this is illegal:

```cpp
BankAccount acc; // ERROR
```

User must provide initial balance.

---

## Copy Constructor

Creates a **new object from another object**.

Definition:

```cpp
ClassName(const ClassName& other);
```

Example:

```cpp
class Car
{
public:
    int speed;

    Car(int s)
    {
        speed = s;
    }

    Car(const Car& other)
    {
        speed = other.speed;
    }
};
```

Usage:

```cpp
Car c1(100);
Car c2 = c1;
```

Copy constructor is called when:

1. Object initialized from another object

```
Car b = a;
```

2. Pass-by-value

```
void foo(Car c)
```

3. Return-by-value

```
Car create()
```

---

## Move Constructor (C++11)

Transfers resources instead of copying.

Definition:

```cpp
Car(Car&& other);
```

Used to avoid expensive deep copies.

Example:

```cpp
class Buffer
{
public:
    int* data;

    Buffer(int size)
    {
        data = new int[size];
    }

    Buffer(Buffer&& other)
    {
        data = other.data;
        other.data = nullptr;
    }
};
```

---

# 3. Constructor Overloading

Multiple constructors with different parameter lists.

Example:

```cpp
class Car
{
public:

    int speed;

    Car()
    {
        speed = 0;
    }

    Car(int s)
    {
        speed = s;
    }

    Car(int s, int turbo)
    {
        speed = s + turbo;
    }
};
```

Usage:

```cpp
Car c1;
Car c2(100);
Car c3(100,50);
```

Compiler selects the correct constructor.

Why it exists:

Objects can be created in **different meaningful ways**.

Example:

```
Date()
Date(day,month,year)
Date(timestamp)
```

---

# 4. Public vs Private Constructors

## Public Constructor

Default case.

```cpp
class Car
{
public:
    Car(){}
};
```

Allows anyone to create objects.

```
Car c;
```

---

## Private Constructor

Prevents object creation outside the class.

```cpp
class Car
{
private:
    Car(){}
};
```

Now this fails:

```
Car c; // ERROR
```

Used when we want **controlled object creation**.

---

## Singleton Example

```cpp
class Logger
{
private:

    Logger(){}

public:

    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }
};
```

Usage:

```cpp
Logger& log = Logger::getInstance();
```

Only one object will exist.

---

# 5. Shallow Copy

Default copy constructor performs **shallow copy**.

Meaning:

Only the **pointer value is copied**, not the actual memory.

Example:

```cpp
class Test
{
public:

    int* data;

    Test(int val)
    {
        data = new int(val);
    }
};
```

Copying:

```cpp
Test t1(10);
Test t2 = t1;
```

Memory Layout:

```
t1.data ─┐
         ├──► 10
t2.data ─┘
```

Both objects share the **same memory**.

Problem:

```
delete t1.data;
```

Now `t2.data` becomes **dangling pointer**.

This causes crashes.

---

# 6. Deep Copy

Deep copy duplicates the actual memory.

Example:

```cpp
class Test
{
public:

    int* data;

    Test(int val)
    {
        data = new int(val);
    }

    Test(const Test& other)
    {
        data = new int(*other.data);
    }
};
```

Memory Layout:

```
t1.data → 10

t2.data → 10
```

Separate memory blocks.

Safe.

---

# 7. Rule of Three

If a class manages **dynamic memory**, you must implement:

```
1. Destructor
2. Copy Constructor
3. Copy Assignment Operator
```

Because compiler versions perform **shallow copy**.

Example skeleton:

```cpp
class Test
{
    int* data;

public:

    Test(int v)
    {
        data = new int(v);
    }

    ~Test()
    {
        delete data;
    }

    Test(const Test& other)
    {
        data = new int(*other.data);
    }

    Test& operator=(const Test& other)
    {
        if(this != &other)
        {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
};
```

---

# 8. Rule of Five (Modern C++)

C++11 adds move semantics.

Now recommended functions:

```
Destructor
Copy Constructor
Copy Assignment
Move Constructor
Move Assignment
```

---

# 9. Constructor Mental Model

Remember this analogy:

```
Constructor → Birth
Destructor → Death
```

Object lifecycle:

```
Memory allocated
↓
Constructor runs
↓
Object used
↓
Destructor runs
↓
Memory released
```

Goal of good C++ design:

```
Object born valid
Object lives valid
Object dies cleanly
```

---

# Quick Interview Memory Table

| Concept                   | Purpose                          |
| ------------------------- | -------------------------------- |
| Constructor               | Initialize object                |
| Default Constructor       | Create object without parameters |
| Parameterized Constructor | Initialize with data             |
| Copy Constructor          | Duplicate object                 |
| Move Constructor          | Transfer resources               |
| Constructor Overloading   | Multiple creation styles         |
| Public Constructor        | Allow object creation            |
| Private Constructor       | Control object creation          |
| Shallow Copy              | Pointer copied                   |
| Deep Copy                 | Actual memory copied             |

---

# Final Thought

Constructors exist to guarantee:

```
Object validity
Safe initialization
Controlled creation
```

If objects start invalid → **bugs propagate everywhere**.

Constructors prevent that.
