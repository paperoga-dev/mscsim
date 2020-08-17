/****************************************************************************//*
 * Copyright (C) 2020 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef F35A_CONTROLS_H
#define F35A_CONTROLS_H

////////////////////////////////////////////////////////////////////////////////

#include <fdm/main/fdm_Controls.h>

#include <fdm_f35a/f35a_FLCS.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

class F35A_Aircraft;    ///< aircraft class forward declaration

/**
 * @brief F-35A controls class.
 */
class F35A_Controls : public Controls
{
public:

    /** Constructor. */
    F35A_Controls( const F35A_Aircraft *aircraft, DataNode *rootNode );

    /** Destructor. */
    ~F35A_Controls();

    /**
     * Reads data.
     * @param dataNode XML node
     */
    void readData( XmlNode &dataNode );

    /** Initializes controls. */
    void initialize();

    /** Updates model. */
    void update();

    inline const F35A_FLCS* getFLCS() const { return _flcs; }

    inline double getAilerons()     const { return _flcs->getAilerons();     }
    inline double getAileronsNorm() const { return _flcs->getAileronsNorm(); }
    inline double getElevator()     const { return _flcs->getElevator();     }
    inline double getElevatorNorm() const { return _flcs->getElevatorNorm(); }
    inline double getRudder()       const { return _flcs->getRudder();       }
    inline double getRudderNorm()   const { return _flcs->getRudderNorm();   }
    inline double getFlapsLE()      const { return _flcs->getFlapsLE();      }
    inline double getFlapsLENorm()  const { return _flcs->getFlapsLENorm();  }
    inline double getFlapsTE()      const { return _flcs->getFlapsTE();      }
    inline double getFlapsTENorm()  const { return _flcs->getFlapsTENorm();  }
    inline double getAirbrake()     const { return _airbrake;      }
    inline double getAirbrakeNorm() const { return _airbrake_norm; }
    inline double getBrakeL()       const { return _brake_l;       }
    inline double getBrakeR()       const { return _brake_r;       }
    inline double getNoseWheel()    const { return _nose_wheel;    }

private:

    const F35A_Aircraft *_aircraft; ///< aircraft model main object

    Channel *_channelRoll;          ///< roll channel
    Channel *_channelPitch;         ///< pitch channel
    Channel *_channelYaw;           ///< yaw channel
    Channel *_channelRollTrim;      ///< roll trim channel
    Channel *_channelPitchTrim;     ///< pitch trim channel
    Channel *_channelYawTrim;       ///< yaw trim channel
    Channel *_channelAirbrake;      ///< airbrake channel
    Channel *_channelBrakeL;        ///< left brake channel
    Channel *_channelBrakeR;        ///< right brake channel
    Channel *_channelNoseWheel;     ///< nose wheel channel

    F35A_FLCS *_flcs;               ///< Fligt Control System

    double _airbrake_max;           ///< [rad] airbrake deflection limit

    double _airbrake;               ///< [rad] airbrake deflection
    double _airbrake_norm;          ///< [-] normalized airbrake deflection
    double _brake_l;                ///< [-] normalized left brake force
    double _brake_r;                ///< [-] normalized right brake force
    double _nose_wheel;             ///< [rad] nose wheel turn angle

    double _angleOfAttack;          ///<
    double _g_y;                    ///<
    double _g_z;                    ///<
    double _rollRate;               ///<
    double _pitchRate;              ///<
    double _yawRate;                ///<
    double _ctrlLat;                ///<
    double _trimLat;                ///<
    double _ctrlLon;                ///<
    double _trimLon;                ///<
    double _ctrlYaw;                ///<
    double _trimYaw;                ///<
    double _statPress;              ///<
    double _dynPress;               ///<
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // F35A_CONTROLS_H