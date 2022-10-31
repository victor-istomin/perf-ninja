#include "solution.hpp"
#include <array>
#include <algorithm>
#include <iostream>

unsigned getSumOfDigits(unsigned n) {
  unsigned sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

// Task: lookup all the values from l2 in l1.
// For every found value, find the sum of its digits.
// Return the sum of all digits in every found number.
// Both lists have no duplicates and elements placed in *random* order.
// Do NOT sort any of the lists. Do NOT store elements in a hash_map/sets.

// Hint: Traversing a linked list is a long data dependency chain:
//       to get the node N+1 you need to retrieve the node N first.
//       Think how you can execute multiple dependency chains in parallel.
template <typename ValueType, size_t MaxSize>
class Bucket
{
public:

  using Buffer   = std::array<ValueType, MaxSize>;
  using iterator = typename Buffer::iterator;

private:

  Buffer   m_buffer;
  iterator m_tail;

public:

  Bucket()  { m_tail = m_buffer.begin(); }

  void push(ValueType v) 
  {
    *m_tail = v;
    ++m_tail;
  }

  void erase(iterator where)
  {
    auto next = std::next(where);
    std::copy(next, m_tail, where);
    //--m_tail;
    //*where = *m_tail;       // swap deleted element with last one

  }

  iterator find(ValueType v) 
  { 
      auto itFound = std::lower_bound(m_buffer.begin(), m_tail, v);
      return *itFound == v ? itFound : m_tail; 
  }

  iterator begin() const     { return m_buffer.begin(); }
  iterator begin()           { return m_buffer.begin(); }
  iterator end() const       { return m_tail; }
  iterator end()             { return m_tail; }

  bool isEmpty() const { return m_tail == m_buffer.begin(); }
  bool isFull() const  { return m_tail == m_buffer.end(); }
};


unsigned solution(List *l1, List *l2) {
  unsigned retVal = 0;

  constexpr size_t BucketSize = 8 * 1024;

  List *head2 = l2;

  // O(N^2) algorithm:
  while (l1) 
  {
    Bucket<unsigned, BucketSize> bucket;
    while (!bucket.isFull() && l1)
    {
      bucket.push(l1->value);
      l1 = l1->next;
    }

    std::sort(bucket.begin(), bucket.end());

    l2 = head2;
    while (l2) 
    {
      unsigned v = l2->value;
      auto itFound = bucket.find(v);
      if (itFound != bucket.end())
      {
        retVal += getSumOfDigits(v);
        bucket.erase(itFound);
        //std::sort(bucket.begin(), bucket.end());

        if (bucket.isEmpty())
          break;
      }

      l2 = l2->next;
    }
  }

  return retVal;
}
