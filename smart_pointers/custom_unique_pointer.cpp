#include <iostream>

using namespace std;

template <typename T>
class my_unique_ptr {
    T *ptr;
public:
    my_unique_ptr() : ptr(nullptr) {}
    my_unique_ptr(T *p) : ptr (p) {}
    /* Delete copy constructor and copy assignment operator so that multiple copies cannot be created */
    my_unique_ptr(const my_unique_ptr &ref) = delete;
    my_unique_ptr *operator = (const my_unique_ptr &ref) = delete;
    /* move semantics */
    my_unique_ptr (my_unique_ptr && old_ref) {
        if (old_ref) {
            this->ptr = old_ref.ptr;
            delete old_ref.ptr;
        }
    }
    my_unique_ptr *operator = (my_unique_ptr &&old_ref) {
        this->ptr = old_ref.ptr;
        delete old_ref.ptr;
    }

    T& operator *() {
        return *(this->ptr);
    }
    T* operator ->() {
        return this->ptr;
    }
    ~my_unique_ptr() {delete ptr;}
};

int main() {
    my_unique_ptr <int> i = new int (10);
    cout << *i << endl;

    my_unique_ptr <float> f = new float(10.2);
    cout << *f << endl;
    return 0;
}
