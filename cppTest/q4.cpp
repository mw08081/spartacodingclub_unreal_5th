#include <iostream>
#include <vector>
using namespace std;

class Animal
{
public:
    virtual void speak()
    {
        cout << "???\n";
    }
};

class Dog : public Animal
{
    void speak() override
    {
        cout << "Woof\n";
    }
};

class Cat : public Animal
{
    void speak() override
    {
        cout << "Meow\n";
    }
};

int main()
{
    vector<Animal *> zoo{new Dog, new Cat, new Animal};
    for (auto p : zoo)
        p->speak(); // Woof / Meow / ???

    for (auto p : zoo)
        delete p;
}