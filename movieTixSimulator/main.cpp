/*
 * Annabelle Tamano
 * CSC 5 - 49300
 * Last modified date: 21-10-2020
 * Problem statement: This program allows a user to buy a movie ticket,
 * picking the movie, the auditorium, the time of viewing, and seat number.
 * Price is calculated, and a ticket summary will be printed at the end of
 * the program.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

// function prototypes
void printMovieDescription(int);
void chooseTime(int, bool&, bool&, bool&, bool&, bool&, string&);
void pickSeat(bool, bool, bool, char&, int&);
void calculatePrice(bool, bool, bool, bool, bool, int, float&);
void printTicket(string, string, char, int, float, bool, bool, bool);
 
int main()
{
    // variables 
    int movieChoice,        // holds numeric equivalent of movie choice from menu
            seatNum,        // holds seat number
            age;            // holds users age
    float totalPrice;       // holds price of ticket
    bool validOption,       // indicates whether movie choice from menu is valid
            isMatinee = false,      // indicates whether ticket is matinee ticket
            isEarlyBird = false,    // indicates whether ticket is early bird ticket
            is3D = false,   // indicates movie is in 3D auditorium
            isEPEX = false, // indicates movie is in EPEX auditorium
            isEPEX3D = false;   // indicates movie is in EPEX 3D auditorium
    char seatRow,           // holds seat row letter
            confirmWatch;   // holds char of whether user wants to watch movie ('y' or 'n')
    string movieTitle,      // holds title of movie watched
            time;           // holds string time
            
    
    // display welcome statement & menu of movie options
    cout << "WELCOME TO THE CS THEATRES!\n"
            << "Here are the movies we have playing today: \n"
            << "1. Tenet PG13\n"
            << "2. Unhinged R\n"
            << "3. Train to Busan Presents: Peninsula NR | 3D | EPEX | EPEX 3D\n"
            << "4. The New Mutants PG13 | 3D | EPEX | EPEX 3D\n"
            << "5. Infidel R\n"
            << "6. Ava R\n"
            << "7. Hocus Pocus PG | 3D | EPEX | EPEX 3D\n"
            << "8. Coco PG | 3D\n"
            << "9. The War with Grandpa PG\n"
            << "10. Kajillionaire R\n\n";
    
    do 
    {
        // ask user for their movie choice
        cout << "Enter the number of the movie you are interested in watching (1-10).\n"
                << "To exit, enter -1: ";
        cin >> movieChoice;
        cout << endl;
        
        // observe initial validity of movie choice & print description if applicable
        switch ( movieChoice )
        {
            case 1:
            case 2:
            case 3: 
            case 4: 
            case 5: 
            case 6:
            case 7:
            case 8:
            case 9: 
            case 10:    printMovieDescription(movieChoice);
                        break;
            case -1:    validOption = true; // break while loop
                        break;
            default:    cout << "That is not a valid option. Choose again.\n";
                        validOption = false;
        }
        
        // further observe validity of movie choice by confirming that 
        // user is of age and would definitely like to watch the movie chosen
        if( movieChoice >= 1 && movieChoice <= 10 )
        {
            // ask user to confirm watching movie
            do
            {
                cout << "Are you sure you would like to watch this movie? ('y' or 'n'): ";
                cin >> confirmWatch;
                
                switch (confirmWatch)
                {
                    case 'y':
                    case 'Y':   cout << "Enter to confirm your age: ";
                                cin >> age;
                                
                                // input validation -- make sure age is an appropriate range
                                while ( !( age >= 0 && age <= 125 ))
                                {
                                    cout << "Please re-enter an appropriate age: ";
                                    cin >> age;
                                }
                                
                                // confirm age for R rated movies
                                if ( movieChoice == 2 || movieChoice == 5
                                        || movieChoice == 6 || movieChoice == 10 )
                                {
                                    if ( age < 17 )
                                    {
                                        cout << "Sorry. You are not of age to watch this movie.\n\n";
                                        validOption = false;
                                    }
                                    else
                                        validOption = true;
                                }
                                
                                // confirm age for PG13 movies
                                else if ( movieChoice == 1 || movieChoice == 4 )
                                {
                                    if ( age < 13)
                                    {
                                        cout << "Sorry. You are not of age to watch this movie.\n\n";
                                        validOption = false;
                                    }
                                    else
                                        validOption = true;
                                }
                                
                                // confirm age for PG and NR movies
                                else
                                    validOption = true;
                                break;             
                    case 'n':
                    case 'N':   validOption = false;
                                cout << endl;
                                break;
                    default:    cout << "Sorry. I did not quite catch what you were saying.\n";
                }
                
            }
            while( !(confirmWatch == 'y' || confirmWatch == 'Y' || confirmWatch == 'n' || confirmWatch == 'N') );
        }
    }
    while ( validOption != true );
    
    // if user decides to exit without picking movie, print goodbye message
    if ( movieChoice == -1 )
        cout << "Thank you for stopping by. Goodbye.";
    
    // execute rest of program, otherwise
    else
    {
        // assign movieTitle
        switch ( movieChoice )
        {
            case 1: movieTitle = "Tenet PG13";
                    break;
            case 2: movieTitle = "Unhinged R";
                    break;
            case 3: movieTitle = "Train to Busan Presents: Peninsula NR";
                    break;
            case 4: movieTitle = "The New Mutants PG13";
                    break;
            case 5: movieTitle = "Infidel R";
                    break;
            case 6: movieTitle = "Ava R";
                    break;
            case 7: movieTitle = "Hocus Pocus PG";
                    break;
            case 8: movieTitle = "Coco PG";
                    break;
            case 9: movieTitle = "The War with Grandpa PG";
                    break;
            case 10: movieTitle = "Kajillionaire R";
        }
        
        cout << endl;
        
        // call chooseTime function
        chooseTime( movieChoice, isEarlyBird, isMatinee, is3D, isEPEX,isEPEX3D, time );
        cout << endl;
        
        // call pickSeat function
        pickSeat ( is3D, isEPEX, isEPEX3D, seatRow, seatNum );
        cout << endl;
        
        // call calculatePrice function
        calculatePrice( isEarlyBird, isMatinee, is3D, isEPEX, isEPEX3D, age, totalPrice );
        cout << endl;
        
        // call printTicket function
        printTicket( movieTitle, time, seatRow, seatNum, totalPrice, is3D, isEPEX, isEPEX3D );
        
        // print summary 
        cout << setprecision(2) << fixed << showpoint;
        cout << "Your ticket for " << movieTitle << " at " << time << " costs $" << totalPrice <<".\n";
        cout << "You can your ticket in the file \"ticket.txt\"!\n";
        cout << "Enjoy the your experience at CS Theatres!";
    }
    return 0; 
}

// ***********************************************************************
// printMovieDescription
//
// task:    This program takes the movie choice chosen from the menu and 
//          prints a description of the movie chosen
// data in: movieChoice
// data out: none
//
// ***********************************************************************
void printMovieDescription(int movieChoice)
{
    if ( movieChoice == 1 )
    {
        cout << "Tenet PG13\n\n"
                << "Genre:      Action/Adventure\n"
                << "Director:   Christopher Nolan\n"
                << "Starring:   John David Washington, Robert Patterson, Elizabeth Debicki,\n"
                << "\t    Dimple Kapadia, Aaron Taylor-Johnson, Clemence Poesy, \n"
                << "\t    Himesh Patel, Michael Caine, Kenneth Branagh\n"
                << "Distributor:Warner Bros.\n"
                << "Synopsis:   Armed with only one word -Tenet- and fighting for the survival of\n"
                << "\t    the entire world, the Protagonist journeys through a twilight\n"
                << "\t    world of international espionage on a mission that will unfold in\n"
                << "\t    something beyond real time. Not time travel - Inversion.\n\n";
    }
    
    else if ( movieChoice == 2 )
    {
        cout << "Unhinged R\n\n"
                << "Genre:      Action, Thriller\n"
                << "Director:   Derrick Borte\n"
                << "Starring:   Russell Crowe, Caren Pistorius, Gabriel Bateman, Jimmi Simpson\n"
                << "\t    Lucy Faust\n"
                << "Distributor:Solstice Studios\n"
                << "Synopsis:   Unhinged takes an ordinary, everyday incident to its most terrifying\n"
                << "\t    conclusion in telling the story of a mother who leans on her horn at the\n"
                << "\t    wrong time, to the wrong guy. \"Road rage\" doesn't begin to describe what\n"
                << "\t    he's about to do to her and everyone she knows.\n\n";
    }
    
    else if ( movieChoice == 3 )
    {
        cout << "Train to Busan Presents: Peninsula NR\n\n"
                << "Genre:      Action, Horror, Thriller\n"
                << "Director:   Sang-ho Yeon\n"
                << "Starring:   Dong-Won Gang, Jung-hyn Lee, Re Lee, Hae-hyo Kwon\n"
                << "\t    Min-Jae Kim, Gyo-hwan Koo, Do-Yoon Kim, Ye-Won Lee\n"
                << "Distributor:Next Entertainment World\n"
                << "Synopsis:   Peninsula takes place four years after the zombie outbreak in\n"
                << "\t    Train to Busan. The Korean peninsula is devastated and Jung Seok,\n"
                << "\t    a former soldier who has managed to escape overseas, is\n"
                << "\t    given a mission to go back and unexpectedly meet survivors.\n\n";
    }
    
    else if ( movieChoice == 4 )
    {
        cout << "The New Mutants PG13\n\n"
                << "Genre:      Action/Adventure, SciFi/Fantasy, Horror, Suspense/Thriller\n"
                << "Director:   Josh Boone\n"
                << "Starring:   Anya Taylor-Joy, Maisie Williams, Charlie Heaton,\n"
                << "\t    Henry Zaga, Blu Hunt\n"
                << "Distributor:20th Century Fox\n"
                << "Synopsis:   Twentieth Century Fox in association with Marvel Entertainment\n"
                << "\t    presents \"The New Mutants,\" an original horror thriller set in an\n"
                << "\t    isolated hospital where a group of young mutants is being held for\n"
                << "\t    psychiatric monitoring. When strange occurences begin to take place,\n"
                << "\t    both their new mutant abilities and their friendships will be tested\n"
                << "\t    as they battle to try and make it out alive.\n\n";
    }
    
    else if ( movieChoice == 5 )
    {
        cout << "Infidel R\n\n"
                << "Genre:      Action/Adventure, Suspense/Thriller\n"
                << "Director:   Cyrus Nowrasteh\n"
                << "Starring:   Jim Caviezel, Claudia Karvan, Hal Ozsan, Stelio Savante, Aly Kassem\n"
                << "Distributor:Cloudburst Entertainment\n"
                << "Synopsis:   Infidel is a contemporary political thriller set in the Middle \n"
                << "\t    East and filled with suspense and intrigue, inspired by true events, and\n"
                << "\t    ripped from today's headlines. Jim Caviezel (The Passion of Christ, \n"
                << "\t    Person of Interest, Deja Vu) plays an American journalist/blogger who is\n"
                << "\t    kidnapped while attending a conference in the Middle East. Taken Hostage\n"
                << "\t    by the Iranian regime, he is put on trial for trumped-up charges of espionage.\n"
                << "\t    His wife, who works for the State Department, quickly realizes that the American\n"
                << "\t    government can do nothing. Feeling desperate and alone, she goes to Iran to \n"
                << "\t    try to free him herself. This exciting story sheds light on the plight of \n"
                << "\t    Americans currently held captive in Iran, about whom the world has forgotten.\n\n";
    }
    
    else if ( movieChoice == 6 )
    {
        cout << "Ava R\n\n"
                << "Genre:      Action/Adventure, Drama\n"
                << "Director:   Tate Taylor\n"
                << "Starring:   Jessica Chastain, Colin Farrell, Geena Davis, John Malkovich,\n"
                << "\t    Diana Silvers, Ioan Gruffudd, Common\n"
                << "Distributor:Vertical Entertainment\n"
                << "Synopsis:   Ava (Jessica Chastain) is a deadly mercenary who works for a black ops\n"
                << "\t    organization, traveling the globe and specializing in high profile hits. Ava's\n"
                << "\t    career takes a bad turn when a high profile job goes wrong due to faulty information\n"
                << "\t    provided to her. With a botched hit (as well as a track record for questioning the\n"
                << "\t    validity of her targets), Ava is told to take a hiatus until the heat blows over, but\n"
                << "\t    secretly the head of the organization, Simon (Colin Farrell), has ordered a hit on her\n"
                << "\t    to ensure nothing traces back to the company. With the recent death of her father, Ava\n"
                << "\t    decides to go back home to Boston and attempt to mend her relationship with her mother and\n"
                << "\t    sister, Judy, though the homecoming proves to be far from happy as the years of \n"
                << "\t    estrangement have created resentment. To complicate things further Ava's ex-fiance, \n"
                << "\t    Michael (Common), is now in a relationship with Judy, and involved with an underground\n"
                << "\t    gambling ring that Ava knows all too well from her younger days. Ava now has to\n"
                << "\t    save her family and herself from multiple threats, while battling her own demons.\n\n";
    }
    
    else if ( movieChoice == 7 )
    {
        cout << "Hocus Pocus PG\n\n"
                << "Genre:      Comedy, Family, SciFi/Fantasy\n"
                << "Director:   Kenny Ortega\n"
                << "Starring:   Bette Midler, Jessica Parker, Kathy Nahimy, Omri Katz, Thora Birch,\n"
                << "\t    Vinessa Shaw, Amanda Shepherd, Larry Bagby, Tobias Jelinek, Stephanie Farcy\n"
                << "Distributor:Walt Disney Pictures\n"
                << "Synopsis:   During a Halloween in Salem, Mass., three witches are accidentally reincarnated\n"
                << "\t    as a young boy who tries to impress the girl of his dreams.\n\n";
    }
    
    else if ( movieChoice == 8  )
    {
        cout << "Coco PG\n\n"
                << "Genre:      Animation, Comedy\n"
                << "Director:   Lee Unkrich, Adrian Molina\n"
                << "Starring:   Gael Garcia Bernal, Anthony Gonzalez, Benjamin Bratt,Renee Victor, \n"
                << "\t    Jaime Camil, Renee Victor\n"
                << "Distributors: Walt Disney Pictures, Walt Disneyy Pictures/PIXA\n"
                << "Synopsis:   Despite his family's baffling generations-old ban on music, Miguel\n"
                << "\t    (voice of newcomer Anthony Gonzalez) dreams of becoming an accomplished\n"
                << "\t    musician like his idol, Ernesto de la Cruz (voice of Benjamin Bratt).\n"
                << "\t    Desperate to prove his talent, Miguel finds himself in the stunning and\n"
                << "\t    colorful Land of the Dead following a mysterious chain of events.\n"
                << "\t    Along the way, he meets charming trickster Hector (voice of Gael Garcia Bernal),\n"
                << "\t    and together, they set off an extraordinary journey to unlock the\n"
                << "\t    real story behind Miguel's family story.\n\n";
    }
    
    else if ( movieChoice == 9 )
    {
        cout << "The War with Grandpa PG\n\n"
                << "Genre:      Comedy, Family\n"
                << "Director:   Tim Hill\n"
                << "Starring:   Robert De Niro, Uma Thurman, Rob Riggle, Oakes Fegley, Jane Seymour,\n"
                << "\t    Laura Marano, Cheech Marin, Christopher Walken\n"
                << "Distributors: The Weinstein Company, Dimension Films, 101 Studios\n"
                << "Synopsis:   Sixth-grader Peter (Oakes Fegley) is pretty much your average kid- he\n"
                << "\t    likes gaming, hanging with his friends and his beloved pair of Air Jordans.\n"
                << "\t    But when his recently widowed grandfather Ed (Robert De Niro) moves\n"
                << "\t    in with Peter's family, the boy is forced to give up his most prized\n"
                << "\t    possession of all, his bedroom. Unwilling to let such an injustice stand,\n"
                << "\t    Peter devises a series of increasingly elaborate pranks to drive out \n"
                << "\t    the interloper, but Grandpa Ed won't go without a fight. Soon, the\n"
                << "\t    friendly combatants are engaged in an all-out war with side-splitting\n"
                << "\t    consequences.\n\n";
    }
    
    else
    {
        cout << "Kajillionaire R\n\n"
                << "Genre:      Crime, Drama\n"
                << "Director:   Miranda July\n"
                << "Starring:   Evan Rachel Wood, Gina Rodriguez, Debra Winger, Mark Ivanir, \n"
                << "\t    Richard Jenkins, Diana Maria Riva, Patricia Belcher\n"
                << "Distributor:Focus Features\n"
                << "Synopsis:   A woman's life is turned upside down when her criminal parents invite\n"
                << "\t    an outsider to join them on a major heist they're planning.\n\n";
    }
}   

// ***********************************************************************
// chooseTime
//
// task:    This function takes the movieChoice, and allows you to choose 
//          the time to watch it
// data in: movieChoice
// data out: time, isEarlyBird, isMatinee, is3D, isEPEX, and isEPEX3D
//
// ***********************************************************************
void chooseTime( int movie, bool& isEarlyBird, bool& isMatinee, bool& is3D,
        bool& isEPEX, bool& isEPEX3D, string& time)
{
    int timeOption; // holds timeOption used for time menus
    int auditoriumOption;   //holds auditorium option used for auditorium menus
    
    // the theater offers 3D, EPEX, and EPEX 3D for the following movies: 
    // Train to Busan Presents: Peninsula NR
    // Hocus Pocus
    // The New Mutants
    if ( movie == 3 || movie == 4 || movie == 7 )
    {
        cout << "Here are the viewing options available for this movie: \n";
        cout << "1. 3D  2. EPEX  3. EPEX 3D  4. Regular\n\n";
        
        do
        {
            cout << "Enter which experience you would like to have (1-4): ";
            cin >> auditoriumOption;
        
            switch( auditoriumOption )
            {
                case 1:     is3D = true;
                            break;
                case 2:     isEPEX = true;
                            break;
                case 3:     isEPEX3D = true;
                            break;
                case 4:     break;
                default:    cout << "This is not a valid option!\n";
                
            }
        }
        while ( !( auditoriumOption >= 1 && auditoriumOption <= 4 ));
    }
    
    // The theater offers 3D as an option for Coco PG
    else if ( movie == 8 )
    {
        cout << "Here are the viewing options available for this movie: \n";
        cout << "1. 3D  2. Regular\n\n";
        
         do
        {
            cout << "Enter which experience you would like to have (1 or 2): ";
            cin >> auditoriumOption;
            
            switch ( auditoriumOption )
            {
                case 1:     is3D = true;
                            break;
                case 2:     break;
                default:    cout << "This is a valid option!\n";
            }
        }
        while ( !( auditoriumOption == 1 || auditoriumOption == 2 ));
    }
    
    // time option for 3D movies
    if ( is3D == true )
    {
        cout << "Here are the time options for this movie in 3D: \n";
        cout << "1. 10:00AM\n2. 12:00PM\n3. 3:00PM\n4.7:00PM\n\n";
        
        do
        {
            cout << "Choose your desired time of viewing (1-4): ";
            cin >> timeOption;
            
            // input validation & check if the time fall into Early Bird or Matinee price 
            switch( timeOption )
            {
                case 1:     isEarlyBird = true;
                            break;
                case 2: 
                case 3:     isMatinee = true;
                            break;
                case 4:     break;
                default:    cout << "That is not a valid option!\n";
                            
            }
        }
        while( !( timeOption >= 1 && timeOption <= 4 ) );
        
        // assign option to time variable
        switch( timeOption )
        {
            case 1: time = "10:00AM";
                    break;
            case 2: time = "12:00PM";
                    break;
            case 3: time = "3:00PM";
                    break;
            case 4: time = "7:00PM";
                    break;
        }
    }
    
    // time option for EPEX movies
    else if ( isEPEX == true )
    {
        cout << "Here are the time options for this movie in the EPEX auditorium: \n";
        cout << "1. 11:00AM\n2. 1:00PM\n3. 4:00PM\n4.9:00PM\n\n";
        
        do
        {
            cout << "Choose your desired time of viewing (1-4): ";
            cin >> timeOption;
            
            // input validation & check if the time fall into Early Bird or Matinee price 
            switch( timeOption )
            {
                case 1:     isEarlyBird = true;
                            break;
                case 2: 
                case 3:     isMatinee = true;
                            break;
                case 4:     break;
                default:    cout << "That is not a valid option!\n";
                            
            }
        }
        while( !( timeOption >= 1 && timeOption <= 4 ) );
        
        // assign option to time variable
        switch( timeOption )
        {
            case 1: time = "11:00AM";
                    break;
            case 2: time = "1:00PM";
                    break;
            case 3: time = "4:00PM";
                    break;
            case 4: time = "9:00PM";
                    break;
        }
    }
    
    // time option for EPEX 3D movies
    else if ( isEPEX3D == true )
    {
        cout << "Here are the time options for this movie in the EPEX 3D auditorium: \n";
        cout << "1. 12:00PM\n2. 5:00PM\n3. 10:00PM\n";
        
        do
        {
            cout << "Choose your desired time of viewing (1-3): ";
            cin >> timeOption;
            
            // input validation & check if the time fall into Early Bird or Matinee price 
            switch( timeOption )
            {
                case 1:    
                case 2:     isMatinee = true;
                            break;
                case 3:     break;
                default:    cout << "That is not a valid option!\n";
                            
            }
        }
        while( !( timeOption >= 1 && timeOption <= 3 ) );
        
        // assign option to time variable
        switch( timeOption )
        {
            case 1: time = "12:00PM";
                    break;
            case 2: time = "5:00PM";
                    break;
            case 3: time = "10:00PM";
                    break;
        }
    }
    
    // time option for regular movies
    else
    {
        cout << "Here are the time options for this movie in the regular auditorium: \n";
        cout << "1. 8:00AM\n2. 11:00AM\n3. 2:00PM\n4. 4:00PM\n5. 5:00PM\n6. 8:00PM\n7. 11:00PM\n";
        
        do
        {
            cout << "Choose your desired time of viewing (1-7): ";
            cin >> timeOption;
            
            // input validation & check if the time fall into Early Bird or Matinee price 
            switch( timeOption )
            {
                case 1:    
                case 2:     isEarlyBird = true;
                            break;
                case 3:
                case 4:
                case 5:     isMatinee = true;
                            break;
                case 6:
                case 7:     break;
                default:    cout << "That is not a valid option!\n";
                            
            }
        }
        while( !( timeOption >= 1 && timeOption <= 7 ) );
        
        // assign option to time variable
        switch( timeOption )
        {
            case 1: time = "8:00AM";
                    break;
            case 2: time = "11:00AM";
                    break;
            case 3: time = "2:00PM";
                    break;
            case 4: time = "4:00PM";
                    break;
            case 5: time = "5:00PM";
                    break;
            case 6: time = "8:00PM";
                    break;
            case 7: time = "11:00PM";
                    break;
        }
    }
}

// ***********************************************************************
// pickSeat
//
// task:    This function asks the user for their preferred row and  
//          seat number
// data in: is3D, isEPEX, and isEPEX3D
// data out: seatRow and seatNum
//
// ***********************************************************************
void pickSeat ( bool is3D, bool isEPEX, bool isEPEX3D, char& row, int& seatNum )
{
    char rowPrint;  
    int seatsInRow;     
    
    cout << "Here is a diagram of the seating arrangement in the auditorium: \n";
    
    // options for 3D and EPEX auditoriums
    if ( is3D == true || isEPEX == true )
    {
        rowPrint = 72;  // start rows at H and is used to help print diagram
        seatsInRow = 16;
        
        // use nested for loop to create diagram for 3D and EPEX auditoriums
        for ( int row = 0; row < 8; row++ )
        {
            cout << setw(4) << rowPrint;
            
            for ( int seat = 1; seat <= seatsInRow; seat++)
                cout << setw(4) << seat;
            
            rowPrint--;
            cout << endl;
        }
        
        cout << endl;
        
        // ask user for row 
        cout << "Out of rows A-H, choose which row you would like to sit in: ";
        cin >> row;
        
        // input validation-- within range of available rows
        while ( !( toupper(row) >= 'A' && toupper(row) <= 'H' ) )
        {
            cout << "That is not a valid row. Please enter a valid option: ";
            cin >> row;
        }
    }
    
    // options for EPEX 3D auditoriums
    else if ( isEPEX3D == true )
    {
        rowPrint = 74;  // start rows at J and is used to help print diagram
        seatsInRow = 20; // 20 seats in each row
        
        // use nested for loop to create diagram for EPEX 3D auditoriums
        for ( int row = 0; row < 10; row++ )
        {
            cout << setw(4) << rowPrint;
            
            for ( int seat = 1; seat <= seatsInRow; seat++)
                cout << setw(4) << seat;
            
            rowPrint--;
            cout << endl;
        }
        
        cout << endl;
        
        // ask user for row 
        cout << "Out of rows A-J, choose which row you would like to sit in: ";
        cin >> row;
        
        // input validation-- within range of available rows
        while ( !( toupper(row) >= 'A' && toupper(row) <= 'J' ) )
        {
            cout << "That is not a valid row. Please enter a valid option: ";
            cin >> row;
        }
    }
    
    // diagram for regular auditorium
    else
    {
        rowPrint = 70;  // start rows at F and is used to help print diagram
        seatsInRow = 12;    // 12 seats in each row
        
        // use nested for loops to create diagram for regular auditorium
        for ( int row = 0; row < 6; row++ )
        {
            cout << setw(4) << rowPrint;
            
            for ( int seat = 1; seat <= seatsInRow; seat++)
                cout << setw(4) << seat;
            
            rowPrint--;
            cout << endl;
        }
        
        cout << endl;
        
        // ask user for row 
        cout << "Out of rows A-F, choose which row you would like to sit in: ";
        cin >> row;
        
        // input validation -- within range of available rows
        while ( !( toupper(row) >= 'A' && toupper(row) <= 'F' ) )
        {
            cout << "That is not a valid row. Please enter a valid option: ";
            cin >> row;
        }
    }
    
    cout << endl;
    
    // ask for seat number
    cout << "Choose which seat number you would like to sit in (1-" << seatsInRow << "): ";
    cin >> seatNum;
    
    // input validation
    while ( !( seatNum >= 1 && seatNum <= seatsInRow) )
    {
        cout << "That is not a valid seat number. Please enter a valid option: ";
        cin >> seatNum;
    }
}

// ***********************************************************************
// calculatePrice
//
// task:    This function sends the price of the function observing whether
//          the ticket is during early bird or matinee times, whether the 
//          user is a child, veteran, or senior, and whether the auditorium chosen 
//          3D, EPEX, or EPEX 3D to calculate price.
//          
// data in: isEarlyBird, isMatinee, is3D, isEPEX, isEPEX3D, age
// data out: price
//
// ***********************************************************************
void calculatePrice( bool isEarlyBird, bool isMatinee, bool is3D, bool isEPEX, bool isEPEX3D, int age, float& price )
{
    char serviceDiscount;   // holds 'y' or 'n'
    
    // determine base price based on time of viewing
    if ( isEarlyBird == true )
        price = 5.00;
    else if ( isMatinee == true )
        price = 6.00;
    else
    {
        // determine price based on other discounts
        if (age >= 55)
            price = 5.00;   // senior discount
        if ( age <= 11)
            price = 6.00;   // children's discount
        else
        {
            // ask user if they are a student or part of the military/police/fire dept
            // to determine price on other discounts
            do
            {
                cout << "Are you a student or part of the military, police department, or fire department? ('y' or 'n'): ";
                cin >> serviceDiscount;
                
                switch ( serviceDiscount )
                {
                    case 'y':
                    case 'Y':   price = 9.00;   // student or service discount
                                break;
                    case 'n':
                    case 'N':   price = 12.00;  // regular adult price
                                break;
                    default:    cout << "Sorry. I didn't catch your answer.\n";
                }
            }
            while( !( serviceDiscount == 'y'|| serviceDiscount == 'Y'
                    || serviceDiscount == 'n' || serviceDiscount == 'N' ));        
        }
    }
    
    // determine additional add on price based on auditorium
    if ( is3D == true )
        price += 2.00;  // add $2 if 3D auditorium
    if ( isEPEX == true )   
        price += 1.00;  // add $1 if EPEX auditorium
    if ( isEPEX3D == true )
        price += 2.00;  // add $2 if EPEX auditorium
        
}

// ***********************************************************************
// printTicket
//
// task:    This function takes movieTitle, time, seatRow, seatNum, price,
//          and prints ticket in a new file "ticket.txt"
// data in: movieTitle, time, seatRow, seatNum, totalPrice, is3D, isEPEX, isEPEX3D
// data out: none
//
// ***********************************************************************
void printTicket( string movie, string time, char row, int seatNum, float price, 
        bool is3D, bool isEPEX, bool isEPEX3D )
{
    ofstream dataOut;
    
    // open file
    dataOut.open( "ticket.txt");
    dataOut << setprecision(2) << fixed << showpoint;
    
    dataOut << "--------------------------------------" << endl << endl;
    dataOut << "CS THEATRES - ADMIT ONE TICKET" << endl;
    dataOut << movie << endl << endl;
    
    if ( is3D == true )
        dataOut << "3D Auditorium";
    else if ( isEPEX == true )
        dataOut << "EPEX Auditorium";
    else if (isEPEX3D == true )
        dataOut << "EPEX 3D Auditorium";
    else
        dataOut << "Regular Auditorium";
    
    dataOut << "\tSeat: " << row << seatNum << endl;
    dataOut << "Time: " << time << "\tPrice: $" << price << endl << endl;
    dataOut << "--------------------------------------";
    
    // close file after use
    dataOut.close();
}