#pragma once

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(NonCopyable const &) = delete;
    NonCopyable &operator=(NonCopyable const &) = delete;

    // I am to lazy to implement them right now
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable &operator =(NonCopyable&&) = delete;

};
