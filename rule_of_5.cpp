
/* Rule of 5 : 
 * If a class has any one of the following implementation then it must have
 * all of the following implementation:

 * 1) Destructor
 * 2) copy constructor
 * 3) copy assignemt operator
 * 4) move constructor
 * 5) move assignemt operator
 * The following program illustrates this concept.
 */

#include <iostream>

using namespace std;

class ruleof5 {
private:
    int *a_;
    int size_;
public:
    ruleof5(int size) : size_(size) , a_ (new int[size]) {
        cout << "normal constructor " << endl;
    }

    ruleof5() : size_(0) , a_(nullptr) {}

    ruleof5(const ruleof5 &obj) {
        cout << "copy constructor called " << endl;
        this->size_ = obj.size_;
        this->a_ = new int [size_];
    }
    ruleof5 &operator = (const ruleof5 &t) {
        cout << "assignment operator called " << endl;
        if (this != &t) {
            delete []this->a_;
            this->size_ = t.size_;
            this->a_ = new int [this->size_];
            for (int i=0; i<t.size_; i++) {
                this->a_[i] = t.a_[i];
            }
        }
        return *this;
    }
    ~ruleof5 () {
        cout << "delete called" << endl;
        delete [] a_;
    }

    ruleof5 (ruleof5 &&obj) noexcept {
        cout << "move constructor called " << endl;
        this->size_ = obj.size_;
        this->a_ = obj.a_;
        obj.a_ = nullptr;
        obj.size_ = 0;
    }

    ruleof5 & operator = (ruleof5 &&obj) {
        cout << "move assignment operator called " << endl;
        if (this != &obj) {
            delete [] this->a_;
            this->a_ = obj.a_;
            this->size_ = obj.size_;
            obj.a_ = nullptr;
            obj.size_ = 0;
        }
        return *this;
    }
};

int main() {
    class ruleof5 obj(10);
    class ruleof5 obj1 = obj;
    class ruleof5 obj2;
    obj2 = obj1;
    class ruleof5 obj3 = move(obj1);
    class ruleof5 obj4(5);
    obj4 = move(obj2);
}
