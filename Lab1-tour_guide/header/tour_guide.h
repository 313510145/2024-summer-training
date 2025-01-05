#ifndef TOUR_GUIDE_H
#define TOUR_GUIDE_H

#include <iostream>
#include <stack>

// Struct representing a coordinate with x and y values
struct coordinate {
    int x, y;
};

// Struct representing a step, which includes a coordinate and the move direction
struct step {
    coordinate position;  // Current position on the map
    int move_way;         // The direction of movement
};

// Class representing a tour guide which keeps track of a tour through a map
class tour_guide {
    public:
        // Method to input the toured track from a stream
        void input_toured_track_and_tour(std::istream& is);
        
        // Method to output the tour track to a stream
        void output_tour_track(std::ostream& os) const;
        
        // Constructor to initialize the tour guide with a map size
        tour_guide();
        
        // Destructor to clean up resources
        ~tour_guide();
    private:
        const int TOUR_MAP_SIZE;        // The size of the tour map
        std::stack<step> tour_track;    // Stack to store the steps of the tour
};

#endif  // TOUR_GUIDE_H
