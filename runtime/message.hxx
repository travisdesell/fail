#ifndef FAIL_MESSAGE
#define FAIL_MESSAGE

class Message {
    private:
        int id;     //an id for this message
        int type;   //the message type
        Actor *target;
        Actor *continuation_director;
};

#endif
