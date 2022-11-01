#include "solution.hpp"

struct MapToBucket
{
  std::array<size_t, 100> m_map;

  MapToBucket()
  {
    for (int v = 0; v < m_map.size(); ++v)
    {
      size_t index = 0;
      if (v >= 0 && v < 13)        index = 0; // 13
      else if (v >= 13 && v < 29)  index = 1; // 16
      else if (v >= 29 && v < 41)  index = 2; // 12
      else if (v >= 41 && v < 53)  index = 3; // 12
      else if (v >= 53 && v < 71)  index = 4; // 18
      else if (v >= 71 && v < 83)  index = 5; // 12
      else if (v >= 83 && v < 100) index = 6; // 17
      m_map[v] = index;
    }
  }
};

static const MapToBucket g_conversion;

static std::size_t mapToBucket(std::size_t v) 
{
  return g_conversion.m_map[v];
}

std::array<std::size_t, NUM_BUCKETS> histogram(const std::vector<int> &values) {
  std::array<std::size_t, NUM_BUCKETS> retBuckets{0};
  for (auto v : values) {
    retBuckets[mapToBucket(v)]++;
  }
  return retBuckets;
}
