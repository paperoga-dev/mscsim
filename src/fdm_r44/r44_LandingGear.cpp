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

#include <fdm_r44/r44_LandingGear.h>
#include <fdm_r44/r44_Aircraft.h>

#include <fdm/utils/fdm_String.h>
#include <fdm/xml/fdm_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

R44_LandingGear::R44_LandingGear( const R44_Aircraft *aircraft, DataNode *rootNode ) :
    LandingGear( aircraft, rootNode ),
    _aircraft ( aircraft )
{}

////////////////////////////////////////////////////////////////////////////////

R44_LandingGear::~R44_LandingGear() {}

////////////////////////////////////////////////////////////////////////////////

void R44_LandingGear::readData( XmlNode &dataNode )
{
    if ( dataNode.isValid() )
    {
        int result = FDM_SUCCESS;

        XmlNode wheelNode = dataNode.getFirstChildElement( "wheel" );

        while ( result == FDM_SUCCESS && wheelNode.isValid() )
        {
            Wheel wheel;

            std::string name = wheelNode.getAttribute( "name" );

            wheel.readData( wheelNode );

            result = _wheels.addWheel( name.c_str(), wheel );

            wheelNode = wheelNode.getNextSiblingElement( "wheel" );
        }

        if ( result != FDM_SUCCESS ) XmlUtils::throwError( __FILE__, __LINE__, dataNode );
    }
    else
    {
        XmlUtils::throwError( __FILE__, __LINE__, dataNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

void R44_LandingGear::computeForceAndMoment()
{
    _for_bas.zeroize();
    _mom_bas.zeroize();

    for ( Wheels::iterator it = _wheels.begin(); it != _wheels.end(); ++it )
    {
        Wheel &wheel = (*it).second;

        double position = 1.0;
        if ( wheel.isInputValid() )
        {
            position = wheel.getInputValue();
        }

        if ( position >= 1.0 )
        {
            Vector3 r_c_bas;
            Vector3 n_c_bas;

            getIsect( wheel.getRa_BAS(), wheel.getRu_BAS(), &r_c_bas, &n_c_bas );

            wheel.computeForceAndMoment( _aircraft->getVel_BAS(),
                                         _aircraft->getOmg_BAS(),
                                         r_c_bas,
                                         n_c_bas,
                                         _steering, _antiskid );

            _for_bas += wheel.getFor_BAS();
            _mom_bas += wheel.getMom_BAS();
        }
    }

    if ( !_for_bas.isValid() || !_mom_bas.isValid() )
    {
        Exception e;

        e.setType( Exception::UnexpectedNaN );
        e.setInfo( "NaN detected in the landing gear model." );

        FDM_THROW( e );
    }
}

////////////////////////////////////////////////////////////////////////////////

void R44_LandingGear::update()
{
    //////////////////////
    LandingGear::update();
    //////////////////////

    _brake_l = 0.0;
    _brake_r = 0.0;

    _ctrlAngle = 0.0;

    _antiskid = _aircraft->getDataInp()->controls.abs;
    _steering = false;

    for ( Wheels::iterator it = _wheels.begin(); it != _wheels.end(); ++it )
    {
        Wheel &wheel = (*it).second;

        Vector3 r_c_bas;
        Vector3 n_c_bas;

        getIsect( wheel.getRa_BAS(), wheel.getRu_BAS(), &r_c_bas, &n_c_bas );

        wheel.integrate( _aircraft->getTimeStep(),
                         _aircraft->getVel_BAS(),
                         _aircraft->getOmg_BAS(),
                         r_c_bas,
                         n_c_bas,
                         _steering );
    }
}