# 🧠 NULL OBJECT PATTERN — ARCHITECT CHEAT SHEET

## “Replace absence with behavior”

---

# 🔥 CORE IDEA (BURN THIS)

> **NULL is not nothing — it is missing behavior**
>
> 👉 Replace it with an object

---

# 🧩 1. WHAT IS NULL OBJECT PATTERN?

---

## Definition

> A **Null Object** is a concrete object that:

* Implements the same interface as real objects
* Represents “no value”
* Provides **safe default behavior**

---

## ❌ Traditional Approach

```cpp
if (customer == NULL) {
    // handle missing case
}
```

---

## ✅ Null Object Approach

```cpp
customer->display();
```

👉 No condition. No crash. Uniform behavior.

---

## 🧠 Core Principle

> “Don’t ask if it exists — just use it”

---

# 🧩 2. WHY DO WE NEED IT?

---

## Problems with NULL

* ❌ Repeated checks everywhere
* ❌ Code duplication
* ❌ Segmentation faults
* ❌ Hard-to-maintain logic
* ❌ Breaks polymorphism

---

## 💣 Root Cause

> NULL breaks the **object contract**

---

## 🧠 Insight

> Good design = consistent behavior
> NULL = inconsistency

---

# 🧩 3. HOW IT WORKS

---

## Step 1 — Define Interface

```cpp
class ICustomer {
public:
    virtual void display() const = 0;
    virtual ~ICustomer() = default;
};
```

---

## Step 2 — Real Object

```cpp
class RealCustomer : public ICustomer {
private:
    std::string name;

public:
    RealCustomer(const std::string& name) : name(name) {}

    void display() const override {
        std::cout << "Customer: " << name << std::endl;
    }
};
```

---

## Step 3 — Null Object

```cpp
class NullCustomer : public ICustomer {
public:
    static NullCustomer& instance() {
        static NullCustomer instance;
        return instance;
    }

    void display() const override {
        std::cout << "Customer: No Customer Available" << std::endl;
    }

private:
    NullCustomer() = default;
};
```

---

## Step 4 — Usage

```cpp
ICustomer& customer = get_customer();  // never NULL
customer.display();
```

---

## 🧠 Result

| Before                 | After        |
| ---------------------- | ------------ |
| NULL checks everywhere | No checks    |
| Crashes possible       | Always safe  |
| Scattered logic        | Encapsulated |

---

# 🧩 4. WHERE TO USE

---

## ✅ Ideal Use Cases

### 1. Optional Dependencies

* Logger
* Metrics
* Monitoring

```cpp
Logger* logger = new NullLogger();
```

---

### 2. Missing Data

```cpp
User* user = find_user(id);
```

👉 Return `GuestUser` instead of NULL

---

### 3. External APIs

Wrap unsafe API:

```cpp
return result ? result : NullObject::instance();
```

---

### 4. Collections

Avoid:

```cpp
if (item != NULL)
```

---

### 5. System / Embedded (Your Domain)

* Missing file → `NullFile`
* No network → `NullConnection`
* Device not present → `NullDevice`

---

# 🧩 5. WHEN TO USE

---

## ✅ Use When

✔ You see repeated NULL checks
✔ You want polymorphism
✔ Behavior is simple fallback
✔ You want safer APIs

---

## ❌ Avoid When

❌ Absence is an error
❌ You must fail fast
❌ Behavior differs drastically
❌ You need strict validation

---

# 🧩 6. DESIGN RULES (VERY IMPORTANT)

---

## 🔑 Rule 1 — Same Interface

Null object must behave like real object

---

## 🔑 Rule 2 — No Side Effects

```cpp
void log() override {
    // do nothing
}
```

---

## 🔑 Rule 3 — Immutable

Null object should not change state

---

## 🔑 Rule 4 — Singleton

```cpp
static NullCustomer& instance();
```

---

## 🔑 Rule 5 — Honest Behavior

Return safe defaults:

* empty string
* zero
* no-op

---

# 🧩 7. ARCHITECT THINKING MODEL

---

## Step 1 — Detect Smell

```cpp
if (x == NULL)
```

---

## Step 2 — Ask

> What should happen instead?

---

## Step 3 — Create Object

```cpp
class NullX : public X {};
```

---

## Step 4 — Replace Condition

```cpp
x->do_work();
```

---

## 🎯 Goal

> Remove condition, not just hide it

---

# 🧩 8. REAL-WORLD EXAMPLES

---

## 🔹 Logger

```cpp
class NullLogger : public Logger {
    void log(std::string) override {}
};
```

---

## 🔹 Payment

```cpp
class NullPayment : public Payment {
    void pay() override {}
};
```

---

## 🔹 File

```cpp
class NullFile : public File {
    void read() override {}
};
```

---

## 🔹 Network

```cpp
class NullConnection : public Connection {
    void send() override {}
};
```

---

# 🧩 9. RELATION TO OTHER PATTERNS

---

## 🔹 Strategy Pattern

Null Object = one strategy

---

## 🔹 Dependency Injection

Inject Null Object when needed

---

## 🔹 Polymorphism

Core mechanism

---

## 🔹 Optional (C++)

```cpp
std::optional<T>
```

👉 Still requires checks (not same as Null Object)

---

# 🧩 10. COMMON MISTAKES

---

## ❌ Mixing NULL + Null Object

```cpp
if (user == NULL)
```

👉 defeats purpose

---

## ❌ Mutable Null Object

```cpp
set_name()  // ❌ dangerous
```

---

## ❌ Complex Logic

Null object must be simple

---

## ❌ Hiding Errors

Don’t use Null Object to ignore failures

---

## ❌ Multiple Instances

Use singleton

---

# 🧩 11. PERFORMANCE (SYSTEM LEVEL)

---

## Benefits

✔ No branching
✔ Better CPU prediction
✔ Cleaner pipelines

---

## Trade-off

* Slight memory overhead

---

## Verdict

👉 Worth it in most systems

---

# 🧩 12. BEFORE vs AFTER

---

## ❌ BEFORE

```cpp
if (file != NULL)
    file->read();
```

---

## ✅ AFTER

```cpp
file->read();
```

---

# 🧩 13. DEEP INSIGHT

---

> The most important abstractions
> are hidden in missing cases

---

## Example

| Concept     | Meaning             |
| ----------- | ------------------- |
| 0           | nothing in numbers  |
| Null Object | nothing in behavior |

---

# 🧠 FINAL MENTAL MODEL

---

## ❌ OLD

```text
Check → Decide → Act
```

---

## ✅ NEW

```text
Tell → Object handles → Done
```

---

# 🚀 FINAL TAKEAWAY

---

> If you are checking for NULL
>
> 👉 You are missing an object

---

# 🧠 ONE LINE TO REMEMBER

> “Nothing should behave like something.”

---