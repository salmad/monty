#include "../include/polymer.h"
#include "../molecule.h"
#include "../include/integrate.h"
#include "../global.h"
# include <iostream>

# include <vector>
# include <cstdlib>
# include <iomanip>
# include <ctime>
# include <cmath>
# include <fstream>


using namespace std;

polymer::polymer()
{
    N = 10;
    M = new molecule [N];
//    molecule m2[N];
//    M = m1 ;//ctor
    delta = 1.0;
    k = 20.;
    pol_id++;
    id = pol_id;
    cout << "\ninit polymer ..." << endl;
    for (int i = 0; i < N; i++){
//        M[i] = molecule();
        M[i].q=-1.0;
        M[i].type=1;

        }

    //polymer id? we need it
}

void polymer::set_polymer(int Nset)
{
    N = Nset;
    molecule m1[N];
    M = m1 ;//ctor
    // delta is the spring length
    delta = 1.0;
    k = 20.;

}

void polymer::polymer_RW( /* int Nset  = 10 , */ double r /* = 0.0 */)
{

    // delta is the spring length
    delta = 1.0;
    k = 20.;


    double theta=acos(2*(drand48()-0.5));
    double phi=2.0*M_PI*drand48();
    double x = r*sin(theta)*cos(phi);
    double y = r*sin(theta)*sin(phi);
    double z = r*cos(theta);
    M[0].move_to_position(x,y,z);


    for (int i = 1; i < N; ++i)
    {

        M[i].move_to_position(M[i-1]);
        M[i].advance(1,delta);
    }

}

// function to create polymer by random walk... to be done

// implement here polymer move functions...

double polymer::bond_energy()
{
    double en = 0.0;
    for (int i = 0; i< N-1;i++){
        molecule mi   = M[i];
        molecule next = M[i+1];
        double d = Distance(mi,next);
        en           += k*(d-delta)*(d-delta);
    }
    //dtor
    return en;
}

void polymer::print(){

    cout << "\n Print polymer ID " << id << endl;
    cout << " N = " << N << " ;  "<< endl;
    for (int i = 0; i < N; ++i)
    {
        /* print all molecules */
        M[i].print();
    }
    cout << " Polymer printed ..." << endl;
}

polymer::~polymer()
{
    delete [] M;
    //dtor
}
