#include <criterion/criterion.h>
#include <criterion/hooks.h>
#include <criterion/redirect.h>
#include <optional>
#include <string>

#include "../../src/utils/CommandLineParser.hpp"

Test(CmdParser, getOptionFail)
{
    CommandLineParser cmdParser(0, nullptr);
    cmdParser.addOption("--opt", "o", "option");
    cmdParser.parse();
    cr_assert_eq(cmdParser.getOption("long"), std::nullopt);
}

Test(CmdParser, getOptionSuccess)
{
    const char* const_argv[] = { "zappy_gui", "-p", "3000", "--ip", "127.0.0.1" };
    char* argv[5];
    for (int i = 0; i < 5; ++i) {
        argv[i] = const_cast<char*>(const_argv[i]);
    }

    CommandLineParser cmdParser(5, argv);

    cmdParser.addOption("--ip", "-i", "The ip to connect to");
    cmdParser.addOption("--port", "-p", "The port to connect to");

    cmdParser.parse();

    std::optional<std::string> opt = cmdParser.getOption("--port");
    if (opt.has_value()) {
        std::string optStr = opt.value();
        cr_assert_str_eq(optStr.c_str(), "3000");
    }
    std::optional<std::string> opt2 = cmdParser.getOption("--ip");
    if (opt.has_value()) {
        std::string optStr = opt2.value();
        cr_assert_str_eq(optStr.c_str(), "127.0.0.1");
    }
}

void setup_stdout_redirect(void) {
    cr_redirect_stdout();
}

Test(CmdParser, displayHelp, .init = setup_stdout_redirect)
{
    const char* const_argv[] = { "zappy_gui", "-h" };
    const int argc = 2;
    char* argv[argc];
    for (int i = 0; i < argc; ++i) {
        argv[i] = const_cast<char*>(const_argv[i]);
    }

    CommandLineParser cmdParser(argc, argv);
    cmdParser.addOption("--help", "-h", "Display this help message");

    cmdParser.displayHelp("zappy_gui");

    std::string expected_output = "Usage: zappy_gui -h, --help     [Display this help message]\n";
    fflush(stdout);

    std::FILE * output = cr_get_redirected_stdout();

    std::ostringstream oss;
    char buffer[1024];
    while (std::fgets(buffer, sizeof(buffer), output) != nullptr) {
        oss << buffer;
    }

    std::string output_str = oss.str();
    cr_assert_str_eq(output_str.c_str(), expected_output.c_str());
}
