export module decorators;
export import <vector>;

export class Component {
public:
    virtual std::vector<float> calculate(const std::vector<float>& input) const = 0;
    virtual ~Component() = default;
};

export class Decorator : public Component {
// Add any fields necessary
protected:
    Component* next;
public:
    explicit Decorator(Component* next); // Fill out constructor
    virtual ~Decorator(); // Fill out destructor
};

export class Input : public Component {
public:
    // Fill out calculate method
    std::vector<float> calculate(const std::vector<float>& input) const override;
};

export class Bias : public Decorator {
    // Add any private fields necessary
    std::vector<float> bias;
public:
    // Fill out constructor
    Bias(const std::vector<float>& bias, Component* next);
    // Fill out calculate method
    std::vector<float> calculate(const std::vector<float>& input) const override;
};

export class Weight : public Decorator {
    // Add any private fields necessary
    std::vector<std::vector<float>> weights;
public:
    // Fill out constructor
    Weight(const std::vector<std::vector<float>>& weights, Component* next);
    // Fill out calculate method
    std::vector<float> calculate(const std::vector<float>& input) const override;
};

export template <typename Func> class ActivationFunction : public Decorator {
    // The template means we don't have to remember function pointer syntax!
    Func fn;
public:
    // Fill out constructor
    ActivationFunction(const Func& fn, Component* next);
    // Fill out calculate method
    std::vector<float> calculate(const std::vector<float>& input) const override;
};
