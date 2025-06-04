// yarinkash1@gmail.com

#pragma once
#include <iostream>  // for std::cout
#include <vector>    // for std::vector
#include <algorithm> // for std::find and std::remove
#include <stdexcept> // for std::invalid_argument
#include <sstream>   // for std::ostringstream

using namespace std;

namespace my_cont_ns
{
    template <typename T = int> // Declares MyContainer as a template class with a default type of int
    class MyContainer
    {
    private:
        std::vector<T> elements; // Vector to store elements of type T

    public:
        /**
         * @brief Default constructor for MyContainer.
         * Initializes an empty container.
         * @param None
         * @returns MyContainer object.
         * @throw None
         */
        MyContainer()
        {
            // Empty - std::vector automatically initializes as empty
            // note: doing: elements = std::vector<T>(); here is exactly the same as not doing anything
        }

        /**
         * @brief Returns the number of elements in the container.
         * @param None
         * @returns The size of the container.
         * @throw None
         */
        size_t size() const
        {
            return elements.size();
        }

        /**
         * @brief Checks if the container is empty.
         * @param None
         * @returns true if the container is empty, false otherwise.
         * @throw None
         */
        bool isEmpty() const
        {
            return elements.empty();
        }

        /**
         * @brief Prints the elements of the container to standard output.
         *
         * @note An << operator overload is also provided for streaming(at the end of the file).
         *
         * @param None
         * @returns void
         * @throw None
         */
        void print() const
        {
            for (const auto &elem : elements)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }

        /**
         * @brief Adds an element to the container.
         * @param element The element to add to the container.
         * @returns void
         * @throw None
         */
        void add(const T &element)
        {
            elements.push_back(element);
        }

        /**
         * @brief Removes all occurrences of the specified element from the container.
         * @param element The element to remove from the container.
         * @returns void
         * @throw std::runtime_error if the element is not found.
         */

        void remove(const T &element)
        {
            // First check if element exists
            auto found = std::find(elements.begin(), elements.end(), element);
            /**
             * @note alternatively, we could have written:
             * typename std::vector<T>::iterator found = std::find(elements.begin(), elements.end(), element);
             */
            if (found == elements.end())
            {
                throw std::invalid_argument("Element not found in container");
            }
            // Remove all occurrences
            auto new_end = std::remove(elements.begin(), elements.end(), element);
            /**
             * @note alternatively, we could have written:
             * typename std::vector<T>::iterator new_end = std::remove(elements.begin(), elements.end(), element);
             */
            elements.erase(new_end, elements.end());
        }

        /**
         * @brief Returns a constant reference to the elements vector.
         * This allows read-only access to the elements stored in the container.
         * @param None
         * @returns const std::vector<T>& - reference to the elements vector.
         * @throw None
         */
        const std::vector<T> &getElements() const { return elements; }

        // == Iterator Classes with Full Implementations ==

        /**
         * @brief Nested AscendingOrder Iterator Class
         * Traverses elements from smallest to largest
         */
        class AscendingOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the AscendingOrder iterator.
             * Initializes the iterator with a sorted copy of the container's elements.
             * @param container The MyContainer instance to iterate over.
             * @returns AscendingOrder object.
             * @throw None
             */
            AscendingOrder(const MyContainer &container) : sorted_elements(container.elements), current_index(0)
            {
                // Sort the elements in ascending order
                std::sort(sorted_elements.begin(), sorted_elements.end(),std::less<T>());
            }

