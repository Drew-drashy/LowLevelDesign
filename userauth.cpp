#include <iostream>
#include <unordered_map>
#include <string>

// ----------------- User Class -----------------
class User {
public:
    std::string username;
    std::string hashedPassword;

    User(std::string uname, std::string hpass)
        : username(uname), hashedPassword(hpass) {}
};

// -------------- PasswordHasher Interface --------------
class PasswordHasher {
public:
    virtual std::string hash(const std::string& password) = 0;
    virtual ~PasswordHasher() {}
};

class SimpleHasher : public PasswordHasher {
public:
    std::string hash(const std::string& password) override {
        // WARNING: Use real hashing in production (e.g., bcrypt/SHA256)
        std::hash<std::string> hasher;
        return std::to_string(hasher(password));
    }
};

// ----------------- UserStore Interface -----------------
class UserStore {
public:
    virtual User* getUser(const std::string& username) = 0;
    virtual void addUser(const User& user) = 0;
    virtual ~UserStore() {}
};

class InMemoryUserStore : public UserStore {
private:
    std::unordered_map<std::string, User> users;
public:
    User* getUser(const std::string& username) override {
        if (users.find(username) != users.end())
            return &users[username];
        return nullptr;
    }

    void addUser(const User& user) override {
        users[user.username] = user;
    }
};

// ----------------- Session Manager -----------------
class SessionManager {
private:
    std::unordered_map<std::string, bool> activeSessions;
public:
    void createSession(const std::string& username) {
        activeSessions[username] = true;
    }

    void destroySession(const std::string& username) {
        activeSessions.erase(username);
    }

    bool isLoggedIn(const std::string& username) {
        return activeSessions.count(username) > 0;
    }
};

// ----------------- Authenticator -----------------
class Authenticator {
private:
    UserStore* store;
    PasswordHasher* hasher;
    SessionManager* sessionManager;
public:
    Authenticator(UserStore* us, PasswordHasher* ph, SessionManager* sm)
        : store(us), hasher(ph), sessionManager(sm) {}

    bool login(const std::string& username, const std::string& password) {
        User* user = store->getUser(username);
        if (user && user->hashedPassword == hasher->hash(password)) {
            sessionManager->createSession(username);
            return true;
        }
        return false;
    }

    void logout(const std::string& username) {
        sessionManager->destroySession(username);
    }
};
int main() {
    InMemoryUserStore store;
    SimpleHasher hasher;
    SessionManager sessions;
    Authenticator auth(&store, &hasher, &sessions);

    // Register user
    std::string username = "alice";
    std::string password = "password123";
    store.addUser(User(username, hasher.hash(password)));

    // Login attempt
    if (auth.login(username, password)) {
        std::cout << "Login successful.\n";
    } else {
        std::cout << "Login failed.\n";
    }

    auth.logout(username);
}
