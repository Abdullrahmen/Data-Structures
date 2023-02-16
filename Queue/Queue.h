/*
Fixed size queue using circular array trick.
*/

#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#include <memory>
using uint = unsigned long;

/// @brief Fixed size queue
/// @tparam T
template <typename T>
class Queue
{
private:
    /// @brief Queue data(values) 
    ///unique_ptr to an array of unique_ptrs -not a direct array- to allow late specify size(after declaration)
    std::unique_ptr<std::unique_ptr<T>[]> _values;

    /// @brief Maximum size (_values array size)
    uint _maximum_size;

    /// @brief Actual size (number of elements added)
    uint _actual_size;

    /// @brief index of the head
    uint _head;

    /// @brief index of the tail
    uint _tail;

    /// @brief circular trick : eg. when idx == maximum_size and step == 1 then next_idx = 0
    /// @param idx
    /// @param step
    /// @return idx + step with circular array
    uint get_next_idx(const uint& idx, const uint& step = 1) const
    { return (idx + step) % _maximum_size; }

public:
    /// @brief Empty constructor
    Queue(uint maximum_size = 0);

    /// @brief Copy constructor
    Queue(const Queue &queue);

    /// @brief Move constructor
    Queue(Queue &&queue);

    /// @brief Late set maximum size after declaration - must be > 0
    /// @param maximum_size Queue size
    /// @note if called with already specified size -> will throw
    void set_maximum_size(const uint &maximum_size);

    /// @todo
    //void reset_maximum_size();

    /// @brief Add element to the end of the queue
    /// @param value The element
    /// @note O(1)
    void enqueue(const T &value);
    void enqueue(T &&value);

    bool is_empty() const { return _actual_size == 0; }
    bool is_full() const { return _actual_size == _maximum_size; }

    /// @brief return first element in the queue and pop it 
    /// @return A unique pointer to the first element in the queue
    /// @note O(1)
    [[nodiscard]] std::unique_ptr<T> dequeue();

    void debug_print();

    //~Queue();
};

#include "Queue.tpp"
#endif // QUEUE_H_
