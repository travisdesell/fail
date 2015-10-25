#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

class HelloWorld {
    private:

    public:
        HelloWorld construct(string[] arguments) {
            StandardOutput *standard_output = new StandardOutput();

            ContinuationDirector *cd1 = new ContinuationDirector();
            send(standard_output, StandardOutput.println_message, StandardOutput.serialize_println_arguments("hello"), null, cd1);
            send(standard_output, StandardOutput.println_message, StandardOutput.serialize_println_arguments(" world!"), cd1, null);

        }
};




int main(int argc, char **argv) {
}


#endif
