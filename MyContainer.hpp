// yarinkash1@gmail.com

#pragma once
#include <iostream>  // for std::cout
#include <vector>    // for std::vector
#include <algorithm> // for std::find and std::remove
#include <stdexcept> // for std::invalid_argument
using namespace std;

namespace my_cont_ns
{
    template <typename T = int> // Declares MyContainer as a template class with a default type of int
    class MyContainer
    {
    private:
        std::vector<T> elements; // Vector to store elements of type T

    public:
        MyContainer();
        size_t size() const;
        bool isEmpty() const;
        void print() const;
        void add(const T &element);
        void remove(const T &element);

        // Forward declaration of nested iterators classes
        //(tells the compiler that these classes exist but doesn't define them yet)
        class AscendingOrder;
        class DescendingOrder;
        class SideCrossOrder;
        class ReverseOrder;
        class Order;
        class MiddleOutOrder;

        // Factory methods to create iterators (wouldn't work without forward declaration):

        AscendingOrder getAscendingOrder() const;
        DescendingOrder getDescendingOrder() const;
        SideCrossOrder getSideCrossOrder() const;
        ReverseOrder getReverseOrder() const;
        Order getOrder() const;
        MiddleOutOrder getMiddleOutOrder() const;
        const std::vector<T> &getElements() const { return elements; }

        // **Nested AscendingOrder Iterator Class**
        class AscendingOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            // Constructor
            AscendingOrder(const MyContainer &container);

            // Iterator operations
            AscendingOrder &operator++();   // Pre-increment
            AscendingOrder operator++(int); // Post-increment
            const T &operator*() const;     // Dereference
            bool operator!=(const AscendingOrder &other) const;
            bool operator==(const AscendingOrder &other) const;
            // Begin and end
            AscendingOrder begin();
            AscendingOrder end();
        };

        // **Nested DescendingOrder Iterator Class**
        class DescendingOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            // Constructor
            DescendingOrder(const MyContainer &container);

            // Iterator operations
            DescendingOrder &operator++();   // Pre-increment
            DescendingOrder operator++(int); // Post-increment
            const T &operator*() const;      // Dereference
            bool operator!=(const DescendingOrder &other) const;
            bool operator==(const DescendingOrder &other) const;

            // Begin and end
            DescendingOrder begin();
            DescendingOrder end();
        };

        // **Nested SideCrossOrder Iterator Class**
        class SideCrossOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            // Constructor
            SideCrossOrder(const MyContainer &container);

            // Iterator operations
            SideCrossOrder &operator++();   // Pre-increment
            SideCrossOrder operator++(int); // Post-increment
            const T &operator*() const;     // Dereference
            bool operator!=(const SideCrossOrder &other) const;
            bool operator==(const SideCrossOrder &other) const;

            // Begin and end
            SideCrossOrder begin();
            SideCrossOrder end();
        };
        // **Nested ReverseOrder Iterator Class**
        class ReverseOrder
        {
        private:
            std::vector<T> reverse_elements;
            size_t current_index;

        public:
            // Constructor
            ReverseOrder(const MyContainer &container);

            // Iterator operations
            ReverseOrder &operator++();   // Pre-increment
            ReverseOrder operator++(int); // Post-increment
            const T &operator*() const;   // Dereference
            bool operator!=(const ReverseOrder &other) const;
            bool operator==(const ReverseOrder &other) const;

            // Begin and end
            ReverseOrder begin();
            ReverseOrder end();
        };

        // **Nested Order Iterator Class**
        class Order
        {
        private:
            std::vector<T> original_elements;
            size_t current_index;

        public:
            // Constructor
            Order(const MyContainer &container);

            // Iterator operations
            Order &operator++();        // Pre-increment
            Order operator++(int);      // Post-increment
            const T &operator*() const; // Dereference
            bool operator!=(const Order &other) const;
            bool operator==(const Order &other) const;

            // Begin and end
            Order begin();
            Order end();
        };

        // **Nested MiddleOutOrder Iterator Class**
        class MiddleOutOrder
        {
        private:
            std::vector<T> middle_out_elements;
            size_t current_index;

        public:
            // Constructor
            MiddleOutOrder(const MyContainer &container);

            // Iterator operations
            MiddleOutOrder &operator++();   // Pre-increment
            MiddleOutOrder operator++(int); // Post-increment
            const T &operator*() const;     // Dereference
            bool operator!=(const MiddleOutOrder &other) const;
            bool operator==(const MiddleOutOrder &other) const;

            // Begin and end
            MiddleOutOrder begin();
            MiddleOutOrder end();
        };
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const MyContainer<T> &container)
    {
        const auto &elements = container.getElements();
        for (const auto &elem : elements)
        {
            os << elem << " ";
        }
        return os;
    }
}