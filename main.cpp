// yarinkash1@gmail.com

#include <iostream>
#include "MyContainer.hpp"

int main()
{
    using namespace my_cont_ns;

    std::cout << "=== MyContainer Demo ===" << std::endl;

    // ========================================
    // SECTION 1: Basic Container Operations
    // ========================================
    std::cout << "\n========== BASIC OPERATIONS ==========" << std::endl;
    
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

    // ========================================
    // SECTION 2: Template Flexibility Tests
    // ========================================
    std::cout << "\n\n========== TEMPLATE FLEXIBILITY ==========" << std::endl;

    std::cout << "\n4. Testing with strings:" << std::endl;
    MyContainer<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("C++");

    std::cout << "   String container size: " << stringContainer.size() << std::endl;
    std::cout << "   String container contents: ";
    stringContainer.print();

    std::cout << "\n5. Testing with characters:" << std::endl;
    MyContainer<char> charContainer;
    charContainer.add('Z');
    charContainer.add('A');
    charContainer.add('M');
    charContainer.add('B');
    charContainer.add('Y');

    std::cout << "   Char container size: " << charContainer.size() << std::endl;
    std::cout << "   Char container contents: ";
    charContainer.print();

    // ========================================
    // SECTION 3: Stream Output Operator
    // ========================================
    std::cout << "\n\n========== STREAM OUTPUT OPERATOR ==========" << std::endl;

    std::cout << "\n6. Testing operator<< for streaming:" << std::endl;
    std::cout << "   Int container:    " << container << std::endl;
    std::cout << "   String container: " << stringContainer << std::endl;
    std::cout << "   Char container:   " << charContainer << std::endl;

    // ========================================
    // SECTION 4: Iterator Demonstrations
    // ========================================
    std::cout << "\n\n========== ITERATOR TYPES ==========" << std::endl;
    
    std::cout << "\n7. Current container state:" << std::endl;
    std::cout << "   Elements: [10, 20, 15] (after removing 5s)" << std::endl;
    std::cout << "   Container contents: ";
    container.print();

    // AscendingOrder iterator
    std::cout << "\n8. AscendingOrder (smallest to largest):" << std::endl;
    auto ascending = container.getAscendingOrder();
    std::cout << "   ";
    for (auto it = ascending.begin(); it != ascending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // DescendingOrder iterator
    std::cout << "\n9. DescendingOrder (largest to smallest):" << std::endl;
    auto descending = container.getDescendingOrder();
    std::cout << "   ";
    for (auto it = descending.begin(); it != descending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // SideCrossOrder iterator
    std::cout << "\n10. SideCrossOrder (alternating min/max):" << std::endl;
    auto sideCross = container.getSideCrossOrder();
    std::cout << "   ";
    for (auto it = sideCross.begin(); it != sideCross.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ReverseOrder iterator
    std::cout << "\n11. ReverseOrder (reverse insertion order):" << std::endl;
    auto reverse = container.getReverseOrder();
    std::cout << "   ";
    for (auto it = reverse.begin(); it != reverse.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Order iterator
    std::cout << "\n12. Order (original insertion order):" << std::endl;
    auto order = container.getOrder();
    std::cout << "   ";
    for (auto it = order.begin(); it != order.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // MiddleOutOrder iterator
    std::cout << "\n13. MiddleOutOrder (middle, then alternating left-right):" << std::endl;
    std::cout << "    Current elements: [10, 20, 15]" << std::endl;
    auto middleOut = container.getMiddleOutOrder();
    std::cout << "   ";
    for (auto it = middleOut.begin(); it != middleOut.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ========================================
    // SECTION 5: Character Iterator Examples  
    // ========================================
    std::cout << "\n\n========== CHAR ITERATOR EXAMPLES ==========" << std::endl;

    std::cout << "\n14. Character container iterator examples:" << std::endl;
    std::cout << "    Original chars: [Z, A, M, B, Y]" << std::endl;

    std::cout << "\n    Char AscendingOrder:  ";
    auto charAscending = charContainer.getAscendingOrder();
    for (auto it = charAscending.begin(); it != charAscending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "    Char DescendingOrder: ";
    auto charDescending = charContainer.getDescendingOrder();
    for (auto it = charDescending.begin(); it != charDescending.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "    Char SideCrossOrder:  ";
    auto charSideCross = charContainer.getSideCrossOrder();
    for (auto it = charSideCross.begin(); it != charSideCross.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ========================================
    // SECTION 6: Error Handling
    // ========================================
    std::cout << "\n\n========== ERROR HANDLING ==========" << std::endl;

    std::cout << "\n15. Testing error handling:" << std::endl;
    
    std::cout << "    Attempting to remove non-existent int (555):" << std::endl;
    try {
        container.remove(555);
    }
    catch (const std::invalid_argument &e) {
        std::cout << "    Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n    Attempting to remove non-existent char ('X'):" << std::endl;
    try {
        charContainer.remove('X');
    }
    catch (const std::invalid_argument &e) {
        std::cout << "    Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Demo Complete ===" << std::endl;

    return 0;
}