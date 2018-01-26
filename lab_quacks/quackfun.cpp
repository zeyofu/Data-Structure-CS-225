/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s) {
  stack<T> temp;
  T summ = T();
  if (!s.empty()) {
    T first = s.top();
    temp.push(first);
    s.pop();
    summ = sum(s) + T(first);
  }
  while (!temp.empty()) {
    s.push(temp.top());
    temp.pop();
  }
    // Your code here
    return summ;
  //return T(summ); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    int count = 0;
    while (!q.empty()) {
      count += 1;
      if (count % 2 == 0) {
        for (int j = 0; j < count; j++) {
          if (q.empty()) break;
          s.push(q.front());
          q.pop();
        }
        while (!s.empty()) {
          q2.push(s.top());
          s.pop();
        }
      } else if (count % 2 == 1){
        for (int i = 0; i < count; i++) {
          if (q.empty()) break;
          q2.push(q.front());
          q.pop();
        }
      }
    }
    while(!q2.empty()) {
      q.push(q2.front());
      q2.pop();
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    if (s.empty()) return true;   //If stack and queue are empty, then by default return true

    bool retval = true;   //local boolean in each recursion

    T temp1 = s.top();    //temp1: top of stack
    s.pop();   //take the first off stack

    //goes over stack, in each recursive case, creats stack values for that current element
    //and goes to the next recursive case until s is empty. So in total there are n variables on stack
    retval = verifySame(s,q);

    //Only executes when last element in s is removed and copied on stack memory
    //The last element is pushed back to s, and after that each saved variable on stack
    // memory goes back to s.
    s.push(temp1);

    //Determines in each recursive case. if both previous retval is true, and the
    //current two elements in s and q are equal, then current retval is true.
    retval = retval && (s.top() == q.front());

    //Pushes the current top in q to the back. So as to reach every element to q.
    q.push(q.front());

    // Since the first element has already been stored in the end of q, delete
    // the first so as we can reach the next element in next round.
    q.pop();
    
    return retval;
  }
}
