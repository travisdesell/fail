#ifndef FAIL_STAGE
#define FAIL_STAGE

#include <list>

#include <mutex>
#include <condition_variable>

#include "message.hxx"

class Stage {
    private:
        int id;

        std::mutex mailbox_mutex;
        std::condition_variable mailbox_cv;

        std::list<Message*> mailbox;

        Message* get_message();

    public:
        Stage(int _id);

        void put_message(Message* message);
        void run();

};

#endif
