// yarinkash1@gmail.com

#include <iostream>
#include "MyContainer.hpp"

int main()
{
    using namespace my_cont_ns;

    std::cout << "=== MyContainer Demo ===" << std::endl;

    // Create a container with default type (int)
    MyContainer<> container;

    std::cout << "1. Initial state:" << std::endl;
    std::cout << "   Size: " << container.size() << std::endl;
    std::cout << "   Is empty: " << (container.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << "\n2. Adding elements: 10, 5, 20, 5, 15" << std::endl;
    container.add(10);
    container.add(5);
    container.add(20);
    container.add(5); // Duplicate
    container.add(15);

    std::cout << "   Size after adding: " << container.size() << std::endl;
    std::cout << "   Container contents: ";
    container.print();

    std::cout << "\n3. Removing element 5 (should remove all occurrences):" << std::endl;
    container.remove(5);
    std::cout << "   Size after removing 5: " << container.size() << std::endl;
    std::cout << "   Container contents: ";
    container.print();

    std::cout << "\n4. With strings:" << std::endl;
    MyContainer<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");

    std::cout << "   String container size: " << stringContainer.size() << std::endl;
    std::cout << "   String container contents: ";
    stringContainer.print();

    // == Iterators ==
    std::cout << "\n5. AscendingOrder iterator:" << std::endl;
    std::cout << "   Original container contents: ";
    container.print();

    // Get ascending order iterator
    auto ascending = container.getAscendingOrder();
    std::cout << "   Ascending order traversal: ";
    for (auto it = ascending.begin(); it != ascending.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // DescendingOrder iterator
    std::cout << "\n6.   DescendingOrder (largest to smallest):" << std::endl;
    auto descending = container.getDescendingOrder();
    std::cout << "   ";
    for (auto it = descending.begin(); it != descending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // SideCrossOrder iterator
    std::cout << "\n7.   SideCrossOrder (alternating min/max):" << std::endl;
    auto sideCross = container.getSideCrossOrder();
    std::cout << "   ";
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ReverseOrder iterator
    std::cout << "\n8.   ReverseOrder (reverse insertion order):" << std::endl;
    auto reverse = container.getReverseOrder();
    std::cout << "   ";
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Order iterator
    std::cout << "\n9.   Order (original insertion order):" << std::endl;
    auto order = container.getOrder();
    std::cout << "   ";
    for (auto it = order.begin(); it != order.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // MiddleOutOrder iterator

    std::cout << "\n10.   MiddleOutOrder (middle, then alternating left-right):" << std::endl;
        std::cout << "Order of elemets added: 10 ,20 ,15" << std::endl;
    auto middleOut = container.getMiddleOutOrder();
    std::cout << "   ";
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // == Error Handling ==
    std::cout << "\n11. Testing error handling:" << std::endl;
    std::cout << "   Attempting to remove an element that doesn't exist (555):" << std::endl;
    try
    {
        container.remove(555); // Element that doesn't exist
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "   Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Demo Complete ===" << std::endl;
    return 0;
}