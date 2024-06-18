#include <criterion/criterion.h>
#include "server.h"

#define NB_FLAGS 6
#define PORT 0
#define WIDTH 1
#define HEIGHT 2
#define NAME 3
#define CLIENT_NB 4
#define FREQ 5

Test(init_flags, valid_args) {
    flags_t flags;
    const char *args[] = {
        "-p", "8080",
        "-x", "20",
        "-y", "20",
        "-n", "Team1", "Team2",
        "-c", "10",
        "-f", "100",
        NULL
    };

    bool result = init_flags(&flags, args);
    cr_assert(result, "init_flags should return true for valid arguments");
    cr_assert_eq(flags.port, 8080, "Port should be 8080");
    cr_assert_eq(flags.width, 20, "Width should be 20");
    cr_assert_eq(flags.height, 20, "Height should be 20");
    cr_assert_str_eq(flags.names[0], "Team1", "First team name should be Team1");
    cr_assert_str_eq(flags.names[1], "Team2", "Second team name should be Team2");
    cr_assert_eq(flags.nb_clients, 10, "Number of clients should be 10");
    cr_assert_eq(flags.frequency, 100, "Frequency should be 100");

    destroy_flags(&flags);
}

Test(init_flags, missing_required_args) {
    flags_t flags;
    const char *args[] = {
        "-p", "8080",
        "-x", "20",
        "-y", "20",
        NULL
    };

    bool result = init_flags(&flags, args);
    cr_assert_not(result, "init_flags should return false for missing required arguments");
}

Test(init_flags, invalid_values) {
    flags_t flags;
    const char *args[] = {
        "-p", "-1",
        "-x", "50",
        "-y", "50",
        "-n", "Team1",
        "-c", "500",
        "-f", "20000",
        NULL
    };

    bool result = init_flags(&flags, args);
    cr_assert_not(result, "init_flags should return false for invalid argument values");
}
