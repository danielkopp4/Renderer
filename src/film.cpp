#include "film.hpp"
#include "vector.hpp"
#include<iostream>
#include<iomanip>

Film::~Film() {
    for (int i = 0; i < height; ++i) {
        delete [] image[i];
        for (int j = 0; j < width; ++j) {
            delete [] samples[i][j];
        }
        delete [] samples[i];
    }
    
    delete [] image;
    delete [] samples;
}

Radiance Film::avg_sample_set(Radiance* sample_set, int samples_progressed) const {
    Radiance sum;

    for (int i = 0; i < samples_progressed; ++i) {
        sum = sum + sample_set[i];
    }
    

    return sum / samples_progressed;
}

// implementation of Reinhard global tone mapping approach
void Film::tone_map() { // i might need to standardize the colors instead of get an average for each color 
    Radiance Lsum = Radiance(0, 0, 0);
    double N = width * height;
    int not_counted = 0;
    for (int i = 0; i < height; ++i) {
        Radiance Lintermediate = Radiance(1, 1, 1);
        for (int j = 0; j < width; ++j) {
            Radiance avg = avg_sample_set(samples[i][j], samples_progressed);
            if (avg.get_average_light() == 0) {
                not_counted++;
            } else {
                Lsum = Lsum + avg.log();
            }
             // redefine to variable delta
            // std::cout << (avg_sample_set(samples[i][j], samples_progressed)+ 0.01).log().get_r() << std::endl;
            
        }
        // std::cout << Lsum.get_b() << std::endl;
    }
    // std::cout << Lsum.get_r() << std::endl;
    
    // double Lavg = (Lsum / N).exp().get_average_light();
    // Radiance Lavg = (Lsum / N).exp();
    double Lavg = (Lsum / (N - not_counted)).exp().get_average_light();
    // std::cout << Lavg << std::endl; 
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Radiance Lscaled = (avg_sample_set(samples[i][j], samples_progressed) / Lavg) * middle_grey; // potentially store a precomputed verson of the avg bc its used twice
            
            // if (int(Lscaled.get_r()) != 0) {
            //     std::cout << Lscaled.get_r() << std::endl;
            // }
            Radiance Lout = Lscaled / (Lscaled + 1);
            Lout = Lout * 255; // remove magic number !!!
            image[i][j] = Vector(Lout.get_r(), Lout.get_g(), Lout.get_b());
            // std::cout << "at (" << i << ", " << j << "): " << image[i][j] << std::endl;
            
        }
    }
}

void Film::init() {
    middle_grey = Radiance(1, 1, 1); // see if this value can be calculated
    initialize_arr();
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         samples[i][j][0] = Radiance(500*std::log(0.01*(i+1) + 1), 0.1, 1);
    //     }
    // }
    samples_progressed = 0;
}

void Film::add_sample(int row, int col, Radiance sample) {
    samples[row][col][samples_progressed] = sample;
}

void Film::initialize_arr() {
    samples = new Radiance**[height];
    image = new Vector*[height];

    for (int i = 0; i < height; ++i) {
        samples[i] = new Radiance*[width];
        image[i] = new Vector[width];
        for (int j = 0; j < width; ++j) {
            samples[i][j] = new Radiance[samples_per_pixel];
        }
    }
}

std::ostream& Film::write_ppm(std::ostream &out) {
    tone_map();
    // print header
    out << "P3" << std::endl;
    // define max val in class and remove magic number
    int max_val = 255;
    out << std::setprecision(0);
    out << std::fixed;
    out << width << " " << height << " " << max_val << std::endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int c = 0; c < 3; ++c) {
                out << image[i][j][c];
                out << " ";
            }
            out << "\t";
        }
        out << "\n";
    }
    return out;
}

void Film::print(std::ostream &out) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            out << avg_sample_set(samples[i][j], samples_progressed).get_average_light() << ", ";
        }
        out << std::endl;
    }
}