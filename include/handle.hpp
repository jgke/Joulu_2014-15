/**
 * \file handle.hpp
 * Signal handling.
 */

#ifndef HANDLE_HPP
#define HANDLE_HPP

/**
 * Handle signals, and call cb for them.
 */
void handle_signals(void (*cb)(int sig));

#endif
