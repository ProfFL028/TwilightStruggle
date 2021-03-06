
#ifndef ALGORITHM_VECTOR_H
#define ALGORITHM_VECTOR_H

#include <iostream>
#include <stdexcept>

namespace ds {
    template<typename T>
    class VectorNode {
    public:
        VectorNode() {
            this->next = nullptr;
        }
        explicit VectorNode(const T &t, VectorNode *node = nullptr) {
            this->element = t;
            this->next = node;
        }

    public:
        T element;
        VectorNode *next;
    };

    template<typename T>
    class Vector {
    public:
        VectorNode<T> *head;
        VectorNode<T> *tail; // keep track of last element.
        int length{};
    public:
        Vector() : head(nullptr), tail(nullptr), length(0) {};
        // notice we need to rewrite `=` function together when we rewrite copy constructor.
        Vector(const Vector& vec) {
            this->copyData(vec);
        };
        /**
         * Delete all VectorNode pointers.
         */
        virtual ~Vector() {
            clear();
        };

        /**
         * clear all elements.
         */
        void clear() {
            VectorNode<T> *cur = head;
            while (cur != nullptr) {
                head = head->next;
                delete cur;
                cur = head;
            }
            this->length = 0;
        }

    public:
        inline bool isEmpty() const {
            return this->length <= 0;
        };

        /**
         * Get first element.
         * @return
         */
        T top() const {
            if (this->length <= 0) {
                throw std::runtime_error("vector is empty");
            }
            return head->element;
        };

        /**
         * Get and remove last element.
         * @return
         */
        T pop() {
            if (this->length <= 0) {
                throw std::runtime_error("vector is empty");
            }
            VectorNode<T> *cur = head;
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
        void insert(const T &t) {
            auto *newNode = new VectorNode<T>(t);
            if (this->isEmpty()) {
                this->head = newNode;
                this->tail = newNode;
            } else {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->length++;
        };

        /**
         * Deep copy another vector to it.
         * @param vec
         */
        void append(const Vector<T>& vec) {
            auto cur = vec.head;
            while (cur != nullptr) {
                this->insert(cur->element);
                cur = cur->next;
            }
        }

        void reserve() {
            // TODO: implement this.
        };

        friend std::ostream &operator<<(std::ostream &out, Vector &vector) {
            VectorNode<T> *cur = vector.head;
            out << "[";
            while (cur != nullptr) {
                out << cur->element << ", ";
                cur = cur->next;
            }
            // remove last `, `.
            out << "\b\b]";
            return out;
        }

        // for we've rewritten copy function.
        Vector &operator=(const Vector& other) {
            this->clear();
            this->copyData(other);
            return *this;
        }

    private:
        // helper functions:
        void copyData(const Vector& other) {
            VectorNode<T> *cur = other.head;
            while (cur != nullptr) {
                this->insert(cur->element);
                cur = cur->next;
            }
        }
    };

}

#endif //ALGORITHM_VECTOR_H
