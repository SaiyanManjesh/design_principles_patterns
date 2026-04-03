# 🧠 Dependency Injection — Architect’s Permanent Mental Model

---

# 1️⃣ WHAT is Dependency Injection?

> Dependency Injection (DI) is a design principle where a class **does NOT create its own dependencies**, but instead **receives them from outside**.

---

## 🔥 Core Rule

❌ Bad:

```cpp
class Car {
    Engine engine;
};
```

❌ Also Bad:

```cpp
class Car {
    Engine* engine;
public:
    Car() {
        engine = new Engine();
    }
};
```

✅ Correct:

```cpp
class Car {
    IEngine* engine;
public:
    Car(IEngine* engine) : engine(engine) {}
};
```

---

# 2️⃣ WHY Dependency Injection Exists

## 🎯 The Real Problem It Solves

Without DI:

* Tight coupling
* Hard to test
* Hard to extend
* Hard to replace implementation
* Violates SOLID principles

With DI:

* Loose coupling
* Testable
* Replaceable modules
* Clean architecture
* Future-proof design

---

# 3️⃣ The Golden Architecture Rule

> High-level modules should NOT depend on low-level modules.
> Both should depend on abstractions.

This is the **Dependency Inversion Principle (DIP)** from SOLID.

DI is how we implement DIP.

---

# 4️⃣ HOW It Works

There are 3 Types:

---

## ✅ 1. Constructor Injection (BEST & SAFEST)

```cpp
class IService {
public:
    virtual void execute() = 0;
    virtual ~IService() = default;
};

class RealService : public IService {
public:
    void execute() override {
        std::cout << "Real Service\n";
    }
};

class Controller {
    IService* service;
public:
    Controller(IService* service) : service(service) {}
};
```

✔ Object cannot exist without dependency
✔ Safe
✔ Clear
✔ Most used in real systems

---

## ⚠ 2. Setter Injection

```cpp
void setService(IService* s);
```

Risk:

* Object may exist in invalid state
* Dependency may be forgotten

Use only if dependency is optional.

---

## ⚠ 3. Method Injection

```cpp
void process(IService* service);
```

Used when dependency is needed only temporarily.

---

# 5️⃣ WHAT DI IS NOT

❌ It is NOT just passing a pointer
❌ It is NOT using new inside constructor
❌ It is NOT Singleton
❌ It is NOT a framework feature

It is a **design principle**.

---

# 6️⃣ Mental Checklist While Coding

Every time you write a class, ask:

1. ❓ Am I creating dependencies inside this class?
2. ❓ Can this dependency change in future?
3. ❓ Will I need to test this class independently?
4. ❓ Am I depending on concrete implementation instead of interface?
5. ❓ Can I inject this from outside?

If the answer is YES → Use DI.

---

# 7️⃣ Architecture-Level Thinking

### Without DI:

```
Controller → creates → Database
Controller → creates → Logger
Controller → creates → NetworkClient
```

Controller becomes GOD object.

---

### With DI:

```
Main (Composition Root)
        ↓
Creates dependencies
        ↓
Injects into Controller
```

Controller only focuses on behavior.

---

# 8️⃣ Composition Root (Very Important)

> The place where all objects are created and wired together.

Usually:

* `main()`
* Bootstrap file
* Application startup layer

Example:

```cpp
int main() {
    Database db;
    Logger logger;
    Service service(&db, &logger);
}
```

Only here object creation should happen.

---

# 9️⃣ When To Use DI

Use DI when:

* Database
* File system
* Network client
* Logger
* Payment gateway
* Message queue
* Cache
* External APIs
* Hardware drivers
* Services
* Strategy behavior

---

# 🔟 When NOT To Use DI

Do NOT use DI for:

* Value objects (Point, Rectangle)
* Simple data structures
* Pure utility functions
* Very small programs
* Performance-critical micro-objects

Overengineering is also bad architecture.

---

# 1️⃣1️⃣ Common Beginner Mistakes

### ❌ Mistake 1: Injecting Concrete Class

Wrong:

```cpp
Car(PetrolEngine* engine);
```

Correct:

```cpp
Car(IEngine* engine);
```

Always depend on abstraction.

---

### ❌ Mistake 2: Using Singleton Instead of DI

```cpp
Database::getInstance();
```

This hides dependency.

Hidden dependency = Hidden coupling.

---

### ❌ Mistake 3: Creating Dependency in Constructor

```cpp
Car() {
    engine = new Engine();
}
```

That is NOT DI.

---

# 1️⃣2️⃣ Testing Power

With DI:

```cpp
class MockService : public IService {
public:
    void execute() override {
        std::cout << "Mock\n";
    }
};
```

Now you can test:

```cpp
MockService mock;
Controller ctrl(&mock);
```

No real database.
No real network.
No real file writing.

---

# 1️⃣3️⃣ Deep Architectural Benefits

DI enables:

* Clean Architecture
* Hexagonal Architecture
* Microservices
* Test-driven development
* Replaceable modules
* Plugin systems
* Strategy Pattern
* Command Pattern
* Observer Pattern

It is foundational.

---

# 1️⃣4️⃣ One Rule To Remember Forever

> "My class should describe behavior, not build the world."

If your class builds the world → you are architecturally wrong.

If your class receives the world → you are architecturally correct.

---

# 1️⃣5️⃣ The 5-Second Coding Rule

Before writing `new`, pause and ask:

👉 Should this be injected instead?

If yes → Move creation to composition root.

---

# 1️⃣6️⃣ DI in One Sentence

> Dependency Injection is about controlling coupling by moving object creation outside the class and depending only on abstractions.

---

# 1️⃣7️⃣ Ultimate Tattoo Line

> Whoever creates the dependency controls the architecture.

---

# 1️⃣8️⃣ Final Mental Model

Think like this:

Your class is an employee.

It should:

* Do its job
* Not build its tools
* Not build the office
* Not build the electricity
* Not build the internet

It should receive them.

That is Dependency Injection.

---
