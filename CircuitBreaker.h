#ifndef CIRCUITBREAKER_H
#define CIRCUITBREAKER_H

#include <chrono>
#include <mutex>

// CircuitBreaker.h
class CircuitBreaker {
public:
    enum class State {
        CLOSED,
        OPEN,
        HALF_OPEN
    };

    CircuitBreaker(int failureThreshold,
                   std::chrono::milliseconds resetTimeout);


    bool isAllowed();
    void recordSuccess();

    void recordFailure();

private:
    const int failureThreshold_;
    const std::chrono::milliseconds resetTimeout_;
    int failures_;
    State state_;
    std::chrono::steady_clock::time_point lastStateChange_;
    std::mutex mutex_;
};

#endif // CIRCUITBREAKER_H
