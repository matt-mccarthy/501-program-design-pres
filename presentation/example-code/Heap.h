#ifndef HEAP_H
#define HEAP_H

#include "./src/Comparators.cpp"
#include "./exceptions/OutOfBounds.h"

namespace DSLib
{

template
<
    typename T,
    bool (*Comparator)(T, T)
>
/// Sorts an array with heap sort.
/// \param T The type to sort.
/// \param Comparator A comparator function.
/// \param in The array to sort; this array is modified.
/// \param aSize The size of the array.
/// \return The sorted input array.
T* heap_sort(T* in, int aSize);
/// Sorts a vector with heap sort.
/// \param T The type to sort.
/// \param Comparator A comparator function.
/// \param in The vector to sort; this vector is modified.
/// \return The sorted input vector.
template
<
    typename T,
    bool (*Comparator)(T, T)
>
std::vector<T>& heap_sort(std::vector<T>& in);

template
<
    typename T,
    bool (*Comparator)(T, T)
>
class basic_heap
{
    public:
        /// Constructs a basic_heap.
        /// \param aMaxSize The maximum size of the heap.
        basic_heap(int aMaxSize);
        /// Constructs a basic_heap.
        /// \param in The initial data.
        /// \param aMaxSize The maximum size of the heap.
        basic_heap(const T* in, int aMaxSize);
        /// Constructs a basic_heap.
        /// \param in The initial data.
        basic_heap(const std::vector<T>& in);
        /// Destroys the heap.
        ~basic_heap();

        // Heap functions
        /// Adds an element to the heap.
        /// \param in The element to add
        /// \throw OutOfBounds Thrown when an addition occurs and the heap is full.
        /// \return A reference to this instance.
        basic_heap<T, Comparator>& add(T in);
        /// Removes an element from the heap.
        /// \throw OutOfBounds Thrown when trying to remove from an empty heap.
        /// \return The item that was removed.
        T remove();

        // Information
        /// Gets the current size of the heap.
        /// \return The current size of the heap.
        int get_size();
        /// Gets the maximum size of the heap.
        /// \return The max size of the heap.
        int get_max_size();

    private:
        T* heap;
        int mMaxSize;
        int mCurSize;

        int get_left_child(int index);
        int get_right_child(int index);
        int get_parent(int index);

        void heapify(int index);
};

template<typename T>
using minheap = basic_heap< T, less_than<T> >;
template<typename T>
using maxheap = basic_heap< T, greater_than<T> >;

template
<
    typename T,
    bool (*Comparator)(T, T)
>
basic_heap<T, Comparator>::basic_heap(int aMaxSize) :
    heap(new T[aMaxSize]), mMaxSize(aMaxSize), mCurSize(0) {}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
basic_heap<T, Comparator>::basic_heap(const T* in, int aMaxSize) :
    heap(new T[aMaxSize]), mMaxSize(aMaxSize), mCurSize(0)
{
    for (int vCount = 0; vCount < aMaxSize; vCount++)
       add(in[vCount]);
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
basic_heap<T, Comparator>::basic_heap(const std::vector<T>& in) :
    heap(new T[in.size()]), mMaxSize(in.size()), mCurSize(0)
{
    for (int vCount = 0; vCount < in.size(); vCount++)
        add(in[vCount]);
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
basic_heap<T, Comparator>::~basic_heap()
{
    delete[] heap;
    mMaxSize = 0;
    mCurSize = 0;
    heap = nullptr;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
T* heap_sort(T* in, int aSize)
{
    basic_heap<T, Comparator> vHeap(aSize);

    for (int Count = 0; Count < aSize; Count++)
        vHeap.add(in[Count]);

    for (int Count = 0; Count < aSize; Count++)
        in[Count] = vHeap.remove();

    return in;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
std::vector<T>& heap_sort(std::vector<T>& in)
{
    basic_heap<T, Comparator> vHeap(in.size());

    for (T vCur : in)
        vHeap.add(vCur);

    for (int Count = 0; Count < in.size(); Count++)
        in[Count] = vHeap.remove();

    return in;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
basic_heap<T, Comparator>& basic_heap<T, Comparator>::add(T in)
{
    // Make sure there is space for input
    if (mCurSize == mMaxSize)
        throw OutOfBounds(mMaxSize, mMaxSize - 1);

    // Actually input
    heap[mCurSize] = in;

    // Calculate indices
    int vNew = mCurSize;
    int vPar = get_parent(vNew);

    // While the new node is not the root and does not fall into the heap's order
    while (vPar != -1 && (*Comparator)(heap[vNew], heap[vPar]))
    {
        // Swap the nodes
        T vTmp = heap[vPar];
        heap[vPar] = heap[vNew];
        heap[vNew] = vTmp;

        // Update the indices
        vNew = vPar;
        vPar = get_parent(vNew);
    }

    mCurSize++;

    return *this;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
T basic_heap<T, Comparator>::remove()
{
    // Make sure there's something to remove
    if (mCurSize == 0)
        throw OutOfBounds(0, -1);

    // Move the last element to the front, forget the first
    T vTmp = heap[0];
    heap[0] = heap[mCurSize - 1];

    mCurSize--;

    // Heapify if there is a heap to heapify
    if (mCurSize > 0)
        heapify(0);

    return vTmp;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
int basic_heap<T, Comparator>::get_left_child(int index)
{
    return index * 2 + 1;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
int basic_heap<T, Comparator>::get_right_child(int index)
{
    return index * 2 + 2;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
int basic_heap<T, Comparator>::get_parent(int index)
{
    if (index == 0)
        return -1;

    return index / 2 - (index % 2 == 0 ? 1 : 0);
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
void basic_heap<T, Comparator>::heapify(int index)
{
    int vLC = get_left_child(index);

    // If the index has a child
    if (vLC < mCurSize)
    {
        int vSwapWith = -1;

        int vRC = vLC + 1;

        // Determine if a right child exists
        if (vRC < mCurSize)
        {
            // Determine if swapping is necessary
            if ( !(*Comparator)(heap[index], heap[vRC]) ||
                 !(*Comparator)(heap[index], heap[vLC]) )
            {
                // Choose the node to swap with
                if ((*Comparator)(heap[vRC], heap[vLC]))
                    vSwapWith = vRC;

                else
                    vSwapWith = vLC;
            }
        }

        else
        {
            // Determine if swapping is necessary
            if (!(*Comparator)(heap[index], heap[vLC]))
                vSwapWith = vLC;
        }

        // Swap if swapping is necessary
        if (vSwapWith > 0)
        {
            T vTmp = heap[index];
            heap[index] = heap[vSwapWith];
            heap[vSwapWith] = vTmp;

            // Heapify the next sub-heap
            heapify(vSwapWith);
        }
    }
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
int basic_heap<T, Comparator>::get_max_size()
{
    return mMaxSize;
}

template
<
    typename T,
    bool (*Comparator)(T, T)
>
int basic_heap<T, Comparator>::get_size()
{
    return mCurSize;
}

} // namespace DSLib

#endif // HEAP_H
