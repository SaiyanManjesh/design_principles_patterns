# 🧠 Command Pattern – Architect’s Field Guide

---

# 1️⃣ What Is Command Pattern (In One Line)

> **Command Pattern turns a request (action) into an object so that the action can be executed, stored, logged, queued, undone, or composed.**

If you remember only one thing, remember this.

It is NOT about adding a middle layer.

It is about **treating behavior as data**.

---

# 2️⃣ Core Idea (Mental Model)

Normal thinking:

```
Call function immediately.
```

Command thinking:

```
Create an instruction object → Decide when/how to execute it.
```

You convert:

```
Control Flow  →  Data Flow
```

Instead of:

```
UI → call deposit()
```

You do:

```
UI → create DepositCommand
Invoker → execute(command)
```

---

# 3️⃣ The 4 Roles (Burn This In Brain)

### 1. Receiver

Knows how to perform work.

Example:

* Document
* BankAccount
* FileSystem
* GameCharacter

Receiver must NOT know about commands.

---

### 2. Command (Interface)

Minimal abstraction.

Usually:

```
execute()
undo()   (optional)
```

Keep it small.
If your interface has business methods (deposit, withdraw, etc.) → You are doing it wrong.

---

### 3. Concrete Command

Encapsulates:

* Receiver
* Operation
* Parameters
* State needed for undo

One command = one action.

---

### 4. Invoker

Responsible for:

* Triggering execution
* Managing undo stack
* Managing redo stack
* Logging
* Clearing redo on new command
* Enforcing execution policy

Invoker manages **when and how**.
Command knows **what**.

---

# 4️⃣ When To Use Command Pattern

Use it when you need:

* ✅ Undo / Redo
* ✅ Logging of operations
* ✅ Queueing / Scheduling
* ✅ Retry logic
* ✅ Macro operations
* ✅ Centralized execution control
* ✅ Treat operations as first-class objects
* ✅ Decoupling UI from domain logic

---

# 5️⃣ When NOT To Use It

Do NOT use it when:

* ❌ Simple direct function call is enough
* ❌ No undo, no logging, no scheduling
* ❌ No future extensibility expected
* ❌ You are overengineering

Architecture rule:

> Simplicity first. Add patterns only when complexity demands it.

---

# 6️⃣ Design Rules (Very Important)

### 🔹 Rule 1: One Command = One Request

Do NOT create:

```
ICommand {
    deposit();
    withdraw();
    transfer();
}
```

That is a service interface, not command pattern.

Each operation must be its own command class.

---

### 🔹 Rule 2: Command Must Be Self-Contained

Command must store:

* Receiver reference
* Parameters
* Previous state (if undo needed)

Invoker should not pass parameters during execute.

Wrong:

```
cmd.execute(amount);
```

Correct:

```
DepositCommand(account, 500);
cmd.execute();
```

---

### 🔹 Rule 3: execute() Should Return Success

If business rules can fail:

```
virtual bool execute();
```

Invoker should push to history ONLY if success.

---

### 🔹 Rule 4: Undo Must Restore Previous State

Undo must reverse the effect.

If delete removed text:

* Store deleted text.
* Reinsert exact text during undo.

Never approximate undo.

---

### 🔹 Rule 5: Use LIFO for Undo

Undo stack must be:

```
std::stack
```

Undo = last executed command.

---

### 🔹 Rule 6: Clear Redo On New Command

If:

* User undo()
* Then executes new command

Redo stack must be cleared.

---

### 🔹 Rule 7: Domain Should Not Print

Receiver must NOT:

* Log
* Print
* Manage history

Domain = pure business logic.

Invoker = execution policy + logging.

---

### 🔹 Rule 8: Ownership Must Be Clear

Prefer:

```
std::unique_ptr<ICommand>
```

Avoid raw new/delete unless justified.

---

# 7️⃣ Common Beginner Mistakes

❌ Making ICommand contain business methods
❌ Creating receiver inside command
❌ Invoker creating concrete commands
❌ Forgetting undo state storage
❌ Using queue instead of stack for undo
❌ Not handling failure properly
❌ Mixing UI with domain
❌ Memory leaks

---

# 8️⃣ Macro Command (Advanced)

When you need:

* Batch operations
* Grouped transactions
* Composite behavior

Create:

```
MacroCommand
```

It stores a list of ICommand.

Execute → forward order
Undo → reverse order

This is Composite + Command together.

---

# 9️⃣ Architectural View

Dependency direction must look like this:

```
Main (composition root)
        ↓
Invoker
        ↓
ICommand (abstraction)
        ↓
Receiver (domain)
```

Receiver must not depend on command.

Invoker must not depend on concrete command.

---

# 🔟 Deep Understanding

Command Pattern separates:

| Responsibility             | Owner            |
| -------------------------- | ---------------- |
| How work is done           | Receiver         |
| What action to perform     | Command          |
| When and under what policy | Invoker          |
| Configuration & wiring     | Composition Root |

This is separation of concerns.

---

# 1️⃣1️⃣ Real World Where It Appears

* Text editor undo systems
* Banking transaction engines
* Job schedulers
* Event-driven systems
* Game input systems
* Macro recorders
* CQRS command handlers

It is everywhere once you start noticing.

---

# 1️⃣2️⃣ Advanced Architect Insight

Command Pattern converts:

```
Immediate behavior
```

into

```
Lifecycle-managed transaction objects
```

That enables:

* History
* Replay
* Serialization
* Distribution
* Centralized control
* Extensibility

---

# 1️⃣3️⃣ Decision Checklist Before Using It

Ask yourself:

1. Do I need undo?
2. Do I need logging?
3. Do I need centralized execution?
4. Do I need macro operations?
5. Do I need scheduling?
6. Do I need retry?
7. Do I need to treat operations as data?

If YES to multiple → Use Command.

If NO → Keep it simple.

---

# 1️⃣4️⃣ Final Memory Lock

Command Pattern is NOT:

* About abstraction for abstraction’s sake.
* About avoiding direct calls blindly.

It IS:

> About making actions first-class objects with lifecycle and policy management.

---

# 1️⃣5️⃣ One-Line Architect Summary

> Command Pattern encapsulates a business operation into a self-contained object so that execution can be controlled, stored, logged, composed, undone, and replayed independently of the caller.

---

Keep this file.
Revisit it before implementing.
If your design violates these principles, rethink.

That’s architect-level command thinking.
