#include "tour_guide.h"

// Method to input the toured track from an input stream
// Reads the number of steps and their positions, then builds the tour
void tour_guide::input_toured_track_and_tour(std::istream& is) {
    // Define 8 possible movement directions (like a knight's move in chess)
    const int NUM_DIRECTION = 8;
    const coordinate DIRECTION[NUM_DIRECTION] = {
        {.x = -1, .y =  2},  // Move 0
        {.x =  1, .y =  2},  // Move 1
        {.x =  2, .y =  1},  // Move 2
        {.x =  2, .y = -1},  // Move 3
        {.x =  1, .y = -2},  // Move 4
        {.x = -1, .y = -2},  // Move 5
        {.x = -2, .y = -1},  // Move 6
        {.x = -2, .y =  1}   // Move 7
    };

    // Create a 2D dynamic array to track visited positions
    bool** tour_map = new bool*[this->TOUR_MAP_SIZE];
    int i;
    for (i = 0; i < this->TOUR_MAP_SIZE; i++) {
        tour_map[i] = new bool[this->TOUR_MAP_SIZE] {0};  // Initialize all to false
    }

    int num_step;
    step current_step;
    coordinate next_coordinate;

    // Read the number of steps and the starting position
    is >> num_step >> current_step.position.x >> current_step.position.y;
    tour_map[current_step.position.x][current_step.position.y] = 1;  // Mark starting position as visited

    int j;
    for (i = 1; i < num_step; i++) {
        // Read the next step's coordinates
        is >> next_coordinate.x >> next_coordinate.y;
        tour_map[next_coordinate.x][next_coordinate.y] = 1;  // Mark visited position

        // Find the movement direction by comparing to the current position
        for (j = 0; j < NUM_DIRECTION; j++) {
            if (
                (next_coordinate.x - current_step.position.x == DIRECTION[j].x) &&
                (next_coordinate.y - current_step.position.y == DIRECTION[j].y)
            ) {
                current_step.move_way = j;  // Store the movement direction
                this->tour_track.push(current_step);  // Push the current step onto the stack
                current_step.position = next_coordinate;  // Update current position
                break;
            }
        }
    }

    int from_way = 0;  // Initialize the starting direction for future moves
    for (; i < this->TOUR_MAP_SIZE * this->TOUR_MAP_SIZE;) {
        // Try all possible directions to find the next unvisited position
        for (j = from_way; j < NUM_DIRECTION; j++) {
            next_coordinate.x = current_step.position.x + DIRECTION[j].x;
            next_coordinate.y = current_step.position.y + DIRECTION[j].y;

            // Check if the next position is within bounds and not yet visited
            if (
                (next_coordinate.x >= 0) && (next_coordinate.x < this->TOUR_MAP_SIZE) &&
                (next_coordinate.y >= 0) && (next_coordinate.y < this->TOUR_MAP_SIZE) &&
                (tour_map[next_coordinate.x][next_coordinate.y] == 0)
            ) {
                current_step.move_way = j;  // Store the direction of movement
                this->tour_track.push(current_step);  // Push the current step onto the stack
                current_step.position = next_coordinate;  // Update current position
                tour_map[current_step.position.x][current_step.position.y] = 1;  // Mark as visited
                from_way = 0;
                i++;
                break;
            }
        }

        // Backtrack if no valid moves are found
        if (this->tour_track.empty()) {
            break;
        }
        else if (j == NUM_DIRECTION) {
            tour_map[current_step.position.x][current_step.position.y] = 0;  // Unmark the current position
            current_step = this->tour_track.top();  // Get the last step
            this->tour_track.pop();  // Remove it from the stack
            from_way = current_step.move_way + 1;  // Try the next direction
            i--;
        }
    }

    // Mark the end of the tour with a special value (-1)
    current_step.move_way = -1;
    this->tour_track.push(current_step);

    // Clean up dynamically allocated memory
    for (i = 0; i < this->TOUR_MAP_SIZE; i++) {
        delete [] tour_map[i];
    }
    delete [] tour_map;
}

// Method to output the tour track to an output stream
// Outputs the x and y coordinates of the tour in order
void tour_guide::output_tour_track(std::ostream& os) const {
    std::stack<step> temp_stack_a = this->tour_track, temp_stack_b;

    // Reverse the stack to output in the correct order
    while (!(temp_stack_a.empty())) {
        temp_stack_b.push(temp_stack_a.top());
        temp_stack_a.pop();
    }

    // Output the x, y positions in sequence
    while (!(temp_stack_b.empty())) {
        os << temp_stack_b.top().position.x << " " << temp_stack_b.top().position.y << std::endl;
        temp_stack_b.pop();
    }
}

// Constructor initializes the map size
tour_guide::tour_guide(): TOUR_MAP_SIZE(5) {}

// Destructor clears the stack
tour_guide::~tour_guide() {
    while (!this->tour_track.empty()) {
        this->tour_track.pop();
    }
}
