#include<bits/stdc++.h>
using namespace std;
class User{
    protected:
    int id;
    string username;
    string password;
    public:
        User(int id, const string& name,const string& password);
        virtual void takeQuiz(const Quiz &quiz)
};
int main(){
    return  0;
}