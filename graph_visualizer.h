#pragma once

#include <vector>
#include <string>

void outputGraphToDotFile(const std::vector<std::vector<int>>& graph, const std::vector<bool>& active_nodes, const std::string& filename);
