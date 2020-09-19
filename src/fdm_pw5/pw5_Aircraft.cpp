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

#include <fdm_pw5/pw5_Aircraft.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

PW5_Aircraft::PW5_Aircraft( DataNode *rootNode, const DataInp *dataInp, DataOut *dataOut ) :
    Aircraft( rootNode, dataInp, dataOut ),

    _aero ( 0 ),
    _ctrl ( 0 ),
    _gear ( 0 ),
    _mass ( 0 ),
    _prop ( 0 )
{
    Aircraft::_aero = _aero = new PW5_Aerodynamics ( this, _rootNode );
    Aircraft::_ctrl = _ctrl = new PW5_Controls     ( this, _rootNode );
    Aircraft::_gear = _gear = new PW5_LandingGear  ( this, _rootNode );
    Aircraft::_mass = _mass = new PW5_Mass         ( this, _rootNode );
    Aircraft::_prop = _prop = new PW5_Propulsion   ( this, _rootNode );

    readFile( Path::get( "data/fdm/pw5/pw5_fdm.xml" ).c_str() );
}

////////////////////////////////////////////////////////////////////////////////

PW5_Aircraft::~PW5_Aircraft()
{
    FDM_DELPTR( _aero );
    FDM_DELPTR( _ctrl );
    FDM_DELPTR( _gear );
    FDM_DELPTR( _mass );
    FDM_DELPTR( _prop );
}

////////////////////////////////////////////////////////////////////////////////

void PW5_Aircraft::initialize( bool engineOn )
{
    /////////////////////////////////
    Aircraft::initialize( engineOn );
    /////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void PW5_Aircraft::updateOutputData()
{
    /////////////////////////////
    Aircraft::updateOutputData();
    /////////////////////////////

    // controls
    _dataOut->controls.ailerons = _ctrl->getAilerons();
    _dataOut->controls.elevator = _ctrl->getElevator();
    _dataOut->controls.rudder   = _ctrl->getRudder();
}