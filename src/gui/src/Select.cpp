#include "Select.hpp"
#include "GuiException.hpp"

#include <algorithm>

Select::Select() : max_fd(-1) {
    FD_ZERO(&read_fds);
}

Select::~Select() {
    while (max_fd >= 0) {
        removeFd(max_fd);
    }
}

void Select::addFd(int fd) {
    FD_SET(fd, &read_fds);
    max_fd = std::max(max_fd, fd);
}

void Select::removeFd(int fd) {
    FD_CLR(fd, &read_fds);
    if (fd == max_fd) {
        while (max_fd >= 0 && !FD_ISSET(max_fd, &read_fds)) {
            --max_fd;
        }
    }
}

bool Select::isSet(int fd) const {
    return FD_ISSET(fd, &read_fds);
}

int Select::select() {
    fd_set copy_fds = read_fds;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    int ret = ::select(max_fd + 1, &copy_fds, nullptr, nullptr, &tv);
    
    if (ret == -1)
        throw guiException("Select::select: select failed");
    return ret;
}
