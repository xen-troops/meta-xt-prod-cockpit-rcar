#ifndef __ACTIVATED__EVENT__
#define  __ACTIVATED__EVENT__
class ActivatedEvent final
{
public:
    ActivatedEvent();
    ActivatedEvent(const ActivatedEvent&) = delete;
    ActivatedEvent(ActivatedEvent&&) = delete;  
    ~ActivatedEvent();
private:
    int file;
};

#endif

