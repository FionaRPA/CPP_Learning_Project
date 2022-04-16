#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"


using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    context_initializer(argc, argv)
{
    create_keystrokes();
    // On doit ajouter le manager à la move_queue, afin que timer() appelle bien sa fonction move() à chaque
    // frame.
    GL::move_queue.emplace(&manager);
}


void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { manager.add(factory.create_random_aircraft()); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    GL::keystrokes.emplace('z', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
    GL::keystrokes.emplace('a', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 180u); });

    GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });

    for(auto i = 0; i < 7; i++){
        GL::keystrokes.emplace('0' + i, [i, this]() { manager.countAircraft(factory.get_airline(i)); });
    }
    GL::keystrokes.emplace('m', [this]() { manager.write_aircraft_crash(); });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keystrokes have meaning:" << std::endl;
    for (const auto& [ks_pair_first, ks_pair_second] : GL::keystrokes)
    {
        std::cout << ks_pair_first << ' ';
    }
    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    Airport *airport = new Airport { one_lane_airport, manager, Point3D { 0, 0, 0 },
                                     new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::Displayable::display_queue.emplace_back(airport);
    factory.update_airport(*airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }
    init_airport();
    //init_aircraft_types();
    GL::loop();
}