/* 
    C++: 
        #include <iostream> 
*/
#include <stdio.h>
#include <stdlib.h>


// a point with integer coordinates
struct Point {
    /*
        C++: 
            int x, y;
    */
    // data
    int x, y;
};


// constructor
/* 
    C++:
        Point()
        {
            x = y = 0;
        }
*/
void Point_init(struct Point *p) {
    p -> x = 0;
    p -> y = 0;
    return;
}


// add point componentwise
/*
    C++:
        void add(const Point &p)
        {
            x += p.x;
            y += p.y;
        }
*/
void Point_add(struct Point *p1, struct Point *p2) {
    p1 -> x = (p1 -> x) + (p2 -> x);
    p1 -> y = (p1 -> y) + (p2 -> y);
    return;
}


// print to standard output
/*
    C++:
        void print() const
        {
            std::cout << "[" << x << "," << y << "]" << std::endl;
        }
*/
void Point_print(struct Point *p) {
    printf("[%d, %d]\n", p -> x, p -> y);
}


/*
    C++:
        int main()
        {
            const int N = 200;
            Point *A = new Point[N], sum;

            for (int i=0; i < N; ++i) {
                A[i].x = i; A[i].y = -i;
                sum.add(A[i]);
            }
            sum.print();
            delete [] A;

            return 0;
        }
*/
int main() {
    // declare a constant size for the array of Points
    const int N = 200;

    // allocate memory for an array of N Point objects
    struct Point *A = calloc(N, sizeof(struct Point));
    for (int i = 0; i < N; ++i) {
        // call constructor for each Point in the array
        Point_init(A + i);
    }

    struct Point sum; // initialize a new Point object named sum
    Point_init(&sum); // call constructor

    for (int i = 0; i < N; ++i) {
        (A + i) -> x = i; (A + i) -> y = -i;
        Point_add(&sum, A + i);
    }
    Point_print(&sum);
    free(A);

    return 0;
}