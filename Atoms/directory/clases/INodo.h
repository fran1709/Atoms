#ifndef _INODO_
#define _INODO_ 1

using namespace std;
class INodo {
    public:
        int getId() {
            return this->id;
        }

        void setId(int pId) {
            this->id = pId;
        }

        string getName() {
            return this->name;
        }

        void setName(string pName) {
            this->name = pName;
        }
        
    protected:
        int id;
        string name;
};

#endif