#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <stdexcept>
#include <iostream>

#define ERROR_MESSAGE std::invalid_argument("Error: vectors must be the same size")

// Operator overloading for vector operations
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";  // Changed from "," to ", "
    }
    os << "]";
    return os;
}

template<typename T, typename U>
std::vector<double> operator+(const std::vector<T>& lhs, const std::vector<U>& rhs) {
    if (lhs.size() != rhs.size()) throw ERROR_MESSAGE;
    std::vector<double> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = static_cast<double>(lhs[i]) + static_cast<double>(rhs[i]);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator-(const std::vector<T>& lhs, const std::vector<U>& rhs) {
    if (lhs.size() != rhs.size()) throw ERROR_MESSAGE;
    std::vector<double> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = static_cast<double>(lhs[i]) - static_cast<double>(rhs[i]);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator*(const std::vector<T>& lhs, const std::vector<U>& rhs) {
    if (lhs.size() != rhs.size()) throw ERROR_MESSAGE;
    std::vector<double> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = static_cast<double>(lhs[i]) * static_cast<double>(rhs[i]);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator*(const T& scalar, const std::vector<U>& vec) {
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = static_cast<double>(scalar) * static_cast<double>(vec[i]);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator/(const std::vector<T>& lhs, const std::vector<U>& rhs) {
    if (lhs.size() != rhs.size()) throw ERROR_MESSAGE;
    std::vector<double> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (rhs[i] == 0) throw std::runtime_error("Error: division by zero");
        result[i] = static_cast<double>(lhs[i]) / static_cast<double>(rhs[i]);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator/(const std::vector<T>& vec, const U& scalar) {
    if (scalar == 0) throw std::runtime_error("Error: division by zero");
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = static_cast<double>(vec[i]) / static_cast<double>(scalar);
    }
    return result;
}

template<typename T, typename U>
std::vector<double> operator,(const std::vector<T>& lhs, const std::vector<U>& rhs) {
    std::vector<double> result;
    result.reserve(lhs.size() + rhs.size());
    for (const auto& elem : lhs) result.push_back(static_cast<double>(elem));
    for (const auto& elem : rhs) result.push_back(static_cast<double>(elem));
    return result;
}

#endif // OPERATORS_H