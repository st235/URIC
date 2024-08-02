#ifndef __URIC_PATH_NORMALISER_H__
#define __URIC_PATH_NORMALISER_H__

#include <string>
#include <vector>

namespace uri {

namespace path {

std::vector<std::string> SplitHierarchicalSegments(const std::string& path);
std::string CodeIfNecessary(const std::string& path);
std::vector<std::string> RemoveDotSegments(const std::vector<std::string>& segments);

std::string Normalise(const std::string& path);

} // namespace path

} // namespace uri

#endif // __URIC_PATH_NORMALISER_H__
