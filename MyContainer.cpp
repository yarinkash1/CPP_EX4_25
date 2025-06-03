// yarinkash1@gmail.com

#include "MyContainer.hpp"

namespace my_cont_ns
{
    // == MyContainer Class Implementation ==
    /**
     * @brief Default constructor for MyContainer.
     * Initializes an empty container.
     * @param None
     * @returns MyContainer object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::MyContainer()
    {
        // Empty - std::vector automatically initializes as empty
    }

    /**
     * @brief Checks if the container is empty.
     * @param None
     * @returns true if the container is empty, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::isEmpty() const
    {
        return elements.empty();
    }

    /**
     * @brief Adds an element to the container.
     * @param element The element to add to the container.
     * @returns void
     * @throw None
     */
    template <typename T>
    void MyContainer<T>::add(const T &element)
    {
        elements.push_back(element);
    }

    /**
     * @brief Removes all occurrences of the specified element from the container.
     * @param element The element to remove from the container.
     * @returns void
     * @throw std::runtime_error if the element is not found.
     */
    template <typename T>
    void MyContainer<T>::remove(const T &element)
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
     * @brief Returns the number of elements in the container.
     * @param None
     * @returns The size of the container.
     * @throw None
     */
    template <typename T>
    size_t MyContainer<T>::size() const
    {
        return elements.size();
    }

