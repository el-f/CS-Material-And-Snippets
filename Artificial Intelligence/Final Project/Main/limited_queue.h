#pragma once

#include <vector>

// A queue that has a max size and will remove the oldest element if the queue is full
template<class T>
class limited_queue {
private:
    int max_size;
    std::vector<T> q;

public:

    limited_queue() : max_size(0) {}

    explicit limited_queue(int max_size) : max_size(max_size) {}

    void push(T t) {
        if (q.size() == max_size) {
            q.erase(q.begin());
        }
        q.push_back(t);
    }

    T pop() {
        T t = q.front();
        q.erase(q.begin());
        return t;
    }

    T top() {
        return q.front();
    }

    bool is_empty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }

    void clear() {
        q.clear();
    }

    bool contains(T t) {
        for (T &i: q)
            if (i == t)
                return true;
        return false;
    }
};
