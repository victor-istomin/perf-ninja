#include "solution.h"

#include <random>
#include <typeindex>

void generateObjects(InstanceArray& array) {
    std::default_random_engine generator(0);
    std::uniform_int_distribution<std::uint32_t> distribution(0, 2);

    InstanceArray arrays[3];

    for (std::size_t i = 0; i < N; i++) {
        int value = distribution(generator);
        if (value == 0) {
          arrays[value].push_back(std::make_unique<ClassA>());
        } else if (value == 1) {
          arrays[value].push_back(std::make_unique<ClassB>());
        } else {
          arrays[value].push_back(std::make_unique<ClassC>());
        }
    }

    array.reserve(arrays[0].size() + arrays[1].size() + arrays[2].size());
    for(InstanceArray& a : arrays)
      std::move(a.begin(), a.end(), std::back_inserter(array));
}

// Invoke the `handle` method on all instances in `output`
void invoke(InstanceArray& array, std::size_t& data) 
{
    for (const auto& item: array) 
    {
        item->handle(data);
    }
}
