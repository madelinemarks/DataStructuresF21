template <typename T>
Vector<T>::Vector()     // default zero parameter constructor
{
    theSize = 0;        
    theCapacity = 0;
    array = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector &rhs)    // copy constructor
{
    theSize = rhs.theSize;          // assign values of vector being copied
    theCapacity = rhs.theCapacity;
    array = nullptr;

    array = new T[theCapacity];             // iterate through vector being copied and populate array
    for (int i = 0; i < theSize; ++i)
        array[i] = rhs.array[i];
}

template <typename T>
Vector<T>::Vector(Vector &&rhs)     // move constructor
{
    rhs.array = nullptr;        
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template <typename T>
Vector<T>::Vector(int num, const T& val)  // num elements w value of val
{
    theSize = num;
    theCapacity = (num*2)+1;    
    array = new T[theCapacity];             // allocate space for new array
    for (int i = 0; i < theSize; ++i) 
        array[i] = val;                    // populate array
    // populate with val
}

template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end) // constructs with elements [start,end)
{
    theSize = end - start;          
    theCapacity = (theSize*2)+1;
    array = new T[theCapacity];     // allocate space for new array

    for (int i = 0; i < theSize; i++)       // populate array
    {  
        array[i] = *(start+i);      // pointer to iterator - position in array 
    }
}

template <typename T>
Vector<T>::~Vector()    // destructor
{
    delete[] array;
}

template <typename T>
T& Vector <T>::operator[](int index)    // index operator
{
    return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const
{
    return array[index];
}

template <typename T>
const Vector<T> &Vector<T>::operator=(const Vector &rhs)    // copy assignment operator
{
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&rhs)   // move assignment operator
{
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(array, rhs.array);

    return *this;
}

template <typename T>
T& Vector<T>::at(int loc)   // at function. safer than operator[]
{
    if (loc > theSize-1 || loc < 0)     // check bounds
        std::cerr<<"OUT OF RANGE";      
    else
        return array[loc];
}

template <typename T>
const T& Vector<T>::at(int loc) const
{
    if (loc > theSize-1 || loc < 0)     // check bounds
        std::cerr<<"OUT OF RANGE";      
    else
        return array[loc];
}

template <typename T>
T& Vector<T>::front()   // reference to the first element
{
    return array[0];
}

template <typename T>
const T& Vector<T>::front() const     
{
    return array[0];
}

template <typename T>
const T& Vector<T>::back() const    // reference to the last element
{
    return array[theSize - 1];
}

template <typename T>
int Vector<T>::size() const
{
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const
{
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return size() == 0;         // true if size = 0
}

template <typename T>
void Vector<T>::clear()     // delete all elements
{
    theSize = 0;            // set size to 0 to empty
}

template <typename T>
void Vector<T>::push_back(const T& val)     // insert to the end
{
    if(theSize == theCapacity)
        reserve(2*theCapacity+1);             // reserve new space
    array[theSize++] = val;
}

template <typename T>
void Vector<T>::pop_back()      // delete last element
{
    --theSize;
}

template <typename T>
void Vector<T>::resize(int num, T val)        // resize vector
{
    int og = theSize;          // temp variable to keep track of original size
    if (num > theCapacity) {
        reserve((num * 2) + 1);
    }
    else if (num > theSize)     // if resizing to bigger size...
    {
        theSize = num;
        reserve((num * 2) + 1);     // reserve new space

        for (int i = og; i < theSize; i++)      // populate new elements w val
        {
            array[i] = val;
        }
    }
    else if (num < theSize)      // if resizing to smaller size, remove extra elements (don't have to clear mem)
    {
        for (int i = og; i > num; i--)
        {
            theSize--;
        }
    }
}

template <typename T>
void Vector<T>::reserve(int newCapacity)    // reserve memory
{
    if (newCapacity < theSize)
        return;

    T *newArray = new T[newCapacity];       // allocate space
    for (int i = 0; i < theSize; ++i)
        newArray[i] = std::move(array[i]);      // move array contents

    theCapacity = newCapacity;              
    std::swap(array, newArray);
    delete [] newArray;         // memory handling
}

template <typename T>   // print out all elements, ofc is delimiter 
void Vector<T>::print(std::ostream& os, char ofc) const
{
    for (int i = 0; i < theSize; ++i)
    {
        os << array[i] << ofc;
    }
}


// iterator support

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return &array[0];       // REFERENCE & will return memory address for iterator
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return &array[0];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return &array[theSize];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return &array[theSize];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val)
{
    if(theSize == theCapacity)
        reserve(2*theCapacity+1);           // reserve new space
    theSize++;
    for (iterator i = end()-1; i!=itr-1; i--)   // iterate through array w/ i
    {
        *(i+1) = *i;
    }
    *itr = val;
    return itr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr)   
{
    for (iterator i = itr; i != end(); i++)     // iterate through array w/ i
    {
        *i = *(i+1);                // move through array w pointers to locations
    }
    theSize--;                      // remove element once @ destination
    return itr;         
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end)
{
    for (iterator i = start; i <= end; i++)     // iterate from start to end
    {
        *i = *(i+1);                    // move through array w pointers to locations
    }
    theSize = end - start;              // subtract iterator positions to get new size
    return end;
}

template <typename T>
void Vector<T>::doubleCapacity()
{
    if (theCapacity == 0) {         // account for 0
        theCapacity = 1;
        reserve(theCapacity);           // reserve space
    }
    else {
        theCapacity *= 2;               // double capacity
        reserve(theCapacity);           // reserve capacity
    }
}

template <typename T>                                       
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs.size() != rhs.size())       // compare sizes first
       { return false; }
    else {
        for (int i = 0; i <= lhs.size(); i++)   // then compare array contents
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs.size() == rhs.size())       // compare sizes first
        { return false; }
    else {
        for (int i = 0; i<= lhs.size(); i++)   // then compare array contents
        {
            if (lhs[i] == rhs[i])
                return false;
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i) {        // similar to print function
        os << v[i];
        if (i != v.size() - 1)          // account for spaces
            os << " ";
    }
    return os;
}
