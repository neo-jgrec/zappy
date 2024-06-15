#ifndef COMMAND_LINE_PARSER_HPP
    #define COMMAND_LINE_PARSER_HPP

    #include <map>
    #include <optional>
    #include <string>
    #include <vector>


class CommandLineParser {

    private:
        std::vector<std::string> args;
        std::map<std::string, std::tuple<std::string, std::string, std::optional<std::string>>> options;

    public:
        CommandLineParser(const int argc, char **argv) { args.assign(argv, argv + argc); }

        void addOption(const std::string &longOpt, const std::string &shortOpt, const std::string &description);

        void parse();

        [[nodiscard]] std::optional<std::string> getOption(const std::string &longOpt) const;

        void displayHelp(const std::string &binaryName) const;
};

#endif //COMMAND_LINE_PARSER_HPP
