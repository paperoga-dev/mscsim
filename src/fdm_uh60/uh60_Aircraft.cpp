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

#include <fdm_uh60/uh60_Aircraft.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

UH60_Aircraft::UH60_Aircraft() :
    Aircraft()
{
    Aircraft::m_aero = m_aero = new UH60_Aerodynamics( this );
    Aircraft::m_ctrl = m_ctrl = new UH60_Controls( this );
    Aircraft::m_gear = m_gear = new UH60_LandingGear( this );
    Aircraft::m_mass = m_mass = new UH60_Mass( this );
    Aircraft::m_prop = m_prop = new UH60_Propulsion( this );

    readData( "data/fdm/uh60/uh60_fdm.xml" );
}

////////////////////////////////////////////////////////////////////////////////

UH60_Aircraft::~UH60_Aircraft()
{
    if ( m_aero ) delete m_aero;
    m_aero = 0;

    if ( m_ctrl ) delete m_ctrl;
    m_ctrl = 0;

    if ( m_gear ) delete m_gear;
    m_gear = 0;

    if ( m_mass ) delete m_mass;
    m_mass = 0;

    if ( m_prop ) delete m_prop;
    m_prop = 0;
}