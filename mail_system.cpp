#include <bits/stdc++.h>
using namespace std;

class Email {
private:
    string to;
    string from;
    string subject;
    string body;
    string date;

public:
    bool opened;

    Email() : opened(false) {}

    Email(string f, string t, string s, string b, string d)
        : from(f), to(t), subject(s), body(b), date(d), opened(false) {}

    string getSubject() const { return subject; }
    string getFrom() const { return from; }
    string getTo() const { return to; }
};

class User {
public:
    string username;
    vector<Email> inbox;
    vector<Email> outbox;

    User() = default;

    User(string uname) : username(uname) {}

    void sendEmail(const Email& e) {
        outbox.push_back(e);
    }

    void receiveEmail(const Email& e) {
        inbox.push_back(e);
    }

    void showInbox() {
        cout << "Inbox for " << username << ":\n";
        for (const auto& it : inbox) {
            cout << "From: " << it.getFrom() << " | Subject: " << it.getSubject() << "\n";
        }
    }

    void showOutbox() {
        cout << "Outbox for " << username << ":\n";
        for (const auto& it : outbox) {
            cout << "To: " << it.getTo() << " | Subject: " << it.getSubject() << "\n";
        }
    }
};

class MailManagement {
private:
    unordered_map<string, User> users;

public:
    void registerUser(const User& u) {
        if (users.count(u.username)) {
            cout << "User already registered\n";
        } else {
            users[u.username] = u;
            cout << "User " << u.username << " registered.\n";
        }
    }

    void showInbox(const string& id) {
        if (!users.count(id)) {
            cout << "User not found\n";
            return;
        }
        users[id].showInbox();
    }

    void showOutbox(const string& id) {
        if (!users.count(id)) {
            cout << "User not found\n";
            return;
        }
        users[id].showOutbox();
    }

    void sendEmail(const string& from, const string& to,
                   const string& subject, const string& body, const string& date) {
        if (!users.count(from) || !users.count(to)) {
            cout << "Sender or receiver does not exist.\n";
            return;
        }

        Email email(from, to, subject, body, date);
        users[from].sendEmail(email);
        users[to].receiveEmail(email);

        cout << "Email sent from " << from << " to " << to << ".\n";
    }
};

int main() {
    MailManagement system;

    system.registerUser(User("alice"));
    system.registerUser(User("bob"));

    system.sendEmail("alice", "bob", "Hello", "How are you?", "2025-05-22");
    system.sendEmail("bob", "alice", "Re: Hello", "I'm fine, thanks!", "2025-05-22");

    system.showInbox("alice");
    system.showInbox("bob");
    system.showOutbox("alice");
    system.showOutbox("bob");

    return 0;
}
