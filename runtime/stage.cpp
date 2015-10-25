#include "message.hxx"
#include "stage.hxx"


Stage::Stage(int _id) : id(_id) {
}

Message* Stage::get_message() {
    Message* message;

    {
        std::unique_lock<std::mutex> lock(mailbox_mutex);
        mailbox_cv.wait(lock, [this]{return !this->mailbox.empty();});
        message = mailbox.front();
        mailbox.pop_front();
    }

    return message;
}

void Stage::put_message(Message *message) {
    std::unique_lock<std::mutex> lock(mailbox_mutex);
    mailbox.push_back(message);
    mailbox_cv.notify_one();
}


void Stage::run() {
    Message *message;
    void *result;

    while (true) {
        message = get_message();

        switch (message->type) {
            case Message::CONSTRUCT_MESSAGE:
                message->target.invokeConstructor(message->id, message->arguments);
                break;

            case Message::BASIC_MESSAGE:
                message->target.invokeMessage(message->id, message->arguments);
                break;

            case Message::CONTINUATION_MESSAGE:
                message->target.invokeMessage(message->id, message->arguments);
                StageService::sendResolveMessage(message->continuation_director);
                break;

            case Message::TOKEN_MESSAGE:
                result = message->target.invokeMessage(message->id, message->arguments);
                StageService::sendTokenMessage(message->continuation_director, result);
                break;

            case Message::CONSTRUCT_CONTINUATION_MESSAGE:
                message->target.invokeConstructor(message->id, message->arguments);
                StageService::sendTokenMessage(message->continuation_director, (void*)message->target);
                break;

            default:
                cerr << "Stage " << id << " attempted to process an unknown message: " << message << endl;


        }
    }
}
