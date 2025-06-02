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
    // **AscendingOrder Iterator Class Implementation**

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

    // Explicit template instantiations for common types
    // This saves compilation time for these types
    template class MyContainer<int>;
    template class MyContainer<double>;
    template class MyContainer<std::string>;
}