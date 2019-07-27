// HEAP.H

// Heap template class
// Author: Q. Prior

#ifndef _HEAP_H_
#define _HEAP_H_

enum STATUS
{
	OK = 100,
	FAILED = 200
};

template <class SOMETYPE>
class HEAP {

  private:

    int size;       // Maximum size
    int nNodes;     // Current number of nodes
    SOMETYPE *buf;  // Pointer to the heap array

  public:

    HEAP (int a_size);
    ~HEAP();
	HEAP(const HEAP& h);
	HEAP& operator = (const HEAP& h);
	SOMETYPE Peek();
    bool IsEmpty() {return (nNodes == 0);}
    bool IsFull() {return (nNodes == size);}
    STATUS Insert(SOMETYPE x);
    STATUS Remove(const SOMETYPE &x);
};

//****************************************************************

template <class SOMETYPE>
HEAP<SOMETYPE>::HEAP(const HEAP& h)
{
	int a_size = h.size;
    nNodes = 0;
    buf = new SOMETYPE[a_size+1]; // +1 because buf[0] is not used
    if (buf) size = a_size;
    else size = 0;

	int i;
	for(i = 0; i < size; i++) {
		buf[i] = h.buf[i];
	}
}

template <class SOMETYPE>
HEAP<SOMETYPE>& HEAP<SOMETYPE>::operator = (const HEAP& h)
{
	delete [] buf;
	int a_size = h.size;
    nNodes = 0;
    buf = new SOMETYPE[a_size+1]; // +1 because buf[0] is not used
    if (buf) size = a_size;
    else size = 0;

	int i;
	for(i = 0; i < size; i++) {
		buf[i] = h.buf[i];
	}

	return *this;
}
template <class SOMETYPE>
HEAP<SOMETYPE>::HEAP(int a_size)

// Constructor: builds a heap of size "a_size".

{
    nNodes = 0;
    buf = new SOMETYPE[a_size+1]; // +1 because buf[0] is not used
    if (buf) size = a_size;
    else size = 0;
}

//****************************************************************

template <class SOMETYPE>
HEAP<SOMETYPE>::~HEAP()

// Destructor.

{
    delete [] buf;
}

//****************************************************************
template <class SOMETYPE>
SOMETYPE HEAP<SOMETYPE>::Peek()
{
	return buf[1];
}


template <class SOMETYPE>
STATUS HEAP<SOMETYPE>::Insert(SOMETYPE x)

// Inserts x into the heap.
// Returns OK if successful, FAILED if the heap is full.

{
    if (IsFull()) return FAILED;

    nNodes++;  // The last node of the heap is now vacant.

    // Starting from the (vacant) last node, go from node i to
    //   its parent iParent and, as long as the parent is
    //   smaller than x, move the parent down:

    int i = nNodes;
    int iParent;
    while (i > 1) {
        iParent = i/2;
        if (x <= buf[iParent]) break;
        buf[i] = buf[iParent];         // Move the parent down;
        i = iParent;                   // buf[i] is now vacant.
    }

    // Insert x into the created vacancy:
    buf[i] = x;

    return OK;
}

//****************************************************************

template <class SOMETYPE>
STATUS HEAP<SOMETYPE>::Remove(const SOMETYPE &xx)

// Removes the largest element (from the root of the heap).
// Returns OK if successful, FAILED if the heap is empty.

{ 
    if (IsEmpty()) return FAILED;

    // Retrieve the top element:

    SOMETYPE x = buf[1];             

    // Starting from the vacant root, go from node iParent to its
    //   larger child i and, as long as that child
    //   is greater than the last element of the heap,
    //   move that child up:

    int iParent = 1;       // root
    int i = 2;             // its left child
    while (i <= nNodes) {
        // Set i to the right child, i+1, if it
        //   exists and is larger:
        if (i < nNodes && buf[i] < buf[i+1]) i++;

        // Compare with the last node:
        if (buf[i] <= buf[nNodes]) break;

        buf[iParent] = buf[i];   // Move the child up; 
        iParent = i;             // buf[iParent] is now vacant.
        i *= 2;                  // i is set to its left child
    }

    // Move the last element into the created vacancy:
    if (nNodes > 1) buf[iParent] = buf[nNodes];
    nNodes--;
 
    return OK;
}

#endif // _HEAP_H_

