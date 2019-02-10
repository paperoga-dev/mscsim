/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
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
#ifndef UH60_AERODYNAMICS_H
#define UH60_AERODYNAMICS_H

////////////////////////////////////////////////////////////////////////////////

#include <fdmMain/fdm_Aerodynamics.h>

#include <fdmMain/fdm_MainRotor.h>
#include <fdmMain/fdm_TailRotor.h>
#include <fdmMain/fdm_Stabilizer.h>

#include <fdm_uh60/uh60_Fuselage.h>
#include <fdm_uh60/uh60_StabilizerHor.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

class UH60_Aircraft; ///< aircraft class forward declaration

/**
 * @brief UH-60 aerodynamics class.
 */
class UH60_Aerodynamics : public Aerodynamics
{
public:

    /** Constructor. */
    UH60_Aerodynamics( const UH60_Aircraft *aircraft );

    /** Destructor. */
    ~UH60_Aerodynamics();

    /**
     * Reads data.
     * @param dataNode XML node
     */
    void readData( XmlNode &dataNode );

    /**
     * Initializes data referneces.
     */
    void initDataRefs();

    /**
     * Computes force and moment.
     */
    void computeForceAndMoment();

    /**
     * Updates model.
     */
    void update();

private:

    const UH60_Aircraft *m_aircraft;    ///< aircraft model main object

    MainRotor *m_mainRotor;             ///<
    TailRotor *m_tailRotor;             ///<
    UH60_Fuselage *m_fuselage;          ///<
    UH60_StabilizerHor *m_stabHor;      ///<
    Stabilizer *m_stabVer;              ///<

    DataRef m_drMainRotorAzimuth;       ///<
    DataRef m_drMainRotorConingAngle;   ///<
    DataRef m_drMainRotorDiskRoll;      ///<
    DataRef m_drMainRotorDiskPitch;     ///<
    DataRef m_drMainRotorCollective;    ///<
    DataRef m_drMainRotorCyclicLon;     ///<
    DataRef m_drMainRotorCyclicLat;     ///<
    DataRef m_drTailRotorAzimuth;       ///<

    double m_dcl_dpR_2v;                ///< [1/rad]
    double m_dcm_dqR_2v;                ///< [1/rad]
    double m_dcn_drR_2v;                ///< [1/rad]
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // UH60_AERODYNAMICS_H