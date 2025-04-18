#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <string>
#include <mutex>
#include <vector>

class LoadBalancer
{
public:
    void addEndpoint(const std::string& endpoint);
    std::string getNextEndpoint();

private:
    std::vector<std::string> endpoints_;
    size_t currentIndex_ = 0;
    std::mutex mutex_;
};

#endif // LOADBALANCER_H
