#ifndef __film_hpp_
#define __film_hpp_

#include "radiance.hpp"
#include "vector.hpp"
#include <iostream>
#include <mutex>

class Film {
private:
    Radiance middle_grey;

    Radiance*** samples; // three dimential array because each pixel has a certain amount of samples
    Vector** image; // fully rendered image so far (maybe convert color from vector to a custom color class)
    
    int samples_per_pixel;
    int samples_progressed;
    int sample_pixels_received;
    int height;
    int width;

    std::mutex mutex;

    Radiance avg_sample_set(Radiance* sample_set, int samples_progressed) const; // actually a non member helper function move somewhere else
public:
    Film(int samples_per_pixel_, int height_, int width_) : samples_per_pixel(samples_per_pixel_), height(height_), width(width_), samples_progressed(0) {}
    ~Film();

    void tone_map(); // converts samples to rgb pixels (global tone mapping)
    void init();
    void initialize_arr();

    double progress() { return sample_pixels_received / (height * width * samples_per_pixel); }

    void print(std::ostream &out);

    std::ostream& write_ppm(std::ostream &out);

    void add_sample(int row, int col, Radiance sample, int count);

    int get_height() const { return height; }
    int get_width() const { return width; }

    void increment_sample_count() { samples_progressed++; }
    void set_sample_count(int count) { samples_progressed = count; } 
    int get_total_samples() const { return samples_per_pixel; }
    void save_intermediate() const;
};

#endif
