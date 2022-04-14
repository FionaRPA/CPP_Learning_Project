#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <list>

#include "airport.hpp"


class AircraftFactory
{
private:
    Airport* airport = nullptr;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

    static constexpr size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    inline void init_aircraft_types()
    {
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .08f, .03f, MediaPath { "concorde_af.png" } };
    }

public:
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type) const
    {
        assert(airport); // make sure the airport is initialized before creating aircraft
        while(true){
            const std::string flight_number = airlines[std::rand()%8] + std::to_string(1000 + (rand() % 9000));
            const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // angle aléatoire
            const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
            const Point3D direction = (-start).normalize();
            // On gère maintenant les Aircraft avec des unique_ptr de bout en bout
            return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
            // }
        }
    }

    std::unique_ptr<Aircraft> create_random_aircraft() const
    {
        return create_aircraft(*(aircraft_types[rand() % 3]));
    }

    AircraftFactory(){init_aircraft_types();};

    ~AircraftFactory()
    {
        delete airport;
    }

    void update_airport(Airport &new_airport){
        airport = &new_airport;
    }

    std::string get_airline(int cpt){
        return airlines[cpt];
    }
};