/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::thermophysicalFunctions::NSRDS14

Description
    NSRDS function number 114

    Source:
    \verbatim
                      NSRDS - AICHE
                 Data Compilation Tables
                    of Properties of
                     Pure Compounds

        Design Institute for Physical Property Data
          American Institute of Chemical Engineers
                  345 East 47th Street
                New York, New York 10017

         National Standard Reference Data System
         American Institute of Chemical Engineers

          T.E. Daubert       -       R.P. Danner

            Department of Chemical Engineering
            The Pennsylvania State University
                University Park, PA 16802
    \endverbatim

\*---------------------------------------------------------------------------*/

#ifndef NSRDS14ThermophysicalFunction_H
#define NSRDS14ThermophysicalFunction_H

#include "thermophysicalFunction.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace thermophysicalFunctions
{

/*---------------------------------------------------------------------------*\
                           Class NSRDS14 Declaration
\*---------------------------------------------------------------------------*/

class NSRDS14
:
    public thermophysicalFunction
{
    // Private Data

        // NSRDS function 114 coefficients
        scalar Tc_, a_, b_, c_, d_;


public:

    //- Runtime type information
    TypeName("NSRDS14");


    // Constructors

        //- Construct from components
        NSRDS14
        (
            const scalar Tc,
            const scalar a,
            const scalar b,
            const scalar c,
            const scalar d
        );

        //- Construct from dictionary
        NSRDS14(const dictionary& dict);


    // Member Functions

        //- Evaluate the function and return the result
        scalar f(scalar, scalar T) const
        {
            scalar Tdash = min(T, Tc_ - rootVSmall);

            scalar t = 1.0 - Tdash/Tc_;
            return
                a_*a_/(t + rootVSmall) + b_ - t
               *(
                   2.0*a_*c_
                 + t*(a_*d_ + t*(c_*c_/3.0 + t*(0.5*c_*d_ + 0.2*d_*d_*t)))
                );
        }

        using thermophysicalFunction::write;

        //- Write the function coefficients
        virtual void write(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace thermophysicalFunctions
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
