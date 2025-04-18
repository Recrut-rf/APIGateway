#include "LoadBalancer.h"

void LoadBalancer::addEndpoint(const std::string &endpoint)
{
    std::lock_guard<std::mutex> lock(mutex_);
    endpoints_.push_back(endpoint);
}

std::string LoadBalancer::getNextEndpoint()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (endpoints_.empty())
    {
        throw std::runtime_error("No endpoints available");
    }

    currentIndex_ = (currentIndex_ + 1) % endpoints_.size();
    return endpoints_[currentIndex_];
}
