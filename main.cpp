#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class Bad_egg : public exception {

    public: 

        const char* what() const noexcept override {

            return "This egg is bad and cannot be eaten.";
        }

};

class now_empty_carton : public exception {

    public: 

        const char* what() const noexcept override {

            return "The carton is now empty.";
        }

};

class full_carton : public exception {

    public: 

        const char* what() const noexcept override {

            return "The carton is full.";
        }

};


class Egg {

    private: 

        string size;
        string flavor;
    
    public:

        Egg(string s, string f) : size(s), flavor(f) {}

        virtual void eat_egg() = 0;

        string get_size() {
            return size;
        }

        string get_flavor() {
            return flavor;
        }


};

class BoiledEgg : public Egg {

    public:

        BoiledEgg(string s, string f) : Egg(s, f) {}

        void eat_egg() override {

            cout << "Eating a << get_size() >> boiled egg with a << get_flavor() >> flavor." << endl;

        }

};

class ScrambledEgg : public Egg {

    public:

        ScrambledEgg(string s, string f) : Egg(s, f) {}

        void eat_egg() override {

            cout << "Eating a << get_size() >> scrambled egg with a << get_flavor() >> flavor with the soft and fluffy texture." << endl;

        }

};

class RottenEgg : public Egg {

    public:

        RottenEgg(string s, string f) : Egg(s, f) {}

        void eat_egg() override {

            throw Bad_egg();

        }

};






class Carton {

    private: 

        vector<Egg*> eggs;

    public:

        void push_back(Egg* e) {
            
            if(eggs.size() >= 12) {
                throw full_carton();
            }
            eggs.push_back(e);

        }

        void remove_and_eat_egg() {

            if (eggs.empty()) {
                throw now_empty_carton();
            }
        

            Egg* e = eggs.back();

            try {

                e->eat_egg();
            }

            catch (Bad_egg& bad_egg) {

                throw bad_egg;
            }

        }

        size_t get_size() {
            return eggs.size();
        }

        Egg* get_value(size_t index) {
            
            return eggs.at(index);
        }

};


int main() {
    
    Egg* egg1 = new BoiledEgg("large", "herbed");
    Egg* egg2 = new RottenEgg("medium", "plain");
    Egg* egg3 = new ScrambledEgg("small", "spicy");

    assert(egg1->get_size() == "large");

    assert(egg2->get_flavor() == "plain");

    assert(egg3->get_size() == "small");


    Carton carton2;
    
    carton2.push_back(egg1);
    carton2.push_back(egg2);
    carton2.push_back(egg3);

    assert(carton2.get_size() == 3);
    assert(carton2.get_value(0) == egg1);
    assert(carton2.get_value(2)->get_flavor() == "spicy");
    assert(carton2.get_value(1)->get_size() == "medium");

    

    
}
