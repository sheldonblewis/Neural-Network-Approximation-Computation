module;
import <vector>;

import decorators;

Decorator::Decorator(Component* next) : next{next} {}

Decorator::~Decorator() { delete next; }

std::vector<float> Input::calculate(const std::vector<float>& input) const {
    return input;
}

Bias::Bias(const std::vector<float>& bias, Component* next)
    : Decorator{next}, bias{bias} {}

std::vector<float> Bias::calculate(const std::vector<float>& input) const {
    std::vector<float> result = next->calculate(input);
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] += bias[i];
    }
    return result;
}

Weight::Weight(const std::vector<std::vector<float>>& weights, Component* next)
    : Decorator{next}, weights{weights} {}

std::vector<float> Weight::calculate(const std::vector<float>& input) const {
    std::vector<float> result(weights.size(), 0.0f);
    std::vector<float> next_input = next->calculate(input);
    for (size_t i = 0; i < weights.size(); ++i) {
        for (size_t j = 0; j < weights[i].size(); ++j) {
            result[i] += weights[i][j] * next_input[j];
        }
    }
    return result;
}

template <typename Func>
ActivationFunction<Func>::ActivationFunction(const Func& fn, Component* next)
    : Decorator{next}, fn{fn} {}

template <typename Func>
std::vector<float> ActivationFunction<Func>::calculate(const std::vector<float>& input) const {
    std::vector<float> result = next->calculate(input);
    for (auto& val : result) {
        val = fn(val);
    }
    return result;
}

// Explicit instantiations for supported function pointer types
template class ActivationFunction<float (*)(float)>;
