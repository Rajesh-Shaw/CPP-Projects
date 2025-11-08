#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

class Movie
{
    private:
        int id;
        string name;
        string time;
        double price;
        int availableSeats;
    public:
        Movie(){}
        Movie(int i, string n, string t, double p, int s)
            : id(i), name(n), time(t), price(p), availableSeats(s){}
        
        void display()
        {
            cout << setw(5) << id << " | ";
            cout << setw(20) << name << " | ";
            cout << setw(10) << time << " | ";
            cout << "Rs." << setw(6) << price << " | ";
            cout << setw(3) << availableSeats << " Seats\n";
        }

        int getId(){ return id;}
        string getName(){ return name; }
        string getTime(){ return time;}
        double getPrice(){ return price;}
        int getSeats(){ return availableSeats;}

        void bookSeats(int n)
        { 
            availableSeats -= n;
        }
        void cancelSeats(int n)
        { 
            availableSeats += n;
        }

        string getDataString()
        {
            return to_string(id) + "," + name + "," + time + "," + 
                    to_string(price) + "," + to_string(availableSeats) + "\n";
        }

        void setData(int i, string n, string t, double p, int s)
        {
            id = i; 
            name = n; 
            time = t; 
            price = p; 
            availableSeats =s;
        }
};


class Booking
{
    private:
        int bookingId;
        string customerName;
        int movieId;
        int seatsBooked;
        double totalCost;
        bool isCancelled;
    
    public:
        Booking() : isCancelled(false){}
        Booking(int id, string cname, int mId, int s, double cost)
            : bookingId(id), customerName(cname), movieId(mId),
                seatsBooked(s), totalCost(cost), isCancelled(false){}
        
        void display()
        {
            cout << setw(5) << bookingId << " | "
                 << setw(15) << customerName << " | "
                 << setw(5) << movieId << " | "
                 << setw(5) << seatsBooked << " | "
                 << "Rs." << totalCost 
                 << (isCancelled ? " (Cancelled)" : "") << "\n";
        }

        int getBookingId(){ return bookingId;}
        int getMovieId(){ return movieId; }
        int getSeats(){ return seatsBooked; }

        bool getIsCancelled() { return isCancelled; }
        void cancel() { isCancelled = true; }


        string getDataString()
        {
            return to_string(bookingId) + "," + customerName + "," +
                   to_string(movieId) + "," + to_string(seatsBooked) + "," +
                   to_string(totalCost) + "," + (isCancelled ? "1" : "0") + "\n";
        }

        void setData(int id, string cname, int mId, int s, double cost, bool cancel = false)
        {
            bookingId = id;
            customerName = cname;
            movieId = mId;
            seatsBooked = s;
            totalCost = cost;
            isCancelled = cancel;
        }
};


class MovieSystem
{
    private:
        Movie movies[20];
        Booking bookings[50];
        int movieCount, bookingCount;
    
    public:
        MovieSystem()
        {
            movieCount = 0;
            bookingCount = 0;
            loadMovies();
            loadBookings();
        }

