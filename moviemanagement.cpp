#include <bits/stdc++.h>
using namespace std;

class Movie {
public:
    int id;
    string name;
    string time;
    int quantity;

    Movie() : id(0), name(""), time(""), quantity(0) {} // <--- Add this
    Movie(int id, string name, string time, int quantity)
        : id(id), name(name), time(time), quantity(quantity) {}
};

class Admin {
public:
    int id;
    string name;
    unordered_map<int, Movie> ongoing;

    Admin(int id, string name) : id(id), name(name) {}

    void addMovie(Movie &m) {
        ongoing[m.id] = m;
        cout << "Movie Added: " << m.name << "\n";
    }

    void removeMovie(Movie &m) {
        if (ongoing.count(m.id) == 0) {
            cout << "Movie Doesn't Exist\n";
        } else {
            ongoing.erase(m.id);
            cout << "Movie Removed: " << m.name << "\n";
        }
    }

    void showMovies() {
        cout << "Ongoing Movies:\n";
        for (auto it : ongoing) {
            Movie m=it.second;
            int id=it.first;
            cout << "ID: " << m.id << " | " << m.name << " | Time: " << m.time << " | Tickets: " << m.quantity << "\n";
        }
    }
};

class User {
public:
    int id;
    string name;
    unordered_map<int, int> bookings; // movieID -> quantity

    User(int id, string name) : id(id), name(name) {}

    void bookTicket(Admin &admin, int movieId, int qty) {
        if (admin.ongoing.count(movieId) == 0) {
            cout << "Movie not found.\n";
            return;
        }

        Movie &m = admin.ongoing[movieId];
        if (m.quantity < qty) {
            cout << "Not enough tickets available.\n";
            return;
        }

        m.quantity -= qty;
        bookings[movieId] += qty;
        cout << "Booked " << qty << " tickets for " << m.name << "\n";
    }

    void cancelTicket(Admin &admin, int movieId, int qty) {
        if (bookings.count(movieId) == 0 || bookings[movieId] < qty) {
            cout << "You don't have that many tickets to cancel.\n";
            return;
        }

        bookings[movieId] -= qty;
        admin.ongoing[movieId].quantity += qty;
        cout << "Cancelled " << qty << " tickets for " << admin.ongoing[movieId].name << "\n";
    }

    void viewBookings(Admin &admin) {
        cout << "Your Bookings:\n";
        for (auto it : bookings) {
            int qty=it.second;
            int movieId=it.first;
            if (qty > 0 && admin.ongoing.count(movieId)) {
                Movie &m = admin.ongoing[movieId];
                cout << m.name << " (" << qty << " tickets)\n";
            }
        }
    }
};

int main() {
    Admin admin(1, "Admin");

    // Create Movies
    Movie m1(101, "Inception", "18:30", 100);
    Movie m2(102, "Interstellar", "20:00", 50);

    admin.addMovie(m1);
    admin.addMovie(m2);

    cout << "\n--- Movies Available ---\n";
    admin.showMovies();

    User user(1, "Alice");
    user.bookTicket(admin, 101, 2);     // Book 2 tickets
    user.bookTicket(admin, 102, 1);     // Book 1 ticket
    user.viewBookings(admin);

    cout << "\n--- After Booking ---\n";
    admin.showMovies();

    user.cancelTicket(admin, 101, 1);   // Cancel 1 ticket
    cout << "\n--- After Cancellation ---\n";
    admin.showMovies();
    user.viewBookings(admin);

    return 0;
}
