#pragma once

namespace STL
{
template <typename T, uint32_t N>
class Stack
{
public:
    Stack()
    {
        write_pos = 0;
        count = 0;
    }

    void push(const T &push_data)
    {
        if (count == N)
            return;
        data[write_pos] = push_data;
        ++write_pos;
        ++count;
    }

    T top(void)
    {
        return data[write_pos - 1];
    }

    void pop(void)
    {
        if (count == 0)
            return;
        --write_pos;
        --count;
    }

    uint32_t size(void)
    {
        return count;
    }

    bool empty(void)
    {
        return !count;
    }

private:
    T data[N];
    uint32_t write_pos, count;
};
/* 一周した場合は何もしない */
template <typename T, uint32_t N>
class Queue
{
public:
    Queue()
    {
        write_pos = 0;
        read_pos = 0;
        count = 0;
    }

    void push(const T &push_data)
    {
        if (count == N)
            return;
        data[write_pos] = push_data;
        ++write_pos;
        ++count;
        if (write_pos == N)
            write_pos = 0;
    }

    void pop(void)
    {
        if (count == 0)
            return;
        ++read_pos;
        --count;
        if (read_pos == N)
            read_pos = 0;
    }

    T front(void) const
    {
        return data[read_pos];
    }

    uint32_t size(void) const
    {
        return count;
    }

    bool empty(void) const
    {
        return !count;
    }

private:
    T data[N];
    uint32_t write_pos, read_pos, count;
};

/* 一周した場合は値を上書き */
template <typename T, uint32_t N>
class RingBuffer
{
public:
    RingBuffer()
    {
        write_pos = 0;
        read_pos = 0;
        count = 0;
    }

    void push(T push_data)
    {
        data[write_pos] = push_data;
        ++write_pos;
        ++count;
        if (write_pos == N)
            write_pos = 0;
    }

    void pop(void)
    {
        if (count == 0)
            return;
        ++read_pos;
        --count;
        if (read_pos == N)
            read_pos = 0;
    }

    T front(void) const
    {
        return data[read_pos];
    }

    uint32_t size(void) const
    {
        return count;
    }

    bool empty(void) const
    {
        return !count;
    }

private:
    T data[N];
    uint32_t write_pos, read_pos, count;
};
} // namespace STL