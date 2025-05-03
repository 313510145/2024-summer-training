#ifndef TOUR_GUIDE_H
#define TOUR_GUIDE_H

#include <iostream>
#include <stack>

struct coordinate {
    int x, y;
};

struct step {
    coordinate position;
    int move_way;
};

class tour_guide {
    public:
        void input_toured_track_and_tour(std::istream& is);
        void output_tour_track(std::ostream& os) const;
        tour_guide();
        ~tour_guide();
    private:
        const int TOUR_MAP_SIZE;
        std::stack<step> tour_track;
};

#endif  // TOUR_GUIDE_H
