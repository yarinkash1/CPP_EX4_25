#pragma once
#include <iostream>
#include <vector>
#include <algorithm> // for std::find and std::remove
#include <stdexcept> // for std::invalid_argument
using namespace std;

namespace my_cont_ns
{
    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> elements;

    public:
        MyContainer();
        size_t size() const;
        bool isEmpty() const;
        void print() const;
        void add(const T &element);
        void remove(const T &element);

        // Containers:
        // Forward declaration of nested iterator class
        class AscendingOrder;

        // Factory method to create iterators
        AscendingOrder getAscendingOrder() const;

        // Nested AscendingOrder Iterator Class
        class AscendingOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            // Constructor
            AscendingOrder(const MyContainer& container);

            // Iterator operations
            AscendingOrder& operator++();    // Pre-increment
            AscendingOrder operator++(int);  // Post-increment
            const T& operator*() const;      // Dereference
            bool operator!=(const AscendingOrder& other) const;
            bool operator==(const AscendingOrder& other) const;
            // Begin and end
            AscendingOrder begin();
            AscendingOrder end();
        };
    };
}