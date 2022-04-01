
#ifndef ALGORITHM_VECTOR_H
#define ALGORITHM_VECTOR_H

#include <iostream>
#include <stdexcept>

namespace ds {
    template<typename T>
    class Vector {
    private:
        class VectorNode {
        public:
            explicit VectorNode(const T &t, VectorNode *node = nullptr) {
                this->element = t;
                this->next = node;
            }

        private:
            T element;
            VectorNode *next;

            friend class Vector<T>;
        };

    public:
        VectorNode *head;
        VectorNode *tail; // keep track of last element.
        int length;
    public:
        Vector() : head(nullptr), tail(nullptr), length(0) {};

        /**
         * Delete all VectorNode pointers.
         */
        virtual ~Vector() {
            VectorNode *cur = head;
            while (cur != nullptr) {
                head = head->next;
                delete cur;
                cur = head;
            }
        };

    public:
        inline bool isEmpty() const {
            return this->length <= 0;
        };

        T top() const {
            if (this->length <= 0) {
                throw std::runtime_error("vector is empty");
            }
            return head->element;
        };

        T peek() {
            if (this->length <= 0) {
                throw std::runtime_error("vector is empty");
            }
            VectorNode *cur = head;
            head = head->next;
            T result = cur->element;
            delete cur;
            return result;
        };

        /**
         * Add a new element to Vector.
         * Set tail to the new element. Set head to the new element if it is the first element.
         * @param t
         */
        void add(const T &t) {
            auto *newNode = new VectorNode(t);
            if (this->isEmpty()) {
                this->head = newNode;
                this->tail = newNode;
            } else {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->length++;
        };

        void reserve() {
            // TODO: implement this.
        };

        friend std::ostream &operator<<(std::ostream &out, Vector &vector) {
            VectorNode *cur = vector.head;
            out << "[";
            while (cur != nullptr) {
                out << cur->element << ", ";
                cur = cur->next;
            }
            out << "\b\b]" << std::endl;
            return out;
        }
    };

}

#endif //ALGORITHM_VECTOR_H
