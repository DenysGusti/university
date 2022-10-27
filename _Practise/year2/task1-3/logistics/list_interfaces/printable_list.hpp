#ifndef UNIVERSITY_PRINTABLE_LIST_HPP
#define UNIVERSITY_PRINTABLE_LIST_HPP

class IPrintableList {
public:
    virtual ~IPrintableList() = default;

    virtual void printAllToTerminal(bool reversed) const noexcept = 0;

    virtual void printAllToFile(bool reversed) const noexcept = 0;
};

#endif
