#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

struct Fd {
    int fd{-1};
    Fd() = default;
    explicit Fd(int x): fd(x) {}
    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;
    Fd(Fd&& o) noexcept : fd(o.fd) { o.fd = -1; }
    Fd& operator=(Fd&& o) noexcept { if (this!=&o){ reset(); fd=o.fd; o.fd=-1; } return *this; }
    ~Fd(){ reset(); }
    void reset(int x=-1){ if(fd!=-1) ::close(fd); fd=x; }
    int get() const { return fd; }
    explicit operator bool() const { return fd!=-1; }
    int release(){ int t=fd; fd=-1; return t; }
};

inline void set_nonblock(int fd){
    int fl = ::fcntl(fd, F_GETFL, 0);
    if (fl < 0 || ::fcntl(fd, F_SETFL, fl | O_NONBLOCK) < 0) throw std::runtime_error("fcntl O_NONBLOCK");
}
