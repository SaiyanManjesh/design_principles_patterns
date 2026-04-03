# 🧠 Sandi Metz Talk — Permanent Cheat Sheet

## “The ONE Idea Behind Great Object-Oriented Design”

---

# 🔥 CORE IDEA (MEMORIZE THIS)

> **Stop asking objects what they are.
> Start telling objects what to do.**

---

# 🧩 1. CONDITIONS ARE A CODE SMELL

## ❌ Problem

```cpp
if (user == NULL) {
    show_guest();
} else {
    show_user(user);
}
```

### What this really means:

* You are doing **type checking**
* You are **deciding behavior outside the object**

---

## ✅ Solution

```cpp
user->display();
```

👉 Let the object decide its behavior

---

## 🧠 Architect Thinking

> Every `if` = **lack of trust in objects**

---

# 🧩 2. NULL OBJECT PATTERN (ACTIVE NOTHING)

## ❌ Problem

```cpp
Animal* animal = find(id);
animal->name();  // 💥 crash if NULL
```

---

## ❌ Typical Fix (WRONG DIRECTION)

```cpp
if (animal != NULL)
    animal->name();
else
    "No animal";
```

---

## ✅ Correct Fix

```cpp
class NullAnimal : public Animal {
public:
    string name() override {
        return "No animal";
    }
};
```

```cpp
Animal* animal = find(id);
animal->name();   // Always safe
```

---

## 🧠 Key Insight

> NULL is not nothing
> It is **missing behavior**

👉 Replace it with an object

---

# 🧩 3. INHERITANCE IS A TRAP

## ❌ Looks Good Initially

```cpp
class House {};
class RandomHouse : public House {};
class EchoHouse : public House {};
```

---

## 💥 Problem

```cpp
Random + Echo = ??? ❌
```

👉 Cannot combine behaviors

---

## 🧠 Key Insight

> Inheritance is NOT for reuse
> It is ONLY for **true specialization**

---

## ❗ Rule

Ask:

> “Is this REALLY an IS-A relationship?”

If not → **don’t use inheritance**

---

# 🧩 4. COMPOSITION + DEPENDENCY INJECTION (REAL SOLUTION)

---

## Step 1 — Identify What Changes

Ask:

> “What varies?”

Example:

* Order of data
* Format of output

---

## Step 2 — Extract Role

```cpp
class OrderStrategy {
public:
    virtual vector<string> apply(vector<string>) = 0;
};
```

---

## Step 3 — Implement Variants

```cpp
class NormalOrder : public OrderStrategy {};
class RandomOrder : public OrderStrategy {};
class EchoOrder : public OrderStrategy {};
```

---

## Step 4 — Inject Behavior

```cpp
class House {
    OrderStrategy* order;

public:
    House(OrderStrategy* order) : order(order) {}

    void build() {
        auto data = order->apply(...);
    }
};
```

---

## 🎯 Result

```cpp
House h1(new NormalOrder());
House h2(new RandomOrder());
House h3(new EchoOrder());
House h4(new RandomEchoOrder());
```

---

## 🧠 Key Insight

> Behavior is **pluggable**

---

# 🧩 5. THE GOLDEN RULE

> There is NO such thing as one variation

If you see:

```cpp
if (random)
```

You already have:

* Normal behavior
* Random behavior

👉 Extract abstraction immediately

---

# 🧩 6. REPLACE IF WITH POLYMORPHISM

## ❌ Before

```cpp
if (type == A) ...
else if (type == B) ...
```

---

## ✅ After

```cpp
behavior->execute();
```

---

# 🧩 7. REAL-WORLD MAPPING (SYSTEM DESIGN / C)

---

## ❌ BAD

```c
if (protocol == HTTP) ...
else if (protocol == SMB) ...
```

---

## ✅ GOOD

```c
protocol->send();
```

---

## ❌ BAD

```c
if (file == NULL) ...
```

---

## ✅ GOOD

```c
file->read();  // NullFile handles safely
```

---

# 🧩 8. ARCHITECT MINDSET (CRITICAL)

When writing code:

---

## 🔍 Step 1 — Find Condition

```cpp
if (...)
```

---

## 🔍 Step 2 — Ask

> What varies?

---

## 🔍 Step 3 — Extract Role

```cpp
interface Behavior {
    execute();
}
```

---

## 🔍 Step 4 — Inject

```cpp
obj->execute();
```

---

# 🧩 9. DEEP INSIGHT (ADVANCED)

> The most important abstractions are
> hidden in the **absence of code**

---

## Example

* Numbers → abstraction
* Zero → representation of nothing
* Null Object → same idea in code

---

## 💣 Final Thought

> “Nothing” is always something
>
> You just haven’t modeled it yet

---

# 🧩 10. DO & DON’T (MEMORY SECTION)

---

## ✅ DO

* Replace `if` with polymorphism
* Use Null Object instead of NULL
* Use composition over inheritance
* Inject behavior (Dependency Injection)
* Name what varies

---

## ❌ DON’T

* Don’t use inheritance for reuse
* Don’t scatter conditions
* Don’t check types
* Don’t return inconsistent objects

---

# 🚀 FINAL SUMMARY

---

## ❌ BAD DESIGN

```text
Caller decides behavior
```

---

## ✅ GOOD DESIGN

```text
Object owns behavior
```

---
