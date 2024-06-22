/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Arch]
** File description:
** debug_print
*/

#ifndef DEBUG_PRINT_HPP_
    #define DEBUG_PRINT_HPP_

    #ifdef DEBUG
        #pragma message "DEBUG is defined"

        #define _D_GREEN_ANSII "\033[0;32m"
        #define _D_END_ANSII "\033[0m"

        #define _D_STRING _D_GREEN_ANSII "[DEBUG] " _D_END_ANSII

        #define debug_print std::cerr << _D_STRING << __FILE__ << ":" << __LINE__ << " "
    #else
        #define debug_print 0 && std::cerr
    #endif

#endif /* !DEBUG_PRINT_HPP_ */
