#include "CircuitBreaker.h"

CircuitBreaker::CircuitBreaker(int failureThreshold,
                               std::chrono::milliseconds resetTimeout): failureThreshold_(failureThreshold)
  , resetTimeout_(resetTimeout)
  , failures_(0)
  , state_(State::CLOSED) { }

bool CircuitBreaker::isAllowed()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (state_ == State::OPEN) {
        if (std::chrono::steady_clock::now() >= lastStateChange_ + resetTimeout_) {
            state_ = State::HALF_OPEN;
            return true;
        }
        return false;
    }

    return true;
}

void CircuitBreaker::recordSuccess()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (state_ == State::HALF_OPEN) {
        state_ = State::CLOSED;
        failures_ = 0;
    }
}

void CircuitBreaker::recordFailure()
{
    std::lock_guard<std::mutex> lock(mutex_);
    failures_++;

    if (failures_ >= failureThreshold_) {
        state_ = State::OPEN;
        lastStateChange_ = std::chrono::steady_clock::now();
    }
}
