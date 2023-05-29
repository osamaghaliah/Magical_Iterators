#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <limits>
#include <sstream>

using namespace ariel;

auto maximalInteger = numeric_limits <int> :: max();
auto minimalInteger = numeric_limits <int> :: min();

TEST_CASE("Containers Initialization & Functionality Correctness") {
    MagicalContainer magicalContainer;
    CHECK((magicalContainer.size() == 0));

    // Attempting to add overflown integers.
    CHECK_THROWS_AS(magicalContainer.addElement(maximalInteger + 1), overflow_error);
    CHECK_THROWS_AS(magicalContainer.addElement(minimalInteger - 1), overflow_error);
    // Attempting to add legal integers.
    CHECK_NOTHROW(magicalContainer.addElement(6));
    CHECK_NOTHROW(magicalContainer.addElement(4));
    CHECK_NOTHROW(magicalContainer.addElement(2));

    // 3 above integers must be contained inside the container now.
    CHECK((magicalContainer.size() == 3));

    // Attempting to retrieve/remove the integers.
    CHECK((magicalContainer[0] == 6));
    CHECK((magicalContainer[1] == 4));
    CHECK((magicalContainer[2] == 2));
    CHECK_THROWS_AS(magicalContainer[3], runtime_error);
    CHECK_NOTHROW(magicalContainer[1]);
    CHECK_THROWS_AS(magicalContainer.removeElement(7), invalid_argument);
    CHECK_NOTHROW(magicalContainer.removeElement(4));
    CHECK((magicalContainer.size() == 2));
    CHECK((magicalContainer[0] == 6));
    CHECK((magicalContainer[1] == 2));

    // Attempting to empty the container and making sure that it is actually empty.
    CHECK_NOTHROW(magicalContainer.removeElement(2));
    CHECK_NOTHROW(magicalContainer.removeElement(6));
    CHECK((magicalContainer.size() == 0));
    CHECK_THROWS_AS(magicalContainer[0], runtime_error);
}

TEST_CASE("AscendingIterator Traversal & Operators Correctness") {
    MagicalContainer magicalContainer;

    // Assigning the magicalContainer to hold the values --> {100, 99, 98, ... , 3, 2, 1}
    for (int i = 100; i >= 1; --i) {
        CHECK_NOTHROW(magicalContainer.addElement(i));
    }

    MagicalContainer::AscendingIterator ascendingIterator(magicalContainer);

    /*
     * Making sure that the ascendingIterator is now holding the magicalContainer's values in ascending order.
     * Although the values are in descending order, the iterator behaves in ascending order on the indexes and values.
     * Iterator's operators that are going to play a role in the following loop are: * , ++ , != , ==
     * Iterator's functions that are going to play a role in the following loop are: begin() , end()
     * Each operator/function must work according to the MagicalContainer::AscendingIterator manner.
     */
    SUBCASE("6 In 1: * , ++ , != , == , begin() , end() Correctness") {
        int index = 99;
        for (auto itr = ascendingIterator.begin(); itr != ascendingIterator.end(); ++itr) {
            CHECK((*itr == magicalContainer[index]));
            index--;
        }
    }

    // Operators < , > correctness.
    SUBCASE("2 In 1: < , > Correctness") {
        for (auto itr = ascendingIterator.begin(); itr != (--ascendingIterator.end()); ++itr) {
            auto temp = itr;
            ++temp;
            CHECK_FALSE((temp < itr));
            CHECK((temp > itr));
        }
    }

    // MagicalContainer::AscendingIterator traversal correctness.
    SUBCASE("Ascending Traversal Values Validation") {
        string traversal;
        for (auto itr = ascendingIterator.begin(); itr != ascendingIterator.end(); ++itr) {
            traversal += (to_string(*itr) + ' ');
        }
        // Must be --> 1 2 3 . . . 98 99 100
        CHECK((traversal == magicalContainer.displayAllElements(ascendingIterator)));
    }

    SUBCASE("Does The AscendingIterator Track The Container's Changes ?") {
        // Removing 99 98 ... 6 5 4
        for (int i = magicalContainer.size() - 1; i >= 4; --i) {
            magicalContainer.removeElement(i);
        }

        auto itr = ascendingIterator.begin();
        CHECK((*itr == 1));
        ++itr;
        CHECK((*itr == 2));
        ++itr;
        CHECK((*itr == 3));
        ++itr;
        CHECK((*itr == 100));
        CHECK((magicalContainer.displayAllElements(ascendingIterator) == "1 2 3 100 "));
    }
}

