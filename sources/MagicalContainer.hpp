#pragma once

/**
 * This file represents a container that specializes with 3 different types of iterators:
 *  1. AscendingIterator - Allowing to travers over the container's data in an ascending order.
 *  2. SideCrossIterator - Allowing to travers over the container's data in a side-cross order.
 *  3. PrimeIterator - Allowing to travers over the container's data in a prime-ary order.
 * The container's mechanism is based on a dynamic array.
 *
 * @author Osama M. Ghaliah
 */

#include <string>

using namespace std;

namespace ariel {
    class MagicalContainer {
    private:
        int *start;
        int capacity;

    public:
        MagicalContainer() : start(nullptr) {

        }

        ~MagicalContainer() {

        }

        void addElement(int element) {

        }

        void removeElement(int element) {

        }

        int& operator [] (int index) {

            return this->capacity;
        }

        int size() const {
            return this->capacity;
        }

        template <typename T> string displayAllElements(T iterator) {

            return "";
        }

        /**
         * This class represents an iterator which travers on our MagicalContainer elements in an ascending order.
         * ASCENDING ==> Means that the iterator traverses starting from the lowest index till the biggest index.
         */
        class AscendingIterator {
        private:
            int *currentIndex;
            MagicalContainer *container;

        public:
            AscendingIterator() {

            }

            AscendingIterator(MagicalContainer container) {

            }

            int& operator * () const {
                return *(this->currentIndex);
            }

            AscendingIterator& operator ++ () {

                return *this;
            }

            AscendingIterator& operator -- () {

                return *this;
            }

            AscendingIterator& operator = (const AscendingIterator ascendingIterator) {

                return *this;
            }

            bool operator == (const AscendingIterator& ascendingIterator) const {

                return false;
            }

            bool operator != (const AscendingIterator& ascendingIterator) const {

                return false;
            }

            bool operator < (const AscendingIterator& rightItr) {

                return false;
            }

            bool operator > (const AscendingIterator& rightItr) {

                return false;
            }

            AscendingIterator begin() {

                return *this;
            }

            AscendingIterator end() {

                return *this;
            }
        };

        /**
         * This class represents an iterator which traverses on our MagicalContainer elements in a side-cross order.
         * SIDE-CROSS ==> Means that the iterator traverses in a "one from the start and one from the end" manner.
         *  E.g, {2, 1, 8, 6, -3, 4} ---> {2, 4, 1, -3, 8, 6}
         *  Why {2, 4, 1, -3, 8, 6} ?
         *  The 2 is the first element from the start.
         *  The 4 is the first element from the end.
         *  The 1 is the second element from the start.
         *  The 8 is the second element from the end.
         *  And so on... this is called a side-cross traversal.
         */
        class SideCrossIterator {
        private:
            int *currentIndex;
            MagicalContainer *container;

        public:
            SideCrossIterator() {

            }

            SideCrossIterator(MagicalContainer container) {

            }

            int& operator * () const {
                return *(this->currentIndex);
            }

            SideCrossIterator& operator ++ () {

                return *this;
            }

            SideCrossIterator& operator -- () {

                return *this;
            }

            SideCrossIterator& operator = (const SideCrossIterator sideCrossIterator) {

                return *this;
            }

            bool operator == (const SideCrossIterator& sideCrossIterator) const {

                return false;
            }

            bool operator != (const SideCrossIterator& sideCrossIterator) const {

                return false;
            }

            bool operator < (const SideCrossIterator& rightItr) {

                return false;
            }

            bool operator > (const SideCrossIterator& rightItr) {

                return false;
            }

            SideCrossIterator begin() {

                return *this;
            }

            SideCrossIterator end() {

                return *this;
            }
        };

        /**
         * This inner class represents an iterator which travers on our MagicalContainer elements in a prime-ary order.
         * PRIME-ARY ==> Means that the iterator traverses ONLY over indexes that are prime numbers. E.g, 2, 3, 5, 7... etc.
         */
        class PrimeIterator {
        private:
            int *currentIndex;
            MagicalContainer *container;

        public:
            PrimeIterator() {

            }

            PrimeIterator(MagicalContainer container) {

            }

            int& operator * () const {
                return *(this->currentIndex);
            }

            PrimeIterator& operator ++ () {

                return *this;
            }

            PrimeIterator& operator -- () {

                return *this;
            }

            PrimeIterator& operator = (const PrimeIterator primeIterator) {

                return *this;
            }

            bool operator == (const PrimeIterator& primeIterator) const {

                return false;
            }

            bool operator != (const PrimeIterator& primeIterator) const {

                return false;
            }

            bool operator < (const PrimeIterator& rightItr) {

                return false;
            }

            bool operator > (const PrimeIterator& rightItr) {

                return false;
            }

            PrimeIterator begin() {

                return *this;
            }

            PrimeIterator end() {

                return *this;
            }
        };
    };
}