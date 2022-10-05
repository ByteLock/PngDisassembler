#include <iostream>
#include <vector> 

class Person {
    public:
        char name[256];
        int age;
};

int main() {

    // std::vector<int> my_vector;
    // std::cout << my_vector.empty() << "\n";
    // for(int i = 0; i < 10; i++) {
    //     my_vector.push_back(i);
    // }
    // for (auto i = my_vector.begin(); i != my_vector.end(); ++i)
    //     std::cout << *i << " ";

    Person p;
    strcpy(p.name, "dennis");
    p.age = 17;
    printf("%s", p.name);

    return 0;
}