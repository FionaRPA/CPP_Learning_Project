#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int nb_aircraft_crash = 0;
    bool compare_to_aircraft(Aircraft &first_aircraft, Aircraft &second_aircraft) const;


public:
    void add(std::unique_ptr<Aircraft> aircraft);
    void countAircraft(std::string company);
    bool move() override;
    int get_required_fuel() const;
    void write_aircraft_crash() const{std::cout << "<< number of aircraft crash >> " << nb_aircraft_crash << std::endl;};
};
