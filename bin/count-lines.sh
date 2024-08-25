#!/bin/bash
find "$(pwd)" -type f \( -name "*.hpp" -o -name "*.cpp" \) -exec wc -l {} +
