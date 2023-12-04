#include <iostream>
#include <chrono>
#include <thread>

// gate superclasses

class Clock;

class LogicGate {
protected:
    Clock* clock = nullptr;

public:
    virtual bool getOutput() const = 0;
    void connectClock(Clock &clk) {
        clock = &clk;
    }
    virtual ~LogicGate() = default;
};

class UnaryInputGate : public LogicGate {
protected:
    LogicGate *input1 = nullptr;

public:
    void setInput(LogicGate &a) {
        input1 = &a;
    }
    virtual ~UnaryInputGate() = default;
};

class BinaryInputGate : public LogicGate {
protected:
    LogicGate *input1 = nullptr;
    LogicGate *input2 = nullptr;

public:
    void setInput(LogicGate &a, LogicGate &b) {
        input1 = &a;
        input2 = &b;
    }
    virtual ~BinaryInputGate() = default;
};

class Clock : public LogicGate {
private:
    bool state = false;
    unsigned int interval; // milliseconds

public:
    Clock(unsigned int interval_ms) : interval(interval_ms) {}

    void tick() {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        state = !state;
    }

    bool getOutput() const override {
        return state;
    }
};

// gate subclasses

class TrueInput : public LogicGate {
public:
    bool getOutput() const override {
        return true;
    }
};

class FalseInput : public LogicGate {
public:
    bool getOutput() const override {
        return false;
    }
};

class AndGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output

public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = (input1 ? input1->getOutput() : false) && (input2 ? input2->getOutput() : false);
        return lastOutput;
    }
};

class OrGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output

public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = (input1 ? input1->getOutput() : false) || (input2 ? input2->getOutput() : false);
        return lastOutput;
    }
};

class NotGate : public UnaryInputGate {
private:
    mutable bool lastOutput = false; // last output
    
public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = !(input1 ? input1->getOutput() : false);
        return lastOutput;
    }
};

class NandGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output
    
public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = !((input1 ? input1->getOutput() : true) && (input2 ? input2->getOutput() : true));
        return lastOutput;
    }
};


class XorGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output
    
public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = (input1 ? input1->getOutput() : false) ^ (input2 ? input2->getOutput() : false);
        return lastOutput;
    }
};

class NorGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output
    
public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = !((input1 ? input1->getOutput() : false) || (input2 ? input2->getOutput() : false));
        return lastOutput;
    }
};

class XnorGate : public BinaryInputGate {
private:
    mutable bool lastOutput = false; // last output
    
public:
    bool getOutput() const override {
        if (clock && clock->getOutput()) // if clock high
            lastOutput = !((input1 ? input1->getOutput() : false) ^ (input2 ? input2->getOutput() : false));
        return lastOutput;
    }
};

int main() {
    // Initialize gates and clock
    FalseInput F;
    TrueInput T;
    AndGate andGate;
    OrGate orGate;
    NotGate notGate;
    NandGate nandGate;
    XorGate xorGate;
    NorGate norGate;
    XnorGate xnorGate;
    
    // clock with 500ms intervals
    Clock clk(500);

    // gate-clock connect
    andGate.connectClock(clk);
    orGate.connectClock(clk);
    notGate.connectClock(clk);
    nandGate.connectClock(clk);
    xorGate.connectClock(clk);
    norGate.connectClock(clk);
    xnorGate.connectClock(clk);

    // gate inputs
    andGate.setInput(T, F);
    orGate.setInput(F, T);
    notGate.setInput(F);
    nandGate.setInput(T, T);
    xorGate.setInput(T, F);
    norGate.setInput(F, F);
    xnorGate.setInput(T, T);

    // simulate clock cycling and gate inputs
    for (int i = 0; i < 10; ++i) {
        clk.tick();

        std::cout << "Clock state: " << clk.getOutput();
        std::cout << " | AND: " << andGate.getOutput();
        std::cout << " | OR: " << orGate.getOutput();
        std::cout << " | NOT: " << notGate.getOutput();
        std::cout << " | NAND: " << nandGate.getOutput();
        std::cout << " | XOR: " << xorGate.getOutput();
        std::cout << " | NOR: " << norGate.getOutput();
        std::cout << " | XNOR: " << xnorGate.getOutput();
        std::cout << std::endl;
    }


    return 0;
}