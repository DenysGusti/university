#ifndef UNIVERSITY_TRANSPORT_INTERFACE_HPP
#define UNIVERSITY_TRANSPORT_INTERFACE_HPP

#include <string>

using namespace std;

class ITransport {
public:
    virtual ~ITransport() = default;

    virtual string getType() const noexcept = 0;

    virtual string deliver() const noexcept = 0;
};

#endif
