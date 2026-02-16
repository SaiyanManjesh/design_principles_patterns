#  C++ Parameter Passing – Complete Mental Model Guide

---
# SIMPLE WAY
void foo(int a, int b)
{
    a++;
    b++;
}
## exists only this function SCOPE (CALL STACK)

|--------------|
|  foo         |
|   a++ b++    |
|--------------|
|  main        |
|   a     b    |
|--------------|
        |
        |
        |
|--------------|
|  main        |
|   a     b    |
|--------------|  

NOW the X and Y needs the actual memory to do the changes 

# How to give the memory address --> & operator --> pass by address pr reference














# 1️⃣ The Three Ways to Pass Data

```cpp
void foo(int p);        // Pass by Value
void foo(int &p);       // Pass by Reference
void foo(int *p);       // Pass by Pointer
```



Each behaves differently in memory.

---

# 2️⃣ Pass By Value

```cpp
void foo(int p)
{
    p = 100;
}
```

## What Happens?

* A copy is created
* Modifying `p` does NOT modify the original variable

## Memory View

```
main stack:      foo stack:
a = 10    --->   p = 10 (copy)
```

## When To Use

* Small types (int, char, double)
* You do NOT want original modified
* Safety is more important than performance

## Example

```cpp
int a = 10;
foo(a);
// a is still 10
```

---

# 3️⃣ Pass By Reference (C++ Only)

```cpp
void foo(int &p)
{
    p = 100;
}
```

## What Happens?

* No copy created
* `p` is an alias of original variable
* Modifying `p` modifies original

## Memory View

```
main stack:
a = 10

foo:
p ----> a
```

## When To Use

* You want to modify original
* Large object (avoid copying)
* Cleaner than pointer
* Parameter must NOT be null

## Example

```cpp
int a = 10;
foo(a);
// a is now 100
```

---

# 4️⃣ Pass By Pointer

```cpp
void foo(int *p)
{
    *p = 100;
}
```

## What Happens?

* Address is copied
* Both pointers point to same memory
* Must dereference with `*`

## Memory View

```
main:
a = 10
p = &a

foo:
p(copy) ----> a
```

## When To Use

* In C language
* Parameter can be NULL
* Low-level memory control
* Dynamic memory
* Hardware register access

## Example

```cpp
int a = 10;
foo(&a);
// a is now 100
```

---

# 5️⃣ Passing Dynamic Memory

## Allocate

```cpp
int *p = new int(10);
```

---

## Case 1: Modify Heap Data

```cpp
void foo(int *p)
{
    *p = 50;
}
```

✔ Changes heap value
❌ Cannot change where pointer points

---

## Case 2: Modify Pointer Itself

### Using Reference to Pointer (Modern C++)

```cpp
void foo(int *&p)
{
    delete p;
    p = new int(200);
}
```

✔ Can reassign pointer

---

### Using Pointer to Pointer (C Style)

```cpp
void foo(int **p)
{
    delete *p;
    *p = new int(300);
}
```

---

# 6️⃣ Comparison Table

| Type      | Copy? | Modify Original? | Can be Null? | Clean Syntax? |
| --------- | ----- | ---------------- | ------------ | ------------- |
| value     | Yes   | No               | No           | Yes           |
| reference | No    | Yes              | No           | Very Clean    |
| pointer   | No    | Yes              | Yes          | No            |

---

# 7️⃣ Object Slicing Warning

❌ Wrong:

```cpp
void foo(Base obj);
```

This slices derived class.

✔ Correct:

```cpp
void foo(Base &obj);
void foo(Base *obj);
```

---

# 8️⃣ Observer Pattern Understanding

```cpp
ISystem *sub1 = new EmergencyControlSystem();
sensor.subscribe(*sub1);
```

Function:

```cpp
void subscribe(ISystem &system)
{
    subscribers[i++] = &system;
}
```

## What Happens?

1. Object created on heap
2. Pointer stored in `sub1`
3. `*sub1` passes object by reference
4. Inside function, reference converted to pointer
5. Pointer stored internally

✔ Clean API
✔ No null allowed
✔ Polymorphism preserved

---

# 9️⃣ Modern C++ Best Practice

Avoid raw pointers when possible.

Use:

```cpp
std::unique_ptr
std::shared_ptr
```

Example:

```cpp
void foo(const std::string &s);
```

---

# 🔟 How To Decide What To Use

Ask yourself:

1️⃣ Do I need a copy?
→ Use value

2️⃣ Do I need to modify original?
→ Use reference

3️⃣ Can it be null?
→ Use pointer

4️⃣ Do I need to reassign pointer?
→ Use pointer reference (`T*&`)

---

# 🧠 Mental Model

| Concept            | Think Like              |
| ------------------ | ----------------------- |
| Value              | Photocopy               |
| Reference          | Alias / Nickname        |
| Pointer            | Address                 |
| Pointer Reference  | Address that can change |
| Pointer to Pointer | Address of address      |

---

# 🚨 Beginner Mistakes

* Forgetting to dereference pointer
* Passing large objects by value
* Not using `const` when not modifying
* Creating memory leaks
* Dangling pointers

---

# 🔥 Golden Rules

* Prefer reference over pointer in C++
* Use `const &` for large read-only objects
* Use pointer only when null is valid
* Avoid raw `new` in modern C++
* Always delete what you allocate

---

# 🏁 Final Architecture-Level Understanding

* Stack stores local variables
* Heap stores dynamic memory
* Passing value copies data
* Passing reference shares object
* Passing pointer shares address
* Passing pointer reference can redirect address

---

# 🎯 One-Line Summary

Value copies data.
Reference aliases data.
Pointer shares address.
Pointer reference can redirect address.
