#include <sys/select.h>
#include <unistd.h>
#include <algorithm>

class Select {
    private:
        fd_set read_fds;
        int max_fd;

    public:
        Select() : max_fd(-1) {
            FD_ZERO(&read_fds);
        }

        ~Select() {
            while (max_fd >= 0) {
                removeFd(max_fd);
            }
        }

        void addFd(int fd) {
            FD_SET(fd, &read_fds);
            max_fd = std::max(max_fd, fd);
        }

        void removeFd(int fd) {
            FD_CLR(fd, &read_fds);
            if (fd == max_fd) {
                while (max_fd >= 0 && !FD_ISSET(max_fd, &read_fds)) {
                    --max_fd;
                }
            }
        }

        bool isSet(int fd) const {
            return FD_ISSET(fd, &read_fds);
        }

        int select() {
            fd_set copy_fds = read_fds;
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            return ::select(max_fd + 1, &copy_fds, nullptr, nullptr, &tv);
        }
};