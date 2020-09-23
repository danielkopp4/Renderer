#ifndef __film_hpp_
#define __film_hpp_

#include "radiance.hpp"
#include "vector.hpp"
#include<iostream>

class Film {
private:
    Radiance middle_grey;

    Radiance*** samples; // three dimential array because each pixel has a certain amount of samples
    Vector** image; // fully rendered image so far (maybe convert color from vector to a custom color class)
    
    int samples_per_pixel;
    int samples_progressed;
    int height;
    int width;

    Radiance avg_sample_set(Radiance* sample_set, int samples_progressed) const; // actually a non member helper function move somewhere else
public:
    Film(int samples_per_pixel_, int height_, int width_) : samples_per_pixel(samples_per_pixel_), height(height_), width(width_), samples_progressed(0) {}

    void tone_map(); // converts samples to rgb pixels (global tone mapping)
    void init();
    void initialize_arr();

    std::ostream& write_ppm(std::ostream &out);

    void add_sample(int row, int col, Radiance sample);

    int get_height() const { return height; }
    int get_width() const { return width; }

    void increment_sample_count() { samples_progressed++; }
    int get_total_samples() const { return samples_per_pixel; }
};

#endif
