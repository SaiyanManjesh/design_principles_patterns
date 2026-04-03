# Strategy Pattern --- Architect Level Notes

A lifetime reference for designing interchangeable algorithms.

------------------------------------------------------------------------

# 1. Core Idea

The **Strategy Pattern** allows an object to **use different algorithms
without knowing which algorithm it is using**.

It separates:

WHAT is done\
FROM\
HOW it is done

Example:

WHAT → Compute Hash\
HOW → SHA256 / MD5 / BLAKE3

The object performing the task should **not contain algorithm logic**.

Instead, the algorithm should be **delegated to a separate object**.

------------------------------------------------------------------------

# 2. Problem Strategy Pattern Solves

Without Strategy Pattern, code often looks like this:

    if (type == SHA256)
    {
        // SHA256 logic
    }
    else if (type == MD5)
    {
        // MD5 logic
    }
    else if (type == BLAKE3)
    {
        // BLAKE3 logic
    }

Problems:

-   Violates Open/Closed Principle
-   Large conditional chains
-   Hard to extend
-   Hard to test
-   Tight coupling

Strategy Pattern replaces this with polymorphism.

------------------------------------------------------------------------

# 3. Strategy Pattern Structure

The pattern contains three main roles.

## Strategy (Interface)

Defines the algorithm interface.

    class Strategy
    {
        virtual void execute() = 0;
    };

## Concrete Strategy

Each implementation provides a specific algorithm.

    class StrategyA : public Strategy
    class StrategyB : public Strategy
    class StrategyC : public Strategy

## Context

The object that **uses the strategy but does not know its
implementation**.

    class Context
    {
        Strategy* strategy;
    };

The context **delegates the work**.

------------------------------------------------------------------------

# 4. Conceptual Diagram

            Context
               |
               v
            Strategy
          /     |     \
    StrategyA StrategyB StrategyC

------------------------------------------------------------------------

# 5. Key Principle

Replace conditional logic with polymorphism.

Whenever you see:

    if (type == A)
    if (type == B)
    if (type == C)

Consider Strategy Pattern.

------------------------------------------------------------------------

# 6. Example (Hash Algorithm System)

## Strategy Interface

``` cpp
class Hash
{
public:
    virtual ~Hash() = default;
    virtual int compute_hash(const std::string& buffer) = 0;
};
```

## Concrete Strategies

SHA256_Hash\
MD5_Hash\
BLAKE3_Hash

Each class implements its own algorithm.

## Context

    class Cryptograph
    {
        Hash* algorithm;

    public:
        void compute_hash()
        {
            algorithm->compute_hash();
        }
    };

The context **does not know which algorithm is used**.

------------------------------------------------------------------------

# 7. Strategy Pattern Mental Model

Think of strategies as **plug-ins**.

    System
      |
      v
    Strategy Interface
      |
    Plugins implementing algorithm

New strategies can be added **without modifying the system**.

------------------------------------------------------------------------

# 8. Golden Rule

Strategy Pattern exists when:

    Multiple ways exist to perform the same task

Examples:

Sorting → QuickSort / MergeSort\
Payment → UPI / Card / PayPal\
Compression → ZIP / RAR / GZIP\
Authentication → Password / OAuth\
Routing → Car / Walking

------------------------------------------------------------------------

# 9. Do's

✔ Separate algorithms from the context\
✔ Use interfaces or abstract classes\
✔ Inject strategies from outside\
✔ Design algorithms as interchangeable modules\
✔ Keep context unaware of concrete strategies

------------------------------------------------------------------------

# 10. Don'ts

❌ Do not put algorithm logic inside the context\
❌ Do not use conditional chains for algorithm selection\
❌ Do not tightly couple algorithm with system\
❌ Avoid overusing strategy for trivial logic

------------------------------------------------------------------------

# 11. Ownership Rules (Modern C++)

Prefer smart pointers.

Good:

    std::unique_ptr<Strategy>

Avoid:

    new Strategy()

Rule:

Raw pointer → non owning reference\
Smart pointer → ownership

------------------------------------------------------------------------

# 12. Pass Large Objects Efficiently

Bad:

    void process(std::string data)

Good:

    void process(const std::string& data)

------------------------------------------------------------------------

# 13. Strategy Pattern vs Command Pattern

  Feature   Strategy                Command
  --------- ----------------------- -------------------------
  Purpose   Switch algorithms       Encapsulate actions
  Focus     How something is done   What action is executed
  Usage     Sorting / Compression   Undo / Redo

------------------------------------------------------------------------

# 14. Strategy Pattern + Dependency Injection

Strategies should be **injected from outside**.

    Cryptograph crypt(new SHA256_Hash());

The context **does not create the strategy**.

------------------------------------------------------------------------

# 15. When NOT to Use Strategy Pattern

Avoid when:

-   Only one algorithm exists
-   Algorithm is trivial
-   No future variation expected

------------------------------------------------------------------------

# 16. Real Systems Using Strategy Pattern

Game Engines\
Machine Learning Pipelines\
Payment Systems\
Compression Tools\
Routing Systems\
Cryptographic Libraries\
Authentication Systems

------------------------------------------------------------------------

# 17. Architect Thinking Rule

Ask:

What part of the system will change?

If the answer is:

algorithm\
behavior\
policy

Then Strategy Pattern may apply.

------------------------------------------------------------------------

# 18. Final Memory Line

Strategy Pattern allows algorithms to vary independently from the
objects that use them.

------------------------------------------------------------------------

# End
