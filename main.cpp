#include <iostream>
#include "strutils.h"

using namespace strutils;

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string test{"  hello world  "};
    std::cout << test << std::endl;
    std::cout << strip(test) << std::endl;
    auto vec = split(test, ' ');
    std::cout << "size of vec is " << vec.size() << std::endl;
    for(const auto& i : vec){
        std::cout << i << std::endl;
    }
    std::string num{"100.1"};
    std::cout << num << std::endl;
    std::cout << to_number<double>(num) + 1 << std::endl;

    std::cout << test + " " + num << std::endl;
    chop(test, 14);
    std::cout << test << std::endl;

    std::string str{"this is a test"};
    std::cout << chopped(str, 13) << std::endl;

    std::string upcase{"I LOVE YOU!"};
    std::cout << to_lower(upcase) << std::endl;

    std::string lowercase{"I LOVE TANG"};
    std::cout << to_upper(lowercase) << std::endl;

    std::string str1{"this is a title"};
    std::cout << capitalize(str1) << std::endl;

    std::string x = "Nine pineapples";
    std::cout << mid(x, 5, 4) << std::endl;
    std::cout << mid(x, 5) << std::endl;

    std::cout << reverse(x) << std::endl;

    std::cout << contains(x, "pine") << std::endl;
    std::cout << contains(x, "pina") << std::endl;
    return 0;
}