TEST_CASE("SideCrossIterator Traversal & Operators Correctness") {
    // -1 3 -5 7
    MagicalContainer magicalContainer;
    magicalContainer.addElement(-1);
    magicalContainer.addElement(3);
    magicalContainer.addElement(-5);
    magicalContainer.addElement(7);

    MagicalContainer::SideCrossIterator sideCrossIterator(magicalContainer);

    /*
     * Making sure that the sideCrossIterator is now holding the magicalContainer's values in side-cross order.
     * Iterator's operators that are going to play a role in the following loop are: * , ++ , != , ==
     * Iterator's functions that are going to play a role in the following loop are: begin() , end()
     * Each operator/function must work according to the MagicalContainer::SideCrossIterator manner.
     */
    SUBCASE("6 In 1: * , ++ , != , == , begin() , end() Correctness") {
        string traversal;
        for (auto itr = sideCrossIterator.begin(); itr != sideCrossIterator.end(); ++itr) {
            traversal += (to_string(*itr) + ' ');
        }
        // Must be --> -1 7 3 -5
        CHECK((magicalContainer.displayAllElements(sideCrossIterator) == "-1 7 3 -5 "));
        CHECK((traversal == magicalContainer.displayAllElements(sideCrossIterator)));
    }

    SUBCASE("2 In 1: < , > Correctness") {
        auto itr = sideCrossIterator.begin();
        auto temp = itr;
        ++temp;
        CHECK((temp > itr));
        CHECK((*temp == 7));
        CHECK_FALSE((temp < itr));
        CHECK((*itr == -1));
    }

    SUBCASE("Does The SideCrossIterator Track The Container's Changes ?") {
        CHECK_NOTHROW(magicalContainer.removeElement(3)); // magicalContainer is now -1 -5 7

        // The sideCrossIterator must be holding the elements in the following order: -1 7 -5
        auto itr = sideCrossIterator.begin();
        // Manual confirmation.
        CHECK((*itr == -1));
        ++itr;
        CHECK((*itr == 7));
        ++itr;
        CHECK((*itr == -5));
    }
}

TEST_CASE("PrimeIterator Traversal & Operators Correctness") {
    MagicalContainer magicalContainer;

    // Assigning the magicalContainer to hold the values --> {1, ... , 10, 11, 12}
    for (int i = 1; i <= 12; ++i) {
        CHECK_NOTHROW(magicalContainer.addElement(i));
    }

    MagicalContainer::PrimeIterator primeIterator(magicalContainer);

    /*
     * Making sure that the MagicalContainer::PrimeIterator is now holding the magicalContainer's values in prime-ary order.
     * Iterator's operators that are going to play a role in the following loop are: * , ++ , != , ==
     * Iterator's functions that are going to play a role in the following loop are: begin() , end()
     * Each operator/function must work according to the MagicalContainer::PrimeIterator manner.
     */
    SUBCASE("6 In 1: * , ++ , != , == , begin() , end() Correctness") {
        string traversal;
        for (auto itr = primeIterator.begin(); itr != primeIterator.end(); ++itr) {
            traversal += (to_string(*itr) + ' ');
        }
        // Must be --> 2 3 5 7 11
        CHECK((magicalContainer.displayAllElements(primeIterator) == "2 3 5 7 11 "));
        CHECK((traversal == magicalContainer.displayAllElements(primeIterator)));
    }

    SUBCASE("2 In 1: < , > Correctness") {
        for (auto itr = primeIterator.begin(); itr != (--primeIterator.end()) ; ++itr) {
            auto temp = itr;
            ++temp;
            CHECK((temp > itr));
            CHECK_FALSE((temp < itr));
        }
    }

    SUBCASE("Does The PrimeIterator Track The Container's Changes ?") {
        // Removing two prime numbers from the container.
        CHECK_NOTHROW(magicalContainer.removeElement(3));
        CHECK_NOTHROW(magicalContainer.removeElement(7));
        // The primeIterator must be holding the container's elements as follows: 2 5 11
        auto itr = primeIterator.begin();
        // Manual confirmation.
        CHECK((*itr == 2));
        ++itr;
        CHECK((*itr == 5));
        ++itr;
        CHECK((*itr == 11));

        // Adding a non-prime number to the container.
        CHECK_NOTHROW(magicalContainer.addElement(98));
        // Manual confirmation - the primeIterator should still hold: 2 5 11
        auto itr1 = primeIterator.begin();
        CHECK((*itr1 == 2));
        ++itr1;
        CHECK((*itr1 == 5));
        ++itr1;
        CHECK((*itr1 == 11));
    }
}

TEST_CASE("Multiple Different Iterators Tracking The Same MagicalContainer Changes") {
    MagicalContainer container;
    container.addElement(-999);
    container.addElement(-4);
    container.addElement(-2);
    container.addElement(0);
    container.addElement(3);
    container.addElement(5);
    container.addElement(999);

    MagicalContainer::AscendingIterator ascendingIterator(container);
    CHECK((container.displayAllElements(ascendingIterator) == "-999 -4 -2 0 3 5 999 "));

    MagicalContainer::SideCrossIterator sideCrossIterator(container);
    CHECK((container.displayAllElements(sideCrossIterator) == "-999 999 -4 5 -2 3 0 "));

    MagicalContainer::PrimeIterator primeIterator(container);
    CHECK((container.displayAllElements(primeIterator) == "5 3 "));
}