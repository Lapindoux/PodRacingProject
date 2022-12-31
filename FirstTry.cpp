#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Point
{
    public:
    double x,y;
    Point();
    Point(int x, int y);
    double distance( const Point &P);
    Point closest( const Point &A,const Point &B);
    void printPoint();
};
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
};
Point::Point()
{
    this->x = 0;
    this->y = 0;
};
double Point::distance(const Point &P)
{
    return sqrt(pow(this->x - P.x,2)+pow(this->y - P.y,2));
};
Point Point::closest(const Point &A, const Point &B)
{
    double distance_a = distance(A);
    double distance_b = distance(B);
    if (distance_a <= distance_b){
        return A;
    }
    return B;
};


class Unit :public Point
{
    public: 
    int id;
    float r;
    float vx;
    float vy;

    // Collision collision(Unit u);
    //void bounce(Unit u);
    Unit();
    Unit(Point p, int id , float r, float vx, float vy);
    Unit(int x, int y, int id, float r, float vx, float vy);


};

/*
void Unit::bounce(Unit u)
{

};
*/

class Pod : public Unit
{
    public: 
    float angle;
    int nextcheckpoint_id;
    int checked;
    int timeout;
    Pod *partner;
    bool shield;
    
    Pod();
    float getAngle(const Point &P);
    float diffAngle(const Point &P);
    void rotate(Point p);
    void boost(int thrust);
    void move(float t);
    void end();
    void play(Point P, int thrust);
    void bounce(Unit u);
    //void output(Move move);

};
class Checkpoint: public Unit
{
    public: 

};
class Collision
{
    Unit a;
    Unit b;
    float t;

};

int main()
{
vector<Point*> list_checkpoint;
int boost = 0;
int shield =0;
int checkpoint_r = 600;
int k_dist=2;
int thrust;
int pop_speed_adapt = 5;
int pop_speed_x = 0;
int pop_speed_y = 0;
bool tour_complet = false;
    // game loop
    while (1) {
        int x;
        int y;
        int x_before;
        int y_before;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        int opponent_x;
        int opponent_y;
        float angle_calculé;
        angle_calculé = asin((float)(next_checkpoint_y-y)/(float)next_checkpoint_dist);
      //  cerr << "valeur de l'angle avec le next checkpoint selon l'input " << next_checkpoint_angle << endl;
      // cerr << "valeur de l'angle selon mon calcul avec arcsin " << angle_calculé << endl;
        cin >> opponent_x >> opponent_y; cin.ignore();
        int next_checkpoint_number;
        pop_speed_x = x -x_before;
        pop_speed_y = y - y_before;
        Point *joueur = new Point(x,y);
        Point *boss = new Point(opponent_x, opponent_y);
        Point *next_checkpoint = new Point(next_checkpoint_x, next_checkpoint_y);
        unsigned int size = list_checkpoint.size();
        bool element_in_vector = false;
        if (tour_complet == false){
            for (unsigned int i = 0; i < size; i++){
                cerr << "Checkpoint"<< i <<" coordonées (" <<list_checkpoint[i]->x << "," << list_checkpoint[i]->y <<")" <<endl; 
            if (list_checkpoint[i]->x == next_checkpoint_x and list_checkpoint[i]->y == next_checkpoint_y){
                if ( i == 0 and size > 1){
                    cerr << " on met le tour complet a true " << endl;
                    tour_complet = true;
                }
                element_in_vector = true;
                next_checkpoint_number = i;
                break;
            };
            
            };
            if (element_in_vector == false){
            list_checkpoint.push_back(next_checkpoint);
            };
        }
        next_checkpoint->closest(*joueur, *boss);
        /*
        if (next_checkpoint->closest(*joueur,*boss).x == joueur->x and joueur->distance(*boss) <= 700 and shield == 0){
            cout << next_checkpoint_x << " " << next_checkpoint_y << " SHIELD" <<  endl;
            shield += 1;
            cerr << "cas shield " << endl;
        }
        */

        // on test si on peut utiliser le boost
        if (next_checkpoint_dist >= 8000 and abs(next_checkpoint_angle) <= 1){
            cout << next_checkpoint_x << " " << next_checkpoint_y << " BOOST" <<  endl;
            cerr << "cas boost" << endl;
        }

        // on fait un cas particulier si on est proche du prochain checkpoint et qu'on connait ceux d'après.

        else if((abs(next_checkpoint_x - x) <= abs(pop_speed_adapt * pop_speed_x)) and abs(next_checkpoint_y - y) <= abs(pop_speed_adapt * pop_speed_y) and tour_complet == true){
            thrust = 100;
            cout << list_checkpoint[next_checkpoint_number]->x << " " << list_checkpoint[next_checkpoint_number]->y << " " << thrust << endl;
            cerr << "ON VISE LE POINT D'APRES" << endl;
        }
        // cas normal d'avancement
        else{
            thrust = 100;
            thrust = int(min(float(thrust), thrust * abs(1 - float(next_checkpoint_angle)/90)));
            thrust = min(thrust * float(next_checkpoint_dist)/(k_dist*checkpoint_r),float (thrust));
            // next_checkpoint_x -= pop_speed_adapt * pop_speed_x;
            // next_checkpoint_y -= pop_speed_adapt * pop_speed_y;
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << endl;
        }
        x_before = x;
        y_before = y;
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        
    }
}
