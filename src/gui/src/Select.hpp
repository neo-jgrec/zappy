#ifndef SELECT_HPP
    #define SELECT_HPP

    #include <sys/select.h>
    #include <unistd.h>

class Select {
    private:
        fd_set read_fds;
        int max_fd;

    public:
        Select();
        ~Select();

        void addFd(int fd);

        void removeFd(int fd);
        bool isSet(int fd) const;
        int select();
};

#endif //SELECT_HPP