            /**
             * @brief Pre-increment operator for the AscendingOrder iterator.
             * @param None
             * @returns Reference to the current AscendingOrder object after incrementing.
             * @throw None
             */
            AscendingOrder &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the AscendingOrder iterator.
             * @param None
             * @returns A copy of the AscendingOrder object before incrementing.
             * @throw None
             */
            AscendingOrder operator++(int)
            {
                AscendingOrder temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the AscendingOrder iterator.
             * @param None
             * @returns A constant reference to the current element in the sorted order.
             * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
             */
            const T &operator*() const
            {
                if (current_index >= sorted_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return sorted_elements[current_index];
            }

            /**
             * @brief Equality operator for the AscendingOrder iterator.
             * @param other Another AscendingOrder iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             */
            bool operator==(const AscendingOrder &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the AscendingOrder iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another AscendingOrder iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const AscendingOrder &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the AscendingOrder iterator.
             * @param None
             * @returns A new AscendingOrder iterator starting from the first element.
             * @throw None
             */
            AscendingOrder begin()
            {
                AscendingOrder iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the AscendingOrder iterator.
             * @param None
             * @returns A new AscendingOrder iterator pointing to one past the last element.
             * @throw None
             */
            AscendingOrder end()
            {
                AscendingOrder iter = *this;
                iter.current_index = sorted_elements.size();
                return iter;
            }
        };

        /**
         * @brief Nested DescendingOrder Iterator Class
         * Traverses elements from largest to smallest
         */
        class DescendingOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the DescendingOrder iterator.
             * @param container The MyContainer instance to iterate over.
             * @returns DescendingOrder object.
             * @throw None
             */
            DescendingOrder(const MyContainer &container): sorted_elements(container.elements), current_index(0)
            {
                // Sort the elements in descending order (largest to smallest)
                std::sort(sorted_elements.begin(), sorted_elements.end(), std::greater<T>());
            }

            /**
             * @brief Pre-increment operator for the DescendingOrder iterator.
             * @param None
             * @returns Reference to the current DescendingOrder object after incrementing.
             * @throw None
             */
            DescendingOrder &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the DescendingOrder iterator.
             * @param None
             * @returns A copy of the DescendingOrder object before incrementing.
             * @throw None
             */
            DescendingOrder operator++(int)
            {
                DescendingOrder temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the DescendingOrder iterator.
             * @param None
             * @returns A constant reference to the current element in the sorted order.
             * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
             */
            const T &operator*() const
            {
                if (current_index >= sorted_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return sorted_elements[current_index];
            }

            /**
             * @brief Equality operator for the DescendingOrder iterator.
             * @param other Another DescendingOrder iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             */
            bool operator==(const DescendingOrder &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the DescendingOrder iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another DescendingOrder iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const DescendingOrder &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the DescendingOrder iterator.
             * @param None
             * @returns A new DescendingOrder iterator starting from the first element.
             * @throw None
             */
            DescendingOrder begin()
            {
                DescendingOrder iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the DescendingOrder iterator.
             * @param None
             * @returns A new DescendingOrder iterator pointing to one past the last element.
             * @throw None
             */
            DescendingOrder end()
            {
                DescendingOrder iter = *this;
                iter.current_index = sorted_elements.size();
                return iter;
            }
        };

        /**
         * @brief Nested SideCrossOrder Iterator Class
         * Alternates between smallest and largest remaining elements
         */
        class SideCrossOrder
        {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the SideCrossOrder iterator.
             * @param container The MyContainer instance to iterate over.
             * @returns SideCrossOrder object.
             * @throw None
             */
            SideCrossOrder(const MyContainer &container) : current_index(0)
            {
                // First, sort all elements
                std::vector<T> temp_sorted = container.elements;
                std::sort(temp_sorted.begin(), temp_sorted.end());

                sorted_elements.reserve(container.elements.size()); // Reserve space for efficiency (allocate once)

                // Create side-cross order: smallest, largest, second smallest, second largest, etc.
                size_t left = 0;
                size_t right = temp_sorted.size();
                bool take_from_left = true;

                while (left < right)
                {
                    if (take_from_left)
                    {
                        sorted_elements.push_back(temp_sorted[left]);
                        ++left;
                    }
                    else
                    {
                        --right;
                        sorted_elements.push_back(temp_sorted[right]);
                    }
                    take_from_left = !take_from_left; // Alternate between left and right
                }
            }

            /**
             * @brief Pre-increment operator for the SideCrossOrder iterator.
             * @param None
             * @returns Reference to the current SideCrossOrder object after incrementing.
             * @throw None
             */
            SideCrossOrder &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the SideCrossOrder iterator.
             * @param None
             * @returns A copy of the SideCrossOrder object before incrementing.
             * @throw None
             */
            SideCrossOrder operator++(int)
            {
                SideCrossOrder temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the SideCrossOrder iterator.
             * @param None
             * @returns A constant reference to the current element in the side-cross order.
             * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
             */
            const T &operator*() const
            {
                if (current_index >= sorted_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return sorted_elements[current_index];
            }

            /**
             * @brief Equality operator for the SideCrossOrder iterator.
             * @param other Another SideCrossOrder iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             * @throw None
             */
            bool operator==(const SideCrossOrder &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the SideCrossOrder iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another SideCrossOrder iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const SideCrossOrder &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the SideCrossOrder iterator.
             * @param None
             * @returns A new SideCrossOrder iterator starting from the first element.
             * @throw None
             */
            SideCrossOrder begin()
            {
                SideCrossOrder iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the SideCrossOrder iterator.
             * @param None
             * @returns A new SideCrossOrder iterator pointing to one past the last element.
             * @throw None
             */
            SideCrossOrder end()
            {
                SideCrossOrder iter = *this;
                iter.current_index = sorted_elements.size();
                return iter;
            }
        };

        /**
         * @brief Nested ReverseOrder Iterator Class
         * Traverses elements in reverse insertion order
         */
        class ReverseOrder
        {
        private:
            std::vector<T> reverse_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the ReverseOrder iterator.
             * @param container The MyContainer instance to iterate over.
             * @returns ReverseOrder object.
             * @throw None
             */
            ReverseOrder(const MyContainer &container) : current_index(0)
            {
                // Copy elements in reverse order
                reverse_elements.reserve(container.elements.size()); // Reserve space for efficiency(allicate once)
                for (auto it = container.elements.rbegin(); it != container.elements.rend(); ++it)
                {
                    reverse_elements.push_back(*it);
                }
            }

            /**
             * @brief Pre-increment operator for the ReverseOrder iterator.
             * @param None
             * @returns Reference to the current ReverseOrder object after incrementing.
             * @throw None
             */
            ReverseOrder &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the ReverseOrder iterator.
             * @param None
             * @returns A copy of the ReverseOrder object before incrementing.
             * @throw None
             */
            ReverseOrder operator++(int)
            {
                ReverseOrder temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the ReverseOrder iterator.
             * @param None
             * @returns A constant reference to the current element in reverse order.
             * @throw std::out_of_range if the current index exceeds the size of reverse_elements.
             */
            const T &operator*() const
            {
                if (current_index >= reverse_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return reverse_elements[current_index];
            }

            /**
             * @brief Equality operator for the ReverseOrder iterator.
             * @param other Another ReverseOrder iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             * @throw None
             */
            bool operator==(const ReverseOrder &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the ReverseOrder iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another ReverseOrder iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const ReverseOrder &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the ReverseOrder iterator.
             * @param None
             * @returns A new ReverseOrder iterator starting from the first element.
             * @throw None
             */
            ReverseOrder begin()
            {
                ReverseOrder iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the ReverseOrder iterator.
             * @param None
             * @returns A new ReverseOrder iterator pointing to one past the last element.
             * @throw None
             */
            ReverseOrder end()
            {
                ReverseOrder iter = *this;
                iter.current_index = reverse_elements.size();
                return iter;
            }
        };

        /**
         * @brief Nested Order Iterator Class
         * Traverses elements in original insertion order
         */
        class Order
        {
        private:
            std::vector<T> original_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the Order iterator.
             * @param container The MyContainer instance to iterate over.
             * @returns Order object.
             * @throw None
             */
            Order(const MyContainer &container): original_elements(container.elements), current_index(0)
            {
                // Simply copy elements in their original order - no sorting needed
            }

            /**
             * @brief Pre-increment operator for the Order iterator.
             * @param None
             * @returns Reference to the current Order object after incrementing.
             * @throw None
             */
            Order &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the Order iterator.
             * @param None
             * @returns A copy of the Order object before incrementing.
             * @throw None
             */
            Order operator++(int)
            {
                Order temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the Order iterator.
             * @param None
             * @returns A constant reference to the current element in original order.
             * @throw std::out_of_range if the current index exceeds the size of original_elements.
             */
            const T &operator*() const
            {
                if (current_index >= original_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return original_elements[current_index];
            }

            /**
             * @brief Equality operator for the Order iterator.
             * @param other Another Order iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             * @throw None
             */
            bool operator==(const Order &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the Order iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another Order iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const Order &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the Order iterator.
             * @param None
             * @returns A new Order iterator starting from the first element.
             * @throw None
             */
            Order begin()
            {
                Order iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the Order iterator.
             * @param None
             * @returns A new Order iterator pointing to one past the last element.
             * @throw None
             */
            Order end()
            {
                Order iter = *this;
                iter.current_index = original_elements.size();
                return iter;
            }
        };

        /**
         * @brief Nested MiddleOutOrder Iterator Class
         * Starts from middle, then alternates left-right
         */
        class MiddleOutOrder
        {
        private:
            std::vector<T> middle_out_elements;
            size_t current_index;

        public:
            /**
             * @brief Constructor for the MiddleOutOrder iterator.
             * 
             * @note if the number of elements is even, it starts from the left middle.
             * 
             * @param container The MyContainer instance to iterate over.
             * @returns MiddleOutOrder object.
             * @throw None
             */
            MiddleOutOrder(const MyContainer &container) : current_index(0)
            {
                if (container.elements.empty())
                {
                    return; // Nothing to arrange
                }

                middle_out_elements.reserve(container.elements.size()); // Reserve space for efficiency (allocate once)

                const std::vector<T> &elements = container.elements;
                size_t size = elements.size();

                // Calculate middle index (for even numbers, choose left middle)
                size_t middle = (size - 1) / 2;

                // Start with the middle element
                middle_out_elements.push_back(elements[middle]);

                // Now alternate left and right from the middle
                size_t left = middle;
                size_t right = middle;
                bool go_left = true;

                while (left > 0 || right < size - 1)
                {
                    if (go_left && left > 0)
                    {
                        --left;
                        middle_out_elements.push_back(elements[left]);
                        go_left = false; // Switch to right
                    }
                    else if (!go_left && right < size - 1)
                    {
                        ++right;
                        middle_out_elements.push_back(elements[right]);
                        go_left = true; // Switch to left
                    }
                    else
                    {
                        // If we can't go in the current direction, try the other
                        go_left = !go_left; // Alternate direction
                    }
                }
            }

            /**
             * @brief Pre-increment operator for the MiddleOutOrder iterator.
             * @param None
             * @returns Reference to the current MiddleOutOrder object after incrementing.
             * @throw None
             */
            MiddleOutOrder &operator++()
            {
                ++current_index;
                return *this;
            }

            /**
             * @brief Post-increment operator for the MiddleOutOrder iterator.
             * @param None
             * @returns A copy of the MiddleOutOrder object before incrementing.
             * @throw None
             */
            MiddleOutOrder operator++(int)
            {
                MiddleOutOrder temp = *this;
                ++current_index;
                return temp;
            }

            /**
             * @brief Dereference operator for the MiddleOutOrder iterator.
             * @param None
             * @returns A constant reference to the current element in middle-out order.
             * @throw std::out_of_range if the current index exceeds the size of middle_out_elements.
             */
            const T &operator*() const
            {
                if (current_index >= middle_out_elements.size())
                {
                    throw std::out_of_range("Iterator out of range");
                }
                return middle_out_elements[current_index];
            }

            /**
             * @brief Equality operator for the MiddleOutOrder iterator.
             * @param other Another MiddleOutOrder iterator to compare with.
             * @returns true if both iterators point to the same index, false otherwise.
             * @throw None
             */
            bool operator==(const MiddleOutOrder &other) const
            {
                return current_index == other.current_index;
            }

            /**
             * @brief Inequality operator for the MiddleOutOrder iterator.
             * 
             * @note This function uses the equality operator to determine inequality.
             * 
             * @param other Another MiddleOutOrder iterator to compare with.
             * @returns true if the iterators point to different indices, false otherwise.
             * @throw None
             */
            bool operator!=(const MiddleOutOrder &other) const
            {
                return !(*this == other);
            }

            /**
             * @brief Begin method for the MiddleOutOrder iterator.
             * @param None
             * @returns A new MiddleOutOrder iterator starting from the first element.
             * @throw None
             */
            MiddleOutOrder begin()
            {
                MiddleOutOrder iter = *this;
                iter.current_index = 0;
                return iter;
            }

            /**
             * @brief End method for the MiddleOutOrder iterator.
             * @param None
             * @returns A new MiddleOutOrder iterator pointing to one past the last element.
             * @throw None
             */
            MiddleOutOrder end()
            {
                MiddleOutOrder iter = *this;
                iter.current_index = middle_out_elements.size();
                return iter;
            }
        };

        // Factory methods to create iterators:
        AscendingOrder getAscendingOrder() const { return AscendingOrder(*this); }

        DescendingOrder getDescendingOrder() const { return DescendingOrder(*this); }

        SideCrossOrder getSideCrossOrder() const { return SideCrossOrder(*this); }

        ReverseOrder getReverseOrder() const { return ReverseOrder(*this); }

        Order getOrder() const { return Order(*this); }

        MiddleOutOrder getMiddleOutOrder() const { return MiddleOutOrder(*this); }
    };

    /**
     * @brief Stream output operator for MyContainer
     * Allows printing container contents using operator<<
     * @param os The output stream to write to.
     * @param container The MyContainer instance to print.
     * @returns The output stream after writing the container contents.
     * @throw None
     */
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