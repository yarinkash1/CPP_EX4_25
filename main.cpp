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

    std::cout << "\n4. Testing with strings:" << std::endl;
    MyContainer<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");

    std::cout << "   String container size: " << stringContainer.size() << std::endl;
    std::cout << "   String container contents: ";
    stringContainer.print();

        std::cout << "\n5. Testing AscendingOrder iterator:" << std::endl;
    std::cout << "   Original container contents: ";
    container.print();

    // Get ascending order iterator
    auto ascending = container.getAscendingOrder();
    std::cout << "   Ascending order traversal: ";
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

        // Test with a new container with more elements
    std::cout << "\n   Testing with more elements:" << std::endl;
    MyContainer<int> testContainer;
    testContainer.add(50);
    testContainer.add(25);
    testContainer.add(75);
    testContainer.add(10);
    testContainer.add(90);
    testContainer.add(25); // Duplicate

    std::cout << "   Original order: ";
    testContainer.print();

    auto testAscending = testContainer.getAscendingOrder();
    std::cout << "   Ascending order: ";
    for (auto it = testAscending.begin(); it != testAscending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "\n6. Testing error handling:" << std::endl;
    try
    {
        container.remove(123456789); // Element that doesn't exist
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "   Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Demo Complete ===" << std::endl;
    return 0;
}