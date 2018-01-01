#include "path_manager.h"


PathManager::PathManager(const uint32_t max, const uint32_t start,
                         const uint32_t end, const bool early_break)
  : _max_size(max), _destination(end), _visited({start}), _shortest_path(nullptr),
    _early_break(early_break)
{}
