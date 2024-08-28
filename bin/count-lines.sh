#!/bin/bash
find "$(pwd)" -path "$(pwd)/build" -prune -o -type f \( -name "*.hpp" -o -name "*.cpp" \) ! -name "json.hpp" -exec wc -l {} +
