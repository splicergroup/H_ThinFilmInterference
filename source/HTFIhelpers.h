// ---------------------------------------
// H_ThinFilmInterference
// By Ryan Hussain
// Contributer, Chi Chu Chang
// Open sourced under the MIT license

#include <ai.h>
#include <string>
#include <cmath>

struct ShaderData
{
    std::string user_data_1;
};

// H_REFRACT - refraction calculations helper function
AtVector H_REFRACT ( AtVector dir, AtVector normal, float ior_in, float ior_out ) {

    AtVector _dir, _normal, _facing, _refractray;
    float _ior_in, _ior_out, _eta, _k;

    _dir = dir;
    _normal = normal;
    _ior_in = ior_in;
    _ior_out = ior_out;
    _eta = _ior_in / _ior_out;

    // check inside:outside
    if (AiV3Dot(_normal, _dir) > 0) { 
        _facing = -_normal;
        _eta = _ior_out / _ior_in;
    }
    else {
        _facing = _normal;
    }
    
    // check for total internal reflection
    _k = 1.0f - (_eta * _eta) * (1.0f - AiV3Dot(_facing, _dir) * AiV3Dot(_facing, _dir) );

    if (_k < 0.0f) {
        _refractray = _dir - 2.0f * AiV3Dot(_dir, _facing) * _facing;
    }
    else {
        _refractray = _eta * _dir - (_eta * AiV3Dot(_facing, _dir) + sqrt(_k)) * _facing;
    }

    return _refractray;
}


// H_SIGNF - returns -1 if float input is less than 0, otherwise 1
float H_SIGNF( float input ) {
    float _input;
    int _sign;
    _input = input;
    
    if (_input == 0) _sign = 0;
    else if (_input > 0) _sign = 1;
    else _sign = -1;

    return _sign;
}


// AiPoint2Col - convert arnold vector to color
AtColor AiPoint2Col (AtPoint *point)

	{
		AtColor color;
		float At_x, At_y, At_z;

        At_x = (*point).x;
        At_y = (*point).y;
        At_z = (*point).z;
        color = AiColor(At_x, At_y, At_z);

        return color;
	}


// Wavelength_to_RGB - convert wavelength to color
AtVector Wavelength_to_RGB(float wl)
{

    float w = wl;
    float R, G, B;

    if (w >= 380 && w < 440){
        R = -(w - 440.0) / (440.0 - 350.0);
        G = 0.0;
        B = 1.0;
    }

    else if (w >= 440 && w < 490){
        R = 0.0;
        G = (w - 440.0) / (490. - 440.0);
        B = 1.0;
    }

    else if (w >= 490 && w < 510){
        R = 0.0;
        G = 1.0;
        B = -(w - 510.0) / (510.0 - 490.0);
    }
    
    else if (w >= 510 && w < 580){
        R = (w - 510.0) / (580.0 - 510.0);
        G = 1.0;
        B = 0.0;
    }
    
    else if (w >= 580 && w < 645){
        R = 1.0;
        G = -(w - 645.0) / (645.0 - 580.0);
        B = 0.0;
    }

    else if (w >= 645 && w <= 780){
        R = 1.0;
        G = 0.0;
        B = 0.0;
    }

    else{
        R = 0.0;
        G = 0.0;
        B = 0.0;
    }

    float SSS;

    //intensity correction
    if (w >= 380 && w < 420){
        SSS = 0.3 + 0.7*(w - 350) / (420 - 350);
    }
    else if (w >= 420 && w <= 700){
        SSS = 1.0;
    }

    else if (w > 700 && w <= 780)
        SSS = 0.3 + 0.7*(780 - w) / (780 - 700);

    else{
        SSS = 0.0;
    }

    SSS *= 255;

    AtVector returnVec;
    AiV3Create(returnVec, SSS*R/255, SSS*G/255, SSS*B/255);
    return returnVec;
}


// map - remap values
float map(float value, float istart, float istop, float ostart, float ostop) 
{
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
