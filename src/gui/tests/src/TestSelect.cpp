#include <criterion/criterion.h>

#include "../../src/Select.hpp"
#include "../../src/GuiException.hpp"

#include <fcntl.h>
#include <unistd.h>

Test(Select, isSet)
{
    Select select;

    select.addFd(1);
    cr_assert_eq(select.isSet(1), true, "got %d, expected 1", select.isSet(1));
}

Test(Select, select)
{
    Select select;

    select.addFd(1);
    cr_assert_eq(select.select(), 0, "got %d, expected 0", select.select());
}

Test(Select, selectThrows)
{
    Select select;
    int fd = open("/dev/null", O_RDONLY);
    cr_assert(fd != -1, "Failed to open /dev/null");
    close(fd);

    select.addFd(fd);

    cr_assert_throw(select.select(), guiException, "Select::select: select failed");
}

Test(Select, removeFd)
{
    Select select;

    select.addFd(1);
    select.removeFd(1);
    cr_assert_eq(select.isSet(1), false, "got %d, expected 0", select.isSet(1));
}