    /**
     * @brief Prints the elements of the container to standard output.
     * @param None
     * @returns void
     * @throw None
     */
    template <typename T>
    void MyContainer<T>::print() const
    {
        for (const auto &elem : elements)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // == Iterator Implementation ==
    // **AscendingOrder Iterator Implementation**

    /**
     * @brief Constructor for the AscendingOrder iterator.
     * Initializes the iterator with a sorted copy of the container's elements.
     * @param container The MyContainer object to iterate over.
     * @returns AscendingOrder object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::AscendingOrder::AscendingOrder(const MyContainer &container)
        : sorted_elements(container.elements), current_index(0)
    {
        // Sort the elements in ascending order
        std::sort(sorted_elements.begin(), sorted_elements.end());
    }

    /**
     * @brief Pre-increment operator for the AscendingOrder iterator.
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current AscendingOrder object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::AscendingOrder &MyContainer<T>::AscendingOrder::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the AscendingOrder iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current AscendingOrder object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::AscendingOrder MyContainer<T>::AscendingOrder::operator++(int)
    {
        AscendingOrder temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the AscendingOrder iterator.
     * Compares two AscendingOrder iterators.
     * @param other The other AscendingOrder iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::AscendingOrder::operator==(const AscendingOrder &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the AscendingOrder iterator.
     * Compares two AscendingOrder iterators.
     * @param other The other AscendingOrder iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::AscendingOrder::operator!=(const AscendingOrder &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the AscendingOrder iterator.
     *
     * @param None
     * @returns A reference to the current element in the sorted order.
     * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
     */
    template <typename T>
    const T &MyContainer<T>::AscendingOrder::operator*() const
    {
        if (current_index >= sorted_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return sorted_elements[current_index];
    }

    /**
     * @brief Begin method for the AscendingOrder iterator.
     * Initializes the iterator to the start of the sorted elements.
     * @param None
     * @returns An AscendingOrder iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::AscendingOrder MyContainer<T>::AscendingOrder::begin()
    {
        AscendingOrder iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the AscendingOrder iterator.
     * Initializes the iterator to the end of the sorted elements.
     * @param None
     * @returns An AscendingOrder iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::AscendingOrder MyContainer<T>::AscendingOrder::end()
    {
        AscendingOrder iter = *this;
        iter.current_index = sorted_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create an AscendingOrder iterator for the MyContainer.
     * This method returns an instance of the AscendingOrder iterator initialized with the current container.
     * @param None
     * @returns An AscendingOrder iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::AscendingOrder MyContainer<T>::getAscendingOrder() const
    {
        return AscendingOrder(*this);
    }

    // ** DescendingOrder Iterator Implementation **

    /**
     * @brief Constructor for the DescendingOrder iterator.
     * Initializes the iterator with a reverse-sorted copy of the container's elements.
     * @param container The MyContainer object to iterate over.
     * @returns DescendingOrder object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::DescendingOrder::DescendingOrder(const MyContainer &container)
        : sorted_elements(container.elements), current_index(0)
    {
        // Sort the elements in descending order (largest to smallest)
        std::sort(sorted_elements.begin(), sorted_elements.end(), std::greater<T>());
    }

    /**
     * @brief Pre-increment operator for the DescendingOrder iterator.
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current DescendingOrder object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::DescendingOrder &MyContainer<T>::DescendingOrder::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the DescendingOrder iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current DescendingOrder object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::DescendingOrder MyContainer<T>::DescendingOrder::operator++(int)
    {
        DescendingOrder temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the DescendingOrder iterator.
     * Compares two DescendingOrder iterators.
     * @param other The other DescendingOrder iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::DescendingOrder::operator==(const DescendingOrder &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the DescendingOrder iterator.
     * Compares two DescendingOrder iterators.
     * @param other The other DescendingOrder iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::DescendingOrder::operator!=(const DescendingOrder &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the DescendingOrder iterator.
     *
     * @param None
     * @returns A reference to the current element in the reverse sorted order.
     * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
     */
    template <typename T>
    const T &MyContainer<T>::DescendingOrder::operator*() const
    {
        if (current_index >= sorted_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return sorted_elements[current_index];
    }

    /**
     * @brief Begin method for the DescendingOrder iterator.
     * Initializes the iterator to the start of the reverse sorted elements.
     * @param None
     * @returns A DescendingOrder iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::DescendingOrder MyContainer<T>::DescendingOrder::begin()
    {
        DescendingOrder iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the DescendingOrder iterator.
     * Initializes the iterator to the end of the reverse sorted elements.
     * @param None
     * @returns A DescendingOrder iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::DescendingOrder MyContainer<T>::DescendingOrder::end()
    {
        DescendingOrder iter = *this;
        iter.current_index = sorted_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create a DescendingOrder iterator for the MyContainer.
     * This method returns an instance of the DescendingOrder iterator initialized with the current container.
     * @param None
     * @returns A DescendingOrder iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::DescendingOrder MyContainer<T>::getDescendingOrder() const
    {
        return DescendingOrder(*this);
    }

    // ** SideCrossOrder Iterator Implementation **

    /**
     * @brief Constructor for the SideCrossOrder iterator.
     * Initializes the iterator with elements arranged in side-cross order (alternating min/max).
     * @param container The MyContainer object to iterate over.
     * @returns SideCrossOrder object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::SideCrossOrder::SideCrossOrder(const MyContainer &container)
        : current_index(0)
    {
        // First, sort all elements
        std::vector<T> temp_sorted = container.elements;
        std::sort(temp_sorted.begin(), temp_sorted.end());

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
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current SideCrossOrder object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::SideCrossOrder &MyContainer<T>::SideCrossOrder::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the SideCrossOrder iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current SideCrossOrder object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::SideCrossOrder MyContainer<T>::SideCrossOrder::operator++(int)
    {
        SideCrossOrder temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the SideCrossOrder iterator.
     * Compares two SideCrossOrder iterators.
     * @param other The other SideCrossOrder iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::SideCrossOrder::operator==(const SideCrossOrder &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the SideCrossOrder iterator.
     * Compares two SideCrossOrder iterators.
     * @param other The other SideCrossOrder iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::SideCrossOrder::operator!=(const SideCrossOrder &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the SideCrossOrder iterator.
     *
     * @param None
     * @returns A reference to the current element in the side-cross order.
     * @throw std::out_of_range if the current index exceeds the size of sorted_elements.
     */
    template <typename T>
    const T &MyContainer<T>::SideCrossOrder::operator*() const
    {
        if (current_index >= sorted_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return sorted_elements[current_index];
    }

    /**
     * @brief Begin method for the SideCrossOrder iterator.
     * Initializes the iterator to the start of the side-cross ordered elements.
     * @param None
     * @returns A SideCrossOrder iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::SideCrossOrder MyContainer<T>::SideCrossOrder::begin()
    {
        SideCrossOrder iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the SideCrossOrder iterator.
     * Initializes the iterator to the end of the side-cross ordered elements.
     * @param None
     * @returns A SideCrossOrder iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::SideCrossOrder MyContainer<T>::SideCrossOrder::end()
    {
        SideCrossOrder iter = *this;
        iter.current_index = sorted_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create a SideCrossOrder iterator for the MyContainer.
     * This method returns an instance of the SideCrossOrder iterator initialized with the current container.
     * @param None
     * @returns A SideCrossOrder iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::SideCrossOrder MyContainer<T>::getSideCrossOrder() const
    {
        return SideCrossOrder(*this);
    }

    // ** ReverseOrder Iterator Implementation **

    /**
     * @brief Constructor for the ReverseOrder iterator.
     * Initializes the iterator with elements in reverse order.
     * @param container The MyContainer object to iterate over.
     * @returns ReverseOrder object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::ReverseOrder::ReverseOrder(const MyContainer &container)
        : current_index(0)
    {
        // Copy elements in reverse order
        reverse_elements.reserve(container.elements.size());
        for (auto it = container.elements.rbegin(); it != container.elements.rend(); ++it)
        {
            reverse_elements.push_back(*it);
        }
    }

    /**
     * @brief Pre-increment operator for the ReverseOrder iterator.
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current ReverseOrder object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::ReverseOrder &MyContainer<T>::ReverseOrder::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the ReverseOrder iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current ReverseOrder object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::ReverseOrder MyContainer<T>::ReverseOrder::operator++(int)
    {
        ReverseOrder temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the ReverseOrder iterator.
     * Compares two ReverseOrder iterators.
     * @param other The other ReverseOrder iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::ReverseOrder::operator==(const ReverseOrder &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the ReverseOrder iterator.
     * Compares two ReverseOrder iterators.
     * @param other The other ReverseOrder iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::ReverseOrder::operator!=(const ReverseOrder &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the ReverseOrder iterator.
     *
     * @param None
     * @returns A reference to the current element in reverse order.
     * @throw std::out_of_range if the current index exceeds the size of reverse_elements.
     */
    template <typename T>
    const T &MyContainer<T>::ReverseOrder::operator*() const
    {
        if (current_index >= reverse_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return reverse_elements[current_index];
    }

    /**
     * @brief Begin method for the ReverseOrder iterator.
     * Initializes the iterator to the start of the reverse ordered elements.
     * @param None
     * @returns A ReverseOrder iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::ReverseOrder MyContainer<T>::ReverseOrder::begin()
    {
        ReverseOrder iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the ReverseOrder iterator.
     * Initializes the iterator to the end of the reverse ordered elements.
     * @param None
     * @returns A ReverseOrder iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::ReverseOrder MyContainer<T>::ReverseOrder::end()
    {
        ReverseOrder iter = *this;
        iter.current_index = reverse_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create a ReverseOrder iterator for the MyContainer.
     * This method returns an instance of the ReverseOrder iterator initialized with the current container.
     * @param None
     * @returns A ReverseOrder iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::ReverseOrder MyContainer<T>::getReverseOrder() const
    {
        return ReverseOrder(*this);
    }

    // ** Order Iterator Implementation **

    /**
     * @brief Constructor for the Order iterator.
     * Initializes the iterator with elements in original insertion order.
     * @param container The MyContainer object to iterate over.
     * @returns Order object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::Order::Order(const MyContainer &container)
        : original_elements(container.elements), current_index(0)
    {
        // Simply copy elements in their original order - no sorting needed
    }

    /**
     * @brief Pre-increment operator for the Order iterator.
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current Order object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::Order &MyContainer<T>::Order::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the Order iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current Order object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::Order MyContainer<T>::Order::operator++(int)
    {
        Order temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the Order iterator.
     * Compares two Order iterators.
     * @param other The other Order iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::Order::operator==(const Order &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the Order iterator.
     * Compares two Order iterators.
     * @param other The other Order iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::Order::operator!=(const Order &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the Order iterator.
     *
     * @param None
     * @returns A reference to the current element in original order.
     * @throw std::out_of_range if the current index exceeds the size of original_elements.
     */
    template <typename T>
    const T &MyContainer<T>::Order::operator*() const
    {
        if (current_index >= original_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return original_elements[current_index];
    }

    /**
     * @brief Begin method for the Order iterator.
     * Initializes the iterator to the start of the original ordered elements.
     * @param None
     * @returns An Order iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::Order MyContainer<T>::Order::begin()
    {
        Order iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the Order iterator.
     * Initializes the iterator to the end of the original ordered elements.
     * @param None
     * @returns An Order iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::Order MyContainer<T>::Order::end()
    {
        Order iter = *this;
        iter.current_index = original_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create an Order iterator for the MyContainer.
     * This method returns an instance of the Order iterator initialized with the current container.
     * @param None
     * @returns An Order iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::Order MyContainer<T>::getOrder() const
    {
        return Order(*this);
    }

    // ** MiddleOutOrder Iterator Implementation **

    /**
     * @brief Constructor for the MiddleOutOrder iterator.
     * Initializes the iterator with elements arranged in middle-out order.
     * Starts from middle, then alternates left-right.
     * 
     * @note if the number of elements is even, it starts from the left middle.
     * 
     * @param container The MyContainer object to iterate over.
     * @returns MiddleOutOrder object.
     * @throw None
     */
    template <typename T>
    MyContainer<T>::MiddleOutOrder::MiddleOutOrder(const MyContainer &container)
        : current_index(0)
    {
        if (container.elements.empty())
        {
            return; // Nothing to arrange
        }

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
     * Moves the iterator to the next element.
     * @param None
     * @returns Reference to the current MiddleOutOrder object.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::MiddleOutOrder &MyContainer<T>::MiddleOutOrder::operator++()
    {
        ++current_index;
        return *this;
    }

    /**
     * @brief Post-increment operator for the MiddleOutOrder iterator.
     * Moves the iterator to the next element and returns the previous state.
     * @param None
     * @returns A copy of the current MiddleOutOrder object before incrementing.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::MiddleOutOrder MyContainer<T>::MiddleOutOrder::operator++(int)
    {
        MiddleOutOrder temp = *this;
        ++current_index;
        return temp;
    }

    /**
     * @brief Equality operator for the MiddleOutOrder iterator.
     * Compares two MiddleOutOrder iterators.
     * @param other The other MiddleOutOrder iterator to compare with.
     * @returns true if the current index is equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::MiddleOutOrder::operator==(const MiddleOutOrder &other) const
    {
        return current_index == other.current_index;
    }

    /**
     * @brief Inequality operator for the MiddleOutOrder iterator.
     * Compares two MiddleOutOrder iterators.
     * @param other The other MiddleOutOrder iterator to compare with.
     * @returns true if the current index is not equal to the other index, false otherwise.
     * @throw None
     */
    template <typename T>
    bool MyContainer<T>::MiddleOutOrder::operator!=(const MiddleOutOrder &other) const
    {
        return !(*this == other); // Use the == operator
    }

    /**
     * @brief Dereference operator for the MiddleOutOrder iterator.
     *
     * @param None
     * @returns A reference to the current element in middle-out order.
     * @throw std::out_of_range if the current index exceeds the size of middle_out_elements.
     */
    template <typename T>
    const T &MyContainer<T>::MiddleOutOrder::operator*() const
    {
        if (current_index >= middle_out_elements.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return middle_out_elements[current_index];
    }

    /**
     * @brief Begin method for the MiddleOutOrder iterator.
     * Initializes the iterator to the start of the middle-out ordered elements.
     * @param None
     * @returns A MiddleOutOrder iterator pointing to the first element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::MiddleOutOrder MyContainer<T>::MiddleOutOrder::begin()
    {
        MiddleOutOrder iter = *this;
        iter.current_index = 0;
        return iter;
    }

    /**
     * @brief End method for the MiddleOutOrder iterator.
     * Initializes the iterator to the end of the middle-out ordered elements.
     * @param None
     * @returns A MiddleOutOrder iterator pointing past the last element.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::MiddleOutOrder MyContainer<T>::MiddleOutOrder::end()
    {
        MiddleOutOrder iter = *this;
        iter.current_index = middle_out_elements.size();
        return iter;
    }

    /**
     * @brief Factory method to create a MiddleOutOrder iterator for the MyContainer.
     * This method returns an instance of the MiddleOutOrder iterator initialized with the current container.
     * @param None
     * @returns A MiddleOutOrder iterator for the current MyContainer.
     * @throw None
     */
    template <typename T>
    typename MyContainer<T>::MiddleOutOrder MyContainer<T>::getMiddleOutOrder() const
    {
        return MiddleOutOrder(*this);
    }

    // Explicit template instantiations for common types
    // This saves compilation time for these types
    template class MyContainer<int>;
    template class MyContainer<double>;
    template class MyContainer<std::string>;
}