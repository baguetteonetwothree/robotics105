#include "Console.hpp"

// Mutex used to ensure thread safety in printing
std::mutex s_printMutex;
