#include <criterion/criterion.h>

Test(basics, test1)
{
    cr_assert(1 == 1, "1 is not equal to 1");
}
