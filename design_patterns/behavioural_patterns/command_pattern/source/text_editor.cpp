/*
PROBLEM STATEMENT:

Design and implement a mini text editor core engine in C++ using the Command Pattern.

🎯 Requirements
You must design a text editing engine that supports:

1️⃣ Basic Editing
Insert text at position
Delete text from position
Replace text

2️⃣ Undo / Redo
Unlimited undo
Unlimited redo
Proper state restoration


3️⃣ Logging
Every executed command must be logged.
[10:21] Insert "Hello" at position 0
[10:22] Delete 3 chars at position 5

4️⃣ Deferred Execution
Commands can be queued and executed later.
Example:
Batch editing script
Background execution
----------------------------------------

EXPECTED SYSTEM BEHAVIOR

Your system must support scenarios like:

Insert("Hello")
Insert(" World")
Undo()
Redo()

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Design Thinking:
Core Engine(Receiver)
1. insert text
2. delete text
3. replace text


Commands
1. Insert text: execute, unexecute
2. delete text: execute, unexecute
3. Repalce text: execute, unexecute

Application: Notepad(Invoker)
click and unclick button with logging
*/


#include <iostream>
#include <string>
#include <stack>
#include <memory>
#include <vector>
#include <ctime>

// ===================== RECEIVER =====================

class Document {
private:
    std::string content;

public:
    void insert(size_t position, const std::string& text) {
        content.insert(position, text);
    }

    std::string erase(size_t position, size_t length) {
        std::string removed = content.substr(position, length);
        content.erase(position, length);
        return removed;
    }

    void replace(size_t position, size_t length, const std::string& text) {
        content.replace(position, length, text);
    }

    const std::string& getContent() const {
        return content;
    }
};

// ===================== COMMAND INTERFACE =====================

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual std::string description() const = 0;
};

// ===================== INSERT COMMAND =====================

class InsertCommand : public ICommand {
private:
    Document& doc;
    size_t position;
    std::string text;

public:
    InsertCommand(Document& d, size_t pos, std::string t)
        : doc(d), position(pos), text(std::move(t)) {}

    bool execute() override {
        doc.insert(position, text);
        return true;
    }

    void undo() override {
        doc.erase(position, text.length());
    }

    std::string description() const override {
        return "Insert \"" + text + "\" at position " + std::to_string(position);
    }
};

// ===================== DELETE COMMAND =====================

class DeleteCommand : public ICommand {
private:
    Document& doc;
    size_t position;
    size_t length;
    std::string deletedText;

public:
    DeleteCommand(Document& d, size_t pos, size_t len)
        : doc(d), position(pos), length(len) {}

    bool execute() override {
        deletedText = doc.erase(position, length);
        return true;
    }

    void undo() override {
        doc.insert(position, deletedText);
    }

    std::string description() const override {
        return "Delete " + std::to_string(length) +
               " chars at position " + std::to_string(position);
    }
};


// ===================== MACRO COMMAND =====================

class MacroCommand : public ICommand {
private:
    std::vector<std::unique_ptr<ICommand>> commands;

public:
    void add(std::unique_ptr<ICommand> cmd) {
        commands.push_back(std::move(cmd));
    }

    bool execute() override {
        for (auto& cmd : commands)
            cmd->execute();
        return true;
    }

    void undo() override {
        for (auto it = commands.rbegin(); it != commands.rend(); ++it)
            (*it)->undo();
    }

    std::string description() const override {
        return "MacroCommand (" + std::to_string(commands.size()) + " operations)";
    }
};


// ===================== INVOKER =====================

class EditorController {
private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;

    void log(const std::string& msg) {
        std::time_t now = std::time(nullptr);
        std::cout << "[" << now << "] " << msg << "\n";
    }

public:
    void execute(std::unique_ptr<ICommand> cmd) {
        if (cmd->execute()) {
            log(cmd->description());
            undoStack.push(std::move(cmd));

            // Clear redo stack
            while (!redoStack.empty())
                redoStack.pop();
        }
    }

    void undo() {
        if (undoStack.empty()) return;

        auto cmd = std::move(undoStack.top());
        undoStack.pop();

        cmd->undo();
        log("Undo: " + cmd->description());

        redoStack.push(std::move(cmd));
    }

    void redo() {
        if (redoStack.empty()) return;

        auto cmd = std::move(redoStack.top());
        redoStack.pop();

        cmd->execute();
        log("Redo: " + cmd->description());

        undoStack.push(std::move(cmd));
    }
};



// ===================== MAIN =====================

int main() {
    Document doc;
    EditorController controller;

    controller.execute(
        std::make_unique<InsertCommand>(doc, 0, "Hello")
    );

    controller.execute(
        std::make_unique<InsertCommand>(doc, 5, " World")
    );

    std::cout << "Current: " << doc.getContent() << "\n";

    controller.undo();
    std::cout << "After Undo: " << doc.getContent() << "\n";

    controller.redo();
    std::cout << "After Redo: " << doc.getContent() << "\n";

    return 0;
}