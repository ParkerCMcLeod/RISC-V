#include <iostream>

// gate superclasses

class LogicGate {
public:
    virtual bool getOutput() const = 0;
    virtual ~LogicGate() = default;
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

class UnaryInputGate : public LogicGate {
protected:
    LogicGate *input1 = nullptr;

public:
    void setInput(LogicGate &a) {
        input1 = &a;
    }
    virtual ~UnaryInputGate() = default;
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
public:
    bool getOutput() const override {
        return (input1 ? input1->getOutput() : false) && (input2 ? input2->getOutput() : false);
    }
};

class OrGate : public BinaryInputGate {
public:
    bool getOutput() const override {
        return (input1 ? input1->getOutput() : false) || (input2 ? input2->getOutput() : false);
    }
};

class NotGate : public UnaryInputGate {
public:
    bool getOutput() const override {
        return !(input1 ? input1->getOutput() : false);
    }
};

class NandGate : public BinaryInputGate {
public:
    bool getOutput() const override {
        return !((input1 ? input1->getOutput() : true) && (input2 ? input2->getOutput() : true));
    }
};


class XorGate : public BinaryInputGate {
public:
    bool getOutput() const override {
        return (input1 ? input1->getOutput() : false) ^ (input2 ? input2->getOutput() : false);
    }
};

class NorGate : public BinaryInputGate {
public:
    bool getOutput() const override {
        return !((input1 ? input1->getOutput() : false) || (input2 ? input2->getOutput() : false));
    }
};

class XnorGate : public BinaryInputGate {
public:
    bool getOutput() const override {
        return !((input1 ? input1->getOutput() : false) ^ (input2 ? input2->getOutput() : false));
    }
};

int main() {

    // testing basic gate functionality

    FalseInput F;
    TrueInput T;

    AndGate andGate;
    OrGate orGate;
    NotGate notGate;
    NandGate nandGate;

    std::cout << "AND:" << std::endl;
    andGate.setInput(F, F);
    std::cout << andGate.getOutput() << std::endl;
    andGate.setInput(F, T);
    std::cout << andGate.getOutput() << std::endl;
    andGate.setInput(T, F);
    std::cout << andGate.getOutput() << std::endl;
    andGate.setInput(T, T);
    std::cout << andGate.getOutput() << std::endl;
    std::cout << std::endl;

    std::cout << "OR:" << std::endl;
    orGate.setInput(F, F);
    std::cout << orGate.getOutput() << std::endl;
    orGate.setInput(F, T);
    std::cout << orGate.getOutput() << std::endl;
    orGate.setInput(T, F);
    std::cout << orGate.getOutput() << std::endl;
    orGate.setInput(T, T);
    std::cout << orGate.getOutput() << std::endl;
    std::cout << std::endl;

    std::cout << "NOT:" << std::endl;
    notGate.setInput(F);
    std::cout << notGate.getOutput() << std::endl;
    notGate.setInput(T);
    std::cout << notGate.getOutput() << std::endl;
    std::cout << std::endl;

    std::cout << "NAND:" << std::endl;
    nandGate.setInput(orGate, andGate);
    std::cout << nandGate.getOutput() << std::endl;
    nandGate.setInput(orGate, F);
    std::cout << nandGate.getOutput() << std::endl;
    std::cout << std::endl;

    return 0;
}