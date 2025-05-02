#include <iostream>
using namespace std;


class EnglishWriting {
    public:
        virtual void call () = 0;

};

class Essay : public EnglishWriting {
    public:
        void call () {
            cout << "Essay" << endl;
        }
};

class Poem : public EnglishWriting {
    public:
        void call () {
            cout << "Poem" << endl;
        }
};

class Report : public EnglishWriting {
    public:
        void call () {
            cout << "Report" << endl;
        }
};

int main (){
    EnglishWriting* obj = new Essay ();
    obj -> call();
    EnglishWriting* obj2 = new Poem ();
    obj2 -> call();
    EnglishWriting* obj3 = new Report ();
    obj3 -> call();

    return 0;
}

