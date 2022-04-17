#include "aircraft_manager.hpp"

#include <utility>
#include <iostream>
#include <cassert>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft);
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::compare_to_aircraft(Aircraft &firstaircraft, Aircraft &secondaircraft) const
{
    if(!firstaircraft.has_terminal() && secondaircraft.has_terminal())
    {
        return true;
    }
    return firstaircraft.get_fuel() > secondaircraft.get_fuel();
}

bool AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [this](std::unique_ptr<Aircraft> &a, std::unique_ptr<Aircraft> &b)
              {return compare_to_aircraft(*a, *b);});

    aircrafts.erase(
        std::remove_if(aircrafts.begin(), aircrafts.end(),
                       [this](const auto &aircraft) {
                           try{
                               return !(*aircraft).move();
                           }
                           catch(const AircraftCrash& err)
                           {
                               nb_aircraft_crash += 1;
                               std::cerr << err.what() << std::endl;
                               return true;
                           }
                       }),
        aircrafts.end());
    return true;
}

void AircraftManager::countAircraft(std::string airline)
{
    auto res = std::count_if(aircrafts.begin(), aircrafts.end(),
                             [airline](const std::unique_ptr<Aircraft> &aircraft) {
                                 return (*aircraft).get_company().find(airline) != std::string::npos;}) ;

    std::cout << "Airline " << airline << " has " << res << " Aircraft" << std::endl;
}

int AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                           [](int fuelTotal,
                           const std::unique_ptr<Aircraft> &aircraft){
                                return fuelTotal + (*aircraft).get_required_fuel();
                           }
    );
}

