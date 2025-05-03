#include "tour_guide.h"

void tour_guide::input_toured_track_and_tour(std::istream& is) {
    const int NUM_DIRECTION = 8;
    const coordinate DIRECTION[NUM_DIRECTION] = {
        {.x = -1, .y =  2},
        {.x =  1, .y =  2},
        {.x =  2, .y =  1},
        {.x =  2, .y = -1},
        {.x =  1, .y = -2},
        {.x = -1, .y = -2},
        {.x = -2, .y = -1},
        {.x = -2, .y =  1}
    };
    bool** tour_map = new bool*[this->TOUR_MAP_SIZE];
    int i;
    for (i = 0; i < this->TOUR_MAP_SIZE; i++) {
        tour_map[i] = new bool[this->TOUR_MAP_SIZE] {0};
    }
    int num_step;
    step current_step;
    coordinate next_coordinate;
    is >> num_step >> current_step.position.x >> current_step.position.y;
    tour_map[current_step.position.x][current_step.position.y] = 1;
    int j;
    for (i = 1; i < num_step; i++) {
        is >> next_coordinate.x >> next_coordinate.y;
        tour_map[next_coordinate.x][next_coordinate.y] = 1;
        for (j = 0; j < NUM_DIRECTION; j++) {
            if (
                (next_coordinate.x - current_step.position.x == DIRECTION[j].x) &&
                (next_coordinate.y - current_step.position.y == DIRECTION[j].y)
            ) {
                current_step.move_way = j;
                this->tour_track.push(current_step);
                current_step.position = next_coordinate;
                break;
            }
        }
    }

    int from_way = 0;
    for (; i < this->TOUR_MAP_SIZE * this->TOUR_MAP_SIZE;) {
        for (j = from_way; j < NUM_DIRECTION; j++) {
            next_coordinate.x = current_step.position.x + DIRECTION[j].x;
            next_coordinate.y = current_step.position.y + DIRECTION[j].y;
            if (
                (next_coordinate.x >= 0) && (next_coordinate.x < this->TOUR_MAP_SIZE) &&
                (next_coordinate.y >= 0) && (next_coordinate.y < this->TOUR_MAP_SIZE) &&
                (tour_map[next_coordinate.x][next_coordinate.y] == 0)
            ) {
                current_step.move_way = j;
                this->tour_track.push(current_step);
                current_step.position = next_coordinate;
                tour_map[current_step.position.x][current_step.position.y] = 1;
                from_way = 0;
                i++;
                break;
            }
        }
        if (this->tour_track.empty()) {
            break;
        }
        else if (j == NUM_DIRECTION) {
            tour_map[current_step.position.x][current_step.position.y] = 0;
            current_step = this->tour_track.top();
            this->tour_track.pop();
            from_way = current_step.move_way + 1;
            i--;
        }
    }
    current_step.move_way = -1;
    this->tour_track.push(current_step);
    for (i = 0; i < this->TOUR_MAP_SIZE; i++) {
        delete [] tour_map[i];
    }
    delete [] tour_map;
}

void tour_guide::output_tour_track(std::ostream& os) const {
    std::stack<step> temp_stack_a = this->tour_track, temp_stack_b;
    while (!(temp_stack_a.empty())) {
        temp_stack_b.push(temp_stack_a.top());
        temp_stack_a.pop();
    }
    while (!(temp_stack_b.empty())) {
        os << temp_stack_b.top().position.x << " " << temp_stack_b.top().position.y << std::endl;
        temp_stack_b.pop();
    }
}

tour_guide::tour_guide(): TOUR_MAP_SIZE(5) {}

tour_guide::~tour_guide() {
    while (!this->tour_track.empty()) {
        this->tour_track.pop();
    }
}