        void menu()
        {
            int choice;
            do{
                cout << "\n====================================\n";
                cout << "       MOVIE TICKET BOOKING SYSTEM\n";
                cout << "====================================\n";
                cout << "1. View Movies\n";
                cout << "2. Book Ticket\n";
                cout << "3. Cancel Booking\n";
                cout << "4. View All Bookings\n";
                cout << "5. Exit & Save\n";
                cout << "------------------------------------\n";

                cout << "Enter your choice: ";
                if(!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                switch(choice)
                {
                    case 1: viewMovies(); break;
                    case 2: bookTicket(); break;
                    case 3: cancelBooking(); break;
                    case 4: viewBookings(); break;
                    case 5: saveMovies();
                            saveBookings();
                            cout << "Data saved successfully. Goodbye!\n";
                            break;
                    default:
                            cout << "Invalid choice. Try again.\n";
                }

            }while(choice != 5);
        }

        void loadMovies()
        {
            ifstream in("movies.txt");
            if(!in)
            {
                cout << "No movie data found. Adding sample movies.\n";
                movies[movieCount++] = Movie(1, "Avengers: Endgame", "6:00 PM", 250, 50);
                movies[movieCount++] = Movie(2, "Inception", "8:00 PM", 200, 40);
                movies[movieCount++] = Movie(3, "Interstellar", "9:30 PM", 300, 30);
                saveMovies();
                return;
            }

            int id, seats;
            string name,time;
            double price;
            while(in >> id)
            {
                in.ignore();
                getline(in, name, ',');
                getline(in, time, ',');
                in >> price;
                in.ignore();
                in >> seats;
                in.ignore();
                movies[movieCount++].setData(id, name, time, price, seats);
            }
            in.close();
        }

        void loadBookings() 
        {
            ifstream in("bookings.txt");
            if (!in) 
                return;

            int id, movieId, seats;
            double cost;
            string name;

            while (in >> id) 
            {
                in.ignore();
                getline(in, name, ',');
                in >> movieId;
                in.ignore();
                in >> seats;
                in.ignore();
                in >> cost;
                in.ignore();
                bookings[bookingCount++].setData(id, name, movieId, seats, cost);
            }
            in.close();
        }


        void viewMovies() 
        {
            cout << "\n---------------------- MOVIES --------------------------\n";
            cout << " ID   | Movie Name           | Time       | Price  | Seats\n";
            cout << "---------------------------------------------------------\n";
            for (int i = 0; i < movieCount; i++)
                movies[i].display();
            cout << "---------------------------------------------------------\n";
        }



        void bookTicket() 
        {
            int movieId, seats;
            string name;

            viewMovies();
            cout << "Enter Movie ID: ";
            cin >> movieId;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter number of seats: ";
            cin >> seats;

            for (int i = 0; i < movieCount; i++) 
            {
                if (movies[i].getId() == movieId) 
                {
                    if (movies[i].getSeats() >= seats) 
                    {
                        double total = seats * movies[i].getPrice();
                        movies[i].bookSeats(seats);
                        bookings[bookingCount++] = Booking(bookingCount + 1, name, movieId, seats, total);
                        cout << "Booking successful! Total: Rs." << total << "\n";
                        return;
                    } 
                    else 
                    {
                        cout << "Not enough seats available.\n";
                        return;
                    }
                }
            }
            cout << "Invalid Movie ID.\n";
        }


        void cancelBooking() 
        {
            int id;
            cout << "Enter Booking ID to cancel: ";
            cin >> id;

            for (int i = 0; i < bookingCount; i++) 
            {
                if (bookings[i].getBookingId() == id) 
                {
                    int movieId = bookings[i].getMovieId();
                    int seats = bookings[i].getSeats();

                    for (int j = 0; j < movieCount; j++) 
                    {
                        if (movies[j].getId() == movieId) 
                        {
                            movies[j].cancelSeats(seats);
                            break;
                        }
                    }

                    for (int k = i; k < bookingCount - 1; k++)
                    {
                        bookings[k] = bookings[k + 1];
                    }
                    bookingCount--;

                    cout << "Booking cancelled and removed successfully.\n";
                    return;

                }
            }
            cout << "Booking not found.\n";
        }




        void viewBookings() 
        {
            cout << "\n---------------- BOOKINGS ---------------------\n";
            cout << " ID   | Customer Name    | M_ID | Seat | Cost\n";
            cout << "-------------------------------------------------\n";
            for (int i = 0; i < bookingCount; i++)
                bookings[i].display();
            cout << "------------------------------------------------\n";
        }

        void saveMovies() 
        {
            ofstream out("movies.txt");
            for (int i = 0; i < movieCount; i++)
                out << movies[i].getDataString();
            out.close();
        }

        void saveBookings() 
        {
            ofstream out("bookings.txt");
            for (int i = 0; i < bookingCount; i++)
                out << bookings[i].getDataString();
            out.close();
        }



};


int main()
{
    MovieSystem system;
    system.menu();
    return 0;
}