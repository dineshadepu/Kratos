//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Ruben Zorrilla
//
//

#if !defined (KRATOS_EULER_LAW_3D_H_INCLUDED)
#define  KRATOS_EULER_LAW_3D_H_INCLUDED

// System includes

// External includes

// Project includes
#include "includes/constitutive_law.h"

namespace Kratos
{
    /**
     * Defines an Euler fluid constitutive law
     * This material law represents a null shear stress contribution.
     */
    class Euler3DLaw : public ConstitutiveLaw
    {
    public:
        /**
         * Type Definitions
         */

        /**
         * Counted pointer of Euler3DLaw
         */
        KRATOS_CLASS_POINTER_DEFINITION(Euler3DLaw);

        /**
         * Life Cycle
         */

        /**
         * Default constructor.
         */
        Euler3DLaw();

        /**
         * Clone function (has to be implemented by any derived class)
         * @return a pointer to a new instance of this constitutive law
         */
        ConstitutiveLaw::Pointer Clone() const override;

        /**
         * Copy constructor.
         */
        Euler3DLaw (const Euler3DLaw& rOther);


        /**
         * Destructor.
         */
        ~Euler3DLaw() override;

        /**
         * Operators
         */

        /**
         * Operations needed by the base class:
         */

        /**
         * @return Working space dimension constitutive law
         */
        SizeType WorkingSpaceDimension() override;

        /**
         * @return Size of the strain vector (in Voigt notation) for the constitutive law
         */
        SizeType GetStrainSize() override;

        void CalculateMaterialResponseCauchy (Parameters& rValues) override;

        /**
         * This function is designed to be called once to check compatibility with element
         * @param rFeatures
         */
        void GetLawFeatures(Features& rFeatures) override;

        /**
         * Input and output
         */

        /**
         * Turn back information as a string.
         */
        std::string Info() const override {
            std::stringstream buffer;
            buffer << "Euler3DLaw #";
            return buffer.str();
        };

        /**
         * Print information about this object.
         */
        void PrintInfo(std::ostream& rOStream) const override {
            rOStream << Info();
        };

        /**
         * Print object's data.
         */
        void PrintData(std::ostream& rOStream) const override {
            rOStream << Info();
        };

    private:

        ///@name Static Member Variables
        ///@{

        ///@}
        ///@name Member Variables
        ///@{

        ///@}
        ///@name Private Operators
        ///@{

        ///@}
        ///@name Private Operations
        ///@{

        ///@}
        ///@name Private  Access
        ///@{

        ///@}
        ///@name Serialization
        ///@{

        friend class Serializer;

        void save(Serializer& rSerializer) const override {
            KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, ConstitutiveLaw )
        }

        void load(Serializer& rSerializer) override {
            KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, ConstitutiveLaw )
        }

    }; // Class Euler3DLaw
}  // namespace Kratos.
#endif // KRATOS_EULER_LAW_3D_H_INCLUDED  defined 
