//
// Created by Carson on 2026/1/14.
//

#include "test.h"
#include <iostream>
#include <vector>
using namespace std;

class MinStack {

    stack<int> m_stack;
public:
    MinStack() {

    }

    void push(int val) {
        stack<int> tmp_stack;
        while (m_stack.top() < val) {
            tmp_stack.push(m_stack.top());
            m_stack.pop();
        }
        m_stack.push(val);
        while (!tmp_stack.empty()) {
            m_stack.push(tmp_stack.top());
            tmp_stack.pop();
        }
    }

    void pop() {
        m_stack.pop();
    }

    int top() {
        return m_stack.top();
    }

    int getMin() {
        return m_stack.top();
    }
};

int main () {

}
