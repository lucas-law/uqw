#include "uqw.hpp"
#include <iostream>

using namespace uqw;
using namespace std;

int main()
{
    unqlite_wrapper uqw("test.db");

    uqw.put("key1", std::vector<unsigned char>{2, 3, 4}, false);
    uqw.put("key2", std::vector<unsigned char>{2, 3, 4, 5}, true);

    std::vector<unsigned char> value1 = uqw.get("key1", false);
    std::vector<unsigned char> value2 = uqw.get("key2", true);
    if (value1.empty()) printf("get value1 failed!\n");
    if (value2.empty()) printf("get value2 failed!\n");

    printf("value1:\n");
    for (const auto &it : value1) {
        printf("%d ", it);
    }

    printf("\n");

    printf("value2:\n");
    for (const auto &it : value2) {
        printf("%d ", it);
    }

    printf("\n");

    return 0;
}
