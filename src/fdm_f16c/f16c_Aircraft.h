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
#ifndef F16C_AIRCRAFT_H
#define F16C_AIRCRAFT_H

////////////////////////////////////////////////////////////////////////////////

#include <fdmMain/fdm_Aircraft.h>

#include <fdm_f16c/f16c_Aerodynamics.h>
#include <fdm_f16c/f16c_Controls.h>
#include <fdm_f16c/f16c_LandingGear.h>
#include <fdm_f16c/f16c_Mass.h>
#include <fdm_f16c/f16c_Propulsion.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

/**
 * @brief F-16 aircraft class.
 */
class F16C_Aircraft : public Aircraft
{
public:

    /** Constructor. */
    F16C_Aircraft();

    /** Destructor. */
    ~F16C_Aircraft();

    inline F16C_Aerodynamics* getAero() { return m_aero; }
    inline F16C_Controls*     getCtrl() { return m_ctrl; }
    inline F16C_LandingGear*  getGear() { return m_gear; }
    inline F16C_Mass*         getMass() { return m_mass; }
    inline F16C_Propulsion*   getProp() { return m_prop; }

    inline const F16C_Aerodynamics* getAero() const { return m_aero; }
    inline const F16C_Controls*     getCtrl() const { return m_ctrl; }
    inline const F16C_LandingGear*  getGear() const { return m_gear; }
    inline const F16C_Mass*         getMass() const { return m_mass; }
    inline const F16C_Propulsion*   getProp() const { return m_prop; }

private:

    F16C_Aerodynamics *m_aero;  ///< aerodynamics model
    F16C_Controls     *m_ctrl;  ///< controls model
    F16C_LandingGear  *m_gear;  ///< landing gear model
    F16C_Mass         *m_mass;  ///< mass and inertia model
    F16C_Propulsion   *m_prop;  ///< propulsion model
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // F16C_AIRCRAFT_H